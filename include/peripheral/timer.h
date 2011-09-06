/******************************************************************************
 *
 *			PIC32MX Core and Peripheral Timer Library definitions
 *
 ******************************************************************************
 * FileName:        timer.h
 * Dependencies:
 * Processor:       PIC32MX family
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC32MX Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip Microcontroller products.
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
 * $Id: Timer.h,v 1.14 2006/11/27 18:35:04 C11842 Exp $
 * $Name:  $
 *
 *****************************************************************************/
#ifndef _TIMER_H_
#define _TIMER_H_

#include <p32xxxx.h>
#include <peripheral/int.h>

/*********************************************************************
 * Core Timer Control Interrupt Functions
 *
 * Function:        void OpenCoreTimer(unsigned int period)
 *
 * PreCondition:    None
 *
 * Inputs:			period - 32 bit value for the timer
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 ********************************************************************/
void __attribute__((nomips16)) OpenCoreTimer(unsigned int period);


/*********************************************************************
 * Core Timer
 *
 * Function:        void UpdateCoreTimer(unsigned int period)
 *
 * PreCondition:    None
 *
 * Inputs:			period - 32 bit value for the timer
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 ********************************************************************/
 void __attribute__((nomips16)) UpdateCoreTimer(unsigned int period);


/******************************************************************************
 * Function:        void ConfigIntCoreTimer(int config)
 *
 * Description:		Configures Core Timer  interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			config: Bit-wise OR value of CT_INT_XXX, CT_INT_PRIOR_XXX
 *							  and CT_INT_SUB_PRIOR_X
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 * Output:          None
 *
 * Example:			ConfigIntCoreTimer(CT_INT_ON | CT_INT_PRIOR_3 | CT_INT_SUB_PRIOR_1)
 *
 *****************************************************************************/
#define mConfigIntCoreTimer(config)      (mCTClearIntFlag(), mCTSetIntPriority(((config) & 7)),\
        mCTSetIntSubPriority((((config) >> 4) & 3)), mCTIntEnable(((config) >> 15)))

	/******************************************************************************
	 * Available options for config parameter. values are mutually exclusive.
	 *****************************************************************************/
		#define CT_INT_ON		            	(1 << 15)
		#define CT_INT_OFF						(0) // Coretimer Int off

		#define CT_INT_PRIOR_7                  (7) // Coretimer Int priority 7
		#define CT_INT_PRIOR_6                  (6) // Coretimer Int priority 6
		#define CT_INT_PRIOR_5                  (5) // Coretimer Int priority 5
		#define CT_INT_PRIOR_4                  (4) // Coretimer Int priority 4
		#define CT_INT_PRIOR_3                  (3) // Coretimer Int priority 3
		#define CT_INT_PRIOR_2                  (2) // Coretimer Int priority 2
		#define CT_INT_PRIOR_1                  (1) // Coretimer Int priority 1
		#define CT_INT_PRIOR_0                  (0) // Coretimer Int priority 0

		#define CT_INT_SUB_PRIOR_3              (3 << 4)  // Coretimer Int sub priority 3
		#define CT_INT_SUB_PRIOR_2              (2 << 4)  // Coretimer Int sub priority 2
		#define CT_INT_SUB_PRIOR_1              (1 << 4)  // Coretimer Int sub priority 1
		#define CT_INT_SUB_PRIOR_0              (0 << 4)  // Coretimer Int sub priority 0
	/***********************************
	 * End config parameter values
	 ************************************/


/******************************************************************************
 * Function:        EnableIntCoreTimer(void)
 *
 * Description:		Enables Core Timer interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			EnableIntCoreTimer()
 *****************************************************************************/
#define mEnableIntCoreTimer()            mCTIntEnable(1)


/******************************************************************************
 * Function:        DisableIntCoreTimer(void)
 *
 * Description:		Disables Core Timer interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			DisableIntCoreTimer()
 *****************************************************************************/
#define mDisableIntCoreTimer()           mCTIntEnable(0)

/******************************************************************************
 * Function:        void SetPriorityIntCoreTimer(int priority)
 *
 * Description:		Sets the priority for Core Timer interrupt
 *					The ConfigIntCoreTimer() sets the priority. Use this
 *					macro to change the previously set priority
 *					without any need to respecify other parameters.
 *
 * PreCondition:    None
 *
 * Inputs:			priority : A value of CT_INT_PRIOR_XXX
 *
 * Output:          None
 *
 *
 * Example:			SetPriorityIntCoreTimer(CT_INT_PRIORITY_3)
 *****************************************************************************/
#define mSetPriorityIntCoreTimer(priority)	mCTSetIntPriority(priority)

/******************************************************************************
 * Function:        unsigned int ReadCoreTimer(void)
 *
 * Description:		Returns the current Core Timer value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          Count value.
 *
 * Example:			ReadCoreTimer()
 *
 *****************************************************************************/
unsigned int __attribute__((nomips16)) ReadCoreTimer(void);


/******************************************************************************
 * Function:        void WriteCoreTimer(unsigned int value)
 *
 * Description:		Loads 32-bit value into CoreTimer.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WriteCoreTimer(0x1234)
 *
 *****************************************************************************/
void __attribute__((nomips16)) WriteCoreTimer(unsigned int timer);

/******************************************************************************
 * Function:        void CloseCoreTimer(void)
 *
 * Description:		Loads 32-bit value into CoreTimer.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WriteCoreTimer(0x1234)
 *
 *****************************************************************************/
#define CloseCoreTimer()        (mCTIntEnable(0))

#if defined _TMR1

/******************************************************************************
 * Function:        void OpenTimer1(unsigned int config, unsigned int period)
 *
 * Description:		Configures Timer 1
 *
 * PreCondition:    None
 *
 * Inputs:			config: Bit-wise OR value of T1_ON/OFF, T1_IDLE_XXX,
 *							T1_GATE_XXX, T1_PS_XXX, T1_SYC_EXT_XXX,
 *							T1_SOURCE_XXX.
 *					period: A value between 0 - 0xffff inclusive
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 * Output:          None
 *
 * Example:			OpenTimer1(T1_ON | T1_IDLE_ON | T1_PS_1_4, 123)
 *
 *****************************************************************************/
#define OpenTimer1(config, period)	(T1CON = ((config)&~(T1_ON)), TMR1 = 0, PR1 = (period), T1CONSET=((config)&(T1_ON)) )

