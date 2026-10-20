/* wasm32-orbit: real threads for the WebAssembly L0 (ADR-0055 decision 9), in the wasi-threads model.
 *
 * The module imports its memory as SHARED memory (wasm-ld --shared-memory --import-memory) and one function to start a thread:
 * `orbit:thread/v1 spawn(arg: i64) -> i64` (the thread id > 0, or a negative status). The host instantiates the same module again
 * on the same memory in a new OS thread and calls the export `orin_thread_start(tid, arg)`; this file passes a pointer to a start
 * record as `arg`. Every name the host interface has is in the next block. Exit or trap in any thread ends all threads
 * (the host's side of the contract); blocking is done here with memory.atomic.wait32 / notify, no host call.
 *
 * wasm-ld's `__wasm_init_memory` (the start function) initialises the data once, by the first instance (an atomic flag the other
 * instances wait on), and gives that instance its thread-local block in static memory. A new thread gets its own stack and its own
 * block (`__wasm_init_tls`), both allocated by the CREATING thread, because the new instance starts with the stack pointer of the
 * main thread and may not touch the C stack before it has its own.
 *
 * A task that traps cannot unwind to its entry (no exceptions in the module): thread_exit publishes "done" for the join and then
 * PARKS the thread for good (see thread_exit). */
#include "../orin_platform.h"

#include "include/orin_sync.h"
#include "include/stdlib.h"
#include "include/string.h"

#ifdef ORBIT_THREADS
#define ORBIT_IMPORT(m, n) __attribute__((import_module(m), import_name(n)))
#define ORBIT_THREAD_START "orin_thread_start" /* the export the host calls in the new instance */
ORBIT_IMPORT("orbit:thread/v1", "spawn") int64_t orbit_thread_spawn(int64_t arg);
ORBIT_IMPORT("orbit:clock/v1", "monotonic_nanos") int64_t orbit_clock_monotonic_nanos(void);

enum { STACK = 1 << 20, THR_MAX = 1 << 16, MON_MAX = 1 << 14, CPUS = 4 };

typedef struct {
    void (*entry)(void *);
    void *arg;
    char *stack, *tls_raw, *tls; /* allocated by the creator, freed by the joiner (not the stack and block of a parked thread) */
    uint64_t tid;
    uint32_t done, parked;
} Rec;
typedef struct {
    Rec *r;
    uint32_t gen, st, next; /* st: 0 free, 1 live, 2 being joined; next chains the free slots (index + 1) */
} Slot;
static Slot *g_thr;
static uint32_t g_thr_cap, g_thr_hi, g_thr_free, g_tab_lock; /* the lock guards the thread table and the monitor table */
static uint64_t g_tid_next = 1;
static uint32_t g_park; /* never written, never notified: parked threads sleep on it */
static __thread uint64_t t_tid = 1; /* the main thread is 1 */
static __thread Rec *t_rec;

extern void __wasm_init_tls(void *); /* synthesised by wasm-ld */

uint64_t orin_platform_thread_id(void) { return t_tid; }
uint64_t orin_platform_cpu_count(void) { return CPUS; }
void orin_orbit_main_begin(void) {}
void orin_orbit_main_end(void) {}

static void thread_done(Rec *r) {
    __atomic_store_n(&r->done, 1, __ATOMIC_SEQ_CST);
    orbit_wake(&r->done, 0xffffffffu);
}
__attribute__((noinline)) static void thread_main(Rec *r) {
    __wasm_init_tls(r->tls);
    t_rec = r, t_tid = r->tid;
    r->entry(r->arg);
    thread_done(r);
}
/* The first function of a new instance: set the stack pointer to the stack the creator allocated, before any C frame exists. */
__attribute__((export_name(ORBIT_THREAD_START), noinline)) void orin_thread_start(int64_t tid, int64_t arg) {
    Rec *r = (Rec *)(uintptr_t)arg;
    (void)tid;
    __asm__ volatile(".globaltype __stack_pointer, i32\n\tlocal.get %0\n\tglobal.set __stack_pointer" ::"r"(r->stack + STACK));
    thread_main(r);
}

static Slot *thr_ref(int64_t h) {
    uint32_t i = orbit_slot_index(h);
    return h > 0 && i < g_thr_hi && g_thr[i].st && g_thr[i].gen == orbit_slot_gen(h) ? &g_thr[i] : NULL;
}

