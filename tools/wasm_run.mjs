#!/usr/bin/env node
// A minimal Orbit host for tests (ADR-0055): runs an Orin program built with `--target=wasm64-orbit` or `--target=wasm32-orbit` under Node (>= 24, for
// memory64 and table64) with the same import contract as Orbit (orin-lang/orbit, docs/host-abi.md), so the conformance
// suite can run in CI without building Orbit. It is NOT a sandbox and NOT Orbit: Orbit is the runtime; this only serves
// the capabilities the target uses.
//
//   node tools/wasm_run.mjs <module.wasm> [--deny CAP]... [--app-arg X]... [--stdin] [--mount /guest=hostdir[:rw]]... [--cwd /guest/dir] [--fs-max-handles N] [--max-threads N]
//
// Capabilities served: log/v1, clock/v1, process/v1 (arguments after argv[0] = the module name; stdin with --stdin) and fs/v1 (mounts
// as in `orbit run --grant fs:/guest=./dir:rw`, the same statuses and path rules, synchronous Node file calls) and thread/v1. NOT served:
// net/v1 (it needs real waits; run such modules on Orbit: tools/test_orbit.py). The semantics follow orbit docs/host-abi.md sections 4b-4c.
//
// Like Orbit it fails closed at load: every import must be an `orbit:` capability it serves with the right shape, and when
// the module carries an `orbit.manifest` section every imported capability must be listed there (exit 2 otherwise).
// orbit:log/v1 write: level >= 4 (error) goes to stderr, everything else to stdout, one line per record.
// Threads (wasm32-orbit, ADR-0055 decision 10): the module imports `env.memory` as SHARED memory (the limits come from the import
// declaration, as Orbit would apply its own maximum) and `orbit:thread/v1 spawn(arg: i64) -> i64`. spawn starts (or reuses an idle)
// worker_thread that instantiates the same module again on the same memory and calls the export `orin_thread_start(tid, arg)`; it
// returns the thread id (> 0) or a negative Orbit status. The main thread of the module is itself a worker, so this process stays free
// to end every thread when any thread exits or traps (a shared status word, woken with Atomics.waitAsync). File handles of fs/v1 and
// the stdin position are per worker here (Orbit keeps one table per module): a handle is used by the thread that opened it.
// Exit status: the result of `orin_main`; after a trap, the status the program passed to exit (export orin_exit_status,
// e.g. 101 for an Orin trap), or 134 for any other trap (stack overflow, out-of-bounds access, abort).
import { readFileSync, writeSync } from 'node:fs';
import * as nodeFs from 'node:fs';
import * as nodePath from 'node:path';
import { Worker, isMainThread, workerData } from 'node:worker_threads';
import { fileURLToPath } from 'node:url';

const isWorker = !isMainThread && !!(workerData && workerData.mod); // a thread of a running module (below)
const [file, ...rest] = isWorker ? workerData.cfg : process.argv.slice(2);
if (!file) {
  process.stderr.write('usage: node tools/wasm_run.mjs <module.wasm> [--deny CAP]...\n');
  process.exit(2);
}
const denied = new Set();
const appArgs = [], mounts = [];
let stdinGranted = false, cwd = '/', maxHandles = 64, maxThreads = 1024; // Orbit's default is 64 and its ceiling 1024 (--max-threads)
for (let i = 0; i < rest.length; i++) {
  if (rest[i] === '--deny' && i + 1 < rest.length) denied.add(rest[++i]);
  else if (rest[i] === '--app-arg' && i + 1 < rest.length) appArgs.push(rest[++i]);
  else if (rest[i] === '--stdin') stdinGranted = true;
  else if (rest[i] === '--cwd' && i + 1 < rest.length) cwd = rest[++i];
  else if (rest[i] === '--max-threads' && i + 1 < rest.length) maxThreads = Number(rest[++i]);
  else if (rest[i] === '--fs-max-handles' && i + 1 < rest.length) maxHandles = Number(rest[++i]);
  else if (rest[i] === '--mount' && i + 1 < rest.length) {
    const m = /^(\/[^=]*)=(.*?)(:rw|:ro)?$/.exec(rest[++i]);
    if (!m) { process.stderr.write('wasm_run: --mount expects /guest=hostdir[:rw|:ro]\n'); process.exit(2); }
    mounts.push({ guest: m[1].replace(/\/+$/, '') || '/', host: nodePath.resolve(m[2]), writable: m[3] === ':rw' });
  } else { process.stderr.write(`wasm_run: unknown argument ${rest[i]}\n`); process.exit(2); }
}
const ERR_INVALID = -1n, ERR_QUOTA = -6n;
const MAX_WORKERS = 4096; // workers of one module, idle ones included
// ctrl: Int32Array over a SharedArrayBuffer: next thread id, exit requested, exit status, workers, idle workers, job queue head / tail,
// futex word of the queue, its lock
const NEXT = 0, EXIT = 1, STATUS = 2, WORKERS = 3, IDLE = 4, HEAD = 5, TAIL = 6, SEM = 7, QLOCK = 8, LIVE = 9, JOBS = 4096;
const ERR_DENIED = -2n, ERR_CANCELLED = -11n;
const fail = (msg) => { process.stderr.write(`wasm_run: ${msg}\n`); process.exit(2); };

