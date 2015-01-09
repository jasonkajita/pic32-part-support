/*
 * Copyright (c) 1996-2003 MIPS Technologies, Inc.
 * All rights reserved.
 * 
 * Unpublished rights (if any) reserved under the copyright laws of the
 * United States of America and other countries.
 * 
 * This code is proprietary to MIPS Technologies, Inc. ("MIPS
 * Technologies").  Any copying, reproducing, modifying or use of
 * this code (in whole or in part) that is not expressly permitted
 * in writing by MIPS Technologies or an authorized third party is
 * strictly prohibited.  At a minimum, this code is protected under
 * unfair competition and copyright laws.  Violations thereof may result
 * in criminal penalties and fines.
 * 
 * MIPS Technologies reserves the right to change this code to improve
 * function, design or otherwise.  MIPS Technologies does not assume any
 * liability arising out of the application or use of this code, or of
 * any error or omission in such code.  Any warranties, whether express,
 * statutory, implied or otherwise, including but not limited to the
 * implied warranties of merchantability or fitness for a particular
 * purpose, are excluded.  Except as expressly provided in any written
 * license agreement from MIPS Technologies or an authorized third party,
 * the furnishing of this code does not give recipient any license to
 * any intellectual property rights, including any patent rights, that
 * cover this code.
 * 
 * This code shall not be exported, reexported, transferred, or released,
 * directly or indirectly, in violation of the law of any country or
 * international law, regulation, treaty, Executive Order, statute,
 * amendments or supplements thereto.  Should a conflict arise regarding
 * the export, reexport, transfer, or release of this code, the laws of
 * the United States of America shall be the governing law.
 * 
 * This code constitutes one or more of the following: commercial
 * computer software, commercial computer software documentation or
 * other commercial items.  If the user of this code, or any related
 * documentation of any kind, including related technical data or
 * manuals, is an agency, department, or other entity of the United
 * States government ("Government"), the use, duplication, reproduction,
 * release, modification, disclosure, or transfer of this code, or
 * any related documentation of any kind, is restricted in accordance
 * with Federal Acquisition Regulation 12.212 for civilian agencies
 * and Defense Federal Acquisition Regulation Supplement 227.7202 for
 * military agencies.  The use of this code by the Government is further
 * restricted in accordance with the terms of the license agreement(s)
 * and/or applicable contract terms and conditions covering this code
 * from MIPS Technologies or an authorized third party.
 * 
 * 
 */

/*
 * sys/time.h : timer definitions
 */


#ifndef __SYS_TIME_H
#ifdef __cplusplus
extern "C" {
#endif
#define __SYS_TIME_H

#include <machine/ansi.h>

struct timeval {
	long	tv_sec;		/* seconds */
	long	tv_usec;	/* and microseconds */
};


struct timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of dst correction */
};


#define	timerisset(tvp)		((tvp)->tv_sec || (tvp)->tv_usec)
#define	timercmp(tvp, uvp, cmp)	\
	(((tvp)->tv_sec == (uvp)->tv_sec) ? \
	    ((tvp)->tv_usec cmp (uvp)->tv_usec) : \
	    ((tvp)->tv_sec cmp (uvp)->tv_sec))
#define	timerclear(tvp)		(tvp)->tv_sec = (tvp)->tv_usec = 0
#define	timeradd(tvp, uvp, vvp)						\
	do {								\
		(vvp)->tv_sec = (tvp)->tv_sec + (uvp)->tv_sec;		\
		(vvp)->tv_usec = (tvp)->tv_usec + (uvp)->tv_usec;	\
		if ((vvp)->tv_usec >= 1000000L) {			\
			(vvp)->tv_sec++;				\
			(vvp)->tv_usec -= 1000000L;			\
		}							\
	} while (0)
