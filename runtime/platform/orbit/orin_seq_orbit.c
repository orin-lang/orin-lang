/* wasm64-orbit: ONE WebAssembly thread runs every task, one at a time, to completion (ADR-0055 decision 4), "run-on-block":
 * thread_create only queues the task; it runs when a context would block (join of it, monitor wait) or when main returns.
 * The runtime's per-task state is __thread data, which the build (-D__thread=...section("orin_tls")) gathers into one block;
 * a switch saves that block, installs its pristine image and restores it afterwards. wasm32-orbit has real threads instead
 * (orin_threads_orbit.c). */
#include "../orin_platform.h"

#include "include/orin_sync.h"

#ifndef ORBIT_THREADS

uint64_t orin_platform_cpu_count(void) { return 1; }

enum { THR_MAX = 1 << 16, MON_MAX = 1 << 14, TH_FREE = 0, TH_QUEUED, TH_RUNNING, TH_DONE };
typedef struct {
    void (*entry)(void *);
    void *arg;
    uint32_t gen, prev, next, st; /* prev / next: the run queue; next also chains the free slots (index + 1, 0 = none) */
} Thr;
static Thr *g_thr;
static uint32_t g_thr_cap, g_thr_hi, g_thr_free, g_q_head, g_q_tail, g_cur; /* g_cur: the running task (index + 1), 0 = main */
static uint64_t g_tid = 1, g_tid_last = 1;                                  /* thread id of the running context */


uint64_t orin_platform_thread_id(void) { return g_tid; }

/* The runtime's per-task state: every __thread object is built into the section orin_tls (see the header comment). */
extern char __start_orin_tls[] __attribute__((weak)), __stop_orin_tls[] __attribute__((weak));
extern char orin_heap[] __attribute__((weak)); /* the heap block of orin_runtime.c: a __thread object, must be inside the section */
static char *g_tls_pristine;
static size_t tls_size(void) { return (size_t)(__stop_orin_tls - __start_orin_tls); }
void orin_orbit_main_begin(void) {
    /* the block is still pristine here */
    if (tls_size() && (g_tls_pristine = (char *)orin_platform_alloc(tls_size()))) orin_platform_mem_copy(g_tls_pristine, __start_orin_tls, tls_size());
}

__attribute__((noreturn)) static void deadlock(void) {
    orin_orbit_fatal("deadlock: a task waits for a notification that no queued task can send (tasks run one at a time, to completion)", "", 134); /* status 134, as natively (Orbit counts -1 as a trap) */
}

static Thr *thr_ref(int64_t h) {
    uint32_t i = orbit_slot_index(h);
    return h > 0 && i < g_thr_hi && g_thr[i].st != TH_FREE && g_thr[i].gen == orbit_slot_gen(h) ? &g_thr[i] : NULL;
}
static void q_remove(uint32_t i) {
    Thr *t = &g_thr[i];
    if (t->prev) g_thr[t->prev - 1].next = t->next;
    else g_q_head = t->next;
    if (t->next) g_thr[t->next - 1].prev = t->prev;
    else g_q_tail = t->prev;
}

/* Runs queued task i to completion on the current stack, in a fresh copy of the runtime's per-task state. */
static void run_task(uint32_t i) {
    size_t n = tls_size();
    char *saved = n ? (char *)orin_platform_alloc(n) : NULL;
    if (n && (!saved || !g_tls_pristine)) orin_orbit_fatal("out of memory", "", 134);
    q_remove(i);
    void (*entry)(void *) = g_thr[i].entry;
    void *arg = g_thr[i].arg;
    g_thr[i].st = TH_RUNNING;
    uint32_t cur = g_cur;
    uint64_t tid = g_tid;
    int64_t wake = orin_platform_wake_bind(0); /* a new task starts with no wake source bound */
    orin_platform_mem_copy(saved, __start_orin_tls, n);
    orin_platform_mem_copy(__start_orin_tls, g_tls_pristine, n);
    g_cur = i + 1, g_tid = ++g_tid_last;
    entry(arg);
    orin_platform_mem_copy(__start_orin_tls, saved, n);
    orin_platform_free(saved);
    g_cur = cur, g_tid = tid;
    orin_platform_wake_bind(wake);
    g_thr[i].st = TH_DONE;
}
void orin_orbit_main_end(void) {
    while (g_q_head) run_task(g_q_head - 1);
}

