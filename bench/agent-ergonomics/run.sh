#!/usr/bin/env bash
# Compile and run every agent-ergonomics task, compare stdout with expected.out.
# Usage: bench/agent-ergonomics/run.sh [--update] [NN ...]     (needs ./tools/orin, i.e. a bootstrapped compiler)
# Per task: main.or (the program), expected.out, optional `stdin` (fed to the program) and `args` (one argument per line).
set -u
here="$(cd "$(dirname "$0")" && pwd)"
root="$(cd "$here/../.." && pwd)"
update=0
if [ "${1:-}" = "--update" ]; then update=1; shift; fi
pass=0; fail=0
for dir in "$here"/tasks/*/; do
  name="$(basename "$dir")"
  if [ $# -gt 0 ]; then
    match=0; for p in "$@"; do case "$name" in "$p"*) match=1;; esac; done
    [ $match = 1 ] || continue
  fi
  out="$(mktemp)"; bin="$(mktemp)"
  if ! "$root/tools/orin" build "$dir/main.or" -o "$bin" >"$out.build" 2>&1; then
    echo "FAIL  $name (compile)"; sed 's/^/      /' "$out.build" | head -20; fail=$((fail+1)); rm -f "$out" "$out.build" "$bin"; continue
  fi
  argv=()
  if [ -f "$dir/args" ]; then while IFS= read -r a; do argv+=("$a"); done < "$dir/args"; fi
  stdin=/dev/null; [ -f "$dir/stdin" ] && stdin="$dir/stdin"
  (cd "$dir" && "$bin" ${argv[@]+"${argv[@]}"} <"$stdin" >"$out" 2>/dev/null)
  if [ $update = 1 ]; then cp "$out" "$dir/expected.out"; echo "UPDATED $name"; pass=$((pass+1))
  elif cmp -s "$out" "$dir/expected.out"; then echo "PASS  $name"; pass=$((pass+1))
  else echo "FAIL  $name (output differs)"; diff "$dir/expected.out" "$out" | head -10 | sed 's/^/      /'; fail=$((fail+1)); fi
  rm -f "$out" "$out.build" "$bin"
done
echo "$pass passed, $fail failed"
[ $fail = 0 ]
