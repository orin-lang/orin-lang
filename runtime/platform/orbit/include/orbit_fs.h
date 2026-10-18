/* L0 family "fs": files, directories and paths over orbit:fs/v1 (host-abi.md section 4b). The generated C includes this file when
 * the program's manifest lists fs/v1 (compiler/analysis/orbit.or), so a program without file access has no such import. The core
 * (orin_platform_orbit.c) holds the refusing stubs this file replaces. Paths are virtual: the host maps them onto its mounts. */
#ifndef ORBIT_FS_H
#define ORBIT_FS_H
#include "orbit_abi.h"

#define ORBIT_FS(n) ORBIT_IMPORT("orbit:fs/v1", n)
ORBIT_FS("open") int64_t orbit_fs_open(int64_t p, int64_t n, int32_t mode);
ORBIT_FS("read") int64_t orbit_fs_read(int64_t h, int64_t p, int64_t cap);
ORBIT_FS("write") int64_t orbit_fs_write(int64_t h, int64_t p, int64_t n);
ORBIT_FS("flush") int32_t orbit_fs_flush(int64_t h);
ORBIT_FS("close") int32_t orbit_fs_close(int64_t h);
ORBIT_FS("stat") int32_t orbit_fs_stat(int64_t p, int64_t n);
ORBIT_FS("size") int64_t orbit_fs_size(int64_t p, int64_t n);
ORBIT_FS("dir_open") int64_t orbit_fs_dir_open(int64_t p, int64_t n);
ORBIT_FS("dir_next") int64_t orbit_fs_dir_next(int64_t h, int64_t p, int64_t cap);
ORBIT_FS("dir_close") int32_t orbit_fs_dir_close(int64_t h);
ORBIT_FS("realpath") int64_t orbit_fs_realpath(int64_t p, int64_t n, int64_t out, int64_t cap);
ORBIT_FS("cwd") int64_t orbit_fs_cwd(int64_t out, int64_t cap);

/* Host status (host-abi.md section 3, negated) to the errno value the L0 contract names (Linux numbering). */
static int fs_code(int64_t st, int writing) {
    static const unsigned char k[] = {0, EINVAL, EACCES, ENOENT, EBADF, ENAMETOOLONG, EMFILE, EIO, EIO, EIO, EIO, EIO, EEXIST,
                                      ENOTDIR, EISDIR, EIO, EIO};
    return st >= 0 ? 0 : writing && st == -6 ? ENOSPC : st >= -16 ? k[-st] : EIO; /* ERR_QUOTA is ENOSPC for a write, else EMFILE */
}

int orin_platform_file_read(const char *path, size_t plen, char **out, size_t *out_len) {
    *out = NULL, *out_len = 0;
    int64_t sz = orbit_fs_size(ORBIT_PTR(path), (int64_t)plen);
    if (sz < 0) return fs_code(sz, 0);
    int64_t h = orbit_fs_open(ORBIT_PTR(path), (int64_t)plen, 0);
    if (h < 0) return fs_code(h, 0);
    size_t cap = (size_t)sz + 1, len = 0; /* one spare byte: the read that returns 0 needs room */
    char *buf = (char *)orin_platform_alloc(cap);
    int err = buf ? 0 : ORIN_PLATFORM_ENOMEM;
    while (!err) {
        if (len == cap) { /* the file grew since size() */
            char *nb = (char *)orin_platform_realloc(buf, cap * 2);
            if (!nb) err = ORIN_PLATFORM_ENOMEM;
            else buf = nb, cap *= 2;
            continue;
        }
        int64_t r = orbit_fs_read(h, ORBIT_PTR(buf + len), (int64_t)(cap - len));
        if (r < 0) err = fs_code(r, 0);
        else if (r == 0) break;
        else len += (size_t)r;
    }
    orbit_fs_close(h);
    if (err) {
        orin_platform_free(buf);
        return err;
    }
    *out = buf, *out_len = len;
    return 0;
}
/* Writes all of data[0..n-1] to host handle h: 0 or the code of the first failure. */
static int fs_write_all(int64_t h, const char *data, size_t n) {
    while (n) {
        int64_t r = orbit_fs_write(h, ORBIT_PTR(data), (int64_t)n);
        if (r < 0) return fs_code(r, 1);
        if (r == 0) return EIO;
        data += r, n -= (size_t)r;
    }
    return 0;
}
int orin_platform_file_write(const char *path, size_t plen, const char *data, size_t dlen) {
    int64_t h = orbit_fs_open(ORBIT_PTR(path), (int64_t)plen, 1);
    if (h < 0) return fs_code(h, 0);
    int err = fs_write_all(h, data, dlen);
    int f = orbit_fs_flush(h), c = orbit_fs_close(h);
    return err ? err : f < 0 ? fs_code(f, 1) : c < 0 ? fs_code(c, 1) : 0;
}
int orin_platform_file_exists(const char *path, size_t plen) { return orbit_fs_stat(ORBIT_PTR(path), (int64_t)plen) > 0; }
int orin_platform_dir_list(const char *path, size_t plen, void (*each)(void *, const char *, size_t, int), void *ctx) {
    char name[1024]; /* longer than any file name; a longer one ends the listing with ENAMETOOLONG */
    int64_t d = orbit_fs_dir_open(ORBIT_PTR(path), (int64_t)plen), r;
    if (d < 0) return fs_code(d, 0);
    while ((r = orbit_fs_dir_next(d, ORBIT_PTR(name), sizeof name)) > 0)
        each(ctx, name, (size_t)(r & 0x3fffffffffffffffLL), (int)((r >> 62) & 1));
    orbit_fs_dir_close(d);
    return fs_code(r, 0);
}

