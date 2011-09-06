/******************************************************************************
 *
 *                  PMP (Parallel Master Port) Library definitions
 *
 ******************************************************************************
 * FileName:        pmp.h
 * Dependencies:	p32xxxx.h, int.h
 * Processor:       PIC32
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc..
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC32MX Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PIC32MX Microcontroller products.
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
 * $Id: PMP.h,v 1.4 2006/11/15 21:22:46 C11842 Exp $
 *
 * $Name:  $
 *
 *****************************************************************************/
#ifndef PMP_H
#define PMP_H

#include <p32xxxx.h>
#include <peripheral/int.h>

typedef enum {BUF0, BUF1, BUF2, BUF3}BUFFER ;

/******************************************************************************
 * Parallel Master Port General Purpose macros
 *
 * Macros:
 *          To enable/disable module's opeation when cpu is in IDLE mode
 *                  mPMPIdleStop(void)
 *                  mPMPIdleContinue(void)
 *
 *          To enable/disable PMP module
 *                  mPMPEnable(void)
 *                  mPMPDisable(void)
 *
 *          To check if Master Mode I,II read/write is busy
 *                  mPMPGetBusyFlag(void)
 *                  mPMPIsPMPBusy(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Example:         mIsPMPBusy();
 *
 *****************************************************************************/
#define mPMPIdleStop()                          (PMCONSET = _PMCON_SIDL_MASK)
#define mPMPIdleContinue()                      (PMCONCLR = _PMCON_SIDL_MASK)
#define mPMPEnable()                            (PMCONSET = _PMCON_ON_MASK)
#define mPMPDisable()                           (PMCONCLR = _PMCON_ON_MASK)
#define mPMPGetBusyFlag()                       (PMMODEbits.BUSY)
#define mIsPMPBusy()                            (PMMODEbits.BUSY)

/******************************************************************************
 * Parallel Master Port Open Function
 *
 * Function:        void PMPOpen(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int)
 *
 * PreCondition:    None
 *
 * Input:           Bit-wise OR value of defined bit-masks
 *                  Argument #1 control defines
 *                  Argument #2 mode defines
 *                  Argument #3 port defines
 *                  Argument #4 interrupt defines
 *						- see below
 *
 * Note:            An absent symbol assumes corresponding bit(s)
 *					are disabled, or default value, and will be set = 0.
 *
 * Output:          None
 *
 * Example:
 * #define CONTROL  (PMP_ON | PMP_IDLE_CON | PMP_MUX_DATA8_LOWER | PMP_READ_WRITE_EN | \
 *                  PMP_CS2_CS1_EN | PMP_LATCH_POL_HI | PMP_CS2_POL_LO | PMP_CS1_POL_LO |\
 *                  PMP_WRITE_POL_LO | PMP_READ_POL_LO)
 *
 * #define MODE     (PMP_IRQ_OFF | PMP_AUTO_ADDR_OFF | PMP_DATA_BUS_8 | PMP_MODE_MASTER2 |\
 *                  PMP_WAIT_BEG_3 | PMP_WAIT_MID_7 | PMP_WAIT_END_3 )
 *
 * #define PORT     (PMP_PEN_ALL)
 *
 * #define INT      (PMP_INT_OFF)
 *
 *                  PMPOpen(CONTROL, MODE, PORT, INT);
 *
 ******************************************************************************/