/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// On/off control - values are mutually exclusive
		#define T1_ON	      	                (1 << _T1CON_ON_POSITION)	    /* Timer1 ON */
		#define T1_OFF							(0)

		// Stop-in-idle control - values are mutually exclusive
		#define T1_IDLE_STOP			        (1 << _T1CON_SIDL_POSITION)		/* stop during idle */
		#define T1_IDLE_CON						(0)								/* operate during idle */

		// Asynchronous write control - values are mutually exclusive
		#define T1_TMWDIS_ON 					(1 << _T1CON_TMWDIS_POSITION)	/* Asynchronous Write Disable */
		#define T1_TMWDIS_OFF					(0)

		// Timer gate control - values are mutually exclusive
		#define T1_GATE_ON		                (1 << _T1CON_TGATE_POSITION)	/* Timer Gate accumulation mode ON */
		#define T1_GATE_OFF						(0)

		// Timer prescaler control - values are mutually exclusive
		#define T1_PS_1_256                     (3 << _T1CON_TCKPS_POSITION)    /* Prescaler 1:256 */
		#define T1_PS_1_64                      (2 << _T1CON_TCKPS_POSITION)    /*           1:64 */
		#define T1_PS_1_8                       (1 << _T1CON_TCKPS_POSITION)    /*           1:8 */
		#define T1_PS_1_1                       (0)								/*           1:1 */

		// Sync option - values are mutually exclusive
		#define T1_SYNC_EXT_ON                  (1 << _T1CON_TSYNC_POSITION)    /* Synch external clk input */
		#define T1_SYNC_EXT_OFF					(0)

		// Source selection - values are mutually exclusive
		#define T1_SOURCE_EXT                   (1 << _T1CON_TCS_POSITION)      /* External clock source */
		#define T1_SOURCE_INT					(0)								/* Internal clock source */
	/***********************************
	 * End config parameter values
	 ************************************/


/******************************************************************************
 * Function:        CloseTimer1()
 *
 * Description:		Switches off the Timer1
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			CloseTimer1()
 *
 *****************************************************************************/
#define CloseTimer1()	(mT1IntEnable(0), T1CON = 0)


/******************************************************************************
 * Function:        void ConfigIntTimer1(unsigned int config)
 *
 * Description:		Configures Timer 1 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			config: Bit-wise OR value of T1_INT_XXX, T1_INT_PRIOR_XXX
 *							  and T1_INT_SUB_PRIOR_X
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 * Output:          None
 *
 * Example:			ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_3 | T1_INT_SUB_PRIOR1)
 *
 *****************************************************************************/
#define ConfigIntTimer1(config) (mT1ClearIntFlag(), mT1SetIntPriority((config) & 7),\
        mT1SetIntSubPriority(((config) >> 4) & 3), mT1IntEnable((config) >> 15))


	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// Interrupt on/off - values are mutually exclusive
		#define T1_INT_ON		            	(1 << 15)
		#define T1_INT_OFF						(0)

		// Interrupt priority - values are mutually exclusive
		#define T1_INT_PRIOR_7                  (7) // Timer int priority 7
		#define T1_INT_PRIOR_6                  (6) // Timer int priority 6
		#define T1_INT_PRIOR_5                  (5) // Timer int priority 5
		#define T1_INT_PRIOR_4                  (4) // Timer int priority 4
		#define T1_INT_PRIOR_3                  (3) // Timer int priority 3
		#define T1_INT_PRIOR_2                  (2) // Timer int priority 2
		#define T1_INT_PRIOR_1                  (1) // Timer int priority 1
		#define T1_INT_PRIOR_0                  (0) // Timer int priority 0

		// Interrupt sub-priority - values are mutually exclusive
		#define T1_INT_SUB_PRIOR_3              (3 << 4) // Timer int sub priority 3
		#define T1_INT_SUB_PRIOR_2              (2 << 4) // Timer int sub priority 2
		#define T1_INT_SUB_PRIOR_1              (1 << 4) // Timer int sub priority 1
		#define T1_INT_SUB_PRIOR_0              (0 << 4) // Timer int sub priority 0
	/***********************************
	 * End config parameter values
	 ************************************/



/******************************************************************************
 * Function:        EnableIntT1
 *
 * Description:		Enables Timer1 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			EnableIntT1()
 *****************************************************************************/
#define EnableIntT1					mT1IntEnable(1)


/******************************************************************************
 * Function:        DisableIntT1
 *
 * Description:		Disables Timer1 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			DisableIntT1()
 *****************************************************************************/
#define DisableIntT1				mT1IntEnable(0)


/******************************************************************************
 * Function:        void SetPriorityIntT1(int priority)
 *
 * Description:		Sets the priority for Timer 1 interrupt
 *					The OpenTimerx() sets the priority. Use this
 *					macro to change the previously set priority
 *					without any need to respecify other parameters.
 *
 * PreCondition:    None
 *
 * Inputs:			priority : A value of T1_INT_PRIOR_XXX
 *
 * Output:          None
 *
 *
 * Example:			SetPriorityIntT1(T1_INT_PRIORITY_3)
 *****************************************************************************/
#define SetPriorityIntT1(priority)	mT1SetIntPriority((priority))


/******************************************************************************
 * Function:        unsigned int ReadTimer1(void)
 *
 * Description:		Returns the current Timer1 value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          TMR1 value.
 *
 * Example:			ReadTimer1()
 *
 *****************************************************************************/
#define ReadTimer1()	(TMR1)


/******************************************************************************
 * Function:        void WriteTimer1(unsigned int value)
 *
 * Description:		Loads given value into Timer1 register.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WriteTimer1(1234)
 *
 *****************************************************************************/
#define WriteTimer1(value)	TMR1 = ((value))


/******************************************************************************
 * Function:        unsigned int ReadPeriod1(void)
 *
 * Description:		Returns the current Period1 value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          PR1 value.
 *
 * Example:			ReadPeriod1()
 *
 *****************************************************************************/
#define ReadPeriod1()	(PR1)


/******************************************************************************
 * Function:        void WritePeriod1(unsigned int value)
 *
 * Description:		Loads given value into Period1 register.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WritePeriod1(1234)
 *
 *****************************************************************************/
#define WritePeriod1(value)	PR1 = ((value))

#endif		// _TMR1

#if defined _TMR2

/******************************************************************************
 * Function:        void OpenTimer2(unsigned int config, unsigned int period)
 *
 * Description:		Configures Timer 2
 *
 * PreCondition:    None
 *
 * Inputs:			config: Bit-wise OR value of T2_ON/OFF, T2_IDLE_XXX,
 *							T2_GATE_XXX, T1_PS_XXX, T2_32BIT_MODE_ON, and
 *							T2_SOURCE_XXX.
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 *					period: A value between 0 - 0xffff inclusive
 *
 * Output:          None
 *
 * Example:			OpenTimer2(T2_ON | T2_IDLE_ON | T2_PS_1_4, 123)
 *
 *****************************************************************************/
