/*********************************************************************
 *
 *                  SPI Library definitions
 *
 *********************************************************************
 * FileName:        Spi.h
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
 * $Id: Spi.h,v 1.3 2006/11/11 00:11:04 C12878 Exp $
 * $Name:  $
 *
 ********************************************************************/

#ifndef _SPI_H_
#define _SPI_H_

#include <p32xxxx.h>

/* Detect the number of supported SPI channels.
 * The number of supported SPI channels is variant specific and it's
 * defined in the specific processor header file.
*/

#undef	_SPI_DEF_CHN_		// symbol used for SPI channel detection/definition

#if defined(_SPI1)
	#define	_SPI_DEF_CHN_		1	
#elif defined(_SPI2)
	#define	_SPI_DEF_CHN_		2
#elif defined(_SPI3)
	#define	_SPI_DEF_CHN_		3
#elif defined(_SPI4)
	#define	_SPI_DEF_CHN_		4
#endif	// getting a valid SPI channel definition
#ifdef _SPI_DEF_CHN_

// SPI channels definition
// this enumerated value can be used in any function that requires
// an SPI channel as an input parameter

typedef enum
{
#if defined(_SPI1)
	SPI_CHANNEL1	= 1,
#endif	// _SPI1

#if defined(_SPI2)
	SPI_CHANNEL2	= 2,
#endif	// _SPI2
	
#if defined(_SPI3)
	SPI_CHANNEL3	= 3,
#endif	// _SPI3

#if defined(_SPI4)
	SPI_CHANNEL4	= 4,
#endif	// _SPI4
        /* Number of available channels */
	SPI_CHANNELS	= 0
#if defined(_SPI1)
                        + 1
#endif
#if defined(_SPI2)
                        + 1
#endif
#if defined(_SPI3)
                        + 1
#endif
#if defined(_SPI4)
                        + 1
#endif
#if defined(_SPI2) || defined(_SPI2A)
	               +1
#endif	// _SPI2 || _SPI2A

#if defined(_SPI1A)
	               +1
#endif	// _SPI1A

}SpiChannel;

/********************
 * Channel functions.
 * Defined only if there's at least one valid SPI channel
 * *********************************/

// macros to translate internal SPI register definition to more user friendly interface definitions
#define _SPI_CON_MASK_(x, m)		_SPI ## x ## CON_ ## m
#define X_SPI_CON_MASK_(x, m)		_SPI_CON_MASK_(x, m)			// concatenation macro
#define _SPIxCON_MASK_(m)		X_SPI_CON_MASK_(_SPI_DEF_CHN_, m)

#define _SPI_STAT_MASK_(x, m)		_SPI ## x ## STAT_ ## m
#define X_SPI_STAT_MASK_(x, m)		_SPI_STAT_MASK_(x, m)			// concatenation macro
#define _SPIxSTAT_MASK_(m)		X_SPI_STAT_MASK_(_SPI_DEF_CHN_, m)

