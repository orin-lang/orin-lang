#!/usr/bin/env node
// A minimal Orbit host for tests (ADR-0055): runs an Orin program built with `--target=wasm64-orbit` or `--target=wasm32-orbit` under Node (>= 24, for
// memory64 and table64) with the same import contract as Orbit (orin-lang/orbit, docs/host-abi.md), so the conformance
// suite can run in CI without building Orbit. It is NOT a sandbox and NOT Orbit: Orbit is the runtime; this only serves
// the two capabilities the target uses.
//
//   node tools/wasm_run.mjs <module.wasm> [--deny CAP]... [--app-arg X]... [--stdin] [--mount /guest=hostdir[:rw]]... [--cwd /guest/dir] [--fs-max-handles N]
//
// Capabilities served: log/v1, clock/v1, process/v1 (arguments after argv[0] = the module name; stdin with --stdin) and fs/v1 (mounts
// as in `orbit run --grant fs:/guest=./dir:rw`, the same statuses and path rules, synchronous Node file calls). NOT served: net/v1 (it
// needs real waits; run such modules on Orbit: tools/test_orbit.py). The semantics follow orbit docs/host-abi.md sections 4b-4c.
//
// Like Orbit it fails closed at load: every import must be an `orbit:` capability it serves with the right shape, and when
// the module carries an `orbit.manifest` section every imported capability must be listed there (exit 2 otherwise).
// orbit:log/v1 write: level >= 4 (error) goes to stderr, everything else to stdout, one line per record.
// Exit status: the result of `orin_main`; after a trap, the status the program passed to exit (export orin_exit_status,
// e.g. 101 for an Orin trap), or 134 for any other trap (stack overflow, out-of-bounds access, abort).
import { readFileSync, writeSync } from 'node:fs';
import * as nodeFs from 'node:fs';
import * as nodePath from 'node:path';

const [file, ...rest] = process.argv.slice(2);
if (!file) {
  process.stderr.write('usage: node tools/wasm_run.mjs <module.wasm> [--deny CAP]...\n');
  process.exit(2);
}
const denied = new Set();
const appArgs = [], mounts = [];
let stdinGranted = false, cwd = '/', maxHandles = 64;
for (let i = 0; i < rest.length; i++) {
  if (rest[i] === '--deny' && i + 1 < rest.length) denied.add(rest[++i]);
  else if (rest[i] === '--app-arg' && i + 1 < rest.length) appArgs.push(rest[++i]);
  else if (rest[i] === '--stdin') stdinGranted = true;
  else if (rest[i] === '--cwd' && i + 1 < rest.length) cwd = rest[++i];
  else if (rest[i] === '--fs-max-handles' && i + 1 < rest.length) maxHandles = Number(rest[++i]);
  else if (rest[i] === '--mount' && i + 1 < rest.length) {
    const m = /^(\/[^=]*)=(.*?)(:rw|:ro)?$/.exec(rest[++i]);
    if (!m) { process.stderr.write('wasm_run: --mount expects /guest=hostdir[:rw|:ro]\n'); process.exit(2); }
    mounts.push({ guest: m[1].replace(/\/+$/, '') || '/', host: nodePath.resolve(m[2]), writable: m[3] === ':rw' });
  } else { process.stderr.write(`wasm_run: unknown argument ${rest[i]}\n`); process.exit(2); }
}
const fail = (msg) => { process.stderr.write(`wasm_run: ${msg}\n`); process.exit(2); };

let mod;
try { mod = new WebAssembly.Module(readFileSync(file)); } catch (e) { fail(`invalid module: ${e.message}`); }

