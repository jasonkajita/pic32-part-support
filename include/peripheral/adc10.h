/*********************************************************************
 *
 *                  ADC10 Library definitions
 *
 *********************************************************************
 * FileName:        ADC10.h
 * Dependencies:
 * Processor:       PIC32
 *
 * Compiler:        MPLAB C Compiler for PIC32 MCUs
 *                  MPLAB IDE v8.10 or later
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the 'Company') for its PIC32 Microcontroller is intended
 * and supplied to you, the Company's customer, for use solely and
 * exclusively on Microchip PIC32 Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN 'AS IS' CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * $Id: adc10.h,v 1.4 2006/10/27 16:50:23 C12532 Exp $
 * $Name: 1.7 $
 *
 ********************************************************************/


#ifndef _ADC10_H_
#define _ADC10_H_

#include <p32xxxx.h>
#include <peripheral/int.h>

/*********************************************************************
 * Function:        void OpenADC10(unsigned int config1,
 *								   unsigned int config2,
 *								   unsigned int config3,
 *								   unsigned int configport,
 *								   unsigned int configscan)
 *
 * Description:     Configures ADC using passed parameters
 *
 * PreCondition:    None
 *
 * Inputs:          AD1CON1 config, AD1CON2 config, AD1CON3 config, port pin config, AD1CSSL config
 *                   An absent symbol is automatically taken as off or default value.
 *							See below for available options for each input
 *
 * Output:          None
 *
 * Example:         OpenADC10(ADC_MODULE_ON | ADC_IDLE_CONTINUE | ADC_FORMAT_FRACT16 | ADC_CLK_AUTO |  ADC_AUTO_SAMPLING_ON ,
 *                   ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_2 |  ADC_BUF_16,
 *                   ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_12,
 *                   ENABLE_AN0_ANA |  ENABLE_AN1_ANA,
 *                   SKIP_SCAN_AN2 | SKIP_SCAN_AN3 | SKIP_SCAN_AN4 | SKIP_SCAN_AN5 | SKIP_SCAN_AN6 | SKIP_SCAN_AN7 | SKIP_SCAN_AN8
 *                   SKIP_SCAN_AN9 | SKIP_SCAN_AN10 | SKIP_SCAN_AN11 | SKIP_SCAN_AN12 | SKIP_SCAN_AN13 | SKIP_SCAN_AN14 | SKIP_SCAN_AN15)
 *
 ********************************************************************/
