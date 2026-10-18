# C2: trap-safe structured cleanup (freeze item C6, ADR-0017 C2)

Status: proposed design, 2026-10-18. For review by the project owner. It changes no accepted behavior, public API or
delivery date. Implementation is planned for the runtime session starting 2026-10-20 and lands only after this design is
accepted.

Anchors: [ADR-0017](../decisions/0017-concurrency-design.md) (Addenda B to D, section "What is not interrupted"),
[async-concurrency roadmap](../roadmaps/async-concurrency.md) section 2, [ADR-0056](../decisions/0056-syntax-and-std-freeze.md)
(C6), [ADR-0030](../decisions/0030-provable-std-and-minimal-trusted-runtime.md) (policy in Orin, mechanism in L0),
[ADR-0054](../decisions/0054-l0-platform-budget-for-concurrency.md) (L0 budget).

## 1. Problem

A trap on a task thread ends that thread and nothing else. A scope the thread had open is abandoned with its children still
running; the children keep their grants, files and sockets, and the parent's trap is reported while the work it started goes
on. Cancellation exists (`CancelToken`, `Scope.cancel`) but only network waits observe it. A task blocked in a channel wait,
`join`, `select` or `sleep` cannot be cancelled, so a scope cannot be made to stop even by an explicit `cancel()`.

The goal of C2: when a task traps, every scope it has open is cancelled and joined (its cooperative descendants have ended)
before the thread exits, and the failure is reported deterministically. The same mechanism makes `cancel()` effective for
channel waits, `join`, `select` and `sleep`.

## 2. Today (baseline `origin/main`)

| Area | Behavior | Source |
|---|---|---|
| Trap on a task thread | `trapAt` copies the message into the task record, sets `trapped`, clears `H_TASK`, calls `heapRetire` (revokes grants, closes files, frees the network buffer, folds counters), `signalDone`, then `plat(PL_THREAD_EXIT)`. It holds no lock and allocates nothing; a failure inside it is an exit. | `runtime/core/task.or` `trapAt`, `trap`, `trapStr` |
| Frames between the trap and the thread entry | Not unwound by Orin code: `thread_exit` forces the unwind (risk 3 of ADR-0017). `finish(tab)` of every open `scope` is therefore never reached. | `runtime/core/task.or` header; `library/std/task.or` `scope`, `finish`, `drain` |
| Children of the trapping task's scopes | Keep running. Their task tables, result monitors and wake sources are never freed (`wakeClose` and `monFree` live in `finish`). | `library/std/task.or` `begin`, `finish` |
| Channel waits | `recv`, `send`, `recvUntil`, `sendUntil`, `select*` wait with `monWait` / `monWaitUntil` on the channel monitor. They end by a value, a close or a deadline; the cancel token is not read. | `library/std/task.or` `Receiver.recv` and the loops around it |
| `join`, `joinUntil`, `sleep`, `sleepUntil` | `join` is `taskJoin` (a thread join); `joinUntil` and `sleepUntil` use `monWaitUntil` on a result or private monitor. None reads the token. | `library/std/task.or` `TaskHandle.join`, `joinUntil`, `sleepUntil` |
| The token | An L0 wake source: a flag, plus an eventfd (a pipe off Linux) created when a network wait first polls it. Sources form a tree; `wake_check` is true if the source or an ancestor is set. Network waits `poll` the eventfd with their socket. A condition-variable wait cannot poll an eventfd, so setting the token cannot wake a monitor wait. | `runtime/platform/orin_platform.c` `wake_*`; `orin_platform.h` |
| Errors | `TaskErrorKind = Timeout \| Closed \| ClockUnavailable \| InvalidDuration`. `std:net` already has `Cancelled` (L0 code 1004). | `library/std/task.or`, ADR-0017 Addendum D |
| Documented as open | "Waits on channels do not observe the token yet ... Making them checkpoints (and a trapped task cancelling its scope) is C2." | ADR-0017 Addendum D section 6(b) |

## 3. Requirements (roadmap section 2, restated as checks)

R1. Waits are interruptible: register a waiter atomically with checking cancellation, then park; a racing cancel is not lost;
recheck predicates after spurious wakes; a timed-out join does not consume the join right.

