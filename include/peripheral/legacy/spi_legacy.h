/*********************************************************************
 *
 *                  SPI Legacy Library definitions
 *
 *********************************************************************
 * FileName:        spi_legacy.h
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
 *
 ********************************************************************/

#ifndef _SPI_LEGACY_H_
#define _SPI_LEGACY_H_



#include <p32xxxx.h>
#include <peripheral/int.h>


#define SPI_CHANNEL1A   SPI_CHANNEL3
#define SPI_CHANNEL2A   SPI_CHANNEL2
#define SPI_CHANNEL3A   SPI_CHANNEL4

/*****************************************************
 * 	Legacy SPI functions
 * 	These functions are provided for backward compatibility only
 * 	They are no longer maintained!
 * 	New projects should not use them!
 *******************************************************/


// old configuration definitions
// configuration flags
typedef enum
{
	// master configuration
	SPI_CON_MSTEN = 	_SPIxCON_MASK_(MSTEN_MASK),	// set the Master mode
	SPI_CON_SMP = 		_SPIxCON_MASK_(SMP_MASK),	// Master Sample Phase for the input bit at the end of the data out time. Otherwise data is sampled in the middle.

	// slave configuration
	SPI_CON_SLVEN =		0,				// set the Slave mode
	SPI_CON_SSEN = 		_SPIxCON_MASK_(SSEN_MASK),	// enable the SS (Slave Select) input pin. 
	
	// clocking configuration
	SPI_CON_CKP = 		_SPIxCON_MASK_(CKP_MASK),	// set the clock polarity to (idle-high, active-low). Otherwise is (idle-low, active-high).
	SPI_CON_CKE = 		_SPIxCON_MASK_(CKE_MASK),	// set the Clock Edge to transmit from active to idle. Otherwise transmit when clock goes from idle to active

	// data characters configuration
	SPI_CON_MODE8 =		0,				// set 8 bits/char
	SPI_CON_MODE16 = 	_SPIxCON_MASK_(MODE16_MASK),	// set 16 bits/char
	SPI_CON_MODE32 = 	_SPIxCON_MASK_(MODE32_MASK),	// set 32 bits/char
	
	// framed mode configuration
	SPI_CON_FRMEN = 	_SPIxCON_MASK_(FRMEN_MASK),	// Enable the Framed SPI support. Otherwise the Framed SPI is disabled.
	SPI_CON_FRMSYNC = 	_SPIxCON_MASK_(FRMSYNC_MASK),	// Frame Sync Pulse (FSP) direction set to input (Frame Slave).
       								// Otherwise the FSP is output and the SPI channel operates as a Frame Master.
	SPI_CON_FRMPOL = 	_SPIxCON_MASK_(FRMPOL_MASK),	// FSP polarity set active high. Otherwise the FSP is active low.
	SPI_CON_SPIFE = 	_SPIxCON_MASK_(SPIFE_MASK),	// Set the Frame Sync Pulse (FSP) to coincide with the 1st bit clock.
       								// Otherwise the FSP precedes the 1st bit clock 

	// general configuration
	SPI_CON_DISSDO = 	_SPIxCON_MASK_(DISSDO_MASK),	// disable the usage of the SDO pin by the SPI
	SPI_CON_SIDL = 		_SPIxCON_MASK_(SIDL_MASK),	// enable the Halt in the CPU Idle mode. Otherwise the SPI will be still active when the CPU is in Idle mode. 
	SPI_CON_FRZ = 		_SPIxCON_MASK_(FRZ_MASK),	// Debug mode only: enable the Freeze operation while in Debug. Otherwise continue to operate.
	SPI_CON_ON = 		_SPIxCON_MASK_(ON_MASK),	// turn ON the SPI (not used in SpiChnOpen)
}SpiCtrlFlags;	// control flags that can be used with SpiChnOpen.




/*********************************************************************
 * Function:        void SpiChnChgMode(SpiChannel chn, int isMaster, int isFrmMaster)
 *
 * PreCondition:    None
 *
 * Input:           chn         - the channel to set
 *                  isMaster    - master/slave mode
 *                  isFrmMaster - frame master/slave mode
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function changes the SPI channel mode on the fly.
 *
 * Note:            - The function blocks until the current transfer, if any, is completed.
 *                    Due to a bug in the PIC32_3XX_4xx and PIC32_5XX_6xx_7xx SPI implementation, the BUSY/SRMT flag is set one spi_clk earlier.
 *                    What it means is that the data is not available in the SPIRxBUFF/SPIRxFIFO at the moment that BUSY is cleared.
 *                    The function will wait for the BUSY to be cleared.
 *                    For high SPIxBRG and PBDIV values note that the number of CPU clock cycles that have to be spent in this function could be significant.
 *                  - isFrmMaster is relevant only if the SPI channel is operating in frame mode
 *                  - The SCK is properly configured as an digital I/O pin
 *                  - The SS is configured as a digital pin only if in frame mode or if the SSEN configuration bit is set.
 *
 * Example:         SpiChnChgMode(SPI_CHANNEL2A, TRUE, TRUE);
 ********************************************************************/
#define	SpiChnChgMode(chn, isMaster, isFrmMaster)	SpiChnChangeMode(chn, isMaster, isFrmMaster, 1)


/******************************************************************************
 * Function:        int mSPIBRG(int pb_clk, int spi_clk)
 *
 * Description:		Calculates the BRG values needed for the SPI configuration
 *
 * PreCondition:    spi_clk <= pb_clk/2;
 *
 * Inputs:		pb_clk:		- the PB clock frequency, Hz
 * 			spi_clk:	- the desired SPI clock frequency, Hz
 *
 * Output:          The proper BRG value
 *
 * Example:	SpiChnSetBrg(SPI_CHANNEL1, mSPIBRG(72000000, 9000000));
 *
 *****************************************************************************/
#define		mSPIBRG		SpiBrgVal

/*********************************************************************
 * Function:        void mSpiChnSetBrg(int chn, UINT brg)
 *
 * PreCondition:    None
 *
 * Input:           chn	- the channel to set
 *                  brg - value for the brg register
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This macro directly updates the values for the SPI channel brg.
 *
 * Note:            The channel parameter is directly used as a string in the macro call,
 *                  so it has to be one of: 1, 2, 1A, 2A, 3A
 *
 * Example:         mSpiChnSetBrg(1, 0x0);
 *                  mSpiChnSetBrg(2, 0x0);
 *                  mSpiChnSetBrg(3A, 2)
 ********************************************************************/
#define		mSpiChnSetBrg(c, brg)		(SPI##c##BRG=(brg))



/*****************************************
 *       Legacy Interrupt functions
 *       The functions in the int.h should be used instead.
 ***********************************************************/

/*********************************************************************
 * Function:        int SpiChnGetRovIntFlag(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the channel to check
 *
 * Output:          TRUE		- if overflow flag
 * 					FALSE		- otherwise
 * Side Effects:    None
 * Overview:        This function reads the SPI channel overflow interrupt flag.
 *
 * Note:            None.
 *
 * Example:         int chn=SPI_CHANNEL1; int isOvflFlag=SpiChnGetRovIntFlag(chn);
 *                  int isOvflFlag=mSpiChnGetRovIntFlag(1);
 ********************************************************************/
