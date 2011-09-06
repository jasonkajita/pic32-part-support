/*********************************************************************
 *
 *                  SPI Legacy Library definitions
 *
 *********************************************************************
 * FileName:        rtcc_legacy.h
 * Dependencies:    p32xxxx.h
 * Processor:       PIC32
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc..
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC32 Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PIC32 Microcontroller products.
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
 * $Id: Rtcc.h,v 1.10 2007/01/16 20:30:43 C12878 Exp $
 * $Name:  $
 *
 ********************************************************************/


#ifndef _RTCC_LEGACY_H_
#define _RTCC_LEGACY_H_


#include <p32xxxx.h>
#include <peripheral/int.h>

/*****************************************************
 * 	Legacy RTCC functions
 * 	These functions are provided for backward compatibility only
 * 	They are no longer maintained!
 * 	New projects should not use them!
 *******************************************************/


/*****************************************
 *       Legacy Interrupt functions
 *       The functions in the int.h should be used instead.
 ***********************************************************/


/*********************************************************************
 * Function:        int mRtccGetIntFlag(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          TRUE		- if RTCC event
 * 					FALSE		- otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function reads the interrupt controller to check if the RTCC interrupt flag is set
 *
 * Note:            None.
 *
 * Example:			int isRtccIf=mRtccGetIntFlag();
 ********************************************************************/
#define		mRtccGetIntFlag()	(mRTCCGetIntFlag())

/*********************************************************************
 * Function:        void mRtccClrIntFlag(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function clears the RTCC event flag in the interrupt controller
 *
 * Note:            None.
 *
 * Example:			mRtccClrIntFlag();
 ********************************************************************/
#define		mRtccClrIntFlag()	(mRTCCClearIntFlag())

/*********************************************************************
 * Function:        void mRtccEnableInt(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function enables the RTCC event interrupts in the INT controller.
 *
 * Note:            None.
 *
 * Example:			mRtccEnableInt();
 ********************************************************************/
#define		mRtccEnableInt()		(mRTCCIntEnable(1))

/*********************************************************************
 * Function:        void mRtccDisableInt(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function disables the RTCC event interrupts in the INT controller.
 *
 * Note:            None.
 *
 * Example:			mRtccDisableInt();
 ********************************************************************/
#define		mRtccDisableInt()	(mRTCCIntEnable(0))


/*********************************************************************
 * Function:        int mRtccGetIntEnable(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          TRUE if the interrupts are enabled,
 * 					FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the status of the RTCC interrupts in the INT controller.
 *
 * Note:            None.
 *
 * Example:			int isRtccIntEnabled=mRtccGetIntEnable();
 ********************************************************************/
#define		mRtccGetIntEnable()	(mRTCCGetIntEnable())


/*********************************************************************
 * Function:        void mRtccSetIntPriority(int pri, int subPri)
 *
 * PreCondition:    pri		- valid priority value, 0-7
 * 					subPri	- valid sub priority value, 0-3
 *
 * Input:			pri			- the interrupt priority
 * 					subPri		- the interrupt subpriority
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function sets the RTCC event interrupt priority and subpriority in the interrupt controller.
 *
 * Note:            None.
 *
 * Example:			mRtccSetIntPriority(5, 3);
 ********************************************************************/
#define		mRtccSetIntPriority(pri, subPri)	(mRTCCSetIntPriority(pri), mRTCCSetIntSubPriority(subPri))


/*********************************************************************
 * Function:        int mRtccGetIntPriority(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          the current RTCC interrupt priority
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the RTCC event interrupt priority in the interrupt controller.
 *
 * Note:            None.
 *
 * Example:			int currPri=mRtccGetIntPriority();
 ********************************************************************/
#define		mRtccGetIntPriority()	(mRTCCGetIntPriority())

