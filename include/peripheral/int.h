/********************************************************************
 * FileName:		int.h
 * Dependencies:
 * Processor:		PIC32MX
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

#ifndef _PIC32INT_HEADER_FILE
#define _PIC32INT_HEADER_FILE

#ifdef __cplusplus
extern "C"
  {
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Includes
// *****************************************************************************
// *****************************************************************************
#include <p32xxxx.h>
#include <sys/attribs.h>

#if (((__PIC32_FEATURE_SET__ >= 300) && (__PIC32_FEATURE_SET__ <= 499)) || defined(__32MXGENERIC__))
#include <peripheral/int_3xx_4xx.h>
#elif (((__PIC32_FEATURE_SET__ >= 500) && (__PIC32_FEATURE_SET__ <= 799)) || defined (__32MXPOCONO__))
#include <peripheral/int_5xx_6xx_7xx.h>
#else
#error "Device not supported by the interrupt peripheral library"
#endif
// *****************************************************************************
// *****************************************************************************
// Section: Legacy Includes
// *****************************************************************************
// *****************************************************************************
#ifndef _PLIB_DISABLE_LEGACY
#include <peripheral/legacy/int_legacy.h>
#endif
// *****************************************************************************
// *****************************************************************************
// Section: Constants & Data Types
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Interrupt Single Vector Shadow Set

  Summary:
    Single vector shadow set selector.

  Description:
    These definitions can be used enable the use of the shadow set when
    in single vector mode.
*/
typedef enum
{
    // Use the the CPU's register set when entering the handler.
    INT_REGISTOR_SET_SELECT_NONE /*DOM-IGNORE-BEGIN*/ = 0 /*DOM-IGNORE-END*/,
    // Use the shadow set when entering the handler
    INT_REGISTOR_SET_SELECT_SS0  /*DOM-IGNORE-BEGIN*/ = (_INTCON_SS0_MASK) /*DOM-IGNORE-END*/

}INT_SV_SS;

// *****************************************************************************
/* Interrupt Vector Priority

  Summary:
    Interrupt vector priority definitions.

  Description:
    These definitions can be used to set the priority of an interrupt
    vector.
*/
typedef enum
{
    // Interrupt vector priority level of 0, interrupt is disabled.
    INT_PRIORITY_DISABLED /*DOM-IGNORE-BEGIN*/=      0 /*DOM-IGNORE-END*/,
    // Interrupt vector priority level of 1.
    INT_PRIORITY_LEVEL_1  /*DOM-IGNORE-BEGIN*/=      1 /*DOM-IGNORE-END*/,
    // Interrupt vector priority level of 2.
    INT_PRIORITY_LEVEL_2  /*DOM-IGNORE-BEGIN*/=      2 /*DOM-IGNORE-END*/,
    // Interrupt vector priority level of 3.
    INT_PRIORITY_LEVEL_3  /*DOM-IGNORE-BEGIN*/=      3 /*DOM-IGNORE-END*/,
    // Interrupt vector priority level of 4.
    INT_PRIORITY_LEVEL_4  /*DOM-IGNORE-BEGIN*/=      4 /*DOM-IGNORE-END*/,
    // Interrupt vector priority level of 5.
    INT_PRIORITY_LEVEL_5  /*DOM-IGNORE-BEGIN*/=      5 /*DOM-IGNORE-END*/,
    // Interrupt vector priority level of 6.
    INT_PRIORITY_LEVEL_6  /*DOM-IGNORE-BEGIN*/=      6 /*DOM-IGNORE-END*/,
    // Interrupt vector priority level of 7.
    INT_PRIORITY_LEVEL_7  /*DOM-IGNORE-BEGIN*/=      7  /*DOM-IGNORE-END*/
}INT_PRIORITY;