#define		SpiChnGetRovIntFlag(chn)	INTGetFlag((INT_SPI1E-1)+(chn))
#define		mSpiChnGetRovIntFlag(c)		(mSPI##c##EGetIntFlag())		// macro version


/*********************************************************************
 * Function:        void SpiChnClrRovIntFlag(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the channel to check
 *
 * Output:          None
 *
 * Side Effects:    None
 * Overview:        This function clears the SPI channel overflow interrupt flag.
 *
 * Note:            None.
 *
 * Example:        int chn=2; SpiChnClrRovIntFlag(chn);
 *                 mSpiChnClrRovIntFlag(2);
 ********************************************************************/
#define		SpiChnClrRovIntFlag(chn)	INTClearFlag((INT_SPI1E-1)+(chn))
#define		mSpiChnClrRovIntFlag(c)		(mSPI##c##EClearIntFlag())		// macro version


/*********************************************************************
 * Function:        int SpiChnGetRxIntFlag(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the channel to check
 *
 * Output:          TRUE		- if SPI Rx flag
 * 					FALSE		- otherwise
 * Side Effects:    None
 * Overview:        This function reads the SPI channel receive interrupt flag.
 *
 * Note:            None.
 *
 * Example:         int chn=SPI_CHANNEL1; int isRxEvent=SpiChnGetRxIntFlag(chn);
 *                  isRxEvent=mSpiChnGetRxIntFlag(1);
 ********************************************************************/
#define		SpiChnGetRxIntFlag(chn)		INTGetFlag((INT_SPI1RX-1)+(chn))
#define		mSpiChnGetRxIntFlag(c)		(mSPI##c##RXGetIntFlag())		// macro version



/*********************************************************************
 * Function:        void SpiChnClrRxIntFlag(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the channel to check
 *
 * Output:          None
 *
 * Side Effects:    None
 * Overview:        This function clears the SPI channel receive interrupt flag.
 *
 * Note:            None.
 *
 * Example:         int chn=1; SpiChnClrRxIntFlag(chn);
 *                  mSpiChnClrRxIntFlag(1);
 ********************************************************************/
#define		SpiChnClrRxIntFlag(chn)		INTClearFlag((INT_SPI1RX-1)+(chn))
#define		mSpiChnClrRxIntFlag(c)		(mSPI##c##RXClearIntFlag())		// macro version


/*********************************************************************
 * Function:        int SpiChnGetTxIntFlag(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the channel to check
 *
 * Output:          TRUE		- if SPI Tx flag
 * 					FALSE		- otherwise
 * Side Effects:    None
 * Overview:        This function reads the SPI channel transmit interrupt flag.
 *
 * Note:            None.
 *
 * Example:         int chn=SPI_CHANNEL1; int isTxEvent=SpiChnGetTxIntFlag(chn);
 *                  isTxEvent=mSpiChnGetTxIntFlag(2);
 ********************************************************************/
#define		SpiChnGetTxIntFlag(chn)		INTGetFlag((INT_SPI1TX-1)+(chn))
#define		mSpiChnGetTxIntFlag(c)		(mSPI##c##TXGetIntFlag())		// macro version

/*********************************************************************
 * Function:        void SpiChnClrTxIntFlag(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the channel to check
 *
 * Output:          None
 *
 * Side Effects:    None
 * Overview:        This function clears the SPI channel transmit interrupt flag.
 *
 * Note:            None.
 *
 * Example:         SpiChnClrTxIntFlag(SPI_CHANNEL1);
 *                  mSpiChnClrTxIntFlag(1);
 ********************************************************************/
#define		SpiChnClrTxIntFlag(chn)		INTClearFlag((INT_SPI1TX-1)+(chn))
#define		mSpiChnClrTxIntFlag(c)		(mSPI##c##TXClearIntFlag())		// macro version


/*********************************************************************
 * Function:        int SpiChnGetIntFlags(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the channel to check
 *
 * Output:          TRUE		- if any SPI flag occurred (Rx, Tx, OVFL)
 * 					FALSE		- otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function reads the SPI channel interrupt flags.
 *
 * Note:            None.
 *
 * Example:         int chn=1; int isRxTxEvent=SpiChnGetIntFlags(chn);
 *                  isRxTxEvent=mSpiChnGetIntFlags(1);
 ********************************************************************/
#define		SpiChnGetIntFlags(chn)	INTGetFlag((INT_SPI1-1)+(chn))
#define		mSpiChnGetIntFlags(c)	(mSPI##c##TXGetIntFlag() || mSPI##c##TXGetIntFlag() ||mSPI##c##EGetIntFlag())		// macro version


/*********************************************************************
 * Function:        void SpiChnClrIntFlags(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the channel to check
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function clears the SPI channel interrupt flags.
 *
 * Note:            None.
 *
 * Example:         int chn=1; SpiChnClrIntFlags(chn);
 *                  mSpiChnClrIntFlags(1);
 ********************************************************************/
#define		SpiChnClrIntFlags(chn)		INTClearFlag((INT_SPI1-1)+(chn))
#define		mSpiChnClrIntFlags(c)		(mSPI##c##ClearAllIntFlags())		// macro version


/*********************************************************************
 * Function:        void SpiChnRxIntEnable(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the requested SPI channel
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function enables the SPI channel receive interrupts.
 *
 * Note:            Clears existing interrupt flags.
 *
 * Example:         SpiChnSetRxIntEnable(SPI_CHANNEL1);
 *                  mSpiChnRxIntEnable(1);
 ********************************************************************/
#define		SpiChnRxIntEnable(chn)		do{INTClearFlag((INT_SPI1-1)+(chn)); INTEnable((INT_SPI1RX-1)+(chn), 1);}while(0)
#define		mSpiChnRxIntEnable(c)		(mSPI##c##ClearAllIntFlags(), mSPI##c##RXIntEnable(1))		// macro version



/*********************************************************************
 * Function:        void SpiChnRxIntDisable(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the requested SPI channel
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function disables the SPI channel receive interrupts.
 *
 * Note:            Clears existing interrupt flags.
 *
 * Example:         int chn=1; SpiChnRxIntDisable(chn);
 *                  mSpiChnRxIntDisable(1);
 ********************************************************************/
#define		SpiChnRxIntDisable(chn)		do{INTClearFlag((INT_SPI1-1)+(chn)); INTEnable((INT_SPI1RX-1)+(chn), 0);}while(0)
#define		mSpiChnRxIntDisable(c)		(mSPI##c##ClearAllIntFlags(), mSPI##c##RXIntEnable(0))		// macro version



/*********************************************************************
 * Function:        void SpiChnTxIntEnable(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the requested SPI channel
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function enables the SPI channel transmit interrupts.
 *
 * Note:            Clears existing interrupt flags.
 *
 * Example:         SpiChnTxIntEnable(SPI_CHANNEL1);
 *                  mSpiChnTxIntEnable(1);
 ********************************************************************/
