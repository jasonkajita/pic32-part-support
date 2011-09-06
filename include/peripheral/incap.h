/*********************************************************************
 *
 *              Header for Input Capture module library functions
 *
 *********************************************************************
 * FileName:        INCAP.H
 * Dependencies:	None
 * Processor:       PIC32
 *
 * Complier:        MPLAB C32
 * Company:         Microchip Technology Inc..
 *
 * Software License Agreement:
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
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
 * $Id $
 * $Name $
 *
 ********************************************************************/


#ifndef __INCAP_H__
#define __INCAP_H__

#include <p32xxxx.h>
#include <peripheral/int.h>


/*********************************************************************
 * <combinewith OpenCapture2, OpenCapture3, OpenCapture4, OpenCapture5>
 *
 * Function:        OpenCapturex()
 *
 * Description:     Configures specified capture channel
 *
 * PreCondition:    None
 *
 * Inputs:          config - see below
 *
 * Output:          None
 *
 * Example:         OpenCapture1(IC_ON | IC_FEDGE_RISE | IC_TIMER2_SRC);
 *
 ********************************************************************/
#ifdef _ICAP1
	#define  OpenCapture1(config)		(IC1CON = (config))
#endif

#ifdef _ICAP2
	#define  OpenCapture2(config)		(IC2CON = (config))
#endif

#ifdef _ICAP3
	#define  OpenCapture3(config)		(IC3CON = (config))
#endif

#ifdef _ICAP4
	#define  OpenCapture4(config)		(IC4CON = (config))
#endif

#ifdef _ICAP5
	#define  OpenCapture5(config)		(IC5CON = (config))
#endif

	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// Module On/off control - values are mutually exclusive
		#define IC_ON					(1 << _IC1CON_ON_POSITION)
		#define IC_OFF					0

		// Module Stop-In-Idle control - values are mutually exclusive
		#define IC_IDLE_CON             (1 << _IC1CON_SIDL_POSITION)  	/* IC operates in sleep mode */
		#define IC_IDLE_STOP            0  								/* IC stop in sleep mode */

		// First Edge control - values are mutually exclusive
		#define IC_FEDGE_RISE			(1 << _IC1CON_FEDGE_POSITION)	/* Capture Rising Edge First */
		#define IC_FEDGE_FALL			0								/* Capture Falling Edge First */

		// 16- or 32-bit - values are mutually exclusive
		#define IC_CAP_32BIT			(1 << _IC1CON_C32_POSITION)		/* 32-bit timer resource capture */
		#define IC_CAP_16BIT			0								/* 16-bit timer resource capture */

		// Timer select - values are mutually exclusive
		#define IC_TIMER3_SRC    (0)                                    /* Timer 3 is the clock source for Capture */
        #define IC_TIMER2_SRC    (1 << _IC1CON_ICTMR_POSITION)          /* Timer2 is the clock source for Capture */


		// Capture interrupt control - values are mutually exclusive
		#define IC_INT_4CAPTURE         (3 << _IC1CON_ICI0_POSITION)  	/* Interrupt on fourth Capture*/
		#define IC_INT_3CAPTURE         (2 << _IC1CON_ICI0_POSITION)	/* Interrupt on third Capture */
		#define IC_INT_2CAPTURE         (1 << _IC1CON_ICI0_POSITION)	/* Interrupt on second Capture*/
		#define IC_INT_1CAPTURE         (0 << _IC1CON_ICI0_POSITION)	/* Interrupt on first Capture */

		// Mode select - values are mutually exclusive
		#define IC_INTERRUPT            (7 << _IC1CON_ICM_POSITION)		/* Interrupt pin only in CPU sleep and idle mode */
		#define IC_SP_EVERY_EDGE   		(6 << _IC1CON_ICM_POSITION)  	/* Specified edge first, then every rising/falling edge */
		#define IC_EVERY_16_RISE_EDGE   (5 << _IC1CON_ICM_POSITION)  	/* Every 16th rising edge */
		#define IC_EVERY_4_RISE_EDGE    (4 << _IC1CON_ICM_POSITION)  	/* Every 4th rising edge  */
		#define IC_EVERY_RISE_EDGE      (3 << _IC1CON_ICM_POSITION)  	/* Every rising edge      */
		#define IC_EVERY_FALL_EDGE      (2 << _IC1CON_ICM_POSITION)  	/* Every falling edge      */
		#define IC_EVERY_EDGE           (1 << _IC1CON_ICM_POSITION)  	/* Every rising/falling edge */
		#define IC_INPUTCAP_OFF         (0)  							/* Input Capture Off      */
	/***********************************
	 * End config parameter values
	 ************************************/


/*********************************************************************
 * <combinewith ConfigIntCapture2, ConfigIntCapture3, ConfigIntCapture4, ConfigIntCapture5>
 *
 * Function:        ConfigIntCapturex(unsigned int)
 *
 * Description:     Configures specified capture channel
 *
 * PreCondition:    None
 *
 * Inputs:          config - see below
 *
 * Output:          None
 *
 * Example:         ConfigIntCapture1(IC_INT_ON | IC_INT_PRIOR_4 | IC_INT_SUB_PRIOR_3);
 *
 ********************************************************************/