#define OpenADC10(config1, config2, config3, configport, configscan) (mPORTBSetPinsAnalogIn(configport), AD1CSSL = ~(configscan), AD1CON3 = (config3), AD1CON2 = (config2), AD1CON1 = (config1) )

	/****************************************
	 * Available options for config1 parameter
	 ****************************************/
		/* Module ON/OFF  - Values are mutually exclusive */
		#define ADC_MODULE_ON            (1 << _AD1CON1_ADON_POSITION)    /* A/D Converter on*/
		#define ADC_MODULE_OFF           (0)      		          /* A/D Converter off*/

		/* IDLE mode operation - Values are mutually exclusive */
		#define ADC_IDLE_CONTINUE        (1 << _AD1CON1_ADSIDL_POSITION)  /* A/D Operate in Idle mode */
		#define ADC_IDLE_STOP            (0) 			          /* A/D Stop in Idle mode */

		/* Result output format - these options are muttually exclusive */
		#define ADC_FORMAT_SIGN_FRACT    (0x03 << _AD1CON1_FORM_POSITION) /* A/D data format 16-bit signed fractional  DsPic compatable (16 bit formatted result)*/
		#define ADC_FORMAT_FRACT         (0x02 << _AD1CON1_FORM_POSITION) /* A/D data format 16-bit fractional         DsPic compatable (16 bit formatted result)*/
		#define ADC_FORMAT_SIGN_INT      (0x01 << _AD1CON1_FORM_POSITION) /* A/D data format 16-bit signed integer     DsPic compatable (16 bit formatted result)*/
		#define ADC_FORMAT_INTG          (0x00 << _AD1CON1_FORM_POSITION) /* A/D data format 16-bit integer            DsPic compatable (16 bit formatted result)*/
		#define ADC_FORMAT_SIGN_FRACT16  (0x03 << _AD1CON1_FORM_POSITION) /* A/D data format 16-bit signed fractional */
		#define ADC_FORMAT_FRACT16       (0x02 << _AD1CON1_FORM_POSITION) /* A/D data format 16-bit fractional */
		#define ADC_FORMAT_SIGN_INT16    (0x01 << _AD1CON1_FORM_POSITION) /* A/D data format 16-bit signed integer */
		#define ADC_FORMAT_INTG16        (0x00 << _AD1CON1_FORM_POSITION) /* A/D data format 16-bit integer */
		#define ADC_FORMAT_SIGN_FRACT32  (0x07 << _AD1CON1_FORM_POSITION) /* A/D data format 32-bit signed fractional */
		#define ADC_FORMAT_FRACT32       (0x06 << _AD1CON1_FORM_POSITION) /* A/D data format 32-bit fractional */
		#define ADC_FORMAT_SIGN_INT32    (0x05 << _AD1CON1_FORM_POSITION) /* A/D data format 32-bit signed integer */
		#define ADC_FORMAT_INTG32        (0x04 << _AD1CON1_FORM_POSITION) /* A/D data format 32-bit integer */

		/* Conversion trigger source - Values are mutually exclusive */
		#define ADC_CLK_AUTO             (7 << _AD1CON1_SSRC_POSITION)    /* Internal counter ends sampling and starts conversion (Auto convert) */
		#define ADC_CLK_TMR              (2 << _AD1CON1_SSRC_POSITION)    /* Timer compare ends sampling and starts conversion */
		#define ADC_CLK_INT0             (1 << _AD1CON1_SSRC_POSITION)    /* Active transition on INT0 ends sampling and starts conversion */
		#define ADC_CLK_MANUAL           (0 << _AD1CON1_SSRC_POSITION)    /* Clearing sample (SAMP) bit ends sampling and starts conversion */

		/* Autosampling selection - Values are mutually exclusive */
		#define ADC_AUTO_SAMPLING_ON     (1 << _AD1CON1_ASAM_POSITION)    /* Auto sampling Select */
		#define ADC_AUTO_SAMPLING_OFF    (0)             		  /* Samples multiple channels individually in sequence */

		/* Sample enable/disable - Values are mutually exclusive */
		#define ADC_SAMP_ON              (1 << _AD1CON1_SAMP_POSITION)	  /* sample / hold amplifiers are sampling */
		#define ADC_SAMP_OFF             (0)             		  /* sample / hold amplifiers are holding */

		/* DONE bit defines */
		#define ADC_CONVERSION_DONE      (1 << _AD1CON1_DONE_POSITION) 	  /* terminate current conversion */
	/****************************************
	 * End config1 parameter values
	 ****************************************/

	/***********************************
	 * Available options for the config2 parameter
	 ************************************/
		/* Voltage reference - Values are mutually exclusive */
		#define ADC_VREF_AVDD_AVSS        (0)                             /* A/D Voltage reference configuration Vref+ is AVdd and Vref- is AVss */
		#define ADC_VREF_EXT_AVSS         (1 << _AD1CON2_VCFG_POSITION)   /* A/D Voltage reference configuration Vref+ external and Vref- is AVss */
		#define ADC_VREF_AVDD_EXT         (2 << _AD1CON2_VCFG_POSITION)   /* A/D Voltage reference configuration Vref+ AVdd and Vref- external */
		#define ADC_VREF_EXT_EXT          (3 << _AD1CON2_VCFG_POSITION)   /* A/D Voltage reference configuration both Vref+ and Vref- are external */

		/* Offset calibration values - Values are mutually exclusive */
		#define ADC_OFFSET_CAL_ENABLE     (1 << _AD1CON2_OFFCAL_POSITION) /* Offset calibration enable */
		#define ADC_OFFSET_CAL_DISABLE    (0)                             /* Offset calibration disable (normal operation) */

		/* Scan selection - Values are mutually exclusive */
		#define ADC_SCAN_ON               (1 << _AD1CON2_CSCNA_POSITION)  /* A/D Scan Input Selections for CH0 during SAMPLE A */
		#define ADC_SCAN_OFF              (0)             	          	  /* A/D Do notScan Input Selections for CH0+ during SAMPLE A */

		/* Number of samples between interrupts - Values are mutually exclusive */
		#define ADC_SAMPLES_PER_INT_1     (0)                             /* A/D Interrupt at the completion of conversion for each sample */
		#define ADC_SAMPLES_PER_INT_2     (0x1 << _AD1CON2_SMPI_POSITION) /* A/D Interrupt at the completion of conversion for each 2nd sample */
		#define ADC_SAMPLES_PER_INT_3     (0x2 << _AD1CON2_SMPI_POSITION) /* A/D interrupt at the completion of conversion for each 3rd sample */
		#define ADC_SAMPLES_PER_INT_4     (0x3 << _AD1CON2_SMPI_POSITION) /* A/D interrupt at the completion of conversion for each 4th sample */
		#define ADC_SAMPLES_PER_INT_5     (0x4 << _AD1CON2_SMPI_POSITION) /* A/D interrupt at the completion of conversion for each 5th sample */
		#define ADC_SAMPLES_PER_INT_6     (0x5 << _AD1CON2_SMPI_POSITION) /* A/D interrupt at the completion of conversion for each 6th sample */
		#define ADC_SAMPLES_PER_INT_7     (0x6 << _AD1CON2_SMPI_POSITION) /* A/D interrupt at the completion of conversion for each 7th sample */
		#define ADC_SAMPLES_PER_INT_8     (0x7 << _AD1CON2_SMPI_POSITION) /* A/D interrupt at the completion of conversion for each 8th sample */
		#define ADC_SAMPLES_PER_INT_9     (0x8 << _AD1CON2_SMPI_POSITION) /* A/D interrupt at the completion of conversion for each 9th sample */
		#define ADC_SAMPLES_PER_INT_10    (0x9 << _AD1CON2_SMPI_POSITION) /* A/D interrupt at the completion of conversion for each 10th sample */
		#define ADC_SAMPLES_PER_INT_11    (0xA << _AD1CON2_SMPI_POSITION) /* A/D interrupt at the completion of conversion for each 11th sample */
		#define ADC_SAMPLES_PER_INT_12    (0xB << _AD1CON2_SMPI_POSITION) /* A/D interrupt at the completion of conversion for each 12th sample */
		#define ADC_SAMPLES_PER_INT_13    (0xC << _AD1CON2_SMPI_POSITION) /* A/D interrupt at the completion of conversion for each 13th sample */
		#define ADC_SAMPLES_PER_INT_14    (0xD << _AD1CON2_SMPI_POSITION) /* A/D interrupt at the completion of conversion for each 14th sample */
		#define ADC_SAMPLES_PER_INT_15    (0xE << _AD1CON2_SMPI_POSITION) /* A/D interrupt at the completion of conversion for each 15th sample */
		#define ADC_SAMPLES_PER_INT_16    (0xF << _AD1CON2_SMPI_POSITION) /* A/D interrupt at the completion of conversion for each 16th sample */

		/* Buffer mode select - Values are mutually exclusive */
		#define ADC_ALT_BUF_ON            (1 << _AD1CON2_BUFM_POSITION)   /* Buffer configured as 2 8-word buffers */
		#define ADC_ALT_BUF_OFF           (0)             		  /* Buffer configured as 1 16-word buffer */
		#define ADC_BUF_8                 (1 << _AD1CON2_BUFM_POSITION)   /* Buffer configured as two 8-word buffers */
		#define ADC_BUF_16                (0)                             /* Buffer configured as one 16-word buffer */

		/* Alternate input sample mode select - Values are mutually exclusive */
		#define ADC_ALT_INPUT_ON          (1 << _AD1CON2_ALTS_POSITION)   /* alternate between MUXA and MUXB */
		#define ADC_ALT_INPUT_OFF         (0)             		  /* use MUXA only */
	/***********************************
	 * End config2 parameter values
	 ************************************/

	/*******************************
	 * Avaialble options for the config3 parameter
	 ********************************/
		/* Auto sample time bits - Values are mutually exclusive */
		#define ADC_SAMPLE_TIME_0         (0x00 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 0 Tad */
		#define ADC_SAMPLE_TIME_1         (0x01 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 1 Tad */
		#define ADC_SAMPLE_TIME_2         (0x02 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 2 Tad */
		#define ADC_SAMPLE_TIME_3         (0x03 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 3 Tad */
		#define ADC_SAMPLE_TIME_4         (0x04 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 4 Tad */
		#define ADC_SAMPLE_TIME_5         (0x05 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 5 Tad */
		#define ADC_SAMPLE_TIME_6         (0x06 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 6 Tad */
		#define ADC_SAMPLE_TIME_7         (0x07 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 7 Tad */
		#define ADC_SAMPLE_TIME_8         (0x08 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 8 Tad */
		#define ADC_SAMPLE_TIME_9         (0x09 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 9 Tad */
		#define ADC_SAMPLE_TIME_10        (0x0A << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 10 Tad */
		#define ADC_SAMPLE_TIME_11        (0x0B << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 11 Tad */
		#define ADC_SAMPLE_TIME_12        (0x0C << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 12 Tad */
		#define ADC_SAMPLE_TIME_13        (0x0D << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 13 Tad */
		#define ADC_SAMPLE_TIME_14        (0x0E << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 14 Tad */
		#define ADC_SAMPLE_TIME_15        (0x0F << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 15 Tad */
		#define ADC_SAMPLE_TIME_16        (0x10 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 16 Tad */
		#define ADC_SAMPLE_TIME_17        (0x11 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 17 Tad */
		#define ADC_SAMPLE_TIME_18        (0x12 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 18 Tad */
		#define ADC_SAMPLE_TIME_19        (0x13 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 19 Tad */
		#define ADC_SAMPLE_TIME_20        (0x14 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 20 Tad */
		#define ADC_SAMPLE_TIME_21        (0x15 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 21 Tad */
		#define ADC_SAMPLE_TIME_22        (0x16 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 22 Tad */
		#define ADC_SAMPLE_TIME_23        (0x17 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 23 Tad */
		#define ADC_SAMPLE_TIME_24        (0x18 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 24 Tad */
		#define ADC_SAMPLE_TIME_25        (0x19 << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 25 Tad */
		#define ADC_SAMPLE_TIME_26        (0x1A << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 26 Tad */
		#define ADC_SAMPLE_TIME_27        (0x1B << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 27 Tad */
		#define ADC_SAMPLE_TIME_28        (0x1C << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 28 Tad */
		#define ADC_SAMPLE_TIME_29        (0x1D << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 29 Tad */
		#define ADC_SAMPLE_TIME_30        (0x1C << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 30 Tad */
		#define ADC_SAMPLE_TIME_31        (0x1F << _AD1CON3_SAMC_POSITION)     /* A/D Auto Sample Time 31 Tad */

		/* Conversion clock source select - Values are mutually exclusive */
		#define ADC_CONV_CLK_INTERNAL_RC  (1 << _AD1CON3_ADRC_POSITION)   /* A/D Conversion Clock Source internal RC Clock */
		#define ADC_CONV_CLK_SYSTEM       (0)                             /* for compatability, actually uses PB clock */
		#define ADC_CONV_CLK_PB           (0)                             /* A/D Conversion Clock Source Clock derived from PB clock */


		/* Conversion clock select - Values are mutually exclusive */
		#define ADC_CONV_CLK_32Tcy       (0x003F << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_63Tcy2      (0x003E << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_31Tcy       (0x003D << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_61Tcy2      (0x003C << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_30Tcy       (0x003B << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_59Tcy2      (0x003A << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_29Tcy       (0x0039 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_57Tcy2      (0x0038 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_28Tcy       (0x0037 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_55Tcy2      (0x0036 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_27Tcy       (0x0035 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_53Tcy2      (0x0034 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_26Tcy       (0x0033 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_51Tcy2      (0x0032 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_25Tcy       (0x0031 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_49Tcy2      (0x0030 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_24Tcy       (0x002F << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_47Tcy2      (0x002E << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_23Tcy       (0x002D << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_45Tcy2      (0x002C << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_22Tcy       (0x002B << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_43Tcy2      (0x002A << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_21Tcy       (0x0029 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_41Tcy2      (0x0028 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_20Tcy       (0x0027 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_39Tcy2      (0x0026 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_19Tcy       (0x0025 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_37Tcy2      (0x0024 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_18Tcy       (0x0023 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_35Tcy2      (0x0022 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_17Tcy       (0x0021 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_33Tcy2      (0x0020 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_16Tcy       (0x001F << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_31Tcy2      (0x001E << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_15Tcy       (0x001D << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_29Tcy2      (0x001C << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_14Tcy       (0x001B << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_27Tcy2      (0x001A << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_13Tcy       (0x0019 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_25Tcy2      (0x0018 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_12Tcy       (0x0017 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_23Tcy2      (0x0016 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_11Tcy       (0x0015 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_21Tcy2      (0x0014 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_10Tcy       (0x0013 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_19Tcy2      (0x0012 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_9Tcy        (0x0011 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_17Tcy2      (0x0010 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_8Tcy        (0x000F << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_15Tcy2      (0x000E << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_7Tcy        (0x000D << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_13Tcy2      (0x000C << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_6Tcy        (0x000B << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_11Tcy2      (0x000A << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_5Tcy        (0x0009 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_9Tcy2       (0x0008 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_4Tcy        (0x0007 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_7Tcy2       (0x0006 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_3Tcy        (0x0005 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_5Tcy2       (0x0004 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_2Tcy        (0x0003 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_3Tcy2       (0x0002 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_Tcy         (0x0001 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
		#define ADC_CONV_CLK_Tcy2        (0x0000 << _AD1CON3_ADCS_POSITION)    /* A/D Conversion Clock Select bits */
	/***********************************
	 * End config3 parameter values
	 ************************************/

	/*******************************
	 * Avaialble options for the configport parameter
	 ********************************/
	 	/* Enable analog channels - Values are mutually exclusive */
		#define ENABLE_AN0_ANA            (1 << _AD1PCFG_PCFG0_POSITION)       /*Enable AN0 in analog mode */
		#define ENABLE_AN1_ANA            (1 << _AD1PCFG_PCFG1_POSITION)       /*Enable AN1 in analog mode */
		#define ENABLE_AN2_ANA            (1 << _AD1PCFG_PCFG2_POSITION)       /*Enable AN2 in analog mode */
		#define ENABLE_AN3_ANA            (1 << _AD1PCFG_PCFG3_POSITION)       /*Enable AN3 in analog mode */
		#define ENABLE_AN4_ANA            (1 << _AD1PCFG_PCFG4_POSITION)       /*Enable AN4 in analog mode */
		#define ENABLE_AN5_ANA            (1 << _AD1PCFG_PCFG5_POSITION)       /*Enable AN5 in analog mode */
		#define ENABLE_AN6_ANA            (1 << _AD1PCFG_PCFG6_POSITION)       /*Enable AN6 in analog mode */
		#define ENABLE_AN7_ANA            (1 << _AD1PCFG_PCFG7_POSITION)       /*Enable AN7 in analog mode */
		#define ENABLE_AN8_ANA            (1 << _AD1PCFG_PCFG8_POSITION)       /*Enable AN8 in analog mode */
		#define ENABLE_AN9_ANA            (1 << _AD1PCFG_PCFG9_POSITION)       /*Enable AN9 in analog mode */
		#define ENABLE_AN10_ANA           (1 << _AD1PCFG_PCFG10_POSITION)      /*Enable AN10 in analog mode */
		#define ENABLE_AN11_ANA           (1 << _AD1PCFG_PCFG11_POSITION)      /*Enable AN11 in analog mode */
		#define ENABLE_AN12_ANA           (1 << _AD1PCFG_PCFG12_POSITION)      /*Enable AN12 in analog mode */
		#define ENABLE_AN13_ANA           (1 << _AD1PCFG_PCFG13_POSITION)      /*Enable AN13 in analog mode */
		#define ENABLE_AN14_ANA           (1 << _AD1PCFG_PCFG14_POSITION)      /*Enable AN14 in analog mode */
		#define ENABLE_AN15_ANA           (1 << _AD1PCFG_PCFG15_POSITION)      /*Enable AN15 in analog mode */
		#define ENABLE_ALL_ANA            (0x0000)       		       	 	   /*Enable AN15 in analog mode */
		#define ENABLE_ALL_DIG            (0xFFFF)                             /*Enable AN15 in analog mode */
	/***********************************
	 * End configport parameter values
	 ************************************/

	/*******************************
	 * Avaialble options for the configscan parameter
	 ********************************/
	 	/* Channels to skip during auto scan mode - Values are mutually exclusive */
		#define SKIP_SCAN_AN0             (1 << _AD1CSSL_CSSL0_POSITION)       /*AN0 enable for Input Scan */
		#define SKIP_SCAN_AN1             (1 << _AD1CSSL_CSSL1_POSITION)       /*AN1 enable for Input Scan */
		#define SKIP_SCAN_AN2             (1 << _AD1CSSL_CSSL2_POSITION)       /*AN2 enable for Input Scan */
		#define SKIP_SCAN_AN3             (1 << _AD1CSSL_CSSL3_POSITION)       /*AN3 enable for Input Scan */
		#define SKIP_SCAN_AN4             (1 << _AD1CSSL_CSSL4_POSITION)       /*AN4 enable for Input Scan */
		#define SKIP_SCAN_AN5             (1 << _AD1CSSL_CSSL5_POSITION)       /*AN5 enable for Input Scan */
		#define SKIP_SCAN_AN6             (1 << _AD1CSSL_CSSL6_POSITION)       /*AN6 enable for Input Scan */
		#define SKIP_SCAN_AN7             (1 << _AD1CSSL_CSSL7_POSITION)       /*AN7 enable for Input Scan */
		#define SKIP_SCAN_AN8             (1 << _AD1CSSL_CSSL8_POSITION)       /*AN8 enable for Input Scan */
		#define SKIP_SCAN_AN9             (1 << _AD1CSSL_CSSL9_POSITION)       /*AN9 enable for Input Scan */
		#define SKIP_SCAN_AN10            (1 << _AD1CSSL_CSSL10_POSITION)      /*AN10 enable for Input Scan */
		#define SKIP_SCAN_AN11            (1 << _AD1CSSL_CSSL11_POSITION)      /*AN11 enable for Input Scan */
		#define SKIP_SCAN_AN12            (1 << _AD1CSSL_CSSL12_POSITION)      /*AN12 enable for Input Scan */
		#define SKIP_SCAN_AN13            (1 << _AD1CSSL_CSSL13_POSITION)      /*AN13 enable for Input Scan */
		#define SKIP_SCAN_AN14            (1 << _AD1CSSL_CSSL14_POSITION)      /*AN14 enable for Input Scan */
		#define SKIP_SCAN_AN15            (1 << _AD1CSSL_CSSL15_POSITION)      /*AN15 enable for Input Scan */
		#define SKIP_SCAN_ALL             (0xFFFF)       		       		   /*Enable AN0-AN15 for Input Scan */
	/***********************************
	 * End configscan parameter values
	 ************************************/


