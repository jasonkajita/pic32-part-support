/*********************************************************************
 *
 *                  Output Compare API definitions
 *
 *********************************************************************
 * FileName:        outcompare.h
 * Dependencies:
 * Processor:       PIC32
 *
 * Complier:        MPLAB C30 v1.31.00 or higher
 *                  MPLAB IDE v7.30.00 or higher
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
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * $Id: outcompare.h,v 1.2 2006/10/30 17:38:51 C12532 Exp $
 *
 * $Name:  $
 ********************************************************************/

#ifndef _OUTPUT_COMPARE_H_
#define _OUTPUT_COMPARE_H_

#include <p32xxxx.h>

/*******************************************************************
  * <combinewith OpenOC2, OpenOC3, OpenOC4, OpenOC5>
  * 
  * Prototype:
  *     void OpenOC1( config, value1, value2)
  * Description:
  *     Configures the OC1 module and loads the R and RS registers
  *     with default values
  * Preconditions:
  *     Module should be disabled or closed
  * Input:
  *     config :   OC configuration values \- see below
  *     value1 :   Secodanry compare value
  *     value 2 :  Primary compare value
  * Return:
  *     None
  *     
  * Example:
  *     OpenOC1( OC_IDLE_STOP | OC_TIMER_MODE32 |
  *     OC_PWM_FAULT_PIN_DISABLE, OC_SINGLE_PULSE , 0x0000, 0xFFFF )
  ******************************************************************
*/
#ifdef _OCMP1
   #define OpenOC1( config, value1, value2) ( OC1RS = (value1), OC1R = (value2), OC1CON = (config) )
#endif
#ifdef _OCMP2
   #define OpenOC2( config, value1, value2) ( OC2RS = (value1), OC2R = (value2), OC2CON = (config) )
#endif
#ifdef _OCMP3
   #define OpenOC3( config, value1, value2) ( OC3RS = (value1), OC3R = (value2), OC3CON = (config) )
#endif
#ifdef _OCMP4
   #define OpenOC4( config, value1, value2) ( OC4RS = (value1), OC4R = (value2), OC4CON = (config) )
#endif
#ifdef _OCMP5
   #define OpenOC5( config, value1, value2) ( OC5RS = (value1), OC5R = (value2), OC5CON = (config) )
#endif

		/********************************************************
		  * <combinewith OC_OFF>
		  * 
		  * Module on/off control - values are mutually exclusive
		  *******************************************************
		*/
		#define OC_ON                      (1 << _OC1CON_ON_POSITION)
		#define OC_OFF                     (0)

		// Stop-in-idle control - values are mutually exclusive
		#define OC_IDLE_STOP               (1 << _OC1CON_OCSIDL_POSITION)    /* stop in idle mode */
		#define OC_IDLE_CON                (0)          /* continue operation in idle mode */

		// 16/32 bit mode - values are mutually exclusive
		#define OC_TIMER_MODE32             (1 << _OC1CON_OC32_POSITION)    /* use 32 bit mode */
		#define OC_TIMER_MODE16             (0)         /* use 16 bit mode */

		// Timer select - values are mutually exclusive
		#define OC_TIMER3_SRC               (1 << _OC1CON_OCTSEL_POSITION)   /* Timer3 is the clock source */
		#define OC_TIMER2_SRC               (0)         /* Timer2 is the clock source */

		// Operation mode select - values are mutually exclusive
		#define OC_PWM_FAULT_PIN_ENABLE  	(7 << _OC1CON_OCM_POSITION)		/* PWM Mode on OCx, fault pin enabled */
		#define OC_PWM_FAULT_PIN_DISABLE    (6 << _OC1CON_OCM_POSITION)     /* PWM Mode on OCx, fault pin disabled */
		#define OC_CONTINUE_PULSE           (5 << _OC1CON_OCM_POSITION)     /* Generates Continuous Output pulse on OCx Pin */
		#define OC_SINGLE_PULSE             (4 << _OC1CON_OCM_POSITION)     /* Generates Single Output pulse on OCx Pin */
		#define OC_TOGGLE_PULSE             (3 << _OC1CON_OCM_POSITION)     /* Compare1 toggels  OCx pin*/
		#define OC_HIGH_LOW                 (2 << _OC1CON_OCM_POSITION)     /* Compare1 forces OCx pin Low*/
		#define OC_LOW_HIGH                 (1 << _OC1CON_OCM_POSITION)     /* Compare1 forces OCx pin High*/
		#define OC_MODE_OFF                 (0 << _OC1CON_OCM_POSITION)     /* OutputCompare x Off*/
	/***********************************
	 * End config parameter values
	 ************************************/

