/*********************************************************************
 *
 *                  BUS MATRIX API definitions
 *
 *********************************************************************
 * FileName:        BMX.h
 * Dependencies:	p32xxxx.h
 * Processor:       PIC32
 *
 * Complier:        MPLAB C32
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
 * $Id: BMX.h,v 1.8 2006/11/06 17:36:05 C12770 Exp $
 * $Name:  $
 *
 ********************************************************************/

#ifndef BMX_H_
#define BMX_H_

#include <p32xxxx.h>

/******************************************************************************************************************************
  * <combinewith mBMXGetArbMode, mBMXEnableXcpts, mBMXEnablePfmCheDma, mBMXEnableIxiExpt, mBMXEnableIcdExpt, mBMXEnableDmaExpt, 
  * mBMXEnableCpuIExpt, mBMXEnableCpuDExpt, mBMXDisableXcpts, mBMXDisablePfmCheDma, mBMXDisableIxiExpt, mBMXDisableIcdExpt, 
  * mBMXDisableDmaExpt, mBMXDisableCpuIExpt, mBMXDisableCpuDExpt, mBMXEnableDRMWaitState, mBMXDisableDRMWaitState>
  * 
  * Prototype:
  *     Inidividial Bit Set/Clr Macros for Bus Matrix Config Register
  * Preconditions:
  *     None
  * Input:
  *     mode :  Valid mode values are 0, 1, or 2
  * Return:
  *     None
  *     
  * Side Effects:
  *     None
  * Remarks:
  *     These macros let the programmer change individual bits in the
  *     bus matrix config BMXCON register. This method allows the
  *     programmer to change one or more bits without effecting the
  *     rest of the configuration bits
  * Note:
  *     None.                                                                                                                                                                                                                                                                                                        
  *****************************************************************************************************************************
*/

#define mBMXSetArbMode(mode)		(BMXCONCLR = _BMXCON_BMXARB_MASK, BMXCONSET = ((mode)&_BMXCON_BMXARB_MASK))
#define mBMXGetArbMode()			((BMXCON)&_BMXCON_BMXARB_MASK)

#define mBMXEnableDRMWaitState()	(BMXCONSET = _BMXCON_BMXWSDRM_MASK)
#define mBMXDisableDRMWaitState() 	(BMXCONCLR = _BMXCON_BMXWSDRM_MASK)

#define mBMXEnableXcpts(val)		(BMXCONSET = val)
#define mBMXDisableXcpts(val)		(BMXCONCLR = val)
	// Valid val values - Bus Error Exceptions
	#define BMX_IXI_XCPT		(0x00100000) // Bus Matrix IXI exception
	#define BMX_ICD_XCPT		(0x00080000) // Bus Matrix ICD exception
	#define BMX_DMA_XCPT		(0x00040000) // Bus Matrix DMA exception
	#define BMX_DS_XCPT			(0x00020000) // Bus Matrix DS exception
	#define BMX_IS_XCPT			(0x00010000) // Bus Matrix IS exception



#define mBMXEnableIxiExpt()			mBMXEnableXcpts(BMX_IXI_XCPT)
#define mBMXDisableIxiExpt()		mBMXDisableXcpts(BMX_IXI_XCPT)

#define mBMXEnableIcdExpt()			mBMXEnableXcpts(BMX_ICD_XCPT)
#define mBMXDisableIcdExpt()		mBMXDisableXcpts(BMX_ICD_XCPT)

#define mBMXEnableDmaExpt()			mBMXEnableXcpts(BMX_DMA_XCPT)
#define mBMXDisableDmaExpt()		mBMXDisableXcpts(BMX_DMA_XCPT)

#define mBMXEnableCpuDExpt()		mBMXEnableXcpts(BMX_DS_XCPT)
#define mBMXDisableCpuDExpt()		mBMXDisableXcpts(BMX_DS_XCPT)

#define mBMXEnableCpuIExpt()		mBMXEnableXcpts(BMX_IS_XCPT)
#define mBMXDisableCpuIExpt()		mBMXDisableXcpts(BMX_IS_XCPT)

#define mBMXEnablePfmCheDma()		(BMXCONSET = BMX_CHE_DMA)
#define mBMXDisablePfmCheDma()		(BMXCONCLR = BMX_CHE_DMA)
	// Program Flash Cacheability for DMA accesses
	#define BMX_CHE_DMA			(0x04000000)


/*********************************************************************
 * Macro:			mSetFlashUserPartition (USER_FLASH_PGM_SZ)
 *
 * PreCondition:    None
 * Input:			USER_FLASH_PGM_SZ - Partition Size in Bytes for user mode Program in Flash
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The macro initializes the Base Address registers for partinioning
 *					the on chip Flash.  The Flash can be divided into 2 partition.  By default
 *					the entire Flash is mapped to Kernel mode program space.  If this macro
 *					is called with a non-zero value, the total Flash size minus this value
 *					(user mode program size) is assigned to the Kernel mode program space in Flash.
 *
 * Note:            None.
 ********************************************************************/
#define mBMXSetFlashUserPartition(USER_FLASH_PGM_SZ)	(BMXPUPBA =(USER_FLASH_PGM_SZ)?(BMXPFMSZ-(USER_FLASH_PGM_SZ)):0)

/*******************************************************************
  * <combinewith mBMXSetRAMUserDataOffset, mBMXSetRAMUserProgOffset>
  * 
  * Prototype:
  *     mBMX_RAM_Setxx (Offset)
  * Preconditions:
  *     None
  * Input:
  *     offset :  Offset into RAM address range
  * Return:
  *     None
  *     
  * Side Effects:
  *     None
  * Remarks:
  *     These macros set the BMX base address registers for RAM
  *     partitioning. Please refer to the Memeory organization
  *     chapter in datasheet and PIC32 Family reference manual to
  *     calculate the value of the offset.
  * Note:
  *     None.                                                       
  ******************************************************************
*/
#define mBMXSetRAMKernProgOffset(offset)	(BMXDKPBA = (offset))
#define mBMXSetRAMUserDataOffset(offset)	(BMXDUDBA = (offset))
#define mBMXSetRAMUserProgOffset(offset)	(BMXDUPBA = (offset))

#endif /*BMX_H_*/