#define mPMPOpen(control, mode, port, interrupt)\
(\
    PMCON = (control), PMMODE = (mode), PMAEN = (port), mPMPClearIntFlag(),\
	mPMPSetIntPriority(((interrupt) & 7)), mPMPSetIntSubPriority((((interrupt)>> 4) & 3)),\
	mPMPIntEnable(((interrupt) >> 15))\
)

	/******************************************************************************
	 * Available options for control parameter
	 *****************************************************************************/
		// On/off control - values are mutually exclusive
		#define PMP_ON  					        (1 << _PMCON_ON_POSITION)		/* Configure PMP enabled */
		#define PMP_OFF								(0)								/* Default */

		/* STOP DURING IDLE control - values are mutually exclusive */
		#define PMP_IDLE_CON                        (0)								/* Operate during IDLE  - default */
		#define PMP_IDLE_STOP						(1 << _PMCON_SIDL_POSITION)

		/* PMP Address multiplexing mode - values are mutually exclusive */
		#define PMP_MUX_DATA16_ALL                  (3 << _PMCON_ADRMUX_POSITION)	/* Configure 11 = All 16-bits addrs muxed on 16-bit data */
		#define PMP_MUX_DATA8_ALL			        (2 << _PMCON_ADRMUX_POSITION)	/* Configure 10 = All 16-bits addrs muxed on 8-bit data */
		#define PMP_MUX_DATA8_LOWER			        (1 << _PMCON_ADRMUX_POSITION)	/* Configure 01 = Lower 8-bits addrs muxed on 8-bit data */
		#define PMP_MUX_OFF							(0)								/* Default */

		/* PMP Input buffer type  - values are mutually exclusive */
		#define PMP_TTL								(1 << _PMCON_PMPTTL_POSITION)	/* Configure 1 = TTL inputs */
		#define PMP_ST								(0)								/* Configure 0 = Schmidt Trigger inputs - default */

		/* Read and Write Strobes enables - values are mutually exclusive */
		#define PMP_READ_WRITE_EN    		        (3 << _PMCON_PTRDEN_POSITION)	/* Configure RD, RD/WR strobe = ON; WR, WR/ENB strobe = ON */
		#define PMP_WRITE_EN    			        (2 << _PMCON_PTRDEN_POSITION)	/* Configure WR, WR/ENB strobe = ON */
		#define PMP_READ_EN     			        (1 << _PMCON_PTRDEN_POSITION)	/* Configure RD, RD/WR strobe = ON */
		#define PMP_READ_WRITE_OFF					(0)								/* Default */

		/* Chip select control - values are mutually exclusive */
		#define PMP_CS2_CS1_EN				        (1 << _PMCON_CSF1_POSITION)		/* Configure 10 = CS1 and CS2 are chip selects */
		#define PMP_CS2_EN    						(1 << _PMCON_CSF0_POSITION)		/* Configure 01 = CS2 = chip select, CS1 = A14 */
		#define PMP_CS2_CS1_OFF						(0)								/* Configure 00 = CS2 = A15, CS1 = A14  - default */

		/* PMP Address latch control - values are mutually exclusive */
		#define PMP_LATCH_POL_HI			        (1 << _PMCON_ALP_POSITION)		/* Configure PMALL, PMALH = active high */
		#define PMP_LATCH_POL_LO			        (0)								/* Configure PMALL, PMALH = active low - default */

		/* CS polarity control - values are mutually exclusive */
		#define PMP_CS2_POL_HI						(1 << _PMCON_CS2P_POSITION)		/* Configure CS2 polarity = active high */
		#define PMP_CS2_POL_LO						(0)								/* Configure CS2 polarity = active low - default */
		#define PMP_CS1_POL_HI						(1 << _PMCON_CS1P_POSITION)		/* Configure CS1 polarity = active high */
		#define PMP_CS1_POL_LO						(0)								/* Configure CS1 polarity = active low - default */

		/* RD/RW/WR/ENB POLARITY bit control - values are mutually exclusive */
		#define PMP_WRITE_POL_HI			        (1 << _PMCON_WRSP_POSITION)		/* Configure Write/ENB strobe polarity = active high */
		#define PMP_WRITE_POL_LO			        (0)								/* Configure Write/ENB strobe polarity = active low - default */
		#define PMP_READ_POL_HI	    		        (1 << _PMCON_RDSP_POSITION)		/* Configure Read/RW strobe polarity = active high */
		#define PMP_READ_POL_LO				        (0)								/* Configure Read/RW strobe polarity = active low */


	/******************************************************************************
	 * Available options for mode parameter
	 *****************************************************************************/
		/* PMP interrupt mode - values are mutually exclusive */
		#define PMP_IRQ_BUF_FULL                    (2 << _PMMODE_IRQM_POSITION)	/* Configure Interrupt on buffer full */
		#define PMP_IRQ_READ_WRITE                  (1 << _PMMODE_IRQM_POSITION)	/* Configure Interrupt at end of R/W cycle */
		#define PMP_IRQ_OFF							(0)

		/* Auto Increment/Decrement FUNCTION SELECTION BITS configuration bit mask defines - values are mutually exclusive */
		#define PMP_AUTO_ADDR_BUFFER		        (3 << _PMMODE_INCM_POSITION)	/* Configure 11 = SLAVE R/W buffers auto increment */
		#define PMP_AUTO_ADDR_DEC   		        (2 << _PMMODE_INCM_POSITION)	/* Configure 10 = Addrs decrements on every R/W cycle */
		#define PMP_AUTO_ADDR_INC	    	        (1 << _PMMODE_INCM_POSITION)	/* Configure 01 = Addrs increments on every R/W cycle */
		#define PMP_AUTO_ADDR_OFF					(0)

		/* MODE16/8 FUNCTION BITS configuration bit mask defines - values are mutually exclusive */
		#define PMP_DATA_BUS_16			        	(1 << _PMMODE_MODE16_POSITION)	/* Configure 16-bit data mode */
		#define PMP_DATA_BUS_8			        	(0)								/* Configure 8-bit data mode (default)*/

		/* Master/Slave MODE FUNCTION SELECTION BITS configuration bit mask defines - values are mutually exclusive */
		#define PMP_MODE_MASTER1			        (3 << _PMMODE_MODE_POSITION)	/* Configure MASTER mode 1 */
		#define PMP_MODE_MASTER2			        (2 << _PMMODE_MODE_POSITION)	/* Configure MASTER modw 2 */
		#define PMP_MODE_ESLAVE     		        (1 << _PMMODE_MODE_POSITION)	/* Configure SLAVE enhanced mode */
		#define PMP_MODE_SLAVE				        (0)								/* Configure SLAVE mode */

		/* PMP Beginning phase wait states - values are mutually exclusive */
		#define PMP_WAIT_BEG_4				        (3 << _PMMODE_WAITB_POSITION)	/* Configure 4 Tpb WAIT */
		#define PMP_WAIT_BEG_3				        (2 << _PMMODE_WAITB_POSITION)	/* Configure 3 Tpb WAIT */
		#define PMP_WAIT_BEG_2				        (1 << _PMMODE_WAITB_POSITION)	/* Configure 2 Tpb WAIT */
		#define PMP_WAIT_BEG_1				        (0)								/* Configure 1 Tpb WAIT */

		/* PMP Middle phase wait states - values are mutually exclusive */
		#define PMP_WAIT_MID_15				        (15 << _PMMODE_WAITM_POSITION)	/* Configure 3 Tpb WAIT */
		#define PMP_WAIT_MID_14				        (14 << _PMMODE_WAITM_POSITION)	/* Configure 2 Tpb WAIT */
		#define PMP_WAIT_MID_13				        (13 << _PMMODE_WAITM_POSITION)	/* Configure 1 Tpb WAIT */
		#define PMP_WAIT_MID_12				        (12 << _PMMODE_WAITM_POSITION)	/* Configure 4 Tpb WAIT */
		#define PMP_WAIT_MID_11				        (11 << _PMMODE_WAITM_POSITION)	/* Configure 3 Tpb WAIT */
		#define PMP_WAIT_MID_10				        (10 << _PMMODE_WAITM_POSITION)	/* Configure 2 Tpb WAIT */
		#define PMP_WAIT_MID_9				        (9 << _PMMODE_WAITM_POSITION)	/* Configure 1 Tpb WAIT */
		#define PMP_WAIT_MID_8				        (8 << _PMMODE_WAITM_POSITION)	/* Configure 4 Tpb WAIT */
		#define PMP_WAIT_MID_7				        (7 << _PMMODE_WAITM_POSITION)	/* Configure 3 Tpb WAIT */
		#define PMP_WAIT_MID_6				        (6 << _PMMODE_WAITM_POSITION)	/* Configure 2 Tpb WAIT */
		#define PMP_WAIT_MID_5				        (5 << _PMMODE_WAITM_POSITION)	/* Configure 1 Tpb WAIT */
		#define PMP_WAIT_MID_4				        (4 << _PMMODE_WAITM_POSITION)	/* Configure 4 Tpb WAIT */
		#define PMP_WAIT_MID_3				        (3 << _PMMODE_WAITM_POSITION)	/* Configure 3 Tpb WAIT */
		#define PMP_WAIT_MID_2				        (2 << _PMMODE_WAITM_POSITION)	/* Configure 3 Tpb WAIT */
		#define PMP_WAIT_MID_1				        (1 << _PMMODE_WAITM_POSITION)	/* Configure 2 Tpb WAIT */
		#define PMP_WAIT_MID_0				        (0)								/* Configure 1 Tpb WAIT */

		/* PMP end phase wait states - values are mutually exclusive  */
		#define PMP_WAIT_END_4				        (3 << _PMMODE_WAITE_POSITION)	/* Configure 4 Tpb WAIT */
		#define PMP_WAIT_END_3				        (2 << _PMMODE_WAITE_POSITION)	/* Configure 3 Tpb WAIT */
		#define PMP_WAIT_END_2				        (1 << _PMMODE_WAITE_POSITION)	/* Configure 2 Tpb WAIT */
		#define PMP_WAIT_END_1				        (0 << _PMMODE_WAITE_POSITION)	/* Configure 1 Tpb WAIT */


	/******************************************************************************
	 * Available options for port parameter
	 *****************************************************************************/
		/* PMP Port enable control- values are mutually exclusive  */
		#define PMP_PEN_ALL					        (0xFFFF)						/* Enable All PMA and PMCS PINS*/
		#define PMP_PEN_15							(1 << _PMAEN_PTEN15_POSITION)	/* Enable Addrs PIN 15 */
		#define PMP_PEN_14					        (1 << _PMAEN_PTEN14_POSITION)	/* Enable Addrs PIN 14 */
		#define PMP_PEN_13					        (1 << _PMAEN_PTEN13_POSITION)	/* Enable Addrs PIN 13 */
		#define PMP_PEN_12					        (1 << _PMAEN_PTEN12_POSITION)	/* Enable Addrs PIN 12 */
		#define PMP_PEN_11					        (1 << _PMAEN_PTEN11_POSITION)	/* Enable Addrs PIN 11 */
		#define PMP_PEN_10					        (1 << _PMAEN_PTEN10_POSITION)	/* Enable Addrs PIN 10 */
		#define PMP_PEN_9					        (1 << _PMAEN_PTEN9_POSITION)	/* Enable Addrs PIN 9 */
		#define PMP_PEN_8					        (1 << _PMAEN_PTEN8_POSITION)	/* Enable Addrs PIN 8 */
		#define PMP_PEN_7					        (1 << _PMAEN_PTEN7_POSITION)	/* Enable Addrs PIN 7 */
		#define PMP_PEN_6					        (1 << _PMAEN_PTEN6_POSITION)	/* Enable Addrs PIN 6 */
		#define PMP_PEN_5					        (1 << _PMAEN_PTEN5_POSITION)	/* Enable Addrs PIN 5 */
		#define PMP_PEN_4					        (1 << _PMAEN_PTEN4_POSITION)	/* Enable Addrs PIN 4 */
		#define PMP_PEN_3					        (1 << _PMAEN_PTEN3_POSITION)	/* Enable Addrs PIN 3 */
		#define PMP_PEN_2					        (1 << _PMAEN_PTEN2_POSITION)	/* Enable Addrs PIN 2 */
		#define PMP_PEN_1					        (1 << _PMAEN_PTEN1_POSITION)	/* Enable Addrs PIN 1 */
		#define PMP_PEN_0					        (1 << _PMAEN_PTEN0_POSITION)	/* Enable Addrs PIN 0 */
		#define PMP_PEN_OFF                         (0)								/* Disable all */


	/******************************************************************************
	 * Available options for interrupt parameter
	 *****************************************************************************/
		// PMP interrupt control - values are mutually exclusive
		#define PMP_INT_ON	        				(1 << 15)						/* Interrupt enable/disable bit */
		#define PMP_INT_OFF    						(0)								/* Interrupt flag position */

		// PMP interrupt priority - values are mutually exclusive
		#define PMP_INT_PRI_7					    (7)								/* Interrupt Priority 7 */
		#define PMP_INT_PRI_6					    (6)								/* Interrupt Priority 6 */
		#define PMP_INT_PRI_5					    (5)								/* Interrupt Priority 5 */
		#define PMP_INT_PRI_4					    (4)								/* Interrupt Priority 4 */
		#define PMP_INT_PRI_3					    (3)								/* Interrupt Priority 3 */
		#define PMP_INT_PRI_2					    (2)								/* Interrupt Priority 2 */
		#define PMP_INT_PRI_1					    (1)								/* Interrupt Priority 1 */
		#define PMP_INT_PRI_0				    	(0)								/* Interrupt Priority 0 */

		// PMP interrupt sub-priority - values are mutually exclusive
		#define PMP_INT_SUB_PRI_3			        (3 << 4)						/* Interrupt Sub-Priority 3 */
		#define PMP_INT_SUB_PRI_2					(2 << 4)						/* Interrupt Sub-Priority 2 */
		#define PMP_INT_SUB_PRI_1					(1 << 4)						/* Interrupt Sub-Priority 1 */
		#define PMP_INT_SUB_PRI_0					(0 << 4)						/* Interrupt Sub-Priority 0 */
	/***********************************
	 * End parameter values
	 ************************************/