// open flags
typedef enum
{
	// master opening mode
	SPI_OPEN_MSTEN = 		_SPIxCON_MASK_(MSTEN_MASK),	// set the Master mode
	SPI_OPEN_SMP_END = 		_SPIxCON_MASK_(SMP_MASK),	// Master Sample Phase for the input bit at the end of the data out time. Otherwise data is sampled in the middle.
	SPI_OPEN_MSSEN = 		_SPIxCON_MASK_(MSSEN_MASK),	// enable the driving of the Slave Select (SS) output pin by the Master
	SPI_OPEN_MSSEN_HIGH = 	_SPIxCON_MASK_(FRMPOL_MASK),	// Master driven SS output active high. Otherwise low.
	
	// slave opening mode
	SPI_OPEN_SLVEN =		0,				// set the Slave mode
	SPI_OPEN_SSEN = 		_SPIxCON_MASK_(SSEN_MASK),	// enable the SS input pin. 
	
	// clocking opening mode
	SPI_OPEN_CKP_HIGH = 		_SPIxCON_MASK_(CKP_MASK),	// set the clock polarity to (idle-high, active-low). Otherwise is (idle-low, active-high).
	SPI_OPEN_CKE_REV = 		_SPIxCON_MASK_(CKE_MASK),	// set the Clock Edge reversed: transmit from active to idle. Otherwise transmit when clock goes from idle to active

	// data characters opening mode
	SPI_OPEN_MODE8 =		0,				// set 8 bits/char
	SPI_OPEN_MODE16 = 		_SPIxCON_MASK_(MODE16_MASK),	// set 16 bits/char
	SPI_OPEN_MODE32 = 		_SPIxCON_MASK_(MODE32_MASK),	// set 32 bits/char
	
	// framed mode opening mode
	SPI_OPEN_FRMEN = 		_SPIxCON_MASK_(FRMEN_MASK),	// Enable the Framed SPI support. Otherwise the Framed SPI is disabled.
	SPI_OPEN_FSP_IN =		_SPIxCON_MASK_(FRMSYNC_MASK),	// Frame Sync Pulse (FSP) direction set to input (Frame Slave).
       									// Otherwise the FSP is output and the SPI channel operates as a Frame Master.
	SPI_OPEN_FSP_HIGH = 		_SPIxCON_MASK_(FRMPOL_MASK),	// FSP polarity set active high. Otherwise the FSP is active low.
	SPI_OPEN_FSP_CLK1 =		_SPIxCON_MASK_(SPIFE_MASK),	// Set the FSP to coincide with the 1st bit clock.
       									// Otherwise the FSP precedes the 1st bit clock
	SPI_OPEN_FSP_WIDE = 		_SPIxCON_MASK_(FRMSYPW_MASK),	// set the FSP one character wide. Otherwise the FSP is one clock wide.
	
	SPI_OPEN_FRM_CNT1 =		(0 << _SPIxCON_MASK_(FRMCNT_POSITION)),	// set the number of characters per frame (Frame Counter) to 1 (default)
	SPI_OPEN_FRM_CNT2 =		(1 << _SPIxCON_MASK_(FRMCNT_POSITION)),	// set the Frame Counter to 2 
	SPI_OPEN_FRM_CNT4 =		(2 << _SPIxCON_MASK_(FRMCNT_POSITION)),	// set the Frame Counter to 4
	SPI_OPEN_FRM_CNT8 =		(3 << _SPIxCON_MASK_(FRMCNT_POSITION)),	// set the Frame Counter to 8
	SPI_OPEN_FRM_CNT16 =		(4 << _SPIxCON_MASK_(FRMCNT_POSITION)),	// set the Frame Counter to 16
	SPI_OPEN_FRM_CNT32 =		(5 << _SPIxCON_MASK_(FRMCNT_POSITION)),	// set the Frame Counter to 32

	// enhanced buffer (FIFO) opening mode
	SPI_OPEN_ENHBUF = 		_SPIxCON_MASK_(ENHBUF_MASK),	// enable the enhanced buffer mode

	SPI_OPEN_TBE_NOT_FULL =	(3 << _SPIxCON_MASK_(STXISEL_POSITION)),	// Tx Buffer event issued when Tx buffer not full (at least one slot empty)
	SPI_OPEN_TBE_HALF_EMPTY =	(2 << _SPIxCON_MASK_(STXISEL_POSITION)),	// Tx Buffer event issued when Tx buffer >= 1/2 empty
	SPI_OPEN_TBE_EMPTY =		(1 << _SPIxCON_MASK_(STXISEL_POSITION)),	// Tx Buffer event issued when Tx buffer completely empty
	SPI_OPEN_TBE_SR_EMPTY =	(0 << _SPIxCON_MASK_(STXISEL_POSITION)),	// Tx Buffer event issued when the last character is shifted out of the internal Shift Register
											// and the transmit is complete
	
	SPI_OPEN_RBF_FULL =		(3 << _SPIxCON_MASK_(SRXISEL_POSITION)),	// Rx Buffer event issued when RX buffer is full
	SPI_OPEN_RBF_HALF_FULL =	(2 << _SPIxCON_MASK_(SRXISEL_POSITION)),	// Rx Buffer event issued when RX buffer is >= 1/2 full
	SPI_OPEN_RBF_NOT_EMPTY =	(1 << _SPIxCON_MASK_(SRXISEL_POSITION)),	// Rx Buffer event issued when RX buffer is not empty
	SPI_OPEN_RBF_EMPTY =		(0 << _SPIxCON_MASK_(SRXISEL_POSITION)),	// Rx Buffer event issued when RX buffer is empty (the last character in the buffer is read).

	// general opening mode
	SPI_OPEN_DISSDO = 		_SPIxCON_MASK_(DISSDO_MASK),	// disable the usage of the SDO pin by the SPI
	SPI_OPEN_SIDL = 		_SPIxCON_MASK_(SIDL_MASK),	// enable the Halt in the CPU Idle mode. Otherwise the SPI will be still active when the CPU is in Idle mode. 
	SPI_OPEN_FRZ = 		_SPIxCON_MASK_(FRZ_MASK),	// Debug mode only: enable the Freeze operation while in Debug. Otherwise continue to operate.
	SPI_OPEN_ON = 		_SPIxCON_MASK_(ON_MASK),	// turn ON the SPI (not used in SpiChnOpen)
}SpiOpenFlags;	// open flags that can be used with SpiChnOpen. Defined in the processor header file.

typedef enum
{
	SPI_STAT_SPIRBF = 		_SPIxSTAT_MASK_(SPIRBF_MASK),	// receive buffer full
	SPI_STAT_SPITBF = 		_SPIxSTAT_MASK_(SPITBF_MASK),	// transmit buffer full
	SPI_STAT_SPITBE = 		_SPIxSTAT_MASK_(SPITBE_MASK),	// transmit buffer empty
	SPI_STAT_SPIRBE = 		_SPIxSTAT_MASK_(SPIRBE_MASK),	// receive buffer empty
	SPI_STAT_SPIROV = 		_SPIxSTAT_MASK_(SPIROV_MASK),	// receive overflow
	SPI_STAT_SPISRMT = 		_SPIxSTAT_MASK_(SRMT_MASK),  	// shift register empty
	SPI_STAT_SPITUR = 		_SPIxSTAT_MASK_(SPITUR_MASK),	// transmit underrun
	SPI_STAT_SPIBUSY = 		_SPIxSTAT_MASK_(SPIBUSY_MASK),	// busy with transaction
}SpiStatusFlags;        // possible SPI status flags 


