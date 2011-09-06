/*********************************************************************
 *
 *                  pCache API definitions
 *
 *********************************************************************
 * FileName:        pCache.h
 * Dependencies:	p32xxxx.h
 * Processor:       PIC32MX
 *
 * Complier:        C32
 *
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
 * $Id: pCache.h,v 1.5 2006/10/23 18:07:00 C13128 Exp $
 *
 ********************************************************************/
#ifndef PCACHE_H_
#define PCACHE_H_

#include <p32xxxx.h>


/******************************************************************
  * <combinewith cheConfigure>
  * 
  * Prototype:
  *     void mCheConfigure(config)
  * Preconditions:
  *     None
  * Return:
  *     none
  * Side Effects:
  *     The pCache will be configured to the state requested by the
  *     \input fields
  * Remarks:
  *     This routine writes the checon register with the requested
  *     fields
  * Note:
  *     none                                                       
  *****************************************************************
*/
#define mCheConfigure(val) (CHECON = (val))
#define cheConfigure(checoh, dcsz, prefen, pfmws) (mCheConfigure((((checoh)<<_CHECON_CHECOH_POSITION) | \
			       		((dcsz)<<_CHECON_DCSZ_POSITION) | ((prefen)<<_CHECON_PREFEN_POSITION) | ((pfmws)<<_CHECON_PFMWS_POSITION))))

	/*****************************************************************************************************************
	  * <combinewith CHE_CONF_WS1, CHE_CONF_WS2, CHE_CONF_WS3, CHE_CONF_WS4, CHE_CONF_WS5, CHE_CONF_WS6, CHE_CONF_WS7>
	  * 
	  * Flash wait state count - Values are mutually exclusive                                                     
	  ****************************************************************************************************************
	*/
		#define CHE_CONF_WS0         (0 << _CHECON_PFMWS_POSITION)
		#define CHE_CONF_WS1         (1 << _CHECON_PFMWS_POSITION)
		#define CHE_CONF_WS2         (2 << _CHECON_PFMWS_POSITION)
		#define CHE_CONF_WS3         (3 << _CHECON_PFMWS_POSITION)
		#define CHE_CONF_WS4         (4 << _CHECON_PFMWS_POSITION)
		#define CHE_CONF_WS5         (5 << _CHECON_PFMWS_POSITION)
		#define CHE_CONF_WS6         (6 << _CHECON_PFMWS_POSITION)
		#define CHE_CONF_WS7         (7 << _CHECON_PFMWS_POSITION)

		/***************************************************************
		  * <combinewith CHE_CONF_PF_ALL, CHE_CONF_PF_C, CHE_CONF_PF_NC>
		  * 
		  * Flash Prefetch option - Values are mutually exclusive       
		  **************************************************************
		*/
		#define CHE_CONF_PF_DISABLE  (0 << _CHECON_PREFEN_POSITION)
		#define CHE_CONF_PF_C        (1 << _CHECON_PREFEN_POSITION )
		#define CHE_CONF_PF_NC       (2 << _CHECON_PREFEN_POSITION)
		#define CHE_CONF_PF_ALL      (3 << _CHECON_PREFEN_POSITION)

		/**************************************************************************
		  * <combinewith CHE_CONF_DC_1LINE, CHE_CONF_DC_2LINES, CHE_CONF_DC_4LINES>
		  * 
		  * Data-line count - Values are mutually exclusive                        
		  *************************************************************************
		*/
		#define CHE_CONF_DC_NONE     (0 << _CHECON_DCSZ_POSITION)
		#define CHE_CONF_DC_1LINE    (1 << _CHECON_DCSZ_POSITION)
		#define CHE_CONF_DC_2LINES   (2 << _CHECON_DCSZ_POSITION)
		#define CHE_CONF_DC_4LINES   (3 << _CHECON_DCSZ_POSITION)

		/********************************************************
		  * <combinewith CHE_CONF_COH_INVALL>
		  * 
		  * Cache Coherency state - Values are mutually exclusive
		  *******************************************************
		*/
		#define CHE_CONF_COH_INVUNL  (0 << _CHECON_CHECOH_POSITION)
		#define CHE_CONF_COH_INVALL  (1 << _CHECON_CHECOH_POSITION)
	/***********************************
	 * End config parameter values
	 ************************************/


/*********************************************************************
 * Function:        void mCheGetCon()
 *
 * PreCondition:    None
 * Input:           none
 * Output:          Value of the checon register
 * Side Effects:    none
 * Overview:        This routine reads the checon register
 * Note:            none
 ********************************************************************/
#define mCheGetCon() CHECON

/*********************************************************************
 * Function:        void mCheSetCacheAccessLine(unsigned int idx, unsigned int writeEnable)
 *
 * PreCondition:    None
 * Input:           idx				- Index of the cache line to access (0-15)
 * 					writeEnable		- Enables writes to the cache line data (tags, mask, data words)
 *									  ( 0 = Disable, 1 = Enable)
 * Output:          none
 * Side Effects:    Determines what cache line will be accessed by the other che* routines
 * Overview:        This routine writes the cheacc register with a cache line number.  The cache
 * 					lines are numbered 0-15.  If the writeEnable parameter is 1, then writes to
 * 					the cache-line tags, masks, and data are allowed.  If the writeEnable parameter
 * 					is 0, then only read access is granted to the tags and mask only.
 * Note:            none
 ********************************************************************/