R2. A live-scope registry: each task knows its open scopes. Trap and normal scope exit stop admission, request cancellation,
wake blocked descendants and join them before scope state is released. A task never waits for itself and never frees state a
descendant can still reach (including a monitor a waiter or cancel callback can reach).

R3. Deterministic primary and secondary failure reporting, including a trap during cleanup. The same path runs when a `join`
propagates a child trap into a parent that has other live children.

R4. Cancellation is cooperative. A CPU loop that never checks is not stopped; this limit is documented and tested, not hidden.

R5. A cleanup hook cannot resume an arbitrary monitor critical section after a trap. State a trap left inconsistent is
abandoned or the process ends; the design does not claim otherwise.

R6. Channel `close` keeps its meaning (a shared-endpoint operation). Cancelling one receive must not close the channel for
other users. Cancellation is not encoded as end of stream or as a task trap.

Acceptance (roadmap): parent traps with nested children blocked on empty or full channels and in joins; scope body traps
before returning; cancel before, during and after wait registration; close and drain races; multiple waiters; duplicate join;
pending result and message disposal. All cooperative descendants finish, registrations are removed, thread, monitor and
transfer registries return to baseline.

## 4. Design

### 4.1 Overview

Three mechanisms, each small:

1. A process-wide registry of waiting monitors (section 4.2), so that a cancel can notify the monitors on which tasks wait.
2. Every blocking wait of `std:task` becomes a cancellation checkpoint using register, check, wait (section 4.3), and
   reports `Err(Cancelled)` where it returns a `Result` (section 4.4).
3. A per-task stack of open scopes, which the trap path (and normal scope exit) unwinds: stop admission, cancel, wake,
   join, release (sections 4.5 and 4.6).

No new primitive is needed in L0: it already has monitors with notify from any thread, and `wake_check`/`wake_signal`. The
eventfd stays a wake source for network waits only.

### 4.2 The waiter registry

One process-wide table, protected by one registry monitor `R`. An entry is `(monitor, wake)`: the monitor a task waits on and
the wake source bound to that task (`wakeBound()` at the time of the wait; 0 = none, so the task is never cancelled and needs
no entry). Entries are `register(m)` and `deregister(m)`; a thread has at most one entry at a time (`select` waits on its own
private watcher monitor `w`, not on the channels, so it registers `w`).

`cancelNotify(c)`, called by `Scope.cancel`, `CancelToken.cancel` and the unwind (4.5) right after `wakeSignal(c)` succeeded:

```
lock R
for each entry e in R:
    if wakeCheck(e.wake) == 1:        # e.wake is c, a descendant of c, or otherwise set
        lock e.monitor; notifyAll(e.monitor, 0); notifyAll(e.monitor, 1); unlock e.monitor
unlock R
```

Cost: O(live waiters) per cancel, no allocation under `R` beyond table growth done at `register` time. If this shows up in
the stress runs, the table becomes per-token lists; the interface does not change.

`R` is held across the notifications on purpose: `deregister` also takes `R`, so a waiter cannot return, and its owner cannot
free the monitor, while `cancelNotify` may still touch it. This is the roadmap's "never free a monitor while a waiter or
cancellation callback can reach it". The scan only locks monitors that have an entry, and an entry exists only while its waiter
is between `register` and `deregister`.

Lock order: **registry, then channel (or other waited monitor)**. No code path takes `R` while holding a waited monitor
(section 4.3 registers before locking the channel and deregisters after unlocking it), so there is no cycle. The watcher
monitors of `select` keep their order (channel, then watcher, as today); `cancelNotify` locks a watcher monitor only as a
leaf under `R`.

Where `R` lives: it is a runtime singleton. `runtime/core/task.or` keeps its handle in the shared block (one word, created
lazily under the runtime lock) and exposes `waitRegistry(): usize`. `library/std/task.or` implements the table (words in the
monitor, like the scope table) so that the layout, the growth rule and the matching live next to the waits that use them.

### 4.3 Waits as checkpoints without lost wakeups

Every blocking wait follows this shape (shown for `recv`):

