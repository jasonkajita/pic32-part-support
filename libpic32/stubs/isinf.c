/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)isinf.c	5.1 (Berkeley) 3/18/91";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <machine/endian.h>
#include <stdlib.h>

union IEEEdp {
    long double	d;
    struct {
#if BYTE_ORDER == LITTLE_ENDIAN
	unsigned long long man : 52;
	unsigned int  exp : 11;
	unsigned int sign :  1;
#elif BYTE_ORDER == BIG_ENDIAN
	unsigned int sign :  1;
	unsigned int  exp : 11;
	unsigned long long man : 52;
#else
#error unsupported IEEE endianness
#endif
    } w;
};

#ifndef __NO_FLOAT
int isnanl (long double d)
{
	union IEEEdp u = {.d = d};
	return (u.w.exp == 0x7ff && u.w.man != 0);
}
int isnan (double d)
{
	return isnanl(d);
}
int isnanf (float d)
{
	return isnanl(d);
}

int isinfl (long double d)
{
	union IEEEdp u = {.d = d};
	return (u.w.exp == 0x7ff && u.w.man == 0);
}

int isinf (double d)
{
  return isinfl(d);
}

int isinff (float d)
{
  return isinfl(d);
}

#endif /* __NO_FLOAT */