/*********************************************************************
 * Function:        ConfigIntADC10(unsigned int config)
 *
 * Description:     Configures ADC interrupt
 *
 * PreCondition:    None
 *
 * Inputs:          priority: Bit-wise OR value of ADC10_INT_XXX, ADC10_INT_PRIOR_XXX
 *                   and ADC10_INT_SUB_PRIOR_X
 *                   An absent symbol is automatically taken as off or default value.
 *							See below for available options for each input
 *
 *
 * Output:          None
 *
 * Example:         ConfigIntADC10(ADC10_INT_ON | ADC10_INT_PRIOR_3 | ADC10_INT_SUB_PRIOR1)
 *
 ********************************************************************/
#define ConfigIntADC10(config) ( mAD1ClearIntFlag(), mAD1SetIntPriority(((config) & 7)), mAD1SetIntSubPriority((((config) >> 4) & 3)), mAD1IntEnable(((config) >> 15)) )

	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		/* Priority values -  Values are mutually exclusive */
		#define ADC_INT_PRI_7            (7)
		#define ADC_INT_PRI_6            (6)
		#define ADC_INT_PRI_5            (5)
		#define ADC_INT_PRI_4            (4)
		#define ADC_INT_PRI_3            (3)
		#define ADC_INT_PRI_2            (2)
		#define ADC_INT_PRI_1            (1)
		#define ADC_INT_PRI_0            (0)

		/* Sub-priority values - values are mutually exclusive */
		#define ADC_INT_SUB_PRI_3        (3 << 4)
		#define ADC_INT_SUB_PRI_2        (2 << 4)
		#define ADC_INT_SUB_PRI_1        (1 << 4)
		#define ADC_INT_SUB_PRI_0        (0 << 4)

		// Interrupt on/off - values are mutually exclusive
		#define ADC_INT_ON				 (1<<15)
		#define ADC_INT_OFF				 (0)

	/***********************************
	 * End config parameter values
	 ************************************/

