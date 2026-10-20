/* Orin L0 platform layer for WebAssembly under the Orbit host ABI v1 (ADR-0055). Contracts: ../orin_platform.h.
 *
 * Target: wasm32 or wasm64 (Memory64), compiled freestanding by clang with the own libc of orin_libc_orbit.c (no WASI function is
 * imported). Every privileged
 * operation goes through an `orbit:<capability>/v1` import (orbit docs/host-abi.md); pointers and lengths are passed as
 * zero-extended i64. A capability the program never reaches is not imported (wasm-ld drops dead imports), and the families of
 * process, file and network access are only linked when the manifest lists them (see below), so the module's import list is
 * exactly what it may ask the host for, and the host's grant decides (deny by default).
 *
 * Differences from the native layer, all fail closed:
 *   stdout / stderr   orbit:log/v1 write, one record per line (stdout = info, stderr = error); an unterminated stdout line waits for
 *                     its newline, and goes out at exit, before a stdin read and before a stderr write;
 *   clock             orbit:clock/v1 (the host may coarsen it);
 *   args, stdin, files, paths, network
 *                     the families orbit_proc.h, orbit_fs.h and orbit_net.h (orbit:process/v1, fs/v1, net/v1). The compiler
 *                     #includes the family of each capability in the program's manifest at the end of the generated C; their
 *                     definitions replace the weak refusing stubs below (no arguments but "main", empty stdin, EPERM). Grants and
 *                     their narrowing are pure (orin_platform_pure.h) and shared with the native layer. There is no environment
 *                     (getenv is NULL: nothing in std reads it, and importing env_get would make every program that starts a task
 *                     need the process capability);
 *   wake sources      L0 only (flags, below). On wasm64 one thread runs everything, so nothing can set a token while a host call blocks: a
 *                     wait checks the bound token first and the host gets no wake handle;
 *   processes (shell) not available (-1), as are mkdir / remove / rename (no L0 entry point);
 *   threads           wasm32-orbit: real threads in the wasi-threads model (orin_threads_orbit.c: import orbit:thread/v1 spawn, shared
 *                     memory, atomics, futex-style locks); wasm64-orbit: one thread runs every task, one at a time, to completion
 *                     (orin_seq_orbit.c, run-on-block); there a wait with no queued task and a trapping task end the module with a
 *                     "wasm64-orbit: " message;
 *   exit              flushes, records the status (export orin_exit_status) and traps: WebAssembly has no unwinding here.
 * Entry point: the export `orin_main` runs the program's main and returns its exit status. */
#include "../orin_platform.h"

#include "../orin_platform_pure.h"
#include "include/orin_sync.h"

#include "orbit_abi.h"
void orin_orbit_flush_line(void);
ORBIT_IMPORT("orbit:log/v1", "write") int32_t orbit_log_write(int32_t level, int64_t ptr, int64_t len);
ORBIT_IMPORT("orbit:clock/v1", "now_unix_nanos") int64_t orbit_clock_now_unix_nanos(void);
ORBIT_IMPORT("orbit:clock/v1", "monotonic_nanos") int64_t orbit_clock_monotonic_nanos(void);
enum { LOG_INFO = 2, LOG_ERROR = 4, LOG_MAX = 16384 };

/* ---------------------------------------------------------------- process */

static char *g_argv0[] = {"main", NULL};
static void (*g_exit_fns[32])(void);
static int g_nexit;
static int32_t g_exit_status = -1; /* -1 until main returned or exit was called */
static uint32_t g_io_lock; /* the line buffers below */
__attribute__((export_name("orin_exit_status"))) int32_t orin_exit_status(void) { return g_exit_status; }

/* ---- the families (orbit_proc.h, orbit_fs.h, orbit_net.h): the generated C includes those its manifest lists and their definitions
 * replace the refusing stubs below. A program without a family therefore has none of its imports, and the host grants nothing it
 * does not use. The stubs behave as a host that grants nothing would: no arguments but "main", empty stdin, no files, no network. */