let memory;
const decoder = new TextDecoder('utf-8', { fatal: true });
const write = (fd, text) => writeSync(fd, text);
const start = process.hrtime.bigint();
const caps = {
  'log/v1': {
    write(level, ptr, len) {
      if (level < 0 || level > 4) return -1;
      const p = Number(ptr), n = Number(len);
      if (p < 0 || n < 0 || n > 16384 || p + n > memory.buffer.byteLength) return -1;
      let text;
      try { text = decoder.decode(new Uint8Array(memory.buffer, p, n)); } catch { return -1; }
      write(level >= 4 ? 2 : 1, text + '\n');
      return 0;
    },
  },
  'clock/v1': {
    now_unix_nanos: () => BigInt(Date.now()) * 1000000n,
    monotonic_nanos: () => process.hrtime.bigint() - start,
  },
};
// ---- process/v1 and fs/v1 (host-abi.md sections 4b, 4c): statuses are negative i64 (returned as BigInt) --------------------------
const OK = 0, INVALID = -1, DENIED = -2, NOT_FOUND = -3, BAD_HANDLE = -4, TOO_LARGE = -5, QUOTA = -6, IO = -7, EXISTS = -12, NOT_DIR = -13, IS_DIR = -14;
const IO_MAX = 1 << 20;
const mem = () => new Uint8Array(memory.buffer);
const inRange = (p, n) => p >= 0 && n >= 0 && p + n <= memory.buffer.byteLength;
const putBytes = (ptr, cap, bytes) => {   // the length, or TOO_LARGE with nothing written
  const p = Number(ptr), c = Number(cap);
  if (c < 0 || !inRange(p, Math.min(c, bytes.length))) return BigInt(INVALID);
  if (bytes.length > c) return BigInt(TOO_LARGE);
  mem().set(bytes, p);
  return BigInt(bytes.length);
};
const argv = [nodePath.basename(file).replace(/\.[^.]*$/, ''), ...appArgs];
const statusOfErr = (e) => ({ ENOENT: NOT_FOUND, EACCES: DENIED, EPERM: DENIED, EISDIR: IS_DIR, ENOTDIR: NOT_DIR, EEXIST: EXISTS, EMFILE: QUOTA, ENAMETOOLONG: TOO_LARGE }[e.code] ?? IO);
// guest path -> { mount, host } | a negative status
function resolveGuest(ptr, len) {
  const p = Number(ptr), n = Number(len);
  if (!inRange(p, n)) return INVALID;
  let text;
  try { text = decoder.decode(mem().slice(p, p + n)); } catch { return INVALID; }
  if (text.includes('\0')) return INVALID;
  if (text === '') return NOT_FOUND;
  if (n > 4096) return TOO_LARGE;
  const parts = [];
  for (const c of (text.startsWith('/') ? text : cwd + '/' + text).split('/')) {
    if (c === '' || c === '.') continue;
    if (c === '..') parts.pop(); else parts.push(c);
  }
  const abs = '/' + parts.join('/');
  const mount = mounts.find((m) => m.guest === '/' || abs === m.guest || abs.startsWith(m.guest + '/'));
  // a proper ancestor of a mount is a read-only virtual directory that lists the mounts below it
  if (!mount) return mounts.some((m) => m.guest.startsWith(abs === '/' ? '/' : abs + '/')) ? { virtual: true, abs } : DENIED;
  const rest = abs.slice(mount.guest === '/' ? 0 : mount.guest.length);
  const host = nodePath.join(mount.host, rest);
  // confinement: the nearest existing ancestor, with links resolved, must stay inside the mount
  let probe = host;
  for (;;) {
    try { const real = nodeFs.realpathSync(probe); if (real !== mount.host && !real.startsWith(mount.host + nodePath.sep)) return DENIED; break; }
    catch { const up = nodePath.dirname(probe); if (up === probe) break; probe = up; }
  }
  return { mount, host, abs };
}
const handles = new Map();
let nextHandle = 1;
const addHandle = (h) => { if (handles.size >= maxHandles) return QUOTA; handles.set(nextHandle, h); return nextHandle++; };
const hget = (h) => handles.get(Number(h));
const big = (x) => BigInt(x);
caps['process/v1'] = {
  arg_count: () => argv.length,
  arg: (i, ptr, cap) => (i < 0 || i >= argv.length ? big(INVALID) : putBytes(ptr, cap, Buffer.from(argv[i]))),
  env_get: (np, nl, ptr, cap) => big(NOT_FOUND),
  stdin_read(ptr, cap, timeoutMs) {
    if (!stdinGranted) return big(DENIED);
    const n = Math.min(Number(cap), IO_MAX), p = Number(ptr);
    if (n < 0 || !inRange(p, n)) return big(INVALID);
    const buf = Buffer.alloc(n);
    let got = 0;
    try { got = nodeFs.readSync(0, buf, 0, n, null); } catch (e) { if (e.code !== 'EOF') return big(IO); }
    mem().set(buf.subarray(0, got), p);
    return big(got);
  },
};
caps['fs/v1'] = {
  open(ptr, len, mode) {
    const r = resolveGuest(ptr, len);
    if (typeof r === 'number') return big(r);
    if (r.virtual) return big(mode === 0 ? IS_DIR : DENIED);
    if (mode !== 0 && !r.mount.writable) return big(DENIED);
    try {
      const st = nodeFs.statSync(r.host, { throwIfNoEntry: false });
      if (st && st.isDirectory()) return big(IS_DIR);
      if (st && !st.isFile()) return big(DENIED);
      const fd = nodeFs.openSync(r.host, mode === 0 ? 'r' : mode === 1 ? 'w' : 'a');
      const h = addHandle({ fd, mode });
      if (h < 0) nodeFs.closeSync(fd);
      return big(h);
    } catch (e) { return big(statusOfErr(e)); }
  },
  read(h, ptr, cap) {
    const f = hget(h), p = Number(ptr);
    if (!f) return big(BAD_HANDLE);
    if (f.mode !== 0 || f.entries) return big(INVALID);
    const n = Math.min(Number(cap), IO_MAX);
    if (n < 0 || !inRange(p, n)) return big(INVALID);
    const buf = Buffer.alloc(n);
    try { const got = nodeFs.readSync(f.fd, buf, 0, n, null); mem().set(buf.subarray(0, got), p); return big(got); } catch (e) { return big(statusOfErr(e)); }
  },
  write(h, ptr, len) {
    const f = hget(h), p = Number(ptr), n = Math.min(Number(len), IO_MAX);
    if (!f) return big(BAD_HANDLE);
    if (f.mode === 0 || f.entries) return big(INVALID);
    if (!inRange(p, n)) return big(INVALID);
    try { return big(nodeFs.writeSync(f.fd, mem().slice(p, p + n))); } catch (e) { return big(statusOfErr(e)); }
  },
  flush: (h) => (hget(h) ? OK : BAD_HANDLE),
  close(h) {
    const f = hget(h);
    if (!f) return BAD_HANDLE;
    handles.delete(Number(h));
    if (!f.entries) nodeFs.closeSync(f.fd);
    return OK;
  },
  stat(ptr, len) {
    const r = resolveGuest(ptr, len);
    if (typeof r === 'number') return r === NOT_FOUND ? 0 : r;
    if (r.virtual) return 2;
    const st = nodeFs.statSync(r.host, { throwIfNoEntry: false });
    return !st ? 0 : st.isDirectory() ? 2 : 1;
  },
  size(ptr, len) {
    const r = resolveGuest(ptr, len);
    if (typeof r === 'number') return big(r);
    if (r.virtual) return big(IS_DIR);
    const st = nodeFs.statSync(r.host, { throwIfNoEntry: false });
    return big(!st ? NOT_FOUND : st.isDirectory() ? IS_DIR : st.size);
  },
  dir_open(ptr, len) {
    const r = resolveGuest(ptr, len);
    if (typeof r === 'number') return big(r);
    if (r.virtual) {
      const below = new Set(mounts.map((m) => m.guest.slice(r.abs === '/' ? 1 : r.abs.length + 1).split('/')[0]));
      return big(addHandle({ entries: [...below].map((n) => ({ name: Buffer.from(n), dir: true })), pos: 0 }));
    }
    try {
      const entries = nodeFs.readdirSync(r.host, { withFileTypes: true }).map((d) => ({ name: Buffer.from(d.name), dir: d.isDirectory() }));
      return big(addHandle({ entries, pos: 0 }));
    } catch (e) { return big(statusOfErr(e)); }
  },
  dir_next(h, ptr, cap) {
    const f = hget(h);
    if (!f) return big(BAD_HANDLE);
    if (!f.entries) return big(INVALID);
    if (f.pos >= f.entries.length) return 0n;
    const e = f.entries[f.pos];
    const n = Number(cap), p = Number(ptr);
    if (n < 0 || !inRange(p, Math.min(n, e.name.length))) return big(INVALID);
    if (e.name.length > n) return big(TOO_LARGE);
    mem().set(e.name, p);
    f.pos += 1;
    return big(e.name.length) | (e.dir ? 0x4000000000000000n : 0n);
  },
  dir_close(h) { return caps['fs/v1'].close(h); },
  realpath(ptr, len, out, cap) {
    const r = resolveGuest(ptr, len);
    if (typeof r === 'number') return big(r);
    if (r.virtual) return putBytes(out, cap, Buffer.from(r.abs));
    let probe = r.host, tail = '';
    for (;;) {
      try { probe = nodeFs.realpathSync(probe); break; }
      catch { const up = nodePath.dirname(probe); if (up === probe) break; tail = nodePath.join(nodePath.basename(probe), tail); probe = up; }
    }
    const realMount = nodeFs.realpathSync(r.mount.host);
    const rel = nodePath.join(nodePath.relative(realMount, probe), tail).split(nodePath.sep).filter(Boolean).join('/');
    return putBytes(out, cap, Buffer.from((r.mount.guest === '/' ? '' : r.mount.guest) + '/' + rel));
  },
  cwd: (out, cap) => putBytes(out, cap, Buffer.from(cwd)),
};