// *****************************************************************************
/* Interrupt Vector Sub-priority

  Summary:
    Interrupt vector sub-priority definitions.

  Description:
    These definitions can be used to set the sub-priority of an interrupt
    vector.
*/
typedef enum
{
    // Interrupt vector sub-priority level of 0.
    INT_SUB_PRIORITY_LEVEL_0 /*DOM-IGNORE-BEGIN*/=   0 /*DOM-IGNORE-END*/,
    // Interrupt vector sub-priority level of 1.
    INT_SUB_PRIORITY_LEVEL_1 /*DOM-IGNORE-BEGIN*/=   1 /*DOM-IGNORE-END*/,
    // Interrupt vector sub-priority level of 2.
    INT_SUB_PRIORITY_LEVEL_2 /*DOM-IGNORE-BEGIN*/=   2 /*DOM-IGNORE-END*/,
    // Interrupt vector sub-priority level of 3.
    INT_SUB_PRIORITY_LEVEL_3 /*DOM-IGNORE-BEGIN*/=   3 /*DOM-IGNORE-END*/
}INT_SUB_PRIORITY;

// *****************************************************************************
/* Interrupt Enable/Disable

  Summary:
    Interrupt enable/disable definitions.

  Description:
    These definitions can be used to enable or disable an interrupt.
*/
typedef enum
{
    // Disables the interrupt.
    INT_DISABLED /*DOM-IGNORE-BEGIN*/ = 0 /*DOM-IGNORE-END*/,
    // Enables the interrupt.
    INT_ENABLED /*DOM-IGNORE-BEGIN*/  = 1 /*DOM-IGNORE-END*/
}INT_EN_DIS;
// *****************************************************************************
/* Interrupt Temporal Proximity Control

  Summary:
    Interrupt Temporal Proximity Control definitions.

  Description:
    These definitions can be used to set the interrupt priority of the Interrupt Temporal Proximity Timer.
*/
typedef enum
{
    // Temporal Proximity Timer disabled.
    INT_TPC_DISABLE            /*DOM-IGNORE-BEGIN*/=      0x00000700 /*DOM-IGNORE-END*/,
    // Temporal Proximity Timer enable for interupt priority level 1.
    INT_TPC_GROUP_PRI_LEVEL_1  /*DOM-IGNORE-BEGIN*/=      1 /*DOM-IGNORE-END*/,
    // Temporal Proximity Timer enable for interupt priority level 2 and below.
    INT_TPC_GROUP_PRI_LEVEL_2  /*DOM-IGNORE-BEGIN*/=      2 /*DOM-IGNORE-END*/,
    // Temporal Proximity Timer enable for interupt priority level 3 and below.
    INT_TPC_GROUP_PRI_LEVEL_3  /*DOM-IGNORE-BEGIN*/=      3 /*DOM-IGNORE-END*/,
    // Temporal Proximity Timer enable for interupt priority level 4 and below.
    INT_TPC_GROUP_PRI_LEVEL_4  /*DOM-IGNORE-BEGIN*/=      4 /*DOM-IGNORE-END*/,
    // Temporal Proximity Timer enable for interupt priority level 5 and below.
    INT_TPC_GROUP_PRI_LEVEL_5  /*DOM-IGNORE-BEGIN*/=      5 /*DOM-IGNORE-END*/,
    // Temporal Proximity Timer enable for interupt priority level 6 and below.
    INT_TPC_GROUP_PRI_LEVEL_6  /*DOM-IGNORE-BEGIN*/=      6 /*DOM-IGNORE-END*/,
    // Temporal Proximity Timer enable for interupt priority level 7 and below.
    INT_TPC_GROUP_PRI_LEVEL_7  /*DOM-IGNORE-BEGIN*/=      7 /*DOM-IGNORE-END*/
}INT_TPC_GROUP;

// *****************************************************************************
/* Interrupt Vector Spacing

  Summary:
    Interrupt vector spacing definitions.

  Description:
    These definitions can be used to set the core's EBASE vector spacing.
*/
typedef enum
{
    // Vector spacing of 32 bytes.
    INT_VS_32  /*DOM-IGNORE-BEGIN*/= 32 /*DOM-IGNORE-END*/,
    // Vector spacing of 64 bytes.
    INT_VS_64  /*DOM-IGNORE-BEGIN*/= 64 /*DOM-IGNORE-END*/,
    // Vector spacing of 128 bytes.
    INT_VS_128  /*DOM-IGNORE-BEGIN*/= 128 /*DOM-IGNORE-END*/,
    // Vector spacing of 256 bytes.
    INT_VS_256  /*DOM-IGNORE-BEGIN*/= 256 /*DOM-IGNORE-END*/,
    // Vector spacing of 512 bytes.
    INT_VS_512  /*DOM-IGNORE-BEGIN*/= 512 /*DOM-IGNORE-END*/
}INT_VS;

