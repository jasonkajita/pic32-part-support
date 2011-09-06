/*********************************************************************
 *
 *                  DMA Legacy Library definitions
 *
 *********************************************************************
 * FileName:        dma_legacy.h
 * Dependencies:    p32xxxx.h
 *                  int.h
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

#ifndef _DMA_LEGACY_H_
#define _DMA_LEGACY_H_

#include <p32xxxx.h>
#ifdef _DMAC0
/* DMA channels exist */
#include <peripheral/dma.h>
#include <peripheral/int.h>


/*****************************************************
 * 	Legacy DMA functions/definitions
 * 	These functions are provided for backward compatibility only
 * 	They are no longer maintained!
 * 	New projects should not use them!
 *******************************************************/


/*****************************************
 *       Legacy Interrupt functions
 *       The functions in the int.h should be used instead.
 ***********************************************************/

/*********************************************************************
 * Function:        void DmaChnIntEnable(int chn)
 *
 * PreCondition:    chn	- valid DMA channel
 *
 * Input:			chn		- DMA channel number
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function enables the interrupts in the Interrupt Controller (EVIC) for the selected DMA channel.
 *
 * Note:            None.
 *
 * Example:			int chn=3; DmaChnIntEnable(chn);
 * 					mDmaChnIntEnable(3);
 ********************************************************************/
#define			DmaChnIntEnable(chn)	INTEnable(INT_DMA0+(chn), 1)
#define			mDmaChnIntEnable(c)		(mDMA##c##IntEnable(1))	// macro version


/*********************************************************************
 * Function:        void DmaChnIntDisable(int chn)
 *
 * PreCondition:    chn	- valid DMA channel
 *
 * Input:			chn		- DMA channel number
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function disables the interrupts in the Interrupt Controller (EVIC) for the selected DMA channel.
 *
 * Note:            None.
 *
 * Example:			int chn=3; DmaChnIntDisable(chn);
 * 					mDmaChnIntDisable(3);
 ********************************************************************/
#define			DmaChnIntDisable(chn)		INTEnable(INT_DMA0+(chn), 0)
#define			mDmaChnIntDisable(c)		(mDMA##c##IntEnable(0))	// macro version



/*********************************************************************
 * Function:        int DmaChnGetIntEnable(int chn)
 *
 * PreCondition:    chn	- valid DMA channel
 *
 * Input:			chn		- DMA channel number
 *
 * Output:          TRUE if the corresponding interrupt is enabled,
 * 					FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:		The function returns the Interrupt Controller (EVIC) interrupt enabled status for the selected DMA channel.
 *
 * Note:            None.
 *
 * Example:			int chn=3; int isEnabled=DmaChnGetIntEnable(chn);
 * 					isEnabled=mDmaChnGetIntEnable(3);
 ********************************************************************/
#define			DmaChnGetIntEnable(chn)		INTGetEnable(INT_DMA0+(chn))
#define			mDmaChnGetIntEnable(c)		(mDMA##c##GetIntEnable())		// macro version

/*********************************************************************
 * Function:        void DmaChnSetIntPriority(int chn, int iPri, int subPri)
 *
 * PreCondition:    chn	- valid DMA channel
 *
 * Input:			chn		- DMA channel number
 * 					iPri	- the interrupt priority in the interrupt controller
 * 					subPri	- the interrupt subpriority in the interrupt controller
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function sets the interrupt priority and subpriority in the Interrupt Controller (EVIC) for the selected DMA channel.
 *
 * Note:            None.
 *
 * Example:			int chn=0; DmaChnSetIntPriority(chn, INT_PRIORITY_LEVEL_5, INT_SUB_PRIORITY_LEVEL_3);
 * 					mDmaChnSetIntPriority(0, 5, 3);
 ********************************************************************/
#define			DmaChnSetIntPriority(chn, iPri, subPri)		do{INTSetPriority(INT_DMA0+(chn), (iPri)); \
															 INTSetSubPriority(INT_DMA0+(chn), (subPri));}while(0)
#define			mDmaChnSetIntPriority(c, iPri, subPri)		(mDMA##c##SetIntPriority(iPri), mDMA##c##SetIntSubPriority(subPri))	// macro version