/*********************************************************************
 * Function:        void SpiChnOpen(SpiChannel chn, SpiOpenFlags oFlags, unsigned int srcClkDiv)
 *
 * PreCondition:    srcClkDiv  - valid value between 2 and 1024
 *                  chn        - a valid SPI channel number
 *
 * Input:           chn    - the channel to set
 *                  oFlags - any of the values from SpiOpenFlags:
 *                             master slave opening mode: SPI_OPEN_MSTEN, SPI_OPEN_SLVEN, SPI_OPEN_SSEN
 *                             clocking and character opening mode: SPI_OPEN_CKP_HIGH, SPI_OPEN_CKE_REV, SPI_OPEN_SMP_END, SPI_OPEN_MODE8, SPI_OPEN_MODE16, SPI_OPEN_MODE32
 *                             framed mode opening mode: SPI_OPEN_FSP_CLK1, SPI_OPEN_FSP_HIGH, SPI_OPEN_FSP_IN, SPI_OPEN_FRMEN
 *                             general opening mode: SPI_OPEN_DISSDO, SPI_OPEN_SIDL, SPI_OPEN_FRZ, SPI_OPEN_ON
 *                  srcClkDiv - Source Clock divisor to extract the bitrate=srcClk/srcClkDiv.
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function opens the SPI channel: turns the channel on and initializes it according to the oFlags input parameter.
 *                  After that the channel is enabled.
 *                  It also sets the brg register.
 *                  The SPI bitrate is given by: bitrate=srcClk/(2*(SPIBRG+1))
 *                  The input parametes srcClkDiv specifies the srcClk divisor term (2*(SPIBRG+1)),
 *                  so the BRG is calculated as SPIBRG=srcClkDiv/2-1.
 *
 * Note:            - The channel is turned off, the pending interrupts are cleared, interrupts are disabled. After that it is configured
 *                  - The bitrate is always obtained by dividing the srcClk by srcClkDiv, an even number
 *                  between 2 and 1024.
 *                  - For a specific SPI bitrate, the srcClkDiv that has to be passed is:
 *                  srcClkDiv=srcClk/bitrate;
 *                  - When selecting the number of bits per character, SPI_OPEN_MODE32 has the highest priority.
 *                  If SPI_OPEN_MODE32 is not set, then SPI_OPEN_MODE16 selects the character width.
 *                  - The function properly sets the SPI pins as digital i/o pins.
 *                  - The SS pin is set as a digital pin only if in frame mnode or if the SPI_OPEN_SSEN is set.
 *                  Even in master mode the library will properly se the SS pin as an digital output
 *                  if the SPI_OPEN_SSEN is set.
 *                  - The SPI channel is turned ON after it is configured. The use of SPI_OPEN_ON is not needed.
 *                  - For PIC32MX the srcClk is the peripheral bus clock.
 *
 * Example:        int srcClk=GetPBusFrequency(); SpiChnOpen(SPI_CHANNEL1, SPI_OPEN_MSTEN|SPI_OPEN_SMP_END|SPI_OPEN_MODE32, srcClk/20000000);
 *                 will open the SPI1 and set the bit rate to 20MHz.
 ********************************************************************/
void	SpiChnOpen(SpiChannel chn, SpiOpenFlags oFlags, unsigned int srcClkDiv);



/*********************************************************************
 * Function:        void SpiChnClose(SpiChannel chn)
 *
 * PreCondition:    chn	- a valid SPI channel number
 *
 * Input:			chn		- the channel to close
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function closes the SPI channel. Some previous error conditions are cleared.
 * 					Channel interrupts are disabled.
 *
 * Note:		- The I/O pins used by the SPI module are returned to their reset configuration.
 * 			- The SPI_OPEN_SSEN is used to decide if the SS pin has to be returned to the reset state.
 *
 * Example:			SpiChnClose(SPI_CHANNEL2);
 ********************************************************************/
void	SpiChnClose(SpiChannel chn);



/*********************************************************************
 * Function:        void SpiChnChangeMode(SpiChannel chn, int isMaster, int isFrmMaster, int waitBusy)
 *
 * PreCondition:    None
 *
 * Input:           chn         - the channel to set
 *                  isMaster    - master/slave mode
 *                  isFrmMaster - frame master/slave mode
 *                  waitBusy    - boolean to wait/no wait for the current transfer to finish
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function changes the SPI channel mode on the fly.
 *
 * Note:            - If waitBusy is TRUE, the function blocks until the current transfer, if any, is completed.
 *                    Due to a bug in the PIC32_5XX_6xx_7xx SPI implementation, the SPIBUSY/SRMT flag is set one spi_clk earlier.
 *                    What it means is that the data is not available in the SPIRxBUFF/SPIRxFIFO at the moment that SPIBUSY is cleared.
 *                    The function will wait for the SPIBUSY to be cleared.
 *                    For high SPIxBRG and PBDIV values note that the number of CPU clock cycles that have to be spent in this function could be significant.
 *                  - If waitBusy is FALSE, the function performs the mode switching immediately. It assumes that no transfer is currently on.
 *                    The caller must make sure that the current transfer, if any, is completed. 
 *                  - isFrmMaster is relevant only if the SPI channel is operating in frame mode
 *                  - The SCK is properly configured as an digital I/O pin
 *                  - The SS is configured as a digital pin only if in frame mode or if the SSEN configuration bit is set.
 *
 * Example:         SpiChnChangeMode(SPI_CHANNEL2, TRUE, TRUE, TRUE);
 ********************************************************************/
void	SpiChnChangeMode(SpiChannel chn, int isMaster, int isFrmMaster, int waitBusy);



/*********************************************************************
 * Function:        int SpiChnDataRdy(SpiChannel chn)
 *
 * PreCondition:    None
 *
 * Input:			chn			- the channel to check
 *
 * Output:          TRUE - if data available
 *                  FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function reads the SPI channel data ready condition.
 *
 * Note:            Valid call in both standard and enhanced buffer (FIFO) mode.
 *
 * Example:         int isDataAvlbl=SpiChnDataRdy(SPI_CHANNEL1);
 ********************************************************************/
