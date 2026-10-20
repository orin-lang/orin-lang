#!/usr/bin/env python3
"""Orin programs on the real Orbit runtime: arguments, stdin, files, TCP, HTTP, DNS and cancellation (ADR-0055, the L0 families
orbit_proc.h / orbit_fs.h / orbit_net.h).

    python3 tools/test_orbit.py [--orinc build/bootstrap/orin2] [--orbit PATH] [--target wasm32-orbit|wasm64-orbit|both] [--keep]

Builds the programs of tests/orbit and examples/http_server.or as WebAssembly modules, runs each under `orbit run` with the matching
grants and checks what it prints and what the host sees (files on disk, sockets, curl). The Orbit binary is $ORBIT, --orbit, the
sibling checkout ../orbit/target/release/orbit or `orbit` on PATH (cd orbit && cargo build --release -p orbit-cli). Without it, or
without a clang with the WebAssembly backend and wasm-ld, the test prints SKIP and exits 0 (CI has no Orbit). The conformance suites
run on Orbit too: python3 tools/run_tests.py --target wasm32-orbit --orbit PATH --suite all.
"""
import argparse
import os
import re
import shutil
import socket
import subprocess
import sys
import tempfile
import time
import urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from runtime_files import rt_inc, rt_src  # noqa: E402

TLS = '-D__thread=__attribute__((section("orin_tls")))'
LOG = re.compile(r"^\[(\w+)\] [^ ]+: (.*)$")
failures = []
checks = 0


def check(ok, what, detail=""):
    global checks
    checks += 1
    if not ok:
        failures.append(what)
        print("FAIL: %s%s" % (what, "\n" + detail if detail else ""))


def find_orbit(explicit):
    for cand in (explicit, os.environ.get("ORBIT"), os.path.join(ROOT, "..", "orbit", "target", "release", "orbit"),
                 shutil.which("orbit")):
        if cand and os.path.isfile(cand) and os.access(cand, os.X_OK):
            return os.path.abspath(cand)
    return None


def have_wasm_toolchain():
    if not shutil.which("clang") or not shutil.which("wasm-ld"):
        return False
    probe = subprocess.run(["clang", "--print-targets"], stdout=subprocess.PIPE, text=True)
    return "wasm32" in probe.stdout and "wasm64" in probe.stdout