#define OpenTimer2(config, period)	(T2CON = ((config)&~(T2_ON)), TMR2 = 0, PR2 = (period), T2CONSET=((config)&(T2_ON)) )

	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// On/off control - values are mutually exclusive
		#define T2_ON                           (1 << _T2CON_ON_POSITION)		/* Timer2 ON */
		#define T2_OFF							(0)

		// Stop-in-idle control - values are mutually exclusive
		#define T2_IDLE_STOP                    (1 << _T2CON_SIDL_POSITION)		/* stop during idle */
		#define T2_IDLE_CON 					(0)								/* operate during idle */

		// Timer gate control - values are mutually exclusive
		#define T2_GATE_ON                      (1 << _T2CON_TGATE_POSITION)	/* Timer Gate accumulation mode ON */
		#define T2_GATE_OFF						(0)

		// Prescale values - values are mutually exclusive
		#define T2_PS_1_256                     (7 << _T2CON_TCKPS_POSITION)    /* Prescaler 1:256 */
		#define T2_PS_1_64                      (6 << _T2CON_TCKPS_POSITION)    /*           1:64 */
		#define T2_PS_1_32                      (5 << _T2CON_TCKPS_POSITION)    /*           1:32 */
		#define T2_PS_1_16                      (4 << _T2CON_TCKPS_POSITION)    /*           1:16 */
		#define T2_PS_1_8                       (3 << _T2CON_TCKPS_POSITION)    /*           1:8 */
		#define T2_PS_1_4                       (2 << _T2CON_TCKPS_POSITION)    /*           1:4 */
		#define T2_PS_1_2                       (1 << _T2CON_TCKPS_POSITION)    /*           1:2 */
		#define T2_PS_1_1                       (0)								/*           1:1 */

		// 32-bit or 16-bit - values are mutually exclusive
		#define T2_32BIT_MODE_ON                (1 << _T2CON_T32_POSITION)      /* Enable 32-bit mode */
		#define T2_32BIT_MODE_OFF				(0)

		// Sync external clock option - values are mutually exclusive
		#define T2_SOURCE_EXT                   (1 << _T2CON_TCS_POSITION)      /* External clock source */
		#define T2_SOURCE_INT					(0)								/* Internal clock source */
	/***********************************
	 * End config parameter values
	 ************************************/


/******************************************************************************
 * Function:        CloseTimer2()
 *
 * Description:		Switches off the Timer2
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			CloseTimer2()
 *
 *****************************************************************************/
#define CloseTimer2()	(mT2IntEnable(0), T2CON = 0)


/******************************************************************************
 * Function:        void ConfigIntTimer2(unsigned int config)
 *
 * Description:		Configures Timer 2 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			priority: Bit-wise OR value of T2_INT_XXX, T2_INT_PRIOR_XXX
 *							  and T2_INT_SUB_PRIOR_X
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 * Output:          None
 *
 * Example:			ConfigIntTimer2(T2_INT_ON | T2_INT_PRIOR_3 | T2_INT_SUB_PRIOR1)
 *
 *****************************************************************************/
#define ConfigIntTimer2(config) (mT2ClearIntFlag(), mT2SetIntPriority(((config) & 7)),\
        mT2SetIntSubPriority(((config) >> 4) & 3), mT2IntEnable((config) >> 15))

	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// Interrupt on/off - values are mutually exclusive
		#define T2_INT_ON			            (1 << 15)		/* T2 Interrupt Enable */
		#define T2_INT_OFF						(0)

		// Interrupt priority - values are mutually exclusive
		#define T2_INT_PRIOR_7                  (7)
		#define T2_INT_PRIOR_6                  (6)
		#define T2_INT_PRIOR_5                  (5)
		#define T2_INT_PRIOR_4                  (4)
		#define T2_INT_PRIOR_3                  (3)
		#define T2_INT_PRIOR_2                  (2)
		#define T2_INT_PRIOR_1                  (1)
		#define T2_INT_PRIOR_0                  (0)

		// Interrupt sub-priority - values are mutually exclusive
		#define T2_INT_SUB_PRIOR_3              (3 << 4)
		#define T2_INT_SUB_PRIOR_2              (2 << 4)
		#define T2_INT_SUB_PRIOR_1              (1 << 4)
		#define T2_INT_SUB_PRIOR_0              (0 << 4)
	/***********************************
	 * End config parameter values
	 ************************************/



/******************************************************************************
 * Function:        EnableIntT2
 *
 * Description:		Enables Timer2 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			EnableIntT2()
 *****************************************************************************/
#define EnableIntT2					mT2IntEnable(1)


/******************************************************************************
 * Function:        DisableIntT2
 *
 * Description:		Disables Timer2 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			DisableIntT2()
 *****************************************************************************/
#define DisableIntT2				mT2IntEnable(0)


/******************************************************************************
 * Function:        void SetPriorityIntT2(int priority)
 *
 * Description:		Sets the priority for Timer 2 interrupt
 *					The OpenTimerx() sets the priority. Use this
 *					macro to change the previously set priority
 *					without any need to respecify other parameters.
 *
 * PreCondition:    None
 *
 * Inputs:			priority : A value of T2_INT_PRIOR_XXX
 *
 * Output:          None
 *
 * Example:			SetPriorityIntT2(T2_INT_PRIORITY_3)
 *****************************************************************************/
#define SetPriorityIntT2(priority)	mT2SetIntPriority((priority))


/******************************************************************************
 * Function:        unsigned int ReadTimer2(void)
 *
 * Description:		Returns the current Timer2 value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          TMR2 value.
 *
 * Example:			ReadTimer2()
 *
 *****************************************************************************/
#define ReadTimer2()	(TMR2)


/******************************************************************************
 * Function:        void WriteTimer2(unsigned int value)
 *
 * Description:		Loads given value into Timer2 register.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WriteTimer2(1234)
 *
 *****************************************************************************/
#define WriteTimer2(value)	TMR2 = (value)


/******************************************************************************
 * Function:        unsigned int ReadPeriod2(void)
 *
 * Description:		Returns the current Period2 value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          PR2 value.
 *
 * Example:			ReadPeriod2()
 *
 *****************************************************************************/
#define ReadPeriod2()	(PR2)


/******************************************************************************
 * Function:        void WritePeriod2(unsigned int value)
 *
 * Description:		Loads given value into Period2 register.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WritePeriod2(1234)
 *
 *****************************************************************************/
#define WritePeriod2(value)	PR2 = ((value))



#endif	// _TMR2


#if defined _TMR3

/******************************************************************************
 * Function:        void OpenTimer3(unsigned int config, unsigned int period)
 *
 * Description:		Configures Timer 3
 *
 * PreCondition:    None
 *
 * Inputs:			config: Bit-wise OR value of T3_ON/OFF, T3_IDLE_XXX,
 *							T3_GATE_XXX, T3_PS_XXX, T3_SOURCE_XXX.
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 *					period: A value between 0 - 0xffff inclusive
 *
 * Output:          None
 *
 * Example:			OpenTimer3(T3_ON | T3_IDLE_ON | T3_PS_1_4, 123)
 *
 *****************************************************************************/