int		SpiChnDataRdy(SpiChannel chn);

/*********************************************************************
 * Function:        int SpiChnRxBuffEmpty(SpiChannel chn)
 *
 * PreCondition:    None
 *
 * Input:           chn - the channel to check
 *
 * Output:          TRUE - if the RX buffer is empty
 *                  FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the SPI channel RX Buffer empty condition.
 *
 * Note:            Valid only in enhanced buffer (FIFO) mode.
 *
 * Example:         int isRxEmpty=SpiChnRxBuffEmpty(SPI_CHANNEL1);
 ********************************************************************/
int		SpiChnRxBuffEmpty(SpiChannel chn);

/*********************************************************************
 * Function:        int SpiChnRxBuffFull(SpiChannel chn)
 *
 * PreCondition:    None
 *
 * Input:           chn - the channel to check
 *
 * Output:          TRUE - if the RX buffer is full
 *                  FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the SPI channel RX Buffer full condition.
 *
 * Note:            Valid in both standard and enhanced buffer (FIFO) mode.
 *                  In enhanced buffer mode it signals that the whole FIFO is full.
 *
 * Example:         int isRxFull=SpiChnRxBuffFull(SPI_CHANNEL1);
 ********************************************************************/
int		SpiChnRxBuffFull(SpiChannel chn);

/*********************************************************************
 * Function:        int SpiChnRxBuffCount(SpiChannel chn)
 *
 * PreCondition:    None
 *
 * Input:           chn - the channel to check
 *
 * Output:          the number of characters available in the RX buffer
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the number of characters available in the SPI channel RX Buffer.
 *
 * Note:            Valid only in enhanced buffer (FIFO) mode.
 *
 * Example:         int nCharsAvlbl=SpiChnRxBuffCount(SPI_CHANNEL1);
 ********************************************************************/
int		SpiChnRxBuffCount(SpiChannel chn);


/*********************************************************************
 * Function:        unsigned int SpiChnReadC(SpiChannel chn)
 *
 * PreCondition:    None
 *
 * Input:           chn - the channel to use
 *
 * Output:          data available in the SPI rx buffer
 *
 * Side Effects:    None
 *
 * Overview:        This function returns immediately the data from the SPI buffer.
 *                  It does not check if there's any new data available.
 *
 * Note:            When a new data word has been shifted into shift register SPIxSR and:
 *                  - in standard mode: the previous contents of receive register SPIxRXB have not been read
 *                  - in FIFO mode: the FIFO is full
 *                  then the Rx Overflow (SPIROV) bit will be set.
 *                  The module will not transfer the received data from SPIxSR to the SPIxRXB (FIFO).
 *                  Further data reception is disabled until the SPIROV bit is cleared. 
 *                  The SPIROV bit is not cleared automatically by the module and must be 
 *                  cleared by the user software (using SpiChnGetRov()).
 *
 * Example:         unsigned int newData=SpiChnReadC(SPI_CHANNEL2);
 ********************************************************************/
unsigned int		SpiChnReadC(SpiChannel chn);


/*********************************************************************
 * Function:        unsigned int SpiChnGetC(SpiChannel chn)
 *
 * PreCondition:    None
 *
 * Input:			chn			- the channel to check
 *
 * Output:          data available in the SPI rx buffer
 *
 * Side Effects:    None
 *
 * Overview:        This function waits for data to be available and returns it.
 *
 * Note:            When a new data word has been shifted into shift register SPIxSR and:
 *                  - in standard mode: the previous contents of receive register SPIxRXB have not been read
 *                  - in FIFO mode: the FIFO is full
 *                  then the Rx Overflow (SPIROV) bit will be set.
 *                  The module will not transfer the received data from SPIxSR to the SPIxRXB (FIFO).
 *                  Further data reception is disabled until the SPIROV bit is cleared. 
 *                  The SPIROV bit is not cleared automatically by the module and must be 
 *                  cleared by the user software (using SpiChnGetRov()).
 *
 * Example:         unsigned int newData=SpiChnGetC(SPI_CHANNEL2);
 ********************************************************************/
unsigned int		SpiChnGetC(SpiChannel chn);


/*********************************************************************
 * Function:        void SpiChnGetS(SpiChannel chn, unsigned int *pBuff, unsigned int nChars)
 *
 * PreCondition:    pBuff has to be a valid pointer to a buffer large enough to store all the received characters
 *
 * Input:           chn    - the SPI channel
 *                  pBuff  - address of buffer to store data
 *                  nChars - number of characters expected
 *
 * Output:          None

 * Side Effects:    None
 *
 * Overview:        This routine reads a buffer of characters from the corresponding SPI channel receive buffer.
 *                  The number of byte/hword/word to be read is determined by parameter nChars.
 *                  Waits for RX data available for each character.
 *
 * Note:            - pBuff is considered to be 8/16/32 bits data pointer, according to the
 *                  current SPI mode!
 *                  - The function blocks waiting for the whole buffer to be received.
 *                  
 *                  When a new data word has been shifted into shift register SPIxSR and 
 *                  the previous contents of receive register SPIxRXB have not been read
 *                  by the user software (or the FIFO is full, in enhanced buffer mode),
 *                  then SPIROV bit will be set.
 *                  The module will not transfer the received data from SPIxSR to the SPIxRXB (FIFO). 
 *                  Further data reception is disabled until the SPIROV bit is cleared. 
 *                  The SPIROV bit is not cleared automatically by the module and must be 
 *                  cleared by the user software (using SpiChnGetRov()).
 *
 * Example:         unsigned short myBuff[100]; SpiChnGetS(SPI_CHANNEL2, myBuff, sizeof(myBuff)/sizeof(*myBuff));	// receive 16 bit characters
 ********************************************************************/