#define mCheSetCacheAccessLine(idx, writeEnable) (CHEACC = ((idx) & 0xf) | (writeEnable ? 0x80000000 : 0))

/*********************************************************************
 * Function:        unsigned long mCheGetCacheTag()
 *
 * PreCondition:    cheSetCacheAccessLine must have been called to set up the correct
 * 					cache line index
 * Input:           none
 * Output:          returns the chetag register in the form of a structure
 * Side Effects:    none
 * Overview:        This routine reads the chetag register.
 * Note:            none
 ********************************************************************/
#define mCheGetCacheTag(lineno) (mCheSetCacheAccessLine((lineno),0), CHETAG)

/*********************************************************************
 * Function:        mCheSetCacheTag(int lineno, unsigned addr, unsigned attr)
 *
 * PreCondition:
 *
 * Input:           lineno : Index of the cache line to access (0 - 15)
 *					addr   : Physical address that corresponds to this cache line
 *					attr   : Bit-wise OR of CHE_TAG_XXXX parameter
 *
 * Output:          None
 * Side Effects:    The pCache will have a new tag written into the cache.  This could cause
 * 					the processor to prefetch a cache line for locked usage, mark a line as invalid,
 *
 * Overview:        This routine writes the chetag register with the requested fields
 * Note:            Extreme care must be taken when writing directly to a cache tag.  Improper
 * 					operation can occur if invalid combinations are written.
 ********************************************************************/
#define mCheSetCacheTag(lineno, addr, attrs) (mCheSetCacheAccessLine((lineno),1), CHETAG = (addr&0xfffffff0) | (attrs))

	/*********************************************************************************
	  * <combinewith CHE_TAG_VALID>
	  * 
	  * Line Valid tag - Values are mutually exclusive                             
	  ********************************************************************************
	*/
		#define CHE_TAG_INVALID      (0<< _CHETAG_LVALID_POSITION)
		#define CHE_TAG_VALID        (1<< _CHETAG_LVALID_POSITION)

		/**************************************************
		  * <combinewith CHE_TAG_LOCKED>
		  * 
		  * Line Locked tag - must only be one of following
		  *************************************************
		*/
		#define CHE_TAG_UNLOCKED     (0<< _CHETAG_LLOCK_POSITION)
		#define CHE_TAG_LOCKED       (1<< _CHETAG_LLOCK_POSITION)

		/************************************************
		  * <combinewith CHE_TAG_TYPE_INST>
		  * 
		  * Line type tag - must only be one of following
		  ***********************************************
		*/
		#define CHE_TAG_TYPE_DATA    (0<< _CHETAG_LTYPE_POSITION)
		#define CHE_TAG_TYPE_INST    (1<< _CHETAG_LTYPE_POSITION)
	/***********************************
	 * End config parameter values
	 ************************************/


/*********************************************************************
 * Function:        unsigned long mCheGetMask(int idx)
 *
 * PreCondition:    none
 * Input:           idx			- Index of cache line to read
 * 								  The only chemask registers that can
 * 								  be non-zero are registers 10 and 11
 * Output:          value of the chemask register from the desired index
 * Side Effects:    none
 * Overview:        This routine reads the chemask register.
 * Note:            Only chemask regsters 10 and 11 can be written.  All
 * 					other chemask registers are always 0.
 ********************************************************************/
#define mCheGetMask(idx) (mCheSetCacheAccessLine((idx), 1), CHEMSK)

/*********************************************************************
 * Function:        unsigned long mCheSetMask(int idx, unsigned long mask)
 *
 * PreCondition:    None
 * Input:           idx			- Index of cache line to read
 * 								  The only chemask registers that can
 * 								  be non-zero are registers 10 and 11
 * 					mask		- Mask bits for cache tag comparisons
 * Output:          none
 * Side Effects:    The chemask registers cause data to appear in multiple
 * 					physical address windows.
 * Overview:        This routine writes the chemask register with the requested value.
 * 					The chemask registers are designed to cache multiple copies of
 * 					the exact same data at regular address intervals.  For example,
 * 					code in exception locations can be duplicated.
 * Note:            Extreme care must be taken when using this function as
 * 					physical memory can be different that the processor's view
 * 					of memory.
 ********************************************************************/
#define mCheSetMask(idx, mask) (mCheSetCacheAccessLine((idx), 1), CHEMSK = (mask))