```
const w = wakeBound()                    # 0: not cancellable, skip register/deregister and the checks
if w != 0: registryAdd(ch, w)            # 1. register BEFORE looking at anything
lock ch
loop:
    if predicate satisfied: break        # value available, closed, drained, ...
    if w != 0 and wakeCheck(w) == 1: cancelled = true; break    # 2. check the token under the channel lock
    monWait(ch, 1)                       # 3. park (atomically unlocks ch)
...
unlock ch
if w != 0: registryRemove(ch)            # after unlock: never hold ch while taking R
```

Why no wakeup is lost. Let `S` be the instant `wakeSignal(c)` takes effect and `N` the registry scan of `cancelNotify` (which
starts after `S`).

- If the waiter's check (step 2) runs after `S`, it sees the token and does not wait.
- If the check runs before `S`, the waiter is either still before its `monWait` or inside it. The check and the `monWait` happen
  under the channel lock, and `N` needs that lock to notify. So `N`'s notify on that channel runs after the waiter is parked, or
  after it has already left.
- `N` finds the entry: the entry was added before the check (step 1), the check is before `S`, and `N` starts after `S`, so the
  entry is present when `N` scans, unless the waiter already returned (then nothing is lost).

Spurious wakeups only repeat the loop. A notify that finds the predicate unchanged and the token set returns `Cancelled`.
A wake with the token set and a satisfied predicate returns the predicate's result (a value that is already there is returned,
as for deadlines today).

Timed waits (`monWaitUntil`) use the same loop with the one absolute deadline kept across retries. `join` and `drain` (which
today block in `taskJoin`, a thread join) get an interruptible form in section 4.6. `sleepUntil` waits on a private monitor
that it registers like any other.

The mutex of the waited monitor is never held across `registryAdd` or `registryRemove`, and `R` is never held across a
`monWait`, so a parked task blocks no other task from registering or cancelling.

### 4.4 Error surface: `TaskErrorKind.Cancelled`

`TaskErrorKind = Timeout | Closed | ClockUnavailable | InvalidDuration | Cancelled`, with `taskErrorMessage(Cancelled)` =
"the task was cancelled". This is an addition to a closed set: callers that `match` exhaustively get a compile-time prompt
(this is the one source-visible effect for existing code). The API snapshot `api/std/task.api.txt` changes.

Which calls report it:

| Call | Result when the token is set and the call would block |
|---|---|
| `Sender.send`, `sendUntil`, `sendTimeout` | `Err(Cancelled)`; the value was not enqueued (it is dropped by the caller as for `Closed`; a send that already enqueued the value returns `Ok`). |
| `Receiver.recvUntil`, `recvTimeout`, `selectUntil`, `selectTimeout`, `joinUntil`, `joinTimeout`, `sleep` | `Err(Cancelled)`. |
| `Receiver.recv()` and `select()` | **Open question, see section 8.** Their types are `Option<T>` and `Result<Selected<T>, TaskError>`. `select` can carry `Cancelled`. `recv(): Option<T>` cannot without being mistaken for end of stream (R6). |
| `TaskHandle.join()`, `sleepUntil` (returns `void`) | **Open question.** `join()` returns `T`. Interrupting it would have to trap or change type. Proposal: `join()` is not a checkpoint; `joinUntil` is. |

A non-cancellable task (no bound token) behaves exactly as today.

### 4.5 The per-task stack of open scopes

`scope()` already has a table `tab` per open scope (a monitor with the ledger, `LG_WAKE`, the closed flag). C2 makes each
task's open scopes discoverable from its own thread state:

- `runtime/core/task.or` adds one word, `H_SCOPES`, to the thread-local block (next to `H_TASK`, `H_JOINED`): the address of a
  small growable array of table handles, newest last. Two runtime functions: `scopePush(tab)` and `scopePop(tab)` (the pop
  checks that `tab` is the top entry; a mismatch is an internal error, an exit). The array is freed by `scopePop` when empty
  and by `heapRetire` as a backstop.
- `begin()` in `library/std/task.or` calls `scopePush(tab)` after it creates the table and the wake source; `finish()` calls
  `scopePop(tab)` last.

Only the owning task reads or writes its stack; there is no lock. The trap path reads it on the same thread.

### 4.6 Unwinding on a trap (the C2 core)