int64_t orin_platform_thread_create(void (*entry)(void *), void *arg) {
    uint32_t i;
    if (orin_heap && (orin_heap < __start_orin_tls || orin_heap >= __stop_orin_tls)) /* built without -D__thread=... */
        orin_orbit_fatal("the runtime was built without -D__thread=... (section orin_tls): tasks would share their state", "", 134);
    if (g_thr_free) {
        i = g_thr_free - 1;
        g_thr_free = g_thr[i].next;
    } else {
        if (g_thr_hi == g_thr_cap) {
            uint32_t nc = g_thr_cap ? g_thr_cap * 2 : 64;
            Thr *p = g_thr_cap == THR_MAX ? NULL : (Thr *)orin_platform_realloc(g_thr, nc * sizeof(Thr));
            if (!p) return 0;
            orin_platform_mem_set(p + g_thr_cap, 0, (nc - g_thr_cap) * sizeof(Thr));
            g_thr = p, g_thr_cap = nc;
        }
        i = g_thr_hi++;
    }
    Thr *t = &g_thr[i];
    t->gen++, t->entry = entry, t->arg = arg, t->st = TH_QUEUED, t->prev = g_q_tail, t->next = 0;
    if (g_q_tail) g_thr[g_q_tail - 1].next = i + 1;
    else g_q_head = i + 1;
    g_q_tail = i + 1;
    return orbit_slot_handle(t->gen, i);
}
int orin_platform_thread_join(int64_t h, void **arg) {
    Thr *t = thr_ref(h);
    if (!t) return ORIN_PLATFORM_EINVAL;
    uint32_t i = (uint32_t)(t - g_thr);
    if (t->st == TH_QUEUED) run_task(i);
    else if (t->st == TH_RUNNING) deadlock(); /* it waits (below this call on the stack) for the task that joins it */
    t = &g_thr[i]; /* the table may have grown */
    *arg = t->arg;
    t->st = TH_FREE, t->next = g_thr_free, g_thr_free = i + 1;
    return 0;
}
/* A task trapped (the runtime has recorded its message): WebAssembly cannot unwind to the join, so the module ends. */
void orin_platform_thread_exit(void) {
    const char *p = g_cur ? (const char *)g_thr[g_cur - 1].arg : NULL; /* RtTask: tok, trapped, done_mon (u64 each), msg[481] (orin_runtime.c, task.or) */
    orin_orbit_fatal("a task trapped: ", p && *(const uint64_t *)(p + 8) == 1 ? p + 24 : "(no message)", 101); /* the instance ends: see ADR-0055 */
}

typedef struct {
    uint64_t *w;
    size_t n;
    uint64_t owner;
    uint32_t gen;
    int live, locked, nwait;
} Mon;
static Mon g_mon[MON_MAX];
static uint32_t g_mon_hi, g_mon_free[MON_MAX], g_mon_nfree;

static Mon *mon_ref(int64_t h) {
    uint32_t i = orbit_slot_index(h);
    return h > 0 && i < g_mon_hi && g_mon[i].live && g_mon[i].gen == orbit_slot_gen(h) ? &g_mon[i] : NULL;
}
static Mon *mon_held(int64_t h) { /* the monitor, locked by the running context */
    Mon *m = mon_ref(h);
    return m && m->locked && m->owner == g_tid ? m : NULL;
}

