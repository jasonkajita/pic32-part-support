/*******************************************************************************
    PIC32MX Interrupt

  Summary:
    This file contains Application Program Interface (API definitions for the
    Interrupt peripheral library.

  Description:
    This library provides a low-level abstraction of the interrupt controller
    module on Microchip PIC32MX family microcontrollers with a 
    convenient C language interface.  It can be used to simplify low-level
    access to the module without the necessity of interacting directly with the 
    module's registers, thus hiding differences from one microcontroller 
    variant to another.
*******************************************************************************/
//DOM-IGNORE-BEGIN
/*******************************************************************************
FileName:       int_5xx_6xx_7xx.h
Processor:      PIC32MX
Compiler:       Microchip MPLAB C32 v1.02 or higher

Copyright © 2008-2009 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
//DOM-IGNORE-END

#ifndef _PIC32INT_5XX_6XX_7XX_HEADER_FILE
#define _PIC32INT_5XX_6XX_7XX_HEADER_FILE

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
#include <peripheral/legacy/int_5xx_6xx_7xx_legacy.h>
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Constants & Data Types
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Interrupt Source

  Summary:
    Interrupt source definitions (PIC32MX5xx/6xx/7xx family).

  Description:
    These definitions can be used to set or get the state of the interrupt source flag and
    interrupt enable.
*/
typedef enum
{
    INT_CT = 0,             // Core Timer Interrupt
                            
    INT_CS0,                // Core Software Interrupt 0
    INT_CS1,                // Core Software Interrupt 1
                            
    INT_INT0,               // External Interrupt 0
    INT_INT1,               // External Interrupt 1
    INT_INT2,               // External Interrrupt 2
    INT_INT3,               // External Interrupt 3
    INT_INT4,               // External Interupt 4
                            
    INT_T1,                 // Timer1
    INT_T2,                 // Timer2
    INT_T3,                 // TImer3
    INT_T4,                 // Timer4
    INT_T5,                 // Timer5

    INT_IC1,                // Input Capture 1
    INT_IC2,                // Input Capture 2
    INT_IC3,                // Input Capture 3
    INT_IC4,                // Input Capture 4
    INT_IC5,                // Input Capture 5

    INT_IC1E,               // Input Capture Error 1
    INT_IC2E,               // Input Capture Error 2
    INT_IC3E,               // Input Capture Error 3
    INT_IC4E,               // Input Capture Error 4
    INT_IC5E,               // Input Capture Error 5

    INT_OC1,                // Output Compare 1
    INT_OC2,                // Output Compare 2
    INT_OC3,                // Output Compare 3
    INT_OC4,                // Output Compare 4
    INT_OC5,                // Output Compare 5

    INT_CN,                 // Change Notice

    INT_SPI1,               // SPI1 Vector
    INT_SPI2,               // SPI2 Vector
    INT_SPI3,               // SPI3 Vector
    INT_SPI4,               // SPI4 Vector
    
    INT_SPI1E,              // SPI1 Fault
    INT_SPI2E,              // SPI2 Fault
    INT_SPI3E,              // SPI3 Fault
    INT_SPI4E,              // SPI4 Fault

    INT_SPI1TX,             // SPI1 Transfer Done
    INT_SPI2TX,             // SPI2 Transfer Done
    INT_SPI3TX,             // SPI3 Transfer Done
    INT_SPI4TX,             // SPI4 Transfer Done

    INT_SPI1RX,             // SPI1 Receive Done
    INT_SPI2RX,             // SPI2 Receive Done
    INT_SPI3RX,             // SPI3 Receive Done
    INT_SPI4RX,             // SPI4 Receive Done

    INT_I2C1,               // I2C1 Vector
    INT_I2C2,               // I2C2 Vector
    INT_I2C3,               // I2C3 Vector
    INT_I2C4,               // I2C4 Vector
    INT_I2C5,               // I2C5 Vector

    INT_I2C1B,              // I2C1 Bus Colision Event
    INT_I2C2B,              // I2C2 Bus Colision Event
    INT_I2C3B,              // I2C3 Bus Colision Event
    INT_I2C4B,              // I2C4 Bus Colision Event
    INT_I2C5B,              // I2C5 Bus Colision Event

    INT_I2C1S,              // I2C1 Slave Event
    INT_I2C2S,              // I2C2 Slave Event
    INT_I2C3S,              // I2C3 Slave Event
    INT_I2C4S,              // I2C4 Slave Event
    INT_I2C5S,              // I2C5 Slave Event

    INT_I2C1M,              // I2C1 Master Event
    INT_I2C2M,              // I2C2 Master Event
    INT_I2C3M,              // I2C3 Master Event
    INT_I2C4M,              // I2C4 Master Event
    INT_I2C5M,              // I2C5 Master Event

    INT_U1,                 // UART1 Vector
    INT_U2,                 // UART2 Vector
    INT_U3,                 // UART3 Vector    
    INT_U4,                 // UART4 Vector
    INT_U5,                 // UART5 Vector
    INT_U6,                 // UART6 Vector

    INT_U1E,                // UART1 Error Event
    INT_U2E,                // UART2 Error Event
    INT_U3E,                // UART3 Error Event   
    INT_U4E,                // UART4 Error Event
    INT_U5E,                // UART5 Error Event
    INT_U6E,                // UART6 Error Event

    INT_U1RX,               // UART1 RX Event
    INT_U2RX,               // UART2 RX Event
    INT_U3RX,               // UART3 RX Event   
    INT_U4RX,               // UART4 RX Event
    INT_U5RX,               // UART5 RX Event
    INT_U6RX,               // UART6 RX Event

    INT_U1TX,               // UART1 TX Event
    INT_U2TX,               // UART2 TX Event
    INT_U3TX,               // UART3 TX Event    
    INT_U4TX,               // UART4 TX Event
    INT_U5TX,               // UART5 TX Event
    INT_U6TX,               // UART6 TX Event

    INT_AD1,                // ADC1 Convert Done

    INT_PMP,                // Parallel Master Port
    INT_PMPE,               // Parallel Master Port Error

    INT_CMP1,               // Comparator 1 Interrupt
    INT_CMP2,               // Comparator 2 Interrupt

    INT_FSCM,               // Fail-safe Monitor

    INT_FCE,                // Flash Control Event

    INT_RTCC,               // Real Time Clock

    INT_DMA0,               // DMA Channel 0
    INT_DMA1,               // DMA Channel 1
    INT_DMA2,               // DMA Channel 2
    INT_DMA3,               // DMA Channel 3
    INT_DMA4,               // DMA Channel 4
    INT_DMA5,               // DMA Channel 5
    INT_DMA6,               // DMA Channel 6
    INT_DMA7,               // DMA Channel 7
                            
    INT_USB,                // USB
                            
    INT_CAN1,               // CAN1
    INT_CAN2,               // CAN2

    INT_ETHERNET,           // Ethernet

    INT_NUM                 // Number of available interrupt soruces and vectors
}INT_SOURCE;