#define		SpiChnTxIntEnable(chn)	do{INTClearFlag((INT_SPI1-1)+(chn)); INTEnable((INT_SPI1TX-1)+(chn), 1);}while(0)
#define		mSpiChnTxIntEnable(c)	(mSPI##c##ClearAllIntFlags(), mSPI##c##TXIntEnable(1))		// macro version


/*********************************************************************
 * Function:        void SpiChnTxIntDisable(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the requested SPI channel
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function disables the SPI channel transmit interrupts.
 *
 * Note:            Clears existing interrupt flags.
 *
 * Example:         int chn=2; SpiChnTxIntDisable(chn);
 *                  mSpiChnTxIntDisable(2);
 ********************************************************************/
#define		SpiChnTxIntDisable(chn)	do{INTClearFlag((INT_SPI1-1)+(chn));INTEnable((INT_SPI1TX-1)+(chn), 0);}while(0)
#define		mSpiChnTxIntDisable(c)	(mSPI##c##ClearAllIntFlags(), mSPI##c##TXIntEnable(0))		// macro version



/*********************************************************************
 * Function:        void SpiChnRxTxIntEnable(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the requested SPI channel
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function enables the SPI channel transmit/receive interrupts.
 *
 * Note:            Clears existing interrupt flags.
 *
 * Example:         int chn=SPI_CHANNEL1; SpiChnRxTxIntEnable(chn);
 *                  mSpiChnRxTxIntEnable(1);
 ********************************************************************/
#define		SpiChnRxTxIntEnable(chn)	do{INTClearFlag((INT_SPI1-1)+(chn));INTEnable((INT_SPI1TX-1)+(chn), 1); \
										INTEnable((INT_SPI1RX-1)+(chn), 1);}while(0)
#define		mSpiChnRxTxIntEnable(c)		(mSPI##c##ClearAllIntFlags(), mSPI##c##TXIntEnable(1), mSPI##c##RXIntEnable(1))	// macro version



/*********************************************************************
 * Function:        void SpiChnRxTxIntDisable(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the requested SPI channel
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function disables the SPI channel transmit/receive interrupts.
 *
 * Note:            Clears existing interrupt flags.
 *
 * Example:         int chn=2; SpiChnRxTxIntDisable(chn);
 *                  mSpiChnRxTxIntDisable(2);
 ********************************************************************/
#define		SpiChnRxTxIntDisable(chn)	do{INTClearFlag((INT_SPI1-1)+(chn));INTEnable((INT_SPI1TX-1)+(chn), 0); \
											INTEnable((INT_SPI1RX-1)+(chn), 0);}while(0)
#define		mSpiChnRxTxIntDisable(c)		(mSPI##c##ClearAllIntFlags(), mSPI##c##TXIntEnable(0), mSPI##c##RXIntEnable(0))	// macro version



/*********************************************************************
 * Function:        void SpiChnFaultIntEnable(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the requested SPI channel
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function enables the SPI channel fault interrupts.
 *
 * Note:            Clears an existing fault interrupt flag.
 *
 * Example:         int chn=SPI_CHANNEL2; SpiChnFaultIntEnable(chn);
 *                  mSpiChnFaultIntEnable(2);
 ********************************************************************/
#define		SpiChnFaultIntEnable(chn)	do{INTClearFlag((INT_SPI1-1)+(chn));INTEnable((INT_SPI1E-1)+(chn), 1);}while(0)
#define		mSpiChnFaultIntEnable(c)	(mSPI##c##ClearAllIntFlags(), mSPI##c##EIntEnable(1))		// macro version



/*********************************************************************
 * Function:        void SpiChnFaultIntDisable(int chn)
 *
 * PreCondition:    None
 * Input:			chn			- the requested SPI channel
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function disables the SPI channel fault interrupts.
 *
 * Note:            Clears an existing fault interrupt flag.
 *
 * Example:         int chn=2; SpiChnFaultIntDisable(chn);
 *                  mSpiChnFaultIntDisable(2);
 ********************************************************************/
#define		SpiChnFaultIntDisable(chn)		do{INTClearFlag((INT_SPI1-1)+(chn));INTEnable((INT_SPI1E-1)+(chn), 0);}while(0)
#define		mSpiChnFaultIntDisable(c)		(mSPI##c##ClearAllIntFlags(), mSPI##c##EIntEnable(0))		// macro version


/*********************************************************************
 * Function:        void SpiChnSetIntPriority(int chn, int pri, int subPri)
 *
 * PreCondition:    pri 	- valid priority 0-7
 * 					subPri	- valid subpriority 0-3
 *
 * Input:			chn			- the requested SPI channel
 *					pri			- the interrupt priority
 *					subPri		- the interrupt sub-priority
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function sets the SPI channel interrupt priority.
 *
 * Note:            None.
 *
 * Example:         int chn, pri, subPri; chn=SPI_CHANNEL1, pri=2, subPri=3; SpiChnSetIntPriority(chn, pri, subPri);
 *                  mSpiChnSetIntPriority(1, 2, 3);
 ********************************************************************/
#define		SpiChnSetIntPriority(chn, pri, subPri) do{INTSetPriority((INT_SPI1-1)+(chn), (pri)); \
							INTSetSubPriority((INT_SPI1-1)+(chn), (subPri));}while(0)
#define		mSpiChnSetIntPriority(c, pri, sPri)	(mSPI##c##SetIntPriority(pri), mSPI##c##SetIntSubPriority(sPri))	// macro version

/*********************************************************************
 * Function:        int SpiChnGetIntPriority(int chn)
 *
 * PreCondition:    chn 	- valid SPI channel
 *
 * Input:			chn			- the requested SPI channel
 *
 * Output:          The current interrupt priority for the selected channel
 *
 * Side Effects:    None
 *
 * Overview:        This function reads the SPI channel interrupt priority in the INT controller.
 *
 * Note:            None.
 *
 * Example:         int chn=2; int currPri=SpiChnGetIntPriority(chn);
 *                  currPri=mSpiChnGetIntPriority(2);
 ********************************************************************/
#define		SpiChnGetIntPriority(chn)		INTGetPriority((INT_SPI1-1)+(chn))
#define		mSpiChnGetIntPriority(c)		(mSPI##c##GetIntPriority())		// macro version

/*********************************************************************
 * Function:        int SpiChnGetIntSubPriority(int chn)
 *
 * PreCondition:    chn 	- valid SPI channel
 *
 * Input:			chn			- the requested SPI channel
 *
 * Output:          The current interrupt subpriority for the selected channel
 *
 * Side Effects:    None
 *
 * Overview:        This function reads the SPI channel interrupt subpriority in the INT controller.
 *
 * Note:            None.
 *
 * Example:         int chn=2; int currSubPri=SpiChnGetIntSubPriority(chn);
 *                  currSubPri=mSpiChnGetIntSubPriority(2);
 ********************************************************************/
#define		SpiChnGetIntSubPriority(chn)	INTGetSubPriority((INT_SPI1-1)+(chn))
#define		mSpiChnGetIntSubPriority(c)		(mSPI##c##GetIntSubPriority())		// macro version







/*****************************************
 *       Legacy channel oriented functions
 *       The new functions taking the channel number parameter from spi.h should be used instead.
 ***********************************************************/