// The limits of the imported memory `env.memory` (WebAssembly.Module.imports does not tell): parse the import section.
function memoryImport(bytes) {
  let p = 8;
  const leb = () => { let r = 0n, s = 0n, b; do { b = bytes[p++]; r |= BigInt(b & 0x7f) << s; s += 7n; } while (b & 0x80); return r; };
  const name = () => { const n = Number(leb()); const t = new TextDecoder().decode(bytes.subarray(p, p + n)); p += n; return t; };
  while (p < bytes.length) {
    const id = bytes[p++], size = Number(leb()), end = p + size;
    if (id === 2) {
      for (let n = Number(leb()); n > 0; n--) {
        const m = name(), f = name(), kind = bytes[p++];
        if (kind === 0) leb();
        else if (kind === 1) { p++; const fl = bytes[p++]; leb(); if (fl & 1) leb(); }
        else if (kind === 2) {
          const fl = bytes[p++], min = leb(), max = fl & 1 ? leb() : null;
          return { module: m, name: f, shared: !!(fl & 2), memory64: !!(fl & 4), min: Number(min), max: max === null ? null : Number(max) };
        } else if (kind === 3) p += 2;
      }
    }
    p = end;
  }
  return null;
}

let mod, bytes;
if (isWorker) mod = workerData.mod;
else {
  bytes = readFileSync(file);
  try { mod = new WebAssembly.Module(bytes); } catch (e) { fail(`invalid module: ${e.message}`); }
}

