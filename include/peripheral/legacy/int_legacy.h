/********************************************************************
 * FileName:		int.h
 * Dependencies:
 * Processor:		PIC32
 * Hardware:		N/A
 * Assembler:		N/A
 * Linker:		    N/A
 * Company:		    Microchip Technology Inc..
 *
 * Software License Agreement:
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
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
 * $Id: INT.h,v 1.6 2006/11/07 23:29:45 C12923 Exp $
 * $Name:  $

 ********************************************************************/

#ifndef _OLD_PIC32INT_HEADER_FILE
#define _OLD_PIC32INT_HEADER_FILE

#include <p32xxxx.h>
#include <sys/attribs.h>


/*********************************************************************
 * Function:        void INTEnableSystemMultiVectoredInt(void)
 *
 * PreCondition:    EBASE and IntCtl.VS set up
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    System interrupts are turned on
 *
 * Overview:        Enables system wide multi-vectored interrupts
 ********************************************************************/
void __attribute__ ((nomips16)) INTEnableSystemMultiVectoredInt(void);
/*********************************************************************
 * Function:       void INTEnableSystemSingleVectoredInt(void)
 *
 * PreCondition:    EBASE and IntCtrl.VS set up (VS = 0)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    Single vectored interrupts are turned on
 *
 * Overview:        Enables system wide single vectored interrupts
 ********************************************************************/
void __attribute__ ((nomips16)) INTEnableSystemSingleVectoredInt(void);
/*********************************************************************
 * Function:       mINTSingleVectorRegistorSelect
 *
 * PreCondition:    EBASE and IntCtrl.VS set up (VS = 0)
 *
 * Input:           the shadow set that the single vector is using
 *
 * Output:          None
 *
 * Side Effects:    Single vector interrupt will use the shadow set
 ********************************************************************/
#define mINTSingleVectorRegistorSelect(reg)     (INTCONCLR = (reg), INTCONSET = (reg))

/*********************************************************************
 * Function:       mINTGetInterruptVectorNumber
 *
 * PreCondition:    EBASE and IntCtrl.VS set up (VS = 0)
 *
 * Input:           None
 *
 * Output:          The current pending interrupt's vector number
 *
 * Side Effects:    The value may not be the vector number that
 *                  made the interrupt occur
 ********************************************************************/
#define mINTGetInterruptVectorNumber()            (INTSTATbits.VEC)
/*********************************************************************
 * Function:       mINTGetInterruptVector
 *
 * PreCondition:    EBASE and IntCtrl.VS set up (VS = 0)
 *
 * Input:           None
 *
 * Output:          The current pending interrupt's vector priority
 *
 * Side Effects:    The value may not be the vector priority that
 *                  made the interrupt occur
 ********************************************************************/
#define mINTGetInterruptVectorPriority()            (INTSTATbits.SRIPL)

/******************************************************************************
  * <combinewith mClearIECRegister, mClearAllIFSRegister, mClearAllIECRegister>
  * 
  * Clear IRQ flag and enable bits funcitons
  * Prototype:
  *     void mClearIFSRegister(reg_num) void
  *     mClearIECRegister(reg_num)
  * Input:
  *     reg_num :  A value between 0 \- 3 inclusive.
  * Return:
  *     None
  *     
  * Side Effects:
  *     None
  * Remarks:
  *     None                                                                   
  *****************************************************************************
*/
#define mClearIFSRegister(reg_num)  (IFS##reg_num##CLR = 0xFFFFFFFF)
#define mClearIECRegister(reg_num)  (IEC##reg_num##CLR = 0xFFFFFFFF)
#define mClearAllIFSRegister()      (   IFS0CLR = 0xFFFFFFFF,   IFS1CLR = 0xFFFFFFFF)
#define mClearAllIECRegister()      (   IEC0CLR = 0xFFFFFFFF,   IEC1CLR = 0xFFFFFFFF)
/*********************************************************************
 * <combinewith mINTSetIFS1>
 * 
 * Function:       void mINTSetIFSx(flag)
 *
 * PreCondition:    None
 *
 * Input:           flag - value you would like to set
 *
 * Output:          None
 *
 * Side Effects:    IFSx - bit(s) will be set
 ********************************************************************/