int64_t orin_platform_thread_create(void (*entry)(void *), void *arg) {
    size_t tsz = (size_t)__builtin_wasm_tls_size(), al = (size_t)__builtin_wasm_tls_align();
    Rec *r = (Rec *)calloc(1, sizeof(Rec));
    if (!r) return 0;
    r->entry = entry, r->arg = arg;
    r->stack = (char *)malloc(STACK);
    r->tls_raw = (char *)malloc(tsz + al);
    if (!r->stack || !r->tls_raw) goto fail;
    r->tls = (char *)(((uintptr_t)r->tls_raw + al - 1) & ~(uintptr_t)(al - 1));
    r->tid = __atomic_add_fetch(&g_tid_next, 1, __ATOMIC_SEQ_CST);
    orbit_lock(&g_tab_lock);
    uint32_t i;
    if (g_thr_free) {
        i = g_thr_free - 1;
        g_thr_free = g_thr[i].next;
    } else {
        if (g_thr_hi == g_thr_cap) {
            uint32_t nc = g_thr_cap ? g_thr_cap * 2 : 64;
            Slot *p = g_thr_cap == THR_MAX ? NULL : (Slot *)realloc(g_thr, nc * sizeof(Slot));
            if (!p) {
                orbit_unlock(&g_tab_lock);
                goto fail;
            }
            memset(p + g_thr_cap, 0, (nc - g_thr_cap) * sizeof(Slot));
            g_thr = p, g_thr_cap = nc;
        }
        i = g_thr_hi++;
    }
    g_thr[i].gen++, g_thr[i].st = 1, g_thr[i].r = r;
    int64_t h = orbit_slot_handle(g_thr[i].gen, i);
    orbit_unlock(&g_tab_lock);
    if (orbit_thread_spawn((int64_t)(uintptr_t)r) > 0) return h;
    orbit_lock(&g_tab_lock);
    g_thr[i].st = 0, g_thr[i].next = g_thr_free, g_thr_free = i + 1;
    orbit_unlock(&g_tab_lock);
fail:
    free(r->stack);
    free(r->tls_raw);
    free(r);
    return 0;
}

int orin_platform_thread_join(int64_t h, void **arg) {
    orbit_lock(&g_tab_lock);
    Slot *s = thr_ref(h);
    if (!s || s->st != 1) {
        orbit_unlock(&g_tab_lock);
        return ORIN_PLATFORM_EINVAL;
    }
    s->st = 2;
    Rec *r = s->r;
    uint32_t i = (uint32_t)(s - g_thr);
    orbit_unlock(&g_tab_lock);
    while (!__atomic_load_n(&r->done, __ATOMIC_SEQ_CST)) orbit_wait(&r->done, 0, -1);
    *arg = r->arg;
    orbit_lock(&g_tab_lock);
    g_thr[i].st = 0, g_thr[i].next = g_thr_free, g_thr_free = i + 1;
    orbit_unlock(&g_tab_lock);
    if (!r->parked) { /* a parked thread still stands on its stack and block */
        free(r->stack);
        free(r->tls_raw);
    }
    free(r);
    return 0;
}

typedef struct {
    uint64_t *w;
    size_t n;
    uint64_t owner; /* the holder's thread id, 0 when free; written only by the holder */
    uint32_t lock, seq[2], gen, live, nwait;
} Mon;
static Mon g_mon[MON_MAX];
static uint32_t g_mon_hi, g_mon_free[MON_MAX], g_mon_nfree;

static Mon *mon_ref(int64_t h) {
    uint32_t i = orbit_slot_index(h);
    return h > 0 && i < __atomic_load_n(&g_mon_hi, __ATOMIC_ACQUIRE) && __atomic_load_n(&g_mon[i].live, __ATOMIC_ACQUIRE) &&
                   g_mon[i].gen == orbit_slot_gen(h)
               ? &g_mon[i]
               : NULL;
}
static Mon *mon_held(int64_t h) { /* the monitor, locked by this thread */
    Mon *m = mon_ref(h);
    return m && __atomic_load_n(&m->owner, __ATOMIC_RELAXED) == t_tid ? m : NULL;
}
static void mon_acquire(Mon *m) {
    orbit_lock(&m->lock);
    __atomic_store_n(&m->owner, t_tid, __ATOMIC_RELAXED);
}
static void mon_release(Mon *m) {
    __atomic_store_n(&m->owner, 0, __ATOMIC_RELAXED);
    orbit_unlock(&m->lock);
}

/* A task trapped (the runtime has recorded the message, retired its heap and published the end to a timed join). WebAssembly
 * cannot unwind to the thread entry, and a trap would end ALL threads, so this thread publishes "done" for the join and parks
 * for good: it sleeps on a word nobody notifies. Cost: one parked OS thread, its 1 MiB stack and its thread-local block for the
 * rest of the run (not freed by the join). The host ends parked threads with the module. */
void orin_platform_thread_exit(void) {
    Rec *r = t_rec;
    for (uint32_t i = 0, hi = g_mon_hi; i < hi; i++) /* a panic must not leave a lock held */
        if (g_mon[i].live && g_mon[i].owner == t_tid) mon_release(&g_mon[i]);
    if (!r) orin_orbit_fatal("a trap left a thread that was not started by thread_create", "", 101);
    r->parked = 1;
    thread_done(r);
    for (;;) orbit_wait(&g_park, 0, -1);
}