/*********************************************************************
 * Function:        int DmaChnGetIntPriority(int chn)
 *
 * PreCondition:    chn	- valid DMA channel
 *
 * Input:			chn		- DMA channel number
 *
 * Output:          the current channel interrupt priority in the INT controller
 *
 * Side Effects:    None
 *
 * Overview:		The function reads the current interrupt priority in the Interrupt Controller (EVIC) for the selected DMA channel.
 *
 * Note:            None.
 *
 * Example:			int chn=2; int currPri=DmaChnGetIntPriority(chn);
 * 					currPri=mDmaChnGetIntPriority(2);
 ********************************************************************/
#define			DmaChnGetIntPriority(chn)	INTGetPriority(INT_DMA0+(chn))
#define			mDmaChnGetIntPriority(c)	(mDMA##c##GetIntPriority())		// macro version

/*********************************************************************
 * Function:        int DmaChnGetIntSubPriority(int chn)
 *
 * PreCondition:    chn	- valid DMA channel
 *
 * Input:			chn		- DMA channel number
 *
 * Output:          the current channel interrupt subpriority in the INT controller
 *
 * Side Effects:    None
 *
 * Overview:		The function reads the current subinterrupt priority in the Interrupt Controller (EVIC) for the selected DMA channel.
 *
 * Note:            None.
 *
 * Example:			int chn=2; int currSubPri=DmaChnGetIntSubPriority(chn);
 * 					currSubPri=mDmaChnGetIntSubPriority(2);
 ********************************************************************/
#define			DmaChnGetIntSubPriority(chn)	INTGetSubPriority(INT_DMA0+(chn))
#define			mDmaChnGetIntSubPriority(c)		(mDMA##c##GetIntSubPriority())		// macro version

/*********************************************************************
 * Function:        int DmaChnGetIntFlag(int chn)
 *
 * PreCondition:    chn	- valid DMA channel
 *
 * Input:			chn		- DMA channel number
 *
 * Output:          TRUE if the corresponding channel interrupt flag is set
 * 					FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:		The function reads the current interrupt flag status in the Interrupt Controller (EVIC) for the selected DMA channel.
 *
 * Note:            None.
 *
 * Example:			int chn=1; int isFlagSet=DmaChnGetIntFlag(chn);
 * 					isFlagSet=mDmaChnGetIntFlag(1);
 ********************************************************************/
#define			DmaChnGetIntFlag(chn)		INTGetFlag(INT_DMA0+(chn))
#define			mDmaChnGetIntFlag(c)		(mDMA##c##GetIntFlag())			// macro version

/*********************************************************************
 * Function:        void DmaChnClrIntFlag(int chn)
 *
 * PreCondition:    chn	- valid DMA channel
 *
 * Input:			chn		- DMA channel number
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function clears the current interrupt flag status in the Interrupt Controller (EVIC) for the selected DMA channel.
 *
 * Note:            None.
 *
 * Example:			int chn=1; DmaChnClrIntFlag(chn);
 * 					mDmaChnClrIntFlag(1);
 ********************************************************************/
#define			DmaChnClrIntFlag(chn)		INTClearFlag(INT_DMA0+(chn))
#define			mDmaChnClrIntFlag(c)		(mDMA##c##ClearIntFlag())		// macro version



/*****************************************
 *       Legacy DMA access functions
 ***********************************************************/
/*********************************************************************
 * Function:        void mDmaEnable(void)
 *
 * PreCondition:    None
 *
 * Input:		None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function/macro enables the DMA controller.
 *
 * Note:            None.
 *
 * Example:	mDmaEnable();
 ********************************************************************/
#define		mDmaEnable()	DmaEnable(1)

/*********************************************************************
 * Function:        void mDmaDisable(void)
 *
 * PreCondition:    None
 *
 * Input:		None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function/macro disables the DMA controller.
 *
 * Note:            None.
 *
 * Example:			mDmaDisable();
 ********************************************************************/
#define		mDmaDisable()	DmaEnable(0)

