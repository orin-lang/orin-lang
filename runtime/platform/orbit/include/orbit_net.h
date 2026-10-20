/* L0 family "net": TCP and DNS over orbit:net/v1 (host-abi.md section 4d). The generated C includes this file when the program's
 * manifest lists net/v1 (compiler/analysis/orbit.or), so a program without network access has no such import. The core
 * (orin_platform_orbit.c) holds the refusing stubs this file replaces, the narrowing of grants (pure, shared with the native
 * layer) and the wake sources.
 *
 * A listener or stream record keeps the host handle (an i64 > 0) in sc[0].lo / .hi, which such a record does not otherwise use, and
 * fd = 1 while it is open. A grant and its scopes are checked here (orin_platform_netscope.h) before the host is asked; the host's
 * own grant is the outer bound. The wake sources are L0 flags: one thread runs everything, so nothing can set a token while a host
 * call blocks. A wait checks the bound token first and the host gets no wake handle (its wake_* functions would import this
 * capability into every program that starts a task). */
#ifndef ORBIT_NET_H
#define ORBIT_NET_H
#include "orbit_abi.h"
#include "../../orin_platform_netscope.h"

#define ORBIT_NET(n) ORBIT_IMPORT("orbit:net/v1", n)
ORBIT_NET("tcp_listen") int64_t orbit_tcp_listen(int64_t a, int64_t n, int32_t port, int32_t backlog, int32_t opt);
ORBIT_NET("local_port") int32_t orbit_local_port(int64_t h);
ORBIT_NET("tcp_accept") int64_t orbit_tcp_accept(int64_t l, int32_t ms, int64_t wake);
ORBIT_NET("peer") int64_t orbit_peer(int64_t h, int64_t out, int64_t cap);
ORBIT_NET("peer_port") int32_t orbit_peer_port(int64_t h);
ORBIT_NET("tcp_connect") int64_t orbit_tcp_connect(int64_t h, int64_t n, int32_t port, int32_t ms, int64_t wake);
ORBIT_NET("recv") int64_t orbit_recv(int64_t h, int64_t p, int64_t cap, int32_t ms, int64_t wake);
ORBIT_NET("send") int64_t orbit_send(int64_t h, int64_t p, int64_t n, int32_t ms, int64_t wake);
ORBIT_NET("shutdown") int32_t orbit_shutdown(int64_t h, int32_t how);
ORBIT_NET("close") int32_t orbit_net_close(int64_t h);
ORBIT_NET("dns_resolve") int64_t orbit_dns_resolve(int64_t n, int64_t nl, int64_t out, int64_t cap);

/* Host status (host-abi.md section 3, negated) to the L0 code: errno values (Linux numbering) and the NET_* codes. */
static int net_code(int64_t st) {
    static const unsigned short k[] = {0, EINVAL, EPERM, ENOENT, EPERM, EINVAL, EMFILE, EIO, ORIN_PLATFORM_NET_EOF,
                                       ORIN_PLATFORM_NET_TIMEOUT, ORIN_PLATFORM_NET_RESET, ORIN_PLATFORM_NET_CANCELLED, EIO, EIO,
                                       EIO, ECONNREFUSED, EADDRINUSE};
    return st >= 0 ? 0 : st >= -16 ? k[-st] : EIO;
}
static int64_t net_h(const orin_platform_net *n) { return (int64_t)(((uint64_t)n->sc[0].hi << 32) | n->sc[0].lo); }
static int net_new(orin_platform_net *out, unsigned kind, int64_t h) { /* a fresh record, or the code of the host failure h */
    if (h < 0) return net_code(h);
    orin_platform_mem_set(out, 0, sizeof *out);
    out->magic = ORIN_PLATFORM_NET_MAGIC, out->kind = kind, out->fd = 1;
    out->sc[0].lo = (unsigned)h, out->sc[0].hi = (unsigned)((uint64_t)h >> 32);
    return 0;
}
/* A cancelled task starts no new network work: the bound token (or an ancestor) is checked before the host is asked. */
static int net_stop(void) { return orin_platform_wake_check(orin_platform_wake_bound()) == 1; }