/* A stream is one host handle, a 4 KiB buffer (for reading or writing, by mode) and the sticky first error. */
enum { SBUF = 4096 };
struct orin_platform_stream {
    int64_t h;
    int mode, err, eof;
    size_t pos, len; /* read: b[pos..len) is unread; write: b[0..len) is unwritten */
    char b[SBUF];
};
static void s_fail(orin_platform_stream *s, int code) {
    if (!s->err) s->err = code ? code : EIO;
}
int orin_platform_stream_open(const char *path, size_t plen, int mode, orin_platform_stream **out) {
    *out = NULL;
    if (mode < 0 || mode > 2) return ORIN_PLATFORM_EINVAL;
    orin_platform_stream *s = (orin_platform_stream *)orin_platform_alloc(sizeof *s);
    if (!s) return ORIN_PLATFORM_ENOMEM;
    int64_t h = orbit_fs_open(ORBIT_PTR(path), (int64_t)plen, mode);
    if (h < 0) {
        orin_platform_free(s);
        return fs_code(h, 0);
    }
    s->h = h, s->mode = mode, s->err = s->eof = 0, s->pos = s->len = 0;
    *out = s;
    return 0;
}
size_t orin_platform_stream_read(orin_platform_stream *s, char *buf, size_t n) {
    size_t got = 0;
    while (got < n) {
        if (s->pos < s->len) {
            size_t k = s->len - s->pos < n - got ? s->len - s->pos : n - got;
            orin_platform_mem_copy(buf + got, s->b + s->pos, k);
            got += k, s->pos += k;
            continue;
        }
        if (s->eof) break;
        int direct = n - got >= SBUF; /* a big read skips the buffer */
        int64_t r = orbit_fs_read(s->h, direct ? ORBIT_PTR(buf + got) : ORBIT_PTR(s->b), direct ? (int64_t)(n - got) : SBUF);
        if (r <= 0) {
            if (r < 0) s_fail(s, fs_code(r, 0));
            s->eof = 1;
        } else if (direct) got += (size_t)r;
        else s->pos = 0, s->len = (size_t)r;
    }
    return got;
}
int orin_platform_stream_getc(orin_platform_stream *s) {
    char c;
    return orin_platform_stream_read(s, &c, 1) == 1 ? (unsigned char)c : -1;
}
int orin_platform_stream_flush(orin_platform_stream *s) {
    if (s->mode == ORIN_PLATFORM_STREAM_READ) return s->err;
    int e = s->len ? fs_write_all(s->h, s->b, s->len) : 0;
    s->len = 0;
    if (e) s_fail(s, e);
    int64_t f = orbit_fs_flush(s->h);
    if (f < 0) s_fail(s, fs_code(f, 1));
    return s->err;
}
size_t orin_platform_stream_write(orin_platform_stream *s, const char *p, size_t n) {
    if (s->mode == ORIN_PLATFORM_STREAM_READ) {
        s_fail(s, EBADF);
        return 0;
    }
    if (s->len + n > SBUF) { /* hand the buffered bytes, and a write that is itself big, to the host */
        int e = fs_write_all(s->h, s->b, s->len);
        s->len = 0;
        if (!e && n >= SBUF) e = fs_write_all(s->h, p, n);
        if (e) {
            s_fail(s, e);
            return 0;
        }
        if (n >= SBUF) return n;
    }
    orin_platform_mem_copy(s->b + s->len, p, n);
    s->len += n;
    return n;
}
int orin_platform_stream_error(const orin_platform_stream *s) { return s->err; }
int orin_platform_stream_close(orin_platform_stream *s) {
    orin_platform_stream_flush(s);
    int64_t c = orbit_fs_close(s->h);
    if (c < 0) s_fail(s, fs_code(c, 1));
    int err = s->err;
    orin_platform_free(s);
    return err;
}

int64_t orin_platform_path_absolute(const char *path, size_t plen, char *out, size_t cap) {
    if (plen == 0) return -1;
    if (path[0] == '/') return orin_platform_path_normalize(path, plen, out, cap);
    char cwd[4097]; /* the virtual working directory: "/", or the host's --cwd */
    int64_t cl = orbit_fs_cwd(ORBIT_PTR(cwd), sizeof cwd - 1);
    char *tmp = cl > 0 ? (char *)orin_platform_alloc((size_t)cl + 1 + plen) : NULL;
    if (!tmp) return -1;
    orin_platform_mem_copy(tmp, cwd, (size_t)cl);
    tmp[cl] = '/';
    orin_platform_mem_copy(tmp + cl + 1, path, plen);
    int64_t r = orin_platform_path_normalize(tmp, (size_t)cl + 1 + plen, out, cap);
    orin_platform_free(tmp);
    return r;
}
int64_t orin_platform_path_real(const char *abs, size_t alen, char *out, size_t cap) { /* a virtual path, never a host path */
    int64_t r = cap ? orbit_fs_realpath(ORBIT_PTR(abs), (int64_t)alen, ORBIT_PTR(out), (int64_t)cap - 1) : -1;
    if (r <= 0) return -1;
    out[r] = 0;
    return r;
}
#endif