void	SpiChnGetS(SpiChannel chn, unsigned int *pBuff, unsigned int nChars);



/*********************************************************************
 * Function:        int SpiChnTxBuffEmpty(SpiChannel chn)
 *
 * PreCondition:    None
 *
 * Input:           chn - the channel to check
 *
 * Output:          TRUE  - if transmit buffer empty
 *                  FALSE - otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function reads the SPI channel transmit buffer empty condition.
 *
 * Note:            Valid in both standard and enhanced buffer mode.
 *
 * Example:         int canTransmit=SpiChnTxBuffEmpty(SPI_CHANNEL1);
 ********************************************************************/
int		SpiChnTxBuffEmpty(SpiChannel chn);

/*********************************************************************
 * Function:        int SpiChnTxBuffFull(SpiChannel chn)
 *
 * PreCondition:    None
 *
 * Input:           chn - the channel to check
 *
 * Output:          TRUE  - if transmit buffer empty
 *                  FALSE - otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function reads the SPI channel transmit buffer empty condition.
 *
 * Note:            Valid only in enhanced buffer mode.
 *
 * Example:         int txFull=SpiChnTxBuffFull(SPI_CHANNEL1);
 ********************************************************************/
int		SpiChnTxBuffFull(SpiChannel chn);

/*********************************************************************
 * Function:        int SpiChnTxBuffCount(SpiChannel chn)
 *
 * PreCondition:    None
 *
 * Input:           chn - the channel to check
 *
 * Output:          the number of characters available in the TX buffer
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the number of characters in the SPI channel TX Buffer.
 *
 * Note:            Valid only in enhanced buffer (FIFO) mode.
 *
 * Example:         int nCharsToTx=SpiChnTxBuffCount(SPI_CHANNEL1);
 ********************************************************************/
int		SpiChnTxBuffCount(SpiChannel chn);



/*********************************************************************
 * Function:        void SpiChnWriteC(SpiChannel chn, unsigned int data)
 *
 * PreCondition:    None
 *
 * Input:           chn  - the channel to use
 *                  data - the data to be written to the port
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine writes inmmediately a character (byte/half word/word) to the SPI buffer register.
 *
 * Note:            byte/hword/word accesses will perform correctly.
 *
 * Example:         SpiChnWriteC(SPI_CHANNEL1, 0x1b);		// send an ESC character
 ********************************************************************/
void		SpiChnWriteC(SpiChannel chn, unsigned int data);


/*********************************************************************
 * Function:        void SpiChnPutC(SpiChannel chn, unsigned int data)
 *
 * PreCondition:    None
 *
 * Input:			chn			- the channel to check
 * 					data	- the data to be written to the port
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine writes a single byte/half word/word to the SPI bus.
 * 					It waits for TX buffer empty, so that it doesn't overwrite the previous untransmitted data.
 *
 * Note:            byte/hword/word accesses will perform correctly.
 *
 * Example:			SpiChnPutC(SPI_CHANNEL1, 0x1b);		// send an ESC character
 ********************************************************************/
void		SpiChnPutC(SpiChannel chn, unsigned int data);

/*********************************************************************
 * Function:        void SpiChnPutS(SpiChannel chn, unsigned int* pBuff, unsigned int nChars)
 *
 * PreCondition:    None
 *
 * Input:           chn		- the SPI channel
 * 					pBuff	- address of buffer storing the data to be transmitted.
 * 					nChars	- number of characters to be transmitted

 * Output:          None

 * Side Effects:    None

 * Overview:        This function writes the specified number of 8/16/32 bit characters
 * 					from the specified buffer.
 *					It waits for Tx buffer empty so the characters are not overwritten.

 * Note:            pBuff is considered to be 8/16/32 bits data pointer, according to the
 * 					current SPI mode!
 *
 * Example:			SpiChnPutS(SPI_CHANNEL1, myBuff, 100);
 ********************************************************************/
void		SpiChnPutS(SpiChannel chn, unsigned int* pBuff, unsigned int nChars);

/*********************************************************************
 * Function:        int SpiChnGetRov(SpiChannel chn, int clear)
 *
 * PreCondition:    None
 *
 * Input:           chn   - the channel to check
 *                  clear - if TRUE, the overflow condition has to be cleared, if present
 *
 * Output:          TRUE  - if overflow
 *                  FALSE - otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function reads the SPI channel overflow condition (SPIROV bit)
 *                  and clears it, if required.
 *
 * Note:            None
 *
 * Example:         int isOvfl=SpiChnGetRov(SPI_CHANNEL1, FALSE);
 ********************************************************************/
int		SpiChnGetRov(SpiChannel chn, int clear);


/*********************************************************************
 * Function:        int SpiChnIsBusy(SpiChannel chn)
 *
 * PreCondition:    None
 *
 * Input:           chn   - the channel to check
 *
 * Output:          TRUE  - if channel is busy with a transaction
 *                  FALSE - otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the SPI channel busy condition (SPIBUSY).
 *                  Whenever there is an ongoing transaction, the SPIBUSY status bit will be set. 
 *
 * Note:            None
 *
 * Example:         int isBusy=SpiChnIsBusy(SPI_CHANNEL1);
 ********************************************************************/