// *****************************************************************************
/* Interrupt Configuration

  Summary:
    Interrupt configuration parameters.

  Description:
    These definitions can be used to configure the system interrupt controller.
*/
typedef enum
{
    // Configure the interrupt module for Mult-vector mode.
    INT_SYSTEM_CONFIG_MULT_VECTOR,
    // Configure the interrupt module for Single Vectored mode.
    INT_SYSTEM_CONFIG_SINGLE_VECTOR
}INT_SYSTEM_CONFIG;

// *****************************************************************************
// *****************************************************************************
// Section: Interrupt Peripheral Library Interface Routines and Macors
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    unsigned int __attribute__((nomips16)) INTDisableInterrupts(void)

  Summary:
    Disables the PIC32MX from handling interrupts.

  Description:
    This routine disables the core from handling any pending interrupt requests.

  Precondition:
    None

  Parameters:
    None

  Returns:
    The previous state of the CP0 register Status.IE bit.  The INTRestoreInterrupts
    function can be used in other routines to restore the system interrupt state.

  Example:
    <code>
    unsigned int intStatus;

    intStatus = INTDisableInterrupts();
    </code>

  Remarks:
    This function cannot be compiled using the MIPS16 instruction set.
  *****************************************************************************/
unsigned int __attribute__((nomips16)) INTDisableInterrupts(void);

/*******************************************************************************
  Function:
    unsigned int __attribute__((nomips16))  INTEnableInterrupts(void)

  Summary:
    Enables the PIC32MX to handle interrupts.

  Description:
    This routine enables the core to handle any pending interrupt requests.

  Precondition:
    Need to configure system using INTConfigureSystem

  Parameters:
    None

  Returns:
    The previous state of the CP0 register Status.IE bit.  The INTRestoreInterrupts
    function can be used in other routines to restore the system interrupt state.

  Example:
    <code>
    unsigned int intStatus;

    intStatus = INTEnableInterrupts();
    </code>

  Remarks:
    This function cannot be compiled using the MIPS16 instruction set.
  *****************************************************************************/
unsigned int __attribute__((nomips16))  INTEnableInterrupts(void);

/*******************************************************************************
  Function:
    void __attribute__((nomips16))  INTRestoreInterrupts(unsigned int status)

  Summary:
    Restores the PIC32MX interrupt state.

  Description:
    This routine restores the core to the previous interrupt handling state.

  Precondition:
    None

  Parameters:
    status      - the state of the CP0 register Status.IE

  Returns:
    None

  Example:
    <code>
    unsigned int intStatus;

    intStatus = INTDisableInterrupts();

    // ... application code

    INTRestoreInterrupts(intStatus);
    </code>

  Remarks:
    This function cannot be compiled using the MIPS16 instruction set.
  *****************************************************************************/
void __attribute__((nomips16))  INTRestoreInterrupts(unsigned int status);

/*******************************************************************************
  Function:
    void __attribute__ ((nomips16)) INTConfigureSystem(INT_SYSTEM_CONFIG config);

  Summary:
    Configures the system for  multi-vector or single vectored interrupts.

  Description:
    This routine configures the core to receive interrupt requests and configures the
    Interrupt module for Multi-vectored or Single Vectored mode.

  Precondition:
    None

  Parameters:
    config      - The interrupt configuration to set.

  Returns:
    None

  Example:
    Configure for Multi-vectored mode
    <code>

    // configure for multi-vectored mode
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    // enable interrupts
    INTEnableInterrupts();

    // ...
    </code>

    Configure for Single Vectored mode
    <code>

    // configure for single vectored mode
    INTConfigureSystem(INT_SYSTEM_CONFIG_SINGLE_VECTOR);

    // enable interrupts
    INTEnableInterrupts();

    // ...
    </code>

  Remarks:
    This function cannot be compiled using the MIPS16 instruction set.
  *****************************************************************************/