#ifdef _ICAP1
	#define ConfigIntCapture1(config) (mIC1ClearIntFlag(), mIC1SetIntPriority((config)&7), mIC1SetIntSubPriority(((config)&3)>>3), mIC1IntEnable((config)>>15))
#endif

#ifdef _ICAP2
	#define ConfigIntCapture2(config) (mIC2ClearIntFlag(), mIC2SetIntPriority((config)&7), mIC2SetIntSubPriority(((config)&3)>>3), mIC2IntEnable((config)>>15))
#endif

#ifdef _ICAP3
	#define ConfigIntCapture3(config) (mIC3ClearIntFlag(), mIC3SetIntPriority((config)&7), mIC3SetIntSubPriority(((config)&3)>>3), mIC3IntEnable((config)>>15))
#endif

#ifdef _ICAP4
	#define ConfigIntCapture4(config) (mIC4ClearIntFlag(), mIC4SetIntPriority((config)&7), mIC4SetIntSubPriority(((config)&3)>>3), mIC4IntEnable((config)>>15))
#endif

#ifdef _ICAP5
	#define ConfigIntCapture5(config) (mIC5ClearIntFlag(), mIC5SetIntPriority((config)&7), mIC5SetIntSubPriority(((config)&3)>>3), mIC5IntEnable((config)>>15))
#endif


	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// Interrupt enable/disable - values are mutually exclusive
		#define IC_INT_ON               (1<<15)  	/* Input Capture Int Enable  */
		#define IC_INT_OFF              (0)			/* Input Capture Int Disable */

		// Interrupt priority values - values are mutually exclusive
		#define IC_INT_PRIOR_0          (0)
		#define IC_INT_PRIOR_1          (1)
		#define IC_INT_PRIOR_2          (2)
		#define IC_INT_PRIOR_3          (3)
		#define IC_INT_PRIOR_4          (4)
		#define IC_INT_PRIOR_5          (5)
		#define IC_INT_PRIOR_6          (6)
		#define IC_INT_PRIOR_7          (7)

		// Interrupt sub-priority values - values are mutually exclusive
		#define IC_INT_SUB_PRIOR_0      (0<<3)
		#define IC_INT_SUB_PRIOR_1      (1<<3)
		#define IC_INT_SUB_PRIOR_2      (2<<3)
		#define IC_INT_SUB_PRIOR_3      (3<<3)
	/***********************************
	 * End config parameter values
	 ************************************/


/*********************************************************************
 * <combinewith SetPriorityIntIC2, SetPriorityIntIC3, SetPriorityIntIC4, SetPriorityIntIC5>
 *
 * Function:        SetPriorityIntICx(priority)
 *
 * Description:     Sets priority and sub-priority for specified capture channel
 *
 * PreCondition:    None
 *
 * Inputs:          config - see below
 *
 * Output:          None
 *
 * Example:         SetPriorityIntIC1(IC_INT_PRIOR_4 | IC_INT_SUB_PRIOR_3);
 *
 ********************************************************************/
#ifdef _ICAP1
	#define SetPriorityIntIC1(priority)     (mIC1SetIntPriority((priority)&7), mIC1SetIntSubPriority(((priority)&3)>>3))
#endif

#ifdef _ICAP2
	#define SetPriorityIntIC2(priority)     (mIC2SetIntPriority((priority)&7), mIC2SetIntSubPriority(((priority)&3)>>3))
#endif

#ifdef _ICAP3
	#define SetPriorityIntIC3(priority)     (mIC3SetIntPriority((priority)&7), mIC3SetIntSubPriority(((priority)&3)>>3))
#endif

#ifdef _ICAP4
	#define SetPriorityIntIC4(priority)     (mIC4SetIntPriority((priority)&7), mIC4SetIntSubPriority(((priority)&3)>>3))
#endif

#ifdef _ICAP5
	#define SetPriorityIntIC5(priority)     (mIC5SetIntPriority((priority)&7), mIC5SetIntSubPriority(((priority)&3)>>3))
#endif


	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		// Interrupt priority values - values are mutually exclusive
		// Use same options from ConfigIntCapturex macro

		// Interrupt sub-priority values - values are mutually exclusive
		// Use same options from ConfigIntCapturex macro
	/***********************************
	 * End config parameter values
	 ************************************/



/*********************************************************************
 * <combinewith DisableIntIC1, EnableIntIC2, DisableIntIC2, EnableIntIC3, DisableIntIC3, EnableIntIC4, DisableIntIC4, EnableIntIC5, DisableIntIC5>
 *
 * Function:        void EnableIntICx
 *					void DisableIntICx
 *
 * Description:     Enables/Disables interrupt for specified capture channel
 *
 * PreCondition:    None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Example:         EnableIntIC1;
 *
 ********************************************************************/
#ifdef _ICAP1
	#define EnableIntIC1                    mIC1IntEnable(1)
	#define DisableIntIC1                   mIC1IntEnable(0)
#endif

