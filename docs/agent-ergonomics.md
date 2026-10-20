# Agent-ergonomics benchmark (ADR-0056 criterion C13)

How well can an AI coding agent that knows only the published documentation write correct Orin? This page records the
benchmark, its results and the findings. The findings may justify syntax or name changes **before the 1.0 freeze**
(ADR-0056); after the freeze a rename costs a major version.

The tasks, the final programs and the expected output are in [`bench/agent-ergonomics/`](../bench/agent-ergonomics/).
`bench/agent-ergonomics/run.sh` compiles and runs all ten and compares the output (`--update` rewrites the expected files).

## Method

* **Writer.** One agent (Claude) that knows TypeScript, Rust and Go but had no prior knowledge of Orin's library. It wrote every
  program in this session, one task at a time, in the order below.
* **Allowed sources.** `docs/tutorial/`, `docs/std.md` (and the `std-*.md` pages it links), `docs/reference/`, `docs/cli.md`,
  `docs/stability.md` and `README.md`. **Not read** while writing: `tests/`, `library/`, `compiler/`, and `examples/`, with one
  exception: for task 4 the server in `examples/projects/notes-service` was read to see how an Orin server is built and tested.
  `docs/ts-developers.md`, `docs/contracts.md` and `docs/concurrency.md` (linked from the tutorial) were **not** read either,
  which is itself a result: a first-time agent that follows only the tutorial hits things those pages explain (anonymous
  records, `Option` methods).
* **Attempt.** One call of `orin check` (then `orin run`) on a complete program. "Attempts" is the number of calls until the
  program compiled **and** printed the right output. A second source of failure, `orin verify --contracts` refuting a
  contract, is counted separately where it applies.
* **Library rule.** `library/` may be read only after a third failed attempt, and that must be recorded. No task needed it: the
  worst task took three attempts. (After all ten programs passed, `library/` and the compiler were grepped to confirm a
  finding, "there is no case conversion", before the docs were fixed. That is not part of any attempt.)
* **Toolchain.** `./tools/orin` from a source checkout (compiler `build/bootstrap/orin2`). The first call builds the
  development compiler (1 min 50 s here); later calls take under a second.
* **Honest limits.** One writer, one run per task: the numbers show where the first-time friction is, not a rate. The writer
  is a model that already knows the Orin tutorial's idioms from its own documentation reading, and it saw
  `.length.toInt()` and `==` on union values in the notes-service test when looking at the server (after tasks 1 to 3 were
  done).

## Results

| # | Task | Attempts | Compile errors | Final result |
|---|---|---:|---|---|
| 1 | word frequency over stdin | 2 | E0405 `toLowerCase` | ok |
| 2 | JSON config reader with validation | 1 | | ok |
| 3 | CSV sum by column | 3 | E0400 `int` vs `usize` (2 sites), then E0400 `expected usize, found int` (2 sites) | ok |
| 4 | tiny HTTP JSON endpoint (std:http + std:net, loopback test) | 2 | E0200 anonymous record type in a return type | ok |
| 5 | bank account with contracts | 3 (+1 verify) | E0200 `from` used as a parameter name (2 errors); E0401 mutating method on a parameter; `verify` REFUTED the constructor | ok, 15 of 15 clauses verified |
| 6 | generic `Stack<T>` with generic method | 1 | | ok |
| 7 | channel producer/consumer (std:task) | 2 | E0300 unknown type `Sender` (not imported) | ok |
| 8 | Result-heavy `key=value` parser | 2 | E0405 `okOr` on `Option` | ok |
| 9 | `Set` / `OrderedMap` | 1 | | ok |
| 10 | CLI with std:host capabilities | 3 | E0452 closure captures the `Host`; E0407 cannot infer the success type of `Err(..)` | ok |

20 attempts for 10 tasks (mean 2.0, median 2); three tasks were right on the first attempt (2, 6, 9: JSON decoding, generics,
collections: the parts whose names follow the documented patterns), none needed more than three. The 10 failed attempts
between them hit 9 distinct compiler errors and, in task 5, one `verify` refutation. Every program compiles and runs; none needed a workaround beyond
what the language offers (the case-folding in task 1 was dropped: see finding 3).

### Per-task detail