void __attribute__ ((nomips16)) INTConfigureSystem(INT_SYSTEM_CONFIG config);

/*******************************************************************************
  Function:
    void __attribute__((nomips16)) INTSetEBASE(unsigned int ebase_address)

  Summary:
    Sets the PIC32MX exception base.

  Description:
    This routine sets the exception base of the core.

  Precondition:
    None

  Parameters:
    ebase_address   - The address of the EBASE.
                    * must be be located in KSEG0 or KSEG1
                    * must be 4KB aligned

  Returns:
    None

  Example:
    <code>

    INTSetEBASE(0xBFC01000);
    </code>

  Remarks:
    This function cannot be compiled using the MIPS16 instruction set.
  *****************************************************************************/
void __attribute__((nomips16)) INTSetEBASE(unsigned int ebase_address);

/*******************************************************************************
  Function:
    void __attribute__((nomips16)) INTSetVectorSpacing(INT_VS vector_spacing)

  Summary:
    Sets the PIC32MX exception vector spacing.

  Description:
    This routine sets the exception vector spacing of the core.

  Precondition:
    None

  Parameters:
    vector_spacing  - The desired vector spacing.

  Returns:
    None

  Example:
    <code>

    INTSetVectorSpacing(INT_VS_32);
    </code>

  Remarks:
    This function cannot be compiled using the MIPS16 instruction set.
  *****************************************************************************/
void __attribute__((nomips16)) INTSetVectorSpacing(INT_VS vector_spacing);

/*******************************************************************************
  Function:
    extern inline void __attribute__ ((always_inline)) INTSingleVectorRegisterSet(INT_SV_SS reg_set)

  Summary:
    Sets the single vectored interrupt handler's general purpose register set.

  Description:
    This routine sets the single vectored interrupt handler's general purpose register set.

  Precondition:
    The interrupt controller must be set in Single Vectored mode.

  Parameters:
    reg_set         - Register set for the single vectored handler.

  Returns:
    None

  Example:
    <code>

    INTSingleVectorRegisterSet(INT_REGISTOR_SET_SELECT_NONE);
    </code>

  Remarks:
    None.
  *****************************************************************************/
extern inline void __attribute__ ((always_inline)) INTSingleVectorRegisterSet(INT_SV_SS reg_set)
{
    INTCONCLR   = reg_set;
    INTCONSET    = reg_set;
}

/*******************************************************************************
  Function:
    extern inline unsigned int __attribute__ ((always_inline)) INTGetInterruptVectorNumber(void)

  Summary:
    Gets the pending interrupt vector.

  Description:
    This routine gets the pending interrupt vector number.

  Precondition:
    None

  Parameters:
    None

  Returns:
    The pending interrupt vector number.

  Example:
    <code>
    unsigned int vector_num;

    vector_num = INTGetInterruptVectorNumber();

    if(vector_num == _CORE_TIMER_VECTOR)
    {
        // ...
    }
    </code>

  Remarks:
    The user can refer to the device file to get the vector number defines.
  *****************************************************************************/
extern inline unsigned int __attribute__ ((always_inline)) INTGetInterruptVectorNumber(void)
{
    return (unsigned int)(INTSTATbits.VEC);
}
/*******************************************************************************
  Function:
    extern inline INT_PRIORITY __attribute__ ((always_inline)) INTGetInterruptVectorPriority(void)

  Summary:
    Gets the pending interrupt vector's priority.

  Description:
    This routine gets the pending interrupt vector's priority.

  Precondition:
    None

  Parameters:
    None

  Returns:
    The pending interrupt vector's priority.

  Example:
    <code>
    INT_PRIORITY vector_pri;

    vector_pri = INTGetInterruptVectorPriority();
    </code>

  Remarks:
    None.
  *****************************************************************************/