/*********************************************************************
 * Function:        void mDmaReset(void)
 *
 * PreCondition:    None
 *
 * Input:		None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function/macro resets the DMA controller.
 *
 * Note:            None.
 *
 * Example:			mDmaReset();
 ********************************************************************/
#define		mDmaReset	DmaReset


/*********************************************************************
 * Function:        void mDmaSetGlobalFlags(DmaGlblFlags gFlags)
 *
 * PreCondition:    None
 *
 * Input:           gFlags	- flags to be set, having the fields described in DmaGlblFlags
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function affects the global behavior of the DMA controller.
 * 					It sets the specified flags. Any flag that is set in the gFlags will be
 * 					enabled, the other flags won't be touched.
 *
 * Note:            None.
 *
 * Example:			mDmaSetGlobalFlags(DMA_GFLG_ON);
 ********************************************************************/
#define				mDmaSetGlobalFlags	DmaSetGlobalFlags

/*********************************************************************
 * Function:        void mDmaClrGlobalFlags(DmaGlblFlags gFlags)
 *
 * PreCondition:    None
 *
 * Input:			gFlags	- flags to be cleared, having the the fields described in DmaGlblFlags
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function affects the global behavior of the DMA controller.
 * 					It clears the specified flags. Any flag that is set in the gFlags will be
 * 					cleared, the other flags won't be touched.
 *
 * Note:            None.
 *
 * Example:			mDmaClrGlobalFlags(DMA_GFLG_SUSPEND);
 ********************************************************************/
#define				mDmaClrGlobalFlags		mDmaClrGlobalFlags

/*********************************************************************
 * Function:        void mDmaWriteGlobalFlags(DmaGlblFlags gFlags)
 *
 * PreCondition:    None
 *
 * Input:			gFlags	- flags to be set, having the the fields described in DmaGlblFlags
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function affects the global behavior of the DMA controller.
 * 					It forces the flags to have the specified gFlags value.
 *
 * Note:            None.
 *
 * Example:			mDmaWriteGlobalFlags(DMA_GFLG_ALL_FLAGS);
 ********************************************************************/
#define				mDmaWriteGlobalFlags		DmaWriteGlobalFlags


/*********************************************************************
 * Function:        DmaGlblFlags mDmaGetGlobalFlags(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          The current DMA controller flags settings having the the fields described in DmaGlblFlags
 *
 * Side Effects:    None
 *
 * Overview:		The function returns the global flags of the DMA controller.
 *
 * Note:            None.
 *
 * Example:			DmaGlblFlags dmaFlags=mDmaGetGlobalFlags();
 ********************************************************************/
#define 			mDmaGetGlobalFlags		DmaGetGlobalFlags


/*********************************************************************
 * Function:        void mDmaFreezeEnable()
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function sets the DMA controller behavior in Debug mode.
 * 					The DMA controller is frozen in Debug mode.
 *
 * Note:            This is intended as a channel test function.
 *
 * Example:			mDmaFreezeEnable();
 ********************************************************************/
#define		mDmaFreezeEnable()	DmaFreezeEnable(1)

/*********************************************************************
 * Function:        void mDmaFreezeDisable()
 *
 * PreCondition:    None
 *
 * Input:			frz	- if TRUE, the DMA controller is frozen in Debug mode.
 * 						- if FALSE,
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function sets the DMA controller behavior in Debug mode.
 * 					The DMA controller continues to run in Debug mode.
 *
 * Note:            This is intended as a channel test function.
 *
 * Example:			mDmaFreezeDisable();
 ********************************************************************/
#define	mDmaFreezeDisable()	DmaFreezeEnable(0)

// High level CRC functions