/******************************************************************************
 * Parallel Master Port Close Function
 *
 * Macro:           void PMPClose(void)
 *
 * Description:		Disables PMP module, clears PMP interrupt enable and PMP
 *                  interrupt flag.
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			PMPClose();
 *
 *****************************************************************************/
#define mPMPClose()     (    mPMPIntEnable(0), mPMPDisable(), mPMPClearIntFlag())


/******************************************************************************
 * Parallel Master Port Set Address Function
 *
 * Function:        PMPSetAddress(unsigned short)
 *
 * PreCondition:    None
 *
 * Input:           (unsigned short) addrs
 *
 * Output:          None
 *
 * Example:         PMPSetAddress(0x4800);
 *
 * Note             Copies argument #1 into the PMADDR register.
 *          		Use in MASTER mode 1 or 2, MODE[1:0] = 10, 11
 *****************************************************************************/
extern inline void __attribute__((always_inline)) PMPSetAddress(unsigned int addrs)
{
    while(mIsPMPBusy());
    PMADDR = addrs;
}
/******************************************************************************
 * Parallel Master Port Read Byte Macro
 *
 * Macro:	        mPMPMasterReadByte ()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          (unsigned char) value
 *
 * Example:         value = mPMPMasterReadByte();
 *
 * Note:            This macro calls function PMPMasterRead() and casts return
 *					value = unsigned char
 *
 *****************************************************************************/
