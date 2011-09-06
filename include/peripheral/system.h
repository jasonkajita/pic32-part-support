/********************************************************************
 * FileName:		System.h
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
 * $Id: CoreTimer.h,v 1.2 2006/11/03 15:07:21 C12923 Exp $
 * $Name:  $
 ********************************************************************/

#ifndef _SYSTEM_HEADER_FILE
#define _SYSTEM_HEADER_FILE

#include <p32xxxx.h>
#include <peripheral/int.h>
#include <peripheral/pcache.h>
#include <peripheral/osc.h>
#include <peripheral/dma.h>
#include <peripheral/bmx.h>
#include <peripheral/lock.h>
#ifdef __cplusplus
extern "C"
  {
#endif
#define FLASH_SPEED_HZ          30000000 //Max Flash speed
#define PB_BUS_MAX_FREQ_HZ      80000000 //Max Peripheral bus speed

/*********************************************************************
 * SYSTEMConfig Flags
 *********************************************************************/
#define SYS_CFG_WAIT_STATES     0x00000001 //SYSTEMConfig wait states
#define SYS_CFG_PB_BUS          0x00000002 //SYSTEMConfig pb bus
#define SYS_CFG_PCACHE          0x00000004 //SYSTEMConfig cache
#define SYS_CFG_ALL             0xFFFFFFFF //SYSTEMConfig All

/*********************************************************************
 * Function:       unsigned int SYSTEMConfigPB(unsigned int sys_clock)
 *
 * PreCondition:    None
 *
 * Input:           sys_clock - system clock in Hz
 *
 * Output:          the PB clock frequency
 *
 * Side Effects:
 *
 * Overview:	    The function sets the PB divider to the optimum value.
 *
 * Note:            The interrupts are disabled shortly, the DMA is suspended and the system is unlocked while performing the operation.
 *                  Upon return the previous status of the interrupts and the DMA are restored. The system is re-locked.
 *
 * Example:	    SYSTEMConfigPB(72000000);
 ********************************************************************/
extern inline unsigned int __attribute__((always_inline)) SYSTEMConfigPB(unsigned int sys_clock)
{
    unsigned int pb_div;
    unsigned int pb_clock;

    pb_clock = sys_clock;

    if(sys_clock > PB_BUS_MAX_FREQ_HZ)
    {
        pb_div=OSC_PB_DIV_2;
        pb_clock >>= 1;
    }
    else
    {
        pb_div=OSC_PB_DIV_1;
    }

    OSCSetPBDIV(pb_div);

    return pb_clock;
}


/*********************************************************************
 * Function:        unsigned int SYSTEMConfigWaitStates(unsigned int sys_clock)
 *
 * PreCondition:    None
 *
 * Input:           sys_clock - system clock in Hz
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:	    The function sets the Flash Wait states to the optimum value.
 *
 * Note:            The interrupts are disabled shortly, the DMA is suspended and the system is unlocked while performing the operation.
 *                  Upon return the previous status of the interrupts and the DMA are restored. The system is re-locked.
 *
 * Example:	    SYSTEMConfigWaitStates(72000000);
 ********************************************************************/
extern inline void __attribute__((always_inline)) SYSTEMConfigWaitStates(unsigned int sys_clock)
{
#ifdef _PCACHE
    unsigned int wait_states;
    unsigned int int_status;
#endif

#ifdef _PCACHE
    wait_states = 0;

    while(sys_clock > FLASH_SPEED_HZ)
    {
        wait_states++;
        sys_clock -= FLASH_SPEED_HZ;
    }

    int_status=INTDisableInterrupts();
    mCheConfigure(wait_states);
    INTRestoreInterrupts(int_status);

#endif
}

/*********************************************************************
 * Function:        unsigned int SYSTEMConfigWaitStatesAndPB(unsigned int sys_clock)
 *
 * PreCondition:    None
 *
 * Input:           sys_clock - system clock in Hz
 *
 * Output:          the PB clock frequency
 *
 * Side Effects:    None
 *
 * Overview:	    The function sets the PB divider and the Flash Wait states to the optimum value.
 *
 * Note:            The interrupts are disabled shortly, the DMA is suspended and the system is unlocked while performing the operation.
 *                  Upon return the previous status of the interrupts and the DMA are restored. The system is re-locked.
 *
 * Example:	    SYSTEMConfigWaitStatesAndPB(72000000);
 ********************************************************************/
extern inline unsigned int __attribute__((always_inline)) SYSTEMConfigWaitStatesAndPB(unsigned int sys_clock)
{
#ifdef _PCACHE
    unsigned int wait_states;
#endif
    unsigned int pb_clock;
    unsigned int int_status;

    pb_clock = SYSTEMConfigPB(sys_clock);


    // set the flash wait states based on 1 wait state
    // for every 20 MHz
#ifdef _PCACHE
    wait_states = 0;

    while(sys_clock > FLASH_SPEED_HZ)
    {
        wait_states++;
        sys_clock -= FLASH_SPEED_HZ;
    }

    int_status=INTDisableInterrupts();
    mCheConfigure(wait_states);
    INTRestoreInterrupts(int_status);

#endif

    return pb_clock;
}
/*********************************************************************
 * Function:       unsigned int SYSTEMConfigPerformance(unsigned int sys_clock)
 *
 * PreCondition:    None
 *
 * Input:           sys_clock - system clock in Hz
 *
 * Output:          the PB clock frequency
 *
 * Side Effects:    Sets the PB and Flash Wait states
 *
 * Overview:	    The function sets the PB divider, the Flash Wait states and the DRM wait states to the optimum value.
 *                  It also enables the cacheability for the K0 segment.
 *
 * Note:            The interrupts are disabled shortly, the DMA is suspended and the system is unlocked while performing the operation.
 *                  Upon return the previous status of the interrupts and the DMA are restored. The system is re-locked.
 *
 * Example:	    SYSTEMConfigPerformance(72000000);
 ********************************************************************/
extern inline unsigned int __attribute__((always_inline)) SYSTEMConfigPerformance(unsigned int sys_clock)
{
    // set up the wait states
    unsigned int pb_clk;
#ifdef _PCACHE
    unsigned int cache_status;
#endif
    unsigned int int_status;

    pb_clk = SYSTEMConfigWaitStatesAndPB(sys_clock);

    int_status=INTDisableInterrupts();

    mBMXDisableDRMWaitState();

#ifdef _PCACHE
    cache_status = mCheGetCon();
    cache_status |= CHE_CONF_PF_ALL;
    mCheConfigure(cache_status);
    CheKseg0CacheOn();
#endif

    INTRestoreInterrupts(int_status);

    return pb_clk;

}
/*********************************************************************
 * Function:       unsigned int SYSTEMConfig(unsigned int sys_clock, unsigned int flags)
 *
 * PreCondition:    None
 *
 * Input:           sys_clock - system clock in Hz
 *                  flags -
 *                  -    SYS_CFG_WAIT_STATES  - configure the flash wait states from the system clock
 *                  -    SYS_CFG_PB_BUS       - configure the PB bus from the system clock
 *                  -    SYS_CFG_PCACHE      - configure the pCache (if used)
 *                  -    SYS_CFG_ALL          - configure all based off of system clock
 *
 * Output:          the PB clock frequency
 *
 * Side Effects:    Could set the wait state, pb bus and turn on the pre-fetch buffer and cache. Sets the RAM
 *                  wait state to 0.
 *
 * Overview:	    The function sets the PB divider, the Flash Wait states and the DRM wait states to the optimum value.
 *                  It also enables the cacheability for the K0 segment.
 *
 * Note:            The interrupts are disabled shortly, the DMA is suspended and the system is unlocked while performing the operation.
 *                  Upon return the previous status of the interrupts and the DMA are restored. The system is re-locked.
 *
 * Example:	    SYSTEMConfig(72000000, SYS_CFG_ALL);
 ********************************************************************/
extern inline unsigned int __attribute__((always_inline)) SYSTEMConfig(unsigned int sys_clock, unsigned int flags)
{
    unsigned int pb_clk;
    unsigned int int_status;
#ifdef _PCACHE
    unsigned int cache_status;
#endif

    int_status=INTDisableInterrupts();

    mBMXDisableDRMWaitState();

    if(flags & SYS_CFG_WAIT_STATES)
    {
        SYSTEMConfigWaitStates(sys_clock);
    }

    if(flags & SYS_CFG_PB_BUS)
    {
        SYSTEMConfigPB(sys_clock);
    }


#ifdef _PCACHE
    if(flags & SYS_CFG_PCACHE)
    {
        cache_status = mCheGetCon();
        cache_status |= CHE_CONF_PF_ALL;
        mCheConfigure(cache_status);
        CheKseg0CacheOn();
    }
#endif

    pb_clk = sys_clock;
    pb_clk >>= OSCCONbits.PBDIV;

    INTRestoreInterrupts(int_status);

    return pb_clk;

}
#ifdef __cplusplus
  }
#endif
#endif

