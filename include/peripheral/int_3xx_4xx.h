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

#ifndef _PIC32INT_3XX_4XX_HEADER_FILE
#define _PIC32INT_3XX_4XX_HEADER_FILE

// *****************************************************************************
// *****************************************************************************
// Section: Includes
// *****************************************************************************
// *****************************************************************************
#include <p32xxxx.h>
#include <sys/attribs.h>
// *****************************************************************************
// *****************************************************************************
// Section: Legacy Includes
// *****************************************************************************
// *****************************************************************************
#ifndef _PLIB_DISABLE_LEGACY
#include <peripheral/legacy/int_3xx_4xx_legacy.h>
#endif

// *****************************************************************************
/* Interrupt Source

  Summary:
    Interrupt Source and Vector definitions (3xx/4xx family)
  Description:
    These definitions can be used to set or get the state of the interrupt source flag,
    interrupt enable.
*/
typedef enum
{
    INT_CT = 0,            // Core Timer Interrupt
    INT_CS0,               // Core Software Interrupt 0
    INT_CS1,               // Core Software Interrupt 1

    INT_INT0,              // External Interrupt 0
    INT_INT1,              // External Interrupt 1
    INT_INT2,              // External Interrrupt 2
    INT_INT3,              // External Interrupt 3
    INT_INT4,              // External Interupt 4

    INT_T1,                // Timer 1
    INT_T2,                // Timer 2
    INT_T3,                // TImer 3
    INT_T4,                // Timer 4
    INT_T5,                // Timer 5

    INT_IC1,               // Input Capture 1
    INT_IC2,               // Input Capture 2
    INT_IC3,               // Input Capture 3
    INT_IC4,               // Input Capture 4
    INT_IC5,               // Input Capture 5

    INT_OC1,               // Output Capture 1
    INT_OC2,               // Output Capture 2
    INT_OC3,               // Output Capture 3
    INT_OC4,               // Output Capture 4
    INT_OC5,               // Input Capture 5

    INT_CN,                // Input Change

    INT_SPI1E,             // SPI 1 Fault
    INT_SPI2E,             // SPI 2 Fault
    INT_SPI1TX,            // SPI 1 Transfer Done
    INT_SPI2TX,            // SPI 2 Transfer Done
    INT_SPI1RX,            // SPI 1 Receive Done
    INT_SPI2RX,            // SPI 2 Receive Done
    INT_SPI1,
    INT_SPI2,

    INT_U1E,               // UART 1 Error
    INT_U2E,               // UART 2 Error
    INT_U1RX,              // UART 1 Receiver
    INT_U2RX,              // UART 2 Receiver
    INT_U1TX,              // UART 1 Transmitter
    INT_U2TX,              // UART 2 Transmitter
    INT_UART1,
    INT_UART2,

    INT_I2C1B,             // I2C 1 Bus Colision Event
    INT_I2C2B,             // I2C 1 Bus Colision Event
    INT_I2C1S,             // I2C 1 Slave Event
    INT_I2C2S,             // I2C 2 Slave Event
    INT_I2C1M,             // I2C 1 Master Event
    INT_I2C2M,             // I2C 2 Master Event
    INT_I2C1,
    INT_I2C2,

    INT_AD1,               // ADC 1 Convert Done

    INT_PMP,               // Parallel Master Port

    INT_CMP1,              // Comparator 1 Interrupt
    INT_CMP2,              // Comparator 2 Interrupt

    INT_FSCM,              // Fail-safe Monitor

    INT_FCE,               // Flash Control Event

    INT_RTCC,              // Real Time Clock

    INT_DMA0,              // DMA Channel 0
    INT_DMA1,              // DMA Channel 1
    INT_DMA2,              // DMA Channel 2
    INT_DMA3,              // DMA Channel 3
    INT_DMA4,              // DMA Channel 4
    INT_DMA5,              // DMA Channel 5
    INT_DMA6,              // DMA Channel 6
    INT_DMA7,              // DMA Channel 7

    INT_USB,               // USB

    INT_NUM
}INT_SOURCE;

