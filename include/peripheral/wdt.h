/*********************************************************************
 *
 *                  WDT API definitions
 *
 *********************************************************************
 * FileName:        WDT.h
 * Dependencies:
 * Processor:       PIC32
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
 * $Id: WDT.h,v 1.5 2006/10/27 16:52:16 C12532 Exp $
 *
 * $Name:  $
 ********************************************************************/

#ifndef WDT_H_
#define WDT_H_

#ifdef _WDT

#include <p32xxxx.h>

/*********************************************************************
 * Function:        EnableWDT()
 *
 * Description:     Enables the WDT
 *
 * PreCondition:    None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Example:         EnableWDT()
 *
 ********************************************************************/
#define EnableWDT() (WDTCONSET = _WDTCON_ON_MASK)


/*********************************************************************
 * Function:        DisableWDT()
 *
 * Description:     Disables the WDT
 *
 * PreCondition:    WDT must not be enabled by the device configuration
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Example:         DisableWDT()
 *
 ********************************************************************/
#define DisableWDT() (WDTCONCLR = _WDTCON_ON_MASK)


/*********************************************************************
 * Function:        ClearWDT()
 *
 * Description:     Resets the WDT
 *
 * PreCondition:    None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Example:         ClearWDT()
 *
 ********************************************************************/
#define ClearWDT() (WDTCONSET = _WDTCON_WDTCLR_MASK)


/*********************************************************************
 * Function:        ClearEventWDT()
 *
 * Description:     Clears the WDT event bit
 *
 * PreCondition:    None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Example:         ClearEventWDT()
 *
 ********************************************************************/
#define ClearEventWDT() ( RCONCLR = _RCON_WDTO_MASK)


/*********************************************************************
 * Function:        ReadEventWDT()
 *
 * Description:     Returns the state of the WDT event bit
 *
 * PreCondition:    None
 *
 * Inputs:          None
 *
 * Output:          State of the WDT event bit
 *
 * Example:         ReadEventWDT()
 *
 ********************************************************************/
#define ReadEventWDT() (RCONbits.WDTO)


/*********************************************************************
 * Function:        ReadPostscalerWDT()
 *
 * Description:     Returns the WDT prescaler value
 *
 * PreCondition:    None
 *
 * Inputs:          None
 *
 * Output:          The WDT Postscaler value
 *
 * Example:         ReadPostscalerWDT()
 *
 ********************************************************************/
#define ReadPostscalerWDT()  (WDTCONbits.WDTPSTA)

#endif /* _WDT */

#endif /*WDT_H_*/