/*********************************************************************
 * Function:        EnableADC10()
 *
 * Description:     Enables ADC
 *
 * PreCondition:    ADC should be configured
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Example:         EnableADC10()
 *
 ********************************************************************/
#define EnableADC10() (AD1CON1SET = _AD1CON1_ON_MASK)



/*********************************************************************
 * Function:        AcquireADC10()
 *
 * Description:     Starts ADC acquistion by setting sample bit (SAMP)
 *
 * PreCondition:    ADC must be configured for manual sampling mode
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Example:         AcquireADC10()
 *
 ********************************************************************/
#define AcquireADC10() (AD1CON1SET = _AD1CON1_SAMP_MASK)


/*********************************************************************
 * Function:        BusyADC10(void)
 *
 * Description:     Returns the status of the ADC DONE bit
 *
 * PreCondition:    None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Example:         BusyADC10()
 *
 ********************************************************************/
#define BusyADC10() (AD1CON1bits.DONE)

/*********************************************************************
 * Function:        ConvertADC10()
 *
 * Description:     Starts ADC conversion by clearing sample bit (SAMP)
 *
 * PreCondition:    ADC must be configured for manual sampling mode and
 *                   and acquistion complete (SAMP = 0)
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Example:         ConvertADC10()
 *
 ********************************************************************/