int		SpiChnIsBusy(SpiChannel chn);

/*********************************************************************
 * Function:        int SpiChnIsSrEmpty(SpiChannel chn)
 *
 * PreCondition:    None
 *
 * Input:           chn   - the channel to check
 *
 * Output:          TRUE  - if the channel shift register is empty
 *                  FALSE - otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the SPI channel shift register condition (SRMT).
 *                  Whenever the transmit shift register is empty, the SRMT status bit will be set. 
 *
 * Note:            None
 *
 * Example:         int isEmpty=SpiChnIsSrEmpty(SPI_CHANNEL1);
 ********************************************************************/
int		SpiChnIsSrEmpty(SpiChannel chn);


/*********************************************************************
 * Function:        int SpiChnGetTur(SpiChannel chn)
 *
 * PreCondition:    None
 *
 * Input:           chn   - the channel to check
 *
 * Output:          TRUE  - if channel transmit underrun occurred
 *                  FALSE - otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the SPI channel transmit underrun condition.
 *                  This condition can occur only in framed mode when there's more than 1 characters per frame.
 *                  If the SPI channel has to transmit another character for the current frame and the character is not available,
 *                  a TX underrun condition occurs.
 *
 * Note:            The Tx Underrun condition must be cleared by disabling /re-enabling the Spi channel.
 *                  No transmission can further occur once this condition is set.
 *
 * Example:         int isUnderrun=SpiChnGetTur(SPI_CHANNEL1);
 ********************************************************************/
int		SpiChnGetTur(SpiChannel chn);


/*********************************************************************
 * Function:        int SpiChnGetStatus(SpiChannel chn)
 *
 * PreCondition:    None
 *
 * Input:           chn   - the channel to check
 *
 * Output:          the current value of the SPI status
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the complete SPI channel status in one single call.
 *
 * Note:            The interpretation of some status bits can differ
 *                  depending on the current operation mode (standard vs enhanced).
 *
 * Example:         SpiStatusFlags chnStat=SpiChnGetStatus(SPI_CHANNEL1);
 ********************************************************************/
SpiStatusFlags      SpiChnGetStatus(SpiChannel chn);


/*********************************************************************
 * Function:        volatile void* SpiChnBuffer(SpiChannel chn)
 *
 * PreCondition:    None
 *
 * Input:           chn   - the required channel
 *
 * Output:          the address of the SPI buffer associated to the selected channel.
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the address of the SPI channel buffer.
 *
 * Note:            The same address is valid for both read and write operations.
 *
 *                  The function is useful when the corresponding SPI channel
 *                  has to be used as the source or destination of a DMA transfer.
 *
 * Example:         volatile unsigned short* spiBuffAdd=(unsigned short*)SpiChnBuffer(SPI_CHANNEL1);
 ********************************************************************/
volatile void*       SpiChnBuffer(SpiChannel chn);

/********************************************************************
 * Low Level SPI functions
 * Direct configuration and Clock/bitrate helpers.
 ********************************************************************/

