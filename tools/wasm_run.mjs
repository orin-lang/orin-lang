#!/usr/bin/env node
// A minimal Orbit host for tests (ADR-0055): runs an Orin program built with `--target=wasm64-orbit` or `--target=wasm32-orbit` under Node (>= 24, for
// memory64 and table64) with the same import contract as Orbit (orin-lang/orbit, docs/host-abi.md), so the conformance
// suite can run in CI without building Orbit. It is NOT a sandbox and NOT Orbit: Orbit is the runtime; this only serves
// the capabilities the target uses: log/v1, clock/v1 and thread/v1.
//
//   node tools/wasm_run.mjs <module.wasm> [--deny log/v1|clock/v1|thread/v1]...
//
// Like Orbit it fails closed at load: every import must be an `orbit:` capability it serves with the right shape, and when
// the module carries an `orbit.manifest` section every imported capability must be listed there (exit 2 otherwise).
// orbit:log/v1 write: level >= 4 (error) goes to stderr, everything else to stdout, one line per record.
// Threads (wasm32-orbit, ADR-0055 decision 9): the module imports `env.memory` as SHARED memory (the limits come from the import
// declaration, as Orbit would apply its own maximum) and `orbit:thread/v1 spawn(arg: i64) -> i64`. spawn starts a worker_thread
// that instantiates the same module again on the same memory and calls the export `orin_thread_start(tid, arg)`; it returns the
// thread id (> 0) or a negative Orbit status. The main thread of the module is itself a worker, so this process stays free to
// end every thread when any thread exits or traps (a shared status word, woken with Atomics.waitAsync).
// Exit status: the result of `orin_main`; after a trap in any thread, the status the program passed to exit (export
// orin_exit_status, e.g. 101 for an Orin trap), or 134 for any other trap (stack overflow, out-of-bounds access, abort).
import { readFileSync, writeSync } from 'node:fs';
import { Worker, isMainThread, workerData } from 'node:worker_threads';
import { fileURLToPath } from 'node:url';

const ERR_INVALID = -1n, ERR_QUOTA = -6n;
const MAX_THREADS = 4096; // live threads of one module (Orbit has a quota too)
// ctrl: Int32Array over a SharedArrayBuffer: next thread id, exit requested, exit status, workers, idle workers, job queue head / tail,
// futex word of the queue, its lock
const NEXT = 0, EXIT = 1, STATUS = 2, WORKERS = 3, IDLE = 4, HEAD = 5, TAIL = 6, SEM = 7, QLOCK = 8, JOBS = 4096;
const decoder = new TextDecoder('utf-8', { fatal: true });
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

// Builds the import object of one instance (the main thread's or a thread's) over the capabilities the module may use.
function buildImports(mod, getMemory, ctrl, start, shared, spawn, denied) {
  const caps = {
    'log/v1': {
      write(level, ptr, len) {
        if (level < 0 || level > 4) return -1;
        const p = Number(ptr), n = Number(len), buf = getMemory().buffer;
        if (p < 0 || n < 0 || n > 16384 || p + n > buf.byteLength) return -1;
        let text;
        try { const copy = new Uint8Array(n); copy.set(new Uint8Array(buf, p, n)); text = decoder.decode(copy); } catch { return -1; }
        writeSync(level >= 4 ? 2 : 1, text + '\n');
        return 0;
      },
    },
    'clock/v1': {
      now_unix_nanos: () => BigInt(Date.now()) * 1000000n,
      monotonic_nanos: () => process.hrtime.bigint() - start,
    },
    'thread/v1': { spawn },
  };
  const manifest = WebAssembly.Module.customSections(mod, 'orbit.manifest');
  let listed = null;
  if (manifest.length > 1) fail('more than one orbit.manifest section');
  if (manifest.length === 1) {
    try { listed = new Set(JSON.parse(new TextDecoder().decode(manifest[0])).requires); } catch (e) { fail(`bad manifest: ${e.message}`); }
  }
  const imports = {};
  for (const imp of WebAssembly.Module.imports(mod)) {
    if (imp.module === 'env' && imp.name === 'memory' && imp.kind === 'memory') { (imports.env ??= {}).memory = getMemory(); continue; }
    const m = /^orbit:([a-z]+\/v[0-9]+)$/.exec(imp.module);
    if (!m || imp.kind !== 'function' || !(m[1] in caps) || !(imp.name in caps[m[1]])) {
      fail(`unknown import ${imp.module}.${imp.name} (${imp.kind})`);
    }
    if (listed && !listed.has(m[1])) fail(`manifest mismatch: ${m[1]} is imported but not listed`);
    if (denied.has(m[1])) fail(`capability not granted: ${m[1]}`);
    (imports[imp.module] ??= {})[imp.name] = caps[m[1]][imp.name];
  }
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
    if (Atomics.load(ctrl, WORKERS) >= MAX_THREADS) return ERR_QUOTA;
    Atomics.add(ctrl, WORKERS, 1);
    try { new Worker(fileURLToPath(import.meta.url), { workerData: { ...common, first: { tid, arg: Number(arg) } } }); }
    catch { Atomics.sub(ctrl, WORKERS, 1); return ERR_INVALID; }
    return BigInt(tid);
  };
}