// *****************************************************************************
/* Interrupt Muli-Channel Converter 

  Summary:
    Interrupt muli-channel converter definitions.

  Description:
    These definitions can be used to convert a channel into the correct INT_SOURCE value.
*/
// Core Software Interrupt Channel.
#define INT_SOURCE_CORE_SW(chn)         /*DOM-IGNORE-BEGIN*/(INT_CS0 + (chn))           /*DOM-IGNORE-END*/        
// External Interrupt Channel.                                                       
#define INT_SOURCE_EX_INT(chn)          /*DOM-IGNORE-BEGIN*/(INT_INT0 + (chn))          /*DOM-IGNORE-END*/        
// Timer Interrupt Channel.                                                          
#define INT_SOURCE_TIMER(chn)           /*DOM-IGNORE-BEGIN*/(INT_T1 + (chn))            /*DOM-IGNORE-END*/        
// Input Capture Interrupt Channel.                                                 
#define INT_SOURCE_INPUT_CAP(chn)       /*DOM-IGNORE-BEGIN*/(INT_IC1 + (chn))           /*DOM-IGNORE-END*/        
// Output Compare Interrupt Channel.                                                 
#define INT_SOURCE_OUTPUT_COM(chn)      /*DOM-IGNORE-BEGIN*/(INT_OC1 + (chn))           /*DOM-IGNORE-END*/        
// SPI Interrupt Channel.
#define INT_SOURCE_SPI(chn)             /*DOM-IGNORE-BEGIN*/((INT_SPI1 - 1) + (chn))    /*DOM-IGNORE-END*/
// SPI Error Interrupt Channel.
#define INT_SOURCE_SPI_ERROR(chn)       /*DOM-IGNORE-BEGIN*/((INT_SPI1E - 1) + (chn))   /*DOM-IGNORE-END*/
// SPI Transmit Interrupt Channel.
#define INT_SOURCE_SPI_TX(chn)          /*DOM-IGNORE-BEGIN*/((INT_SPI1TX - 1) + (chn))  /*DOM-IGNORE-END*/
// SPI Receive Interrupt Channel.
#define INT_SOURCE_SPI_RX(chn)          /*DOM-IGNORE-BEGIN*/((INT_SPI1RX - 1) + (chn))  /*DOM-IGNORE-END*/
// I2C Interrupt Channel.
#define INT_SOURCE_I2C(chn)             /*DOM-IGNORE-BEGIN*/(INT_I2C1 + (chn))          /*DOM-IGNORE-END*/
// I2C Bus Collision Interrupt Channel.
#define INT_SOURCE_I2C_ERROR(chn)       /*DOM-IGNORE-BEGIN*/(INT_I2C1B + (chn))         /*DOM-IGNORE-END*/
// I2C Slave Interrupt Channel.
#define INT_SOURCE_I2C_SLAVE(chn)       /*DOM-IGNORE-BEGIN*/(INT_I2C1S + (chn))         /*DOM-IGNORE-END*/
// I2C Master Interrupt Channel.
#define INT_SOURCE_I2C_MASTER(chn)      /*DOM-IGNORE-BEGIN*/(INT_I2C1M + (chn))         /*DOM-IGNORE-END*/
// UART Interrupt Channel.
#define INT_SOURCE_UART(chn)            /*DOM-IGNORE-BEGIN*/(INT_U1 + (chn))            /*DOM-IGNORE-END*/
// UART Error Interrupt Channel.
#define INT_SOURCE_UART_ERROR(chn)      /*DOM-IGNORE-BEGIN*/(INT_U1E + (chn))           /*DOM-IGNORE-END*/
// UART Receive Interrupt Channel.
#define INT_SOURCE_UART_RX(chn)         /*DOM-IGNORE-BEGIN*/(INT_U1RX + (chn))          /*DOM-IGNORE-END*/
// UART Transmit Interrupt Channel.
#define INT_SOURCE_UART_TX(chn)         /*DOM-IGNORE-BEGIN*/(INT_U1TX + (chn))          /*DOM-IGNORE-END*/
// DMA Interrupt Channel.
#define INT_SOURCE_DMA(chn)             /*DOM-IGNORE-BEGIN*/(INT_DMA0 + (chn))          /*DOM-IGNORE-END*/
// CAN Interrupt Channel.
#define INT_SOURCE_CAN(chn)             /*DOM-IGNORE-BEGIN*/(INT_CAN1 + (chn))          /*DOM-IGNORE-END*/

