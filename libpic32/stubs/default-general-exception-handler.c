/*********************************************************************
 *
 *        Default General Exception Handler Implementation
 *
 *********************************************************************
 * Filename:        default-general-exception-handler.c
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
 * (the 'Company') for its PIC32/PIC24F Microcontroller is intended
 * and supplied to you, the Company's customer, for use solely and
 * exclusively on Microchip PIC32/PIC24F Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ********************************************************************/
/* This is a default definition of a general exception handler function.
 * It does nothing and just does a software reset. If the user
 * application supplies a handler function, this function will not be
 * referenced and thus not pulled in from the library.
 */
extern void __attribute__((nomips16, noreturn, far)) __pic32_software_reset();
void __attribute__((weak)) __exception_handler_break(void);
extern void _DEBUGGER  __attribute__((weak));

void 
__attribute__((weak, nomips16, noreturn)) _general_exception_handler (void)
{
  if (&_DEBUGGER != 0 && __exception_handler_break)
    __asm__ volatile ("sdbbp 0");
   
  __pic32_software_reset();
}

