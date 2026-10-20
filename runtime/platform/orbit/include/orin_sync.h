/* Synchronisation of the WebAssembly L0 (ADR-0055 decision 9): a futex-style mutex over memory.atomic.wait32 / notify.
 * wasm32-orbit is built with -matomics (real threads); wasm64-orbit has one thread, so the lock is nothing. */
#ifndef ORIN_ORBIT_SYNC_H
#define ORIN_ORBIT_SYNC_H
#include <stdint.h>

#ifdef __wasm_atomics__
#define ORBIT_THREADS 1
/* Blocks while *w == expected; timeout_ns < 0 waits forever. Returns 0 woken, 1 value differed, 2 timed out. */
static inline int orbit_wait(uint32_t *w, uint32_t expected, int64_t timeout_ns) {
    return __builtin_wasm_memory_atomic_wait32((int *)w, (int)expected, timeout_ns);
}
static inline void orbit_wake(uint32_t *w, uint32_t n) { __builtin_wasm_memory_atomic_notify((int *)w, n); }
/* Drepper's mutex: 0 free, 1 locked, 2 locked with waiters. */
static inline void orbit_lock(uint32_t *l) {
    uint32_t z = 0;
    if (__atomic_compare_exchange_n(l, &z, 1, 0, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)) return;
    while (__atomic_exchange_n(l, 2, __ATOMIC_ACQUIRE) != 0) orbit_wait(l, 2, -1);
}
static inline void orbit_unlock(uint32_t *l) {
    if (__atomic_exchange_n(l, 0, __ATOMIC_RELEASE) == 2) orbit_wake(l, 1);
}
#else
static inline void orbit_lock(uint32_t *l) { (void)l; }
static inline void orbit_unlock(uint32_t *l) { (void)l; }
#endif

/* handles are generation << 32 | (index + 1) (orin_platform.h) */
static inline int64_t orbit_slot_handle(uint32_t gen, uint32_t i) { return (int64_t)(((uint64_t)gen << 32) | (uint64_t)(i + 1)); }
static inline uint32_t orbit_slot_index(int64_t h) { return (uint32_t)((uint64_t)h & 0xffffffffu) - 1u; }
static inline uint32_t orbit_slot_gen(int64_t h) { return (uint32_t)((uint64_t)h >> 32); }

/* between the L0 files: orin_platform_orbit.c ends the module with a message the test runner knows */
#include <stddef.h>
__attribute__((noreturn)) void orin_orbit_fatal(const char *what, const char *detail, int status);
void orin_orbit_main_begin(void); /* before main: threads / tasks of the build set themselves up */
void orin_orbit_main_end(void);   /* after main returned */
#endif