int orin_platform_tcp_listen(const orin_platform_net *g, const char *a, size_t al, int port, int backlog, int opt,
                             orin_platform_net *out, int *out_port) {
    if (net_ok(g, ORIN_PLATFORM_NET_GRANT) || !net_scope(g, ORIN_PLATFORM_NET_LISTEN, a, al, port)) return ORIN_PLATFORM_EPERM;
    orin_platform_net n;
    int e = net_new(&n, ORIN_PLATFORM_NET_LISTENER, orbit_tcp_listen(ORBIT_PTR(a), (int64_t)al, port, backlog, opt));
    if (e) return e;
    int bound = orbit_local_port(net_h(&n));
    *out = n, *out_port = bound > 0 ? bound : port;
    return 0;
}
int orin_platform_tcp_accept(const orin_platform_net *l, int timeout_ms, int opt, orin_platform_net *out, char *peer,
                             size_t pcap, int *peer_port) {
    (void)opt; /* NODELAY is always on */
    if (net_ok(l, ORIN_PLATFORM_NET_LISTENER)) return ORIN_PLATFORM_EPERM;
    if (net_stop()) return ORIN_PLATFORM_NET_CANCELLED;
    orin_platform_net n;
    int e = net_new(&n, ORIN_PLATFORM_NET_STREAM, orbit_tcp_accept(net_h(l), timeout_ms, 0));
    if (e) return e;
    char t[64]; /* a numeric address is at most 45 bytes */
    int64_t pl = orbit_peer(net_h(&n), ORBIT_PTR(t), sizeof t);
    size_t k = pl > 0 && pcap ? ((size_t)pl < pcap - 1 ? (size_t)pl : pcap - 1) : 0;
    orin_platform_mem_copy(peer, t, k);
    if (pcap) peer[k] = 0;
    int pp = orbit_peer_port(net_h(&n));
    *peer_port = pp > 0 ? pp : 0;
    *out = n;
    return 0;
}
int orin_platform_tcp_connect(const orin_platform_net *g, const char *h, size_t hl, int port, int timeout_ms, int opt,
                              orin_platform_net *out) {
    (void)opt;
    if (net_ok(g, ORIN_PLATFORM_NET_GRANT) || !net_scope(g, ORIN_PLATFORM_NET_CONNECT, h, hl, port)) return ORIN_PLATFORM_EPERM;
    if (net_stop()) return ORIN_PLATFORM_NET_CANCELLED;
    if (port < 1 || port > 65535) return ORIN_PLATFORM_EINVAL;
    return net_new(out, ORIN_PLATFORM_NET_STREAM, orbit_tcp_connect(ORBIT_PTR(h), (int64_t)hl, port, timeout_ms, 0));
}
int orin_platform_stream_recv(const orin_platform_net *s, char *buf, size_t cap, int timeout_ms, size_t *out_len) {
    *out_len = 0;
    if (net_ok(s, ORIN_PLATFORM_NET_STREAM)) return ORIN_PLATFORM_EPERM;
    if (cap == 0) return ORIN_PLATFORM_EINVAL;
    if (net_stop()) return ORIN_PLATFORM_NET_CANCELLED;
    int64_t r = orbit_recv(net_h(s), ORBIT_PTR(buf), (int64_t)cap, timeout_ms, 0);
    if (r < 1) return r < 0 ? net_code(r) : EIO;
    *out_len = (size_t)r;
    return 0;
}
int orin_platform_stream_send(const orin_platform_net *s, const char *data, size_t len, int timeout_ms, size_t *out_sent) {
    *out_sent = 0;
    if (net_ok(s, ORIN_PLATFORM_NET_STREAM)) return ORIN_PLATFORM_EPERM;
    if (net_stop()) return ORIN_PLATFORM_NET_CANCELLED;
    int64_t r = orbit_send(net_h(s), ORBIT_PTR(data), (int64_t)len, timeout_ms, 0);
    *out_sent = r > 0 ? (size_t)r : 0;
    return net_code(r);
}
int orin_platform_net_shutdown(const orin_platform_net *s, int how) {
    if (net_ok(s, ORIN_PLATFORM_NET_STREAM)) return ORIN_PLATFORM_EPERM;
    return how < 0 || how > 2 ? ORIN_PLATFORM_EINVAL : net_code(orbit_shutdown(net_h(s), how));
}
int orin_platform_net_close(orin_platform_net *h) {
    if (!h || h->magic != ORIN_PLATFORM_NET_MAGIC) return ORIN_PLATFORM_EPERM;
    if (h->fd >= 0 && h->kind != ORIN_PLATFORM_NET_GRANT) orbit_net_close(net_h(h));
    h->fd = -1, h->can = 0;
    return 0;
}
int orin_platform_dns_resolve(const orin_platform_net *g, const char *name, size_t nlen, char *out, size_t cap,
                              size_t *out_len) {
    *out_len = 0;
    if (net_ok(g, ORIN_PLATFORM_NET_GRANT) || !net_scope(g, ORIN_PLATFORM_NET_CONNECT, name, nlen, (int)g->sc[1].lo))
        return ORIN_PLATFORM_EPERM;
    if (net_stop()) return ORIN_PLATFORM_NET_CANCELLED;
    int64_t r = orbit_dns_resolve(ORBIT_PTR(name), (int64_t)nlen, ORBIT_PTR(out), (int64_t)cap);
    if (r < 0) return net_code(r);
    *out_len = (size_t)r;
    return 0;
}
#endif