/* List of SFRs for SPI */
/* This list contains the SFRs with default (POR) values to be used for configuring SPI */
/* The user can modify this based on the requirement */
#define SPI1STAT_VALUE         0x00000000
#define SPI2STAT_VALUE         0x00000000
#define SPI1CON_VALUE          0x00000000
#define SPI2CON_VALUE          0x00000000
#define SPI1BUF_VALUE          0x00000000
#define SPI2BUF_VALUE          0x00000000



// OpenSPI config1 word structure
typedef union
{
	struct
	{
	    unsigned PPRE:		2;		// primary prescaler
	    unsigned SPRE:		3;		// secondary prescaler
	    unsigned MSTEN:		1;		// master mode enable
	    unsigned CKP:		1;		// clock polarity
	    unsigned SSEN:		1;		// slave select
	    unsigned CKE:		1;		// clock edge
	    unsigned SMP:		1;		// sample phase
	    unsigned MODE16:	1;		// word/hword/byte communication select
	    unsigned MODE32:	1;		// word/hword/byte communication select
	    unsigned DISSDO:	1;		// disable SDO pin
	    unsigned:			17;		// reserved
	    unsigned FRMSYNC:	1;		// frame sync direction
		unsigned FRMEN:		1;		// framed SPI
	};								// field access
	unsigned int			w;		// word access
}SpiOpenConfig1;


#define  FRAME_ENABLE_ON        (0x80000000)  		/* Frame SPI support enable */
#define  FRAME_ENABLE_OFF       (0x00000000)  /* Frame SPI support Disable */

#define  FRAME_SYNC_INPUT       (0x40000000)  		/* Frame sync pulse Input (slave) */
#define  FRAME_SYNC_OUTPUT      (0x00000000) /* Frame sync pulse Output (master) */

#define  ENABLE_SCK_PIN         (0x00000000)			/* SCK pin is not handled here */
#define  DISABLE_SCK_PIN        (0x00000000)	/* SCK pin is not handled here */

#define  DISABLE_SDO_PIN        (0x00001000)  		/* SDO pin is not used by module */
#define  ENABLE_SDO_PIN         (0x00000000)	/* SDO pin is  used by module */

#define  SPI_MODE32_ON          (0x00000800)			/* Communication is 32 bits wide */
#define  SPI_MODE32_OFF         (0x00000000)  		/* Communication is selected by SPI_MODE16_ON/OFF */

#define  SPI_MODE16_ON          (0x00000400)			/* If SPI_MODE32_OFF, Communication is 16 bits wide */
#define  SPI_MODE16_OFF         (0x00000000)			/* If SPI_MODE32_OFF, Communication is 8 bits wide */

#define  SPI_MODE8_ON           (0x00000000)			/* If SPI_MODE32_OFF and SPI_MODE16_OFF, Communication is 8 bits wide */

#define  SPI_SMP_ON             (0x00000200)		/* Input data sampled at end of data output time */
#define  SPI_SMP_OFF            (0x00000000)	/* Input data sampled at middle of data output time */

#define  SPI_CKE_ON             (0x00000100)		/* Transmit happens from active clock state to idle clock state*/
#define  SPI_CKE_OFF            (0x00000000)	/* Transmit happens on transition from idle clock state to active clock state */

#define  SLAVE_ENABLE_ON        (0x00000080)			/* Slave Select enbale */
#define  SLAVE_ENABLE_OFF       (0x00000000)	/* Slave Select not used by module */

#define  CLK_POL_ACTIVE_LOW     (0x00000040)				/* Idle state for clock is high, active is low */
#define  CLK_POL_ACTIVE_HIGH    (0x00000000)	/* Idle state for clock is low, active is high */

#define  MASTER_ENABLE_ON       (0x00000020)			/* Master Mode */
#define  MASTER_ENABLE_OFF     	(0x00000000)	/* Slave Mode */

#define  SEC_PRESCAL_1_1        (0x0000001c)  		/* Secondary Prescale 1:1   */
#define  SEC_PRESCAL_2_1        (0x00000018)  		/* Secondary Prescale 2:1   */
#define  SEC_PRESCAL_3_1        (0x00000014)  		/* Secondary Prescale 3:1   */
#define  SEC_PRESCAL_4_1        (0x00000010)  		/* Secondary Prescale 4:1   */
#define  SEC_PRESCAL_5_1        (0x0000000c)  		/* Secondary Prescale 5:1   */
#define  SEC_PRESCAL_6_1        (0x00000008)  		/* Secondary Prescale 6:1   */
#define  SEC_PRESCAL_7_1        (0x00000004)  		/* Secondary Prescale 7:1   */
#define  SEC_PRESCAL_8_1        (0x00000000)  		/* Secondary Prescale 8:1   */

#define  PRI_PRESCAL_1_1        (0x00000003)  		/* Primary Prescale 1:1     */
#define  PRI_PRESCAL_4_1        (0x00000002)  		/* Primary Prescale 4:1     */
#define  PRI_PRESCAL_16_1       (0x00000001)  		/* Primary Prescale 16:1    */
#define  PRI_PRESCAL_64_1       (0x00000000)  		/* Primary Prescale 64:1    */



// OpenSPI config2 word structure
typedef union
{
	struct
	{
		unsigned:			6;		// reserved
		unsigned SPIROV:	1;		// receiver overflow
		unsigned:			6;		// reserved
		unsigned SIDL:		1;		// stop in idle
		unsigned FRZ:		1;		// freeze
		unsigned ON:		1;		// enable peripheral
		unsigned:			1;		// reserved
		unsigned SPIFE:		1;		// frame edge select
		unsigned:			11;		//
	    unsigned FRMPOL:	1;		// frame sync polarity
	};								// field access
	unsigned int			w;		// word access
}SpiOpenConfig2;


#define  SPI_ENABLE             (0x00008000)			/* Enable module */
#define  SPI_DISABLE            (0x00000000)		/* Disable module */

#define	SPI_FRZ_BREAK			(0x00004000)			/* Break device operation in debug mode */
#define	SPI_FRZ_CONTINUE		(0x00000000)	/* Continue device operation in debug mode */

#define  SPI_IDLE_STOP          (0x00002000)  		/* Discontinue module operation in idle mode */
#define  SPI_IDLE_CON           (0x00000000)		/* Continue module operation in idle mode */

#define  SPI_RX_OVFLOW			(0x00000040)			/* receive overflow bit */
#define  SPI_RX_OVFLOW_CLR		(0x00000000)	/* Clear receive overflow bit */

#define  FRAME_POL_ACTIVE_HIGH	(0x20000000)					/* Frame pulse active high */
#define  FRAME_POL_ACTIVE_LOW	(0x00000000)	/* Frame pulse active low */

#define	FRAME_SYNC_EDGE_COINCIDE (0x00020000)					/* frame pulse coincides with the first bit clock */
#define	FRAME_SYNC_EDGE_PRECEDE	(0x00000000)	/* frame pulse precedes the first bit clock */

#define	FIFO_BUFFER_ENABLE		(0x00000000)					/* no enhanced buffer functionality */
#define	FIFO_BUFFER_DISABLE	(0x00000000)		/* ineffective */




	/* SPI Interrupt defines */