// *****************************************************************************
/* Interrupt Muli-Channel Converter 

  Summary:
    Interrupt Muli-Channel Converter definitions

  Description:
    These definitions can be used to convert a channel into the correct INT_SOURCE value.
*/
#define INT_SOURCE_CORE_SW(chn)         (INT_CS0 + (chn))           // Core Software Interrupt Channel
#define INT_SOURCE_EX_INT(chn)          (INT_INT0 + (chn))          // External Interrupt Channel
#define INT_SOURCE_TIMER(chn)           (INT_T1 + (chn))            // Timer Interrupt Channel
#define INT_SOURCE_INPUT_CAP(chn)       (INT_IC1 + (chn))           // Intput Capture Interrupt Channel
#define INT_SOURCE_OUTPUT_COM(chn)      (INT_OC1 + (chn))           // Output Compare Interrupt Channel
#define INT_SOURCE_SPI(chn)             ((INT_SPI1 - 1) + (chn))    // SPI Interrupt Channel
#define INT_SOURCE_SPI_ERROR(chn)       ((INT_SPI1E - 1) + (chn))   // SPI Error Interrupt Channel
#define INT_SOURCE_SPI_TX(chn)          ((INT_SPI1TX - 1) + (chn))  // SPI Transmit Interrupt Channel
#define INT_SOURCE_SPI_RX(chn)          ((INT_SPI1RX - 1) + (chn))  // SPI Receive Interrupt Channel
#define INT_SOURCE_I2C(chn)             (INT_I2C1 + (chn))          // I2C Interrupt Channel
#define INT_SOURCE_I2C_ERROR(chn)       (INT_I2C1B + (chn))         // I2C Bus Collision Interrupt Channel
#define INT_SOURCE_I2C_SLAVE(chn)       (INT_I2C1S + (chn))         // I2C Slave Interrupt Channel
#define INT_SOURCE_I2C_MASTER(chn)      (INT_I2C1M + (chn))         // I2C Master Interrupt Channel
#define INT_SOURCE_UART(chn)            (INT_UART1 + (chn))           // UART Interrupt Channel
#define INT_SOURCE_UART_ERROR(chn)      (INT_U1E + (chn))          // UART Error Interrupt Channel
#define INT_SOURCE_UART_RX(chn)         (INT_U1RX + (chn))         // UART Receive Interrupt Channel
#define INT_SOURCE_UART_TX(chn)         (INT_U1TX + (chn))         // UART Transmit Interrupt Channel
#define INT_SOURCE_DMA(chn)             (INT_DMA0 + (chn))          // DMA Interrupt Channel

