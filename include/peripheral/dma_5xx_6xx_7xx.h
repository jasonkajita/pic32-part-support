/*********************************************************************
 *
 *                  DMA API definitions
 *
 *********************************************************************
 * FileName:        Dma.h
 * Dependencies:	p32xxxx.h
 * 					int.h
 *
 * Processor:       PIC32
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC32/PIC24F Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PIC32/PIC24F Microcontroller products.
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
 * $Id: Dma.h,v 1.9 2007/01/17 21:35:46 C12878 Exp $
 * $Name:  $
 *
 ********************************************************************/

#ifndef _DMA_H_
#define _DMA_H_

#include <p32xxxx.h>


// DMA definitions

#ifdef _DMAC0
	#define _DMA_CHANNELS		// DMA channels exist


// existent DMA channels
	typedef enum
	{
		DMA_CHANNEL0,
	#ifdef _DMAC1
		DMA_CHANNEL1,
	#ifdef _DMAC2
		DMA_CHANNEL2,
	#ifdef _DMAC3
		DMA_CHANNEL3,
	#ifdef _DMAC4
		DMA_CHANNEL4,
	#ifdef _DMAC5
		DMA_CHANNEL5,
	#ifdef _DMAC6
		DMA_CHANNEL6,
	#ifdef _DMAC7
		DMA_CHANNEL7,
	#endif	// _DMAC7
	#endif	// _DMAC6
	#endif	// _DMAC5
	#endif	// _DMAC4
	#endif	// _DMAC3
	#endif	// _DMAC2
	#endif	// _DMAC1
		//	add/remove DMA channel as needed here

		DMA_CHANNELS	// number of current available channels
	}DmaChannel;


	// Relative Dma channels priority, between each other
	typedef enum
	{
		DMA_CHN_PRI0,
		DMA_CHN_PRI1,
		DMA_CHN_PRI2,
		DMA_CHN_PRI3
	}DmaChannelPri;



	// high level definitions for the API functions

	typedef enum
	{
		DMA_OPEN_DEFAULT = 0,							        // DMA default operation
		DMA_OPEN_AUTO	= _DCH0CON_CHAEN_MASK,					// DMA channel is auto enabled
		DMA_OPEN_CHAIN_LOW  = (_DCH0CON_CHCHN_MASK|_DCH0CON_CHCHNS_MASK),	// DMA channel is chained to lower channel
		DMA_OPEN_CHAIN_HI  = (_DCH0CON_CHCHN_MASK),				// DMA channel is chained to higher channel
		DMA_OPEN_DET_EN = _DCH0CON_CHAED_MASK,					// events detection enabled while channel off
		DMA_OPEN_ENABLE = _DCH0CON_CHEN_MASK,					// DMA channel is enabled after open
		DMA_OPEN_MATCH	= 0x80000000,						    // DMA channel stops on match
	}DmaOpenFlags;	// flags for the channel open


	typedef enum
	{
		DMA_EV_ERR =			0x1,		// address error event
		DMA_EV_ABORT = 			0x2,		// transfer abort event
		DMA_EV_CELL_DONE =		0x4,		// cell transfer complete event
		DMA_EV_BLOCK_DONE =		0x8,		// block transfer complete event
		DMA_EV_DST_HALF =		0x10,		// destination half event
		DMA_EV_DST_FULL =		0x20,		// destination full event
		DMA_EV_SRC_HALF =		0x40,		// source half event
		DMA_EV_SRC_FULL =		0x80,		// source full event

		DMA_EV_ALL_EVNTS=		(DMA_EV_ERR|DMA_EV_ABORT|DMA_EV_CELL_DONE|DMA_EV_BLOCK_DONE|DMA_EV_DST_HALF|
									DMA_EV_DST_FULL|DMA_EV_SRC_HALF|DMA_EV_SRC_FULL)				// all available events
	}DmaEvFlags;	// flags for controlling the DMA channel events; Bit fields from the processor header file.


	typedef enum
	{
		DMA_TXFER_OK,			// the transfer was performed successfully
		DMA_TXFER_ADD_ERR,		// address error while performing the transfer
		DMA_TXFER_ABORT,		// the DMA transfer was aborted
		DMA_TXFER_BC_ERR,		// block complete not set after the DMA transfer performed
		DMA_TXFER_CC_ERR,		// cell complete not set after the DMA transfer performed
		DMA_TXFER_TMO			// DMA transfer timeout
	}DmaTxferRes;		// DMA transfer result

	typedef enum
	{
		DMA_WAIT_NOT,		// don't wait for the transfer to complete, return immediately
		DMA_WAIT_CELL,		// wait for the cell transfer to complete, than return
		DMA_WAIT_BLOCK		// wait for the block transfer to complete, than return
	}DmaWaitMode;		// DMA transfer wait mode

	typedef enum
	{
		DMA_CHKSUM_CRC,		// LFSR CRC
		DMA_CHKSUM_IP,		// IP Checksum
	}DmaChksumType;		// DMA SFM supported checksum types

	typedef enum
	{
		DMA_BITO_MSb,		// MSb first (not reflected)
		DMA_BITO_LSb,		// LSb first (reflected)
	}DmaBitOrder;		// DMA SFM supported bit ordering

	typedef enum
	{
		DMA_REORDER_NOT,	// no reordering, destination matches the source
		DMA_REORDER_ENDIAN,	// change endianess on word (32 bit) boundaries: LE<->BE
		DMA_REORDER_SWAP_HALF,	// swap half words (16 bit) within word (32 bit)		
		DMA_REORDER_SWAP_BYTE,	// swap bytes within half word (16 bit)				
	}DmaReorderMode;	// DMA SFM supported re-ordering modes


	/*********************************************************************
	 * Function:        void DmaChnOpen(DmaChannel chn, DmaChannelPri chPri, DmaOpenFlags oFlags)
	 *
	 * PreCondition:    chPri  - valid channel priority, 0-3
	 *
	 * Input:           chn    - channel to be configured in the DMA controller
	 *                  chPri  - the priority given to the channel, 0-3
	 *                  oFlags - orred flags specifying the open mode:
	 *                           DMA_OPEN_DEFAULT: DMA default operation mode
	 *                           DMA_OPEN_AUTO:	DMA channel is auto enabled
	 *                           DMA_OPEN_CHAIN_LOW: DMA channel is chained to lower channel
	 *                           DMA_OPEN_CHAIN_HI: DMA channel is chained to higher channel
	 *                           DMA_OPEN_DET_EN: events detection enabled while channel off
	 *                           DMA_OPEN_ENABLE: DMA channel is enabled when opened
	 *                           DMA_OPEN_MATCH:	DMA channel stops on match
	 *
	 *
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function opens and configures the selected DMA channel using the supplied user flags and priority.
	 *
	 * Note:            - This is a high level access function that doesn't give access to all the settings possible for a DMA channel.
	 *                  Use the low level functions to address special settings.
	 *                  - The channel is turned off, the pending interrupts are cleared, interrupts are disabled.
	 *                  After that the channel is configured.
	 *                  - After calling this function, the channel should be enabled using DmaChnEnable(chn) call
	 *                  if DMA_OPEN_ENABLE flag was not specified.
	 *                  - If the CRC is attached to the submitted channel, the CRC append mode will be turned off.
	 *                  This way, the transfer will occur correctly together with CRC calculation.
	 *                  - The start and abort Irqs will be disabled and the channel event enable flags are disabled.
	 *                  User has to call event channel functions to enable the event flags if needed.
	 *
	 * Example:         DmaChnOpen(DMA_CHANNEL2, DMA_CHN_PRI2, DMA_OPEN_AUTO|DMA_OPEN_MATCH|DMA_OPEN_ENABLE);
	 ********************************************************************/
	 void			DmaChnOpen(DmaChannel chn, DmaChannelPri chPri, DmaOpenFlags oFlags);

	/*********************************************************************
	 * Function:        void DmaChnEnable(DmaChannel chn)
	 *
	 * PreCondition:    None
	 *
	 * Input:			chn		- channel to be enabled
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function enables a previously configured DMA channel.
	 *
	 * Note:            DmaChnOpen()/DmaChnConfigure() should have been called before.
	 *
	 * Example:			DmaChnEnable(DMA_CHANNEL3);
	 ********************************************************************/
	 void			DmaChnEnable(DmaChannel chn);

	/*********************************************************************
	 * Function:        void DmaChnDisable(DmaChannel chn)
	 *
	 * PreCondition:    None
	 *
	 * Input:			chn		- selected channel in the DMA controller
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function disables a DMA channel. The channel operation stops.
	 *
	 * Note:            None.
	 *
	 * Example:			DmaChnDisable(DMA_CHANNEL3);
	 ********************************************************************/
	 void			DmaChnDisable(DmaChannel chn);

	/*********************************************************************
	 * Function:        void DmaChnSetTxfer(DmaChannel chn, const void* vSrcAdd, void* vDstAdd, int srcSize, int dstSize, int cellSize)
	 *
	 * PreCondition:    chn		- valid DMA channel
	 * 				- vSrcAdd, vDstAdd	- valid pointers
	 *                              - 0 < srcSize <= DmaGetMaxTxferSize()
	 *                              - 0 < dstSize <= DmaGetMaxTxferSize()
	 *                              - 0 < cellSize <= DmaGetMaxTxferSize()
	 *
	 * Input:			chn			- DMA channel number
	 * 								- vSrcAdd: source of the DMA transfer
	 * 								- vDstAdd: destination of the DMA transfer
	 * 								- srcSize: source buffer size, 1 to DmaGetMaxTxferSize() bytes, wrapped arround
	 * 								- dstSize: destination buffer size, 1 to DmaGetMaxTxferSize() bytes, wrapped around
	 * 								- cellSize: cell transfer size, 1 to DmaGetMaxTxferSize() bytes.
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function sets the transfer characteristics for a DMA channel transfer:
	 * 					the source and the destination addresses.
	 * 					the source and destination lengths
	 * 					and the number of bytes	transferred per event.
	 *
	 * Note:            The function clears the existing DMA channel event flags.
	 *                  The source to destination byte re-ordering is affected by DmaSfmConfigure(), DmaSfmTxferReorder().
	 *
	 * Example:			DmaChnSetTxfer(DMA_CHANNEL3, &U2RXREG, dstBuff, 1, 200, 1);
	 ********************************************************************/
	 void			DmaChnSetTxfer(DmaChannel chn, const void* vSrcAdd, void* vDstAdd, int srcSize, int dstSize, int cellSize);


	/*********************************************************************
	 * Function:        void DmaChnSetSrcAdd(DmaChannel chn, const void* vSrcAdd)
	 *
	 * PreCondition:    chn		- valid DMA channel
	 *
	 * Input:           chn		- DMA channel number
	 * 				- vSrcAdd: source (virtual) of the DMA transfer
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function is a helper to set directly the transfer source address.
	 *
	 * Note:            None.
	 *
	 * Example:         DmaChnSetSrcAdd(DMA_CHANNEL2, srcBuff+sizeof(srcBuff));
	 ********************************************************************/
	 void			DmaChnSetSrcAdd(DmaChannel chn, const void* vSrcAdd);

	/*********************************************************************
	 * Function:        void DmaChnSetDstAdd(DmaChannel chn, void* vDstAdd)
	 *
	 * PreCondition:    chn		- valid DMA channel
	 *
	 * Input:			chn			- DMA channel number
	 * 								- vDstAdd: destination (virtual) of the DMA transfer
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function is a helper to set directly the transfer destination address.
	 *
	 * Note:            None
	 *
	 * Example:         DmaChnSetDstAdd(DMA_CHANNEL2, dstBuff+sizeof(dstBuff));
	 ********************************************************************/
	 void			DmaChnSetDstAdd(DmaChannel chn, void* vDstAdd);

	/*********************************************************************
	 * Function:        void DmaChnSetMatchPattern(DmaChannel chn, int pattern)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 * 					pattern	-  the match pattern
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function sets the curent match pattern for the selected DMA channel.
	 *
	 * Note:            None.
	 *
	 * Example:			DmaChnSetMatchPattern(DMA_CHANNEL3, '\r');
	 ********************************************************************/
	 void			DmaChnSetMatchPattern(DmaChannel chn, int pattern);

	/*********************************************************************
	 * Function:        int DmaChnGetMatchPattern(DmaChannel chn)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 *
	 * Output:          The channel match pattern.
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function retrieves the curent match pattern for the selected DMA channel.
	 *
	 * Note:            None.
	 *
	 * Example:			int pattern=DmaChnGetMatchPattern(DMA_CHANNEL3);
	 ********************************************************************/
	 int			DmaChnGetMatchPattern(DmaChannel chn);

	/*********************************************************************
	 * Function:        DmaTxferRes DmaChnStartTxfer(DmaChannel chn, DmaWaitMode wMode, unsigned long retries)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 * 					wMode	- if DMA_WAIT_NOT, return immediately
	 * 							- if DMA_WAIT_CELL, return after the cell transfer complete
	 * 							- if DMA_WAIT_BLOCK, return after the whole transfer is done
	 * 					retries	- retry counter: if transfer not complete after so many retries, return with tmo.
	 * 								If 0, wait forever.
	 *
	 * Output:          DMA_TXFER_OK if not waiting for the transfer completion or if the transfer ended normally,
	 * 					an DmaTxferRes error code  otherwise
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function initiates (forces) a DMA transfer for the selected DMA channel.
	 * 					The DMA channel is enabled.
	 * 					If waiting for the transfer completion needed (user doesn't use an ISR to catch
	 * 					this event) the function will periodically query the DMA controller for the
	 * 					transfer completion status.
     * 					If DMA_WAIT_BLOCK is specified and multiple cell transfers are needed to complete
     * 					the block transfer than the function will re-force the transfer for each cell.
	 *
	 * Note:            This function can not ne used when the DMA channel is triggerred
     *                  by hardware interrupt requests.
     *                  This is because the transfers are software forced, theere is no
     *                  wait for the occurrence of the hardware trigger. 
	 *
	 * Example:         DmaChnStartTxfer(DMA_CHANNEL2, DMA_WAIT_BLOCK, 0);
	 ********************************************************************/
	 DmaTxferRes DmaChnStartTxfer(DmaChannel chn, DmaWaitMode wMode, unsigned long retries);

	/*********************************************************************
	 * Function:        void DmaChnForceTxfer(DmaChannel chn)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function forces a DMA transfer to occur for the selected DMA channel.
	 *
	 * Note:            None.
	 *
	 * Example:			DmaChnForceTxfer(DMA_CHANNEL3);
	 ********************************************************************/
	 void			DmaChnForceTxfer(DmaChannel chn);

	/*********************************************************************
	 * Function:        void DmaChnAbortTxfer(DmaChannel chn)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function aborts a current undergoing DMA transfer for the selected DMA channel.
	 *
	 * Note:            None.
	 *
	 * Example:			DmaChnAbortTxfer(DMA_CHANNEL3);
	 ********************************************************************/
	 void			DmaChnAbortTxfer(DmaChannel chn);

	// High level channel event and interrupt control functions

	/*********************************************************************
	 * Function:        void DmaChnSetEvEnableFlags(DmaChannel chn, DmaEvFlags eFlags)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 * 					eFlags	- event flags with the following significance:
	 * 								- DMA_EV_ERR: address error event
	 * 								- DMA_EV_ABORT: transfer abort event
	 * 								- DMA_EV_CELL_DONE: cell transfer complete event
	 * 								- DMA_EV_BLOCK_DONE: block transfer complete event
	 * 								- DMA_EV_DST_HALF: destination half event
	 * 								- DMA_EV_DST_FULL: destination full event
	 * 								- DMA_EV_SRC_HALF: source half event
	 * 								- DMA_EV_SRC_FULL: source full event
	 * 								- DMA_EV_ALL_EVNTS: all of the above flags
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function sets the event enable flags for the selected DMA channel.
	 * 					Multiple flags can be orr-ed together. Any flag that is set in the eFlags will be
	 * 					enabled for the selected channel, the other channel event flags won't be touched.
	 *
	 * Note:            None.
	 *
	 * Example:			DmaChnSetEvEnableFlags(DMA_CHANNEL3, DMA_EV_ERR|DMA_EV_ABORT|DMA_EV_BLOCK_DONE|DMA_EV_SRC_FULL);
	 ********************************************************************/
	 void			DmaChnSetEvEnableFlags(DmaChannel chn, DmaEvFlags eFlags);

	/*********************************************************************
	 * Function:        void DmaChnClrEvEnableFlags(DmaChannel chn, DmaEvFlags eFlags)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 * 					eFlags	- event flags with the following significance:
	 * 								- DMA_EV_ERR: address error event
	 * 								- DMA_EV_ABORT: transfer abort event
	 * 								- DMA_EV_CELL_DONE: cell transfer complete event
	 * 								- DMA_EV_BLOCK_DONE: block transfer complete event
	 * 								- DMA_EV_DST_HALF: destination half event
	 * 								- DMA_EV_DST_FULL: destination full event
	 * 								- DMA_EV_SRC_HALF: source half event
	 * 								- DMA_EV_SRC_FULL: source full event
	 * 								- DMA_EV_ALL_EVNTS: all of the above flags
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function clears the event enable flags for the selected DMA channel.
	 * 					Multiple flags can be orr-ed together. Any flag that is set in the eFlags will be
	 * 					disabled for the selected channel, the other channel event flags won't be touched.
	 *
	 * Note:            None.
	 *
	 * Example:			DmaChnClrEvEnableFlags(DMA_CHANNEL3, DMA_EV_ERR|DMA_EV_ABORT|DMA_EV_BLOCK_DONE|DMA_EV_SRC_FULL);
	 ********************************************************************/
	 void			DmaChnClrEvEnableFlags(DmaChannel chn, DmaEvFlags eFlags);

	/*********************************************************************
	 * Function:        void DmaChnWriteEvEnableFlags(DmaChannel chn, DmaEvFlags eFlags)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 * 					eFlags	- event flags with the following significance:
	 * 								- DMA_EV_ERR: address error event
	 * 								- DMA_EV_ABORT: transfer abort event
	 * 								- DMA_EV_CELL_DONE: cell transfer complete event
	 * 								- DMA_EV_BLOCK_DONE: block transfer complete event
	 * 								- DMA_EV_DST_HALF: destination half event
	 * 								- DMA_EV_DST_FULL: destination full event
	 * 								- DMA_EV_SRC_HALF: source half event
	 * 								- DMA_EV_SRC_FULL: source full event
	 * 								- DMA_EV_ALL_EVNTS: all of the above flags
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function sets the event enable flags for the selected DMA channel.
	 * 					The channel event flags are forced to the eFlags value.
	 *
	 * Note:            None.
	 *
	 * Example:			DmaChnWriteEvEnableFlags(DMA_CHANNEL3, DMA_EV_ALL_EVNTS);
	 ********************************************************************/
	 void			DmaChnWriteEvEnableFlags(DmaChannel chn, DmaEvFlags eFlags);

	/*********************************************************************
	 * Function:        DmaEvFlags DmaChnGetEvEnableFlags(DmaChannel chn)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 *
	 * Output:          - event flags with the following significance:
	 * 						- DMA_EV_ERR: address error event
	 * 						- DMA_EV_ABORT: transfer abort event
	 * 						- DMA_EV_CELL_DONE: cell transfer complete event
	 * 						- DMA_EV_BLOCK_DONE: block transfer complete event
	 * 						- DMA_EV_DST_HALF: destination half event
	 * 						- DMA_EV_DST_FULL: destination full event
	 * 						- DMA_EV_SRC_HALF: source half event
	 * 						- DMA_EV_SRC_FULL: source full event
	 *						- DMA_EV_ALL_EVNTS: all of the above flags
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function returns the event enabled flags for the selected DMA channel.
	 *
	 * Note:            None.
	 *
	 * Example:			DmaEvFlags enabledFlags=DmaChnGetEvEnableFlags(DMA_CHANNEL3);
	 ********************************************************************/
	 DmaEvFlags	DmaChnGetEvEnableFlags(DmaChannel chn);

	/*********************************************************************
	 * Function:        void DmaChnClrEvFlags(DmaChannel chn, DmaEvFlags eFlags)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 * 					eFlags	- event flags with the following significance:
	 * 								- DMA_EV_ERR: address error event
	 * 								- DMA_EV_ABORT: transfer abort event
	 * 								- DMA_EV_CELL_DONE: cell transfer complete event
	 * 								- DMA_EV_BLOCK_DONE: block transfer complete event
	 * 								- DMA_EV_DST_HALF: destination half event
	 * 								- DMA_EV_DST_FULL: destination full event
	 * 								- DMA_EV_SRC_HALF: source half event
	 * 								- DMA_EV_SRC_FULL: source full event
	 * 								- DMA_EV_ALL_EVNTS: all of the above flags
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function clears the event flags for the selected DMA channel.
	 * 					Multiple flags can be orr-ed together. Any flag that is set in the eFlags will be
	 * 					cleared for the selected channel, the other channel event flags won't be touched.
	 *
	 * Note:            None.
	 *
	 * Example:			DmaChnClrEvFlags(DMA_CHANNEL3, DMA_EV_ALL_EVNTS);
	 ********************************************************************/
	 void			DmaChnClrEvFlags(DmaChannel chn, DmaEvFlags eFlags);

	/*********************************************************************
	 * Function:        DmaEvFlags DmaChnGetEvFlags(DmaChannel chn)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 *
	 * Output:          event flags with the following significance:
	 * 						- DMA_EV_ERR: address error event
	 * 						- DMA_EV_ABORT: transfer abort event
	 * 						- DMA_EV_CELL_DONE: cell transfer complete event
	 * 						- DMA_EV_BLOCK_DONE: block transfer complete event
	 * 						- DMA_EV_DST_HALF: destination half event
	 * 						- DMA_EV_DST_FULL: destination full event
	 * 						- DMA_EV_SRC_HALF: source half event
	 * 						- DMA_EV_SRC_FULL: source full event
	 * 						- DMA_EV_ALL_EVNTS: all of the above flags
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function returns the event flags for the selected DMA channel.
	 *
	 * Note:            None.
	 *
	 * Example:			DmaEvFlags intSetFlags=DmaChnGetEvFlags(DMA_CHANNEL3);
	 ********************************************************************/
	 DmaEvFlags	DmaChnGetEvFlags(DmaChannel chn);


	// high level helpers for fast strcpy/memcpy transfers

	/*********************************************************************
	 * Function:        DmaTxferRes DmaChnMemcpy(void* s1, const void* s2, int n, DmaChannel chn, DmaChannelPri chPri)
	 *
	 * PreCondition:    chn		- a valid DMA channel
	 * 					s1, s2	- valid memory pointers
	 * 					n>0, n<=DmaGetMaxTxferSize()
	 *
	 * Input:			s1		- destination pointer
	 * 					s2		- source pointer
	 * 					n		- number of bytes to transfer
	 * 					chn		- the DMA channel to perform the transfer
	 * 					chPri	- the desired channel priority
	 *
	 * Output:          DMA_TXFER_OK if the transfer ended normally,
	 * 					an DmaTxferRes error code  otherwise
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function configures a DMA channel for a fast memory transfer.
	 * 			Then it copies one block of memory from source to destination.
	 *
	 *
	 * Note:            - If the SFM is attached to the submitted channel, the SFM append mode will be turned off.
	 *                    This way, the transfer will occur correctly together with checksum calculation.
	 *                  - The start and abort Irqs will be disabled and the channel event enable flags are disabled.
	 *                  - Multiple channels could be opened to perform fast memory transfers, if necessary.
	 *                  - The function clears the suspend state and resumes the operation of the DMA controller.
	 *                  - The source to destination byte re-ordering is affected by DmaSfmConfigure(), DmaSfmTxferReorder().
	 *
 	 * Example:		res=DmaChnMemcpy(pDst, pSrc, buffSz, DMA_CHANNEL0, DMA_CHN_PRI3);
 	 ********************************************************************/
	 DmaTxferRes	DmaChnMemcpy(void* s1, const void* s2, int n, DmaChannel chn, DmaChannelPri chPri);

	/*********************************************************************
	 * Function:        DmaTxferRes DmaChnStrcpy(char* s1, const char* s2, DmaChannel chn, DmaChannelPri chPri)
	 *
	 * PreCondition:    chn		- a valid DMA channel
	 * 					s1, s2	- valid memory pointers
	 *
	 * Input:			s1		- destination pointer
	 * 					s2		- source pointer
	 * 					chn		- the DMA channel to perform the transfer
	 * 					chPri	- the desired channel priority
	 *
	 * Output:          DMA_TXFER_OK if the transfer ended normally,
	 * 					an DmaTxferRes error code  otherwise
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function configures a DMA channel for a fast memory transfer.
	 * 			Then it copies one zero terminated string from source to destination.
	 *
	 *
	 * Note:            - If the SFM is attached to the submitted channel, the SFM append mode will be turned off.
	 *                    This way, the transfer will occur correctly together with checksum calculation.
	 *                  - The start and abort Irqs will be disabled and the channel event enable flags are disabled.
	 *                  - Multiple channels could be opened to perform fast memory transfers, if necessary.
	 *                  - The function clears the suspend state and resumes the operation of the DMA controller.
	 *                  - The source to destination byte re-ordering is affected by DmaSfmConfigure(), DmaSfmTxferReorder().
	 *
	 *
 	 * Example:		res=DmaChnStrcpy(str1, str2, DMA_CHANNEL1, DMA_CHN_PRI3);
	 *********************************************************************/
	 DmaTxferRes	DmaChnStrcpy(char* s1, const char* s2, DmaChannel chn, DmaChannelPri chPri);

	/*********************************************************************
	 * Function:        DmaTxferRes DmaChnStrncpy(char* s1, const char* s2, int n, DmaChannel chn, DmaChannelPri chPri)
	 *
	 * PreCondition:    chn		- a valid DMA channel
	 * 				- s1, s2	- valid memory pointers
	 *                              - 0 < n <= DmaGetMaxTxferSize()
	 *
	 * Input:			s1		- destination pointer
	 * 					s2		- source pointer
	 * 					n	- max number of bytes to transfer
	 * 					chn		- the DMA channel to perform the transfer
	 * 					chPri	- the desired channel priority
	 *
	 * Output:          DMA_TXFER_OK if the transfer ended normally,
	 * 					an DmaTxferRes error code  otherwise
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function configures a DMA channel for a fast memory transfer.
	 * 			Then it copies one zero terminated string from source to destination.
	 * 			It copies no more than n characters from s2.
	 *
	 *
	 * Note:            - If the SFM is attached to the submitted channel, the SFM append mode will be turned off.
	 *                    This way, the transfer will occur correctly together with checksum calculation.
	 *                  - The start and abort Irqs will be disabled and the channel event enable flags are disabled.
	 *                  - Multiple channels could be opened to perform fast memory transfers, if necessary.
	 *                  - The function clears the suspend state and resumes the operation of the DMA controller.
	 *                  - The source to destination byte re-ordering is affected by DmaSfmConfigure(), DmaSfmTxferReorder().
	 *
	 *
 	 * Example:		res=DmaChnStrncpy(str1, str2, MAX_STR_LEN, DMA_CHANNEL1, DMA_CHN_PRI3);
	 ********************************************************************/
	 DmaTxferRes DmaChnStrncpy(char* s1, const char* s2, int n, DmaChannel chn, DmaChannelPri chPri);

	/*********************************************************************
	 * Function:        DmaTxferRes DmaChnMemCrc(void* d, const void* s, int n, DmaChannel chn, DmaChannelPri chPri)
	 *
	 * PreCondition:    chn    - a valid DMA channel
	 *                  d, s   - valid memory pointer
	 *                  n>0, n<=DmaGetMaxTxferSize()
	 *
	 * Input:           d     - address where to deposit the result
	 *                  s     - source buffer pointer
	 *                  n     - number of bytes in the pointer
	 *                  chn   - the DMA channel to use
	 *                  chPri - the desired channel priority
	 * 
	 * Output:          DMA_TXFER_OK if the transfer ended normally,
	 *                  an DmaTxferRes error code  otherwise
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function is a helper that calculates the CRC of a memory block.
	 *                  The function configures the DMA channel for a fast memory transfer and calculates the CRC.
	 *
	 *
	 * Note:            - The CRC generator must have been previously configured using DmaSfmCrcConfigure()
	 *                  - No transfer is done, just the CRC is calculated.
	 *                  - The start and abort Irqs will be disabled and the channel event enable flags are disabled.
	 *                  - Append mode is enabled and the data transfer re-ordering is disabled (illegal combination, see DmaSfmTxferReorder()).
	 *                  - The checksum type is switched to CRC.
	 *                  - The way the data is fed into the checksum calculation block is affected by DmaSfmConfigure().
	 *                  
	 * Example:          int myCrc; DmaChnMemCrc(&myCrc, srcBuff, sizeof(srcBuff), DMA_CHANNEL2, DMA_CHN_PRI3);
	 ********************************************************************/
	 DmaTxferRes	DmaChnMemCrc(void* d, const void* s, int n, DmaChannel chn, DmaChannelPri chPri);

	/*********************************************************************
	 * Function:        DmaTxferRes DmaChnMemChecksum(void* d, const void* s, int n, DmaChannel chn, DmaChannelPri chPri)
	 *
	 * PreCondition:    chn    - a valid DMA channel
	 *                  d, s   - valid memory pointer
	 *                  n>0, n<=DmaGetMaxTxferSize()
	 *
	 * Input:           d     - address where to deposit the result
	 *                  s     - source buffer pointer
	 *                  n     - number of bytes in the pointer
	 *                  chn   - the DMA channel to use
	 *                  chPri - the desired channel priority
	 * 
	 * Output:          DMA_TXFER_OK if the transfer ended normally,
	 *                  an DmaTxferRes error code  otherwise
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function is a helper that calculates the IP checksum of a memory block.
	 *                  The function configures the DMA channel for a fast memory transfer and calculates the IP checksum.
	 *
	 *
	 * Note:            - The checksum generator must have been previously seeded using DmaSfmSetSeed()
	 *                  - No transfer is done, just the checksum is calculated.
	 *                  - The start and abort Irqs will be disabled and the channel event enable flags are disabled.
	 *                  - Append mode is enabled and the data transfer re-ordering is disabled (illegal combination, see DmaSfmTxferReorder()).
	 *                  - The checksum type is switched to IP checksum.
	 *                  - The way the data is fed into the checksum calculation block is affected by DmaSfmConfigure().
	 *                  
	 * Example:          int myChecksum; DmaChnMemChecksum(&myChecksum, srcBuff, sizeof(srcBuff), DMA_CHANNEL1, DMA_CHN_PRI3);
	 ********************************************************************/
	 DmaTxferRes	DmaChnMemChecksum(void* d, const void* s, int n, DmaChannel chn, DmaChannelPri chPri);

	// High level Special Function Module (SFM) functions

	/*********************************************************************
	 * Function:        void DmaSfmConfigure(DmaChksumType cType, DmaBitOrder bitO, DmaReorderMode rMode)
	 *
	 * PreCondition:    cType, bitO, rMode - valid values
	 *
	 * Input:           cType - checksum type to be calculated: CRC or IP Checksum
	 *                  bitO  - the bit order to be used MSb or LSb first
	 *                  rMode - the reordering mode of the bytes when calculating the checksum 
	 *
	 * Output:          None
	 *
	 * Side Effects:    Whenever the Transfer re-ordering is enabled the rMode setting will influence the destination data layout
	 *
	 * Overview:        The function configures the SFM module by setting the parameters that define the behavior:
	 *                      - the type of the checksum to be calculated (either CRC or IP checksum are supported)
	 *                      - the bit ordering (how a specific byte is used in the checksum calculation: MSb or LSb first) 
	 *                      - the data re-ordering (how bytes are re-ordered before calculating the checksum).
	 *                      All these values affect the way the checksum is calculated.
	 *
	 * Note:            None
	 *
	 * Example:         DmaSfmConfigure(DMA_CHKSUM_CRC, DMA_BITO_LSb, DMA_REORDER_ENDIAN);
	 ********************************************************************/
	extern __inline__ void __attribute__((always_inline)) DmaSfmConfigure(DmaChksumType cType, DmaBitOrder bitO, DmaReorderMode rMode)
	{
		DCRCCONCLR=_DCRCCON_CRCTYP_MASK|_DCRCCON_BITO_MASK|_DCRCCON_BYTO_MASK;
		DCRCCONSET=(cType<<_DCRCCON_CRCTYP_POSITION)|(bitO<<_DCRCCON_BITO_POSITION)|(rMode<<_DCRCCON_BYTO_POSITION);
	}

	/*********************************************************************
	 * Function:        void DmaSfmTxferReorder(int enable)
	 *
	 * PreCondition:    None
	 *
	 * Input:           enable - boolean to enable/disable the re-ordering of the data transfer
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function configures the data transfer re-ordering of the SFM module.
	 *                  If the re-ordering is enabled, the data is read from the source, re-ordered accordingly and then written to the destination.
	 *                  Otherwise the data is written to the destination un-modified.
	 *                  The re-ordering is the one specified by the DmaReorderMode parameter in the DmaSfmConfigure() call.
	 *                  
	 *
	 * Note:            - The data transfer re-ordering should be used only for normal (background mode) data transfers.
	 *                  - In append mode the data transfer re-ordering should not be enabled (undefined behavior)!
	 *                  - Whenever the data re-ordering is enabled, the transfer should be aligned at both ends (source and destination).
	 *                    Un-aligned transfers are not supported (undefined behavior)!
	 *
	 * Example:         DmaSfmTxferReorder();
	 ********************************************************************/
	extern __inline__ void __attribute__((always_inline)) DmaSfmTxferReorder(int enable)
	{
		DCRCCONCLR=_DCRCCON_WBO_MASK;
		DCRCCONSET=(enable<<_DCRCCON_WBO_POSITION);
	}


	 /*********************************************************************
	 * Function:        void DmaSfmCrcConfigure(unsigned int polynomial, int pLen, unsigned int seed)
	 *
	 * PreCondition:    pLen   - valid polynomial length within 1-32
	 *
	 * Input:           polynomial	- the layout of the CRC generator
	 *                  pLen        - the length of the CRC generator polynomial
	 *                  seed        - the initial seed of the CRC generator
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function configures the SFM CRC module by setting the parameters that define the generator polynomial:
	 *                  - the length of the CRC generator polynomial, pLen;
	 *                  - the function sets the layout of the shift stages that take place in the CRC generation.
	 *                    Setting a bit to 1 enables the XOR input from the MSb (pLen bit) to the selected stage in the shift register.
	 *                    If bit is cleared, the selected shift stage gets data directly from the previous stage in the shift register.
	 *                    Note that in a proper CRC polynomial, both the most significant bit (MSb) and least significant bit(LSb)
	 *                    are always a '1'. Considering the generator polynomial: X^16+X^15+X^2+1, the value to be written as
	 *                    feedback should be 0x8005, or 0x8004, but not 0x018005;
	 *                  - the function sets the seed of the CRC generator. This is the initial data present in the
	 *                   CRC shift register before the CRC calculation begins. A good initial value is usually 0xffffffff.
	 *
	 * Note:            - Bit 0 of the generator polynomial is always XOR'ed.
	 *                  - When the append mode is set, the attached DMA channel has to have destination size <=4.
	 *                    Upon the transfer completion the calculated CRC is stored at the destination address.
	 *                  - When append mode is cleared, the DMA transfer occurs normally, and the CRC value is available using
	 *                    the CrcResult() function.
	 *                  - The CRC module should be configured before enabled.
	 *                  - These settings are relevant only when the SFM is configured for the CRC type of checksum.
	 *                  - The checksum register is the same for CRC or IP checksum mode. Therefore, this function changes also the seed for the IP checksum.
	 *                  - The way the data is fed into the checksum calculation block and the type of the checksum performed is affected by DmaSfmConfigure().
	 *
	 * Example:         DmaSfmCrcConfigure(0x04c11db7, 32, 0xffffffff);
	 ********************************************************************/
	extern __inline__ void __attribute__((always_inline)) DmaSfmCrcConfigure(unsigned int polynomial, int pLen, unsigned int seed)
	{
		DCRCCONCLR=_DCRCCON_PLEN_MASK;
		DCRCCONSET=(pLen-1)<<_DCRCCON_PLEN_POSITION;
		DCRCDATA=seed;
		DCRCXOR=polynomial;
	}
	
	#define DmaCrcConfigure	DmaSfmCrcConfigure	// PIC32_3xx backward compatibility name


	/*********************************************************************
	 * Function:        void DmaSfmAttachChannel(DmaChannel chn, int appendMode)
	 *
	 * PreCondition:    chn	   - valid DMA channel
	 *
	 * Input:           chn         - the DMA channel to be attached to the checksum module.
	 *                  appendMode	- if TRUE the data passed to the checksum generator is not transferred to destination
	 *                                but it's written to the destination address when the block transfer is complete.
	 *                              - if FALSE the data is transferred normally while the checksum is calculated.
	 *                                The checksum will be available using the DmaSfmChecksum function.
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function attaches the SFM checksum module to a DMA channel and enables the checksum generator.
	 *                  From now on, all the DMA traffic is directed to the SFM checksum generator. Once the DMA block transfer
	 *                  is complete, the checksum result is available in the checksum data register.
	 *                  If append mode is enabled, no data transfer takes place but the checksum result will be deposited at the DMA destination address.

	 *
	 * Note:            If append mode is enabled the data transfer re-ordering is disabled (illegal combination, see DmaSfmTxferReorder()).
	 * 
	 * Example:         DmaSfmAttachChannel(DMA_CHANNEL0, TRUE);
	 ********************************************************************/
	void			DmaSfmAttachChannel(DmaChannel chn, int appendMode);
	#define			CrcAttachChannel	DmaSfmAttachChannel		// PIC32_3xx backward compatibility name	

	/*********************************************************************
	 * Function:        unsigned int DmaSfmChecksum(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:			None
	 *
	 * Output:          the current value of the checksum generator.
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function returns the calculated checksum value.
	 *
	 * Note:            - The function returns the valid checksum result. The masking out the unused MSbits in the checksum register is done by the hardware.
	 *                  - The way the data is fed into the checksum calculation block and the type of the checksum performed is affected by DmaSfmConfigure().
	 *
	 * Example:         unsigned int myChk=DmaSfmChecksum();
	 ********************************************************************/
	extern __inline__ int __attribute__((always_inline)) DmaSfmChecksum(void)
	{
		return DCRCDATA;
	}
	#define		CrcResult	DmaSfmChecksum		// PIC32_3xx backward compatibility name
	#define		DmaCrcGetValue	DmaSfmChecksum		// PIC32_3xx backward compatibility name 


	/*********************************************************************
	 * Function:        void DmaSfmSetSeed(unsigned int seed)
	 *
	 * PreCondition:    None
	 *
	 * Input:           seed	- the initial seed of the checksum generator
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function sets the seed of the checksum generator. This is the initial data present in the
	 *                  CRC shift register or the IP checksum calculator before the actual transfer/calculation begins.
	 *
	 * Note:            When the SFM is configured for IP checksum mode, only the least significant 16 bits are relevant.
	 *
	 * Example:         DmaSfmSetSeed(0xffffffff);
	 ********************************************************************/
	extern __inline__ void __attribute__((always_inline)) DmaSfmSetSeed(unsigned int seed)
	{
		DCRCDATA=seed;
	}
	#define		DmaCrcSetSeed	DmaSfmSetSeed		// PIC32_3xx backward compatibility name

	 