#define OpenTimer3(config, period)	(T3CON = ((config)&~(T3_ON)), TMR3 = 0, PR3 = (period), T3CONSET=((config)&(T3_ON)) )

	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// On/off control - values are mutually exclusive
		#define T3_ON                           (1 << _T3CON_ON_POSITION)		/* Timer3 ON */
		#define T3_OFF							(0)

		// Stop-in-idle control - values are mutually exclusive
		#define T3_IDLE_STOP                    (1 << _T3CON_SIDL_POSITION)		/* stop during idle */
		#define T3_IDLE_CON 					(0)								/* operate during idle */

		// Timer gate control - values are mutually exclusive
		#define T3_GATE_ON                      (1 << _T3CON_TGATE_POSITION)	/* Timer Gate accumulation mode ON */
		#define T3_GATE_OFF						(0)

		// Timer prescaler control - values are mutually exclusive
		#define T3_PS_1_256                     (7 << _T3CON_TCKPS_POSITION)    /* Prescaler 1:256 */
		#define T3_PS_1_64                      (6 << _T3CON_TCKPS_POSITION)    /*           1:64 */
		#define T3_PS_1_32                      (5 << _T3CON_TCKPS_POSITION)    /*           1:32 */
		#define T3_PS_1_16                      (4 << _T3CON_TCKPS_POSITION)    /*           1:16 */
		#define T3_PS_1_8                       (3 << _T3CON_TCKPS_POSITION)    /*           1:8 */
		#define T3_PS_1_4                       (2 << _T3CON_TCKPS_POSITION)    /*           1:4 */
		#define T3_PS_1_2                       (1 << _T3CON_TCKPS_POSITION)    /*           1:2 */
		#define T3_PS_1_1                       (0)								/*           1:1 */

		// Source selection - values are mutually exclusive
		#define T3_SOURCE_EXT                   (1 << _T3CON_TCS_POSITION)      /* External clock source */
		#define T3_SOURCE_INT					(0)								/* Internal clock source */
	/***********************************
	 * End config parameter values
	 ************************************/



/******************************************************************************
 * Function:        CloseTimer3()
 *
 * Description:		Switches off the Timer3
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			CloseTimer3()
 *
 *****************************************************************************/
#define CloseTimer3()   (mT3IntEnable(0), T3CON = 0)



/******************************************************************************
 * Function:        void ConfigIntTimer3(unsigned int config)
 *
 * Description:		Configures Timer 3 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			config: Bit-wise OR value of T3_INT_XXX, T3_INT_PRIOR_XXX
 *							  and T3_INT_SUB_PRIOR_X
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 * Output:          None
 *
 * Example:			ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_3 | T3_INT_SUB_PRIOR1)
 *
 *****************************************************************************/
#define ConfigIntTimer3(config) (mT3ClearIntFlag(), mT3SetIntPriority(((config) & 7)),\
        mT3SetIntSubPriority(((config) >> 4) & 3), mT3IntEnable((config) >> 15))

	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// Interrupt on/off - values are mutually exclusive
		#define T3_INT_ON			            (1<<15)		/* Interrupt Enable */
		#define T3_INT_OFF						(0)

		// Interrupt priority - values are mutually exclusive
		#define T3_INT_PRIOR_7                  (7)
		#define T3_INT_PRIOR_6                  (6)
		#define T3_INT_PRIOR_5                  (5)
		#define T3_INT_PRIOR_4                  (4)
		#define T3_INT_PRIOR_3                  (3)
		#define T3_INT_PRIOR_2                  (2)
		#define T3_INT_PRIOR_1                  (1)
		#define T3_INT_PRIOR_0                  (0)

		// Interrupt sub-priority - values are mutually exclusive
		#define T3_INT_SUB_PRIOR_3              (3 << 4)
		#define T3_INT_SUB_PRIOR_2              (2 << 4)
		#define T3_INT_SUB_PRIOR_1              (1 << 4)
		#define T3_INT_SUB_PRIOR_0              (0 << 4)
	/***********************************
	 * End config parameter values
	 ************************************/


/******************************************************************************
 * Function:        EnableIntT3()
 *
 * Description:		Enables Timer3 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			EnableIntT3()
 *****************************************************************************/
#define EnableIntT3					mT3IntEnable(1)


/******************************************************************************
 * Function:        DisableIntT3
 *
 * Description:		Disables Timer3 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			DisableIntT3()
 *****************************************************************************/
#define DisableIntT3				mT3IntEnable(0)


/******************************************************************************
 * Function:        void SetPriorityIntT3(unsigned int priority)
 *
 * Description:		Sets the priority for Timer 3 interrupt
 *					The OpenTimerx() sets the priority. Use this
 *					macro to change the previously set priority
 *					without any need to respecify other parameters.
 *
 * PreCondition:    None
 *
 * Inputs:			priority : A value of T3_INT_PRIOR_XXX
 *
 * Output:          None
 *
 * Example:			SetPriorityIntT3(T3_INT_PRIORITY_3)
 *****************************************************************************/
#define SetPriorityIntT3(priority)	mT3SetIntPriority((priority))


/******************************************************************************
 * Function:        unsigned int ReadTimer3(void)
 *
 * Description:		Returns the current Timer3 value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          TMR3 value.
 *
 * Example:			ReadTimer3()
 *
 *****************************************************************************/
#define ReadTimer3()	(TMR3)


/******************************************************************************
 * Function:        void WriteTimer3(unsigned int value)
 *
 * Description:		Loads given value into Timer3 register.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WriteTimer3(1234)
 *
 *****************************************************************************/
#define WriteTimer3(value)	TMR3 = (value)


/******************************************************************************
 * Function:        unsigned int ReadPeriod3(void)
 *
 * Description:		Returns the current Period3 value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          PR3 value.
 *
 * Example:			ReadPeriod3()
 *
 *****************************************************************************/
#define ReadPeriod3()	(PR3)


/******************************************************************************
 * Function:        void WritePeriod3(unsigned int value)
 *
 * Description:		Loads given value into Period3 register.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WritePeriod3(1234)
 *
 *****************************************************************************/
#define WritePeriod3(value)	PR3 = ((value))



/******************************************************************************
 * Function:        void OpenTimer23(unsigned int config, unsigned int period)
 *
 * Description:		Configures Timer 23 - A 32-bit time by pairing
 *					Timer 2 & 3.
 *
 * PreCondition:    None
 *
 * Inputs:			config: Bit-wise OR value of T2_ON/OFF, T2_IDLE_XXX,
 *							T2_GATE_XXX, T2_PS_XXX, T2_SOURCE_XXX.
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 *					period: A value between 0 - 0xffffffff inclusive
 *
 * Output:          None
 *
 * Example:			OpenTimer23(T2_ON | T2_IDLE_ON | T2_PS_1_4, 123)
 *****************************************************************************/
#define OpenTimer23(config, period) \
( OpenTimer2((config) | T2_32BIT_MODE_ON, (period)))