extern inline INT_PRIORITY __attribute__ ((always_inline)) INTGetInterruptVectorPriority(void)
{
    return (INT_PRIORITY)(INTSTATbits.SRIPL);
}

/*******************************************************************************
  Function:
    extern inline void __attribute__ ((always_inline)) INTGetInterruptVectorNumberAndPriority(unsigned int *number, INT_PRIORITY *priority)

  Summary:
    Gets the pending interrupt vector number and priority.

  Description:
    This routine gets the pending interrupt vector number and priority.

  Precondition:
    *number - pointer to the vector number

    *priority - pointer to the interrupt priority

  Parameters:
    None

  Returns:
    The pending interrupt vector's priority.

  Example:
    <code>
    INT_PRIORITY vector_pri;
    unsigned int vector_num;

    INTGetInterruptVectorNumberAndPriority(&vector_num, &vector_pri);

    if(vector_num == _CORE_TIMER_VECTOR)
    {
        // ...
    }
    </code>

  Remarks:
    None.
  *****************************************************************************/
extern inline void __attribute__ ((always_inline)) INTGetInterruptVectorNumberAndPriority(unsigned int *number, INT_PRIORITY *priority)
{
    *number     = INTSTAT;
    *priority   = (INT_PRIORITY)((*number >> 8) & 7);
    *number     &= 0x3F;
}

/*******************************************************************************
  Function:
    void INTClearFlag(INT_SOURCE source)

  Summary:
    Clears an interrupt request flag.

  Description:
    This routine clears an interrupt request flag.

  Precondition:
    None

  Parameters:
    source  - Interrupt source.

  Returns:
    None

  Example:
    <code>
    INTClearFlag(INT_CT);
    </code>

  Remarks:
    None
  *****************************************************************************/
void INTClearFlag(INT_SOURCE source);

/*******************************************************************************
  Function:
    void INTSetFlag(INT_SOURCE source)

  Summary:
    Sets an interrupt request flag.

  Description:
    This routine sets an interrupt request flag.

  Precondition:
    None

  Parameters:
    source  - Interrupt source.

  Returns:
    None

  Example:
    <code>
    INTSetFlag(INT_CT);
    </code>

  Remarks:
    If the corresponding interrupt enable is set, this routine will cause the
    application to vector to the interrupt's handler.
  *****************************************************************************/
void INTSetFlag(INT_SOURCE source);

/*******************************************************************************
  Function:
    unsigned int INTGetFlag(INT_SOURCE source)

  Summary:
    Gets the interrupt request flag.

  Description:
    This routine gets an interrupt request flag.

  Precondition:
    None

  Parameters:
    source  - Interrupt source.

  Returns:
    * 0 if the interrupt request flag is clear
    * 1 if the interrupt request flag is set

  Example:
    <code>
    if(INTGetFlag(INT_CT))
    {
        // ... do something
    }
    </code>

  Remarks:
    None
  *****************************************************************************/
unsigned int INTGetFlag(INT_SOURCE source);

/*******************************************************************************
  Function:
    void INTEnable(INT_SOURCE source, INT_EN_DIS enable)

  Summary:
    Enables or disables the interrupt.

  Description:
    This routine enables or disables the interrupt source.

  Precondition:
    None

  Parameters:
    source  - Interrupt source.
    enable  - Enable state to set.

  Returns:
    None

  Example:
    <code>
    INTEnable(INT_CT, INT_ENABLED);
    </code>

  Remarks:
    None
  *****************************************************************************/
void INTEnable(INT_SOURCE source, INT_EN_DIS enable);

/*******************************************************************************
  Function:
    unsigned int INTGetEnable(INT_SOURCE source)

  Summary:
    Gets the interrupt enable.

  Description:
    This routine gets an interrupt enable.

  Precondition:
    None

  Parameters:
    source  - Interrupt source.

  Returns:
    * 0 if interrupt is disabled
    * else interrupt is enabled

  Example:
    <code>
    if(INTGetEnable(INT_CT))
    {
        // ... do something
    }
    </code>

  Remarks:
    None
  *****************************************************************************/