/*********************************************************************
 * Function:        void mCrcConfigure(unsigned int polynomial, int pLen, unsigned int seed)
 *
 * PreCondition:    pLen		- valid polynomial length within 1-16
 *
 * Input:			polynomial	- the layout of the CRC generator
 * 					pLen		- the length of the CRC generator polynomial
 * 					seed		- the initial seed of the CRC generator
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function configures the CRC module by setting the parameters that define the generator polynomial:
 * 					- the length of the CRC generator polynomial, pLen;
 * 					- the function sets the layout of the shift stages that take place in the CRC generation.
 * 						Setting a bit to 1 enables the XOR input from the MSb (pLen bit) to the selected stage in the shift register.
 * 						If bit is cleared, the selected shift stage gets data directly from the previous stage in the shift register.
 * 						Note that in a proper CRC polynomial, both the most significant bit (MSb) and least significant bit(LSb)
 * 						are always a '1'. Considering the generator polynomial: X^16+X^15+X^2+1, the value to be written as
 * 						feedback should be 0x8005, or 0x8004, but not 0x018005;
 *					- the function sets the seed of the CRC generator. This is the initial data present in the
 * 						CRC shift register before the CRC calculation begins. A good initial value is usually 0xffffffff.
 *
 * Note:            - Bit 0 of the generator polynomial is always XOR'ed.
 * 					- When the append mode is set, the attached DMA channel has to have destination size <=4.
 * 						Upon the transfer completion the calculated CRC is stored at the destination address.
 * 					- When append mode is cleared, the DMA transfer occurs normally, and the CRC value is available using
 * 						the CrcResult() function.
 * 					- The CRC module should be configured before enabled.
 *
 * Example:			mCrcConfigure(0x8005, 16, 0xffff);
 ********************************************************************/
#define mCrcConfigure		DmaCrcConfigure		// backward compatibility name


// Low level CRC functions

/*********************************************************************
 * Function:        void mCrcEnable(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function enables the CRC module functionality and the attached DMA channel transfers are routed to the CRC module.
 *
 * Note:            The CRC module should be properly configured before enabled.
 *
 * Example:			mCrcEnable();
 ********************************************************************/
#define mCrcEnable		DmaCrcEnable(1)


/*********************************************************************
 * Function:        void mCrcDisable(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function disables the CRC module functionality.
 *
 * Note:            None
 *
 * Example:			mCrcDisable();
 ********************************************************************/
#define mCrcDisable()	DmaCrcEnable(0)


/*********************************************************************
 * Function:        int mCrcGetEnable(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          TRUE, if the CRC module is enabled
 * 					FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:		The function returns the CRC module enabling status.
 *
 * Note:            None
 *
 * Example:			int isCrcEnabled=mCrcGetEnable();
 ********************************************************************/
#define				mCrcGetEnable		DmaCrcGetEnable


/*********************************************************************
 * Function:        void mCrcAppendModeEnable()
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function enables the CRC append mode. In this mode, the attached DMA channel reads
 * 					the source data but does not write it to the destination address. The data it's just passed
 * 					to the CRC generator for CRC calculation.
 * 					When the block transfer is completed, the CRC result is written to the
 * 					DMA channel destination address.
 *
 * Note:            The CRC module should be properly configured before enabled.
 *
 * Example:			mCrcAppendModeEnable();
 ********************************************************************/
#define	mCrcAppendModeEnable()	DmaCrcAppendModeEnable(1)


/*********************************************************************
 * Function:        void mCrcAppendModeDisable()
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function disables the CRC append mode. When the append mode is disabled,
 * 					The attached DMA channel normally transfers data from source to destination.
 * 					Data is also passed to the CRC controller for CRC calculation.
 * 					When the DMA transfer is completed, the CRC value is available using the CrcGetValue function.
 *
 * Note:            None
 *
 * Example:			mCrcAppendModeDisable();
 ********************************************************************/
#define		mCrcAppendModeDisable()	DmaCrcAppendModeEnable(0)


/*********************************************************************
 * Function:        int mCrcGetAppendMode(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          TRUE, if the CRC append mode is enabled
 * 					FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:		The function returns the CRC module enabling status.
 *
 * Note:            None
 *
 * Example:			int isAppendEnabled=mCrcGetAppendMode();
 ********************************************************************/
#define			mCrcGetAppendMode	DmaCrcGetAppendMode


/*********************************************************************
 * Function:        void mCrcSetDmaAttach(DmaChannel chn)
 *
 * PreCondition:    chn		- valid DMA channel
 *
 * Input:			chn	- the DMA channel to be attached to the CRC module (the DMA channel transfers will be routed to the CRC module)
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function attaches a DMA channel to the CRC module.
 *
 * Note:            None
 *
 * Example:			mCrcSetDmaAttach(3);
 ********************************************************************/