#define ConvertADC10() (AD1CON1CLR = _AD1CON1_SAMP_MASK)


/*********************************************************************
 * Function:        ReadActiveBufferADC10
 *
 * Description:     This function returns the buffer that is currently being filled by the ADC
 *
 * PreCondition:    ADC should be in dual buffer mode
 *
 * Inputs:          None
 *
 * Output:          0 if locations 0x0-0x7 are being written, 1 if locations 0x8-0xF are being written
 *
 * Example:         result = ReadActiveBufferADC10(3)
 *
 ********************************************************************/
#define ReadActiveBufferADC10() ( AD1CON2bits.BUFS )


/*********************************************************************
 * Function:        ReadADC10
 *
 * Description:     This function reads from one of the 16 ADC Buffers (ADCBUF0 - ADCBUFF)
 *
 * PreCondition:    None
 *
 * Inputs:          Offset from base (ADC1BUF0) of desired buffer
 *
 * Output:          value contained in desired buffer location
 *
 * Example:         result = ReadADC10(3)
 *
 * Note:	    ADC result registers are spaced 4 registers apart
 *
 ********************************************************************/
#define ReadADC10(bufIndex) (*(&ADC1BUF0+((bufIndex) * 4)))


/*********************************************************************
 * Function:        SetChanADC10(config)
 *
 * Description:     Configures the ADC MUX inputs
 *
 * PreCondition:    None
 *
 * Inputs:          Desired input configuration for muxes
 *                   An absent symbol is automatically taken as off or default value.
 *							See below for available options for each input
 *
 * Output:          None
 *
 * Example:         SetChanADC10( ADC_CH0_NEG_SAMPLEB_AN1 | ADC_CH0_POS_SAMPLEB_AN15 | ADC_CH0_NEG_SAMPLEA_NVREF
 *                   | ADC_CH0_POS_SAMPLEA_AN10 )
 *
 ********************************************************************/
