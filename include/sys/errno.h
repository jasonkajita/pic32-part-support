/*
 * errno.h : error number definitions
 *
 * Copyright (c) 1996-2001 MIPS Technologies Inc. All Rights Reserved.
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)errno.h	7.1 (Berkeley) 6/4/86
 */

#ifndef __SYS_ERRNO_H
#define __SYS_ERRNO_H

/*
 * Error codes
 */

#define	EPERM		1		/* Not owner */
#define	ENOENT		2		/* No such file or directory */
#define	ESRCH		3		/* No such process */
#define	EINTR		4		/* Interrupted system call */
#define	EIO		5		/* I/O error */
#define	ENXIO		6		/* No such device or address */
#define	E2BIG		7		/* Arg list too long */
#define	ENOEXEC		8		/* Exec format error */
#define	EBADF		9		/* Bad file number */
#define	ECHILD		10		/* No children */
#define	EAGAIN		11		/* No more processes */
#define	ENOMEM		12		/* Not enough core */
#define	EACCES		13		/* Permission denied */
#define	EFAULT		14		/* Bad address */
#define	ENOTBLK		15		/* Block device required */
#define	EBUSY		16		/* Mount device busy */
#define	EEXIST		17		/* File exists */
#define	EXDEV		18		/* Cross-device link */
#define	ENODEV		19		/* No such device */
#define	ENOTDIR		20		/* Not a directory*/
#define	EISDIR		21		/* Is a directory */
#define	EINVAL		22		/* Invalid argument */
#define	ENFILE		23		/* File table overflow */
#define	EMFILE		24		/* Too many open files */
#define	ENOTTY		25		/* Not a typewriter */
#define	ETXTBSY		26		/* Text file busy */
#define	EFBIG		27		/* File too large */
#define	ENOSPC		28		/* No space left on device */
#define	ESPIPE		29		/* Illegal seek */
#define	EROFS		30		/* Read-only file system */
#define	EMLINK		31		/* Too many links */
#define	EPIPE		32		/* Broken pipe */

/* math software */
#define	EDOM		33		/* Argument too large */
#define	ERANGE		34		/* Result too large */

#define ENOMSG		35		/* No message of desired type */
/* non-blocking and interrupt i/o */
#define	EWOULDBLOCK	45		/* Operation would block */
#define	EDEADLK		EWOULDBLOCK	/* ditto */
#define	EINPROGRESS	119		/* Operation now in progress */
#define	EALREADY	120		/* Operation already in progress */

/* ipc/network software */

	/* argument errors */
#define	ENOTSOCK	108		/* Socket operation on non-socket */
#define	EDESTADDRREQ	121		/* Destination address required */
#define	EMSGSIZE	122		/* Message too long */
#define	EPROTOTYPE	107		/* Protocol wrong type for socket */
#define	ENOPROTOOPT	109		/* Protocol not available */
#define	EPROTONOSUPPORT	123		/* Protocol not supported */
#define	ESOCKTNOSUPPORT	124		/* Socket type not supported */
#define	EOPNOTSUPP	95		/* Operation not supported on socket */
#define	EPFNOSUPPORT	96		/* Protocol family not supported */
#define	EAFNOSUPPORT	106		/* Address family not supported by protocol family */
#define	EADDRINUSE	112		/* Address already in use */
#define	EADDRNOTAVAIL	125		/* Can't assign requested address */

#define	ENOSYS		EOPNOTSUPP	/* Operation not supported */
#define ENOTSUP		EOPNOTSUPP	/* Operation not supported */

	/* operational errors */
#define	ENETDOWN	115		/* Network is down */
#define	ENETUNREACH	114		/* Network is unreachable */
#define	ENETRESET	126		/* Network dropped connection on reset */
#define	ECONNABORTED	113		/* Software caused connection abort */
#define	ECONNRESET	104		/* Connection reset by peer */
#define	ENOBUFS		105		/* No buffer space available */
#define	EISCONN		127		/* Socket is already connected */
#define	ENOTCONN	128		/* Socket is not connected */
#define	ESHUTDOWN	110		/* Can't send after socket shutdown */
#define	ETOOMANYREFS	129		/* Too many references: can't splice */
#define	ETIMEDOUT	116		/* Connection timed out */
#define	ETIME		62		/* Pthread timed wait expired */
#define	ECONNREFUSED	111		/* Connection refused */

	/* */
#define	ELOOP		92		/* Too many levels of symbolic links */
#define	ENAMETOOLONG	91		/* File name too long */

/* should be rearranged */
#define	EHOSTDOWN	117		/* Host is down */
#define	EHOSTUNREACH	118		/* No route to host */
#define	ENOTEMPTY	90		/* Directory not empty */

/* quotas & mush */
#define	EPROCLIM	130		/* Too many processes */
#define	EUSERS		131		/* Too many users */
#define	EDQUOT		132		/* Disc quota exceeded */

/* Network File System */
#define	ESTALE		133		/* Stale NFS file handle */
#define	EREMOTE		66		/* Too many levels of remote in path */

/* SystemV Record Locking */
#define ENOLCK          46              /* No record locks available. */

#define EILSEQ		138
#define	ECANCELED	140		/* Not used but needed for POSIX */

#ifdef _KERNEL
/* pseudo-errors returned inside kernel to modify return to process */
#define	ERESTART	(-1)		/* restart syscall */
#define	EJUSTRETURN	(-2)		/* don't modify regs, just return */
#endif

#endif /* !__SYS_ERRNO_H */
