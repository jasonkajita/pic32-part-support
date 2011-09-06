/*********************************************************************
 *
 *                  Power API definitions
 *
 *********************************************************************
 * FileName:        power.h
 * Dependencies:
 * Processor:     PIC32
 *
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc..
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PIC Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * $Id: OSC.h,v 1.6 2006/10/13 21:24:31 C12532 Exp $
 *
 * $Name:  $
 ********************************************************************/
#ifndef _POWER_HEADER_FILE
#define _POWER_HEADER_FILE

#include <p32xxxx.h>


/*********************************************************************
 * Function:        PowerSaveSleep()
 *
 * Description:	    Sets Powersave mode to Sleep and enters Sleep mode
 *
 * PreCondition:    None
 *
 * Inputs:	        None
 *
 * Output:          None
 *
 * Example:     	PowerSaveSleep()
 *
 ********************************************************************/
void __attribute__((nomips16)) PowerSaveSleep(void);



/*********************************************************************
 * Function:        PowerSaveIdle()
 *
 * Description:	    Sets Powersave mode to Idle and enters Idle mode
 *
 * PreCondition:    None
 *
 * Inputs:	        None
 *
 * Output:          None
 *
 * Example:	        PowerSaveIdle()
 *
 ********************************************************************/
void __attribute__((nomips16)) PowerSaveIdle(void);


#endif