int64_t orin_platform_monitor_new(size_t nwords) {
    if (nwords > (size_t)-1 / sizeof(uint64_t)) return 0; /* the byte count must fit a 32-bit size_t */
    uint64_t *w = (uint64_t *)orin_platform_alloc(nwords * sizeof(uint64_t));
    if (!w) return 0;
    orin_platform_mem_set(w, 0, nwords * sizeof(uint64_t));
    uint32_t i;
    if (g_mon_nfree) i = g_mon_free[--g_mon_nfree];
    else if (g_mon_hi < MON_MAX) i = g_mon_hi++;
    else {
        orin_platform_free(w);
        return 0;
    }
    Mon *m = &g_mon[i];
    m->gen++;
    m->w = w, m->n = nwords, m->live = 1, m->locked = 0, m->nwait = 0;
    return orbit_slot_handle(m->gen, i);
}
int orin_platform_monitor_free(int64_t h) {
    Mon *m = mon_ref(h);
    if (!m) return ORIN_PLATFORM_EINVAL;
    if (m->locked || m->nwait) return ORIN_PLATFORM_EBUSY;
    orin_platform_free(m->w);
    m->w = NULL, m->live = 0;
    g_mon_free[g_mon_nfree++] = (uint32_t)(m - g_mon);
    return 0;
}
int orin_platform_monitor_lock(int64_t h) {
    Mon *m = mon_ref(h);
    if (!m) return ORIN_PLATFORM_EINVAL;
    if (m->locked && m->owner == g_tid) return ORIN_PLATFORM_EDEADLK;
    if (m->locked) deadlock(); /* held by a context suspended below this one on the stack: it cannot run before we end */
    m->locked = 1, m->owner = g_tid;
    return 0;
}
int orin_platform_monitor_unlock(int64_t h) {
    Mon *m = mon_held(h);
    if (!m) return ORIN_PLATFORM_EINVAL;
    m->locked = 0;
    return 0;
}
/* The caller would sleep until another task notifies: with one thread, run the next queued task to completion instead (the
 * monitor is released meanwhile) and let the caller re-check its condition, which the contract allows (spurious wake-up). */
static void block_on(Mon *m) {
    if (!g_q_head) deadlock();
    m->locked = 0, m->nwait++;
    run_task(g_q_head - 1);
    m->nwait--;
    if (m->locked) deadlock(); /* a task ended holding the monitor */
    m->locked = 1, m->owner = g_tid;
}
int orin_platform_monitor_wait(int64_t h, int cond) {
    Mon *m = mon_held(h);
    if (!m || (cond != 0 && cond != 1)) return ORIN_PLATFORM_EINVAL;
    block_on(m);
    return 0;
}
int orin_platform_monitor_wait_until(int64_t h, int cond, int64_t deadline_ms) {
    Mon *m = mon_held(h);
    if (!m || (cond != 0 && cond != 1) || deadline_ms < 0) return ORIN_PLATFORM_EINVAL;
    if (!g_q_head) return ORIN_PLATFORM_WAIT_TIMEOUT; /* nobody can notify, so the wait ends at the deadline (no sleeping here) */
    block_on(m);
    return 0;
}
int orin_platform_monitor_notify(int64_t h, int cond, int all) {
    (void)all;
    return !mon_held(h) || (cond != 0 && cond != 1) ? ORIN_PLATFORM_EINVAL : 0; /* a waiter re-checks after the task it ran */
}
int orin_platform_monitor_get(int64_t h, size_t i, uint64_t *out) {
    Mon *m = mon_held(h);
    if (!m || i >= m->n) return ORIN_PLATFORM_EINVAL;
    *out = m->w[i];
    return 0;
}
int orin_platform_monitor_set(int64_t h, size_t i, uint64_t v) {
    Mon *m = mon_held(h);
    if (!m || i >= m->n) return ORIN_PLATFORM_EINVAL;
    m->w[i] = v;
    return 0;
}
int orin_platform_monitor_grow(int64_t h, size_t nwords) {
    Mon *m = mon_held(h);
    if (!m || nwords < m->n) return ORIN_PLATFORM_EINVAL;
    if (nwords > (size_t)-1 / sizeof(uint64_t)) return ORIN_PLATFORM_ENOMEM;
    uint64_t *w = (uint64_t *)orin_platform_realloc(m->w, nwords * sizeof(uint64_t));
    if (!w) return ORIN_PLATFORM_ENOMEM;
    orin_platform_mem_set(w + m->n, 0, (nwords - m->n) * sizeof(uint64_t));
    m->w = w, m->n = nwords;
    return 0;
}
void orin_platform_runtime_lock(void) {}
void orin_platform_runtime_unlock(void) {}
#endif