`trapAt` on a task thread currently goes: record message, `heapRetire`, `signalDone`, `thread_exit`. C2 inserts one step before
`heapRetire`, while the task's heap, grants and files are still alive (the unwind runs std code that allocates and takes locks, so
it must run before the heap retires, not after). This weakens the current "the trap path allocates nothing and holds no lock"
property for tasks that have open scopes; tasks without open scopes keep it.

```
trapAt(msg):
    record message and trapped flag                 # primary failure, as today
    if unwindFn != 0 and H_SCOPES != 0 and not UNWINDING:
        set UNWINDING in the task record            # re-entrancy guard, section 5
        call the unwind callback                    # section 4.6.1
    heapRetire(); signalDone(t); thread_exit
```

The step runs `unwindScopes()` which, newest scope first:

1. Stop admission: under the table lock mark the scope closed, so a later `spawn` traps with the existing message "spawn in a
   scope that has ended". (Only the owning task can spawn into its scope, because a `Scope` cannot be captured, so this guards
   the invariant rather than a real race.)
2. `wakeSignal(w)` of the scope's token, then `cancelNotify(w)`: every descendant blocked in a checkpoint wakes with
   `Cancelled`; descendants blocked in a network wait wake through the eventfd as today.
3. Drain the table like `drain(tab)` does today: for every unclaimed entry, claim it and `taskJoin` the thread. The result of
   a normal end is dropped (`transitDrop`). A child that trapped contributes a secondary failure (section 5). `monFree(res)`.
4. `wakeClose(w)`, `monFree(tab)`, `scopePop(tab)`.

Because each step uses the ledger code that normal scope exit uses, `finish` and the unwind share `drain`; the only difference
is that the unwind does not trap at the end. The thread then continues with `heapRetire`.

Nested scopes inside children are handled by the children themselves: each child that is cancelled and returns normally runs
its own `finish`; a child that traps while being cancelled runs this same unwind for its scopes first. Order is therefore
leaves-first, bounded by the nesting depth (at most `ORIN_PLATFORM_WAKE_DEPTH` + 1 levels).

Normal scope exit (`finish`) is unchanged: it waits for every task of the scope and does not cancel siblings of a failed child
(that is a language decision, see section 8).

#### 4.6.1 Where the unwind code lives

The unwind needs the ledger layout (`LG_*`, entry stride), which is defined and tested in `library/std/task.or`. Duplicating it in
`runtime/core` would give two sources of truth. Proposal:

- `library/std/task.or` defines `unwindScopes()` (shares `drain`, `cancelNotify`, `registryAdd/Remove`).
- `runtime/core/task.or` stores one function address, `unwindFn`, in the shared block. `begin()` registers it on first use
  (`taskSetUnwind(fnAddr(unwindEntry))`, idempotent, under the runtime lock). `trapAt` calls it through the same `fnAddr`
  mechanism that starts tasks (`E_TASK_MAIN` today). A program that never opens a scope never registers it, and `trapAt`
  sees 0 and skips the step.
- The alternative (the unwind written in `runtime/core` against a documented ledger layout) is smaller at the call site but
  couples the runtime to a std data layout; it is rejected unless the callback proves too heavy (section 8).

### 4.7 Split between `runtime/core` and `library/std/task.or`

| Piece | Where | Reason |
|---|---|---|
| Registry table (entries, growth, `cancelNotify` scan) | `library/std/task.or` | Policy and layout next to the waits (ADR-0030). Provable parts (matching, table updates) can go in `task_internal.or` as pure functions with tests. |
| Registry singleton handle (one shared word, lazy create) | `runtime/core/task.or` | Process-wide state; std modules have no mutable globals. |
| `H_SCOPES` stack, `scopePush`, `scopePop` | `runtime/core/task.or` (heap block word) | Per-thread state that the trap path must read without std. |
| `unwindFn` slot and the call in `trapAt` | `runtime/core/task.or` | The trap path is runtime code. |
| `UNWINDING` guard in the task record | `runtime/core/task.or` | Same record as `trapped`. |
| Waits as checkpoints, `Cancelled`, `cancelNotify` callers, `unwindScopes`, `begin`/`finish` changes | `library/std/task.or` | Library behavior. |
| Wake sources, monitors, thread join | L0, unchanged | Mechanism already sufficient. |

## 5. Failure reporting (primary and secondary)