/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// On/off control - values are mutually exclusive
		#define T23_ON                          (1 << _T2CON_ON_POSITION)		/* Timer2 ON */
		#define T23_OFF							(0)

		// Stop-in-idle control - values are mutually exclusive
		#define T23_IDLE_STOP                   (1 << _T2CON_SIDL_POSITION)		/* stop during idle */
		#define T23_IDLE_CON					(0)								/* operate during idle */

		// Timer gate control - values are mutually exclusive
		#define T23_GATE_ON                     (1 << _T2CON_TGATE_POSITION)	/* Timer Gate accumulation mode ON */
		#define T23_GATE_OFF					(0)

		// Prescale values - values are mutually exclusive
		#define T23_PS_1_256                    (7 << _T2CON_TCKPS_POSITION)    /* Prescaler 1:256 */
		#define T23_PS_1_64                     (6 << _T2CON_TCKPS_POSITION)    /*           1:64 */
		#define T23_PS_1_32                     (5 << _T2CON_TCKPS_POSITION)    /*           1:32 */
		#define T23_PS_1_16                     (4 << _T2CON_TCKPS_POSITION)    /*           1:16 */
		#define T23_PS_1_8                      (3 << _T2CON_TCKPS_POSITION)    /*           1:8 */
		#define T23_PS_1_4                      (2 << _T2CON_TCKPS_POSITION)    /*           1:4 */
		#define T23_PS_1_2                      (1 << _T2CON_TCKPS_POSITION)    /*           1:2 */
		#define T23_PS_1_1                      (0)								/*           1:1 */

		// 32-bit or 16-bit - values are mutually exclusive
		#define T23_32BIT_MODE_ON               (1 << _T2CON_T32_POSITION)      /* Enable 32-bit mode */
		#define T23_32BIT_MODE_OFF				(0)

		// Sync external clock option - values are mutually exclusive
		#define T23_SOURCE_EXT                  (1 << _T2CON_TCS_POSITION)      /* External clock source */
		#define T23_SOURCE_INT					(0)								/* Internal clock source */
	/***********************************
	 * End config parameter values
	 ************************************/

/******************************************************************************
 * Function:        CloseTimer23()
 *
 * Description:		Switches off the 32-bit Timer23
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			CloseTimer23()
 *
 *****************************************************************************/
#define CloseTimer23()	(CloseTimer2(), CloseTimer3())


/******************************************************************************
 * Function:        void ConfigIntTimer23(unsigned int config)
 *
 * Description:		Configures the 32-bit Timer23 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			priority: Bit-wise OR value of T23_INT_XXX, T23_INT_PRIOR_XXX
 *							  and T23_INT_SUB_PRIOR_X
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 * Output:          None
 *
 * Example:			ConfigIntTimer23(T23_INT_ON | T23_INT_PRIOR_3 | T23_INT_SUB_PRIOR1)
 *
 *****************************************************************************/
#define ConfigIntTimer23(config)	ConfigIntTimer3((config))

	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// Interrupt on/off - values are mutually exclusive
		#define T23_INT_ON			            (1<<15)		/* Interrupt Enable */
		#define T23_INT_OFF						(0)

		// Interrupt priority - values are mutually exclusive
		#define T23_INT_PRIOR_7                  (7)
		#define T23_INT_PRIOR_6                  (6)
		#define T23_INT_PRIOR_5                  (5)
		#define T23_INT_PRIOR_4                  (4)
		#define T23_INT_PRIOR_3                  (3)
		#define T23_INT_PRIOR_2                  (2)
		#define T23_INT_PRIOR_1                  (1)
		#define T23_INT_PRIOR_0                  (0)

		// Interrupt sub-priority - values are mutually exclusive
		#define T23_INT_SUB_PRIOR_3              (3 << 4)
		#define T23_INT_SUB_PRIOR_2              (2 << 4)
		#define T23_INT_SUB_PRIOR_1              (1 << 4)
		#define T23_INT_SUB_PRIOR_0              (0 << 4)
	/***********************************
	 * End config parameter values
	 ************************************/



/******************************************************************************
 * Function:        EnableIntT23()
 *
 * Description:		Enables the 32-bit Timer23 interrupt(Timer3 interrupt)
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			EnableIntT23()
 *****************************************************************************/
#define EnableIntT23				EnableIntT3


/******************************************************************************
 * Function:        DisableIntT23
 *
 * Description:		Disables 32-bit Timer23 interrupt(Timer3 interrupt)
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			DisableIntT23()
 *****************************************************************************/
#define DisableIntT23				DisableIntT3


/******************************************************************************
 * Function:        void SetPriorityIntT23(unsigned int priority)
 *
 * Description:		Sets the priority for 32-bit Timer 23 interrupt
 *					The OpenTimerx() sets the priority. Use this
 *					macro to change the previously set priority
 *					without any need to respecify other parameters.
 *                  Interrupts are Timer3.
 *

 * PreCondition:    None
 *
 * Inputs:			priority : A value of T2_INT_PRIOR_XXX
 *
 * Output:          None
 *
 * Example:			SetPriorityIntT23(T2_INT_PRIORITY_3)
 *****************************************************************************/
#define SetPriorityIntT23(priority)	SetPriorityIntT3((priority))


/******************************************************************************
 * Function:        unsigned int ReadTimer23(void)
 *
 * Description:		Returns the current 32-bit Timer23 value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          The current 32-bit timer value.
 *
 * Example:			ReadTimer23()
 *
 *****************************************************************************/
#define ReadTimer23()	ReadTimer2()


/******************************************************************************
 * Function:        void WriteTimer23(unsigned int value)
 *
 * Description:		Loads given value into 32-bit Timer23 register.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WriteTimer23(1234)
 *
 *****************************************************************************/
#define WriteTimer23(value)	WriteTimer2((value))


/******************************************************************************
 * Function:        unsigned int ReadPeriod23(void)
 *
 * Description:		Returns the current Period23 value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          PR2 value.
 *
 * Example:			ReadPeriod23()
 *
 *****************************************************************************/
#define ReadPeriod23()	(PR2)


/******************************************************************************
 * Function:        void WritePeriod23(unsigned int value)
 *
 * Description:		Loads given value into Period23 register.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WritePeriod23(1234)
 *
 *****************************************************************************/
#define WritePeriod23(value)	PR2 = (value)



#endif // _TMR3


#if defined _TMR4

/******************************************************************************
 * Function:        void OpenTimer4(unsigned int config, unsigned int period)
 *
 * Description:		Configures Timer 4
 *
 * PreCondition:    None
 *
 * Inputs:			config: Bit-wise OR value of T4_ON/OFF, T4_IDLE_XXX,
 *							T4_GATE_XXX, T4_PS_XXX, T4_32BIT_MODE_ON, and
 *							T4_SOURCE_XXX.
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 *					period: A value between 0 - 0xffff inclusive
 *
 * Output:          None
 *
 * Example:			OpenTimer4(T4_ON | T4_IDLE_ON | T4_PS_1_4, 123)
 *
 *****************************************************************************/