#define mPMPMasterReadByte()             ((unsigned char) PMPMasterRead())


/******************************************************************************
 * Parallel Master Port Read Word Macro
 *
 * Macro:	        mPMPMasterReadWord ()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          (unsigned short) value
 *
 * Example:         value = mPMPMasterReadWord();
 *
 * Note:            This macro calls function PMPMasterRead() and casts return
 *					value = unsigned word
 *
 *****************************************************************************/
#define mPMPMasterReadWord()             ((unsigned short) PMPMasterRead())


/******************************************************************************
 * Parallel Master Port Master mode I,II Read Function
 *
 * Function:        unsigned int PMPMasterRead(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          (unsigned int)
 *
 * Example:         value = PMPMasterRead();
 *
 * Note:            Returns the current contents of PMDIN register
 *
 *					Note 1: This function is blocking while the PMMODE busy flag
 *					is being polled.
 *
 *					Note 2: Due to the architecture of the PMP module, the data
 *					obtained from the PMDIN register is actually the latched value
 *					from the previous read operation.  Refer to the PIC32MX Family
 *					Reference Manual for further details regarding this behavior.
 *
 *					Note 3: Depending on the PMP mode, the data could be 8-bit or 16-bit.
 *					However, the value returned is always 32-bits wide (unsigned int).
 *					For example, in 8-bit mode, a value of 0xFF read from an external
 *					device will be returned from this function as 0x000000FF.
 *					Likewise, in 16-bit mode, a value of 0xFFFF read from an external
 *					device will be returned as 0x0000FFFF.
 *
 *					Note 3: Use macros mPMPMasterReadWord or mPMPMasterReadByte to
 *					provide a return value cast to the appropriate size.
 *					mPMPMasterReadWord and mPMPMasterReadByte call PMPMasterRead().
 *
 *      			Use in MASTER mode 1 or 2, MODE[1:0] = 10, 11
 *****************************************************************************/