const manifest = WebAssembly.Module.customSections(mod, 'orbit.manifest');
let listed = null;
if (manifest.length > 1) fail('more than one orbit.manifest section');
if (manifest.length === 1) {
  try { listed = new Set(JSON.parse(new TextDecoder().decode(manifest[0])).requires); } catch (e) { fail(`bad manifest: ${e.message}`); }
}
const imports = {};
for (const imp of WebAssembly.Module.imports(mod)) {
  const m = /^orbit:([a-z]+\/v[0-9]+)$/.exec(imp.module);
  if (!m || imp.kind !== 'function' || !(m[1] in caps) || !(imp.name in caps[m[1]])) {
    fail(`unknown import ${imp.module}.${imp.name} (${imp.kind})`);
  }
  if (listed && !listed.has(m[1])) fail(`manifest mismatch: ${m[1]} is imported but not listed`);
  if (denied.has(m[1])) fail(`capability not granted: ${m[1]}`);
  (imports[imp.module] ??= {})[imp.name] = caps[m[1]][imp.name];
}
// the engine checks the signatures at instantiation: a wrong shape fails with a LinkError

let instance;
try { instance = new WebAssembly.Instance(mod, imports); } catch (e) { fail(`instantiate failed: ${e.message}`); }
memory = instance.exports.memory;
if (!(memory instanceof WebAssembly.Memory) || typeof instance.exports.orin_main !== 'function') {
  fail('the module exports no memory or no orin_main');
}
let status;
try {
  status = instance.exports.orin_main();
} catch (e) {
  if (!(e instanceof WebAssembly.RuntimeError)) throw e;
  status = typeof instance.exports.orin_exit_status === 'function' ? instance.exports.orin_exit_status() : -1;
  if (status < 0) {
    write(2, `trap: ${e.message}\n`);
    status = 134;
  }
}
process.exitCode = status;