/*********************  end of high level functions ****************************************/

	// low level definitions for the API functions


	typedef struct
	{
		union
		{
			struct
			{
				unsigned int chn:	3;		// last active DMA channel
				unsigned int rdOp:	1;		// last DMA operation, read if 1, write if 0
			};
			unsigned int	w;						// word access
		}lastAccess;
		void*	lastAddress;		// most recent DMA address
	}DmaStatus;			// DMA controller status

	typedef enum
	{
		DMA_GFLG_SUSPEND =	_DMACON_SUSPEND_MASK,	// suspend DMA controller operation
		DMA_GFLG_FRZ =		_DMACON_FRZ_MASK,		// DMA controller frozen/active in debug mode
		DMA_GFLG_ON =		_DMACON_ON_MASK,		// DMA module enabled/desabled
		//
		DMA_GFLG_ALL_FLAGS=	DMA_GFLG_SUSPEND|DMA_GFLG_FRZ|DMA_GFLG_ON		// all flags
	}DmaGlblFlags;	// flags for controlling global DMA controller behavior. From processor header file.




	typedef enum
	{
		DMA_EV_ABORT_IRQ_EN =		_DCH0ECON_AIRQEN_MASK,
		DMA_EV_START_IRQ_EN =		_DCH0ECON_SIRQEN_MASK,
        // use DMA_EV_START_IRQ() and DMA_EV_ABORT_IRQ() below for selecting
        // the start and abort IRQ signals
		DMA_EV_MATCH_EN =			_DCH0ECON_PATEN_MASK,


        // compiler use only field
        _DMA_EV_MAX_MASK =     _DCH0ECON_CHAIRQ_MASK,
	}DmaEvCtrlFlags;	// DMA channel event control fields accessibile as flags
	// also part of DmaEvCtrlFlags:
	#define	DMA_EV_START_IRQ(irq)	(DMA_EV_START_IRQ_EN | ((irq)<<_DCH0ECON_CHSIRQ_POSITION))	// NOTE: irq has to be a symbol from the processor header file
	#define	DMA_EV_ABORT_IRQ(irq)	(DMA_EV_ABORT_IRQ_EN | ((irq)<<_DCH0ECON_CHAIRQ_POSITION))	// NOTE: irq has to be a symbol from the processor header file

	// DMA channel event control as a structure:
	#define	DmaEvCtrl	__DCH0ECONbits_t




	typedef enum
	{
		DMA_CTL_AUTO_EN =		_DCH0CON_CHAEN_MASK,
		DMA_CTL_CHAIN_EN =		_DCH0CON_CHCHN_MASK,
		DMA_CTL_DET_EN =		_DCH0CON_CHAED_MASK,
		DMA_CTL_CHN_EN =		_DCH0CON_CHEN_MASK,
		DMA_CTL_CHAIN_DIR =		_DCH0CON_CHCHNS_MASK,
        // use the DMA_CTL_PRI() below for selecting the DMA
        // channel priority
	}DmaChnCtrlFlags;	// controlling the DMA channel with flags
	// also part of DmaChnCtrlFlags:
	#define	DMA_CTL_PRI(pri)	((pri)&_DCH0CON_CHPRI_MASK) // DMA Control channel priority

	// DMA channel control as a structure:
	#define	DmaChnCtrl  	__DCH0CONbits_t

	typedef struct
	{
		void*	vSrcAdd;		// source of the DMA transfer, virtual
		void*	vDstAdd;		// destination of the DMA transfer, virtual
		int	srcSize;		// source buffer size, 1 to DmaGetMaxTxferSize() bytes. Wrapped around.
		int	dstSize;		// destination buffer size, 1 to DmaGetMaxTxferSize() bytes. Wrapped around.
		int	cellSize;		// no of bytes txferred per event, 1 to DmaGetMaxTxferSize().
	}DmaTxferCtrl;		// transfer setting: the transfer source, destination addresses and size, cell size


	/********************** low level DMA channel functions *******************************/



	// Global DMA controller functions

	/*********************************************************************
	 * Function:        void DmaEnable(int enable)
	 *
	 * PreCondition:    None
	 *
	 * Input:           enable - boolean to enable/disable the DMA controller
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:       The function enables/disables the DMA controller.
	 *
	 * Note:           None.
	 *
	 * Example:        DmaEnable(1);
	 ********************************************************************/
	extern __inline__ void __attribute__((always_inline)) DmaEnable(int enable)
	{
		if(enable)
		{
			DMACONSET=_DMACON_ON_MASK;
		}
		else
		{
			DMACONCLR=_DMACON_ON_MASK;
			while(DMACONbits.ON);		// wait to take effect
		}
	}

	/*********************************************************************
	 * Function:        void DmaReset(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:		None
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function resets the DMA controller.
	 *
	 * Note:            None.
	 *
	 * Example:        DmaReset();
	 ********************************************************************/
	#define            DmaReset()	DmaEnable(0)


	/*********************************************************************
	 * Function:        int DmaSuspend(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:		None
	 *
	 * Output:          true if the DMA was previously suspended, false otherwise
	 *
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function suspends the DMA controller.
	 *
	 * Note:            After the execution of this function the DMA operation is supposed to be suspended.
	 *                  I.e. the function has to wait for the suspension to take place!
	 *
	 * Example:         int susp=DmaSuspend();
	 ********************************************************************/
        extern __inline__ int __attribute__((always_inline)) DmaSuspend(void)
	{
		int suspSt;
		if(!(suspSt=DMACONbits.SUSPEND))
		{
			DMACONSET=_DMACON_SUSPEND_MASK;		// suspend
			while((DMACONbits.DMABUSY));	// wait to be actually suspended
		}
		return suspSt;
	}



	/*********************************************************************
	 * Function:        void DmaResume(int susp)
	 *
	 * PreCondition:    None
	 *
	 * Input:		the desired DMA suspended state.
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function restores the DMA controller activity to the old suspended mode.
	 *
	 * Note:            None.
	 *
	 * Example:			int isSusp=DmaSuspend(); {....}; DmaResume(isSusp);
	 ********************************************************************/
        extern __inline__ void __attribute__((always_inline)) DmaResume(int susp)
	{
		if(susp)
		{
			DmaSuspend();
		}
		else
		{
			DMACONCLR=_DMACON_SUSPEND_MASK;		// resume DMA activity
		}
	}

	/*********************************************************************
	 * Function:        void DmaGetStatus(DmaStatus* pStat)
	 *
	 * PreCondition:    pStat	- valid pointer
	 *
	 * Input:			pStat	- pointer to a DmaStatus structure to store the current DMA controller
	 * 							status, carrying the following info:
	 * 								- chn:	the last active DMA channel
	 * 								- rdOp: the last DMA operation, read/write
	 * 								- lastAddress: the most recent DMA address
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function updates the info for the current DMA controller status.
	 * 					It updates the last DMA: operation, channel used and address.
	 *
	 * Note:            None.
	 *
	 * Example:			DmaStatus stat; DmaGetStatus(&stat);
	 ********************************************************************/
	 void			DmaGetStatus(DmaStatus* pStat);

	/*********************************************************************
	 * Function:        void DmaSetGlobalFlags(DmaGlblFlags gFlags)
	 *
	 * PreCondition:    None
	 *
	 * Input:           gFlags - flags to be set, having the following fields:
	 * 			- DMA_GFLG_SUSPEND: DMA controller operation suspend
	 * 			- DMA_GFLG_FRZ: DMA controller frozen/active in debug mode
	 * 			- DMA_GFLG_ON: DMA controller enabled/desabled
	 * 			- DMA_GFLG_ALL_FLAGS: all flags
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function affects the global behavior of the DMA controller.
	 *                  It sets the specified flags. Any flag that is set in the gFlags will be
	 *                  enabled, the other flags won't be touched.
	 *
	 * Note:            None.
	 *
	 * Example:         DmaSetGlobalFlags(DMA_GFLG_ON);
	 ********************************************************************/
        extern __inline__ void __attribute__((always_inline)) DmaSetGlobalFlags(DmaGlblFlags gFlags)
	{
		DMACONSET=gFlags;
	}

	/*********************************************************************
	 * Function:        void DmaClrGlobalFlags(DmaGlblFlags gFlags)
	 *
	 * PreCondition:    None
	 *
	 * Input:           gFlags - flags to be cleared, having the following fields:
	 *                               - DMA_GFLG_SUSPEND: DMA controller operation suspend
	 *                               - DMA_GFLG_FRZ: DMA controller frozen/active in debug mode
	 *                               - DMA_GFLG_ON: DMA controller enabled/desabled
	 *                               - DMA_GFLG_ALL_FLAGS: all flags
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function affects the global behavior of the DMA controller.
	 *                  It clears the specified flags. Any flag that is set in the gFlags will be
	 *                  cleared, the other flags won't be touched.
	 *
	 * Note:            None.
	 *
	 * Example:         DmaClrGlobalFlags(DMA_GFLG_SUSPEND);
	 ********************************************************************/
        extern __inline__ void __attribute__((always_inline)) DmaClrGlobalFlags(DmaGlblFlags gFlags)
	{
		DMACONCLR=gFlags;
	}


	/*********************************************************************
	 * Function:        void DmaWriteGlobalFlags(DmaGlblFlags gFlags)
	 *
	 * PreCondition:    None
	 *
	 * Input:           gFlags - flags to be set, having the following fields:
	 *                                 - DMA_GFLG_SUSPEND: DMA controller operation suspend
	 *                                 - DMA_GFLG_FRZ: DMA controller frozen/active in debug mode
	 *                                 - DMA_GFLG_ON: DMA controller enabled/desabled
	 *                                 - DMA_GFLG_ALL_FLAGS: all flags
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function affects the global behavior of the DMA controller.
	 *                  It forces the flags to have the specified gFlags value.
	 *
	 * Note:            None.
	 *
	 * Example:         DmaWriteGlobalFlags(DMA_GFLG_ALL_FLAGS);
	 ********************************************************************/
        extern __inline__ void __attribute__((always_inline)) DmaWriteGlobalFlags(DmaGlblFlags gFlags)
	{
		DMACON=gFlags;
	}

	/*********************************************************************
	 * Function:        DmaGlblFlags DmaGetGlobalFlags(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          The current DMA controller flags settings.
	 *                              - DMA_GFLG_SUSPEND: DMA controller operation suspend
	 *                              - DMA_GFLG_FRZ: DMA controller frozen/active in debug mode
	 *                              - DMA_GFLG_ON: DMA controller enabled/desabled
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function returns the global flags of the DMA controller.
	 *
	 * Note:            None.
	 *
	 * Example:         DmaGlblFlags dmaFlags=DmaGetGlobalFlags();
	 ********************************************************************/
        extern __inline__ DmaGlblFlags __attribute__((always_inline)) DmaGetGlobalFlags(void)
	{
		return (DmaGlblFlags)DMACON;
	}


	/*********************************************************************
	 * Function:        int DmaGetMaxTxferSize(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          The maximum transfer capacity for a DMA channel, in bytes.
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function returns the maximum number of bytes that can be transferred by a DMA channel.
	 *
	 * Note:            Revision dependant.
	 *
	 * Example:         int dmaMaxSz=DmaGetMaxTxferSize();
	 ********************************************************************/
	extern __inline__ int __attribute__((always_inline)) DmaGetMaxTxferSize(void)
	{
		return 65536;
	}

	// Direct Channel control functions

	typedef enum
	{
		DMA_CONFIG_DEFAULT = 0,                             // DMA default operation
		DMA_CONFIG_AUTO	= _DCH0CON_CHAEN_MASK,              // DMA channel is auto enabled
		DMA_CONFIG_CHAIN_LOW  = (_DCH0CON_CHCHN_MASK|_DCH0CON_CHCHNS_MASK),	// DMA channel is chained to lower channel
		DMA_CONFIG_CHAIN_HI  = (_DCH0CON_CHCHN_MASK),		// DMA channel is chained to higher channel
		DMA_CONFIG_DET_EN = _DCH0CON_CHAED_MASK,			// events detection enabled while channel off
		DMA_CONFIG_ENABLE = _DCH0CON_CHEN_MASK,	            // DMA channel is enabled after open
		DMA_CONFIG_MATCH	= 0x80000000,                   // DMA channel stops on match
	}DmaConfigFlags;	// flags for the channel configuration



	/*********************************************************************
	 * Function:        void DmaChnConfigure(DmaChannel chn, DmaChannelPri chPri, DmaConfigFlags cFlags)
	 *
	 * PreCondition:    chPri  - valid channel priority, 0-3
	 *
	 * Input:           chn    - channel to be configured in the DMA controller
	 *                  chPri  - the priority given to the channel, 0-3
	 *                  cFlags - orred flags specifying the configuration:
	 *                           DMA_CONFIG_DEFAULT: DMA default operation mode
	 *                           DMA_CONFIG_AUTO:	DMA channel is auto enabled
	 *                           DMA_CONFIG_CHAIN_LOW: DMA channel is chained to lower channel
	 *                           DMA_CONFIG_CHAIN_HI: DMA channel is chained to higher channel
	 *                           DMA_CONFIG_DET_EN: events detection enabled while channel off
	 *                           DMA_CONFIG_ENABLE: DMA channel is enabled when opened
	 *                           DMA_CONFIG_MATCH:	DMA channel stops on match
	 *
	 *
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function configures the selected DMA channel using the supplied user flags and priority.
	 *
	 * Note:            - The channel is NOT turned off. It should be turned off before calling this function.
	 *                  The channel is just configured.
	 *                  - After calling this function, the channel should be enabled using DmaChnEnable(chn) call
	 *                  if DMA_CONFIG_ENABLE flag was not specified.
	 *                  - The function does not touch the interrupt flags, interrupt enables, etc.
	 *                  The interrupt flags should have been previously cleared and interrupts disabled before calling this function.
	 *                  - The start and abort Irqs, the channel event enable flags are not touched/cleared by this function.
	 *                  User has to call event channel functions to clear/enable the event flags if needed.
	 *
	 * Example:         DmaChnDisable(DMA_CHANNEL2); DmaChnConfigure(DMA_CHANNEL2, DMA_CHN_PRI2, DMA_CONFIG_AUTO|DMA_CONFIG_MATCH|DMA_CONFIG_ENABLE);
	 ********************************************************************/
	void			DmaChnConfigure(DmaChannel chn, DmaChannelPri chPri, DmaConfigFlags cFlags);


	/*********************************************************************
	 * Function:        int DmaChnGetSrcPnt(DmaChannel chn)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 *
	 * Output:          Current channel source pointer.
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function retrieves the current source pointer for the selected DMA channel.
	 * 					It is the current offset, 0 to DmaGetMaxTxferSize()-1, in the source transfer buffer.
	 *
	 * Note:            None
	 *
	 * Example:         int srcPnt=DmaChnGetSrcPnt(DMA_CHANNEL3);
	 ********************************************************************/
	 int			DmaChnGetSrcPnt(DmaChannel chn);

	/*********************************************************************
	 * Function:        int DmaChnGetDstPnt(DmaChannel chn)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 *
	 * Output:          Current channel destination pointer.
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function retrieves the current destination pointer for the selected DMA channel.
	 * 					It is the current offset, 0 to DmaGetMaxTxferSize()-1, in the destination transfer buffer.
	 *
	 * Note:            None
	 *
	 * Example:			int dstPnt=DmaChnGetDstPnt(DMA_CHANNEL3);
	 ********************************************************************/
	 int			DmaChnGetDstPnt(DmaChannel chn);

	/*********************************************************************
	 * Function:        int DmaChnGetCellPnt(DmaChannel chn)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 *
	 * Output:          Current channel transfer pointer.
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function retrieves the current transfer progress pointer for the selected DMA channel.
	 * 					It ranges 0 to DmaGetMaxTxferSize()-1.
	 *
	 * Note:            None
	 *
	 * Example:			int cellPnt=DmaChnGetCellPnt(DMA_CHANNEL3);
	 ********************************************************************/
	 int			DmaChnGetCellPnt(DmaChannel chn);



	/*********************************************************************
	 * Function:        void DmaChnSetEventControlFlags(DmaChannel chn, DmaEvCtrlFlags dmaEvCtrl)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn			- DMA channel number
	 * 					dmaEvCtrl	- 	either a DmaEvCtrl structure field, carrying the following info:
	 * 										- AIRQEN: enable/disable the abort IRQ action
	 * 										- SIRQEN: enable/disable the start IRQ action
	 * 										- PATEN: enable/disable the pattern match and abort
	 * 									or any of the DmaEvCtrlFlags:
	 * 										DMA_EV_ABORT_IRQ_EN|DMA_EV_START_IRQ_EN|DMA_EV_MATCH_EN
	 *
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function sets the events that start and abort the transfer
	 * 					for the selected DMA channel.
	 * 					Multiple flags can be orr-ed together. Any flag that is set in the eFlags will be
	 * 					enabled for the selected channel, the other channel event flags won't be touched.
	 *
	 * Note:            None.
	 *
	 * Example:			either:
	 * 						DmaChnSetEventControlFlags(DMA_CHANNEL3, DMA_EV_MATCH_EN|DMA_EV_START_IRQ_EN;
	 * 					or:
	 * 						DmaEvCtrl evCtrl; evCtrl.w=0; evCtrl.PATEN=1; evCtrl.SIRQEN=1;
	 * 						DmaChnSetEventControlFlags(DMA_CHANNEL3, evCtrl.w);
	 *
	 ********************************************************************/
	 void			DmaChnSetEventControlFlags(DmaChannel chn, DmaEvCtrlFlags dmaEvCtrl);


	/*********************************************************************
	 * Function:        void DmaChnClrEventControlFlags(DmaChannel chn, DmaEvCtrlFlags dmaEvCtrl)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn			- DMA channel number
	 * 					dmaEvCtrl	- 	either a DmaEvCtrl structure field, carrying the following info:
	 * 										- AIRQEN: enable/disable the abort IRQ action
	 * 										- SIRQEN: enable/disable the start IRQ action
	 * 										- PATEN: enable/disable the pattern match and abort
	 * 									or any of the DmaEvCtrlFlags:
	 * 										DMA_EV_ABORT_IRQ_EN|DMA_EV_START_IRQ_EN|DMA_EV_MATCH_EN
	 *
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function clears the events that start and abort the transfer
	 * 					for the selected DMA channel.
	 * 					Multiple flags can be orr-ed together. Any flag that is set in the eFlags will be
	 * 					disabled for the selected channel, the other channel event flags won't be touched.
	 *
	 * Note:            None.
	 *
	 * Example:			either:
	 * 						DmaChnClrEventControlFlags(DMA_CHANNEL3, DMA_EV_MATCH_EN|DMA_EV_START_IRQ_EN);
	 * 					or:
	 * 						DmaEvCtrl evCtrl; evCtrl.w=0; evCtrl.PATEN=1; evCtrl.AIRQEN=1;
	 * 						DmaChnClrEventControlFlags(DMA_CHANNEL3, evCtrl.w);
	 *
	 ********************************************************************/
	 void			DmaChnClrEventControlFlags(DmaChannel chn, DmaEvCtrlFlags dmaEvCtrl);



	/*********************************************************************
	 * Function:        void DmaChnWriteEventControlFlags(DmaChannel chn, DmaEvCtrlFlags dmaEvCtrl)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn			- DMA channel number
	 * 					dmaEvCtrl	- 	either a DmaEvCtrl structure field, carrying the following info:
	 * 										- AIRQEN: enable/disable the abort IRQ action
	 * 										- SIRQEN: enable/disable the start IRQ action
	 * 										- PATEN: enable/disable the pattern match and abort
	 * 										- CHSIRQ: IRQ number to start the DMA channel transfer
	 * 										- CHAIRQ: IRQ number to abort the DMA channel transfer
	 * 									or any of the DmaEvCtrlFlags:
	 * 										DMA_EV_ABORT_IRQ_EN|DMA_EV_START_IRQ_EN|DMA_EV_MATCH_EN|DMA_EV_START_IRQ(irq)|DMA_EV_ABORT_IRQ(irq)
	 *
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function writes the events that start and abort the transfer
	 * 					for the selected DMA channel.
	 *
	 * Note:            None.
	 *
	 * Example:			either:
	 * 						DmaChnWriteEventControlFlags(DMA_CHANNEL3, DMA_EV_MATCH_EN|DMA_EV_START_IRQ(_UART2_RX_IRQ));
	 * 					or:
	 * 						DmaEvCtrl evCtrl; evCtrl.w=0; evCtrl.AIRQEN=1; evCtrl.PATEN=1; evCtrl.CHSIRQ=_UART2_RX_IRQ;
	 * 						DmaChnWriteEventControlFlags(DMA_CHANNEL3, evCtrl.w);
	 *
	 ********************************************************************/
	 void			DmaChnWriteEventControlFlags(DmaChannel chn, DmaEvCtrlFlags dmaEvCtrl);



	/*********************************************************************
	 * Function:        void DmaChnSetEventControl(DmaChannel chn, DmaEvCtrlFlags dmaEvCtrl)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn			- DMA channel number
	 * 					dmaEvCtrl	- 	either a DmaEvCtrl structure field, carrying the following info:
	 * 										- AIRQEN: enable/disable the abort IRQ action
	 * 										- SIRQEN: enable/disable the start IRQ action
	 * 										- PATEN: enable/disable the pattern match and abort
	 * 										- CHSIRQ: IRQ number to start the DMA channel transfer
	 * 										- CHAIRQ: IRQ number to abort the DMA channel transfer
	 * 									or any of the DmaEvCtrlFlags:
	 * 										DMA_EV_ABORT_IRQ_EN|DMA_EV_START_IRQ_EN|DMA_EV_MATCH_EN|DMA_EV_START_IRQ(irq)|DMA_EV_ABORT_IRQ(irq)
	 *
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function sets the events that start and abort the transfer
	 * 					for the selected DMA channel.
	 * 					Multiple flags can be orr-ed together. Any flag that is set in the eFlags will be
	 * 					enabled for the selected channel, the other channel event flags won't be touched.
	 *
	 * Note:           A shorter name for DmaChnWriteEventControlFlags();
	 *
	 * Example:			either:
	 * 						DmaChnSetEventControl(DMA_CHANNEL3, DMA_EV_MATCH_EN|DMA_EV_START_IRQ(_UART2_RX_IRQ));
	 * 					or:
	 * 						DmaEvCtrl evCtrl; evCtrl.w=0; evCtrl.AIRQEN=1; evCtrl.PATEN=1; evCtrl.CHSIRQ=_UART2_RX_IRQ;
	 * 						DmaChnSetEventControl(DMA_CHANNEL3, evCtrl.w);
	 *
	 ********************************************************************/
	#define			DmaChnSetEventControl(chn, dmaEvCtrl)	DmaChnWriteEventControlFlags(chn, dmaEvCtrl)


	/*********************************************************************
	 * Function:        DmaEvCtrlFlags DmaChnGetEventControl(DmaChannel chn)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 *
	 * Output:          - 	either a DmaEvCtrl structure field, carrying the following info:
	 * 							- AIRQEN: enable/disable the abort IRQ action
	 * 							- SIRQEN: enable/disable the start IRQ action
	 * 							- PATEN: enable/disable the pattern match and abort
	 * 							- CHSIRQ: IRQ number to start the DMA channel transfer
	 * 							- CHAIRQ: IRQ number to abort the DMA channel transfer
	 * 						or any of the DmaEvCtrlFlags:
	 * 							DMA_EV_ABORT_IRQ_EN|DMA_EV_START_IRQ_EN|DMA_EV_MATCH_EN|DMA_EV_START_IRQ(irq)|DMA_EV_ABORT_IRQ(irq)
	 *
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function retrieves the events that start and abort the transfer
	 * 					for the selected DMA channel.
	 *
	 * Note:            None.
	 *
	 * Example:			either:
	 * 						DmaEvCtrlFlags evCtrlW=DmaChnGetEventControl(DMA_CHANNEL3); if(evCtrlW&DMA_EV_MATCH_EN) {...}
	 * 					or:
	 * 						DmaEvCtrl evCtrl; evCtrl.w=DmaChnGetEventControl(DMA_CHANNEL3); if(evCtrl.PATEN){...}
	 *
	 ********************************************************************/
	 DmaEvCtrlFlags	DmaChnGetEventControl(DmaChannel chn);


	/*********************************************************************
	 * Function:        void DmaChnSetControlFlags(DmaChannel chn, DmaChnCtrlFlags dmaChnCtrl)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn			- DMA channel number
	 * 					dmaChnCtrl	- 	either a DmaChnCtrl structure field, carrying the following info:
	 * 										- autoEn: enable/disable the automatic mode
	 * 										- chainEn: enable/disable channel chaining
	 * 										- detectEn: enable/disable events detection when channel disabled
	 * 										- chEn: enable/disable channel functionality
	 * 										- chainDir:	chain direction: chain to lower(1)/higher(0),pri channel
	 * 									or any of the DmaChnCtrlFlags flags:
	 * 										DMA_CTL_AUTO_EN|DMA_CTL_CHAIN_EN|DMA_CTL_DET_EN|DMA_CTL_CHN_EN|DMA_CTL_CHAIN_DIR
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function sets the selected DMA channel control flags:
	 * 					the chaining or auto mode, and events detection.
	 * 					Multiple flags can be orr-ed together. Any flag that is set in the dmaChnCtrl will be
	 * 					set for the selected channel, the other channel control flags won't be touched.
	 *
	 * Note:            None.
	 *
	 * Example:			either:
	 * 						DmaChnSetControlFlags(DMA_CHANNEL3, DMA_CTL_AUTO_EN|DMA_CTL_CHAIN_EN);
	 * 					or:
	 * 						DmaChnCtrl chCtrl; chCtrl.w=0; chCtrl.autoEn=1; chCtrl.chainEn=1;
	 * 						DmaChnSetControlFlags(DMA_CHANNEL3, chCtrl.w);
	 *
	 ********************************************************************/
	 void			DmaChnSetControlFlags(DmaChannel chn, DmaChnCtrlFlags dmaChnCtrl);

	/*********************************************************************
	 * Function:        void DmaChnClrControlFlags(DmaChannel chn, DmaChnCtrlFlags dmaChnCtrl)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn			- DMA channel number
	 * 					dmaChnCtrl	- 	either a DmaChnCtrl structure field, carrying the following info:
	 * 										- autoEn: enable/disable the automatic mode
	 * 										- chainEn: enable/disable channel chaining
	 * 										- detectEn: enable/disable events detection when channel disabled
	 * 										- chEn: enable/disable channel functionality
	 * 										- chainDir:	chain direction: chain to lower(1)/higher(0),pri channel
	 * 									or any of the DmaChnCtrlFlags flags:
	 * 										DMA_CTL_AUTO_EN|DMA_CTL_CHAIN_EN|DMA_CTL_DET_EN|DMA_CTL_CHN_EN|DMA_CTL_CHAIN_DIR
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function clears the selected DMA channel control flags:
	 * 					the chaining or auto mode and events detection.
	 * 					Multiple flags can be orr-ed together. Any flag that is set in the dmaChnCtrl will be
	 * 					cleared for the selected channel, the other channel control flags won't be touched.
	 *
	 * Note:            None.
	 *
	 * Example:			either:
	 * 						DmaChnClrControlFlags(DMA_CHANNEL3, DMA_CTL_AUTO_EN|DMA_CTL_CHAIN_EN);
	 * 					or:
	 * 						DmaChnCtrl chCtrl; chCtrl.w=0; chCtrl.autoEn=1; chCtrl.chainEn=1;
	 * 						DmaChnClrControlFlags(DMA_CHANNEL3, chCtrl.w);
	 *
	 ********************************************************************/
	 void			DmaChnClrControlFlags(DmaChannel chn, DmaChnCtrlFlags dmaChnCtrl);

	/*********************************************************************
	 * Function:        void DmaChnWriteControlFlags(DmaChannel chn, DmaChnCtrlFlags dmaChnCtrl)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn			- DMA channel number
	 * 					dmaChnCtrl	- 	either a DmaChnCtrl structure field, carrying the following info:
	 * 										- chPri: channel priority 0-3
	 * 										- autoEn: enable/disable the automatic mode
	 * 										- chainEn: enable/disable channel chaining
	 * 										- detectEn: enable/disable events detection when channel disabled
	 * 										- chEn: enable/disable channel functionality
	 * 										- chainDir:	chain direction: chain to lower(1)/higher(0),pri channel
	 * 									or any of the DmaChnCtrlFlags flags:
	 * 										DMA_CTL_PRI(pri)|DMA_CTL_AUTO_EN|DMA_CTL_CHAIN_EN|DMA_CTL_DET_EN|DMA_CTL_CHN_EN|DMA_CTL_CHAIN_DIR
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function enables/disables the selected DMA channel and also sets
	 * 					the channel priority, chaining mode or auto and events detection.
	 *
	 * Note:            None.
	 *
	 * Example:			either:
	 * 						DmaChnWriteControlFlags(DMA_CHANNEL3, DMA_CTL_PRI(DMA_CHN_PRI2)|DMA_CTL_AUTO_EN|DMA_CTL_CHAIN_EN);
	 * 					or:
	 * 						DmaChnCtrl chCtrl; chCtrl.w=0; chCtrl.chPri=DMA_CHN_PRI2; chCtrl.autoEn=1; chCtrl.chainEn=1;
	 * 						DmaChnWriteControlFlags(DMA_CHANNEL3, chCtrl.w);
	 *
	 ********************************************************************/
	 void			DmaChnWriteControlFlags(DmaChannel chn, DmaChnCtrlFlags dmaChnCtrl);

	/*********************************************************************
	 * Function:        void DmaChnSetControl(DmaChannel chn, DmaChnCtrlFlags dmaChnCtrl)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:	    chn		- DMA channel number
	 *                  dmaChnCtrl	- 	either a DmaChnCtrl structure field, carrying the following info:
	 * 						- chPri: channel priority 0-3
	 * 						- autoEn: enable/disable the automatic mode
	 * 						- chainEn: enable/disable channel chaining
	 * 						- detectEn: enable/disable events detection when channel disabled
	 * 						- chEn: enable/disable channel functionality
	 * 						- chainDir:	chain direction: chain to lower(1)/higher(0),pri channel
	 * 					or any of the DmaChnCtrlFlags flags:
	 * 						DMA_CTL_PRI(pri)|DMA_CTL_AUTO_EN|DMA_CTL_CHAIN_EN|DMA_CTL_DET_EN|DMA_CTL_CHN_EN|DMA_CTL_CHAIN_DIR
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function enables/disables the selected DMA channel and also sets
	 * 					the channel priority, chaining mode or auto and events detection.
	 *
	 * Note:            Another name ( backward compatible) for DmaChnWriteControlFlags().
	 *
	 * Example:         either:
	 *                      DmaChnSetControl(DMA_CHANNEL3, DMA_CTL_PRI(DMA_CHN_PRI2)|DMA_CTL_AUTO_EN|DMA_CTL_CHAIN_EN);
	 *                  or:
	 *                     	DmaChnCtrl chCtrl; chCtrl.w=0; chCtrl.chPri=DMA_CHN_PRI2; chCtrl.autoEn=1; chCtrl.chainEn=1;
	 * 			DmaChnSetControl(DMA_CHANNEL3, chCtrl.w);
	 *
	 ********************************************************************/
	#define		DmaChnSetControl(chn, dmaChnCtrl)	DmaChnWriteControlFlags(chn, dmaChnCtrl)

	/*********************************************************************
	 * Function:        DmaChnCtrlFlags DmaChnGetControlFlags(DmaChannel chn)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn			- DMA channel number
	 *
	 * Output:          - either a DmaChnCtrl structure field, carrying the following info:
	 * 							- chPri: channel priority 0-3
	 * 							- autoEn: enable/disable the automatic mode
	 * 							- chainEn: enable/disable channel chaining
	 * 							- detectEn: enable/disable events detection when channel disabled
	 * 							- chEn: enable/disable channel functionality
	 * 							- chainDir:	chain direction: chain to lower(1)/higher(0),pri channel
	 *						or any of the DmaChnCtrlFlags flags:
	 *							DMA_CTL_PRI(pri)|DMA_CTL_AUTO_EN|DMA_CTL_CHAIN_EN|DMA_CTL_DET_EN|DMA_CTL_CHN_EN|DMA_CTL_CHAIN_DIR
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function retrieves the current control settings for the selected DMA channel,
	 * 					including the channel enable/disable status, the channel priority,
	 * 					chaining mode, auto mode and events detection.
	 *
	 * Note:            None.
	 *
	 * Example:			either:
	 * 						DmaChnCtrlFlags ctrl=DmaChnGetControlFlags(DMA_CHANNEL3); if(ctrl&DMA_CTL_AUTO_EN) {...}
	 * 					or:
	 * 						DmaChnCtrl chnCtrl; chnCtrl.w=DmaChnGetControlFlags(DMA_CHANNEL3); if(chnCtrl.autoEn) {...}
	 *
	 ********************************************************************/
	 DmaChnCtrlFlags	DmaChnGetControlFlags(DmaChannel chn);


	/*********************************************************************
	 * Function:        int DmaChnGetEvDetect(DmaChannel chn)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 *
	 * Output:          TRUE if an DMA event was detected, FALSE otherwise.
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function returns the current event detection for the selected DMA channel.
	 *
	 * Note:            None.
	 *
	 * Example:			int evDetect=DmaChnGetEvDetect(DMA_CHANNEL3);
	 *
	 ********************************************************************/
	 int			DmaChnGetEvDetect(DmaChannel chn);

	/*********************************************************************
	 * Function:        void DmaChnGetTxfer(DmaChannel chn, DmaTxferCtrl* pTxCtrl, int mapToK0)
	 *
	 * PreCondition:    chn		- valid DMA channel
	 * 					pTxCtrl	- valid pointer
	 *
	 * Input:			chn			- DMA channel number
	 * 					pTxCtrl		- pointer to a DmaTxferCtrl that will carry the following info:
	 * 								- vSrcAdd: source of the DMA transfer
	 * 								- vDstAdd: destination of the DMA transfer
	 * 								- srcSize: source buffer size, 1 to DmaGetMaxTxferSize() bytes, wrapped arround
	 * 								- dstSize: destination buffer size, 1 to DmaGetMaxTxferSize() bytes, wrapped around
	 * 								- cellSize: cell transfer size, 1 to DmaGetMaxTxferSize() bytes.
	 *					mapToK0		- if TRUE, a Kernel address is mapped to KSeg0, else KSeg1.
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function retrieves the transfer characteristics for a DMA channel transfer:
	 * 					the source and the destination addresses.
	 * 					It also retrieves the source and destination lengths
	 * 					and the number of bytes	transferred per event.
	 *
	 * Note:            None
	 *
	 * Example:			DmaTxferCtrl txCtl; DmaChnGetTxfer(DMA_CHANNEL3, &txCtl, FALSE);
	 ********************************************************************/
	 void			DmaChnGetTxfer(DmaChannel chn, DmaTxferCtrl* pTxCtrl, int mapToK0);

	// Low level checksum functions

	/*********************************************************************
	 * Function:        void DmaSfmEnable(int enable)
	 *
	 * PreCondition:    None
	 *
	 * Input:           enable _ boolean to enable/disable the SFM functionality
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function enables/diables the checksum module functionality.
	 *                  When enabled the attached DMA channel transfers are routed to the SFM module.
	 *
	 * Note:            The SFM module should be properly configured before enabled.
	 *
	 * Example:         DmaSfmEnable(1);
	 ********************************************************************/
	extern __inline__ void __attribute__((always_inline)) DmaSfmEnable(int enable)
	{
		if(enable)
		{
			DCRCCONSET=_DCRCCON_CRCEN_MASK;
		}
		else
		{
			DCRCCONCLR=_DCRCCON_CRCEN_MASK;
		}
	}
	#define DmaCrcEnable	DmaSfmEnable		// PIC32_3xx backward compatibility


	/*********************************************************************
	 * Function:        int DmaSfmGetEnable(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:			None
	 *
	 * Output:          TRUE, if the SFM module is enabled
	 * 		    FALSE otherwise
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function returns the SFM module enabling status.
	 *
	 * Note:            None
	 *
	 * Example:	    int isSfmEnabled=DmaSfmGetEnable();
	 ********************************************************************/
	extern __inline__ int __attribute__((always_inline)) DmaSfmGetEnable(void)
	{
		return DCRCCONbits.CRCEN!=0;
	}
	#define		DmaCrcGetEnable 	DmaSfmGetEnable		// PIC32_3xx backward compatibility


	/*********************************************************************
	 * Function:        void DmaSfmAppendEnable(int enable)
	 *
	 * PreCondition:    None
	 *
	 * Input:           enable _ boolean to enable/disable the SFM append mode
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function enables the SFM append mode. In this mode, the attached DMA channel reads
	 *                  the source data but does not write it to the destination address. The data it's just passed
	 *                  to the checksum generator for CRC/IP checksum calculation.
	 *                  When the block transfer is completed, the checksum result is written to the
	 *                  DMA channel destination address.
	 *
	 * Note:            The SFM module should be properly configured before enabled.
	 *
	 * Example:         DmaSfmAppendModeEnable(TRUE);
	 ********************************************************************/
	extern __inline__ void __attribute__((always_inline)) DmaSfmAppendEnable(int enable)
	{
		if(enable)
		{
			DCRCCONSET=_DCRCCON_CRCAPP_MASK;
		}
		else
		{
			DCRCCONCLR=_DCRCCON_CRCAPP_MASK;
		}
	}
	#define		DmaCrcAppendModeEnable	DmaSfmAppendEnable	// PIC32_3xx backward compatibility


	/*********************************************************************
	 * Function:        int DmaSfmGetAppendMode(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          TRUE, if the SFM append mode is enabled
	 *                  FALSE otherwise
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function returns the SFM module enabling status.
	 *
	 * Note:            None
	 *
	 * Example:         int isAppendEnabled=DmaSfmGetAppendMode();
	 ********************************************************************/
	extern __inline__ int __attribute__((always_inline)) DmaSfmGetAppendMode(void)
	{
		return DCRCCONbits.CRCAPP!=0;
	}
	#define	DmaCrcGetAppendMode	DmaSfmGetAppendMode		// PIC32_3xx backward compatibility


	/*********************************************************************
	 * Function:        void DmaSfmSetAttach(DmaChannel chn)
	 *
	 * PreCondition:    chn		- valid DMA channel
	 *
	 * Input:           chn	- the DMA channel to be attached to the SFM module (the DMA channel transfers will be routed to the SFM module)
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function directly attaches a DMA channel to the SFM module.
	 *
	 * Note:            None
	 *
	 * Example:         DmaSfmSetAttach(DMA_CHANNEL3);
	 ********************************************************************/
	extern __inline__ void __attribute__((always_inline)) DmaSfmSetAttach(DmaChannel chn)
	{
		DCRCCONCLR=_DCRCCON_CRCCH_MASK;
		DCRCCONSET=chn;
	}
	#define		DmaCrcSetAttach		DmaSfmSetAttach		// PIC32_3xx backward compatibility


	/*********************************************************************
	 * Function:        DmaChannel DmaSfmGetAttach(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          the DMA channel that is currently attached to the CRC module
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function returns the DMA channel number that is currently attached to the SFM module.
	 *
	 * Note:            None
	 *
	 * Example:         DmaChannel chn=DmaSfmGetAttach();
	 ********************************************************************/
	extern __inline__ DmaChannel __attribute__((always_inline)) DmaSfmGetAttach(void)
	{
		return (DmaChannel)DCRCCONbits.CRCCH;
	}
	#define		DmaCrcGetAttach		DmaSfmGetAttach		// PIC32_3xx backward compatibility

	/*********************************************************************
	 * Function:        void DmaCrcSetPLen(int pLen)
	 *
	 * PreCondition:    pLen - valid polynomial length within 1-32
	 *
	 * Input:           pLen	- the length of the CRC generator polynomial
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The length of the CRC generator polynomial is set as being pLen;
	 *
	 * Note:            None
	 *
	 * Example:         DmaCrcSetPLen(32);
	 ********************************************************************/
	extern __inline__ void __attribute__((always_inline)) DmaCrcSetPLen(int pLen)
	{
		DCRCCONCLR=_DCRCCON_PLEN_MASK;
		DCRCCONSET=(pLen)-1;
	}

	/*********************************************************************
	 * Function:        int DmaCrcGetPLen(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          the length of the CRC generator polynomial
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function returns the current length of the CRC generator polynomial.
	 *                  It's always a number between 1 and 32.
	 *
	 * Note:            None
	 *
	 * Example:         int polyLen=DmaCrcGetPLen();
	 ********************************************************************/
	extern __inline__ int __attribute__((always_inline)) DmaCrcGetPLen(void)
	{
		return	DCRCCONbits.PLEN+1; 
	}

	/*********************************************************************
	 * Function:        void DmaCrcSetShiftFeedback(unsigned int feedback)
	 *
	 * PreCondition:    None
	 *
	 * Input:           feedback - the layout of the CRC generator
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function sets the layout of the shift stages that take place in the CRC generation.
	 *                  Setting a bit to 1 enables the XOR input from the MSb (pLen bit) to the selected stage in the shift register.
	 *                  If bit is cleared, the selected shift stage gets data directly from the previous stage in the shift register.
	 *
	 * Note:            Bit 0 of the generator polynomial is always XOR'ed.
	 *
	 * Example:         DmaCrcSetShiftFeedback(0x04c11db7);
	 ********************************************************************/
	extern __inline__ void __attribute__((always_inline)) DmaCrcSetShiftFeedback(unsigned int feedback)
	{
		DCRCXOR=feedback;
	}


	/*********************************************************************
	 * Function:        unsigned int DmaCrcGetShiftFeedback(void)
	 *
	 * PreCondition:    None
	 *
	 * Input:           None
	 *
	 * Output:          the current layout of the CRC generator
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function returns the layout of the shift stages that take place in the CRC generation.
	 *                  A bit set to 1 enables the XOR input from the MSb (pLen bit) to the selected stage in the shift register.
	 *                  If a bit is cleared, the selected shift stage gets data directly from the previous stage in the shift register.
	 *
	 * Note:            Bit 0 of the generator polynomial is always XOR'ed.
	 *
	 * Example:         int feedback=DmaCrcGetShiftFeedback();
	 ********************************************************************/
	extern __inline__ unsigned int __attribute__((always_inline)) DmaCrcGetShiftFeedback(void)
	{
		return DCRCXOR;
	}



	// Channel test/debug and special functions

	/*********************************************************************
	 * Function:        void DmaChnSetEvFlags(DmaChannel chn, DmaEvFlags eFlags)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 * 					eFlags	- event flags with the following significance:
	 * 								- DMA_EV_ERR: address error event
	 * 								- DMA_EV_ABORT: transfer abort event
	 * 								- DMA_EV_CELL_DONE: cell transfer complete event
	 * 								- DMA_EV_BLOCK_DONE: block transfer complete event
	 * 								- DMA_EV_DST_HALF: destination half event
	 * 								- DMA_EV_DST_FULL: destination full event
	 * 								- DMA_EV_SRC_HALF: source half event
	 * 								- DMA_EV_SRC_FULL: source full event
	 * 								- DMA_EV_ALL_EVNTS: all of the above flags
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function sets the event flags for the selected DMA channel.
	 * 					Multiple flags can be orr-ed together. Any flag that is set in the eFlags will be
	 * 					set for the selected channel, the other channel event flags won't be touched.
	 *
	 * Note:            This is intended as a channel test function.
	 *
	 * Example:			DmaChnSetEvFlags(DMA_CHANNEL0, DMA_EV_ERR|DMA_EV_ABORT|DMA_EV_BLOCK_DONE|DMA_EV_SRC_FULL);
	 ********************************************************************/
	 void			DmaChnSetEvFlags(DmaChannel chn, DmaEvFlags eFlags);

	/*********************************************************************
	 * Function:        void DmaChnWriteEvFlags(DmaChannel chn, DmaEvFlags eFlags)
	 *
	 * PreCondition:    chn	- valid DMA channel
	 *
	 * Input:			chn		- DMA channel number
	 * 					eFlags	- event flags with the following significance:
	 * 								- DMA_EV_ERR: address error event
	 * 								- DMA_EV_ABORT: transfer abort event
	 * 								- DMA_EV_CELL_DONE: cell transfer complete event
	 * 								- DMA_EV_BLOCK_DONE: block transfer complete event
	 * 								- DMA_EV_DST_HALF: destination half event
	 * 								- DMA_EV_DST_FULL: destination full event
	 * 								- DMA_EV_SRC_HALF: source half event
	 * 								- DMA_EV_SRC_FULL: source full event
	 * 								- DMA_EV_ALL_EVNTS: all of the above flags
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:		The function writes the event flags for the selected DMA channel.
	 * 					The channel event flags are forced to the eFlags value.
	 *
	 * Note:            This is intended as a channel test function.
	 *
	 * Example:			DmaChnWriteEvFlags(DMA_CHANNEL0, DMA_EV_ERR|DMA_EV_ABORT|DMA_EV_BLOCK_DONE|DMA_EV_SRC_FULL);
	 ********************************************************************/
	 void			DmaChnWriteEvFlags(DmaChannel chn, DmaEvFlags eFlags);


	/*********************************************************************
	 * Function:        void DmaFreezeEnable(int enable)
	 *
	 * PreCondition:    None
	 *
	 * Input:           enable - boolean to enable/disable the freeze mode
	 *
	 * Output:          None
	 *
	 * Side Effects:    None
	 *
	 * Overview:        The function sets the DMA controller behavior in Debug mode.
	 *                  The DMA controller is frozen/continues to run in Debug mode.
	 *
	 * Note:            This is intended as a channel test function.
	 *                  It takes effect from a debug exception only.
	 *
	 * Example:         DmaFreezeEnable(1);
	 ********************************************************************/
        extern __inline__ void __attribute__((always_inline)) DmaFreezeEnable(int enable)
	{
		if(enable)
		{
			DMACONSET=_DMACON_FRZ_MASK;
		}
		else
		{
			DMACONCLR=_DMACON_FRZ_MASK;
		}
	}


	/********************************************************************
	 * Include legacy DMA functions
	 * New projects should not use them!
	 * Note that interrupt functions are no longer provided.
	 * The functions in the int.h should be used instead.
	 ********************************************************************/
	#ifndef _PLIB_DISABLE_LEGACY
		#include <peripheral/legacy/dma_legacy.h>
	#endif


#else
	#undef _DMA_CHANNELS		// no DMA channels
#endif	// _DMAC0

#endif /*_DMA_H_*/