// ConfigIntSPI word structure
typedef union
{
	struct
	{
		unsigned ipl:		3;		// interrupt priority level
		unsigned ispl:		2;		// interrupt sub-priority level
		unsigned fie:		1;		// fault interrupt enable/disable
		unsigned txie:		1;		// tx interrupt enable/disable
		unsigned rxie:		1;		// rx interrupt enable/disable
	};								// field access
	unsigned int			w;		// word access
}SpiConfigInt;


#define  SPI_FAULT_INT_EN		(0x00000020)  /* SPI Fault Interrupt Enable     */
#define  SPI_FAULT_INT_DIS		(0x00000000)  /* SPI Fault Interrupt Disable    */

#define  SPI_TX_INT_EN			(0x00000040)  /* SPI Tx Interrupt Enable */
#define  SPI_TX_INT_DIS			(0x00000000)  /* SPI Tx Interrupt Disable    */

#define  SPI_RX_INT_EN			(0x00000080)  /* SPI Rx Interrupt Enable */
#define  SPI_RX_INT_DIS			(0x00000000)  /* SPI Rx Interrupt Disable    */

#define  SPI_INT_EN             (SPI_TX_INT_EN | SPI_RX_INT_EN)  /* SPI Interrupt Enable: tx+rx */
#define  SPI_INT_DIS            (0x00000000)  /* SPI Interrupt Disable    */


#define  SPI_INT_SUB_PRI_0     (0x00000000)  /* SPI Interrupt Sub-Prior Level_0 */
#define  SPI_INT_SUB_PRI_1     (0x00000008)  /* SPI Interrupt Sub-Prior Level_1 */
#define  SPI_INT_SUB_PRI_2     (0x00000010)  /* SPI Interrupt Sub-Prior Level_2 */
#define  SPI_INT_SUB_PRI_3     (0x00000018)  /* SPI Interrupt Sub-Prior Level_3 */


#define  SPI_INT_PRI_0          (0x00000000)  /* SPI Interrupt Prior Level_0 */
#define  SPI_INT_PRI_1          (0x00000001)  /* SPI Interrupt Prior Level_1 */
#define  SPI_INT_PRI_2          (0x00000002)  /* SPI Interrupt Prior Level_2 */
#define  SPI_INT_PRI_3          (0x00000003)  /* SPI Interrupt Prior Level_3 */
#define  SPI_INT_PRI_4          (0x00000004)  /* SPI Interrupt Prior Level_4 */
#define  SPI_INT_PRI_5          (0x00000005)  /* SPI Interrupt Prior Level_5 */
#define  SPI_INT_PRI_6          (0x00000006)  /* SPI Interrupt Prior Level_6 */
#define  SPI_INT_PRI_7          (0x00000007)  /* SPI Interrupt Prior Level_7 */





/* FUNCTION PROTOTYPES */