// *****************************************************************************
/* Interrupt Vector

  Summary:
    Interrupt Vector definitions (5xx/6xx/7xx family)

  Description:
    These definitions can be used to set or get the state of the interrupt vector 
    priority and sub-priority.
*/
typedef enum
{
    INT_CORE_TIMER_VECTOR,            // Core Timer Interrupt

    INT_CORE_SOFTWARE_0_VECTOR,       // Core Software Interrupt 0
    INT_CORE_SOFTWARE_1_VECTOR,       // Core Software Interrupt 1

    INT_EXTERNAL_0_VECTOR,            // External Interrupt 0
    INT_EXTERNAL_1_VECTOR,            // External Interrupt 1
    INT_EXTERNAL_2_VECTOR,            // External Interrrupt 2
    INT_EXTERNAL_3_VECTOR,            // External Interrupt 3
    INT_EXTERNAL_4_VECTOR,            // External Interupt 4

    INT_TIMER_1_VECTOR,               // Timer 1
    INT_TIMER_2_VECTOR,               // Timer 2
    INT_TIMER_3_VECTOR,               // TImer 3
    INT_TIMER_4_VECTOR,               // Timer 4
    INT_TIMER_5_VECTOR,               // Timer 5
    
    INT_INPUT_CAPTURE_1_VECTOR,       // Input Capture 1
    INT_INPUT_CAPTURE_2_VECTOR,       // Input Capture 2
    INT_INPUT_CAPTURE_3_VECTOR,       // Input Capture 3
    INT_INPUT_CAPTURE_4_VECTOR,       // Input Capture 4
    INT_INPUT_CAPTURE_5_VECTOR,       // Input Capture 5
    
    INT_OUTPUT_COMPARE_1_VECTOR,       // Output Compare 1
    INT_OUTPUT_COMPARE_2_VECTOR,       // Output Compare 2
    INT_OUTPUT_COMPARE_3_VECTOR,       // Output Compare 3
    INT_OUTPUT_COMPARE_4_VECTOR,       // Output Compare 4
    INT_OUTPUT_COMPARE_5_VECTOR,       // Output Compare 5

    INT_SPI_1_VECTOR,                 // SPI 1 vector
    INT_SPI_2_VECTOR,                 // SPI 2 vector

    INT_UART_1_VECTOR,               // UART 1 vector
    INT_UART_2_VECTOR,               // UART 2 vector

    INT_I2C_1_VECTOR,                 // I2C 1 vector
    INT_I2C_2_VECTOR,                 // I2C 2 vector

    INT_CHANGE_NOTICE_VECTOR,         // Change Notice
    INT_ADC_VECTOR,                   // ADC 1 Convert Done
    INT_PMP_VECTOR,                   // Parallel Master Port
    
    INT_COMPARATOR_1_VECTOR,          // Comparator 1 Interrupt
    INT_COMPARATOR_2_VECTOR,          // Comparator 2 Interrupt
    
    INT_FAIL_SAFE_MONITOR_VECTOR,     // Fail-safe Monitor
    INT_RTCC_VECTOR,                  // Real Time Clock

    INT_DMA_0_VECTOR,                 // DMA Channel 0
    INT_DMA_1_VECTOR,                 // DMA Channel 1
    INT_DMA_2_VECTOR,                 // DMA Channel 2
    INT_DMA_3_VECTOR,                 // DMA Channel 3
    INT_DMA_4_VECTOR,                 // DMA Channel 4
    INT_DMA_5_VECTOR,                 // DMA Channel 5
    INT_DMA_6_VECTOR,                 // DMA Channel 6
    INT_DMA_7_VECTOR,                 // DMA Channel 7

    INT_FCE_VECTOR,                   // Flash Control Event

    INT_USB_1_VECTOR,                 // USB
    

}INT_VECTOR;

// *****************************************************************************
/* Interrupt Muli-Channel Converter 

  Summary:
    Interrupt Muli-Channel Converter definitions

  Description:
    These definitions can be used to convert a channel into the correct INT_VECTOR value.
*/
// Core Software Interrupt Channel
#define INT_VECTOR_CORE_SW(chn)         /*DOM-IGNORE-BEGIN*/(INT_CORE_SOFTWARE_0_VECTOR + (chn))    /*DOM-IGNORE-END*/
// External Interrupt Channel
#define INT_VECTOR_EX_INT(chn)          /*DOM-IGNORE-BEGIN*/(INT_EXTERNAL_0_VECTOR + (chn))         /*DOM-IGNORE-END*/
// Timer Interrupt Channel
#define INT_VECTOR_TIMER(chn)           /*DOM-IGNORE-BEGIN*/(INT_TIMER_1_VECTOR + (chn))            /*DOM-IGNORE-END*/
// Input Capture Interrupt Channel
#define INT_VECTOR_INPUT_CAP(chn)       /*DOM-IGNORE-BEGIN*/(INT_INPUT_CAPTURE_1_VECTOR + (chn))    /*DOM-IGNORE-END*/
// Output Compare Interrupt Channel
#define INT_VECTOR_OUTPUT_COM(chn)      /*DOM-IGNORE-BEGIN*/(INT_OUTPUT_COMPARE_1_VECTOR + (chn))   /*DOM-IGNORE-END*/
// SPI Interrupt Channel
#define INT_VECTOR_SPI(chn)             /*DOM-IGNORE-BEGIN*/((INT_SPI_1_VECTOR - 1) + (chn))        /*DOM-IGNORE-END*/
// I2C Interrupt Channel
#define INT_VECTOR_I2C(chn)             /*DOM-IGNORE-BEGIN*/(INT_I2C_1_VECTOR + (chn))              /*DOM-IGNORE-END*/
// UART Interrupt Channel
#define INT_VECTOR_UART(chn)            /*DOM-IGNORE-BEGIN*/(INT_UART_1_VECTOR + (chn))            /*DOM-IGNORE-END*/
// DMA Interrupt Channel
#define INT_VECTOR_DMA(chn)             /*DOM-IGNORE-BEGIN*/(INT_DMA_0_VECTOR + (chn))              /*DOM-IGNORE-END*/

#endif