Each table: what failed, whether the diagnostic told the writer how to fix it, and what the documentation did or did not say.

**1. Word frequency.** 2 attempts.

| Problem | Diagnostic helped? | Docs |
|---|---|---|
| `raw.trim().toLowerCase()`: E0405 no method `toLowerCase` on `string` | Partly: it lists the methods a string has (so the absence is clear) but offers no alternative | Missing. No page says there is no case conversion; tutorial 5 lists the string methods without saying the list is complete. Reading stdin (`readLine(stdio)` from `std:io`) was only a name in `std.md`; the import path and signature were taken from the grant pattern and worked first time |

Guessed differently: `toLowerCase`/`toUpperCase`; `sort` needs a comparison closure even for strings (`(a, b) => a < b ? -1 : ...`),
where TypeScript's default and Rust's `sort()` need none.

**2. JSON config.** 1 attempt. The `std:json/decode` page documents every function and the example config; names and import lists
were taken from it directly. Doc problem: none. Slight cost: `decodeRoot`, `requiredField`, `decodeInt(cursor, min, max)`
and `?` make a long chain, but each step was discoverable. The error text names the JSON Pointer (`/port: integer out of range`).

**3. CSV sum.** 3 attempts.

| Problem | Diagnostic helped? | Docs |
|---|---|---|
| `while (i < names.length)` with `let i = 0`: E0400 cannot mix `int` and `usize`; convert explicitly | Half: says to convert, not how (`.toInt()` / `.toUsize()`) | Tutorial 5 says `length` is a `usize` but not that an index must be one, nor how to convert; `.toUsize()` is only in the reference (types, chapter 3). **Fixed**: tutorial 2 and 5 |
| after `.toInt()`: `names[i]` E0400 expected `usize`, found `int` | No: no suggestion, and the earlier advice (`.toInt()`) leads here | same |

Guessed differently: nearly every language a programmer knows lets an `int` variable index an array and compare with the length.

**4. HTTP endpoint.** 2 attempts.

| Problem | Diagnostic helped? | Docs |
|---|---|---|
| `): { code: int; body: string; } {`: E0200 expected identifier, found `{` | No: nothing says that record types must be named | Stated only in `ts-developers.md` (not on the tutorial path). **Fixed**: tutorial 3 now says it |

The rest compiled at once, helped by the notes-service example for the shape of a server and by consistent names: the docs list
`RequestParser`, `Response`, `standardStatus`, `serializeResponse`, `useAccepted`, `recv`, `sendAll`. Gaps: `std.md` mentions
`useListenerNet` and `useConnectionBeside` in prose but gives no signature (guessed from the `use*` pattern, correct;
**signatures added** to `std.md`), and no document says how to unit-test a server (the answer is "keep the handler pure and call it").
Constructing a `Response` takes six positional arguments including two `Headers` and a `forHead` flag; `ResponseParts`
is nicer but only appears in the API table.

**5. Bank account.** 3 attempts plus one `verify` round.

| Problem | Diagnostic helped? | Docs |
|---|---|---|
| `transfer(from: Account, ...)`: E0200 expected expression, found `from`, then a second E0200 on the signature | No: it does not say that `from` is a keyword | `from` is in the keyword list of the lexical reference; tutorial 2 did not mention that contextual TypeScript words are reserved. **Fixed**: tutorial 2 |
| `src.withdraw(amount)` on a parameter: E0401 cannot call mutating method on `src`: it is not declared with `let` | Mostly: but "declare with `let`" cannot be done for a parameter; the fix is to copy into a `let` and return the copy | Tutorial 4 says parameters are never mutable; I did not connect it to a method call |
| `verify --contracts`: REFUTED constructor `@Invariant(this.balance >= 0)` with `balance = -1` | Yes: counterexample, three options and a candidate `@Requires` | Tutorial 8 shows `@Requires`, `@Ensures`, `old`; constructor preconditions and `@Invariant` on a class are only in the reference |

Also: tutorial 8 says contracts are checked "with `orin compile --check-contracts`"; `orin run --check-contracts` is an unknown option
(`orin test` checks them). **Fixed**: tutorial 8.