void orin_platform_init(int argc, char **argv) { (void)argc, (void)argv; }
ORBIT_WEAK int orin_platform_arg_count(void) { return 1; }
ORBIT_WEAK const char *orin_platform_arg(int i) { return g_argv0[i]; }
const char *orin_platform_getenv(const char *name) { /* no environment: see orbit_proc.h */
    (void)name;
    return NULL;
}
int orin_platform_at_exit(void (*fn)(void)) {
    if (g_nexit == 32) return -1;
    g_exit_fns[g_nexit++] = fn;
    return 0;
}
static void run_at_exit(void) {
    while (g_nexit > 0) g_exit_fns[--g_nexit]();
}

void orin_platform_exit(int code) {
    run_at_exit();
    orin_orbit_flush_line();
    g_exit_status = code & 0xff;
    __builtin_trap();
}
void orin_platform_abort(void) { __builtin_trap(); }

int64_t orin_platform_shell(const char *cmd, size_t n) {
    (void)cmd, (void)n;
    orin_orbit_flush_line();
    return -1;
}
int64_t orin_platform_shell_timeout(const char *cmd, size_t n, int64_t seconds) {
    (void)seconds;
    return orin_platform_shell(cmd, n);
}

int main(int argc, char **argv); /* emitted by the compiler */

__attribute__((export_name("orin_main"))) int32_t orin_main(void) {
    orin_orbit_main_begin();
    g_exit_status = main(1, g_argv0);
    orin_orbit_main_end(); /* wasm64: tasks nobody joined still run before the program ends */
    run_at_exit();
    orin_orbit_flush_line();
    return g_exit_status;
}

/* ---------------------------------------------------------------- clocks */

int64_t orin_platform_now_millis(void) { return orbit_clock_now_unix_nanos() / 1000000; }
int64_t orin_platform_monotonic_millis(void) {
    int64_t ns = orbit_clock_monotonic_nanos();
    return ns < 0 ? -1 : ns / 1000000;
}

/* ---------------------------------------------------------------- floating point text */

void orin_orbit_fmt_exp(char *buf, size_t cap, int prec, double x); /* orin_libc_orbit.c */
double orin_orbit_parse_float(const char *s, int is_f32);
void orin_platform_double_to_exp(char *buf, size_t cap, int prec, double x) { orin_orbit_fmt_exp(buf, cap, prec, x); }
double orin_platform_parse_double(const char *s, int is_f32) { return orin_orbit_parse_float(s, is_f32); }

/* ---------------------------------------------------------------- byte I/O: one log record per line */

typedef struct {
    size_t n;
    char b[LOG_MAX];
} LineBuf;
static LineBuf g_out, g_err;

static void line_emit(LineBuf *lb, int level) {
    if (lb->n) orbit_log_write(level, (int64_t)(uintptr_t)lb->b, (int64_t)lb->n);
    lb->n = 0;
}

static void line_put(LineBuf *lb, int level, const char *p, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (p[i] == '\n') {
            orbit_log_write(level, (int64_t)(uintptr_t)lb->b, (int64_t)lb->n); /* an empty line is still a record */
            lb->n = 0;
            continue;
        }
        if (lb->n == LOG_MAX) line_emit(lb, level);
        lb->b[lb->n++] = p[i];
    }
}

static void write_bytes(int stream, const char *p, size_t n, int newline) {
    if (stream == ORIN_PLATFORM_STDOUT) {
        line_put(&g_out, LOG_INFO, p, n);
        if (newline) line_put(&g_out, LOG_INFO, "\n", 1);
    } else {
        line_emit(&g_out, LOG_INFO);
        line_put(&g_err, LOG_ERROR, p, n);
        if (newline) line_put(&g_err, LOG_ERROR, "\n", 1);
        line_emit(&g_err, LOG_ERROR);
    }
}
void orin_platform_write(int stream, const char *p, size_t n) {
    orbit_lock(&g_io_lock);
    write_bytes(stream, p, n, 0);
    orbit_unlock(&g_io_lock);
}
void orin_platform_write_line(int stream, const char *p, size_t n) {
    orbit_lock(&g_io_lock);
    write_bytes(stream, p, n, 1);
    orbit_unlock(&g_io_lock);
}
/* Every complete line is delivered to the log as it ends, so a flush has nothing to add. The unterminated one is not cut at a flush
 * (std:io writeStdout flushes after each call, and "text" then "\n" must stay one record); it goes out when the module ends,
 * before a read of stdin (a prompt), before a stderr write (ordering) and when it outgrows its buffer. */