unsigned int INTGetEnable(INT_SOURCE source);

/*******************************************************************************
  Function:
    void INTSetVectorPriority(INT_VECTOR vector, INT_PRIORITY priority)

  Summary:
    Sets the interrupt vector's priority.

  Description:
    This routine sets the interrupt vector's priority.

  Precondition:
    None

  Parameters:
    vector    - Interrupt vector.
    priority  - Interrupt vector's priority.

  Returns:
    None

  Example:
    <code>
    INTSetVectorPriority(INT_CORE_TIMER_VECTOR, INT_PRIORITY_LEVEL_4);
    </code>

  Remarks:
    None
  *****************************************************************************/
void INTSetVectorPriority(INT_VECTOR vector, INT_PRIORITY priority);

/*******************************************************************************
  Function:
    INT_PRIORITY INTGetVectorPriority(INT_VECTOR vector)

  Summary:
    Gets the interrupt vector's priority.

  Description:
    This routine gets the interrupt vector's priority.

  Precondition:
    None

  Parameters:
    vector    - Interrupt vector.

  Returns:
    interrupt vector's priority

  Example:
    <code>
    INT_PRIORITY intPriority;

    intPriority = INTGetVectorPriority(INT_CORE_TIMER_VECTOR);
    </code>

  Remarks:
    None
  *****************************************************************************/
INT_PRIORITY INTGetVectorPriority(INT_VECTOR vector);

/*******************************************************************************
  Function:
    void INTSetVectorSubPriority(INT_VECTOR vector, INT_SUB_PRIORITY subPriority)

  Summary:
    Sets the interrupt vector's sub-priority.

  Description:
    This routine sets the interrupt vector's sub-priority.

  Precondition:
    None

  Parameters:
    vector          - Interrupt vector.
    subPriority     - Interrupt vector's sub-priority.

  Returns:
    None

  Example:
    <code>
    INTSetVectorSubPriority(INT_CORE_TIMER_VECTOR, INT_SUB_PRIORITY_LEVEL_1);
    </code>

  Remarks:
    None
  *****************************************************************************/
void INTSetVectorSubPriority(INT_VECTOR vector, INT_SUB_PRIORITY subPriority);

/*******************************************************************************
  Function:
    INT_SUB_PRIORITY INTGetVectorSubPriority(INT_VECTOR vector)

  Summary:
    Gets the interrupt vector's priority.

  Description:
    This routine gets the interrupt vector's priority.

  Precondition:
    None

  Parameters:
    vector    - Interrupt vector.

  Returns:
    interrupt vector's sub-priority

  Example:
    <code>
    INT_SUB_PRIORITY intSubPriority;

    intSubPriority = INTGetVectorSubPriority(INT_CORE_TIMER_VECTOR);
    </code>

  Remarks:
    None
  *****************************************************************************/
INT_SUB_PRIORITY INTGetVectorSubPriority(INT_VECTOR vector);


/*******************************************************************************
  Function:
    extern inline void __attribute__ ((always_inline)) INTSetIntProximityTimerReload(unsigned int time)

  Summary:
    Sets or reloads the interrupt proximity timer.

  Description:
    This routine sets or reloads the interrupt proximity timer.

  Precondition:
    None

  Parameters:
    time            - 32-bit timer value.

  Returns:
    None

  Example:
    <code>
    INTSetIntProximityTimerReload(56000);
    </code>

  Remarks:
    None
  *****************************************************************************/
extern inline void __attribute__ ((always_inline)) INTSetIntProximityTimerReload(unsigned int time)
{
    IPTMR = time;
}
/*******************************************************************************
  Function:
    extern inline unsigned int __attribute__ ((always_inline)) INTGetIntProximityTimer(void)

  Summary:
    Gets the interrupt proximity timer.

  Description:
    This routine gets the interrupt proximity timer.

  Precondition:
    None

  Parameters:
    None

  Returns:
    The current tick count of the timer.

  Example:
    <code>
    unsigned int time

    time = INTGetIntProximityTimer();
    </code>

  Remarks:
    None
  *****************************************************************************/
