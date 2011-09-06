/*********************************************************************
 *
 *                  CVref API definitions
 *
 *********************************************************************
 * FileName:        CVREF.h
 * Dependencies:	plib.h
 * Processor:       pic32
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
 * $Id: CVREF.h,v 1.1 2006/10/19 20:47:41 C12532 Exp $
 *
 * $Name:  $
 ********************************************************************/

#include <p32xxxx.h>

#ifndef CVREF_H_
#define CVREF_H_


/*********************************************************************
 * Function:      CVREFOpen(config)
 *
 * Description:	  Configures CVREF
 *
 * PreCondition:  None
 *
 * Inputs:	  	Desired configuration - see below
 *
 * Output:        None
 *
 * Example:	  CVREFOpen( CVREF_ENABLE | CVREF_OUTPUT_ENABLE | CVREF_RANGE_HIGH | CVREF_SOURCE_AVDD | CVREF_STEP_15 )
 *
 ********************************************************************/
#define CVREFOpen(config) (CVRCON = (config))

	/****************************************
	 * Available options for config parameter
	 ****************************************/
	 	// CVRef mode select - values are mutually exclusive
		#define CVREF_ENABLE  			(1 << _CVRCON_ON_POSITION)
		#define CVREF_DISABLE 			(0)

	 	// CVRef output control - values are mutually exclusive
		#define CVREF_OUTPUT_ENABLE 	(1 << _CVRCON_CVROE_POSITION)
		#define CVREF_OUTPUT_DISABLE 	(0)

	 	// CVRef range control - values are mutually exclusive
		#define CVREF_RANGE_HIGH 		(0)
		#define CVREF_RANGE_LOW  		(1 << _CVRCON_CVRR_POSITION)

	 	// CVRef Reference source select - values are mutually exclusive
		#define CVREF_SOURCE_AVDD 		(0)
		#define CVREF_SOURCE_VREF 		(1 << _CVRCON_CVRSS_POSITION)

	 	// CVRef Output Voltage Select - values are mutually exclusive
		#define CVREF_STEP_0 			(0)
		#define CVREF_STEP_1 			(1 << _CVRCON_CVR_POSITION)
		#define CVREF_STEP_2 			(2 << _CVRCON_CVR_POSITION)
		#define CVREF_STEP_3 			(3 << _CVRCON_CVR_POSITION)
		#define CVREF_STEP_4 			(4 << _CVRCON_CVR_POSITION)
		#define CVREF_STEP_5 			(5 << _CVRCON_CVR_POSITION)
		#define CVREF_STEP_6 			(6 << _CVRCON_CVR_POSITION)
		#define CVREF_STEP_7 			(7 << _CVRCON_CVR_POSITION)
		#define CVREF_STEP_8 			(8 << _CVRCON_CVR_POSITION)
		#define CVREF_STEP_9 			(9 << _CVRCON_CVR_POSITION)
		#define CVREF_STEP_10			(10 << _CVRCON_CVR_POSITION)
		#define CVREF_STEP_11 			(11 << _CVRCON_CVR_POSITION)
		#define CVREF_STEP_12 			(12 << _CVRCON_CVR_POSITION)
		#define CVREF_STEP_13 			(13 << _CVRCON_CVR_POSITION)
		#define CVREF_STEP_14 			(14 << _CVRCON_CVR_POSITION)
		#define CVREF_STEP_15 			(15 << _CVRCON_CVR_POSITION)
	/****************************************
	 * End config1 parameter values
	 ****************************************/



/*********************************************************************
 * Function:      CVREFClose()
 *
 * Description:	  Disables CVREF
 *
 * PreCondition:  None
 *
 * Inputs:	  	  None
 *
 * Output:        None
 *
 * Example:	  	  CVREFClose()
 *
 ********************************************************************/
#define CVREFClose() 	(CVRCONCLR = _CVRCON_ON_MASK)


#endif