#define OpenTimer4(config, period)	(T4CON = ((config)&~(T4_ON)), TMR4 = 0, PR4 = (period), T4CONSET=((config)&(T4_ON)) )

	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// On/off control - values are mutually exclusive
		#define T4_ON                           (1 << _T4CON_ON_POSITION)		/* Timer4 ON */
		#define T4_OFF							(0)

		// Stop-in-idle control - values are mutually exclusive
		#define T4_IDLE_STOP                    (1 << _T4CON_SIDL_POSITION)		/* stop during idle */
		#define T4_IDLE_CON						(0)								/* operate during idle */
        
		// Timer gate control - values are mutually exclusive
		#define T4_GATE_ON                      (1 << _T4CON_TGATE_POSITION)	/* Timer Gate accumulation mode ON */
		#define T4_GATE_OFF						(0)

		// Timer prescaler control - values are mutually exclusive
		#define T4_PS_1_256                     (7 << _T4CON_TCKPS_POSITION)    /* Prescaler 1:256 */
		#define T4_PS_1_64                      (6 << _T4CON_TCKPS_POSITION)    /*           1:64 */
		#define T4_PS_1_32                      (5 << _T4CON_TCKPS_POSITION)    /*           1:32 */
		#define T4_PS_1_16                      (4 << _T4CON_TCKPS_POSITION)    /*           1:16 */
		#define T4_PS_1_8                       (3 << _T4CON_TCKPS_POSITION)    /*           1:8 */
		#define T4_PS_1_4                       (2 << _T4CON_TCKPS_POSITION)    /*           1:4 */
		#define T4_PS_1_2                       (1 << _T4CON_TCKPS_POSITION)    /*           1:2 */
		#define T4_PS_1_1                       (0)								/*           1:1 */

		// 32-bit or 16-bit option - values are mutually exclusive
		#define T4_32BIT_MODE_ON                (1 << _T4CON_T32_POSITION)      /* Enable 32-bit mode */
		#define T4_32BIT_MODE_OFF				(0)

		// Source selection - values are mutually exclusive
		#define T4_SOURCE_EXT                   (1 << _T4CON_TCS_POSITION)      /* External clock source */
		#define T4_SOURCE_INT					(0)								/* Internal clock source */
	/***********************************
	 * End config parameter values
	 ************************************/


/******************************************************************************
 * Function:        void CloseTimer4(void)
 *
 * Description:		Switches off the Timer4
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			CloseTimer4()
 *
 *****************************************************************************/
#define CloseTimer4()	(mT4IntEnable(0), T4CON = 0x0)



/******************************************************************************
 * Function:        void ConfigIntTimer4(unsigned int config)
 *
 * Description:		Configures Timer 4 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			priority: Bit-wise OR value of T4_INT_XXX, T4_INT_PRIOR_XXX
 *							  and T4_INT_SUB_PRIOR_X
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 * Output:          None
 *
 * Example:			ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_3 | T4_INT_SUB_PRIOR1)
 *
 *****************************************************************************/
#define ConfigIntTimer4(config) (mT4ClearIntFlag(), mT4SetIntPriority((config) & 7), \
        mT4SetIntSubPriority(((config) >> 4) & 3),  mT4IntEnable((config) >> 15))


	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// Interrupt on/off - values are mutually exclusive
		#define T4_INT_ON			            (1<<15)		/* Interrupt Enable */
		#define T4_INT_OFF						(0)

		// Interrupt priority - values are mutually exclusive
		#define T4_INT_PRIOR_7                  (7)
		#define T4_INT_PRIOR_6                  (6)
		#define T4_INT_PRIOR_5                  (5)
		#define T4_INT_PRIOR_4                  (4)
		#define T4_INT_PRIOR_3                  (3)
		#define T4_INT_PRIOR_2                  (2)
		#define T4_INT_PRIOR_1                  (1)
		#define T4_INT_PRIOR_0                  (0)

		// Interrupt sub-priority - values are mutually exclusive
		#define T4_INT_SUB_PRIOR_3              (3 << 4)
		#define T4_INT_SUB_PRIOR_2              (2 << 4)
		#define T4_INT_SUB_PRIOR_1              (1 << 4)
		#define T4_INT_SUB_PRIOR_0              (0 << 4)
	/***********************************
	 * End config parameter values
	 ************************************/


/******************************************************************************
 * Function:        EnableIntT4()
 *
 * Description:		Enables Timer4 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			EnableIntT4()
 *****************************************************************************/
#define EnableIntT4					mT4IntEnable(1)


/******************************************************************************
 * Function:        DisableIntT4
 *
 * Description:		Disables Timer4 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			DisableIntT4()
 *****************************************************************************/
#define DisableIntT4				mT4IntEnable(0)


/******************************************************************************
 * Function:        void SetPriorityIntT4(unsigned int priority)
 *
 * Description:		Sets the priority for Timer 4 interrupt
 *					The OpenTimerx() sets the priority. Use this
 *					macro to change the previously set priority
 *					without any need to respecify other parameters.
 *
 * PreCondition:    None
 *
 * Inputs:			priority : A value of T4_INT_PRIOR_XXX
 *
 * Output:          None
 *
 * Example:			SetPriorityIntT4(T4_INT_PRIORITY_3)
 *****************************************************************************/
#define SetPriorityIntT4(priority)	mT4SetIntPriority(priority)


/******************************************************************************
 * Function:        unsigned int ReadTimer4(void)
 *
 * Description:		Returns the current Timer4 value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          TMR4 value.
 *
 * Example:			ReadTimer4()
 *
 *****************************************************************************/
#define ReadTimer4()	(TMR4)


/******************************************************************************
 * Function:        void WriteTimer4(unsigned int value)
 *
 * Description:		Loads given value into Timer4 register.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WriteTimer4(1234)
 *
 *****************************************************************************/
#define WriteTimer4(value)	TMR4 = value


/******************************************************************************
 * Function:        unsigned int ReadPeriod4(void)
 *
 * Description:		Returns the current Period4 value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          PR4 value.
 *
 * Example:			ReadPeriod4()
 *
 *****************************************************************************/
#define ReadPeriod4()	(PR4)


/******************************************************************************
 * Function:        void WritePeriod4(unsigned int value)
 *
 * Description:		Loads given value into Period4 register.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WritePeriod4(1234)
 *
 *****************************************************************************/
#define WritePeriod4(value)	PR4 = (value)

#endif  // _TMR4


#if defined _TMR5

/******************************************************************************
 * Function:        void OpenTimer5(unsigned int config, unsigned int period)
 *
 * Description:		Configures Timer 5
 *
 * PreCondition:    None
 *
 * Inputs:			config: Bit-wise OR value of T5_ON/OFF, T5_IDLE_XXX,
 *							T5_GATE_XXX, T5_PS_XXX, T5_SOURCE_XXX.
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 *					period: A value between 0 - 0xffff inclusive
 *
 * Output:          None
 *
 * Example:			OpenTimer5(T5_ON | T5_IDLE_ON | T5_PS_1_4, 123)
 *
 *****************************************************************************/