#ifdef _ICAP2
	#define EnableIntIC2                    mIC2IntEnable(1)
	#define DisableIntIC2                   mIC2IntEnable(0)
#endif

#ifdef _ICAP3
	#define EnableIntIC3                    mIC3IntEnable(1)
	#define DisableIntIC3                   mIC3IntEnable(0)
#endif

#ifdef _ICAP4
	#define EnableIntIC4                    mIC4IntEnable(1)
	#define DisableIntIC4                   mIC4IntEnable(0)
#endif

#ifdef _ICAP5
	#define EnableIntIC5                    mIC5IntEnable(1)
	#define DisableIntIC5                   mIC5IntEnable(0)
#endif


/*********************************************************************
 * <combinewith  CloseCapture2, CloseCapture3, CloseCapture4, CloseCapture5>
 *
 * Function:        void CloseCapturex(void)
 *
 * Description:     Closes specified capture channel
 *
 * PreCondition:    None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Example:         CloseCapture1();
 *
 ********************************************************************/
#ifdef _ICAP1
	#define CloseCapture1()	(mIC1IntEnable(0), mIC1ClearIntFlag(), IC1CONCLR = _IC1CON_ICM_MASK)
#endif

#ifdef _ICAP2
	#define CloseCapture2()	(mIC2IntEnable(0), mIC2ClearIntFlag(), IC2CONCLR = _IC2CON_ICM_MASK)
#endif

#ifdef _ICAP3
	#define CloseCapture3()	(mIC3IntEnable(0), mIC3ClearIntFlag(), IC3CONCLR = _IC3CON_ICM_MASK)
#endif

#ifdef _ICAP4
	#define CloseCapture4()	(mIC4IntEnable(0), mIC4ClearIntFlag(), IC4CONCLR = _IC4CON_ICM_MASK)
#endif

#ifdef _ICAP5
	#define CloseCapture5()	(mIC5IntEnable(0), mIC5ClearIntFlag(), IC5CONCLR = _IC5CON_ICM_MASK)
#endif


/*********************************************************************
 * <combinewith  ReadCapture2, ReadCapture3, ReadCapture4, ReadCapture5>
 *
 * Function:        void ReadCapture1x(void)
 *
 * Description:     Reads specified capture channel, waits if data is not ready
 *
 * PreCondition:    None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Example:         ReadCapture11();
 *
 ********************************************************************/
#ifdef _ICAP1
	void ReadCapture1(unsigned int * buffer);
#endif

#ifdef _ICAP2
	void ReadCapture2(unsigned int * buffer);
#endif

#ifdef _ICAP3
	void ReadCapture3(unsigned int * buffer);
#endif

#ifdef _ICAP4
	void ReadCapture4(unsigned int * buffer);
#endif

#ifdef _ICAP5
	void ReadCapture5(unsigned int * buffer);
#endif


/*********************************************************************
 * <combinewith  mIC2CaptureReady, mIC3CaptureReady, mIC4CaptureReady, mIC5CaptureReady>
 *
 * Function:        int mICxCaptureReady(void)
 *
 * Description:     Checks to see if specified channel has captured anything
 *
 * PreCondition:    None
 *
 * Inputs:          None
 *
 * Output:          '1' if there is a captured data
 *					'0' otherwise
 *
 * Example:         if ( mIC1CaptureReady1() )
 *						// There is some data
 *					else
 *						// There is no data
 *
 ********************************************************************/
#ifdef _ICAP1
	#define mIC1CaptureReady()				(IC1CONbits.ICBNE)
#endif

#ifdef _ICAP2
	#define mIC2CaptureReady()				(IC2CONbits.ICBNE)
#endif

#ifdef _ICAP3
	#define mIC3CaptureReady()				(IC3CONbits.ICBNE)
#endif

#ifdef _ICAP4
	#define mIC4CaptureReady()				(IC4CONbits.ICBNE)
#endif

#ifdef _ICAP5
	#define mIC5CaptureReady()				(IC5CONbits.ICBNE)
#endif


/*********************************************************************
 * <combinewith  mIC2ReadCapture, mIC3ReadCapture, mIC4ReadCapture, mIC5ReadCapture>
 *
 * Function:        int mIC1ReadCapture(void)
 *
 * Description:     Reads the captured data
 *
 * PreCondition:    mIC1CaptureReady() must be '1'
 *
 * Inputs:          None
 *
 * Output:          Captured data
 *
 * Example:         if ( mIC1CaptureReady1() )
 *						// There is some data
 *						myData = mIC1ReadCapture();
 *					else
 *						// There is no data
 *
 ********************************************************************/
#ifdef _ICAP1
	#define mIC1ReadCapture()				(IC1BUF)
#endif

#ifdef _ICAP2
	#define mIC2ReadCapture()				(IC2BUF)
#endif

#ifdef _ICAP3
	#define mIC3ReadCapture()				(IC3BUF)
#endif

#ifdef _ICAP4
	#define mIC4ReadCapture()				(IC4BUF)
#endif

#ifdef _ICAP5
	#define mIC5ReadCapture()				(IC5BUF)
#endif


#endif  /*__INCAP_H__  */


