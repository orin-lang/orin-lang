/* Orin L0 platform layer: the scope rules of a network grant (ADR-0033), pure (no socket, no OS), shared by the native layer
 * (through orin_platform_pure.h) and the WebAssembly families (orbit/include/orbit_net.h): both enforce the same rules before any
 * system call or host call. Static functions only, so it can be included from several translation units. Contracts: orin_platform.h. */
#ifndef ORIN_PLATFORM_NETSCOPE_H
#define ORIN_PLATFORM_NETSCOPE_H

static int net_ok(const orin_platform_net *h, unsigned kind) { /* identity, liveness and policy: 0 or EPERM */
    int live = h && h->magic == ORIN_PLATFORM_NET_MAGIC && h->kind == kind && !h->deny;
    return live && (kind == ORIN_PLATFORM_NET_GRANT ? h->can != 0 : h->fd >= 0) ? 0 : ORIN_PLATFORM_EPERM;
}

static int ieq(const char *a, const char *b, size_t n) {
    for (size_t i = 0; i < n; i++) {
        char x = a[i], y = b[i];
        if (x >= 'A' && x <= 'Z') x = (char)(x + 32);
        if (y >= 'A' && y <= 'Z') y = (char)(y + 32);
        if (x != y) return 0;
    }
    return 1;
}

/* Does pattern p cover s? s is a name or itself a "*.sfx" pattern (then every name s covers must be covered). */
static int net_cover(const char *p, size_t pl, const char *s, size_t sl) {
    int sw = sl >= 2 && s[0] == '*' && s[1] == '.';
    if (pl == 1 && p[0] == '*') return 1;
    if (pl >= 2 && p[0] == '*' && p[1] == '.')
        return (sw ? sl - 1 >= pl - 1 : sl > pl - 1) && ieq(s + sl - (pl - 1), p + 1, pl - 1);
    return !sw && pl == sl && ieq(p, s, pl);
}

static int net_text(const char *h, size_t hl) { /* a usable host text: 1..63 bytes, no NUL, no '*' */
    for (size_t i = 0; i < hl; i++)
        if (h[i] == 0 || h[i] == '*') return 0;
    return hl >= 1 && hl <= 63;
}

static int net_scope(const orin_platform_net *g, unsigned what, const char *h, size_t hl, int port) {
    const orin_platform_scope *s = &g->sc[what - 1];
    return (g->can & what) && net_text(h, hl) && port >= 0 && (unsigned)port >= s->lo && (unsigned)port <= s->hi &&
           net_cover(s->h, s->hl, h, hl);
}

#endif
