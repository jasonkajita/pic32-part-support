/********************************************************************
 * FileName:		perilib.h
 * Dependencies:
 * Processor:		PICxx
 * Hardware:		N/A
 * Assembler:		N/A
 * Linker:		    N/A
 * Company:		    Microchip Technology, Inc.
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
 *********************************************************************
 * File Description:
 *
 * Peripheral Library Master Include
 *
 *
 * $Id$
 ********************************************************************/

#ifndef _PERIPHERAL_LIBRARY_MASTER_HEADER_FILE
#define _PERIPHERAL_LIBRARY_MASTER_HEADER_FILE

#ifdef __cplusplus
extern "C" {
#endif

#include <peripheral/adc10.h>
#include <peripheral/bmx.h>
#include <peripheral/cmp.h>
#include <peripheral/cvref.h>
#include <peripheral/dma.h>
#include <peripheral/i2c.h>
#include <peripheral/incap.h>
#include <peripheral/int.h>
#include <peripheral/nvm.h>
#include <peripheral/outcompare.h>
#include <peripheral/pcache.h>
#include <peripheral/pmp.h>
#include <peripheral/ports.h>
#include <peripheral/power.h>
#include <peripheral/reset.h>
#include <peripheral/rtcc.h>
#include <peripheral/spi.h>
#include <peripheral/system.h>
#include <peripheral/timer.h>
#include <peripheral/uart.h>
#include <peripheral/wdt.h>
#include <peripheral/eth.h>
#include <peripheral/CAN.h>

#ifdef __cplusplus
}
#endif

#endif