extern inline unsigned int __attribute__ ((always_inline)) INTGetIntProximityTimer(void)
{
    return IPTMR;
}
/*******************************************************************************
  Function:
    extern inline void __attribute__ ((always_inline)) INTSetFreeze(void)

  Summary:
    Sets the freeze (FRZ) bit.

  Description:
    This routine sets the freeze (FRZ) bit.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Example:
    <code>
    INTSetFreeze();
    </code>

  Remarks:
    None
  *****************************************************************************/
extern inline void __attribute__ ((always_inline)) INTSetFreeze(void)
{
    INTCONSET = INTCON_FRZ_BIT;
}
/*******************************************************************************
  Function:
    extern inline void __attribute__ ((always_inline)) INTClearFreeze(void)

  Summary:
    Clears the freeze (FRZ) bit.

  Description:
    This routine clears the freeze (FRZ) bit.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Example:
    <code>
    INTSetFreeze();
    </code>

  Remarks:
    None
  *****************************************************************************/
extern inline void __attribute__ ((always_inline)) INTClearFreeze(void)
{
    INTCONCLR = INTCON_FRZ_BIT;
}
/*******************************************************************************
  Function:
    extern inline void __attribute__ ((always_inline)) INTSetTemporalProximityControl(INT_TPC_GROUP level)

  Summary:
    Sets the Temporal Proximity Control level.

  Description:
    This routine sets the temporal Proximity Control level.

  Precondition:
    None

  Parameters:
    level   - Level of the temporal proximity control.

  Returns:
    None

  Example:
    <code>
    INTSetTemporalProximityControl(INT_TPC_GROUP_PRI_LEVEL_3);
    </code>

  Remarks:
    None
  *****************************************************************************/
extern inline void __attribute__ ((always_inline)) INTSetTemporalProximityControl(INT_TPC_GROUP level)
{
    INTCONCLR = INT_TPC_DISABLE;

    if(level != INT_TPC_DISABLE)
        INTCONSET = (level << _INTCON_TPC_POSITION);
}

/*******************************************************************************
//DOM-IGNORE-BEGIN
  *****************************************************************************/
#define CORE_SW_0           0x00000100
#define CORE_SW_1           0x00000200
/*******************************************************************************
//DOM-IGNORE-END
  *****************************************************************************/


/*******************************************************************************
  Function:
    void __attribute__ ((nomips16)) CoreSetSoftwareInterrupt0(void)

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

    CoreSetSoftwareInterrupt0();
    </code>

  Remarks:
    This function cannot be compiled using the MIPS16 instruction set.
  *****************************************************************************/
void __attribute__((nomips16)) CoreSetSoftwareInterrupt0(void);

/*******************************************************************************
  Function:
    void __attribute__ ((nomips16)) CoreSetSoftwareInterrupt1(void)

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

    CoreSetSoftwareInterrupt1();
    </code>

  Remarks:
    This function cannot be compiled using the MIPS16 instruction set.
  *****************************************************************************/
void __attribute__((nomips16))  CoreSetSoftwareInterrupt1(void);

/*******************************************************************************
  Function:
    void __attribute__ ((nomips16)) CoreClearSoftwareInterrupt0(void)

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

    CoreClearSoftwareInterrupt0();

    INTClearFlag(INT_CS0);
    </code>

  Remarks:
    This function cannot be compiled using the MIPS16 instruction set.

    You must call this routine before clearing the interrupt request flag.
  *****************************************************************************/
void __attribute__((nomips16))  CoreClearSoftwareInterrupt0(void);

/*******************************************************************************
  Function:
    void __attribute__ ((nomips16)) CoreClearSoftwareInterrupt1(void)

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

    CoreClearSoftwareInterrupt1();

    INTClearFlag(INT_CS1);
    </code>

  Remarks:
    This function cannot be compiled using the MIPS16 instruction set.

    You must call this routine before clearing the interrupt request flag.
  *****************************************************************************/
void __attribute__((nomips16))  CoreClearSoftwareInterrupt1(void);

#ifdef __cplusplus
  }
#endif

#endif