let memory = isWorker ? workerData.memory : undefined;
const decoder = new TextDecoder('utf-8', { fatal: true });
const write = (fd, text) => writeSync(fd, text);
const start = isWorker ? workerData.start : process.hrtime.bigint();
const caps = {
  'log/v1': {
    write(level, ptr, len) {
      if (level < 0 || level > 4) return -1;
      const p = Number(ptr), n = Number(len);
      if (p < 0 || n < 0 || n > 16384 || p + n > memory.buffer.byteLength) return -1;
      let text;
      try { const copy = new Uint8Array(n); copy.set(new Uint8Array(memory.buffer, p, n)); text = decoder.decode(copy); } catch { return -1; } // shared memory: copy first
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
// fs/v1 handles are valid in every thread (Orbit: one table per isolate): files live in a table in shared memory (state, fd, mode; the
// fds are process-wide), a directory listing stays in the worker that opened it (its handle is BAD_HANDLE elsewhere).
const htab = isWorker ? workerData.htab : new Int32Array(new SharedArrayBuffer(12 * maxHandles));
const localDirs = new Map();
const addHandle = (h) => {
  for (let i = 0; i < maxHandles; i++) {
    if (Atomics.compareExchange(htab, 3 * i, 0, -1) !== 0) continue;
    if (h.entries) { localDirs.set(i + 1, h); htab[3 * i + 1] = -1; htab[3 * i + 2] = 0; Atomics.store(htab, 3 * i, 2); }
    else { htab[3 * i + 1] = h.fd; htab[3 * i + 2] = h.mode; Atomics.store(htab, 3 * i, 1); }
    return i + 1;
  }
  return QUOTA;
};
const hget = (h) => {
  const i = Number(h) - 1;
  if (!(i >= 0 && i < maxHandles)) return undefined;
  const st = Atomics.load(htab, 3 * i);
  return st === 1 ? { fd: htab[3 * i + 1], mode: htab[3 * i + 2] } : st === 2 ? localDirs.get(i + 1) : undefined;
};
const hfree = (h) => { localDirs.delete(Number(h)); Atomics.store(htab, 3 * (Number(h) - 1), 0); };
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
    hfree(h);
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
// The import object of one instance over the capabilities the module may use (the load checks run in every thread).
function buildImports() {
  const imports = {};
  for (const imp of WebAssembly.Module.imports(mod)) {
    if (imp.module === 'env' && imp.name === 'memory' && imp.kind === 'memory') { (imports.env ??= {}).memory = memory; continue; }
    const m = /^orbit:([a-z]+\/v[0-9]+)$/.exec(imp.module);
    if (!m || imp.kind !== 'function' || !(m[1] in caps) || !(imp.name in caps[m[1]])) {
      fail(`unknown import ${imp.module}.${imp.name} (${imp.kind})`);
    }
    if (listed && !listed.has(m[1])) fail(`manifest mismatch: ${m[1]} is imported but not listed`);
    if (denied.has(m[1])) fail(`capability not granted: ${m[1]}`);
    (imports[imp.module] ??= {})[imp.name] = caps[m[1]][imp.name];
  }
  // the engine checks the signatures at instantiation: a wrong shape fails with a LinkError
  return imports;
}
// Runs fn in this thread: [status, trapped]. A trap gives the status the program set (or 134).
function guarded(instance, fn) {
  try {
    return [fn(), false];
  } catch (e) {
    let status;
    if (!(e instanceof WebAssembly.RuntimeError)) { process.stderr.write(`wasm_run: ${e && e.stack || e}\n`); status = 134; }
    else {
      status = typeof instance.exports.orin_exit_status === 'function' ? instance.exports.orin_exit_status() : -1;
      if (status < 0) { writeSync(2, `trap: ${e.message}\n`); status = 134; }
    }
    return [status, true];
  }
}
function endModule(ctrl, status) {
  if (Atomics.compareExchange(ctrl, EXIT, 0, 1) === 0) { Atomics.store(ctrl, STATUS, status); Atomics.notify(ctrl, EXIT); }
}

// Threads. A worker that finished its thread stays as an idle worker and takes the next spawn (a job queue in shared memory), so a
// program that starts thousands of short tasks does not pay a Worker start for each. jobs: Int32Array pairs (tid, arg).
const lockQ = (ctrl) => { while (Atomics.compareExchange(ctrl, QLOCK, 0, 1) !== 0) Atomics.wait(ctrl, QLOCK, 1, 1); };
const unlockQ = (ctrl) => Atomics.store(ctrl, QLOCK, 0);

function threadSpawner(common) {
  const { ctrl, jobs } = common;
  return (arg) => {
    if (maxThreads === 0) return ERR_DENIED;
    if (Atomics.load(ctrl, EXIT)) return ERR_CANCELLED; // the module is ending
    if (Atomics.add(ctrl, LIVE, 1) >= maxThreads) { Atomics.sub(ctrl, LIVE, 1); return ERR_QUOTA; } // spawned threads alive at once
    const tid = Atomics.add(ctrl, NEXT, 1) + 1;
    lockQ(ctrl);
    if (Atomics.load(ctrl, IDLE) > 0) { // hand the job to an idle worker
      Atomics.sub(ctrl, IDLE, 1);
      const t = Atomics.load(ctrl, TAIL);
      jobs[2 * (t % JOBS)] = tid; jobs[2 * (t % JOBS) + 1] = Number(arg);
      Atomics.store(ctrl, TAIL, t + 1);
      unlockQ(ctrl);
      Atomics.add(ctrl, SEM, 1); Atomics.notify(ctrl, SEM, 1);
      return BigInt(tid);
    }
    unlockQ(ctrl);
    if (Atomics.load(ctrl, WORKERS) >= MAX_WORKERS) { Atomics.sub(ctrl, LIVE, 1); return ERR_QUOTA; }
    Atomics.add(ctrl, WORKERS, 1);
    try { new Worker(fileURLToPath(import.meta.url), { workerData: { ...common, first: { tid, arg: Number(arg) } } }); }
    catch { Atomics.sub(ctrl, WORKERS, 1); Atomics.sub(ctrl, LIVE, 1); return ERR_INVALID; }
    return BigInt(tid);
  };
}


if (isWorker) {
  // ---- a worker of the module: its main thread (first === null) or a thread started by spawn, then idle for the next one
  const { ctrl, jobs, first } = workerData;
  caps['thread/v1'] = { spawn: threadSpawner(workerData) };
  let instance;
  try { instance = new WebAssembly.Instance(mod, buildImports()); } catch (e) { fail(`instantiate failed: ${e.message}`); }
  if (first === null) {
    endModule(ctrl, guarded(instance, () => instance.exports.orin_main())[0]);
  } else {
    let job = first;
    for (;;) {
      const [st, trapped] = guarded(instance, () => instance.exports.orin_thread_start(BigInt(job.tid), BigInt(job.arg)));
      if (trapped) { endModule(ctrl, st); break; }
      Atomics.sub(ctrl, LIVE, 1);
      job = null;
      lockQ(ctrl); Atomics.add(ctrl, IDLE, 1); unlockQ(ctrl);
      while (!job) {
        const seen = Atomics.load(ctrl, SEM);
        lockQ(ctrl);
        const h = Atomics.load(ctrl, HEAD);
        if (h < Atomics.load(ctrl, TAIL)) { job = { tid: jobs[2 * (h % JOBS)], arg: jobs[2 * (h % JOBS) + 1] >>> 0 }; Atomics.store(ctrl, HEAD, h + 1); }
        unlockQ(ctrl);
        if (!job) Atomics.wait(ctrl, SEM, seen);
      }
    }
  }
} else if (bytes && memoryImport(bytes)?.shared) {
  // wasm32-orbit with threads: the main thread of the module runs in a worker; this thread waits for the end of the module.
  const mi = memoryImport(bytes);
  if (mi.module !== 'env' || mi.name !== 'memory' || mi.memory64) fail(`unsupported memory import ${mi.module}.${mi.name}`);
  memory = new WebAssembly.Memory({ initial: mi.min, maximum: mi.max ?? 65536, shared: true });
  const ctrl = new Int32Array(new SharedArrayBuffer(64)), jobs = new Int32Array(new SharedArrayBuffer(8 * JOBS));
  Atomics.store(ctrl, WORKERS, 1);
  caps['thread/v1'] = { spawn: () => ERR_INVALID };
  buildImports(); // the load checks fail here, with status 2, before anything starts
  const w = new Worker(fileURLToPath(import.meta.url), { workerData: { mod, memory, ctrl, jobs, start, first: null, htab, cfg: [file, ...rest] } });
  w.on('error', (e) => { process.stderr.write(`wasm_run: ${e && e.stack || e}\n`); process.exit(134); });
  Atomics.waitAsync(ctrl, EXIT, 0).value.then(() => process.exit(Atomics.load(ctrl, STATUS)));
} else {
  let instance;
  try { instance = new WebAssembly.Instance(mod, buildImports()); } catch (e) { fail(`instantiate failed: ${e.message}`); }
  memory = instance.exports.memory;
  if (!(memory instanceof WebAssembly.Memory) || typeof instance.exports.orin_main !== 'function') {
    fail('the module exports no memory or no orin_main');
  }
  process.exitCode = guarded(instance, () => instance.exports.orin_main())[0];
}
