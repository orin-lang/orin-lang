/* Minimal freestanding libc surface for the Orbit L0 (ADR-0055): the errno values orin_platform.h names (Linux numbering). */
#ifndef ORIN_ORBIT_ERRNO_H
#define ORIN_ORBIT_ERRNO_H
#define EPERM 1
#define ENOENT 2
#define ENOMEM 12
#define EIO 5
#define EBADF 9
#define EACCES 13
#define EEXIST 17
#define ENOTDIR 20
#define EISDIR 21
#define EMFILE 24
#define ENOSPC 28
#define ENAMETOOLONG 36
#define EADDRINUSE 98
#define ECONNREFUSED 111
#define EBUSY 16
#define EINVAL 22
#define EDEADLK 35
#endif