#define			mCrcSetDmaAttach	DmaCrcSetAttach


/*********************************************************************
 * Function:        DmaChannel mCrcGetDmaAttach(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          the DMA channel that is currently attached to the CRC module
 *
 * Side Effects:    None
 *
 * Overview:		The function returns the DMA channel number that is currently attached to the CRC module.
 *
 * Note:            None
 *
 * Example:			DmaChannel chn=mCrcGetDmaAttach();
 ********************************************************************/
#define			mCrcGetDmaAttach	DmaCrcGetAttach

/*********************************************************************
 * Function:        void mCrcSetPLen(int pLen)
 *
 * PreCondition:    pLen	- valid polynomial length within 1-16
 *
 * Input:			pLen	- the length of the CRC generator polynomial
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The length of the CRC generator polynomial is set as being pLen;
 *
 * Note:            None
 *
 * Example:			mCrcSetPLen(16);
 ********************************************************************/
#define			mCrcSetPLen		DmaCrcSetPLen


/*********************************************************************
 * Function:        int mCrcGetPLen(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          the length of the CRC generator polynomial
 *
 * Side Effects:    None
 *
 * Overview:		The function returns the current length of the CRC generator polynomial.
 * 					It's always a number between 1 and 16.
 *
 * Note:            None
 *
 * Example:			int polyLen=mCrcGetPLen();
 ********************************************************************/
#define				mCrcGetPLen	DmaCrcGetPLen

/*********************************************************************
 * Function:        void mCrcSetShiftFeedback(unsigned int feedback)
 *
 * PreCondition:    None
 *
 * Input:			feedback	- the layout of the CRC generator
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function sets the layout of the shift stages that take place in the CRC generation.
 * 					Setting a bit to 1 enables the XOR input from the MSb (pLen bit) to the selected stage in the shift register.
 * 					If bit is cleared, the selected shift stage gets data directly from the previous stage in the shift register.
 *
 * Note:            Bit 0 of the generator polynomial is always XOR'ed.
 *
 * Example:			mCrcSetShiftFeedback(0x8005);
 ********************************************************************/
#define			mCrcSetShiftFeedback	DmaCrcSetShiftFeedback


/*********************************************************************
 * Function:        unsigned int mCrcGetShiftFeedback(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          the current layout of the CRC generator
 *
 * Side Effects:    None
 *
 * Overview:		The function returns the layout of the shift stages that take place in the CRC generation.
 * 					A bit set to 1 enables the XOR input from the MSb (pLen bit) to the selected stage in the shift register.
 * 					If a bit is cleared, the selected shift stage gets data directly from the previous stage in the shift register.
 *
 * Note:            Bit 0 of the generator polynomial is always XOR'ed.
 *
 * Example:			int feedback=mCrcGetShiftFeedback();
 ********************************************************************/
#define				mCrcGetShiftFeedback	DmaCrcGetShiftFeedback


/*********************************************************************
 * Function:        void mCrcSetSeed(unsigned int seed)
 *
 * PreCondition:    None
 *
 * Input:			seed	- the initial seed of the CRC generator
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function sets the seed of the CRC generator. This is the initial data present in the
 * 					CRC shift register before the CRC calculation begins.
 *
 * Note:            None
 *
 * Example:			mCrcSetSeed(0xffff);
 ********************************************************************/
#define			mCrcSetSeed	DmaCrcSetSeed

/*********************************************************************
 * Function:        unsigned int mCrcGetValue(void)
 *
 * PreCondition:    None
 *
 * Input:			None
 *
 * Output:          the current value of the CRC generator
 *
 * Side Effects:    None
 *
 * Overview:		The function returns the current value of the CRC generator.
 *
 * Note:            Only the remainder bits (0 to pLen-1) are significant, the rest should be ignored.
 *
 * Example:		unsigned int calcCrc=mCrcGetValue();
 ********************************************************************/
#define				mCrcGetValue		DmaCrcGetValue

/*****************************************
 *       Very low level functions
 ***********************************************************/

