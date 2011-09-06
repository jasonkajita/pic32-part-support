/******************************************************************************
 *
 *                  I2C Library definitions
 *
 ******************************************************************************
 * FileName:        I2C.h
 * Dependencies:    p32xxxx.h
 *                  peripheral/int.h
 * Processor:       PIC32
 *
 * Compiler:        MPLAB C Compiler for PIC32 MCUs
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc.
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
 * $Id: I2C.h,v 1.1 2006/10/16 21:47:03 C12770 Exp $
 * $Name:  $
 *
 *****************************************************************************/
#ifndef _I2CAPI_H_
#define _I2CAPI_H_

#include <p32xxxx.h>
#include <peripheral/int.h>

// *****************************************************************************
// *****************************************************************************
// Section: Constants & Data Types
// *****************************************************************************
// *****************************************************************************

/* I2C Module
 
 Summary:
 Legacy I2C SCM Names
 
 Description:
 This defines the legacy SCM Port names for the  I2C modules.
 
 Remarks:
 The caller should not rely on the specific numbers assigned to any of 
 these values as they may change from one processor ot the next.
 
 Not all modules will be available on all microcontrollers.  Refer to the 
 data sheet for the specific controller in use.
 */

#define I2C1A   I2C3
#define I2C2A   I2C4
#define I2C3A   I2C5

/******************************************************************************
 * <combinewith OpenI2C2>
 *
 * Function:        void OpenI2Cx( unsigned int config1, unsigned int brg )
 *
 * PreCondition:    None
 *
 * Input:           config1 - I2CxCON register bit definition
 *                  brg - I2CxBRG register bit definition
 *
 *					Note: An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        User-called function to initialize and configure the
 *                  I2C module 1.
 *
 * Example:         OpenI2C1( I2C1_ON | I2C1_10BIT_ADD | I2C1_STRICT_EN, 200 )
 *****************************************************************************/
#if defined _I2C1
	#define OpenI2C1(config, brg)	(I2C1CON = (config), I2C1BRG = (brg))
#endif

#if defined _I2C2
	#define OpenI2C2(config, brg)	(I2C2CON = (config), I2C2BRG = (brg))
#endif

	/****************************************
	 * Available options for config parameter
	 ****************************************/
	 	// I2C Enable control - values are mutually exclusive
		#define I2C_EN           	(1 << _I2C1CON_ON_POSITION)
		#define I2C_ON           	(1 << _I2C1CON_ON_POSITION)
		#define I2C_OFF          	0

	 	// I2C Stop-in-Idle control - values are mutually exclusive
		#define I2C_IDLE_STOP	 	(1 << _I2C1CON_SIDL_POSITION)
		#define I2C_IDLE_CON	 	(0)

	 	// I2C SCL Release control - values are mutually exclusive
		#define I2C_CLK_REL      	(1 << _I2C1CON_SCLREL_POSITION)
		#define I2C_CLK_HOLD     	0

	 	// I2C Strict addressing mode - values are mutually exclusive
		#define I2C_STRICT_EN    	(1 << _I2C1CON_STRICT_POSITION)
		#define I2C_STRICT_DIS   	0

	 	// I2C Address mode - values are mutually exclusive
		#define I2C_10BIT_ADD  		(1 << _I2C1CON_A10M_POSITION)
		#define I2C_7BIT_ADD     	0

	 	// I2C Slew Rate control - values are mutually exclusive
		#define I2C_SLW_DIS      	(1 << _I2C1CON_DISSLW_POSITION)
		#define I2C_SLW_EN		 	0

	 	// I2C SMBus Input level control - values are mutually exclusive
		#define I2C_SM_EN        	(1 << _I2C1CON_SMEN_POSITION)
		#define I2C_SM_DIS       	0

	 	// I2C General call control - values are mutually exclusive
		#define I2C_GC_EN        	(1 << _I2C1CON_GCEN_POSITION)
		#define I2C_GC_DIS       	0

	 	// I2C Acknolwedge data bit control - values are mutually exclusive
		#define I2C_ACKDT         	(1 << _I2C1CON_ACKDT_POSITION)
		#define I2C_NACK         	(1 << _I2C1CON_ACKDT_POSITION)
		#define I2C_ACK          	0

	 	// I2C Acknolwedge Sequence control - values are mutually exclusive
		#define I2C_ACK_EN       	(1 << _I2C1CON_ACKEN_POSITION)
		#define I2C_ACK_DIS      	0

	 	// I2C Receive control - values are mutually exclusive
		#define I2C_RCV_EN       	(1 << _I2C1CON_RCEN_POSITION)
		#define I2C_RCV_DIS      	0

	 	// I2C Stop condition control - values are mutually exclusive
		#define I2C_STOP_EN      	(1 << _I2C1CON_PEN_POSITION)
		#define I2C_STOP_DIS     	0

	 	// I2C Restart condition control - values are mutually exclusive
		#define I2C_RESTART_EN   	(1 << _I2C1CON_RSEN_POSITION)
		#define I2C_RESTART_DIS  	0

	 	// I2C Start condition control - values are mutually exclusive
		#define I2C_START_EN   		(1 << _I2C1CON_SEN_POSITION)
		#define I2C_START_DIS  		0


	/******************************************************************************
	 * Parameter values to be used with OpenI2C1()
	 *****************************************************************************/
	#define I2C1_STR_EN			(1 << _I2C1CON_STREN_POSITION)
	#define I2C1_STR_DIS  		0

	#define I2C_STR_EN			(1 << _I2C1CON_STREN_POSITION)
	#define I2C_STR_DIS  		0

	/****************************************
	 * End config parameter values
	 ****************************************/