**6. Generic stack.** 1 attempt. Everything (field initialiser `items: T[] = []`, `Option` returns, `<U>` method type parameter,
`T extends Ord`) matched tutorial 4. Note that `Stack<T>` has to expose `items` publicly for `largestOf`, since there is no
`friend` or iterator protocol.

**7. Producer/consumer.** 2 attempts.

| Problem | Diagnostic helped? | Docs |
|---|---|---|
| `tx: Sender<int>` in a signature: E0300 unknown type `Sender` | No import suggestion | The tutorial only uses `ch.tx` and never names the types. **Fixed**: tutorial 10 |

Everything else (structured `scope`, `spawn`, `join`, bounded `channel`, closing to end the consumer) came straight from tutorial 10.
Guessed differently: nothing; the capture rule ("a closure takes a snapshot") was clear, but using `ch.tx` from two tasks
is only implied.

**8. `key=value` parser.** 2 attempts.

| Problem | Diagnostic helped? | Docs |
|---|---|---|
| `parseInt(v).okOr(BadInt(..))`: E0405 no method `okOr` on `Option<int>` | Partly: it names the type but, unlike for `string`, does not list the methods that exist | Reference 3 lists the `Option` and `Result` methods but the tutorial never says that is all there is. **Fixed**: tutorial 3 lists them and says to use `match` |

Guessed differently (not yet tried, same family): `Result.unwrapOr` does not exist, only `Option.unwrapOr`; no `map`, `andThen`, `mapErr`.

**9. Set and OrderedMap.** 1 attempt. `Set.add` returning `bool`, `OrderedMap(16)`, `floorKey`/`ceilKey`, `entries()` with `.key`
and `.value` were all in `std.md`. Guessed differently, but documented: `Map.size` is a property while `Set.size()` and
`OrderedMap.size()` are methods; `new OrderedMap<K, V>(16)` takes a tuning argument that a newcomer cannot choose (the docs say "use 16").

**10. CLI with host capabilities.** 3 attempts.

| Problem | Diagnostic helped? | Docs |
|---|---|---|
| `withFs(host, fs => withStdio(host, ...))`: E0452 a closure cannot capture a resource handle | Half: the text is right but it does not name the variable (`host`) or say that `withHost` hands out all grants at once | Tutorial 6 says grants cannot be captured but not that the `Host` cannot. `std.md` listed `useFs`... but not their `with*` twins. **Fixed**: tutorial 6 and `std.md` |
| `withHost(host, (fs, proc, stdio, clock) => { ... return Err("usage") ...})`: E0407 cannot infer the success type of `Err(..)` | Yes (the fix, an annotation, is clear) but no example is shown | Not documented. **Fixed**: `std.md` and tutorial 3 |

The `Result<void, string>` plus `Ok()` convention for success worked. `console.error` and `exit` need no grant.

## Findings, ranked

Rank = how many times the problem bit (failed attempts attributable to it), then how likely a fresh agent is to repeat it.
Classes: **(a)** documentation fix, **(b)** diagnostic improvement (listed, not implemented here), **(c)** syntax or name
candidate for the freeze, with a concrete proposal (listed, not implemented here).

| # | Finding | Bit | Class |
|---:|---|---|---|
| 1 | `int` / `usize` friction: `length` is `usize`, indexing needs `usize`, literals adapt, variables do not | 1 task, 2 attempts, 4 sites | a, b, c |
| 2 | `Option` / `Result` have no combinators (`okOr`, `map`, `andThen`, `mapErr`; `Result.unwrapOr`) | 1 task | a, b, c |
| 3 | No `toLowerCase` / `toUpperCase`; `sort` needs a comparison even for strings | 1 task (+ 3 uses of the comparator) | a, c |
| 4 | Closures cannot capture the `Host` or a grant; closure `Err(..)` needs a result type | 1 task, 2 attempts | a, b |
| 5 | `from` is a hard keyword | 1 task | a, b, c |
| 6 | Record types must be named; the error is cryptic | 1 task | a, b |
| 7 | A type named in a signature must be imported; unknown-type diagnostic suggests nothing | 1 task | a, b |
| 8 | Methods cannot mutate a parameter; the diagnostic suggests the impossible `let` | 1 task | b |
| 9 | `orin run` has no `--check-contracts`; tutorial 8 implied it | doc only | a |
| 10 | Inconsistent size accessors: `Map.size`, `Array.length` (properties) vs `Set.size()`, `Deque.size()` (methods) | 0 (documented) | c |
| 11 | Stdin, `std:net` loopback and `with*` twins are described in prose or not at all | 0 (guessed correctly) | a |