def build(orinc, src, target, outdir):
    """src.or -> outdir/<name>.wasm (the C backend, as tools/run_tests.py builds a test)."""
    name = os.path.basename(src)[:-3]
    c, wasm = os.path.join(outdir, name + ".c"), os.path.join(outdir, name + ".wasm")
    r = subprocess.run([orinc, "compile", os.path.relpath(src, ROOT), "-o", c, "--target=" + target], cwd=ROOT,
                       stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if r.returncode != 0:
        raise SystemExit("compile %s failed:\n%s" % (src, r.stderr))
    triple = "--target=" + target[:6] + "-unknown-unknown"
    cmd = ["clang", "-O2", "-w", triple, "-mbulk-memory", "-ffreestanding", "-nostdlib", TLS, *rt_inc("orbit"), c, *rt_src("orbit"),
           "-Wl,--no-entry", "-Wl,--stack-first", "-Wl,-z,stack-size=1048576", "-o", wasm]
    r = subprocess.run(cmd, cwd=ROOT, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if r.returncode != 0:
        raise SystemExit("clang %s failed:\n%s" % (src, r.stderr[:2000]))
    return wasm


class Orbit:
    def __init__(self, binary):
        self.bin = binary

    def run(self, wasm, *opts, stdin=None, timeout=30):
        r = subprocess.run([self.bin, "run", wasm, *opts], input=stdin, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                           timeout=timeout)
        return r.returncode, logs(r.stderr.decode("utf-8", "replace")), r.stderr.decode("utf-8", "replace")

    def start(self, wasm, *opts):
        return subprocess.Popen([self.bin, "run", wasm, *opts], stdin=subprocess.DEVNULL, stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE)

    def inspect(self, wasm):
        r = subprocess.run([self.bin, "inspect", wasm], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
        return r.stdout


def logs(stderr):
    """The guest's output: Orbit writes console output as log records on stderr (info = stdout, error = stderr)."""
    out = []
    for line in stderr.split("\n"):
        m = LOG.match(line)
        out.append((m.group(1), m.group(2)) if m else ("host", line))
    return out


def info(records):
    return [t for lvl, t in records if lvl == "info"]


def free_port():
    s = socket.socket()
    s.bind(("127.0.0.1", 0))
    port = s.getsockname()[1]
    s.close()
    return port


def wait_for(proc, text, seconds=15):
    """Reads the server's stderr until a line contains text; returns the lines read so far."""
    seen = []
    end = time.time() + seconds
    while time.time() < end:
        line = proc.stderr.readline().decode("utf-8", "replace")
        if not line:
            break
        seen.append(line.rstrip("\n"))
        if text in line:
            return seen
    raise SystemExit("server did not print %r; saw %r" % (text, seen))


def finish(proc, seconds=15):
    try:
        out, err = proc.communicate(timeout=seconds)
    except subprocess.TimeoutExpired:
        proc.kill()
        out, err = proc.communicate()
        return None, logs(err.decode("utf-8", "replace"))
    return proc.returncode, logs(err.decode("utf-8", "replace"))


def http(port, path, data=None):
    """curl when it is installed (the usual way to look at a server), else urllib. Returns (status, content type, body)."""
    url = "http://127.0.0.1:%d%s" % (port, path)
    if shutil.which("curl"):
        cmd = ["curl", "-s", "-m", "10", "-o", "-", "-w", "\n%{http_code} %{content_type}", url]
        if data is not None:
            cmd += ["-X", "POST", "--data-binary", data, "-H", "Content-Type: text/x-test"]
        out = subprocess.run(cmd, stdout=subprocess.PIPE).stdout.decode()
        body, _, tail = out.rpartition("\n")
        status, _, ctype = tail.partition(" ")
        return int(status or 0), ctype, body
    req = urllib.request.Request(url, data=data.encode() if data is not None else None,
                                 headers={"Content-Type": "text/x-test"} if data is not None else {})
    with urllib.request.urlopen(req, timeout=10) as resp:
        return resp.status, resp.headers.get("Content-Type"), resp.read().decode()


def scenario_process(orbit, wasm):
    stdin = b"Ada\nabcdXYZ\nl1\n\nlast"
    rc, recs, raw = orbit.run(wasm, "--grant", "log/v1", "--grant", "process:stdin", "--app-arg", "one", "--app-arg", "two words",
                              "--env", "K=V", stdin=stdin)
    want = ["argc=2", "arg:one", "arg:two words", "name? ", "hello Ada", "bytes=[abcd]", "line 1: XYZ (3)", "line 2: l1 (2)",
            "line 3:  (0)", "line 4: last (4)", "lines=4"]
    check(rc == 0 and info(recs) == want, "args and stdin: arguments, a prompt without newline, readLine and readBytes", raw)
    rc, recs, raw = orbit.run(wasm, "--grant", "log/v1", "--grant", "process/v1", stdin=b"ignored\n")
    check(rc == 0 and info(recs)[:2] == ["argc=0", "name? "] and "hello <eof>" in info(recs),
          "args and stdin: without --grant process:stdin the arguments are empty and stdin reads as end of input", raw)
    rc, recs, raw = orbit.run(wasm, "--grant", "log/v1")
    check(rc != 0 and "process/v1" in raw, "args and stdin: without the process grant the module does not load", raw)


def scenario_files(orbit, wasm, tmp):
    d = os.path.join(tmp, "data")
    os.makedirs(os.path.join(d, "sub"))
    with open(os.path.join(d, "in.txt"), "w") as f:
        f.write("input file\n")
    rc, recs, raw = orbit.run(wasm, "--grant", "log/v1", "--grant", "fs:/data=%s:rw" % d)
    got = info(recs)
    entries = sorted(t for t in got if t.startswith("entry: "))  # the listing is in OS order
    got = [t for t in got if not t.startswith("entry: ")]
    want = ["exists in.txt: true", "exists nothing: false", "read: input file", "", "write: true", "readback: 28 bytes",
            "missing: cannot read '/data/missing.txt': No such file or directory",
            "outside the mount: cannot read '/etc/passwd': Permission denied",
            "dotdot: cannot read '/data/../etc/passwd': Permission denied",
            "a directory: cannot read '/data/sub': Is a directory",
            "stream written: true", "line 1: one", "line 2: two", "line 3: three-four", "stream lines: 3", "big: true",
            "read-only write refused: true", "under: true"]
    check(rc == 0 and got == want and entries == ["entry: in.txt", "entry: out.txt", "entry: sub/"],
          "files: exists, read, write, list, errno texts, streams, append, a 128 KiB file and narrowed grants under a mount", raw)
    host = lambda n: open(os.path.join(d, n)).read()  # noqa: E731
    check(host("out.txt") == "hello from orin\nsecond line\n" and host("stream.txt") == "one\ntwo\nthree-four\n"
          and len(host("big.txt")) == 16 * 8192, "files: the host directory holds what the guest wrote")
    rc, recs, raw = orbit.run(wasm, "--grant", "log/v1", "--grant", "fs:/data=%s:ro" % d)
    check("write: false" in info(recs), "files: a read-only mount refuses the write", raw)
    rc, recs, raw = orbit.run(wasm, "--grant", "log/v1")
    check(rc != 0 and "fs/v1" in raw, "files: without the fs grant the module does not load", raw)


def scenario_net(orbit, echo, client, tmp):
    port, closed = free_port(), free_port()
    srv = orbit.start(echo, "--grant", "log/v1", "--grant", "clock/v1", "--listen", "127.0.0.1:%d" % port, "--app-arg", str(port))
    wait_for(srv, "listening on 127.0.0.1:%d" % port)
    rc, recs, raw = orbit.run(client, "--grant", "log/v1", "--grant", "clock/v1",
                              "--grant", "net:connect=127.0.0.1:%d-%d" % (min(port, closed), max(port, closed)),
                              "--grant", "net:connect=localhost:1-65535", "--grant", "net:connect=*.invalid:1-65535",
                              "--app-arg", str(port), "--app-arg", str(closed))
    got = info(recs)
    want = ["echo: hello over tcp", "echo again: second connection", "localhost resolves to loopback: true"]
    check(rc == 0 and got[:3] == want, "tcp client: connect, send, receive, DNS for localhost", raw)
    check(got[3].startswith("no-such-host.invalid: error") and "denied" not in got[3],
          "tcp client: a name that does not resolve is a plain error, not a denial (%s)" % got[3])
    check(got[4] == "closed port: failed: Connection refused (code 111)", "tcp client: connection refused is ECONNREFUSED (%s)" % got[4])
    check(got[5:] == ["outside the host grant: denied", "narrowed to the echo port, other port: denied",
                      "narrowed to the echo port, same port: connected", "quit: quit"],
          "tcp client: the host grant and the L0 narrowing both refuse what is out of scope", raw)
    rc, recs = finish(srv)
    out = info(recs)
    check(rc == 0 and out[-1] == "quit" and
          [t for t in out if t.endswith("echoed")] == ["connection from 127.0.0.1: 14 bytes echoed",
                                                       "connection from 127.0.0.1: 17 bytes echoed",
                                                       "connection from 127.0.0.1: 0 bytes echoed",
                                                       "connection from 127.0.0.1: 4 bytes echoed"],
          "tcp server: echoed four connections one after another and stopped on quit", "\n".join(map(str, recs)))
    # a raw socket from Python as well: a client that is not Orin
    port = free_port()
    srv = orbit.start(echo, "--grant", "log/v1", "--grant", "clock/v1", "--listen", "127.0.0.1:%d" % port, "--app-arg", str(port))
    wait_for(srv, "listening on")
    with socket.create_connection(("127.0.0.1", port), timeout=5) as s:
        s.sendall(b"abc" * 5000)
        data = b""
        while len(data) < 15000:
            chunk = s.recv(65536)
            if not chunk:
                break
            data += chunk
    check(data == b"abc" * 5000, "tcp server: 15000 bytes echoed to a socket client in order")
    with socket.create_connection(("127.0.0.1", port), timeout=5) as s:
        s.sendall(b"quit")
    rc, recs = finish(srv)
    check(rc == 0, "tcp server: stops on quit")
    # no listen grant: the host refuses and the program says why
    srv = orbit.start(echo, "--grant", "log/v1", "--grant", "clock/v1", "--grant", "net:connect=127.0.0.1:1", "--app-arg", "0")
    rc, recs = finish(srv)
    check(any("cannot listen: permission denied" in t for lvl, t in recs), "tcp server: without a listen grant it cannot listen", str(recs))


def scenario_http(orbit, server):
    port = free_port()
    # the unchanged examples/http_server.or: a pool of worker tasks. One thread runs them, so it accepts N connections first and
    # serves them when it would block (maxConnections = 2 here; the two requests are made at the same time)
    srv = orbit.start(server, "--grant", "log/v1", "--grant", "clock/v1", "--listen", "127.0.0.1:%d" % port, "--app-arg", str(port),
                      "--app-arg", "2")
    wait_for(srv, "listening on")
    from concurrent.futures import ThreadPoolExecutor
    with ThreadPoolExecutor(2) as pool:
        a = pool.submit(http, port, "/health")
        b = pool.submit(http, port, "/echo", "ping-body")
        health, echo = a.result(), b.result()
    check(health[0] == 200 and health[1] == "text/plain" and health[2].strip() == "ok",
          "http: GET /health through examples/http_server.or (%r)" % (health,))
    check(echo[0] == 200 and echo[1] == "text/x-test" and echo[2] == "ping-body", "http: POST /echo returns the body and its type (%r)" % (echo,))
    rc, recs = finish(srv)
    check(rc == 0 and "accepted 2, served 2" in [t for _, t in recs], "http: the server served both and stopped", str(recs))


def scenario_cancel(orbit, wasm):
    t0 = time.time()
    rc, recs, raw = orbit.run(wasm, "--grant", "log/v1", "--grant", "clock/v1", "--grant", "net:listen=127.0.0.1:0-65535",
                              "--grant", "net:connect=127.0.0.1:0-65535")
    c = "connect Cancelled, accept Cancelled"
    check(rc == 0 and info(recs) == ["timeout: Timeout", "precancel: " + c, "cancel: " + c + " (cancel true, again false)", "nested: " + c],
          "cancel: accept and connect report Cancelled at once once the scope token is set; accept times out otherwise", raw)
    check(time.time() - t0 < 10, "cancel: no wait ran into its 30 s limit")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--orinc", default=os.path.join(ROOT, "build", "bootstrap", "orin2"))
    ap.add_argument("--orbit", default=None)
    ap.add_argument("--target", choices=["wasm32-orbit", "wasm64-orbit", "both"], default="both")
    ap.add_argument("--keep", action="store_true", help="keep the build directory (build/orbit)")
    a = ap.parse_args()
    binary = find_orbit(a.orbit)
    if not binary:
        print("SKIP test_orbit: no orbit binary (set ORBIT, pass --orbit, or build ../orbit with: cargo build --release -p orbit-cli)")
        return 0
    if not have_wasm_toolchain():
        print("SKIP test_orbit: needs clang with the WebAssembly backend and wasm-ld")
        return 0
    orbit = Orbit(binary)
    for target in (["wasm32-orbit", "wasm64-orbit"] if a.target == "both" else [a.target]):
        print("[orbit] %s on %s" % (target, binary))
        out = os.path.join(ROOT, "build", "orbit", target)
        os.makedirs(out, exist_ok=True)
        mods = {n: build(a.orinc, p, target, out) for n, p in [
            ("args_stdin", "tests/orbit/args_stdin.or"), ("files", "tests/orbit/files.or"), ("echo", "tests/orbit/echo.or"),
            ("client", "tests/orbit/client.or"), ("cancel", "tests/orbit/cancel.or"), ("http_server", "examples/http_server.or"),
            ("hello", "tests/wasm_target/hello.or")]}
        want = {"hello": "log/v1", "args_stdin": "log/v1, process/v1", "files": "fs/v1, log/v1",
                "echo": "clock/v1, log/v1, net/v1, process/v1", "client": "clock/v1, log/v1, net/v1, process/v1",
                "cancel": "clock/v1, log/v1, net/v1", "http_server": "clock/v1, log/v1, net/v1, process/v1"}
        for n, caps in want.items():
            text = orbit.inspect(mods[n])
            check("validation: ok" in text and ("requires: " + caps + "\n") in text,
                  "inspect %s: validation ok, requires exactly %s" % (n, caps), text)
        tmp = tempfile.mkdtemp(prefix="orbit-test-")
        try:
            scenario_process(orbit, mods["args_stdin"])
            scenario_files(orbit, mods["files"], tmp)
            scenario_net(orbit, mods["echo"], mods["client"], tmp)
            scenario_http(orbit, mods["http_server"])
            scenario_cancel(orbit, mods["cancel"])
        finally:
            shutil.rmtree(tmp, ignore_errors=True)
    if not a.keep:
        shutil.rmtree(os.path.join(ROOT, "build", "orbit"), ignore_errors=True)
    print("%d checks, %d failures" % (checks, len(failures)))
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