#define OpenTimer5(config, period)	(T5CON = ((config)&~(T5_ON)), TMR5 = 0, PR5 = (period), T5CONSET=((config)&(T5_ON)) )

	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// On/off control - values are mutually exclusive
		#define T5_ON                           (1 << _T5CON_ON_POSITION)		/* Timer5 ON */
		#define T5_OFF							(0)

		// Stop-in-idle control - values are mutually exclusive
		#define T5_IDLE_STOP                    (1 << _T5CON_SIDL_POSITION)		/* stop during idle */
		#define T5_IDLE_CON 					(0)								/* operate during idle */

		// Timer gate control - values are mutually exclusive
		#define T5_GATE_ON                      (1 << _T5CON_TGATE_POSITION)	/* Timer Gate accumulation mode ON */
		#define T5_GATE_OFF						(0)

		// Prescale values - values are mutually exclusive
		#define T5_PS_1_256                     (7 << _T5CON_TCKPS_POSITION)    /* Prescaler 1:256 */
		#define T5_PS_1_64                      (6 << _T5CON_TCKPS_POSITION)    /*           1:64 */
		#define T5_PS_1_32                      (5 << _T5CON_TCKPS_POSITION)    /*           1:32 */
		#define T5_PS_1_16                      (4 << _T5CON_TCKPS_POSITION)    /*           1:16 */
		#define T5_PS_1_8                       (3 << _T5CON_TCKPS_POSITION)    /*           1:8 */
		#define T5_PS_1_4                       (2 << _T5CON_TCKPS_POSITION)    /*           1:4 */
		#define T5_PS_1_2                       (1 << _T5CON_TCKPS_POSITION)    /*           1:2 */
		#define T5_PS_1_1                       (0)								/*           1:1 */

		// Sync external clock option - values are mutually exclusive
		#define T5_SOURCE_EXT                   (1 << _T5CON_TCS_POSITION)      /* External clock source */
		#define T5_SOURCE_INT					(0)								/* Internal clock source */
	/***********************************
	 * End config parameter values
	 ************************************/

/******************************************************************************
 * Function:        void CloseTimer5(void)
 *
 * Description:		Switches off the Timer5
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			CloseTimer5()
 *
 *****************************************************************************/
#define CloseTimer5()	(mT5IntEnable(0), T5CON = 0x0)



/******************************************************************************
 * Function:        void ConfigIntTimer5(unsigned int config)
 *
 * Description:		Configures Timer 5 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			config: Bit-wise OR value of T5_INT_XXX, T5_INT_PRIOR_XXX
 *							  and T5_INT_SUB_PRIOR_X
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 * Output:          None
 *
 * Example:			ConfigIntTimer5(T5_INT_ON | T5_INT_PRIOR_3 | T5_INT_SUB_PRIOR1)
 *
 *****************************************************************************/
#define ConfigIntTimer5(config) (mT5ClearIntFlag(), mT5SetIntPriority((config) & 7), \
        mT5SetIntSubPriority(((config) >> 4) & 3), mT5IntEnable((config) >> 15))

	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// Interrupt on/off - values are mutually exclusive
		#define T5_INT_ON			            (1<<15)		/* Interrupt Enable */
		#define T5_INT_OFF						(0)

		// Interrupt priority - values are mutually exclusive
		#define T5_INT_PRIOR_7                  (7)
		#define T5_INT_PRIOR_6                  (6)
		#define T5_INT_PRIOR_5                  (5)
		#define T5_INT_PRIOR_4                  (4)
		#define T5_INT_PRIOR_3                  (3)
		#define T5_INT_PRIOR_2                  (2)
		#define T5_INT_PRIOR_1                  (1)
		#define T5_INT_PRIOR_0                  (0)

		// Interrupt sub-priority - values are mutually exclusive
		#define T5_INT_SUB_PRIOR_3              (3 << 4)
		#define T5_INT_SUB_PRIOR_2              (2 << 4)
		#define T5_INT_SUB_PRIOR_1              (1 << 4)
		#define T5_INT_SUB_PRIOR_0              (0 << 4)
	/***********************************
	 * End config parameter values
	 ************************************/


/******************************************************************************
 * Function:        EnableIntT5()
 *
 * Description:		Enables Timer5 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			EnableIntT5()
 *****************************************************************************/
#define EnableIntT5					mT5IntEnable(1)


/******************************************************************************
 * Function:        DisableIntT5
 *
 * Description:		Disables Timer5 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			DisableIntT5()
 *****************************************************************************/
#define DisableIntT5				mT5IntEnable(0)


/******************************************************************************
 * Function:        void SetPriorityIntT5(unsigned int priority)
 *
 * Description:		Sets the priority for Timer 5 interrupt
  *					The OpenTimerx() sets the priority. Use this
 *					macro to change the previously set priority
 *					without any need to respecify other parameters.
*
 * PreCondition:    None
 *
 * Inputs:			priority : A value of T5_INT_PRIOR_XXX
 *
 * Output:          None
 *
 * Example:			SetPriorityIntT5(T5_INT_PRIORITY_3)
 *****************************************************************************/
#define SetPriorityIntT5(priority)	mT5SetIntPriority(priority)


/******************************************************************************
 * Function:        unsigned int ReadTimer5(void)
 *
 * Description:		Returns the current Timer5 value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          TMR5 value.
 *
 * Example:			ReadTimer5()
 *
 *****************************************************************************/
#define ReadTimer5()	(TMR5)


/******************************************************************************
 * Function:        void WriteTimer5(unsigned int value)
 *
 * Description:		Loads given value into Timer5 register.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WriteTimer5(1234)
 *
 *****************************************************************************/
#define WriteTimer5(value)	TMR5 = value


/******************************************************************************
 * Function:        unsigned int ReadPeriod5(void)
 *
 * Description:		Returns the current Period5 value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          PR5 value.
 *
 * Example:			ReadPeriod5()
 *
 *****************************************************************************/
#define ReadPeriod5()	(PR5)


/******************************************************************************
 * Function:        void WritePeriod5(unsigned int value)
 *
 * Description:		Loads given value into Period5 register.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WritePeriod5(1234)
 *
 *****************************************************************************/
#define WritePeriod5(value)	PR5 = (value)



/******************************************************************************
 * Function:        void OpenTimer45(unsigned int config, unsigned int period)
 *
 * Description:		Configures Timer 45 - A 32-bit time by pairing
 *					Timer 4 & 5.
 *
 * PreCondition:    None
 *
 * Inputs:			config: Bit-wise OR value of T4_ON/OFF, T4_IDLE_XXX,
 *							T4_GATE_XXX, T4_PS_XXX, T4_SOURCE_XXX.
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 *					period: A value between 0 - 0xffffffff inclusive
 *
 * Output:          None
 *
 * Example:			OpenTimer45(T4_ON | T4_IDLE_ON | T4_PS_1_4, 123)
 *****************************************************************************/