#ifdef _SPI1

	/* OpenSPI */
	/*********************************************************************
	 * Function:        void OpenSPI1(unsigned int config1,unsigned int config2)
	 *
	 * Condition:    	None
	 *
	 * Input:           config1	- sets the module behavior using the SpiOpenConfig1 bits:
	 *					  	typedef union
	 *						{
	 *							struct
	 *							{
	 *							    unsigned PPRE:		2;		// primary prescaler
	 *							    unsigned SPRE:		3;		// secondary prescaler
	 *							    unsigned MSTEN:		1;		// master mode enable
	 *							    unsigned CKP:		1;		// clock polarity
	 *							    unsigned SSEN:		1;		// slave select
	 *							    unsigned CKE:		1;		// clock edge
	 *							    unsigned SMP:		1;		// sample phase
	 *							    unsigned MODE16:	1;		// word/hword/byte communication select
	 *							    unsigned MODE32:	1;		// word/hword/byte communication select
	 *							    unsigned DISSDO:	1;		// disable SDO pin
	 *							    unsigned:			17;		// reserved
	 *							    unsigned FRMSYNC:	1;		// frame sync direction
	 *								unsigned FRMEN:		1;		// framed SPI
	 *							};								// field access
	 *							unsigned int			w;		// word access
	 *						}SpiOpenConfig1;
	 *
	 * 					config2	- sets the module behavior using the SpiOpenConfig2 bits:
	 *						typedef union
	 *						{
	 *							struct
	 *							{
	 *								unsigned:			6;		// reserved
	 *								unsigned SPIROV:	1;		// receiver overflow
	 *								unsigned:			6;		// reserved
	 *								unsigned SIDL:		1;		// stop in idle
	 *								unsigned FRZ:		1;		// freeze
	 *								unsigned ON:		1;		// enable peripheral
	 *								unsigned:			1;		// reserved
	 *								unsigned SPIFE:		1;		// frame edge select
	 *								unsigned:			11;		//
	 *							    unsigned FRMPOL:	1;		// frame sync polarity
	 *							};								// field access
	 *							unsigned int			w;		// word access
	 *						}SpiOpenConfig2;
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function initializes and enables the SPI module.
	 *
	 * Note:            The format of configuration words is chosen for backward compatibility reasons.
	 * 					The config words don't reflect the actual register bits.
	 *
	 * Example:			OpenSPI1(SPI_MODE32_ON|SPI_SMP_ON|MASTER_ENABLE_ON|SEC_PRESCAL_1_1|PRI_PRESCAL_1_1, SPI_ENABLE);
	 ********************************************************************/
	void	OpenSPI1(unsigned int config1, unsigned int config2);


	/* CloseSPI. Disables SPI module */
	/*********************************************************************
	 * Function:        void CloseSPI1(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This routine disables the SPI module and clears its interrupt bits.
	 *
	 * Note:            None
	 *
	 * Example:			CloseSPI1();
	 ********************************************************************/
	#define CloseSPI1()	(SPI1CONCLR=_SPI2CON_ON_MASK, mSPI1IntDisable(), mSPI1ClearAllIntFlags())
						// disable the module; disable all ints; clear any existing event

	/* ConfigIntSPI. Configure Interrupt enable and priorities */
	/*********************************************************************
	 * Function:        void ConfigIntSPI1( unsigned int config)
	 *
	 * PreCondition:    None
	 *
	 * Input :			config	- SpiConfigInt value having the following fields:
	 * 								- ipl:	3		the interrupt priority level
	 * 								- ispl: 2		the interrupt sub-priority level
	 * 								- fie:	1		fault interrupt enable/disable
	 * 								- txie:	1		tx interrupt enable/disable
	 * 								- rxie:	1		rx interrupt enable/disable
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function Configures Interrupt and sets the Interrupt Priority
	 *
	 * Note:            None
	 *
	 * Example:			ConfigIntSPI1(SPI_FAULT_INT_EN|SPI_INT_EN|SPI_INT_PRI_0|SPI_INT_SUB_PRI_2);
	 ********************************************************************/
	#define	ConfigIntSPI1(config) (mSPI1IntDisable(), mSPI1ClearAllIntFlags(), mSPI1SetIntPriority((config)&0x7), \
				mSPI1SetIntSubPriority(((config)&0x18)>>3), mSPI1SetIntEnable(((config)&0xe0)>>5))
							// disable all ints, clear any existing event, set new priority, sub-priority, set (rxie, txie, fie)



	/* Enable/Disable interrupts and set Interrupt priority of SPI */

	/*********************************************************************
	 * Macro:        EnableIntSPI1
	 *
	 * PreCondition:    None
	 *
	 * Input :			None
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function enables the receive and transmit interrupts for SPI 1
	 *
	 * Note:            None
	 *
	 * Example:			EnableIntSPI1;
	 ********************************************************************/
	#define EnableIntSPI1	(mSPI1ClearAllIntFlags(), mSPI1RXIntEnable(1), mSPI1TXIntEnable(1) )
							// clear int flags, enable rx and tx interrupts


	/*********************************************************************
	 * Macro:        DisableIntSPI1
	 *
	 * PreCondition:    None
	 *
	 * Input :			None
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function disables the receive and transmit interrupts for SPI 1
	 *
	 * Note:            None
	 *
	 * Example:			DisableIntSPI1;
	 ********************************************************************/
	#define DisableIntSPI1	(mSPI1ClearAllIntFlags(), mSPI1RXIntEnable(0), mSPI1TXIntEnable(0) )
							// clear int flags, disable rx and tx interrupts



	/*********************************************************************
	 * Function:        void SetPriorityIntSPI1(int priority)
	 *
	 * PreCondition:    None
	 *
	 * Input :			priority	- new priority for the SPI channel:
	 * 							0ne of the values SPI_INT_PRI_0 to SPI_INT_PRI_7
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function sets the priority interrupt for SPI channel 1
	 *
	 * Note:            None
	 *
	 * Example:			SetPriorityIntSPI1(SPI_INT_PRI_0);
	 ********************************************************************/
	#define SetPriorityIntSPI1(priority)	(mSPI1SetIntPriority(priority))

	/*********************************************************************
	 * Function:        void SetSubPriorityIntSPI1(int subPriority)
	 *
	 * PreCondition:    None
	 *
	 * Input :			subPriority	- new sub-priority for the SPI channel:
	 * 							0ne of the values SPI_INT_SUB_PRI_0 to SPI_INT_SUB_PRI_3
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function sets the sub-priority interrupt for SPI channel 1
	 *
	 * Note:            None
	 *
	 * Example:			SetSubPriorityIntSPI1(SPI_INT_SUB_PRI_3);
	 ********************************************************************/
	#define SetSubPriorityIntSPI1(subPriority)	(mSPI1SetIntSubPriority(((subPriority)&0x18)>>3))


	/* DataRdySPI. Test if receive data available */
	/*********************************************************************
	 * Function:        int DataRdySPI1(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          TRUE if data is available (Receiver Buffer Full), FALSE otherwise
	 *
	 * Side Effects:    None
	 *
	 * Overview:        Determine if there is a data to be read from the SPIBUF register.
	 *
	 * Note:            None
	 *
	 * Example:			if(DataRdySPI1()){...}
	 ********************************************************************/
	#define DataRdySPI1() (SPI1STATbits.SPIRBF)



	/* TxBufFullSPI. Test if transmit buffer is full */
	/*********************************************************************
	 * Function:        int TxBufFullSPI1(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          TRUE if SPI buffer is full and data cannot be written to device, in order to be serialized, FALSE otherwise
	 *
	 * Side Effects:    None
	 *
	 * Overview:        Determine if the data can be written to the SPIBUF register without overwriting
	 * 					the previous, unsent data.
	 *
	 * Note:            None
	 *
	 * Example:			if(!TxBufFullSPI1()){WriteSPI1('a');}
	 ********************************************************************/
	#define	TxBufFullSPI1()	(!SPI1STATbits.SPITBE)



	/* ReadSPI.Read byte/word from SPIBUF register */
	/*********************************************************************
	 * Function:         unsigned int ReadSPI1(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          Returns the contents of SPIBUF register in byte/hword/word format
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function will read single byte/half word/word from SPI receive register.
	 *
	 * Note:            User interface is always 32 bits.
	 *
	 * Example:			int data=ReadSPI1();
	 ********************************************************************/
	#define	ReadSPI1()	(SPI1BUF)

	/* WriteSPI. Write byte/word directly to SPIBUF register */
	/*********************************************************************
	 * Function:         void WriteSPI1(unsigned int data_out)
	 *
	 * PreCondition:    None
	 *
	 * Input:           data_out	- Single data byte/half word/word for SPI bus
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This routine writes a single byte/half word/word to the SPI bus.
	 *
	 * Note:            None.
	 *
	 * Example:			WriteSPI1(0x4433);
	 ********************************************************************/
	#define	WriteSPI1(data_out)	(SPI1BUF=(data_out))


	/* getcSPI. Wait character available and read from SPIBUF register */
	/*********************************************************************
	 * Function:         unsigned int getcSPI1(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          the contents of SPIBUF register in byte/hword/word format
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function waits for receive data to be available.
	 * 					It will then read single byte/half word/word from SPI bus.
	 *
	 * Note:            byte/hword/word accesses will perform correctly.
     *
     *                  When a new data word has been shifted into shift register SPIxSR and 
     *                  the previous contents of receive register SPIxRXB have not been read
     *                  by the user software, then SPIROV bit (SPIxSTAT<6>) will be set.The 
     *                  module will not transfer the received data from SPIxSR to the SPIxRXB. 
     *                  Further data reception is disabled until the SPIROV bit is cleared. 
     *                  The SPIROV bit is not cleared automatically by the module and must be 
     *                  cleared by the user software.
	 *
	 * Example:			int data=getcSPI1();
	 ********************************************************************/
	unsigned int getcSPI1(void);


	/* putcSPI. Wait for buffer empty and write byte/word to SPIBUF register */
	/*********************************************************************
	 * Function:         void putcSPI1(unsigned int data_out)
	 *
	 * PreCondition:    None
	 *
	 * Input:           data_out	- Single data byte/half word/word for SPI bus
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This routine writes a single byte/half word/word to the SPI bus.
	 * 					It waits so that it doesn't overwrite the previous untransmitted data.
	 *
	 * Note:            byte/hword/word accesses will perform correctly.
	 *
	 * Example:			putcSPI1(0xaa);
	 ********************************************************************/
	#define	putcSPI1(data_out)	do{while(!SPI1STATbits.SPITBE); SPI1BUF=(data_out); }while(0)


	/* getsSPI.Read string from SPIBUF */
	/*********************************************************************
	 * Function:        unsigned int getsSPI1(unsigned int length, unsigned int *rdptr,
	 * 											unsigned int spi_data_wait)
	 *
	 * PreCondition:    rdptr	- valid pointer
	 *
	 * Input:           length			- The length of data expected
	 * 					rdptr			- the received data to be recorded to this array
	 * 					spi_data_wait	- timeout value
	 *
	 * Output:          number of data bytes yet to be received
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This routine reads a string from the SPI receive buffer.
	 * 					The number of byte/word to be read is determined by parameter 'length'.
	 *
	 * Note:            rdptr is considered to be 8/16/32 bits data pointer, according to the
	 * 					current SPI mode!
     *                  When a new data word has been shifted into shift register SPIxSR and 
     *                  the previous contents of receive register SPIxRXB have not been read
     *                  by the user software, then SPIROV bit (SPIxSTAT<6>) will be set.The 
     *                  module will not transfer the received data from SPIxSR to the SPIxRXB. 
     *                  Further data reception is disabled until the SPIROV bit is cleared. 
     *                  The SPIROV bit is not cleared automatically by the module and must be 
     *                  cleared by the user software.
	 *
	 * Example:			getsSPI1(sizeof(buff), buff, 1000);
	 ********************************************************************/
	unsigned int	getsSPI1(unsigned int length, unsigned int *rdptr, unsigned int spi_data_wait);


	/* putsSPI Write string to SPIBUF */
	/*********************************************************************
	 * Function:        void putsSPI1(unsigned int length, unsigned int *wrptr)
	 *
	 * PreCondition:    wrptr	- valid pointer
	 *
	 * Input:           length	- length of bytes/words to be written
	 * 					wrptr	- address of buffer storing the data to be transmitted.
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function writes the specified length of data words/bytes
	 * 					from the specified buffer.
	 *
	 * Note:            wrptr is considered to be 8/16/32 bits data pointer, according to the
	 * 					current SPI mode!
	 *
	 * Example:			putsSPI1(sizeof(buf), buf);
	 ********************************************************************/
	void	putsSPI1(unsigned int length, unsigned int *wrptr);