void orin_platform_flush(void) {}
void orin_orbit_flush_line(void) {
    orbit_lock(&g_io_lock);
    line_emit(&g_out, LOG_INFO);
    orbit_unlock(&g_io_lock);
}

ORBIT_WEAK size_t orin_platform_stdin_read(char *buf, size_t n) {
    (void)buf, (void)n;
    return 0;
}
ORBIT_WEAK int orin_platform_stdin_getc(void) { return -1; }

const char *orin_platform_error_message(int code) {
    static const struct { int code; const char *text; } t[] = {
        {0, "Success"}, {EPERM, "Operation not permitted"}, {ENOENT, "No such file or directory"}, {EIO, "Input/output error"},
        {EBADF, "Bad file descriptor"}, {ENOMEM, "Cannot allocate memory"}, {EACCES, "Permission denied"},
        {EBUSY, "Device or resource busy"}, {EEXIST, "File exists"}, {ENOTDIR, "Not a directory"}, {EISDIR, "Is a directory"},
        {EINVAL, "Invalid argument"}, {EMFILE, "Too many open files"}, {ENOSPC, "No space left on device"},
        {ENAMETOOLONG, "File name too long"}, {EADDRINUSE, "Address already in use"}, {ECONNREFUSED, "Connection refused"}};
    for (unsigned i = 0; i < sizeof t / sizeof t[0]; i++)
        if (t[i].code == code) return t[i].text;
    return "Unknown error";
}

ORBIT_WEAK int orin_platform_file_read(const char *path, size_t plen, char **out, size_t *out_len) {
    (void)path, (void)plen;
    *out = NULL, *out_len = 0;
    return ORIN_PLATFORM_EPERM;
}
ORBIT_WEAK int orin_platform_file_write(const char *path, size_t plen, const char *data, size_t dlen) {
    (void)path, (void)plen, (void)data, (void)dlen;
    return ORIN_PLATFORM_EPERM;
}
ORBIT_WEAK int orin_platform_file_exists(const char *path, size_t plen) {
    (void)path, (void)plen;
    return 0;
}
ORBIT_WEAK int orin_platform_dir_list(const char *path, size_t plen, void (*each)(void *, const char *, size_t, int), void *ctx) {
    (void)path, (void)plen, (void)each, (void)ctx;
    return ORIN_PLATFORM_EPERM;
}
ORBIT_WEAK int orin_platform_stream_open(const char *path, size_t plen, int mode, orin_platform_stream **out) {
    (void)path, (void)plen;
    *out = NULL;
    return mode < 0 || mode > 2 ? ORIN_PLATFORM_EINVAL : ORIN_PLATFORM_EPERM;
}
/* No stream can be opened, so the functions below are never reached with a valid stream. */
ORBIT_WEAK size_t orin_platform_stream_read(orin_platform_stream *s, char *buf, size_t n) {
    (void)s, (void)buf, (void)n;
    return 0;
}
ORBIT_WEAK int orin_platform_stream_getc(orin_platform_stream *s) {
    (void)s;
    return -1;
}
ORBIT_WEAK size_t orin_platform_stream_write(orin_platform_stream *s, const char *p, size_t n) {
    (void)s, (void)p, (void)n;
    return 0;
}
ORBIT_WEAK int orin_platform_stream_flush(orin_platform_stream *s) {
    (void)s;
    return ORIN_PLATFORM_EPERM;
}
ORBIT_WEAK int orin_platform_stream_error(const orin_platform_stream *s) {
    (void)s;
    return ORIN_PLATFORM_EPERM;
}
ORBIT_WEAK int orin_platform_stream_close(orin_platform_stream *s) {
    (void)s;
    return ORIN_PLATFORM_EPERM;
}

