/*********************************************************************
 *
 *              Default _mon_getc Implementation
 *
 *********************************************************************
 * Filename:        _mon_getc.c
 *
 * Processor:       PIC32
 *
 * Compiler:        MPLAB C Compiler for PIC32 MCUs
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the Company) for its PIC32/PIC24F Microcontroller is intended
 * and supplied to you, the Companys customer, for use solely and
 * exclusively on Microchip PIC32/PIC24F Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN AS IS CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ********************************************************************/

extern int __XC_UART;
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

  if (__XC_UART == 0)
    {
      if (_appio_getc)
        return _appio_getc (canblock);
      if (_p32mxsk_getc)
        return _p32mxsk_getc (canblock);
    }
  else if (__XC_UART == 2)
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