/******************************************************************************
 * <combinewith SetPriorityIntI2C2>
 *
 * Function:        void SetPriorityIntI2Cx( config )
 *
 * PreCondition:    None
 *
 * Input:           config - see below
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Sets priority and sub-priority values
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	#define SetPriorityIntI2C1(config)    (mI2C1ClearAllIntFlags(), mI2C1SetIntPriority((config)&7), mI2C1SetIntSubPriority(((config)>>4)&3), mI2C1BIntEnable((config)>>15), mI2C1SIntEnable(((config)>>14) & 0x01), mI2C1MIntEnable(((config)>>13) & 0x01))
#endif

#if defined _I2C2
	#define SetPriorityIntI2C2(config)    (mI2C2ClearAllIntFlags(), mI2C2SetIntPriority((config)&7), mI2C2SetIntSubPriority(((config)>>4)&3), mI2C2BIntEnable((config)>>15), mI2C2SIntEnable(((config)>>14) & 0x01), mI2C2MIntEnable(((config)>>13) & 0x01))
#endif

	/***********************************
	 * Available options for the priority parameter
	 ************************************/
		// Priority for I2C Interrupts - values are mutually exclusive
		#define I2C_INT_PRI_7		(7)
		#define I2C_INT_PRI_6		(6)
		#define I2C_INT_PRI_5		(5)
		#define I2C_INT_PRI_4		(4)
		#define I2C_INT_PRI_3		(3)
		#define I2C_INT_PRI_2		(2)
		#define I2C_INT_PRI_1		(1)
		#define I2C_INT_PRI_0		(0)


		// SUB-Priority for I2C Interrupts - values are mutually exclusive
		#define I2C_INT_SUB_PRI_3	(3 << 4)
		#define I2C_INT_SUB_PRI_2	(2 << 4)
		#define I2C_INT_SUB_PRI_1	(1 << 4)
		#define I2C_INT_SUB_PRI_0	(0 << 4)

		// Interrupt on/off - values are mutually exclusive
		#define I2C_INT_ON			(7 << 13)
        #define I2C_INT_BUS_ERR     (1 << 15)     
        #define I2C_INT_SLAVE       (1 << 14)
        #define I2C_INT_MASTER      (1 << 13)
        #define I2C_INT_OFF			(0)

	/***********************************
	 * End config parameter values
	 ************************************/