#define	timersub(tvp, uvp, vvp)						\
	do {								\
		(vvp)->tv_sec = (tvp)->tv_sec - (uvp)->tv_sec;		\
		(vvp)->tv_usec = (tvp)->tv_usec - (uvp)->tv_usec;	\
		if ((vvp)->tv_usec < 0) {				\
			(vvp)->tv_sec--;				\
			(vvp)->tv_usec += 1000000L;			\
		}							\
	} while (0)

/*
 * Names of the interval timers, and structure
 * defining a timer setting.
 */
#define ITIMER_REAL	0
#define ITIMER_VIRTUAL	1
#define ITIMER_PROF	2
#define ITIMER_USER	3
#define NITIMER		4

struct xcptcontext;

struct itimerval {
    struct timeval	it_interval;	/* timer interval */
    struct timeval	it_value;	/* current value */
    void		(*it_func)(struct timeval *, struct xcptcontext *);
};

int setitimer (unsigned int, struct itimerval *, struct itimerval *);
int getitimer (unsigned int, struct itimerval *);
int gettimeofday (struct timeval *, void *);
int settimeofday (const struct timeval *, void *);

/* POSIX.4 stuff */
#if defined(_POSIX_TIMERS) || defined(_KERNEL)
struct timespec {
    long	 	tv_sec;		/* seconds */
    long 		tv_nsec;	/* and nanoseconds */
};

struct itimerspec {
    struct timespec	it_value;
    struct timespec	it_interval;
};

/* Operations on timespecs. */
#define	timespecclear(tsp)		(tsp)->tv_sec = (tsp)->tv_nsec = 0
#define	timespecisset(tsp)		((tsp)->tv_sec || (tsp)->tv_nsec)
#define	timespeccmp(tsp, usp, cmp)					\
	(((tsp)->tv_sec == (usp)->tv_sec) ?				\
	    ((tsp)->tv_nsec cmp (usp)->tv_nsec) :			\
	    ((tsp)->tv_sec cmp (usp)->tv_sec))
#define	timespecadd(tsp, usp, vsp)					\
	do {								\
		(vsp)->tv_sec = (tsp)->tv_sec + (usp)->tv_sec;		\
		(vsp)->tv_nsec = (tsp)->tv_nsec + (usp)->tv_nsec;	\
		if ((vsp)->tv_nsec >= 1000000000L) {			\
			(vsp)->tv_sec++;				\
			(vsp)->tv_nsec -= 1000000000L;			\
		}							\
	} while (0)
#define	timespecsub(tsp, usp, vsp)					\
	do {								\
		(vsp)->tv_sec = (tsp)->tv_sec - (usp)->tv_sec;		\
		(vsp)->tv_nsec = (tsp)->tv_nsec - (usp)->tv_nsec;	\
		if ((vsp)->tv_nsec < 0) {				\
			(vsp)->tv_sec--;				\
			(vsp)->tv_nsec += 1000000000L;			\
		}							\
	} while (0)

#ifdef	_CLOCKID_T_
typedef	_CLOCKID_T_	clockid_t;
#undef	_CLOCKID_T_
#endif

#define CLOCK_REALTIME	0
#define CLOCK_IDLETIME	1		/* XXX non standard */
#define CLOCK_PROCTIME	2		/* XXX non standard */
#define CLOCK_MONOTONIC	3

int	clock_getres (clockid_t, struct timespec *);
int	clock_gettime (clockid_t, struct timespec *);
int	clock_settime (clockid_t, const struct timespec *);
int	nanosleep (const struct timespec *, struct timespec *);

struct sigevent;

#define TIMER_ABSTIME	1

#ifdef	_TIMER_T_
typedef	_TIMER_T_	timer_t;
#undef	_TIMER_T_
#endif

int	timer_create (clockid_t, struct sigevent *, timer_t *);
int	timer_delete (timer_t);
int	timer_getoverrun (timer_t);
int	timer_gettime (timer_t, struct itimerspec *);
int	timer_settime (timer_t, int, const struct itimerspec *,
		       struct itimerspec *);

#endif /* _POSIX_TIMERS */

#ifdef __cplusplus
}
#endif
#endif