#define mINTSetIFS0(flag)                    ( IFS0SET = (unsigned int)(flag)  )
#define mINTSetIFS1(flag)                    ( IFS1SET = (unsigned int)(flag)  )
/*********************************************************************
 * <combinewith mINTClearIFS1>
 *
 * Function:       void mINTClearIFSx(flag)
 *
 * PreCondition:    None
 *
 * Input:           flag - value you would like to cleared
 *
 * Output:          None
 *
 * Side Effects:    IFSx - bit(s) will be cleared
 ********************************************************************/
#define mINTClearIFS0(flag)                  ( IFS0CLR = (unsigned int)(flag)  )
#define mINTClearIFS1(flag)                  ( IFS1CLR = (unsigned int)(flag)  )
/*********************************************************************
 * <combinewith mINTGetIFS1>
 *
 * Function:       void mINTGetIFSx(flag)
 *
 * PreCondition:    None
 *
 * Input:           flag - value you would like to cleared
 *
 * Output:          None
 *
 * Side Effects:    Will tell is the flag is set
 ********************************************************************/
#define mINTGetIFS0(flag)               (IFS0 & (flag))
#define mINTGetIFS1(flag)               (IFS1 & (flag))
/*********************************************************************
 * <combinewith mINTSetIEC1>
 * 
 * Function:       void mINTSetIECx(flag)
 *
 * PreCondition:    None
 *
 * Input:           flag - value you would like to set
 *
 * Output:          None
 *
 * Side Effects:    IECx - bit(s) will be set
 ********************************************************************/
#define mINTSetIEC0(flag)                    ( IEC0SET = (unsigned int)(flag)  )
#define mINTSetIEC1(flag)                    ( IEC1SET = (unsigned int)(flag)  )
/*********************************************************************
 * <combinewith mINTClearIEC1>
 * 
 * Function:       void mINTClearIECx(flag)
 *
 * PreCondition:    None
 *
 * Input:           flag - value you would like to cleared
 *
 * Output:          None
 *
 * Side Effects:    IECx - bit(s) will be cleared
 ********************************************************************/
#define mINTClearIEC0(flag)                  ( IEC0CLR = (unsigned int)(flag)  )
#define mINTClearIEC1(flag)                  ( IEC1CLR = (unsigned int)(flag)  )
/*********************************************************************
 * Function:       void INTSetIntProximityTimerReload(WORD time)
 *
 * PreCondition:    None
 *
 * Input:           time - 16 bit value that will be used to reload the IP
 *                          time with tiggered
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Set the time that will be loaded into the IP timer
 ********************************************************************/
#define mINTSetIntProximityTimerReload(time)    (IPTMR = time)
/*********************************************************************
 * Function:        WORD INTGetIntProximityTimer(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Returns the current IP timer value
 *
 * Side Effects:    None
 *
 * Overview:        This function will return the current value of the
 *                  IP timer.
 ********************************************************************/
#define mINTGetIntProximityTimer()      (IPTMR)
/*********************************************************************
 * <combinewith mINTClearFreeze>
 *
 * Function:        void INTSetFreeze(void)
 *                  void INTClearFreeze(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    When emulator in Debug Mode, module freezes operation
 *
 * Overview:        Sets/Clears FRZ bit in INTCON
 ********************************************************************/