// *****************************************************************************
/* Interrupt Vector

  Summary:
    Interrupt vector definitions (PIC32MX5xx/6xx/7xx family).

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

    INT_TIMER_1_VECTOR,               // Timer1
    INT_TIMER_2_VECTOR,               // Timer2
    INT_TIMER_3_VECTOR,               // TImer3
    INT_TIMER_4_VECTOR,               // Timer4
    INT_TIMER_5_VECTOR,               // Timer5
    
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

    INT_SPI_1_VECTOR,                 // SPI1 Vector
    INT_SPI_2_VECTOR,                 // SPI2 Vector
    INT_SPI_3_VECTOR,                 // SPI3 Vector
    INT_SPI_4_VECTOR,                 // SPI4 Vector

    INT_UART_1_VECTOR,                // UART1 Vector
    INT_UART_2_VECTOR,                // UART2 Vector
    INT_UART_3_VECTOR,                // UART3 Vector
    INT_UART_4_VECTOR,                // UART4 Vector
    INT_UART_5_VECTOR,                // UART5 Vector
    INT_UART_6_VECTOR,                // UART6 Vector
    
    INT_I2C_1_VECTOR,                 // I2C1 Vector
    INT_I2C_2_VECTOR,                 // I2C2 Vector
    INT_I2C_3_VECTOR,                 // I2C3 Vector
    INT_I2C_4_VECTOR,                 // I2C4 Vector
    INT_I2C_5_VECTOR,                 // I2C5 Vector

    INT_CHANGE_NOTICE_VECTOR,         // Change Notice
    INT_ADC_VECTOR,                   // ADC1 Convert Done
    INT_PMP_VECTOR,                   // Parallel Master Port
    
    INT_COMPARATOR_1_VECTOR,          // Comparator 1 Interrupt
    INT_COMPARATOR_2_VECTOR,          // Comparator 2 Interrupt
    
    INT_FAIL_SAFE_MONITOR_VECTOR,     // Fail-safe Monitor
    INT_RTCC_VECTOR,                  // Real-Time Clock

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
    
    INT_CAN_1_VECTOR,                 // CAN1
    INT_CAN_2_VECTOR,                 // CAN2
    
    INT_ETH_VECTOR                   // Ethernet 
    

}INT_VECTOR;

// *****************************************************************************
/* Interrupt Muli-Channel Converter 

  Summary:
    Interrupt muli-channel converter definitions.

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
#define INT_VECTOR_UART(chn)            /*DOM-IGNORE-BEGIN*/(INT_UART_1_VECTOR + (chn))             /*DOM-IGNORE-END*/
// DMA Interrupt Channel
#define INT_VECTOR_DMA(chn)             /*DOM-IGNORE-BEGIN*/(INT_DMA_0_VECTOR + (chn))              /*DOM-IGNORE-END*/
// CAN Interrupt Channel
#define INT_VECTOR_CAN(chn)             /*DOM-IGNORE-BEGIN*/(INT_CAN_1_VECTOR + (chn))              /*DOM-IGNORE-END*/

#endif