/************************************************************
  * <combinewith CloseOC2, CloseOC3, CloseOC4, CloseOC5>
  * 
  * Prototype:
  *     CloseOCx()
  * Description:
  *     Turns off the output compare channel and disables its
  *     interrupt
  * Preconditions:
  *     None
  * Return:
  *     None
  *     
  * Example:
  *     CloseOC1()                                           
  ***********************************************************
*/
#ifdef _OCMP1
   #define CloseOC1() ( mOC1IntEnable(0), mOC1ClearIntFlag(), OC1CONCLR = _OC1CON_ON_MASK )
#endif
#ifdef _OCMP2
   #define CloseOC2() ( mOC2IntEnable(0), mOC2ClearIntFlag(), OC2CONCLR = _OC2CON_ON_MASK )
#endif
#ifdef _OCMP3
   #define CloseOC3() ( mOC3IntEnable(0), mOC3ClearIntFlag(), OC3CONCLR = _OC3CON_ON_MASK )
#endif
#ifdef _OCMP4
   #define CloseOC4() ( mOC4IntEnable(0), mOC4ClearIntFlag(), OC4CONCLR = _OC4CON_ON_MASK )
#endif
#ifdef _OCMP5
   #define CloseOC5() ( mOC5IntEnable(0), mOC5ClearIntFlag(), OC5CONCLR = _OC5CON_ON_MASK )
#endif

/***********************************************************************
  * <combinewith ConfigIntOC2, ConfigIntOC3, ConfigIntOC4, ConfigIntOC5>
  * 
  * Prototype:
  *     ConfigIntOCx()
  * Description:
  *     Configure interrupt for OCx
  * Preconditions:
  *     Module should be enabled using OpenOC1 prior to configuring
  *     interrupts
  * Return:
  *     None
  *     
  * Example:
  *     ConfigIntOC1()                                                  
  **********************************************************************
*/
#ifdef _OCMP1
   #define ConfigIntOC1(config) ( mOC1ClearIntFlag(), mOC1SetIntPriority((config)&7), mOC1SetIntSubPriority(((config) >> 3)&3), mOC1IntEnable((config) >> 15) )
#endif
#ifdef _OCMP2
   #define ConfigIntOC2(config) ( mOC2ClearIntFlag(), mOC2SetIntPriority((config)&7), mOC2SetIntSubPriority(((config) >> 3)&3), mOC2IntEnable((config) >> 15) )
#endif
#ifdef _OCMP3
   #define ConfigIntOC3(config) ( mOC3ClearIntFlag(), mOC3SetIntPriority((config)&7), mOC3SetIntSubPriority(((config) >> 3)&3), mOC3IntEnable((config) >> 15) )
#endif
#ifdef _OCMP4
   #define ConfigIntOC4(config) ( mOC4ClearIntFlag(), mOC4SetIntPriority((config)&7), mOC4SetIntSubPriority(((config) >> 3)&3), mOC4IntEnable((config) >> 15) )
#endif
#ifdef _OCMP5
   #define ConfigIntOC5(config) ( mOC5ClearIntFlag(), mOC5SetIntPriority((config)&7), mOC5SetIntSubPriority(((config) >> 3)&3), mOC5IntEnable((config) >> 15) )
#endif


		/*******************************************************************************************************************************
		  * <combinewith OC_INT_PRIOR_0, OC_INT_PRIOR_1, OC_INT_PRIOR_2, OC_INT_PRIOR_3, OC_INT_PRIOR_4, OC_INT_PRIOR_5, OC_INT_PRIOR_6>
		  * 
		  * Interrupt Priority values - Values are mutually exclusive                                                                   
		  ******************************************************************************************************************************
		*/
		#define OC_INT_PRIOR_7         (7)
		#define OC_INT_PRIOR_6         (6)
		#define OC_INT_PRIOR_5         (5)
		#define OC_INT_PRIOR_4         (4)
		#define OC_INT_PRIOR_3         (3)
		#define OC_INT_PRIOR_2         (2)
		#define OC_INT_PRIOR_1         (1)
		#define OC_INT_PRIOR_0         (0)

		/*********************************************************************
		  * <combinewith OC_INT_SUB_PRI_0, OC_INT_SUB_PRI_1, OC_INT_SUB_PRI_2>
		  * 
		  * Sub-Priority values - Values are mutually exclusive               
		  ********************************************************************
		*/
		#define OC_INT_SUB_PRI_3       (3<<3)
		#define OC_INT_SUB_PRI_2       (2<<3)
		#define OC_INT_SUB_PRI_1       (1<<3)
		#define OC_INT_SUB_PRI_0       (0<<3)

		/***********************************************************
		  * <combinewith OC_INT_OFF>
		  * 
		  * Interrupt enable/disable - Values are mutually exclusive
		  **********************************************************
		*/
		#define OC_INT_ON				(1<<15)
		#define OC_INT_OFF				(0)

