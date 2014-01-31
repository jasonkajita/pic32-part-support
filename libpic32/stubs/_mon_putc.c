/*********************************************************************
 *
 *              Default _mon_putc Implementation
 *
 *********************************************************************
 * Filename:        _mon_putc.c
 *
 * Processor:       PIC32
 *
 * Compiler:        MPLAB XC32
 *                  MPLAB X IDE
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

  if (__XC_UART == 0)
    {
      if (_appio_putc)
        return _appio_putc (c);
      else if (_p32mxsk_putc)
        return _p32mxsk_putc (c);
    }
  else if (__XC_UART == 1)
    {
      ustatus = &U1STA;
      ustatusset = &U1STASET;
      umodeset = &U1MODESET;
      txreg = &U1TXREG;
    }
  else if (__XC_UART == 2)
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