#define SetChanADC10(config) (AD1CHS = (config))

	/******************************************************************************
	 * Available options for config parameter
	 *****************************************************************************/
		/* A/D Channel 0 positive input select for sample A - values are mutually exclusive */
		#define ADC_CH0_POS_SAMPLEA_AN15  (0xF << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN15 */
		#define ADC_CH0_POS_SAMPLEA_AN14  (0xE << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN14 */
		#define ADC_CH0_POS_SAMPLEA_AN13  (0xD << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN13 */
		#define ADC_CH0_POS_SAMPLEA_AN12  (0xC << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN12 */
		#define ADC_CH0_POS_SAMPLEA_AN11  (0xB << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN11 */
		#define ADC_CH0_POS_SAMPLEA_AN10  (0xA << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN10 */
		#define ADC_CH0_POS_SAMPLEA_AN9   (0x9 << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN9 */
		#define ADC_CH0_POS_SAMPLEA_AN8   (0x8 << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN8 */
		#define ADC_CH0_POS_SAMPLEA_AN7   (0x7 << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN7 */
		#define ADC_CH0_POS_SAMPLEA_AN6   (0x6 << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN6 */
		#define ADC_CH0_POS_SAMPLEA_AN5   (0x5 << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN5 */
		#define ADC_CH0_POS_SAMPLEA_AN4   (0x4 << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN4 */
		#define ADC_CH0_POS_SAMPLEA_AN3   (0x3 << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN3 */
		#define ADC_CH0_POS_SAMPLEA_AN2   (0x2 << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN2 */
		#define ADC_CH0_POS_SAMPLEA_AN1   (0x1 << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN1 */
		#define ADC_CH0_POS_SAMPLEA_AN0   (0x0 << _AD1CHS_CH0SA_POSITION)    /* A/D Chan 0 pos input select for SAMPLE A is AN0 */

		/* A/D channel 0 negative input select for sample A - values are mutually exclusive */
		#define ADC_CH0_NEG_SAMPLEA_AN1   (1 << _AD1CHS_CH0NA_POSITION)      /* A/D Channel 0 negative input select for SAMPLE A */
		#define ADC_CH0_NEG_SAMPLEA_NVREF (0)            /* A/D Channel 0 negative input select for SAMPLE B */


		/* A/D Channel 0 positive input select for sample B - values are mutually exclusive */
		#define ADC_CH0_POS_SAMPLEB_AN15  (0x0F << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN14  (0x0E << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN13  (0x0D << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN12  (0x0C << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN11  (0x0B << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN10  (0x0A << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN9   (0x09 << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN8   (0x08 << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN7   (0x07 << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN6   (0x06 << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN5   (0x05 << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN4   (0x04 << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN3   (0x03 << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN2   (0x02 << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN1   (0x01 << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */
		#define ADC_CH0_POS_SAMPLEB_AN0   (0x00 << _AD1CHS_CH0SB_POSITION)       /* A/D Channel 0 positive input select for SAMPLE B */

		/* A/D channel 0 negative input select for sample B - values are mutually exclusive */
		#define ADC_CH0_NEG_SAMPLEB_AN1   (1 << _AD1CHS_CH0NB_POSITION)          /* A/D Channel 0 negative input select for SAMPLE B */
		#define ADC_CH0_NEG_SAMPLEB_NVREF (0)              		         		 /* A/D Channel 0 negative input select for SAMPLE B */
	/***********************************
	 * End config parameter values
	 ************************************/


/*********************************************************************
 * Function:        CloseADC10(void)
 *
 * Description:     Switches off the ADC and disables the interrupt
 *
 * PreCondition:    None
 *
 * Inputs:          None
 *
 * Output:          None
 *
 * Example:         CloseADC10()
 *
 ********************************************************************/
#define CloseADC10() ( mAD1IntEnable(0), AD1CON1CLR = _AD1CON1_ON_MASK )


#endif