/*********************************************************************
 * Function:        void mCheWriteCacheLine(unsigned long values[4])
 *
 * PreCondition:    cheSetCacheAccessLine must have been called to set up the correct
 * 					cache line index.  Also the writeEnable bit of cheacc must be 1, otherwise
 * 					writes to the cache data array are not allowed.
 * Input:           values			- the 4 unsigned long values to be written into the
 * 									  data array of the selected cache line
 * Output:          none
 * Side Effects:    Cache hits on this line will return these new data to the processor
 * Overview:        This routine writes the selected cache line data array with user
 * 					supplied data.
 * Note:            coherency between the cache and physical memory is not maintained
 * 					when using this function.
 ********************************************************************/
#define mCheWriteCacheLine(values) (CHEW0=values[0],CHEW1=values[1],CHEW2=values[2],CHEW3=values[3])

/*********************************************************************
 * Function:        void mCheInvalidateLine(int idx)
 *
 * PreCondition:    None
 * Input:           idx				- Index of the cache line to invalidate (0-15)
 * Output:          none
 * Side Effects:    The selected cache line is invalidated
 * Overview:        This routine clears the valid bit of the selected line, causing
 * 					it to no longer generate cache hits.  The LRU algorithm still
 * 					can select this line for replacement at which time this line
 * 					will be loaded with valid data again.
 * Note:            The checon writeEnable is automatically set to 1
 ********************************************************************/
#define mCheInvalidateLine(idx)	(mCheSetCacheAccessLine((idx),1), CHETAGCLR = 8)

/*********************************************************************
 * Function:        void mCheInvalidateAllLines()
 *
 * PreCondition:    None
 * Input:          	none
 * Output:          none
 * Side Effects:    The pCache is marked invalid
 * Overview:        This routine clears the valid bit of the all lines, causing
 * 					no cache hits on existing data with the cache.  This
 * 					routine can be used to make sure the system memory is
 * 					coherent with cache contents.
 * Note:            The checon writeEnable is automatically set to 1
 * 					for all lines in the cache.
 ********************************************************************/
#define mCheInvalidateAllLines() ( \
{ \
	int idx; \
	for (idx=0; idx<16; idx++) { mCheInvalidateLine(idx); } \
} \
)


/*********************************************************************
 * Function:        void mCheLockLine(int idx, int ltype, unsigned long addr)
 *
 * PreCondition:    None
 * Input:           idx				- index of cache line to lock
 * 					ltype			- 0:data, 1:Instruction
 * 					addr			- Address of data or instruction to
 * 									  preload into the pCache
 * Output:          none
 * Side Effects:    The pCache locks a line in the pCache and causes a
 * 					preload.
 * Overview:        This routine is used to preload and lock a line of
 * 					pCache.  Locking a line in the cache basically removes
 * 					the cache line from the normal LRU replacement algorithm.
 *
 * Note:            This function provides flexibility in performance
 * 					tuning.
 ********************************************************************/
#define mCheLockLine(idx, ltype, addr)	(mCheSetCacheTag((idx), (addr), CHE_TAG_INVALID | CHE_TAG_LOCKED | ((ltype)<<1)))


/*********************************************************************
 * Function:        void mCheGetHit()
 *
 * PreCondition:    None
 * Input:           none
 * Output:          Return the value of the chehit register
 * Side Effects:    none
 * Overview:        This routine returns the value of the chehit register.
 * 					The chehit register contains a 32-bit value representing
 * 					the number of cache hits.
 * Note:            none
 ********************************************************************/
#define mCheGetHit() CHEHIT

/*********************************************************************
 * Function:        void mCheGetMis()
 *
 * PreCondition:    None
 * Input:           none
 * Output:          Return the value of the chemis register
 * Side Effects:    none
 * Overview:        This routine returns the value of the chemis register.
 * 					The chemis register contains a 32-bit value representing
 * 					the number of cache misses.
 * Note:            none
 ********************************************************************/
#define mCheGetMis() CHEMIS

/*********************************************************************
 * Function:        void mCheGetAcc()
 *
 * PreCondition:    None
 * Input:           none
 * Output:          Return the value of the cheacc register
 * Side Effects:    none
 * Overview:        This routine returns the value of the cheacc register.
 * Note:            none
 ********************************************************************/
#define mCheGetAcc() CHEACC

/*********************************************************************
 * Function:        void CheKseg0CacheOff(void)
 *
 * PreCondition:    None
 * Input:           None
 * Output:          none
 * Side Effects:    Sets the CCA field in the Config register of Co-
 * 					processor 0 to the value "010"b
 * Overview:        This routine is used to disable cacheability of KSEG0.
 *
 * Note:            This macro cannot be executed in MIPS16 mode
 *
 ********************************************************************/
void __attribute__ ((nomips16)) CheKseg0CacheOff();

/*********************************************************************
 * Function:        void CheKseg0CacheOn(void)
 *
 * PreCondition:    None
 * Input:           None
 * Output:          none
 * Side Effects:    Sets the CCA field in the Config register of Co-
 * 					processor 0 to the value "011"b
 * Overview:        This routine is used to enable cacheability of KSEG0.
 *
 * Note:            This macro cannot be executed in MIPS16 mode
 *
 ********************************************************************/
void __attribute__ ((nomips16)) CheKseg0CacheOn();

#endif /*PCACHE_H_*/