/* ---------------------------------------------------------------- host policy and paths */

int orin_platform_policy_load(unsigned *mask) { /* the host grant is the policy: nothing is denied on top of it */
    *mask = 0;
    return 0;
}
ORBIT_WEAK int64_t orin_platform_path_absolute(const char *path, size_t plen, char *out, size_t cap) {
    if (plen == 0) return -1;
    if (path[0] == '/') return orin_platform_path_normalize(path, plen, out, cap);
    char *tmp = (char *)orin_platform_alloc(plen + 1); /* the working directory is "/" */
    if (!tmp) return -1;
    tmp[0] = '/';
    orin_platform_mem_copy(tmp + 1, path, plen);
    int64_t r = orin_platform_path_normalize(tmp, plen + 1, out, cap);
    orin_platform_free(tmp);
    return r;
}
ORBIT_WEAK int64_t orin_platform_path_real(const char *abs, size_t alen, char *out, size_t cap) { /* no file system, no links */
    if (alen == 0 || alen + 1 > cap) return -1;
    orin_platform_mem_copy(out, abs, alen);
    out[alen] = 0;
    return (int64_t)alen;
}

/* Ends the module with a message the test runner recognises (the prefix "wasm32-orbit: " or "wasm64-orbit: ", by pointer width). */
__attribute__((noreturn)) void orin_orbit_fatal(const char *what, const char *detail, int status) {
    static char buf[1100];
    size_t n = 0;
    const char *parts[] = {sizeof(void *) == 4 ? "wasm32-orbit: " : "wasm64-orbit: ", what, detail};
    for (int k = 0; k < 3; k++)
        for (const char *p = parts[k]; *p && n < sizeof buf - 1; p++) buf[n++] = *p;
    orin_orbit_flush_line();
    orin_platform_write_line(ORIN_PLATFORM_STDERR, buf, n);
    g_exit_status = status;
    __builtin_trap();
}

/* ---------------------------------------------------------------- network: the narrowing of grants is pure; the rest is orbit_net.h */

ORBIT_WEAK int orin_platform_tcp_listen(const orin_platform_net *g, const char *a, size_t al, int port, int backlog, int opt,
                                        orin_platform_net *out, int *out_port) {
    (void)g, (void)a, (void)al, (void)port, (void)backlog, (void)opt, (void)out, (void)out_port;
    return ORIN_PLATFORM_EPERM;
}
ORBIT_WEAK int orin_platform_tcp_accept(const orin_platform_net *l, int timeout_ms, int opt, orin_platform_net *out, char *peer,
                                        size_t pcap, int *peer_port) {
    (void)l, (void)timeout_ms, (void)opt, (void)out, (void)peer, (void)pcap, (void)peer_port;
    return ORIN_PLATFORM_EPERM;
}
ORBIT_WEAK int orin_platform_tcp_connect(const orin_platform_net *g, const char *h, size_t hl, int port, int timeout_ms, int opt,
                                         orin_platform_net *out) {
    (void)g, (void)h, (void)hl, (void)port, (void)timeout_ms, (void)opt, (void)out;
    return ORIN_PLATFORM_EPERM;
}
ORBIT_WEAK int orin_platform_stream_recv(const orin_platform_net *s, char *buf, size_t cap, int timeout_ms, size_t *out_len) {
    (void)s, (void)buf, (void)cap, (void)timeout_ms;
    *out_len = 0;
    return ORIN_PLATFORM_EPERM;
}
ORBIT_WEAK int orin_platform_stream_send(const orin_platform_net *s, const char *data, size_t len, int timeout_ms, size_t *out_sent) {
    (void)s, (void)data, (void)len, (void)timeout_ms;
    *out_sent = 0;
    return ORIN_PLATFORM_EPERM;
}
ORBIT_WEAK int orin_platform_net_shutdown(const orin_platform_net *s, int how) {
    (void)s, (void)how;
    return ORIN_PLATFORM_EPERM;
}
ORBIT_WEAK int orin_platform_net_close(orin_platform_net *h) { /* a record that never held a socket: nothing to release */
    if (h) h->fd = -1, h->can = 0;
    return 0;
}
ORBIT_WEAK int orin_platform_dns_resolve(const orin_platform_net *g, const char *name, size_t nlen, char *out, size_t cap,
                                         size_t *out_len) {
    (void)g, (void)name, (void)nlen, (void)out, (void)cap;
    *out_len = 0;
    return ORIN_PLATFORM_EPERM;
}


