/*********************************************************************
 *
 *                  NVM Library definitions
 *
 *********************************************************************
 * FileName:        NVM.h
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
 * $Id: NVM.h,v 1.1 2006/10/16 20:30:29 C10737 Exp $
 * $Name: $
 *
 ********************************************************************/
#ifndef _NVM_H_
#define _NVM_H_

#include <p32xxxx.h>
#include <peripheral/int.h>
#include <sys/kmem.h>

#define PAGE_SIZE               1024        // # of 32-bit Instructions per Page
#define BYTE_PAGE_SIZE          (4 * PAGE_SIZE) // Page size in Bytes
#define ROW_SIZE                128         // # of 32-bit Instructions per Row
#define BYTE_ROW_SIZE           (4 * ROW_SIZE) // # Row size in Bytes
#define NUM_ROWS_PAGE           8              //Number of Rows per Page 

/*********************************************************************
 * Function:        unsigned int NVMProgram(void* address, const void* data, unsigned int size void * pagebuff)
 *
 * Description:     Programs size characters from the source buffer to
 *                  Flash memory starting at the destination address.
 *
 * PreCondition:    None
 *
 * Inputs:			address:  Destination address to start writing from.
 *                  data:  Location of data to write.
 *                  size:  Number of bytes to write.
 *                  pagebuff:   Ram buffer to preserve 1 page worth of data
 *
 * Output:          '0' if operation completed successfully.
 *
 * Example:			NVMProgram((void*) 0xBD000000, (const void*) 0xA0000000, 1024, (void *) 0xA0002000)
 ********************************************************************/
unsigned int NVMProgram(void * address, const void * data, unsigned int size, void* pagebuff);

/*********************************************************************
 * Function:        unsigned int NVMWriteWord(void* address, unsigned int data)
 *
 * Description:     The smallest block of data that can be programmed in
 *                  a single operation is 1 instruction word (4 Bytes).  The word at
 *                  the location pointed to by NVMADDR is programmed.
 *
 * PreCondition:    None
 *
 * Inputs:          address:   Destination address to write.
 *                  data:      Word to write.
 *
 * Output:          '0' if operation completed successfully.
 *
 * Example:         NVMWriteWord((void*) 0xBD000000, 0x12345678)
 ********************************************************************/
unsigned int NVMWriteWord(void* address, unsigned int data);

/*********************************************************************
 * Function:        unsigned int NVMWriteRow(void* address, void* data)
 *
 * Description:		The largest block of data that can be programmed in
 *                  a single operation is 1 row 128 instructions (512 Bytes).  The row at
 *                  the location pointed to by NVMADDR is programmed with the data buffer
 *                  pointed to by NVMSRCADDR.
 *
 * PreCondition:    The row of data must be pre-loaded into a buffer in RAM.
 *
 * Inputs:			address:  Destination Row address to write.
 *                  data:  Location of data to write.
 *
 * Output:          '0' if operation completed successfully.
 *
 * Example:			NVMWriteRow((void*) 0xBD000000, (void*) 0xA0000000)
 ********************************************************************/
unsigned int NVMWriteRow(void* address, void* data);

/*********************************************************************
 * Function:        unsigned int NVMErasePage(void* address)
 *
 * Description:		A page erase will erase a single page of program flash,
 *                  which equates to 1k instructions (4KBytes). The page to
 *                  be erased is selected using NVMADDR. The lower bytes of
 *                  the address given by NVMADDR are ignored in page selection.
 *
 * PreCondition:    None
 *
 * Inputs:			address:  Destination page address to Erase.
 *
 * Output:          '0' if operation completed successfully.
 *
 * Example:			NVMErasePage((void*) 0xBD000000)
 ********************************************************************/
unsigned int NVMErasePage(void* address);

/*********************************************************************
 * Function:        unsigned int NVMClearError(void)
 *
 * Description:     If the NVMCON error flag is set, it can only be cleared
 *                  by performing an NVM NOP opertion.
 *
 * PreCondition:    None
 *
 * Inputs:          None
 *
 * Output:          '0' if operation completed successfully.
 *
 * Example:         NMVClearError()
 ********************************************************************/
unsigned int NVMClearError(void);

/*********************************************************************
 * Function:        NVMIsError()
 *
 * Description:     Reads the NVMCON Error flags.
 *
 * PreCondition:    None
 *
 * Inputs:          None
 *
 * Output:          '0' if error flag is not set.
 *
 * Example:         if(NVMIsError())
 *                      NVMClearError();
 ********************************************************************/
#define NVMIsError()    (NVMCON & (_NVMCON_WRERR_MASK | _NVMCON_LVDERR_MASK))


#endif /*_NVM_H_*/