#endif	// _SPI1

#ifdef _SPI2
	/* OpenSPI */
	/*********************************************************************
	 * Function:        void OpenSPI2(unsigned int config1,unsigned int config2)
	 *
	 * Condition:    	None
	 *
	 * Input:           config1	- sets the module behavior using the SpiOpenConfig1 bits:
	 *					  	typedef union
	 *						{
	 *							struct
	 *							{
	 *							    unsigned PPRE:		2;		// primary prescaler
	 *							    unsigned SPRE:		3;		// secondary prescaler
	 *							    unsigned MSTEN:		1;		// master mode enable
	 *							    unsigned CKP:		1;		// clock polarity
	 *							    unsigned SSEN:		1;		// slave select
	 *							    unsigned CKE:		1;		// clock edge
	 *							    unsigned SMP:		1;		// sample phase
	 *							    unsigned MODE16:	1;		// word/hword/byte communication select
	 *							    unsigned MODE32:	1;		// word/hword/byte communication select
	 *							    unsigned DISSDO:	1;		// disable SDO pin
	 *							    unsigned:			17;		// reserved
	 *							    unsigned FRMSYNC:	1;		// frame sync direction
	 *								unsigned FRMEN:		1;		// framed SPI
	 *							};								// field access
	 *							unsigned int			w;		// word access
	 *						}SpiOpenConfig1;
	 *
	 * 					config2	- sets the module behavior using the SpiOpenConfig2 bits:
	 *						typedef union
	 *						{
	 *							struct
	 *							{
	 *								unsigned:			6;		// reserved
	 *								unsigned SPIROV:	1;		// receiver overflow
	 *								unsigned:			6;		// reserved
	 *								unsigned SIDL:		1;		// stop in idle
	 *								unsigned FRZ:		1;		// freeze
	 *								unsigned ON:		1;		// enable peripheral
	 *								unsigned:			1;		// reserved
	 *								unsigned SPIFE:		1;		// frame edge select
	 *								unsigned:			11;		//
	 *							    unsigned FRMPOL:	1;		// frame sync polarity
	 *							};								// field access
	 *							unsigned int			w;		// word access
	 *						}SpiOpenConfig2;
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function initializes and enables the SPI module.
	 *
	 * Note:            The format of configuration words is chosen for backward compatibility reasons.
	 * 					The config words don't reflect the actual register bits.
	 *
	 * Example:			OpenSPI2(SPI_MODE32_ON|SPI_SMP_ON|MASTER_ENABLE_ON|SEC_PRESCAL_1_1|PRI_PRESCAL_1_1, SPI_ENABLE);
	 ********************************************************************/
	void	OpenSPI2(unsigned int config1, unsigned int config2 );


	/* CloseSPI. Disables SPI module */
	/*********************************************************************
	 * Function:        void CloseSPI2(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This routine disables the SPI module and its interrupt bits.
	 *
	 * Note:            None
	 *
	 * Example:			CloseSPI2();
	 ********************************************************************/
	#define CloseSPI2()	(SPI2CONCLR=_SPI2CON_ON_MASK, mSPI2IntDisable(), mSPI2ClearAllIntFlags())
						 // disable the module; disable all ints; clear any existing event



	/* ConfigIntSPI. Configure Interrupt enable and priorities */
	/*********************************************************************
	 * Function:        void ConfigIntSPI2( unsigned int config)
	 *
	 * PreCondition:    None
	 *
	 * Input :			config	- SpiConfigInt value having the following fields:
	 * 								- ipl:	3		the interrupt priority level
	 * 								- ispl: 2		the interrupt sub-priority level
	 * 								- fie:	1		fault interrupt enable/disable
	 * 								- txie:	1		tx interrupt enable/disable
	 * 								- rxie:	1		rx interrupt enable/disable
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function Configures Interrupt and sets the Interrupt Priority
	 *
	 * Note:            None
	 *
	 * Example:			ConfigIntSPI2(SPI_FAULT_INT_EN|SPI_INT_EN|SPI_INT_PRI_0|SPI_INT_SUB_PRI_3);
	 ********************************************************************/
	#define	ConfigIntSPI2(config) (mSPI2IntDisable(), mSPI2ClearAllIntFlags(), mSPI2SetIntPriority((config)&0x7), \
					mSPI2SetIntSubPriority(((config)&0x18)>>3), mSPI2SetIntEnable(((config)&0xe0)>>5) )
							// disable all ints, clear any existing event, set new priority, sub-priority, set (rxie, txie, fie)

	/* Enable/Disable interrupts and set Interrupt priority of SPI */
	/*********************************************************************
	 * Macro:        EnableIntSPI2
	 *
	 * PreCondition:    None
	 *
	 * Input :			None
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function enables the receive and transmit interrupts for SPI 2
	 *
	 * Note:            None
	 *
	 * Example:			EnableIntSPI2;
	 ********************************************************************/
	#define EnableIntSPI2	(mSPI2ClearAllIntFlags(), mSPI2RXIntEnable(1), mSPI2TXIntEnable(1) )
							// clear int flags, enable rx and tx interrupts

	/*********************************************************************
	 * Macro:        DisableIntSPI2
	 *
	 * PreCondition:    None
	 *
	 * Input :			None
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function disables the receive and transmit interrupts for SPI 2
	 *
	 * Note:            None
	 *
	 * Example:			DisableIntSPI2;
	 ********************************************************************/
	#define DisableIntSPI2	(mSPI2ClearAllIntFlags(), mSPI2RXIntEnable(0), mSPI2TXIntEnable(0) )
							// clear int flags, disable rx and tx interrupts

	/*********************************************************************
	 * Function:        void SetPriorityIntSPI2(int priority)
	 *
	 * PreCondition:    None
	 *
	 * Input :			priority	- new priority for the SPI channel:
	 * 							0ne of the values SPI_INT_PRI_0 to SPI_INT_PRI_7
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function sets the priority interrupt for SPI channel 2
	 *
	 * Note:            None
	 *
	 * Example:			SetPriorityIntSPI2(SPI_INT_PRI_0);
	 ********************************************************************/
	#define SetPriorityIntSPI2(priority)	(mSPI2SetIntPriority(priority))


	/*********************************************************************
	 * Function:        void SetSubPriorityIntSPI2(int subPriority)
	 *
	 * PreCondition:    None
	 *
	 * Input :			subPriority	- new sub-priority for the SPI channel:
	 * 							0ne of the values SPI_INT_SUB_PRI_0 to SPI_INT_SUB_PRI_3
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function sets the sub-priority interrupt for SPI channel 2
	 *
	 * Note:            None
	 *
	 * Example:			SetSubPriorityIntSPI2(SPI_INT_SUB_PRI_3);
	 ********************************************************************/
	#define SetSubPriorityIntSPI2(subPriority)	(mSPI2SetIntSubPriority(((subPriority)&0x18)>>3))


	/* DataRdySPI. Test if receive data available */
	/*********************************************************************
	 * Function:        int DataRdySPI2(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          TRUE if data is available (Receiver Buffer Full), FALSE otherwise
	 *
	 * Side Effects:    None
	 *
	 * Overview:        Determine if there is a data to be read from the SPIBUF register.
	 *
	 * Note:            None
	 *
	 * Example:			if(DataRdySPI2()){...}
	 ********************************************************************/
	#define DataRdySPI2() (SPI2STATbits.SPIRBF)

	/* TxBufFullSPI. Test if transmit buffer is full */
	/*********************************************************************
	 * Function:        int TxBufFullSPI2(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          TRUE if SPI buffer is full and data cannot be written to device, in order to be serialized, FALSE otherwise
	 *
	 * Side Effects:    None
	 *
	 * Overview:        Determine if the data can be written to the SPIBUF register without overwriting
	 * 					the previous, unsent data.
	 *
	 * Note:            None
	 *
	 * Example:			if(!TxBufFullSPI2()){WriteSPI2('a');}
	 ********************************************************************/
	#define	TxBufFullSPI2()	(!SPI2STATbits.SPITBE)


	/* ReadSPI.Read byte/word from SPIBUF register */
	/*********************************************************************
	 * Function:         unsigned int ReadSPI2(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          Returns the contents of SPIBUF register in byte/hword/word format
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function will read single byte/half word/word from SPI receive register.
	 *
	 * Note:            User interface is always 32 bits.
	 *
	 * Example:			int data=ReadSPI2();
	 ********************************************************************/
	#define	ReadSPI2()	(SPI2BUF)

	/* WriteSPI. Write byte/word directly to SPIBUF register */
	/*********************************************************************
	 * Function:         void WriteSPI2(unsigned int data_out)
	 *
	 * PreCondition:    None
	 *
	 * Input:           data_out	- Single data byte/half word/word for SPI bus
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This routine writes a single byte/half word/word to the SPI bus.
	 *
	 * Note:            None.
	 *
	 * Example:			WriteSPI2(0x4433);
	 ********************************************************************/
	#define	WriteSPI2(data_out)	(SPI2BUF=(data_out))

	/* getcSPI. Wait character available and read from SPIBUF register */
	/*********************************************************************
	 * Function:         unsigned int getcSPI2(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          the contents of SPIBUF register in byte/hword/word format
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function waits for receive data to be available.
	 * 					It will then read single byte/half word/word from SPI bus.
	 *
	 * Note:            byte/hword/word accesses will perform correctly.
     *
     *                  When a new data word has been shifted into shift register SPIxSR and 
     *                  the previous contents of receive register SPIxRXB have not been read
     *                  by the user software, then SPIROV bit (SPIxSTAT<6>) will be set.The 
     *                  module will not transfer the received data from SPIxSR to the SPIxRXB. 
     *                  Further data reception is disabled until the SPIROV bit is cleared. 
     *                  The SPIROV bit is not cleared automatically by the module and must be 
     *                  cleared by the user software.
	 *
	 * Example:			int data=getcSPI2();
	 ********************************************************************/
	unsigned int	getcSPI2(void);

	/* putcSPI. Wait for buffer empty and write byte/word to SPIBUF register */
	/*********************************************************************
	 * Function:         void putcSPI2(unsigned int data_out)
	 *
	 * PreCondition:    None
	 *
	 * Input:           data_out	- Single data byte/half word/word for SPI bus
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This routine writes a single byte/half word/word to the SPI bus.
	 * 					It waits so that it doesn't overwrite the previous untransmitted data.
	 *
	 * Note:            byte/hword/word accesses will perform correctly.
	 *
	 * Example:			putcSPI2(0xaa);
	 ********************************************************************/
	#define	putcSPI2(data_out)	do{while(!SPI2STATbits.SPITBE); SPI2BUF=(data_out); }while(0)

	/* getsSPI.Read string from SPIBUF */
	/*********************************************************************
	 * Function:        unsigned int getsSPI2(unsigned int length, unsigned int *rdptr,
	 * 											unsigned int spi_data_wait)
	 *
	 * PreCondition:    rdptr	- valid pointer
	 *
	 * Input:           length			- The length of data expected
	 * 					rdptr			- the received data to be recorded to this array
	 * 					spi_data_wait	- timeout value
	 *
	 * Output:          number of data bytes yet to be received
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This routine reads a string from the SPI receive buffer.
	 * 					The number of byte/word to be read is determined by parameter 'length'.
	 *
	 * Note:            rdptr is considered to be 8/16/32 bits data pointer, according to the
	 * 					current SPI mode!
     *                  When a new data word has been shifted into shift register SPIxSR and 
     *                  the previous contents of receive register SPIxRXB have not been read
     *                  by the user software, then SPIROV bit (SPIxSTAT<6>) will be set.The 
     *                  module will not transfer the received data from SPIxSR to the SPIxRXB. 
     *                  Further data reception is disabled until the SPIROV bit is cleared. 
     *                  The SPIROV bit is not cleared automatically by the module and must be 
     *                  cleared by the user software.
	 *
	 * Example:			getsSPI2(sizeof(buff), buff, 1000);
	 ********************************************************************/
	unsigned int	getsSPI2(unsigned int length, unsigned int *rdptr, unsigned int spi_data_wait);


	/* putsSPI Write string to SPIBUF */
	/*********************************************************************
	 * Function:        void putsSPI2(unsigned int length, unsigned int *wrptr)
	 *
	 * PreCondition:    wrptr	- valid pointer
	 *
	 * Input:           length	- length of bytes/words to be written
	 * 					wrptr	- address of buffer storing the data to be transmitted.
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        This function writes the specified length of data words/bytes
	 * 					from the specified buffer.
	 *
	 * Note:            wrptr is considered to be 8/16/32 bits data pointer, according to the
	 * 					current SPI mode!
	 *
	 * Example:			putsSPI2(sizeof(buf), buf);
	 ********************************************************************/
	void	putsSPI2(unsigned int length, unsigned int *wrptr);

#endif	// _SPI2




#endif /*_SPI_LEGACY_H_*/