/* ---------------------------------------------------------------- wake sources: flags (a wait that would block is a monitor wait) */

enum { WAKE_MAX = 1 << 12 };
typedef struct {
    int live, set, depth;
    uint32_t gen;
    int64_t parent;
} Wake;
static Wake g_wake[WAKE_MAX];
static uint32_t g_wake_hi, g_wake_free[WAKE_MAX], g_wake_nfree, g_wake_lock; /* the lock guards open / close */
#ifdef ORBIT_THREADS
static __thread int64_t g_wake_bound; /* the wake source bound to this thread */
#else
static int64_t g_wake_bound; /* orin_seq_orbit.c switches it with the running task */
#endif

static Wake *wake_ref(int64_t h) {
    uint32_t i = orbit_slot_index(h);
    return h > 0 && i < g_wake_hi && g_wake[i].live && g_wake[i].gen == orbit_slot_gen(h) ? &g_wake[i] : NULL;
}
int64_t orin_platform_wake_open(void) {
    orbit_lock(&g_wake_lock);
    Wake *p = wake_ref(g_wake_bound);
    uint32_t i;
    if (p && p->depth >= ORIN_PLATFORM_WAKE_DEPTH) i = WAKE_MAX;
    else if (g_wake_nfree) i = g_wake_free[--g_wake_nfree];
    else if (g_wake_hi < WAKE_MAX) i = g_wake_hi++;
    else i = WAKE_MAX;
    if (i == WAKE_MAX) {
        orbit_unlock(&g_wake_lock);
        return 0;
    }
    Wake *w = &g_wake[i];
    w->gen++;
    w->set = 0, w->depth = p ? p->depth + 1 : 0, w->parent = p ? g_wake_bound : 0;
    __atomic_store_n(&w->live, 1, __ATOMIC_RELEASE);
    g_wake_bound = orbit_slot_handle(w->gen, i);
    orbit_unlock(&g_wake_lock);
    return g_wake_bound;
}
int64_t orin_platform_wake_close(int64_t h) {
    orbit_lock(&g_wake_lock);
    Wake *w = wake_ref(h);
    if (w) {
        if (g_wake_bound == h) g_wake_bound = w->parent;
        __atomic_store_n(&w->live, 0, __ATOMIC_RELEASE);
        g_wake_free[g_wake_nfree++] = (uint32_t)(w - g_wake);
    }
    orbit_unlock(&g_wake_lock);
    return w ? 0 : ORIN_PLATFORM_EINVAL;
}
int64_t orin_platform_wake_signal(int64_t h) {
    Wake *w = wake_ref(h);
    int zero = 0;
    return w && __atomic_compare_exchange_n(&w->set, &zero, 1, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST) ? 1 : 0;
}
int64_t orin_platform_wake_check(int64_t h) {
    Wake *w = wake_ref(h);
    if (!w) return 2;
    for (; w; w = wake_ref(w->parent))
        if (__atomic_load_n(&w->set, __ATOMIC_SEQ_CST)) return 1;
    return 0;
}
int64_t orin_platform_wake_bind(int64_t h) {
    int64_t old = g_wake_bound;
    g_wake_bound = wake_ref(h) ? h : 0;
    return old;
}
int64_t orin_platform_wake_bound(void) { return g_wake_bound; }
