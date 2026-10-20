/* L0 family "process": arguments and standard input over orbit:process/v1 (host-abi.md section 4c). The generated C includes this
 * file when the program's manifest lists process/v1 (compiler/analysis/orbit.or), so a program that never reads its arguments or
 * stdin has no such import. The core (orin_platform_orbit.c) holds the refusing stubs this file replaces.
 * No getenv: nothing in std reads the environment, and importing env_get would make every program that starts a task need the
 * process capability (the runtime reads ORIN_THREADS; there is one thread here). */
#ifndef ORBIT_PROC_H
#define ORBIT_PROC_H
#include "orbit_abi.h"

ORBIT_IMPORT("orbit:process/v1", "arg_count") int32_t orbit_arg_count(void);
ORBIT_IMPORT("orbit:process/v1", "arg") int64_t orbit_arg(int32_t i, int64_t p, int64_t cap);
ORBIT_IMPORT("orbit:process/v1", "stdin_read") int64_t orbit_stdin_read(int64_t p, int64_t cap, int64_t timeout_ms);

static int g_argc = -1; /* -1: the host has not been asked yet */
static char **g_argv;

static void args_load(void) {
    int32_t n = orbit_arg_count();
    g_argc = 0;
    g_argv = (char **)orin_platform_alloc(((size_t)(n > 0 ? n : 0) + 1) * sizeof(char *));
    for (int32_t i = 0; g_argv && i < n; i++) {
        char *a = NULL;
        for (size_t cap = 128; cap <= (1u << 20); cap *= 2) { /* the host gives the length only with the value: grow until it fits */
            if (!(a = (char *)orin_platform_alloc(cap))) break;
            int64_t r = orbit_arg(i, ORBIT_PTR(a), (int64_t)cap - 1);
            if (r >= 0) {
                a[r] = 0;
                break;
            }
            orin_platform_free(a), a = NULL;
            if (r != -5) break; /* ERR_TOO_LARGE: try a bigger buffer */
        }
        if (!a) break;
        g_argv[g_argc++] = a;
    }
}
int orin_platform_arg_count(void) {
    if (g_argc < 0) args_load();
    return g_argc;
}
const char *orin_platform_arg(int i) { return g_argv[i]; }

/* stdin: buffered, filled by stdin_read (waits without bound; 0 = end of input; a status, such as denied, also ends the input). */
static char g_in[4096];
static size_t g_in_pos, g_in_len;
void orin_orbit_flush_line(void); /* orin_platform_orbit.c */
static int in_fill(void) {
    orin_orbit_flush_line(); /* a prompt without a newline is shown before the program waits */
    int64_t r = orbit_stdin_read(ORBIT_PTR(g_in), sizeof g_in, -1);
    g_in_pos = 0, g_in_len = r > 0 ? (size_t)r : 0;
    return r > 0;
}
size_t orin_platform_stdin_read(char *buf, size_t n) {
    size_t got = 0;
    while (got < n && (g_in_pos < g_in_len || in_fill())) {
        size_t k = g_in_len - g_in_pos < n - got ? g_in_len - g_in_pos : n - got;
        orin_platform_mem_copy(buf + got, g_in + g_in_pos, k);
        got += k, g_in_pos += k;
    }
    return got;
}
int orin_platform_stdin_getc(void) { return g_in_pos < g_in_len || in_fill() ? (unsigned char)g_in[g_in_pos++] : -1; }
#endif