if (!isMainThread && workerData && workerData.mod) {
  // ---- a worker of the module: its main thread (first === null) or a thread started by spawn, then idle for the next one
  const { mod, memory, ctrl, jobs, start, denied, first } = workerData;
  const dn = new Set(denied);
  const imports = buildImports(mod, () => memory, ctrl, start, true, threadSpawner(workerData), dn);
  let instance;
  try { instance = new WebAssembly.Instance(mod, imports); } catch (e) { fail(`instantiate failed: ${e.message}`); }
  if (first === null) {
    endModule(ctrl, guarded(instance, () => instance.exports.orin_main())[0]);
  } else {
    let job = first;
    for (;;) {
      const [st, trapped] = guarded(instance, () => instance.exports.orin_thread_start(BigInt(job.tid), BigInt(job.arg)));
      if (trapped) { endModule(ctrl, st); break; }
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
} else {
  const [file, ...rest] = process.argv.slice(2);
  if (!file) { process.stderr.write('usage: node tools/wasm_run.mjs <module.wasm> [--deny CAP]...\n'); process.exit(2); }
  const denied = new Set();
  for (let i = 0; i < rest.length; i++) {
    if (rest[i] === '--deny' && i + 1 < rest.length) denied.add(rest[++i]);
    else { process.stderr.write(`wasm_run: unknown argument ${rest[i]}\n`); process.exit(2); }
  }
  const bytes = readFileSync(file);
  let mod;
  try { mod = new WebAssembly.Module(bytes); } catch (e) { fail(`invalid module: ${e.message}`); }
  const start = process.hrtime.bigint();
  const mi = memoryImport(bytes);
  if (mi && (mi.module !== 'env' || mi.name !== 'memory')) fail(`unknown import ${mi.module}.${mi.name} (memory)`);
  if (mi && mi.shared) {
    // wasm32-orbit with threads: the main thread of the module runs in a worker; this thread waits for the end of the module.
    if (mi.memory64) fail('shared memory64 is not supported');
    const memory = new WebAssembly.Memory({ initial: mi.min, maximum: mi.max ?? 65536, shared: true });
    const ctrl = new Int32Array(new SharedArrayBuffer(64)), jobs = new Int32Array(new SharedArrayBuffer(8 * JOBS));
    Atomics.store(ctrl, WORKERS, 1);
    // load checks run here too (same function), so a bad module fails with status 2 before anything starts
    buildImports(mod, () => memory, ctrl, start, true, () => ERR_INVALID, denied);
    const w = new Worker(fileURLToPath(import.meta.url), { workerData: { mod, memory, ctrl, jobs, start, first: null, denied: [...denied] } });
    w.on('error', (e) => { process.stderr.write(`wasm_run: ${e && e.stack || e}\n`); process.exit(134); });
    Atomics.waitAsync(ctrl, EXIT, 0).value.then(() => process.exit(Atomics.load(ctrl, STATUS)));
  } else {
    let memory;
    const imports = buildImports(mod, () => memory, null, start, false, () => ERR_INVALID, denied);
    let instance;
    try { instance = new WebAssembly.Instance(mod, imports); } catch (e) { fail(`instantiate failed: ${e.message}`); }
    memory = instance.exports.memory;
    if (!(memory instanceof WebAssembly.Memory) || typeof instance.exports.orin_main !== 'function') {
      fail('the module exports no memory or no orin_main');
    }
    process.exitCode = guarded(instance, () => instance.exports.orin_main())[0];
  }
}