extern inline unsigned int __attribute__((always_inline)) PMPMasterRead(void)
{
	while(mIsPMPBusy());
	return(PMDIN);
}


/******************************************************************************
 * Parallel Master Port Read a block of bytes (8-bit)
 *
 * Function:        void PMPMasterReadByteBlock(unsigned int, unsigned int,
 *                                              unsigned char*)
 *
 * PreCondition:    None
 *
 * Input:           Argument #1 (unsigned int) addrs = starting address
 *                  Argument #2 (unsigned int) bytes = number of bytes to read
 *                  Argument #3 (unsigned char*) pDest = byte data destination
 *
 * Output:          None
 *
 * Example:         PMPMasterReadByteBlock(0x6400, 32, &myArray);
 *
 * Note:            Reads N bytes (argument #2) starting at location specified
 *                  in (argument #1) and stores the data at destination
 *                  specified by byte pointer (argument #3)
 *
 *                  Use in MASTER mode 1 or 2, MODE[1:0] = 10, 11
 *****************************************************************************/
void PMPMasterReadByteBlock(unsigned int addrs, unsigned int bytes, unsigned char* pDest);


/******************************************************************************
 * Parallel Master Port Read a block of words (16-bit)
 *
 * Function:        void PMPMasterReadWordBlock(unsigned int, unsigned int,
 *                                              unsigned short*)
 *
 * PreCondition:    None
 *
 * Input:           Argument #1 (unsigned int) addrs = starting address
 *                  Argument #2 (unsigned int) words = number of words to read
 *                  Argument #3 (unsigned short*) pDest = word data destination
 *
 * Output:          None
 *
 * Example:         PMPMasterReadWordBlock(0x6400, 16, &myArray);
 *
 * Note:            Reads N words (argument #2) starting at location specified
 *                  in (argument #1) and stores the data at destination
 *                  specified by byte pointer (argument #3)
 *
 *                  Use in MASTER mode 1 or 2, MODE[1:0] = 10, 11
 *****************************************************************************/