/*********************************************************************
 * Function:        int mRtccGetIntSubPriority(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          the current RTCC interrupt subpriority
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the RTCC event interrupt subpriority in the interrupt controller.
 *
 * Note:            None.
 *
 * Example:			int currSubPri=mRtccGetIntSubPriority();
 ********************************************************************/
#define		mRtccGetIntSubPriority()	(mRTCCGetIntSubPriority())


/*****************************************
 * Alarm and Time legacy functions
 * *******************************************************/

/*********************************************************************
 * Function:        unsigned long mRtccGetAlarmTime(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          the current alarm time
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current alarm time of the RTCC device.
 *
 * Note:            None
 *
 * Example:			rtccTime tm; tm.l=mRtccGetAlarmTime();
 ********************************************************************/
#define		mRtccGetAlarmTime	RtccGetAlarmTime

/*********************************************************************
 * Function:        unsigned long mRtccGetAlarmDate(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          The current alarm date. Can be safely cast into an rtccDate.
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current alarm date of the RTCC device.
 *
 * Note:            None
 *
 * Example:			rtccDate dt; dt.l=mRtccGetAlarmDate();
 ********************************************************************/
#define			mRtccGetAlarmDate	RtccGetAlarmDate

/*********************************************************************
 * Function:        int mRtccGetEnable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          the current enabled/disabled status of the RTCC module.
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the RTCCON.ON bit anded with RTCCLKON.
 *
 * Note:            None
 *
 * Example:			int isEnabled=mRtccGetEnable();
 ********************************************************************/
#define		mRtccGetEnable	RtccGetEnable

/*********************************************************************
 * Function:        int mRtccGetCalibration(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Current value of the RTCC calibration field.
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the value that the RTCC uses in the
 * 					auto-adjust feature, once every minute.
 * 					The calibration value is a signed 10 bits value, [-512, +511].
 *
 * Note:            None
 *
 * Example:			int currCal=mRtccGetCalibration();
 ********************************************************************/
#define			mRtccGetCalibration	RtccGetCalibration

/*********************************************************************
 * Function:        void mRtccWrEnable()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None.
 *
 * Side Effects:    None
 *
 * Overview:        The function/macro enables the updates to the RTCC
 * 					time registers and ON control bit.
 *
 * Note:            - The write can be enabled by performing a specific unlock sequence.
 * 					In order to succeed, this sequence need not be interrupted by other memory accesses
 * 					(DMA transfers, interrupts, etc).
 * 					- Interrupts and DMA transfers that might disrupt the write unlock sequence are disabled
 * 					shortly for properly unlocking the device.
 *
 * Example:			mRtccWrEnable();
 ********************************************************************/
#define		mRtccWrEnable()		RtccWrEnable(1)

/*********************************************************************
 * Function:        void mRtccWrDisable()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None.
 *
 * Side Effects:    None
 *
 * Overview:        The function disables further updates to the RTCC time registers and ON control bit.
 *
 *
 * Note:            None
 *
 * Example:			mRtccWrDisable();
 ********************************************************************/
#define		mRtccWrDisable()	RtccWrEnable(0)

/*********************************************************************
 * Function:        int mRtccGetWrEnable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if the RTCC is unlocked, FALSE if locked
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current status of the RTCC write enable bit.
 *
 * Note:            None
 *
 * Example:			int isWrEnabled=mRtccGetWrEnable();
 ********************************************************************/
#define		mRtccGetWrEnable	RtccGetWrEnable


/*********************************************************************
 * Function:        int mRtccGetSync(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if the SYNC signal is asserted, FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current status of the RTCCON SYNC bit.
 *
 * Note:            None
 *
 * Example:			int isSync=mRtccGetSync();
 ********************************************************************/
#define		mRtccGetSync		RtccGetSync


/*********************************************************************
 * Function:        int mRtccGetHalfSecond(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if the RTCC is in the second HALF SECOND  interval, FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current status of the RTCCON HALFSEC bit.
 *
 * Note:            None
 *
 * Example:			int is2HalfSec=mRtccGetHalfSecond();
 ********************************************************************/