int64_t orin_platform_monitor_new(size_t nwords) {
    if (nwords > (size_t)-1 / sizeof(uint64_t)) return 0; /* the byte count must fit a 32-bit size_t */
    uint64_t *w = (uint64_t *)calloc(nwords ? nwords : 1, sizeof(uint64_t));
    if (!w) return 0;
    orbit_lock(&g_tab_lock);
    uint32_t i;
    if (g_mon_nfree) i = g_mon_free[--g_mon_nfree];
    else if (g_mon_hi < MON_MAX) i = g_mon_hi;
    else {
        orbit_unlock(&g_tab_lock);
        free(w);
        return 0;
    }
    Mon *m = &g_mon[i];
    m->gen++;
    m->w = w, m->n = nwords, m->lock = 0, m->owner = 0, m->nwait = 0, m->seq[0] = m->seq[1] = 0;
    __atomic_store_n(&m->live, 1, __ATOMIC_RELEASE);
    if (i == g_mon_hi) __atomic_store_n(&g_mon_hi, i + 1, __ATOMIC_RELEASE);
    orbit_unlock(&g_tab_lock);
    return orbit_slot_handle(m->gen, i);
}
int orin_platform_monitor_free(int64_t h) {
    orbit_lock(&g_tab_lock);
    Mon *m = mon_ref(h);
    int rc = !m ? ORIN_PLATFORM_EINVAL : __atomic_load_n(&m->lock, __ATOMIC_SEQ_CST) || __atomic_load_n(&m->nwait, __ATOMIC_SEQ_CST) ? ORIN_PLATFORM_EBUSY : 0;
    if (!rc) {
        free(m->w);
        m->w = NULL;
        __atomic_store_n(&m->live, 0, __ATOMIC_RELEASE);
        g_mon_free[g_mon_nfree++] = (uint32_t)(m - g_mon);
    }
    orbit_unlock(&g_tab_lock);
    return rc;
}
int orin_platform_monitor_lock(int64_t h) {
    Mon *m = mon_ref(h);
    if (!m) return ORIN_PLATFORM_EINVAL;
    if (__atomic_load_n(&m->owner, __ATOMIC_RELAXED) == t_tid) return ORIN_PLATFORM_EDEADLK;
    mon_acquire(m);
    return 0;
}
int orin_platform_monitor_unlock(int64_t h) {
    Mon *m = mon_held(h);
    if (!m) return ORIN_PLATFORM_EINVAL;
    mon_release(m);
    return 0;
}
/* Sleep on queue `cond` until its counter moves (a notify) or the timeout: the counter is read while the monitor is held, so a
 * notify between the unlock and the sleep makes wait32 return at once. */
static int mon_sleep(Mon *m, int cond, int64_t timeout_ns) {
    uint32_t seen = __atomic_load_n(&m->seq[cond], __ATOMIC_SEQ_CST);
    __atomic_add_fetch(&m->nwait, 1, __ATOMIC_SEQ_CST);
    mon_release(m);
    int r = orbit_wait(&m->seq[cond], seen, timeout_ns);
    mon_acquire(m);
    __atomic_sub_fetch(&m->nwait, 1, __ATOMIC_SEQ_CST);
    return r;
}
int orin_platform_monitor_wait(int64_t h, int cond) {
    Mon *m = mon_held(h);
    if (!m || (cond != 0 && cond != 1)) return ORIN_PLATFORM_EINVAL;
    mon_sleep(m, cond, -1);
    return 0;
}
int orin_platform_monitor_wait_until(int64_t h, int cond, int64_t deadline_ms) {
    Mon *m = mon_held(h);
    if (!m || (cond != 0 && cond != 1) || deadline_ms < 0) return ORIN_PLATFORM_EINVAL;
    int64_t left = -1; /* nanoseconds; -1: forever */
    if (deadline_ms <= INT64_MAX / 1000000) {
        left = deadline_ms * 1000000 - orbit_clock_monotonic_nanos();
        if (left <= 0) return ORIN_PLATFORM_WAIT_TIMEOUT; /* passed already: no sleep */
    }
    return mon_sleep(m, cond, left) == 2 ? ORIN_PLATFORM_WAIT_TIMEOUT : 0;
}
int orin_platform_monitor_notify(int64_t h, int cond, int all) {
    Mon *m = mon_held(h);
    if (!m || (cond != 0 && cond != 1)) return ORIN_PLATFORM_EINVAL;
    __atomic_add_fetch(&m->seq[cond], 1, __ATOMIC_SEQ_CST);
    orbit_wake(&m->seq[cond], all ? 0xffffffffu : 1);
    return 0;
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
    uint64_t *w = (uint64_t *)realloc(m->w, nwords * sizeof(uint64_t));
    if (!w) return ORIN_PLATFORM_ENOMEM;
    memset(w + m->n, 0, (nwords - m->n) * sizeof(uint64_t));
    m->w = w, m->n = nwords;
    return 0;
}

static uint32_t g_rt_lock;
void orin_platform_runtime_lock(void) { orbit_lock(&g_rt_lock); }
void orin_platform_runtime_unlock(void) { orbit_unlock(&g_rt_lock); }
#endif