void PMPMasterReadWordBlock(unsigned int addrs, unsigned int words, unsigned short* pDest);


/******************************************************************************
 * Parallel Master Port Master mode I,II Write Function
 *
 * Function:        void PMPMasterWrite(unsigned int)
 *
 * PreCondition:    None
 *
 * Input:           Argument #1 (unsigned int) value to be written to PMDIN register
 *
 * Output:          None
 *
 * Example:         PMPMasterWrite(0xAA);
 *
 * Note:    		In 8-bit data mode, the 8-bits of data appear on the lower 8
 *					data lines while the upper 8-bits are not used.
 *					In 16-bit data mode, the lower 8-bits appear on the lower 8
 *					data lines and the upper 8-bits of data appear on the upper
 *					8 data lines.
 *
 *					Note 1: This function is blocking while the PMMODE busy flag
 *					is being polled.
 *
 *      			Use in MASTER mode 1 or 2, MODE[1:0] = 10, 11
 *****************************************************************************/
extern inline void __attribute__((always_inline)) PMPMasterWrite(unsigned short value)
{
	while(mIsPMPBusy());
	PMDIN = value;
}


/******************************************************************************
 * Parallel Master Port Write a block of bytes (8-bit)
 *
 * Function:        void PMPMasterWriteByteBlock(unsigned int, unsigned int,
 *                                               unsigned char*)
 *
 * PreCondition:    None
 *
 * Input:           Argument #1 (unsigned int) addrs = starting address
 *                  Argument #2 (unsigned int) bytes = number of bytes to read
 *                  Argument #3 (unsigned char*) source = byte data destination
 *
 * Output:          None
 *
 * Example:         PMPMasterWriteByteBlock(0x8000, 0x800, &myArray);
 *
 * Overview:        Writes N bytes (argument #2) starting at location specified
 *                  in (argument #1), from the destination specified by
 *                  byte pointer (argument #3)
 *
 * Note:            Use in MASTER mode 1 or 2, MODE[1:0] = 10, 11
 *****************************************************************************/
void PMPMasterWriteByteBlock(unsigned int addrs, unsigned int bytes, unsigned char* source);