#define		mRtccGetHalfSecond		RtccGetHalfSecond


/*********************************************************************
 * Function:        int mRtccGetAlrmSync(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if the AlrmSync signal is asserted, FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current status of the RTCALRM ALRMSYNC bit.
 *
 * Note:            None
 *
 * Example:			int isSync=mRtccGetAlrmSync();
 ********************************************************************/
#define		mRtccGetAlrmSync	RtccGetAlrmSync

/*********************************************************************
 * Function:        void mRtccSelectSecPulseOutput(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function selects the seconds clock pulse as the function of the RTCC output pin.
 *
 * Note:            The RTCC has to be enabled for the output to actually be active.
 *
 * Example:			mRtccSelectSecPulseOutput();
 ********************************************************************/
#define		mRtccSelectSecPulseOutput()	RtccSelectPulseOutput(1)

/*********************************************************************
 * Function:        void mRtccSelectAlarmPulseOutput(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function selects the alarm pulse as the function of the RTCC output pin.
 *
 * Note:            The RTCC has to be enabled for the output to actually be active.
 *
 * Example:			mRtccSelectAlarmPulseOutput();
 ********************************************************************/
#define		mRtccSelectAlarmPulseOutput()	RtccSelectPulseOutput(0)

/*********************************************************************
 * Function:        int mRtccGetAlarmPulse(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          the state of the Alarm Pulse .
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current state of the output Alarm Pulse.
 *
 * Note:            None
 *
 * Example:			int alrmPulse=mRtccGetAlarmPulse();
 ********************************************************************/
#define	mRtccGetAlarmPulse	RtccGetAlarmPulse

/*********************************************************************
 * Function:        void mRtccOutputEnable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function enables the Output pin of the RTCC.
 *
 * Note:            The RTCC has to be enabled for the output to actually be active.
 *
 * Example:			mRtccOutputEnable();
 ********************************************************************/
#define		mRtccOutputEnable()	RtccOutputEnable(1)

/*********************************************************************
 * Function:        void mRtccOutputDisable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function disables the Output pin of the RTCC.
 *
 * Note:            None
 *
 * Example:			mRtccOutputDisable();
 ********************************************************************/
#define		mRtccOutputDisable()	RtccOutputEnable(0)

/*********************************************************************
 * Function:        int mRtccGetOutputEnable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if Output is enabled, FALSE otherwise.
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the enabled/disabled status of the RTCC Output pin.
 *
 * Note:            None
 *
 * Example:			int isOutEnabled=mRtccGetOutputEnable();
 ********************************************************************/
#define		mRtccGetOutputEnable	RtccGetOutputEnable

// special purpose functions
/*********************************************************************
 * Function:        void mRtccFreezeEnable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function enables the FRZ status of the RTCC
 *
 * Note:            The FRZ bit reads always 0, unless in debug mode.
 *
 * Example:			mRtccFreezeEnable();
 ********************************************************************/
#define		mRtccFreezeEnable()	RtccFreezeEnable(1)

/*********************************************************************
 * Function:        void mRtccFreezeDisable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function disables the FRZ status of the RTCC
 *
 * Note:            The FRZ bit reads always 0, unless in debug mode.
 *
 * Example:			mRtccFreezeDisable();
 ********************************************************************/
#define		mRtccFreezeDisable()	RtccFreezeEnable(0)


/*********************************************************************
 * Function:        int mRtccGetFreeze(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if freeze mode enabled, FALSE if disabled
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the FRZ status of the RTCC
 *
 * Note:            The FRZ bit reads always 0, unless in debug mode.
 *
 * Example:			int isFrz=mRtccGetFreeze();
 ********************************************************************/
#define		mRtccGetFreeze		mRtccGetFreeze


#endif /*_RTCC_LEGACY_H_*/
