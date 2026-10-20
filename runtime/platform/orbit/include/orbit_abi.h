/* The Orbit host ABI as the WebAssembly L0 uses it (ADR-0055; orbit docs/host-abi.md). Shared by the core
 * (orin_platform_orbit.c) and by the capability families (orbit_proc.h, orbit_fs.h, orbit_net.h). */
#ifndef ORBIT_ABI_H
#define ORBIT_ABI_H
#include "../../orin_platform.h"

#define ORBIT_IMPORT(m, n) __attribute__((import_module(m), import_name(n)))
#define ORBIT_PTR(x) ((int64_t)(uintptr_t)(x)) /* pointers and lengths cross the ABI as i64, zero-extended on wasm32 */
#define ORBIT_WEAK __attribute__((weak))     /* the core's refusing stub of a family function: the family's definition replaces it */
#endif