/******************************************************************************
 * Parallel Master Port Write a block of words (16-bit)
 *
 * Function:        void PMPMasterWriteWordBlock(unsigned int, unsigned int,
 *                                               unsigned short*)
 *
 * PreCondition:    None
 *
 * Input:           Argument #1 (unsigned int) addrs = starting address
 *                  Argument #2 (unsigned int) words = number of words to write
 *                  Argument #3 (unsigned char*) source = word data destination
 *
 * Output:          None
 *
 * Example:         PMPMasterWriteWordBlock(0x8000, 16, &myArray);
 *
 * Note:            Writes N words (argument #2) starting at location specified
 *                  in (argument #1), from the destination specified by
 *                  word pointer (argument #3).
 *
 *                  Use in MASTER mode 1 or 2, MODE[1:0] = 10, 11
 *****************************************************************************/
void PMPMasterWriteWordBlock(unsigned int addrs, unsigned int words, unsigned short* source);


/******************************************************************************
 * Parallel Master Port Read Slave Buffer Function
 *
 * Function:        unsigned int PMPSlaveReadBuffer(enum BUFFER)
 *
 * PreCondition:    None
 *
 * Input:           (enum BUFFER) 0..3
 *
 * Output:          The value in selected buffer register.
 *
 * Example:         value = PMPSlaveReadBuffer(BUF0);
 *
 * Note:            Reads the value in PMDIN register.
 *
 *                  Use in SLAVE BUFFERED mode, MODE[1:0] = 00 and INCM[1:0]=11
 *					or SLAVE ENHANCED mode, MODE[1:0] = 01
 *****************************************************************************/
unsigned char PMPSlaveReadBuffer(BUFFER);


/******************************************************************************
 * Parallel Master Port Read Enhanced Slave Buffers Function
 *
 * Function:        void PMPSlaveReadBuffers(unsigned char*)
 *
 * PreCondition:    None
 *
 * Input:           (unsigned char* ) pointer to destination array
 *
 * Output:          The contents of the (4) 8-bit slave buffer registers.
 *
 * Example:         PMPSlaveReadBuffers(&myArray);
 *
 * Note:            Copies 4 bytes from DATAIN buffers to a starting location
 *					pointed to by input parameter.
 *
 *                  Use in SLAVE BUFFERED mode, MODE[1:0] = 00 and INCM[1:0]=11
 *					or SLAVE ENHANCED mode, MODE[1:0] = 01
 *****************************************************************************/
void PMPSlaveReadBuffers(unsigned char* pDest);


/******************************************************************************
 * Parallel Master Port Write Slave Buffer Function
 *
 * Function:        void PMPSlaveWriteBuffer(enum BUFFER, unsigned char)
 *
 * PreCondition:    None
 *
 * Input:           Argument #1 (enum BUFFER) = 0..3
 *                  Argument #2 (unsigned char) = value to be written
 *
 * Output:          None
 *
 * Example:         PMPSlaveWriteBuffer(BUF2, 0x88);
 *
 * Note:            Writes the desired value into the selected output buffer.
 *                  This function does not check or modify the OBUF bit and
 *                  therefore it is the user's responsibility to check for
 *                  an overflow condition.
 *
 *                  Use in SLAVE BUFFERED mode, MODE[1:0] = 00
 *					or SLAVE ENHANCED mode, MODE[1:0] = 00  and INCM[1:0]=11
 *****************************************************************************/
void PMPSlaveWriteBuffer(BUFFER, unsigned char value);



/******************************************************************************
 * Parallel Master Port Write Enhanced Slave Buffers Function
 *
 * Function:        void PMPSlaveWriteBuffers(unsigned char*)
 *
 * PreCondition:    None
 *
 * Input:           (unsigned char*) source = pointer to data
 *
 * Output:          None
 *
 * Example:         PMPSlaveWriteBuffers(&myArray);
 *
 * Note:            Copies 4 bytes, addressed by the pointer argument #1, into
 *					the corresponding PMDOUT registers.
 *
 *                  Use in SLAVE BUFFERED mode, MODE[1:0] = 00
 *					or SLAVE ENHANCED mode, MODE[1:0] = 00  and INCM[1:0]=11
 *****************************************************************************/