// indexes of all available channel registers
typedef enum
{
	// control register
	DMA_REG_IX_CON,
	DMA_REG_IX_CON_CLR,
	DMA_REG_IX_CON_SET,
	DMA_REG_IX_CON_INV,
	// event control register
	DMA_REG_IX_ECON,
	DMA_REG_IX_ECON_CLR,
	DMA_REG_IX_ECON_SET,
	DMA_REG_IX_ECON_INV,
	// interrupt control register
	DMA_REG_IX_INTR,
	DMA_REG_IX_INTR_CLR,
	DMA_REG_IX_INTR_SET,
	DMA_REG_IX_INTR_INV,
	// source address register
	DMA_REG_IX_SSA,
	DMA_REG_IX_SSA_CLR,
	DMA_REG_IX_SSA_SET,
	DMA_REG_IX_SSA_INV,
	// destination address register
	DMA_REG_IX_DSA,
	DMA_REG_IX_DSA_CLR,
	DMA_REG_IX_DSA_SET,
	DMA_REG_IX_DSA_INV,
	// source size register
	DMA_REG_IX_SSIZ,
	DMA_REG_IX_SSIZ_CLR,
	DMA_REG_IX_SSIZ_SET,
	DMA_REG_IX_SSIZ_INV,
	// destination size register
	DMA_REG_IX_DSIZ,
	DMA_REG_IX_DSIZ_CLR,
	DMA_REG_IX_DSIZ_SET,
	DMA_REG_IX_DSIZ_INV,
	// source pointer register
	DMA_REG_IX_SPTR,
	DMA_REG_IX_RESERVED0,
	DMA_REG_IX_RESERVED1,
	DMA_REG_IX_RESERVED2,
	// destination pointer register
	DMA_REG_IX_DPTR,
	DMA_REG_IX_RESERVED3,
	DMA_REG_IX_RESERVED4,
	DMA_REG_IX_RESERVED5,
	// cell size register
	DMA_REG_IX_CSIZ,
	DMA_REG_IX_CSIZ_CLR,
	DMA_REG_IX_CSIZ_SET,
	DMA_REG_IX_CSIZ_INV,
	// cell pointer register
	DMA_REG_IX_CPTR,
	DMA_REG_IX_RESERVED6,
	DMA_REG_IX_RESERVED7,
	DMA_REG_IX_RESERVED8,
	// pattern data register
	DMA_REG_IX_DAT,
	DMA_REG_IX_DAT_CLR,
	DMA_REG_IX_DAT_SET,
	DMA_REG_IX_DAT_INV,
}DmaChnRegIx;

/*********************************************************************
 * Function:        void DmaChnSetRegister(DmaChannel chn, DmaChnRegIx regIx, int value)
 *
 * PreCondition:    chn	- valid DMA channel
 *
 * Input:			chn		- DMA channel number
 * 					regIx	- register index
 * 					value	- value to be set
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:		The function sets directly a value into a DMA channel register.
 *
 * Note:            This is intended as a low level access channel function.
 *
 * Example:			DmaChnSetRegister(3, DMA_REG_IX_SSIZ, myBuffSz);
 ********************************************************************/
 void			DmaChnSetRegister(DmaChannel chn, DmaChnRegIx regIx, unsigned int value);

/*********************************************************************
 * Function:        unsigned int DmaChnGetRegister(DmaChannel chn, DmaChnRegIx regIx)
 *
 * PreCondition:    chn	- valid DMA channel
 *
 * Input:			chn		- DMA channel number
 * 					regIx	- register index
 *
 * Output:          the current register value
 *
 * Side Effects:    None
 *
 * Overview:		The function retrieves the current value of a DMA channel register.
 *
 * Note:            This is intended as a low level access channel function.
 * 					Read from CLR/SET/INV registers yields undefined value.
 *
 * Example:			unsigned int mySrcSizeReg=DmaChnGetRegister(3, DMA_REG_IX_SSIZ);
 ********************************************************************/
 unsigned int		DmaChnGetRegister(DmaChannel chn, DmaChnRegIx regIx);

#endif	/* _DMAC0 */
#endif /*_DMA_LEGACY_H_*/