/***********************************************************************
  * <combinewith ReadDCOC2PWM, ReadDCOC3PWM, ReadDCOC4PWM, ReadDCOC5PWM>
  * 
  * Prototype:
  *     ReadDCOCxPWM()
  * Description:
  *     This routine reads duty cycle from the Secondary register in
  *     PWM mode
  * Preconditions:
  *     Module must be in PWM mode
  * Return:
  *     unsigned int: duty cycle from Secondary register
  *     
  * Example:
  *     Duty = ReadOC1PWM()                                             
  **********************************************************************
*/
#ifdef _OCMP1
   #define ReadDCOC1PWM() ( OC1RS )
#endif
#ifdef _OCMP2
   #define ReadDCOC2PWM() ( OC2RS )
#endif
#ifdef _OCMP3
   #define ReadDCOC3PWM() ( OC3RS )
#endif
#ifdef _OCMP4
   #define ReadDCOC4PWM() ( OC4RS )
#endif
#ifdef _OCMP5
   #define ReadDCOC5PWM() ( OC5RS )
#endif

/*****************************************************************
  * <combinewith ReadRegOC2, ReadRegOC3, ReadRegOC4, ReadRegOC5>
  * 
  * Prototype:
  *     ReadRegOCx()
  * Description:
  *     \Returns the contents of the OCRS or OCR register based on
  *     the input parameter
  * Preconditions:
  *     None
  * Input:
  *     0 or 1 :  0 = return OCxR, 1 = return OCxRS
  * Return:
  *     unsigned int: OCRS (if reg is 0) or OCR (if reg is 1)
  *     
  * Example:
  *     value = ReadRegOC1()                                      
  ****************************************************************
*/
#ifdef _OCMP1
   #define ReadRegOC1(offset) *( &OC1R + (offset) * 0x10 )
#endif
#ifdef _OCMP2
   #define ReadRegOC2(offset) *( &OC2R + (offset) * 0x10 )
#endif
#ifdef _OCMP3
   #define ReadRegOC3(offset) *( &OC3R + (offset) * 0x10 )
#endif
#ifdef _OCMP4
   #define ReadRegOC4(offset) *( &OC4R + (offset) * 0x10 )
#endif
#ifdef _OCMP5
   #define ReadRegOC5(offset) *( &OC5R + (offset) * 0x10 )
#endif


/*******************************************************************
  * <combinewith SetDCOC2PWM, SetDCOC3PWM, SetDCOC4PWM, SetDCOC5PWM>
  * 
  * Prototype:
  *     SetDCOCxPWM()
  * Description:
  *     Writes passed data to the dutycycle register
  * Preconditions:
  *     module must be in PWM mode
  * Return:
  *     unsigned int: OCRS (if reg is 0) or OCR (if reg is 1)
  *     
  * Example:
  *     SetDCOCxPWM(0xff)                                           
  ******************************************************************
*/
#ifdef _OCMP1
   #define SetDCOC1PWM(dutycycle) (OC1RS = (dutycycle))
#endif
#ifdef _OCMP2
   #define SetDCOC2PWM(dutycycle) (OC2RS = (dutycycle))
#endif
#ifdef _OCMP3
   #define SetDCOC3PWM(dutycycle) (OC3RS = (dutycycle))
#endif
#ifdef _OCMP4
   #define SetDCOC4PWM(dutycycle) (OC4RS = (dutycycle))
#endif
#ifdef _OCMP5
   #define SetDCOC5PWM(dutycycle) (OC5RS = (dutycycle))
#endif

/*******************************************************************
  * <combinewith SetPulseOC2, SetPulseOC3, SetPulseOC4, SetPulseOC5>
  * 
  * Prototype:
  *     SetPulseOCx()
  * Description:
  *     Writes passed data to the dutycycle register
  * Preconditions:
  *     module must be in PWM mode
  * Return:
  *     unsigned int: OCRS (if reg is 0) or OCR (if reg is 1)
  *     
  * Example:
  *     SetPulseOC1(0xFF, 0xFFFF)                                   
  ******************************************************************
*/
#ifdef _OCMP1
   #define SetPulseOC1( pulse_start, pulse_stop) (OC1R = (pulse_start), OC1RS = (pulse_stop))
#endif
#ifdef _OCMP2
   #define SetPulseOC2( pulse_start, pulse_stop) (OC2R = (pulse_start), OC2RS = (pulse_stop))
#endif
#ifdef _OCMP3
   #define SetPulseOC3( pulse_start, pulse_stop) (OC3R = (pulse_start), OC3RS = (pulse_stop))
#endif
#ifdef _OCMP4
   #define SetPulseOC4( pulse_start, pulse_stop) (OC4R = (pulse_start), OC4RS = (pulse_stop))
#endif
#ifdef _OCMP5
   #define SetPulseOC5( pulse_start, pulse_stop) (OC5R = (pulse_start), OC5RS = (pulse_stop))
#endif

#endif  /* _OUTPUT_COMPARE_H_ */