void PMPSlaveWriteBuffers(unsigned char* source);


/******************************************************************************
 * Parallel Master Port Read Slave Macro
 *
 * Macro:	        mPMPSlaveRead ()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          8-bit value in slave buffer register
 *
 * Example:         value = mPMPSlaveRead();
 *
 * Note:            Reads the value in PMDIN register
 *
 *					Note 1: This macro does not check the status of the
 *					PMSTAT.IBF (input buffer full) bit prior to reading the
 *					PMDIN register.  It is recommended that the user's software
 *					verify PMSTAT.IBF = 1 prior to reading the PMDIN register.
 *
 *		            Note 2: If an external master write occurs before the current
 *					contents of the PMDIN register is performed, the IBOV flag
 *					will be set, indicating an overflow.  This function does
 *					not check or modify the IBOV bit.  Therefore it should the
 *					user's responsibility to check for an overflow condition.
 *
 *					Use in SLAVE LEGACY mode, MODE[1:0] = 00
 *****************************************************************************/
#define mPMPSlaveRead()             (PMDIN)

/******************************************************************************
 * Parallel Master Port Slave Write Macro
 *
 * Macro:	        mPMPSlaveWrite(unsigned char)
 *
 * PreCondition:    None
 *
 * Input:           (unsigned char) _value
 *
 * Output:          None
 *
 * Example:         mPMPSlaveWrite(0x20);
 *
 * Note:            Writes argument #1 into PMDOUT register.
 *
 *					Note 1: This function does not check the status of the
 *					PMSTAT.OBE (output buffer empty) bit prior to writing to the
 *					PMDOUT register.  It is recommended that the user's software
 *					verify PMSTAT.OBE = 1 prior to writing the PMDOUT register.
 *
 *					Use in SLAVE LEGACY mode, MODE[1:0] = 00
 *****************************************************************************/
#define mPMPSlaveWrite(_value)              (PMDOUT = (unsigned char) (_value))


/******************************************************************************
 * Parallel Master Port Slave mode general purpose macros
 *
 * Macros:
 *          To read Slave Output Buffer Empty Flags
 *                  mIsPMPSlaveBufferEmpty(void)
 *                  mPMPGetBufferEmptyFlags((enum BUFFER) _buffer)
 *
 *          To read Slave Input Buffer Full Flags
 *                  mIsPMPSlaveBufferFull(void)
 *                  mPMPGetBufferFullFlags((enum BUFFER) _buffer)
 *
 *          To read/clear Slave Output Buffer Underflow Flags
 *                  mIsPMPSlaveBufferUnderflow(void)
 *                  mPMPClearBufferUnderflow(void)
 *
 *          To read/clear Slave Input Buffer Overflow Flags
 *                  mIsPMPSlaveBufferOverflow(void)
 *                  mPMPClearBufferOverflow(void)
 *
 * PreCondition:    None
 *
 * Input:           Depends
 *
 * Output:          None
 *
 * Example:         mPMPClearBufferOverflowFlag();
 *
 *                  Use in SLAVE BUFFERED mode, MODE[1:0] = 00 and INCM[1:0]=11
 *					or SLAVE ENHANCED mode, MODE[1:0] = 01
 *****************************************************************************/
#define	mIsPMPSlaveBufferFull()                 (PMSTATbits.IBF)
#define mPMPGetBufferFullFlags(_buffer)         ((PMSTAT & (1 << ((BUFFER) (_buffer) + 8)))\
												>> ((BUFFER) (_buffer) + 8))
#define mIsPMPSlaveBufferOverflow()				(PMSTATbits.IBOV)
#define mPMPClearBufferOverflow()			    (PMSTATCLR = _PMSTAT_IBOV_MASK)

#define	mIsPMPSlaveBufferEmpty()                (PMSTATbits.OBE)
#define mPMPGetBufferEmptyFlags(_buffer)        ((PMSTAT & (1 << (BUFFER )(_buffer)))\
												>> (BUFFER) (_buffer))
#define mIsPMPSlaveBufferUnderflow()			(PMSTATbits.OBUF)
#define	mPMPClearBufferUnderflow()		    	(PMSTATCLR = _PMSTAT_OBUF_MASK)

#endif
// END OF PMP.H