### (a) Documentation fixes made in this change

* `docs/tutorial/02-values.md`: conversions (`toUsize`, `toFloat`) and the `usize` index rule; a paragraph on reserved words
  (`from`).
* `docs/tutorial/03-data.md`: record types are always named; closures returning `Err(..)`/`Ok(..)` need a result type; the
  complete list of `Option` and `Result` methods and the missing combinators.
* `docs/tutorial/05-collections.md`: array index must be `usize`; `.toInt()` / `.toUsize()`; no `toLowerCase` / `toUpperCase`.
* `docs/tutorial/06-cli.md`: the `Host` cannot be captured either; `withHost` returns a value.
* `docs/tutorial/08-contracts.md`: `orin run` has no `--check-contracts`; use `orin test` or `orin compile --check-contracts`.
* `docs/tutorial/10-concurrency.md`: `Sender<T>`, `Receiver<T>`, `TaskHandle<T>` and `Scope` are imported from `std:task`.
* `docs/std.md`: the `with*` twins of the `use*` functions; signatures and imports for `readLine`, `readBytes`, `writeStdout`,
  `args` and `exit`; the `Host`-capture rule and the `withHost` closure annotation; signatures of `useListenerNet` and
  `useConnectionBeside`.

Still open (a): show a stdin-reading program in tutorial 6 (today only a file is read); a "unit-testing a server" paragraph; mention
that `sort` always takes a comparison.

### (b) Diagnostic improvements (compiler/ is not touched by this change)

1. **E0400 `int` vs `usize`**: add a help line naming the conversion: "use `.toUsize()` on the `int`" / "use `.toInt()` on the `usize`".
   The current text ("convert explicitly") and the second form ("expected `usize`, found `int`", no help) send the writer round in a circle.
2. **E0200 on a keyword used as a name** (`from`, `type`, `match`, ...): say "`from` is a keyword and cannot be a name", and do not
   emit the second cascading E0200 on the signature.
3. **E0200 `expected identifier, found {` in a type position**: add "record types are named: declare `type Name = { ... }` and use `Name`".
4. **E0405 on `Option` / `Result`**: list the available methods, as the `string` variant already does, and suggest `match` when the
   missing method is a combinator (`okOr`, `map`, `mapErr`, `andThen`).
5. **E0300 unknown type that is exported by a standard module** (`Sender`, `Receiver`, `TaskHandle`, `Scope`): add "add it to the
   `import ... from "std:task"` list".
6. **E0452**: name the captured variable (`host`), and when it is a `Host` or grant say "take the grants once with
   `useHost` / `withHost` and pass them as arguments".
7. **E0407**: show the annotation in the note: `(fs, proc, stdio, clock): Result<void, string> => ...`.
8. **E0401 on a parameter**: add "parameters are immutable; copy it first (`let s = src;`) and return the changed copy".
9. **`verify` counterexamples** for constructors list every field twice (`owner.length = 1, ..., this.owner.length = 1`); showing the
   parameter that violates the clause (`balance = -1`) would be enough.

### (c) Syntax and name candidates for the freeze

Each is additive or renames a small surface; none changes the meaning of a program that compiles today, so they can also wait
until after the freeze (as additions) except where marked.

1. **`int` / `usize`** (finding 1, the most frequent). Proposal: accept an `int` expression as an array or string index (a negative
   value or one at least `length` traps exactly like an out-of-range `usize` today) and allow comparing `int` with a `usize` length
   by widening the `usize`. Alternative: make `length`, `size()` and `indexOf` return `int`, keeping `usize` for explicit sizes.
   The current rule rejects a program in every loop over an array, and the two-step error message (finding 1) shows that
   even a writer who follows the diagnostic cannot get out without knowing `toUsize`. Decide before the freeze: adding the
   implicit index conversion later is compatible, changing the type of `length` is not.