- **Primary failure**: the trap that started the unwind. Its message is stored first (section 4.6), so the joiner of the
  trapping task sees `task panicked: <primary>`, exactly as today.
- **Secondary failures**: a child ended on a trap while the unwind joined it. The unwind records the first secondary message
  and a count in the task record (the record has 480 message bytes; the layout adds `secondary@..` and `count@..` words and the
  message becomes `<primary>` + `; and N more task(s) failed during cleanup: <first>` cut at 479 bytes, primary kept whole
  when possible). The joiner sees one trap message whose first clause is the primary failure. Order is the unwind's order
  (newest scope, entry index), so output is deterministic for a given program and schedule of ends.
- **A trap during cleanup**: a trap raised by the unwind code on the trapping thread itself (for example a bug, or a resource
  denial while joining) finds `UNWINDING` set. It does not re-enter: it records itself as a secondary failure if the message
  slot allows and ends the thread with `thread_exit`, leaving the remaining scopes unjoined, and `heapRetire` still runs. This
  case is a defect, not a supported path: the runtime test suite asserts the unwind code cannot trap on valid state, and
  the fallback is documented as best effort. A trap inside a *child* during cancellation is the ordinary secondary case above.
- **A join that propagates a child trap** into a parent with other live children is the same path: `join()` traps the parent
  (`task panicked: ...` becomes the primary), then the parent's unwind cancels and joins the other children.
- **The main thread**: unchanged. A trap on the main thread prints and exits 101; the process exit ends every thread. C2 does
  not add an unwind there (nothing observes it).

## 6. Impact on L0, the seed snapshot and other layers

- **L0 (ADR-0054)**: no new function and no change to the existing ones. The registry uses monitors and `wake_check`, both
  present. The L0 budget (364 lines left, 127 spent by C3) is untouched, and so are the CBMC harnesses and ACSL contracts.
  The explicit non-goal: no callback from L0 into Orin when a source is signalled (an unsafe re-entry into the managed
  heap from an arbitrary signalling thread).
