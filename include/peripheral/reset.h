/******************************************************************************
 *
 *                  RESET Library definitions
 *
 ******************************************************************************
 * FileName:        reset.h
 * Dependencies:
 * Processor:       PIC32MX family
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc..
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC32MX Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PIC32MX Microcontroller products.
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
 * $Id: reset.h,v 1.1 2006/11/27 16:47:07 C11842 Exp $
 *
 * $Name:  $
 *
 *****************************************************************************/

#ifndef _RESET_H_
#define _RESET_H_

#include <p32xxxx.h>
#include <peripheral/lock.h>



/******************************************************************************************************************************
  * <combinewith mGetBORFlag, mGetMCLRFlag, mGetSWRFlag, mGetWDTOFlag, mGetCMRFlag, mGetIDLEFlag, mGetSLEEPFlag, mGetVREGSFlag>
  * 
  * Prototype:
  *     mGetPORFlag(void) mGetBORFlag(void) mGetMCLRFlag(void)
  *     mGetWDTOFlag(void) mGetCMRFlag(void) mGetSWRFlag(void)
  *     mGetSLEEPFlag(void) mGetIDLEFlag(void) mGetVREGSFlag(void)
  * Description:
  *     RESET Status bit Macros
  *     
  *     These macros get/set their corresponding status bit
  * Preconditions:
  *     None
  * Return:
  *     The values returned are either '0' or a '1' in the respective
  *     status bit position.
  *     
  * Example:
  *     mGetPORFlag(); - This macro returns '0' or '1' (0x0001)
  *     mGetBORFlag(); - This macro returns '0' or '2' (0x0002)
  *     mGetWDTOFlag(); - This macro returns '0' or '8' (0x0008) ...
  *     mGetMCLRFlag(); - This macro returns '0' or '128' (0x0080)                                                             
  *****************************************************************************************************************************
*/
#define mGetPORFlag()                   (RCONbits.POR)
#define mGetBORFlag()                   (RCONbits.BOR)
#define mGetMCLRFlag()                  (RCONbits.EXTR)
#define mGetSWRFlag()                   (RCONbits.SWR)
#define mGetWDTOFlag()					(RCONbits.WDTO)
#define mGetCMRFlag()                   (RCONbits.CMR)
#define mGetSLEEPFlag()                 (RCONbits.SLEEP)
#define mGetIDLEFlag()                  (RCONbits.IDLE)
#define mGetVREGSFlag()                 (RCONbits.VREGS)


/*************************************************************************************************************************************************************
  * <combinewith mClearBORFlag, mClearCMRFlag, mClearIDLEFlag, mClearMCLRFlag, mClearSLEEPFlag, mClearSWRFlag, mClearVREGSFlag, mClearWDTOFlag, mSetVREGSFlag>
  * 
  * Prototype:
  *     mClearPORFlag() mClearBORFlag() mClearMCLRFlag()
  *     mClearSWRFlag() mClearWDTOFlag() mClearCMRFlag()
  *     mClearSLEEPFlag() mClearIDLEFlag() mClearVREGSFlag()
  *     mSetVREGSFlag()
  * Description:
  *     RESET Clear/Set Status Macros
  *     
  *     These macros clear/set their corresponding status bit
  * Preconditions:
  *     None
  * Return:
  *     None
  *     
  * Example:
  *     mClearMCLRFlag(); - This macro clears MCLR bit in RCON
  *     register                                                                                                                                              
  ************************************************************************************************************************************************************
*/
#define mClearPORFlag()					(RCONCLR = _RCON_POR_MASK)
#define mClearBORFlag()					(RCONCLR = _RCON_BOR_MASK)
#define mClearMCLRFlag()				(RCONCLR = _RCON_EXTR_MASK)
#define mClearSWRFlag()					(RCONCLR = _RCON_SWR_MASK)
#define mClearWDTOFlag()				(RCONCLR = _RCON_WDTO_MASK)
#define mClearCMRFlag()					(RCONCLR = _RCON_CMR_MASK)
#define mClearSLEEPFlag()				(RCONCLR = _RCON_SLEEP_MASK)
#define mClearIDLEFlag()				(RCONCLR = _RCON_IDLE_MASK)
#define mClearVREGSFlag()				(RCONCLR = _RCON_VREGS_MASK)
#define mSetVREGSFlag()					(RCONSET = _RCON_VREGS_MASK)