// configuration flags
typedef enum
{
	// master configuration
	SPI_CONFIG_MSTEN = 		_SPIxCON_MASK_(MSTEN_MASK),	// set the Master mode
	SPI_CONFIG_SMP_END = 		_SPIxCON_MASK_(SMP_MASK),	// Master Sample Phase for the input bit at the end of the data out time. Otherwise data is sampled in the middle.
	SPI_CONFIG_MSSEN = 		_SPIxCON_MASK_(MSSEN_MASK),	// enable the driving of the Slave Select (SS) output pin by the Master
	SPI_CONFIG_MSSEN_HIGH = 	_SPIxCON_MASK_(FRMPOL_MASK),	// Master driven SS output active high. Otherwise low.
	
	// slave configuration
	SPI_CONFIG_SLVEN =		0,				// set the Slave mode
	SPI_CONFIG_SSEN = 		_SPIxCON_MASK_(SSEN_MASK),	// enable the SS input pin. 
	
	// clocking configuration
	SPI_CONFIG_CKP_HIGH = 		_SPIxCON_MASK_(CKP_MASK),	// set the clock polarity to (idle-high, active-low). Otherwise is (idle-low, active-high).
	SPI_CONFIG_CKE_REV = 		_SPIxCON_MASK_(CKE_MASK),	// set the Clock Edge reversed: transmit from active to idle. Otherwise transmit when clock goes from idle to active

	// data characters configuration
	SPI_CONFIG_MODE8 =		0,				// set 8 bits/char
	SPI_CONFIG_MODE16 = 		_SPIxCON_MASK_(MODE16_MASK),	// set 16 bits/char
	SPI_CONFIG_MODE32 = 		_SPIxCON_MASK_(MODE32_MASK),	// set 32 bits/char
	
	// framed mode configuration
	SPI_CONFIG_FRMEN = 		_SPIxCON_MASK_(FRMEN_MASK),	// Enable the Framed SPI support. Otherwise the Framed SPI is disabled.
	SPI_CONFIG_FSP_IN =		_SPIxCON_MASK_(FRMSYNC_MASK),	// Frame Sync Pulse (FSP) direction set to input (Frame Slave).
       									// Otherwise the FSP is output and the SPI channel operates as a Frame Master.
	SPI_CONFIG_FSP_HIGH = 		_SPIxCON_MASK_(FRMPOL_MASK),	// FSP polarity set active high. Otherwise the FSP is active low.
	SPI_CONFIG_FSP_CLK1 =		_SPIxCON_MASK_(SPIFE_MASK),	// Set the FSP to coincide with the 1st bit clock.
       									// Otherwise the FSP precedes the 1st bit clock
	SPI_CONFIG_FSP_WIDE = 		_SPIxCON_MASK_(FRMSYPW_MASK),	// set the FSP one character wide. Otherwise the FSP is one clock wide.
	
	SPI_CONFIG_FRM_CNT1 =		(0 << _SPIxCON_MASK_(FRMCNT_POSITION)),	// set the number of characters per frame (Frame Counter) to 1 (default)
	SPI_CONFIG_FRM_CNT2 =		(1 << _SPIxCON_MASK_(FRMCNT_POSITION)),	// set the Frame Counter to 2 
	SPI_CONFIG_FRM_CNT4 =		(2 << _SPIxCON_MASK_(FRMCNT_POSITION)),	// set the Frame Counter to 4
	SPI_CONFIG_FRM_CNT8 =		(3 << _SPIxCON_MASK_(FRMCNT_POSITION)),	// set the Frame Counter to 8
	SPI_CONFIG_FRM_CNT16 =		(4 << _SPIxCON_MASK_(FRMCNT_POSITION)),	// set the Frame Counter to 16
	SPI_CONFIG_FRM_CNT32 =		(5 << _SPIxCON_MASK_(FRMCNT_POSITION)),	// set the Frame Counter to 32

	// enhanced buffer (FIFO) configuration
	SPI_CONFIG_ENHBUF = 		_SPIxCON_MASK_(ENHBUF_MASK),	// enable the enhanced buffer mode

	SPI_CONFIG_TBE_NOT_FULL =	(3 << _SPIxCON_MASK_(STXISEL_POSITION)),	// Tx Buffer event issued when Tx buffer not full (at least one slot empty)
	SPI_CONFIG_TBE_HALF_EMPTY =	(2 << _SPIxCON_MASK_(STXISEL_POSITION)),	// Tx Buffer event issued when Tx buffer >= 1/2 empty
	SPI_CONFIG_TBE_EMPTY =		(1 << _SPIxCON_MASK_(STXISEL_POSITION)),	// Tx Buffer event issued when Tx buffer completely empty
	SPI_CONFIG_TBE_SR_EMPTY =	(0 << _SPIxCON_MASK_(STXISEL_POSITION)),	// Tx Buffer event issued when the last character is shifted out of the internal Shift Register
											// and the transmit is complete
	
	SPI_CONFIG_RBF_FULL =		(3 << _SPIxCON_MASK_(SRXISEL_POSITION)),	// Rx Buffer event issued when RX buffer is full
	SPI_CONFIG_RBF_HALF_FULL =	(2 << _SPIxCON_MASK_(SRXISEL_POSITION)),	// Rx Buffer event issued when RX buffer is >= 1/2 full
	SPI_CONFIG_RBF_NOT_EMPTY =	(1 << _SPIxCON_MASK_(SRXISEL_POSITION)),	// Rx Buffer event issued when RX buffer is not empty
	SPI_CONFIG_RBF_EMPTY =		(0 << _SPIxCON_MASK_(SRXISEL_POSITION)),	// Rx Buffer event issued when RX buffer is empty (the last character in the buffer is read).

	// general configuration
	SPI_CONFIG_DISSDO = 		_SPIxCON_MASK_(DISSDO_MASK),	// disable the usage of the SDO pin by the SPI
	SPI_CONFIG_SIDL = 		_SPIxCON_MASK_(SIDL_MASK),	// enable the Halt in the CPU Idle mode. Otherwise the SPI will be still active when the CPU is in Idle mode. 
	SPI_CONFIG_FRZ = 		_SPIxCON_MASK_(FRZ_MASK),	// Debug mode only: enable the Freeze operation while in Debug. Otherwise continue to operate.
	SPI_CONFIG_ON = 		_SPIxCON_MASK_(ON_MASK),	// turn ON the SPI (not used in SpiChnOpen)
}SpiConfigFlags;	// configuration flags that can be used with SpiChnConfigure. Defined in the processor header file.


/*********************************************************************
 * Function:        void SpiChnConfigure(SpiChannel chn, SpiConfigFlags config)
 *
 * PreCondition:    chn        - a valid SPI channel number
 *
 * Input:           chn    - the channel to set
 *                  config - any of the values from SpiConfigFlags:
 *                             master slave configure: SPI_CONFIG_MSTEN, SPI_CONFIG_SLVEN, SPI_CONFIG_SSEN
 *                             clocking and character configuration: SPI_CONFIG_CKP, SPI_CONFIG_CKE, SPI_CONFIG_SMP_END, SPI_CONFIG_MODE8, SPI_CONFIG_MODE16, SPI_CONFIG_MODE32
 *                             framed mode configuration: SPI_CONFIG_SPIFE, SPI_CONFIG_FRMPOL, SPI_CONFIG_FRMSYNC, SPI_CONFIG_FRMEN
 *                             general configuration: SPI_CONFIG_DISSDO, SPI_CONFIG_SIDL, SPI_CONFIG_FRZ, SPI_CONFIG_ON
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is an alternative to SpiChnOpen. The application can first configure and then turn ON the channel.
 *                  The function performs the configuration of the SPI channel according to the config input parameter.
 *
 * Note:            - The channel is NOT turned off by this function; It should be turned off before calling this function.
 *                  - The pending interrupts are NOT cleared or disabled.
 *                  - The function does NOT set the SPI pins as digital i/o pins.
 *                  - The SPI channel is configured but NOT turned ON. Use SpiChnEnable(chn, 1) to turn ON the channel.
 *                  - When selecting the number of bits per character, SPI_CONFIG_MODE32 has the highest priority.
 *                  If SPI_CONFIG_MODE32 is not set, then SPI_CONFIG_MODE16 selects the character width.
 *
 * Example:        SpiChnEnable(SPI_CHANNEL1, 0);
 *                 SpiChnConfigure(SPI_CHANNEL1, SPI_CONFIG_MSTEN|SPI_CONFIG_SMP_END|SPI_CONFIG_MODE32);
 *                 SpiChnEnable(SPI_CHANNEL1, 1);
 *                 will configure and then enable the SPI1.
 ********************************************************************/