- **Seed snapshot `bootstrap/seed/runtime/`**: this is the part Henry decides. `std:task` is compiled into the compiler itself
  (parallel compilation, ADR-0049), so stage 0 and stage 1 link the frozen C runtime. Any new runtime entry point that
  `std:task` calls on every path (`waitRegistry`, `scopePush`, `scopePop`, `taskSetUnwind`) must also exist in the snapshot, as
  an "additive exception" appended verbatim from `runtime/core/` (precedent: `orin_rt_task_watch` and `orin_mon_wait_until`
  for C1, and the four `orin_fs_*` functions for C4 in #59). That is an edit to a frozen directory, so it needs explicit
  approval before the implementation PR. The trap-path change itself (`trapAt`) lives in Orin runtime code and does not touch the
  snapshot.
- **Compiler**: four new task operations in `compiler/hir/taskops.or` (and their wrappers in `mir/rt.or` and both backends)
  if the runtime functions are reached through the `BTask` table, like `wakeOpen`. If the shared-block word and the heap-block word
  are reached with the existing `load64`/`store64` of `std:core`, no new operation is needed. The implementation session
  picks the second form unless it breaks the contract checks.
- **Reference and docs**: `docs/reference/08-concurrency.md` loses its gap "cancellation of channel waits and of a scope by a
  trapped task"; `docs/concurrency.md`, `docs/std.md`, ADR-0017 Addendum E (this design, accepted) and the freeze table are
  updated.
- **Performance**: a task without a bound token (`wakeBound() == 0`) pays one load and a compare per wait, no registry access. A
  cancellable task pays two uncontended lock operations on `R` per blocking wait (register, deregister). The registry is not
  touched on the fast path of a send or receive that does not block: register only on the path that is about to
  `monWait`.

## 7. Test plan

All new tests are deterministic where the logic is deterministic, and stress-based under sanitizers for the races. They extend
`tests/concurrency/` and run from `tools/test_concurrency.sh` (plain, ASan and UBSan, ThreadSanitizer, each on the C and LLVM
backends, as the existing cancel tests do).

**Unit and conformance**
1. Registry (pure functions in `task_internal.or`): add, remove, scan, growth, duplicate remove; tests in `tests/std/`.
2. `Cancelled` surface: each call of the table in section 4.4 returns `Err(Cancelled)` after `cancel()`, before, during and
   after the wait starts; messages and `taskErrorMessage`; API snapshot updated.
3. A value already queued is returned even when the token is set; a closed and drained channel reports `Closed`, not
   `Cancelled`, when both hold (the order is fixed and documented).
4. A task without a token is unchanged (byte-identical behavior on the existing concurrency suite).

**Trap-path cases (acceptance of the roadmap)**
5. Parent task traps in a scope body with children blocked on an empty channel, a full channel, `joinUntil`, `select`, `sleep`:
   all children end with `Cancelled`, the parent's joiner sees the primary message, registries return to baseline.
6. Trap before the scope body returns; trap after the last `spawn`; trap with zero children.
7. Nested: grandchild blocked, child in a `scope`, parent traps. Leaves end first.
8. `join()` propagates a child trap into a parent with two other live children; the other children end, the failure reads
   `task panicked: <child message>`.
9. Secondary failures: a child traps on cancellation; the report has the primary first and the count and first secondary
   second; ordering is stable over 1000 runs.
10. Duplicate join and join after cancellation; `joinUntil` timeout then `join` (the join right is not consumed).
11. A non-cooperating CPU child: the unwind does not finish within a bound. The test uses an external watchdog and asserts the
    documented limit (no cleanup guarantee), as required by R4.

**Races (ThreadSanitizer and stress)**
12. Cancel before, between and after `registryAdd`, the check and `monWait`, forced with yield points in a test build; assert
    no waiter parks after a cancel that preceded its check (the lost-wakeup property of section 4.3).
13. `cancelNotify` against `registryRemove` and monitor free: 10^5 iterations of wait/return/free on one thread while another
    cancels; TSan reports no race and ASan no use after free (the property of holding `R` across the scan).
14. Close, drain and cancel together on one channel with many senders and receivers; token and buffered-message accounting
    returns to baseline (`transitDrop` counts equal).
15. Lock-order check: a debug build records `R` and channel acquisition order per thread and asserts registry-before-channel
    everywhere (a failing assertion lists the two sites).
16. Storm: the existing `cancel_storm.or` extended with channel waits, plus a trap storm (hundreds of tasks trapping with
    nested scopes) with thread, monitor, token and wake-source counts checked at quiescence.

**Formal and review gates**: the registry's add/remove/scan are pure state machines checked with the existing Orin contracts
(`orin verify --contracts`); L0 CBMC is unaffected. The runtime pieces stay `TESTED_ONLY`, as the roadmap already requires. The
implementation PRs follow the roadmap's boundaries: (a) registry and checkpoint waits with `Cancelled`; (b) scope stack and
unwind; (c) failure reporting and docs.

## 8. Decisions for the project owner

1. **Seed snapshot.** Approve the additive exception (new runtime functions appended verbatim to `bootstrap/seed/runtime/`), or
   require that the implementation uses only existing memory operations (`load64`/`store64` on the shared and heap blocks) so
   that the snapshot is untouched. The design works either way; the second is smaller to review but ties the layout to
   word offsets.
2. **`recv()` and `join()`** cannot report `Cancelled` with their current types (`Option<T>`, `T`). Choices: keep them
   non-interruptible and say so (the checkpoint calls are `recvUntil`, `selectUntil`, `joinUntil`, `sleep`); change `recv()` to a
   `Result` before the freeze (ADR-0048 uses `Result` for the net equivalents); or let a cancelled `recv()` trap. The design
   proposes the first as the default and the second as the freeze-time change.
3. **Sibling cancellation on a child trap.** This design does not cancel siblings when a child traps while its parent is still
   running (the parent decides at `join`). If the project wants "first failure cancels the scope" (structured-concurrency
   style), it is a one-line policy in `drain`, but it changes observable behavior of existing programs and needs an ADR line.
4. **Unwind callback versus runtime-side unwind** (section 4.6.1).
5. **Message format** for secondary failures (section 5).

## 9. Out of scope

Reclaiming a trapped task's heap objects (roadmap section 4, R3/R4 route); public recovery of a trap; forced thread
cancellation; compiler-inserted safepoints for CPU loops; DNS and filesystem cancellation (ADR-0017 Addendum D keeps its
stated limits); a scheduler (roadmap section 5).
