/*********************************************************************
 *
 *              Default _mon_putc Implementation
 *
 *********************************************************************
 * Filename:        _mon_putc.c
 *
 * Dependency:      p32xxxx.h
 *
 * Processor:       PIC32
 *
 * Compiler:        chipKIT for PIC32 MCUs
 *
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * This software is developed by Microchip Technology Inc. and its
 * subsidiaries ("Microchip").
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1.      Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2.      Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3.      Microchip's name may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING BUT NOT LIMITED TO
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWSOEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *-------------------------------------------------------------------------*/

extern int __C32_UART;
extern __attribute__ ((noinline,nomips16,weak)) void _appio_putc (char c);
extern void __attribute__ ((noinline,nomips16,weak)) _p32mxsk_putc (char c);

#ifndef _U1MODE_UARTEN_POSITION
#define _U1MODE_UARTEN_POSITION                 0x0000000F
#endif

#ifndef _U1STA_UTXEN_POSITION
#define _U1STA_UTXEN_POSITION                   0x0000000A
#endif

#ifndef _U1STA_TRMT_POSITION
#define _U1STA_TRMT_POSITION                    0x00000008
#endif

#ifndef _U1STA_URXDA_POSITION
#define _U1STA_URXDA_POSITION                   0x00000000
#endif

extern volatile unsigned int U1MODE __attribute__((weak,section("sfrs")));
extern volatile unsigned int U1STA __attribute__((weak,section("sfrs")));
extern volatile unsigned int U1MODESET __attribute__((weak,section("sfrs")));
extern volatile unsigned int U1STASET __attribute__((weak,section("sfrs")));
extern volatile unsigned int U1RXREG __attribute__((weak,section("sfrs")));
extern volatile unsigned int U1TXREG __attribute__((weak,section("sfrs")));
extern volatile unsigned int U1BRG __attribute__((weak,section("sfrs")));

extern volatile unsigned int U2MODE __attribute__((weak,section("sfrs")));
extern volatile unsigned int U2STA __attribute__((weak,section("sfrs")));
extern volatile unsigned int U2MODESET __attribute__((weak,section("sfrs")));
extern volatile unsigned int U2STASET __attribute__((weak,section("sfrs")));
extern volatile unsigned int U2RXREG __attribute__((weak,section("sfrs")));
extern volatile unsigned int U2TXREG __attribute__((weak,section("sfrs")));
extern volatile unsigned int U2BRG __attribute__((weak,section("sfrs")));

/* THIS FUNCTION ASSUMES THE UART HAS ALREADY BEEN INITIALIZED */
/* Sends a character out on the UART */
void __attribute__((weak))
_mon_putc (char c)
{
  volatile unsigned int *ustatus = &U2STA;
  volatile unsigned int *umodeset = &U2MODESET;
  volatile unsigned int *ustatusset = &U2STASET;
  volatile unsigned int *txreg = &U2TXREG;

  if (__C32_UART == 0)
    {
      if (_appio_putc)
        return _appio_putc (c);
      else if (_p32mxsk_putc)
        return _p32mxsk_putc (c);
    }
  else if (__C32_UART == 1)
    {
      ustatus = &U1STA;
      ustatusset = &U1STASET;
      umodeset = &U2MODESET;
      txreg = &U1TXREG;
    }
  else if (__C32_UART == 2)
    {
#if 0
      ustatus = &U2STA;
      txreg = &U2TXREG;
#endif
    }
  *umodeset   = (1 << _U1MODE_UARTEN_POSITION);
  *ustatusset = (1 << _U1STA_UTXEN_POSITION);
  while ((*ustatus & (1 << _U1STA_TRMT_POSITION)) == 0);
  *txreg = c;
}