void	SpiChnConfigure(SpiChannel chn, SpiConfigFlags config);


/*********************************************************************
 * Function:        void SpiChnEnable(SpiChannel chn, int enable)
 *
 * PreCondition:    chn        - a valid SPI channel number
 *
 * Input:           chn    - the channel to enable/disable
 *                  enable - boolean to enable/disable the channel
 *                  
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function enables or disables the SPI channel.
 * 
 * Note:            - Before enabling the channel, proper configuration should be done.
 *
 * Example:        SpiChnConfigure(SPI_CHANNEL1, SPI_CONFIG_MSTEN|SPI_CONFIG_SMP_END|SPI_CONFIG_MODE32);
 *                 SpiChnEnable(SPI_CHANNEL1, 1);
 *                 will configure and enable the SPI1 channel.
 ********************************************************************/
void	SpiChnEnable(SpiChannel chn, int enable);



/*********************************************************************
 * Function:        unsigned int SpiChnSetBitRate(SpiChannel chn, unsigned int srcClk, unsigned int spiClk)
 *
 * PreCondition:    srcClk/1024 <= spiClk <= srcClk/2;
 *                  chn        - a valid SPI channel number
 *
 * Input:           chn    - the channel to set the bitrate for
 *                  srcClk - the SPI module Source Clock, Hz
 *                  spiClk - the desired SPI bitrate frequency, Hz
 *
 * Output:          the actual selected bitrate, Hz
 *
 * Side Effects:    None
 *
 * Overview:        This function configures the SPI channel with a desired bitrate.
 *                  The SPI bitrate is given by: spiClk=srcClk/(2*(SPIBRG+1))
 *                  The proper SPIBRG value is calculated as SPIBRG=(srcClk/spiClk)/2-1.
 *
 * Note:            - The channel has to be first configured with a valid bitrate and then enabled.
 *                  The bitrate can be changed dynamically, when no transaction is in progress.
 *                  - The bitrate is irrelevant for the Slave operation mode since the clock is provided externally, by the Master.
 *                  - For PIC32MX the srcClk is the peripheral bus clock.
 *
 * Example:        SpiChnEnable(SPI_CHANNEL1, 0);
 *                 SpiChnConfigure(SPI_CHANNEL1, SPI_CONFIG_MSTEN|SPI_CONFIG_SMP_END|SPI_CONFIG_MODE32); 
 *                 SpiChnSetBitRate(SPI_CHANNEL1, GetPBusFrequency(), 20000000);
 *                 SpiChnEnable(SPI_CHANNEL1, 1);
 *                 will configure the SPI1, set the bitrate to 20MHz.
 ********************************************************************/
unsigned int	SpiChnSetBitRate(SpiChannel chn, unsigned int srcClk, unsigned int spiClk);



/*********************************************************************
 * Function:        void SpiChnSetBrg(SpiChannel chn, unsigned int brg)
 *
 * PreCondition:    None
 *
 * Input:			chn		- the channel to set
 *					brg		- value for the brg register
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function updates the values for the SPI channel brg/prescalers.
 *
 * Note:            None
 *
 * Example:         SpiChnSetBrg(SPI_CHANNEL1, 0x12);
 ********************************************************************/
void	SpiChnSetBrg(SpiChannel chn, unsigned int brg);


/******************************************************************************
 * Function:        unsigned int SpiBrgVal(unsigned int srcClk, unsigned int spiClk)
 *
 * Description:     Calculates the BRG values needed for the SPI configuration
 *
 * PreCondition:    srcClk/1024 <= spiClk <= srcClk/2;
 *
 * Inputs:          srcClk:   - the source clock to the SPI module, Hz
 *                  spiClk:   - the desired SPI clock frequency, Hz
 *
 * Output:          The proper BRG value.
 *                  For PIC32MX the srcClk is the Peripheral bus clock value.
 *
 * Example:         SpiChnSetBrg(SPI_CHANNEL1, SpiBrgVal(72000000, 9000000));
 *
 *****************************************************************************/
extern __inline__ unsigned int __attribute__((always_inline))	SpiBrgVal(unsigned int srcClk, unsigned int spiClk)
{
	return (srcClk / (2 * spiClk)) - 1;
}


/********************************************************************
 * Include legacy SPI functions
 * New projects should not use them!
 * Note that interrupt functions are no longer provided.
 * The functions in the int.h should be used instead.
 ********************************************************************/
#ifndef _PLIB_DISABLE_LEGACY
	#include <peripheral/legacy/spi_legacy.h>
#endif



#endif		// _SPI_DEF_CHN_ 

#endif /*_SPI_H_*/

