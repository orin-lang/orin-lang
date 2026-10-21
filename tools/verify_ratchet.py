#!/usr/bin/env python3
"""CI ratchet for `orin verify --contracts` on the compiler's own sources (docs/contracts.md, "Verification ratchet").

  python3 tools/verify_ratchet.py --check     run the verifier on compiler/main.or and compare with the baseline
  python3 tools/verify_ratchet.py --update    run it (twice, see --runs) and rewrite tools/verify-baseline/compiler.txt

--check fails (exit 1) when
  * any obligation is REFUTED (the ratchet starts at 0 and stays there), or
  * an obligation has more UNKNOWN results than the baseline (new obligation, or VERIFIED in the baseline and now UNKNOWN).
It passes when things improve (UNKNOWN -> VERIFIED, removed obligations) and then prints a hint to run --update.

Regenerating the baseline (one command; run it after merging or rebasing a PR that changes obligation counts, e.g. the
verifier-gaps PR that adds loop obligations):

  python3 tools/verify_ratchet.py --update --orin $PWD/build/bootstrap/orin2 --cache-dir $PWD/build/rat/cache --threads 4

It needs only a built compiler (build/bootstrap/orin2, or --orin PATH), takes the rlimit defaults below, and refuses to write
when anything is REFUTED. Commit tools/verify-baseline/compiler.txt; the per-module table it prints is for the PR body.

Obligation key: file, function, kind, clause text. No line numbers: an unrelated edit above a function must not break
the baseline. One key can stand for several obligations (an `ensures` is asked at every return); the baseline keeps
`V<verified> U<unknown>` for the key, and U may not grow. An obligation whose status differed between the runs of
--update is `unstable` (a wall-clock safety net fired in one run): it is tolerated either way, but never when REFUTED.

Determinism: z3's `--rlimit` (resource units, independent of machine load) is the deciding budget; the wall times are only a
safety net far above what the rlimit needs. Extra arguments after `--` go to `orin verify`.
"""
import argparse, json, os, subprocess, sys, time
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASELINE = os.path.join(ROOT, "tools", "verify-baseline", "compiler.txt")
HEADER = [
    "# Baseline of tools/verify_ratchet.py: `orin verify --contracts compiler/main.or` (docs/contracts.md, ratchet).",
    "# Do not edit by hand: python3 tools/verify_ratchet.py --update",
    "# file | function | kind | clause | V<verified> U<unknown> [unstable]",
]
# defaults chosen by measurement (docs/contracts.md): deciding budget is the rlimit
RLIMIT = 3000000
TIMEOUT_MS = 60000
RETRY_MS = 10000


def z3_version():
    try:
        return subprocess.run(["z3", "--version"], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True).stdout.strip()
    except OSError:
        return "(z3 not found)"


def baseline_z3():
    for ln in open(BASELINE, encoding="utf-8"):
        if ln.startswith("# z3: "):
            return ln[6:].strip()
    return ""