2. **`Option` / `Result` combinators.** Add to the prelude, with the Rust/TypeScript spellings: `Option.map(f)`, `Option.andThen(f)`,
   `Option.okOr(e)`, `Result.map(f)`, `Result.mapErr(f)`, `Result.andThen(f)`, `Result.unwrapOr(d)`. The names are the part that
   must be fixed before the freeze; the set can start with `okOr`, `mapErr`, `Result.unwrapOr` (the three that bit or are
   asymmetric).
3. **Case conversion.** `string.toLowerCase()` and `string.toUpperCase()` (ASCII only until Unicode tables exist, documented as
   such, like `std:http.toLowerAscii` today) or `std:text.toLowerAscii`/`toUpperAscii`. Also a default ordering for sorting:
   `xs.sort()` for `T extends Ord` (the closure form stays); today a sorted list of words needs
   `(a, b) => a < b ? -1 : a > b ? 1 : 0` written out (three times in tasks 1 and 9). A function `compare<T extends Ord>(a, b): int`
   in the prelude would also do.
4. **`from` as a contextual keyword.** Parse `from` as a keyword only in `import { .. } from "..."` so that `transfer(from, to, n)` works.
   A parameter named `from` is the first thing a TypeScript or Go programmer writes for a transfer or a range.
5. **Uniform size accessor.** `Map.size` and `Array.length` are properties, `Set.size()`, `OrderedMap.size()` and `Deque.size()` are
   methods. Proposal: add `size()` / `length()` method spellings on `Map` and arrays, or turn the collection classes' `size()`
   into a property (`size`), and decide before the freeze which one is the documented spelling. It did not cost an attempt here only
   because `std.md` states it.
6. **Not recommended:** anonymous record types and object literals, `Option.map` as a method chain on `?.`; these are deliberate
   non-goals in `ts-developers.md` and the error message (b3) is the right fix.

### What worked without trouble

Naming consistency made first guesses right for: `Set`, `OrderedMap`, `std:json/decode`, `scope`/`spawn`/`join`, `channel`, generic classes
and methods, `@Requires`/`@Ensures`/`old`/`==>`, `@Invariant` on a class, `useListenerNet` and `useConnectionBeside`, `withHost`,
`writeStdout`, and `Result<void, E>` with `Ok()`. `orin verify --contracts` proved all 15 clauses of the account program once the
constructor precondition was added, and its refutation message told the writer exactly what to do.

## Decisions for the freeze (2026-10-18)

Taken by the release thread under the owner's "decide and finish" rule (fastest path to 1.0). A finding changes
the language or a name before the freeze only if it cannot be fixed by an addition later, because 1.x may add but
not change.

| Finding | Decision |
|---|---|
| int/usize indexing | No language change: `usize` indices and `length` stay (they carry the bounds proofs). The E0400 message should name `.toUsize()` / `.toInt()`, a diagnostic item for 1.0. |
| Option/Result combinators | Additive, so not freeze-blocking. The names are fixed now so that 1.x cannot pick others: `map`, `andThen`, `okOr` on `Option`; `map`, `mapErr`, `andThen`, `unwrapOr` on `Result`. |
| `toLowerCase`/`toUpperCase`, no-argument `sort()` | Additive (ASCII case conversion; `sort()` for `T extends Ord`), 1.x or earlier if time allows. |
| `from` as a hard keyword | Making it contextual accepts more programs, so it is additive; it stays reserved for 1.0 and may become contextual in 1.x. |
| Named record types only | Stays (anonymous record types are not in the 1.0 grammar); the diagnostic should say "name the record type". |
| `size` property vs `size()` method | The one breaking item. Decision: it stays as frozen (`Map.size`, `Array.length` are properties; `Set`, `OrderedMap`, `Deque` use `size()`), documented in std.md. A rename later would need a deprecation cycle. |
| Closure capturing `Host`, `Err(..)` result type, missing import hint, parameter mutation hint, `orin run --check-contracts` | Diagnostic and doc items; the docs are fixed in this change, the diagnostics are listed for 1.0. |

## Reproduce

```sh
./tools/bootstrap.sh                 # when build/bootstrap/orin2 is missing
bench/agent-ergonomics/run.sh        # compile, run and compare all ten tasks
bench/agent-ergonomics/run.sh 03 07  # a subset
```