/******************************************************************************
 * Function:        	void SoftReset(void)
 *
 * Description:			software device reset
 *
 * PreCondition:    	None
 *
 * Inputs:				None
 *
 * Output:				None
 *
 * Example:				SoftReset();
 *
 * How it works:		The following steps are performed by this function:
 *						Step 1 - Execute "unlock" sequence to access the RSWRST register.
 *						Step 2 - Write a '1' to RSWRST.SWRST bit to arm the software reset.
 *						Step 3 - A Read of the RSWRST register must follow the write.  This
 *						action triggers the software reset, which should occur on the next
 *						clock cycle.
 * Note:				The read instruction must be following with either 4 nop
 *						instructions (fills the instruction pipe) or a while(1)loop to
 *						ensure no instructions can access the bus before reset occurs.
 *****************************************************************************/
void __attribute__((noreturn)) SoftReset(void);


/******************************************************************************
 * Check status of wakeup event
 *
 * Function:        isWU()
 *
 * Description:		Checks if wakeup from sleep was caused by MCLR, POR or BOR
 *					or interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			none
 *
 * Output:          Return codes:	0= no wake from sleep
 *									1 = wake from sleep due to interrupt
 *									2 = wake from sleep due to MCLR
 *									4 = wake from sleep due to BOR
 *
 * Example:			isWU();
 *
 *****************************************************************************/
char isWU(void);

/******************************************************************************
 * Reset POR event
 *
 * Function:        PORStatReset
 *
 * Description:		Clears POR event flag
 *
 * PreCondition:    None
 *
 * Inputs:			none
 *
 * Output:          None
 *
 * Example:			PORStatReset;
 *
 *****************************************************************************/
#define PORStatReset					mClearPORFlag()


/******************************************************************************
 * Reset BOR event
 *
 * Function:        BORStatReset
 *
 * Description:		Clears BOR event flag
 *
 * PreCondition:    None
 *
 * Inputs:			none
 *
 * Output:          None
 *
 * Example:			BORStatReset;
 *
 *****************************************************************************/
#define BORStatReset					mClearBORFlag()

/******************************************************************************
 * Checks to see if this was MCLR reset
 *
 * Function:        int isMCLR(void)
 *
 * Description:		Returns MCLR event occurred flag
 *
 * PreCondition:    None
 *
 * Inputs:			none
 *
 * Output:          '1' if MCLR ocurred,
 *					'0' otherwise
 *
 * Example:			isMCLR();
 *
 *****************************************************************************/
#define isMCLR()						mGetMCLRFlag()

/******************************************************************************
 * Checks to see if this was POR reset
 *
 * Function:        int isPOR(void)
 *
 * Description:		Returns POR event occurred flag
 *
 * PreCondition:    None
 *
 * Inputs:			none
 *
 * Output:          '1' if POR ocurred,
 *					'0' otherwise
 *
 * Example:			isPOR();
 *
 *****************************************************************************/
#define isPOR()							mGetMCLRFlag()


/******************************************************************************
 * Checks to see if this was BOR reset
 *
 * Function:        int isBOR(void)
 *
 * Description:		Returns BOR event occurred flag
 *
 * PreCondition:    None
 *
 * Inputs:			none
 *
 * Output:          '1' if BOR ocurred,
 *					'0' otherwise
 *
 * Example:			isBOR();
 *
 *****************************************************************************/
#define isBOR()							mGetBORFlag()


/******************************************************************************
 * Checks to see if this was LVD event
 *
 * Function:        int isLVD(void)
 *
 * Description:		Returns LVD event occurred flag
 *
 * PreCondition:    None
 *
 * Inputs:			none
 *
 * Output:          '1' if LVD ocurred,
 *					'0' otherwise
 *
 * Example:			isLVD();
 *
 *****************************************************************************/
#define isLVD()							0

/******************************************************************************
 * Checks to see if this was WDTO reset
 *
 * Function:        int isWDTO(void)
 *
 * Description:		Returns WDTO event occurred flag
 *
 * PreCondition:    None
 *
 * Inputs:			none
 *
 * Output:          '1' if WDTO ocurred,
 *					'0' otherwise
 *
 * Example:			isPOR();
 *
 *****************************************************************************/
#define isWDTTO()						(RCONbits.WDTO)


/******************************************************************************
 * Checks to see if this was WDT wakeup reset
 *
 * Function:        int isWDTWU(void)
 *
 * Description:		Returns WDT wakeup event occurred flag
 *
 * PreCondition:    None
 *
 * Inputs:			none
 *
 * Output:          '1' if WDT wakeup ocurred,
 *					'0' otherwise
 *
 * Example:			isPOR();
 *
 *****************************************************************************/
#define isWDTWU()						((RCONbits.WDTO ) && (RCONbits.SLEEP))

#endif  // _RESET_H_