#define mINTSetFreeze()                 (INTCONSET = INTCON_FRZ_BIT)
#define mINTClearFreeze()               (INTCONCLR = INTCON_FRZ_BIT)
/****************************************************************************************************
  * <combinewith INT_TPC_GROUP_PRI_LEVEL_1, INT_TPC_GROUP_PRI_LEVEL_2, INT_TPC_GROUP_PRI_LEVEL_3, 
  * INT_TPC_GROUP_PRI_LEVEL_4, INT_TPC_GROUP_PRI_LEVEL_5, INT_TPC_GROUP_PRI_LEVEL_6, 
  * INT_TPC_GROUP_PRI_LEVEL_7, mINTSetTemporalProximityControl, mINTDisableTemporalProximityControl>
  * 
  * Prototype:
  *     void INTSetTemporalProximityControl(level) void
  *     INTDisableTemporalProximityControl(void)
  * Preconditions:
  *     None
  * Input:
  *     level :  The interrupt level group priority or lower start the
  *              IP timer and are disabled while the IP is counting
  * Return:
  *     None
  *     
  * Side Effects:
  *     TPC bits are modified
  * Remarks:
  *     TPC bits is the INTCON are set                                                                                                                                                                                                                                             
  ****************************************************************************************************
*/
#define mINTSetTemporalProximityControl(level)  (INTCONbits.TPC = level)
#define mINTDisableTemporalProximityControl()   (INTCONCLR = INT_TPC_DISABLE)

/***********************************************************************************************************************************
  * <combinewith CSW_INT_OFF, CSW_INT_PRIOR_0, CSW_INT_PRIOR_1, CSW_INT_PRIOR_2, CSW_INT_PRIOR_3, CSW_INT_PRIOR_4, CSW_INT_PRIOR_5, 
  * CSW_INT_PRIOR_6, CSW_INT_PRIOR_7, CSW_INT_SUB_PRIOR_0, CSW_INT_SUB_PRIOR_1, CSW_INT_SUB_PRIOR_2, CSW_INT_SUB_PRIOR_3>
  * 
  * Parameter values to be used with ConfigIntCoreSWx()                                                                                                                                                                                                  
  **********************************************************************************************************************************
*/
#define CSW_INT_ON		            	(1 << 15)
#define CSW_INT_OFF						(0)

#define CSW_INT_PRIOR_7                  (7)
#define CSW_INT_PRIOR_6                  (6)
#define CSW_INT_PRIOR_5                  (5)
#define CSW_INT_PRIOR_4                  (4)
#define CSW_INT_PRIOR_3                  (3)
#define CSW_INT_PRIOR_2                  (2)
#define CSW_INT_PRIOR_1                  (1)
#define CSW_INT_PRIOR_0                  (0)

#define CSW_INT_SUB_PRIOR_3              (3 << 4)
#define CSW_INT_SUB_PRIOR_2              (2 << 4)
#define CSW_INT_SUB_PRIOR_1              (1 << 4)
#define CSW_INT_SUB_PRIOR_0              (0 << 4)
/*********************************************************************
  * <combinewith mConfigIntCoreSW1>
  * 
  * Prototype:
  *     void ConfigIntCoreSWx(int config)
  * Description:
  *     Configures Core Software interrupt
  * Preconditions:
  *     None
  * Input:
  *     config :  Bit\-wise OR value of CSW_INT_XXX, CSW_INT_PRIOR_XXX
  *               and CSW_INT_SUB_PRIOR_X
  * Note:
  *     An absent symbol assumes corresponding bit(s) are disabled,
  *     or default value, and will be set = 0.
  * Return:
  *     None
  *     
  * Example:
  *     ConfigIntCoreSW0(CSW_INT_ON | CSW_INT_PRIOR_3 |
  *     CSW_INT_SUB_PRIOR_1)                                          
  ********************************************************************
*/
#define mConfigIntCoreSW0(config)      (mCS0ClearIntFlag(), mCS0SetIntPriority(((config) & 7)),\
        mCS0SetIntSubPriority((((config) >> 4) & 3)), mCS0IntEnable(((config) >> 15)))

#define mConfigIntCoreSW1(config)      (mCS1ClearIntFlag(), mCS1SetIntPriority(((config) & 7)),\
        mCS1SetIntSubPriority((((config) >> 4) & 3)), mCS1IntEnable(((config) >> 15)))