def run_verify(a, extra, tag):
    wd = os.path.join(ROOT, "build", "ratchet", tag)
    os.makedirs(wd, exist_ok=True)
    cmd = [a.orin, "verify", "--contracts", "--format=json", "--rlimit", str(a.rlimit),
           "--timeout-ms", str(a.timeout_ms), "--retry-ms", str(a.retry_ms), "--solver-stats"]
    if a.cache_dir:
        cmd += ["--cache-dir", os.path.abspath(a.cache_dir)]
        if not a.no_cache_wall_unknown:
            # also keep the wall-clock unknowns (~250 queries of ~60 s each, a third of a warm run): for a ratchet a sticky
            # timeout is harmless (a changed function is another query text; a timeout that would be solved only improves)
            cmd += ["--cache-unknown"]
    cmd += extra + [os.path.join(ROOT, "compiler", "main.or")]
    env = dict(os.environ)
    if a.threads:
        env["ORIN_THREADS"] = str(a.threads)
    t = time.time()
    p = subprocess.run(cmd, cwd=wd, env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    sys.stderr.write(p.stderr[-400:])
    print("verify run %s: %.0f s" % (tag, time.time() - t), file=sys.stderr)
    try:
        return json.loads(p.stdout)
    except ValueError:
        sys.exit("verify_ratchet: no JSON from orin verify (exit %d): %s" % (p.returncode, p.stdout[:300]))


def rel(f):
    f = f.replace("\\", "/")
    i = f.find("compiler/")
    return f[i:] if i >= 0 else f


def collect(res):
    """key -> [verified, unknown, refuted]"""
    d = defaultdict(lambda: [0, 0, 0])
    for r in res["results"]:
        k = (rel(r["file"]), r["function"], r["kind"], " ".join(str(r.get("clause", "")).split()))
        s = r["status"]
        d[k][0 if s == "VERIFIED" else 2 if s == "REFUTED" else 1] += 1
    return d


def read_baseline():
    d = {}
    for ln in open(BASELINE, encoding="utf-8"):
        ln = ln.rstrip("\n")
        if not ln or ln.startswith("#"):
            continue
        f = ln.split(" | ")
        tail = f[-1].split()
        d[(f[0], f[1], f[2], " | ".join(f[3:-1]))] = (int(tail[0][1:]), int(tail[1][1:]), "unstable" in tail)
    return d


def module_of(f):
    p = f.split("/")
    return p[1] if len(p) > 2 else "(root)"


def table(d):
    m = defaultdict(lambda: [0, 0, 0])
    for k, (v, u, r) in d.items():
        t = m[module_of(k[0])]
        t[0] += v
        t[1] += u
        t[2] += r
    out = ["| module | VERIFIED | UNKNOWN | REFUTED |", "|---|---:|---:|---:|"]
    for k in sorted(m):
        out.append("| %s | %d | %d | %d |" % (k, *m[k]))
    t = [sum(x[i] for x in m.values()) for i in range(3)]
    out.append("| **total** | %d | %d | %d |" % tuple(t))
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--check", action="store_true")
    g.add_argument("--update", action="store_true")
    ap.add_argument("--orin", default=os.path.join(ROOT, "build", "bootstrap", "orin2"))
    ap.add_argument("--rlimit", type=int, default=RLIMIT)
    ap.add_argument("--timeout-ms", type=int, default=TIMEOUT_MS)
    ap.add_argument("--retry-ms", type=int, default=RETRY_MS)
    ap.add_argument("--cache-dir", default="", help="answer cache of orin verify (sat, unsat and rlimit-unknown answers, keyed by z3 version and rlimit; safe)")
    ap.add_argument("--no-cache-wall-unknown", action="store_true", help="do not cache wall-clock unknowns (default with --cache-dir: cache them)")
    ap.add_argument("--threads", type=int, default=0)
    ap.add_argument("--runs", type=int, default=2, help="--update: number of runs; differing obligations are unstable")
    ap.add_argument("--from-json", nargs="+", help="use these saved `verify --format=json` outputs instead of running")
    ap.add_argument("--table", action="store_true", help="print the per-module table (markdown)")
    a, extra = ap.parse_known_args()
    extra = [x for x in extra if x != "--"]
    if a.from_json:
        runs = [json.load(open(p)) for p in a.from_json]
    else:
        runs = [run_verify(a, extra, "run%d" % i) for i in range(a.runs if a.update else 1)]
    cs = [collect(r) for r in runs]
    keys = set().union(*cs)
    cur = {}
    for k in keys:
        vals = [tuple(c.get(k, (0, 0, 0))) for c in cs]
        unstable = len(set(vals)) > 1
        v = max(x[0] for x in vals) if not unstable else min(x[0] for x in vals)
        u = max(x[1] for x in vals)
        r = max(x[2] for x in vals)
        cur[k] = (v, u, r, unstable)
    refuted = sorted(k for k, x in cur.items() if x[2])
    if a.update:
        if refuted:
            for k in refuted:
                print("REFUTED: %s %s [%s] %s" % k, file=sys.stderr)
            sys.exit("verify_ratchet: refusing to write a baseline with REFUTED obligations (the ratchet starts at 0)")
        os.makedirs(os.path.dirname(BASELINE), exist_ok=True)
        with open(BASELINE, "w", encoding="utf-8") as f:
            f.write("\n".join(HEADER[:2] + ["# z3: " + z3_version()] + HEADER[2:]) + "\n")
            for k in sorted(cur):
                v, u, r, un = cur[k]
                f.write(" | ".join(k) + " | V%d U%d%s\n" % (v, u, " unstable" if un else ""))
        n_un = sum(1 for x in cur.values() if x[3])
        print("verify_ratchet: baseline written: %d keys, %d unstable" % (len(cur), n_un))
        print(table({k: x[:3] for k, x in cur.items()}))
        return
    base = read_baseline()
    if not a.from_json and baseline_z3() != z3_version():
        print("verify_ratchet: note: baseline made with %r, running with %r (rlimit counts differ between z3 versions)" % (baseline_z3(), z3_version()), file=sys.stderr)
    bad, better = [], []
    for k in sorted(cur):
        v, u, r, _ = cur[k]
        b = base.get(k)
        if r:
            bad.append("REFUTED: %s :: %s [%s] %s" % (k[0], k[1], k[2], k[3]))
        elif b is None:
            if u:
                bad.append("new UNKNOWN (obligation not in baseline): %s :: %s [%s] %s" % (k[0], k[1], k[2], k[3]))
        elif not b[2] and u > b[1]:
            why = "was VERIFIED" if b[1] == 0 else "was UNKNOWN %d times" % b[1]
            bad.append("new UNKNOWN (%s, now %d): %s :: %s [%s] %s" % (why, u, k[0], k[1], k[2], k[3]))
        elif not b[2] and u < b[1]:
            better.append(k)
    gone = [k for k in base if k not in cur]
    if a.table:
        print(table({k: x[:3] for k, x in cur.items()}))
    for s in bad:
        print("verify_ratchet: " + s, file=sys.stderr)
    if bad:
        print("verify_ratchet: FAILED (%d). A new UNKNOWN means the verifier no longer proves what it proved before: fix the "
              "code or the contract; do not refresh the baseline for it." % len(bad), file=sys.stderr)
        sys.exit(1)
    if better or gone:
        print("verify_ratchet: ok; %d obligations improved, %d removed: run `python3 tools/verify_ratchet.py --update` and "
              "commit tools/verify-baseline/compiler.txt" % (len(better), len(gone)))
    else:
        print("verify_ratchet: ok (%d obligation keys, baseline unchanged)" % len(cur))


if __name__ == "__main__":
    main()
