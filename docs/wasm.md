# WebAssembly: running Orin programs in Orbit

Orin compiles programs to WebAssembly modules for [Orbit](https://github.com/orin-lang/orbit), Orin's isolate runtime.
Design and measurements: [ADR-0055](decisions/0055-webassembly-target-orbit.md).

```sh
orin build --target=wasm64-orbit                   # -> build/dev/<name>.wasm (build/release/ with --release)
orin build --target=wasm32-orbit                   # the same program with a 32-bit memory
orbit inspect build/dev/hello.wasm                 # imports, exports, the capability manifest
orbit run build/dev/hello.wasm --grant log/v1 --invoke orin_main
```

A program that uses files, the network, arguments or stdin runs unchanged; the grants on the command line decide what it may reach:

```sh
orbit run app.wasm --grant log/v1 --app-arg one --app-arg two        # std:process args (grants process/v1)
orbit run app.wasm --grant log/v1 --grant process:stdin < input.txt  # std:io readLine / readBytes
orbit run app.wasm --grant log/v1 --grant fs:/data=./dir:rw --cwd /data   # std:fs, std:path under a mount
orbit run app.wasm --grant log/v1 --grant clock/v1 --listen 127.0.0.1:8080  # std:net, std:http server (clock/v1: timeouts)
orbit run app.wasm --grant log/v1 --grant clock/v1 --grant net:connect='*.example.com:443'   # outgoing connections and DNS
```

Needs a clang with the WebAssembly backend and `wasm-ld`: the pinned LLVM (`orin toolchain install`) has both; on Ubuntu the
system `clang` plus the `lld` package also works (`CC=clang`).

## What the module looks like

- **wasm64** (Memory64) or **wasm32**, freestanding: no WASI, no libc imports. The only imports are Orbit capabilities the program reaches:
  `orbit:log/v1` (console output, trap messages), `orbit:clock/v1` (time), `orbit:process/v1` (arguments, stdin), `orbit:fs/v1` (files) and
  `orbit:net/v1` (TCP, DNS). A module imports exactly the capabilities its manifest lists, so `hello` needs only `log/v1`.
- **Exports:** `memory`; `orin_main() -> i32` runs `main` and returns the exit status; `orin_exit_status() -> i32` gives the
  status passed to `exit` after a trap (101 for an Orin trap such as an out-of-bounds index), or -1 for any other trap.
- **Manifest:** a custom section `orbit.manifest`, e.g. `{"abi":1,"requires":["log/v1"],"producer":"orin"}`, derived from the
  program's effects (`orin effects`). It describes what the program needs; Orbit grants nothing because of it.

## What works, and what does not

| Feature | On `wasm64-orbit` and `wasm32-orbit` |
|---|---|
| the language, std collections, strings, floats, closures, generics, traps | as native (the conformance suites pass as modules) |
| `console.log`, stderr | one log record per line (stdout = info, stderr = error) |
| time (`std:time`, clocks) | `orbit:clock/v1`; the host may coarsen it |
| `std:process` `args` | `orbit:process/v1`: `["<module name>", ...--app-arg]`, read on first use (`args` skips argv[0]) |
| `std:io` stdin (`readLine`, `readBytes`) | `orbit:process/v1` `stdin_read` with `--grant process:stdin`; without it stdin is empty. A prompt written without a newline is shown before the read |
| environment variables | none: nothing in std reads them (the runtime's own `ORIN_THREADS` is ignored; there is one thread) |
| `std:fs`, `std:path` | `orbit:fs/v1`: files and directories under the mounts of `--grant fs:/guest=./host:ro\|rw`; paths are virtual, anything outside a mount is `Permission denied`; `--cwd` is the working directory. No mkdir, remove or rename (no L0 entry point yet) |
| `std:net`, `std:http`, DNS | `orbit:net/v1`: TCP listen, accept, connect, send, recv, shutdown and `resolve`, within `--listen` / `--grant net:listen=...` / `net:connect=...`; the L0 narrowing of grants (`useListen`, `useConnect`) is enforced in the guest as natively. No UDP, TLS or poll over several sockets |
| `std:io` `shell`, process spawning | not available: the build fails with E0523 naming the effect and where it comes from |
| `std:task`, channels, `.parallel()` | run, one task at a time, to completion, inside the one WebAssembly thread (see below) |

## Tasks and channels: one at a time

A WebAssembly instance has one thread, so the module runs `std:task` tasks one after the other, each to completion. `spawn`
only queues a task. A queued task runs when someone would otherwise block: `join` of it, or any wait on a channel, scope or
monitor (the waiting task gives the thread to the next queued task and re-checks its condition afterwards); tasks nobody
joined run before `main` ends. So these work as natively: spawn-and-join, `scope`, `.parallel()` (with one core), channels
whose sender never waits for the receiver (the capacity is large enough, or the producer is joined before the consumer
reads), fan-out and fan-in.

Two things do not work, and both end the module with a line that starts with `wasm64-orbit: ` (`wasm32-orbit: ` for the 32-bit target) on stderr instead of
hanging or giving a wrong answer:

- **Interleaving.** A task that waits for something only a task suspended below it can produce (ping-pong over bounded
  channels, a producer that blocks on a full channel while the consumer waits for the next item) cannot be resumed
  without stack switching: `wasm64-orbit: deadlock: ...`, trap, exit status 134.
- **A task that traps.** Natively the trap ends the task and the joiner sees it (`panic reaches join`). WebAssembly cannot
  unwind the task's frames, so the whole module ends: `wasm64-orbit: a task trapped: <message>`, exit status 101.

Because the spawned closure is an unresolved callback to the effect analysis, the manifest of a program that spawns tasks
also lists `clock/v1` (the module still imports only what it uses). Timed waits do not sleep: with nothing queued a timed wait returns as timed out at once, so a program that waits for a
deadline sees it early. How it is built (ADR-0055, decision 4): the runtime keeps per-task state in `__thread` objects; the
build turns each into an ordinary object of the section `orin_tls` (`-D__thread=__attribute__((section("orin_tls")))`), so
they form one block, and the L0 saves that block, installs its pristine image, runs the task and restores the block. No
atomics or WebAssembly threads are involved (the module needs no extra WebAssembly feature).

## Files, network and cancellation on Orbit

Each capability family is a header of the L0 (`runtime/platform/orbit/include/orbit_proc.h`, `orbit_fs.h`, `orbit_net.h`). The compiler
appends an `#include` of the family for each capability the manifest lists (`compiler/analysis/orbit.or`); the core
(`orin_platform_orbit.c`) holds refusing stubs for them. That is how a module imports exactly what it lists: the runtime refers to the
file and socket functions from code every program with a grant reaches (revoking a grant closes its sockets), so a link-time choice
would otherwise import all three. The host's status codes become the errno values and `NET_*` codes of the L0 contract
(`orbit/docs/orin-std-mapping.md`), so `std:fs` and `std:net` report the same errors as natively (`No such file or directory`,
`Connection refused`, `Permission denied` for a path outside the mounts).

One WebAssembly thread runs every task, so a server serves one connection at a time. `examples/http_server.or` runs unchanged: its
accepting task takes `maxConnections` connections, then the workers (queued tasks) serve them when it waits to join them. A
long-running server that must answer while it accepts needs `orbit:thread/v1`, which does not exist yet. For the same reason a
client and a server in one program only work when the client does not have to run while the server waits in `accept`.

Cancellation: the wake sources of `std:task` are flags in the L0 (the host's `wake_*` functions would import `orbit:net/v1` into every
program that starts a task). A network wait checks the bound token first and fails with `Cancelled` before the host is asked, so a
task started after `scope.cancel()` does no network work, and an `accept` or `connect` in a cancelled scope returns at once. A token
cannot be set while a host call blocks (nothing else runs), so a blocked `accept` ends by its timeout (`Timeout`, at most
3 600 000 ms, as natively) and by the host's wall-clock limit (`--timeout-ms`), not by a task cancelling it.

## wasm32-orbit or wasm64-orbit?

Same language, same behaviour, same manifest, same imports; only the width of the C pointers differs. In `wasm32-orbit`
Orin values stay 64-bit (`usize`, `int`, every slot), so arithmetic and memory per object are the same as on wasm64; only
addresses are 4 bytes. Choose by where the module runs:

- **wasm32-orbit** runs everywhere (every engine and every Orbit version) and avoids the bounds-check cost of Memory64
  (ADR-0055 "Measurements" has the numbers). Limits: the memory is at most 4 GiB (an allocation that does not fit fails with
  `out of memory`, a size above 4 GiB traps with the same message, never wraps), and the module's own 1 MiB stack and data
  count against that.
- **wasm64-orbit** has no 4 GiB limit but needs an engine with Memory64 (Node >= 24, Wasmtime, Orbit).

The host contract is identical: every pointer and length that crosses the Orbit ABI is an `i64`, zero-extended for the 32-bit memory.

## Testing

`tools/test_wasm.sh` runs the conformance suites as WebAssembly modules (once per width) under Node >= 24 (`tools/wasm_run.mjs` serves
`log/v1`, `clock/v1`, `process/v1` and `fs/v1` with Orbit's load-time checks and statuses; the network tests are SKIP there), plus the
differential tests of the WebAssembly L0 and its size budget. One
suite only: `NODE=node python3 tools/run_tests.py --orinc build/bootstrap/orin2 --target wasm64-orbit --suite all` (or `--target wasm32-orbit`).

On the real Orbit runtime (a checkout of [orin-lang/orbit](https://github.com/orin-lang/orbit) built with
`cargo build --release -p orbit-cli`; point `ORBIT` at the binary, or leave it in `../orbit/target/release/orbit`):

```sh
python3 tools/test_orbit.py --orinc build/bootstrap/orin2          # args, stdin, files, TCP echo, HTTP server + curl, DNS, cancellation, both widths
python3 tools/run_tests.py --orinc build/bootstrap/orin2 --target wasm32-orbit --suite all --orbit "$ORBIT"   # the conformance suites on Orbit, network included
```

`tools/test_orbit.py` prints `SKIP` and exits 0 when there is no `orbit` binary or no clang with the WebAssembly backend, so
CI without Orbit still passes. Two conformance tests are SKIP on Orbit (`net_accepted_served_twice`, `net_task_move`): a client and a
server task must run at the same time.