/**************************************
  * <combinewith mEnableIntCoreSW1>
  * 
  * Prototype:
  *     EnableIntCoreSWx(void)
  * Description:
  *     Enables Core Software interrupt
  * Preconditions:
  *     None
  * Return:
  *     None
  *     
  * Example:
  *     EnableIntCoreSW0()             
  *************************************
*/
#define mEnableIntCoreSW0()            mCS0IntEnable(1)

#define mEnableIntCoreSW1()            mCS1IntEnable(1)


/***************************************
  * <combinewith mDisableIntCoreSW1>
  * 
  * Prototype:
  *     DisableIntCoreSWx(void)
  * Description:
  *     Disables Core Software interrupt
  * Preconditions:
  *     None
  * Return:
  *     None
  *     
  * Example:
  *     DisableIntCoreSW0()             
  **************************************
*/
#define mDisableIntCoreSW0()             mCS0IntEnable(0)

#define mDisableIntCoreSW1()             mCS1IntEnable(0)

/******************************************************************************
 * <combinewith mSetPriorityIntCoreSW1>
 *
 * Function:        void SetPriorityIntCoreSWx(int priority)
 *
 * Description:		Sets the priority for Core Software interrupt
 *					The ConfigIntCoreSWx() sets the priority. Use this
 *					macro to change the previously set priority
 *					without any need to respecify other parameters.
 *
 * PreCondition:    None
 *
 * Inputs:			priority : A value of CSW_INT_PRIOR_XXX
 *
 * Output:          None
 *
 *
 * Example:			SetPriorityIntCoreSW0(CSW_INT_PRIORITY_3)
 *****************************************************************************/
#define mSetPriorityIntCoreSW0(priority)	    mCS0SetIntPriority(priority)

#define mSetPriorityIntCoreSW1(priority)	    mCS1SetIntPriority(priority)

/*******************************************************************************
  Function:
    void __attribute__ ((nomips16)) SetCoreSW0(void)

  Summary:
    Set the Core Software Interrupt 0.

  Description:
    This routine sets the core software interrupt 0.  This will produce an interrupt
    service request.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Example:
    <code>

    SetCoreSW0();
    </code>

  Remarks:
    This function can not be compiled using the MIPS16 instruciton set.
  *****************************************************************************/
void __attribute__((nomips16)) SetCoreSW0(void);

/*******************************************************************************
  Function:
    void __attribute__ ((nomips16)) SetCoreSW1(void)

  Summary:
    Set the Core Software Interrupt 1.

  Description:
    This routine sets the core software interrupt 1.  This will produce an interrupt
    service request.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Example:
    <code>

    SetCoreSW1();
    </code>

  Remarks:
    This function can not be compiled using the MIPS16 instruciton set.
  *****************************************************************************/
void __attribute__((nomips16))  SetCoreSW1(void);

/*******************************************************************************
  Function:
    void __attribute__ ((nomips16)) ClearCoreSW0(void)

  Summary:
    Clears the Core Software Interrupt 0.

  Description:
    This routine clears the core software interrupt 0.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Example:
    <code>

    ClearCoreSW0();

    INTClearFlag(INT_CS0);
    </code>

  Remarks:
    This function can not be compiled using the MIPS16 instruciton set.

    You must call this routine before clearing the interrupt request flag.
  *****************************************************************************/
void __attribute__((nomips16))  ClearCoreSW0(void);

/*******************************************************************************
  Function:
    void __attribute__ ((nomips16)) ClearCoreSW1(void)

  Summary:
    Clears the Core Software Interrupt 1.

  Description:
    This routine clears the core software interrupt 1.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Example:
    <code>

    ClearCoreSW1();

    INTClearFlag(INT_CS1);
    </code>

  Remarks:
    This function can not be compiled using the MIPS16 instruciton set.

    You must call this routine before clearing the interrupt request flag.
  *****************************************************************************/
void __attribute__((nomips16))  ClearCoreSW1(void);


#endif