#define OpenTimer45(config, period) \
( OpenTimer4((config) | T4_32BIT_MODE_ON, (period)))

	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// On/off control - values are mutually exclusive
		#define T45_ON                          (1 << _T4CON_ON_POSITION)		/* Timer4 ON */
		#define T45_OFF							(0)

		// Stop-in-idle control - values are mutually exclusive
		#define T45_IDLE_STOP                   (1 << _T4CON_SIDL_POSITION)		/* stop during idle */
		#define T45_IDLE_CON 					(0)								/* operate during idle */

		// Timer gate control - values are mutually exclusive
		#define T45_GATE_ON                     (1 << _T4CON_TGATE_POSITION)	/* Timer Gate accumulation mode ON */
		#define T45_GATE_OFF					(0)

		// Timer prescaler control - values are mutually exclusive
		#define T45_PS_1_256                    (7 << _T4CON_TCKPS_POSITION)    /* Prescaler 1:256 */
		#define T45_PS_1_64                     (6 << _T4CON_TCKPS_POSITION)    /*           1:64 */
		#define T45_PS_1_32                     (5 << _T4CON_TCKPS_POSITION)    /*           1:32 */
		#define T45_PS_1_16                     (4 << _T4CON_TCKPS_POSITION)    /*           1:16 */
		#define T45_PS_1_8                      (3 << _T4CON_TCKPS_POSITION)    /*           1:8 */
		#define T45_PS_1_4                      (2 << _T4CON_TCKPS_POSITION)    /*           1:4 */
		#define T45_PS_1_2                      (1 << _T4CON_TCKPS_POSITION)    /*           1:2 */
		#define T45_PS_1_1                      (0)								/*           1:1 */

		// 32-bit or 16-bit option - values are mutually exclusive
		#define T45_32BIT_MODE_ON               (1 << _T4CON_T32_POSITION)      /* Enable 32-bit mode */
		#define T45_32BIT_MODE_OFF				(0)

		// Source selection - values are mutually exclusive
		#define T45_SOURCE_EXT                  (1 << _T4CON_TCS_POSITION)      /* External clock source */
		#define T45_SOURCE_INT					(0)								/* Internal clock source */
	/***********************************
	 * End config parameter values
	 ************************************/

/******************************************************************************
 * Function:        CloseTimer45()
 *
 * Description:		Switches off the 32-bit Timer45
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			CloseTimer45()
 *
 *****************************************************************************/
#define CloseTimer45()	(CloseTimer4(), CloseTimer5())


/******************************************************************************
 * Function:        void ConfigIntTimer45(unsigned int config)
 *
 * Description:		Configures the 32-bit Timer45 interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			priority: Bit-wise OR value of T4_INT_XXX, T4_INT_PRIOR_XXX
 *							  and T4_INT_SUB_PRIOR_X
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 * Output:          None
 *
 * Example:			ConfigIntTimer45(T4_INT_ON | T4_INT_PRIOR_3 | T4_INT_SUB_PRIOR1)
 *
 *****************************************************************************/
#define ConfigIntTimer45(config)	ConfigIntTimer5(config)

	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// Interrupt on/off - values are mutually exclusive
		#define T45_INT_ON			            (1<<15)		/* Interrupt Enable */
		#define T45_INT_OFF						(0)

		// Interrupt priority - values are mutually exclusive
		#define T45_INT_PRIOR_7                  (7)
		#define T45_INT_PRIOR_6                  (6)
		#define T45_INT_PRIOR_5                  (5)
		#define T45_INT_PRIOR_4                  (4)
		#define T45_INT_PRIOR_3                  (3)
		#define T45_INT_PRIOR_2                  (2)
		#define T45_INT_PRIOR_1                  (1)
		#define T45_INT_PRIOR_0                  (0)

		// Interrupt sub-priority - values are mutually exclusive
		#define T45_INT_SUB_PRIOR_3              (3 << 4)
		#define T45_INT_SUB_PRIOR_2              (2 << 4)
		#define T45_INT_SUB_PRIOR_1              (1 << 4)
		#define T45_INT_SUB_PRIOR_0              (0 << 4)
	/***********************************
	 * End config parameter values
	 ************************************/


/******************************************************************************
 * Function:        EnableIntT45()
 *
 * Description:		Enables the 32-bit Timer45 interrupt(Timer5 interrupt)
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			EnableIntT45()
 *****************************************************************************/
#define EnableIntT45				EnableIntT5


/******************************************************************************
 * Function:        DisableIntT45
 *
 * Description:		Disables 32-bit Timer45 interrupt(Timer5 interrupt)
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			DisableIntT45()
 *****************************************************************************/
#define DisableIntT45				DisableIntT5


/******************************************************************************
 * Function:        void SetPriorityIntT45(int priority)
 *
 * Description:		Sets the priority for 32-bit Timer 45 interrupt
 *					The OpenTimerx() sets the priority. Use this
 *					macro to change the previously set priority
 *					without any need to respecify other parameters.
 *                  Timer5 interrupt.
 *
 * PreCondition:    None
 *
 * Inputs:			priority : A value of T4_INT_PRIOR_XXX
 *
 * Output:          None
 *
 * Example:			SetPriorityIntT45(T4_INT_PRIORITY_3)
 *****************************************************************************/
#define SetPriorityIntT45(priority)	SetPriorityIntT5(priority)


/******************************************************************************
 * Function:        unsigned int ReadTimer45(void)
 *
 * Description:		Returns the current 32-bit Timer45 value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          The current 32-bit timer value.
 *
 * Example:			ReadTimer45()
 *
 *****************************************************************************/
#define ReadTimer45()	ReadTimer4()


/******************************************************************************
 * Function:        void WriteTimer45(unsigned int value)
 *
 * Description:		Loads given value into 32-bit Timer45 register.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WriteTimer45(1234)
 *
 *****************************************************************************/
#define WriteTimer45(value)	WriteTimer4(value)


/******************************************************************************
 * Function:        unsigned int ReadPeriod45(void)
 *
 * Description:		Returns the current Period45 value.
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          PR4 value.
 *
 * Example:			ReadPeriod45()
 *
 *****************************************************************************/
#define ReadPeriod45()	PR4


/******************************************************************************
 * Function:        void WritePeriod45(unsigned int value)
 *
 * Description:		Loads given value into Period45 register.
 *
 * PreCondition:    None
 *
 * Inputs:			value: The value to be loaded.
 *
 * Output:          None
 *
 * Example:			WritePeriod45(1234)
 *
 *****************************************************************************/
#define WritePeriod45(value)	PR4 = (value)

#endif		// _TMR5
#endif /*TIMER_H_*/