/******************************************************************************
 * <combinewith DisableIntSI2C1, EnableIntSI2C2, DisableIntSI2C2>
 *
 * Function:        void EnableIntSI2Cx
 *					void DisableIntSI2Cx
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Enables and disables Slave I2C interrupt
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	#define EnableIntSI2C1                   mI2C1SIntEnable(1)
	#define DisableIntSI2C1                  mI2C1SIntEnable(0)
#endif

#if defined _I2C2
	#define EnableIntSI2C2                   mI2C2SIntEnable(1)
	#define DisableIntSI2C2                  mI2C2SIntEnable(0)
#endif


/******************************************************************************
 * <combinewith DisableIntMI2C1, EnableIntMI2C2, DisableIntMI2C2>
 *
 * Function:        void EnableIntMI2Cx
 *					void DisableIntMI2Cx
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Enables and disables Master I2C interrupt
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	#define EnableIntMI2C1                   mI2C1MIntEnable(1)
	#define DisableIntMI2C1                  mI2C1MIntEnable(0)
#endif

#if defined _I2C2
	#define EnableIntMI2C2                   mI2C2MIntEnable(1)
	#define DisableIntMI2C2                  mI2C2MIntEnable(0)
#endif


/******************************************************************************
 * <combinewith DisableIntBI2C1, EnableIntBI2C2, DisableIntBI2C2>
 *
 * Function:        void EnableIntBI2Cx
 *					void DisableIntBI2Cx
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Enables and disables I2C bus collision interrupt
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	#define EnableIntBI2C1                   mI2C1BIntEnable(1)
	#define DisableIntBI2C1                  mI2C1BIntEnable(0)
#endif

#if defined _I2C2
	#define EnableIntBI2C2                   mI2C2BIntEnable(1)
	#define DisableIntBI2C2                  mI2C2BIntEnable(0)
#endif


/******************************************************************************
 * <combinewith MasterputcI2C1, SlaveputcI2C2, MasterputcI2C2>
 *
 * Function:        void SlaveputcI2Cx(int v)
 *					void MasterputcI2Cx(int v)
 *
 * PreCondition:    None
 *
 * Input:           data to be 'put' on I2C bus
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Writes a data character on I2C buffer
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	#define SlaveputcI2C1(v) 				SlaveWriteI2C1(v)
	#define MasterputcI2C1(v) 				MasterWriteI2C1(v)
#endif

#if defined _I2C2
	#define SlaveputcI2C2(v) 				SlaveWriteI2C2(v)
	#define MasterputcI2C2(v) 				MasterWriteI2C2(v)
#endif


/******************************************************************************
 * <combinewith StartI2C2>
 *
 * Function:        void StartI2Cx( void )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Generates START condition during master mode
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	#define StartI2C1() (I2C1CONSET = _I2C1CON_SEN_MASK)
#endif

#if defined _I2C2
	#define StartI2C2() (I2C2CONSET = _I2C2CON_SEN_MASK)
#endif


/******************************************************************************
 * <combinewith StopI2C2>
 *
 * Function:        void StopI2Cx( void )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Generates STOP condition during master mode
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	#define StopI2C1() (I2C1CONSET = _I2C1CON_PEN_MASK)
#endif

#if defined _I2C2
	#define StopI2C2() (I2C2CONSET = _I2C1CON_PEN_MASK)
#endif



/******************************************************************************
 * <combinewith AckI2C2>
 *
 * Function:        void AckI2C1( void )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Generates ACK condition during master mode
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	#define AckI2C1()	(I2C1CONCLR = _I2C1CON_ACKDT_MASK, I2C1CONSET = _I2C1CON_ACKEN_MASK)
#endif

#if defined _I2C2
	#define AckI2C2()	(I2C2CONCLR = _I2C2CON_ACKDT_MASK, I2C2CONSET = _I2C2CON_ACKEN_MASK)
#endif

/******************************************************************************
 * <combinewith NotAckI2C2>
 *
 * Function:        void NotAckI2Cx( void )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Generates NAK condition during master mode
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	#define NotAckI2C1() (I2C1CONSET = _I2C1CON_ACKDT_MASK, I2C1CONSET = _I2C1CON_ACKEN_MASK)
#endif

#if defined _I2C2
	#define NotAckI2C2() (I2C2CONSET = _I2C2CON_ACKDT_MASK, I2C2CONSET = _I2C2CON_ACKEN_MASK)
#endif


/******************************************************************************
 * <combinewith CloseI2C2>
 *
 * Function:        void CloseI2Cx( void )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Disables the I2C module by
 *                  clearing the I2CEN/ON bit in I2CxCON register and
 *                  disabling MI2C, SI2C and BI2C interrupts.
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	#define CloseI2C1() (I2C1CONCLR = _I2C1CON_ON_MASK, DisableIntSI2C1, DisableIntMI2C1, DisableIntBI2C1)
#endif

#if defined _I2C2
	#define CloseI2C2() (I2C2CONCLR = _I2C2CON_ON_MASK, DisableIntSI2C2, DisableIntMI2C2, DisableIntBI2C2)
#endif


/******************************************************************************
 * <combinewith RestartI2C2>
 *
 * Function:        void RestartI2Cx( void )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Generates RESTART condition during master mode
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	#define RestartI2C1() (I2C1CONSET = _I2C1CON_RSEN_MASK)
#endif

#if defined _I2C2
	#define RestartI2C2() (I2C2CONSET = _I2C2CON_RSEN_MASK)
#endif


/******************************************************************************
 * <combinewith DataRdyI2C2>
 *
 * Function:        int DataRdyI2Cx( void )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          0 - Data is NOT ready (receive not complete and
 *                      I2C1RCV is empty)
 *                  1 - Data is ready (receive complete and I2C1RCV
 *                      is full)
 *
 * Side Effects:    None
 *
 * Overview:        Provides the status whether the
 *                  receive buffer is full by returning the RBF bit
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	#define DataRdyI2C1() (I2C1STATbits.RBF)
#endif


#if defined _I2C2
	#define DataRdyI2C2() (I2C2STATbits.RBF)
#endif

/******************************************************************************
 * <combinewith IdleI2C2>
 *
 * Function:        void IdleI2Cx( void )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Generates wait condition until I2C bus is idle
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	void IdleI2C1( void );
#endif

#if defined _I2C2
	void IdleI2C2( void );
#endif


/******************************************************************************
 * <combinewith MasterReadI2C2>
 *
 * Function:        unsigned char MasterReadI2Cx( void )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          1 byte of data
 *
 * Side Effects:    None
 *
 * Overview:        Reads a single byte from the I2C bus.
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	unsigned char MasterReadI2C1( void );
#endif

#if defined _I2C2
	unsigned char MasterReadI2C2( void );
#endif

/******************************************************************************
 * <combinewith MasterWriteI2C2>
 *
 * Function:        unsigned int MasterWriteI2C2( unsigned char data )
 *
 * PreCondition:    None
 *
 * Input:           data - 1 byte of data
 *
 * Output:          0 - Operation successful
 *                  -1 - Operation failed due to IWCOL bit is set
 *
 * Side Effects:    None
 *
 * Overview:        Writes a single byte to the I2C bus.
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	unsigned int MasterWriteI2C1( unsigned char data );
#endif

#if defined _I2C2
	unsigned int MasterWriteI2C2( unsigned char data );
#endif

/******************************************************************************
 * <combinewith MastergetsI2C2>
 *
 * Function:        unsigned int MastergetsI2Cx( unsigned int length,
 *                                               unsigned char *data,
 *                                               unsigned int I2cDataWait )
 *
 * PreCondition:    None
 *
 * Input:           length -  length of data obtained
 *                  data - output buffer for data
 *                  I2cDataWait -
 *
 * Output:          0 - Operation successful
 *
 * Side Effects:    None
 *
 * Overview:        Reads a predetermined number of
 *                  byte(s) from the I2C bus.
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	unsigned int MastergetsI2C1( unsigned int length, unsigned char *data,
                                    unsigned int I2cDataWait );
#endif

#if defined _I2C2
	unsigned int MastergetsI2C2( unsigned int length, unsigned char *data,
                                    unsigned int I2cDataWait );
#endif


/******************************************************************************
 * <combinewith MasterputsI2C2>
 *
 * Function:        unsigned int MasterputsI2Cx( unsigned char *data )
 *
 * PreCondition:    None
 *
 * Input:           data - input data to be written
 *
 * Output:          0 - Operation successful
 *
 * Side Effects:    None
 *
 * Overview:        Writes a string to the I2C bus.
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	unsigned int MasterputsI2C1( unsigned char *data );
#endif

#if defined _I2C2
	unsigned int MasterputsI2C2( unsigned char *data );
#endif


/******************************************************************************
 * <combinewith SlaveReadI2C2>
 *
 * Function:        unsigned char SlaveReadI2Cx( void )
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          1 byte of data
 *
 * Side Effects:    None
 *
 * Overview:        Reads a single byte from the I2C bus.
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	unsigned char SlaveReadI2C1( void );
#endif

#if defined _I2C2
	unsigned char SlaveReadI2C2( void );
#endif

/******************************************************************************
 * <combinewith SlaveWriteI2C2>
 *
 * Function:        void SlaveWriteI2Cx( unsigned char data )
 *
 * PreCondition:    None
 *
 * Input:           data - 1 byte of data
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Writes a single byte to the I2C bus.
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	void SlaveWriteI2C1( unsigned char data );
#endif

#if defined _I2C2
	void SlaveWriteI2C2( unsigned char data );
#endif

/******************************************************************************
 * <combinewith SlavegetsI2C2>
 *
 * Function:        unsigned int SlavegetsI2Cx( unsigned char *data,
 *                                              unsigned int I2cDataWait )
 *
 * PreCondition:    None
 *
 * Input:           data - output buffer for data
 *                  I2cDataWait -
 *
 * Output:          number of bytes received
 *
 * Side Effects:    None
 *
 * Overview:        Reads bytes from the I2C bus until the STOP bit is received.
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	unsigned int SlavegetsI2C1( unsigned char *data,
                                   unsigned int I2cDataWait );
#endif

#if defined _I2C2
	unsigned int SlavegetsI2C2( unsigned char *data,
                                   unsigned int I2cDataWait );
#endif


/******************************************************************************
 * <combinewith SlaveputsI2C2>
 *
 * Function:        unsigned int SlaveputsI2Cx( unsigned char *data )
 *
 * PreCondition:    None
 *
 * Input:           data - input data to be written
 *
 * Output:          0 - Operation successful
 *
 * Side Effects:    None
 *
 * Overview:        Writes a string to the I2C bus.
 *
 * Note:            None
 *****************************************************************************/
#if defined _I2C1
	unsigned int SlaveputsI2C1( unsigned char *data );
#endif

#if defined _I2C2
	unsigned int SlaveputsI2C2( unsigned char *data );
#endif

#endif
