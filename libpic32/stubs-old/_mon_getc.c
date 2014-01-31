/*********************************************************************
 *
 *              Default _mon_getc Implementation
 *
 *********************************************************************
 * Filename:        _mon_getc.c
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
extern __attribute__ ((noinline,nomips16,weak)) int _appio_getc (int canblock);
extern __attribute__ ((noinline,nomips16,weak)) int _p32mxsk_getc (int canblock);

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

int __attribute__((weak))
_mon_getc (int canblock)
{
  int i;
  volatile unsigned int *umode = &U1MODE;
  volatile unsigned int *umodeset = &U1MODESET;
  volatile unsigned int *ustatus = &U1STA;
  volatile unsigned int *ustatusset = &U1STASET;
  volatile unsigned int *rxreg = &U1RXREG;
  volatile unsigned int *brg = &U1BRG;

  if (__C32_UART == 0)
    {
      if (_appio_getc)
        return _appio_getc (canblock);
      if (_p32mxsk_getc)
        return _p32mxsk_getc (canblock);
    }
  else if (__C32_UART == 2)
    {
      umode = &U2MODE;
      ustatus = &U2STA;
      rxreg = &U2RXREG;
      brg = &U2BRG;
    }
  if ((*umode & (1 << _U1MODE_UARTEN_POSITION)) == 0)
    {
      *umodeset = (1 << _U1MODE_UARTEN_POSITION);
    }
  {
    int nTimeout;

    /*
    ** Timeout is 16 cycles per 10-bit char
    */
    nTimeout = 16*10;
    while (((*ustatus & (1 << _U1STA_URXDA_POSITION)) == 0) && nTimeout) --nTimeout;
    return *rxreg;
  }

  return -1;
}

