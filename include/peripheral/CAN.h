/*******************************************************************************
  CAN Library Interface Definition

  Summary:
    This file contains the Application Program Interface (API) definition  for 
    the CAN peripheral library.
    
  Description:
    This library provides a low-level abstraction of the CAN (Controller Area
    Network) module on Microchip PIC32MX family microcontrollers with a 
    convenient C language interface.  It can be used to simplify low-level
    access to the module without the necessity of interacting directly with the 
    module's registers, thus hiding differences from one microcontroller 
    variant to another.
*******************************************************************************/
//DOM-IGNORE-BEGIN
/*******************************************************************************
FileName:       can.h
Processor:      PIC32MX
Compiler:       Microchip MPLAB C32 v1.06 or higher

Copyright © 2008-2009 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
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


#ifndef _CAN_H_
#define _CAN_H_

#include <p32xxxx.h>
#include <sys/kmem.h>

// *****************************************************************************
// *****************************************************************************
// Section: Constants & Data Types
// *****************************************************************************
// *****************************************************************************

// Size of CAN TX and Full Receive RX Message Buffer in bytes.
#define CAN_TX_RX_MESSAGE_SIZE_BYTES 16    

// Size of CAN Data-Only RX Message Buffer in bytes.
#define CAN_RX_DATA_ONLY_SIZE_BYTES 8   


// *****************************************************************************
/* CAN Module

  Summary:
    Identifies the supported CAN Modules.

  Description:
    This enumeration identifies the available CAN modules.
*/

typedef enum  
{
#ifdef _CAN1
    CAN1,   // CAN Module 1 ID.
#endif

#ifdef _CAN2
    CAN2,    // CAN Module 2 ID.
#endif

    CAN_NUMBER_OF_MODULES   // Number of available CAN modules.

}CAN_MODULE;



// *****************************************************************************
/* CAN Channel

  Summary:
    Identifies the supported CAN Channels.

  Description:
    This enumeration identifies the available CAN channels. Each CAN channel
    can be configured to trasnmit and receive messages.    
*/   

typedef enum 
{
	CAN_CHANNEL0,       // Channel 0 ID
	CAN_CHANNEL1,       // Channel 1 ID
	CAN_CHANNEL2,       // Channel 2 ID
	CAN_CHANNEL3,       // Channel 3 ID
	CAN_CHANNEL4,       // Channel 4 ID
	CAN_CHANNEL5,       // Channel 5 ID
	CAN_CHANNEL6,       // Channel 6 ID
	CAN_CHANNEL7,       // Channel 7 ID
	CAN_CHANNEL8,       // Channel 8 ID
	CAN_CHANNEL9,       // Channel 9 ID
	CAN_CHANNEL10,      // Channel 10 ID
	CAN_CHANNEL11,      // Channel 11 ID
	CAN_CHANNEL12,      // Channel 12 ID
	CAN_CHANNEL13,      // Channel 13 ID
	CAN_CHANNEL14,      // Channel 14 ID
	CAN_CHANNEL15,      // Channel 15 ID
	CAN_CHANNEL16,      // Channel 16 ID
	CAN_CHANNEL17,      // Channel 17 ID
	CAN_CHANNEL18,      // Channel 18 ID
	CAN_CHANNEL19,      // Channel 19 ID
	CAN_CHANNEL20,      // Channel 20 ID
	CAN_CHANNEL21,      // Channel 21 ID
	CAN_CHANNEL22,      // Channel 22 ID
	CAN_CHANNEL23,      // Channel 23 ID
	CAN_CHANNEL24,      // Channel 24 ID
	CAN_CHANNEL25,      // Channel 25 ID
	CAN_CHANNEL26,      // Channel 26 ID
	CAN_CHANNEL27,      // Channel 27 ID
	CAN_CHANNEL28,      // Channel 28 ID
	CAN_CHANNEL29,      // Channel 29 ID
	CAN_CHANNEL30,      // Channel 30 ID
	CAN_CHANNEL31,      // Channel 31 ID
	CAN_ALL_CHANNELS    // This ID covers all channels. This ID can only
                        // be used with the CANAbortPendingTx() function.
		
}CAN_CHANNEL;

// *****************************************************************************
/* CAN Operation Mode

  Summary:
    Lists all possible CAN Module modes.

  Description:
    This enumerates all operating modes of the CAN module. The application
    should set the desired mode using the CANSetOperatingMode() function, and 
    should then use the CANGetOperatingMode() function to check if the CAN module
    has entered the requested mode. 
*/   

typedef enum 
{
    // CAN Normal Operation Mode. The CAN module
    // transmits and receives messages in this mode. 
	CAN_NORMAL_OPERATION,           

    // CAN Disable Mode. The CAN module does not transmit
    // or receive messages in this mode. 
	CAN_DISABLE,                   

    // CAN Loopback Mode. In this mode, the CAN module TX is
    // internally connected to the RX line. This mode is 
    // useful for debugging operation.  
	CAN_LOOPBACK,                   

    // CAN Listen Only Mode. In this mode, the CAN module will
    // not acknowledge signal and will not participate in error
    // signalling. All messages are captured.
	CAN_LISTEN_ONLY,                

    // CAN Configuration Mode. Various CAN module settings 
    // can be configured in this mode.
	CAN_CONFIGURATION,              

    // CAN Listen All Message Mode. The CAN module listens to all
    // messages, regardless of errors.
	CAN_LISTEN_ALL_MESSAGES = 7     

}CAN_OP_MODE;

// *****************************************************************************
/* CAN Channel Event

  Summary:
    Identifies all possible CAN Channel events.

  Description:
    This enumerates all CAN RX and TX channel events. This enumeration can be used
    to enable or disable channel events and as a mask to check if a channel event is
    active.
    A single or a combination of the events can be logically OR'ed to specify the
    event(s) to be enabled disabled or events to check. The CAN_RX_CHANNEL_xx_xx 
    events should only be used with a RX channel. The CAN_TX_CHANNEL_xx_xx events 
    should only be used with a TX channel. The CAN_xx_CHANNEL_ANY EVENT can be used
    to enable or disable all events or to check if any channel event is active.

    This enumeration is used by the CANGetChannelEvent() and CANEnableChannelEvent()
    functions.
*/   

typedef enum 
{
	CAN_RX_CHANNEL_NOT_EMPTY 	= 0x1,      // CAN RX Channel Not Empty Event Mask
	CAN_RX_CHANNEL_HALF_FULL 	= 0x2,      // CAN RX Channel Half Full Event Mask
	CAN_RX_CHANNEL_FULL 		= 0x4,      // CAN RX Channel Full Event Mask
	CAN_RX_CHANNEL_OVERFLOW 	= 0x8,      // CAN RX Channel Overflow Event Mask
	CAN_RX_CHANNEL_ANY_EVENT 	= 0xF,      // CAN RX Channel Any Event Mask
	CAN_TX_CHANNEL_EMPTY 		= 0x100,    // CAN TX Channel Empty Event Mask
	CAN_TX_CHANNEL_HALF_EMPTY 	= 0x200,    // CAN TX Channel Half Empty Event Mask
	CAN_TX_CHANNEL_NOT_FULL		= 0x400,    // CAN TX Channel Not Full Event Mask
	CAN_TX_CHANNEL_ANY_EVENT 	= 0x700     // CAN TX Channel Any Event Mask

}CAN_CHANNEL_EVENT;

// *****************************************************************************
/* CAN bit Time Quanta

  Summary:
    All possible values for the assignable number of Time Quanta. 

  Description:
    This enumeration defines values that can be assigned while defining the 
    number of Time Quanta in a bit. 
*/   

typedef enum 
{
	CAN_BIT_1TQ,    // 1-bit Time Quanta
	CAN_BIT_2TQ,    // 2-bit Time Quanta
	CAN_BIT_3TQ,    // 3-bit Time Quanta
	CAN_BIT_4TQ,    // 4-bit Time Quanta
	CAN_BIT_5TQ,    // 5-bit Time Quanta
	CAN_BIT_6TQ,    // 6-bit Time Quanta
	CAN_BIT_7TQ,    // 7-bit Time Quanta
	CAN_BIT_8TQ     // 8-bit Time Quanta

}CAN_BIT_TQ;

// *****************************************************************************
/* CAN bit Configuration

  Summary:
    Configuration of number of bit Time quanta in a CAN bit. 

  Description:
    This data structure provides an interface to the CAN bit configuration parameters.
    Note that the bit configuration affects the CAN Bus Speed. The total number of 
    time quanta in a bit is between 8 and 25 inclusive.  Refer to the CAN Bus 
    specification for more details on  setting up the time quanta in a bit.

    This data type is used with the CANSetSpeed() function.
*/   

typedef struct 
{
    // Number of Time quanta in Phase Segment 2. 
    // This value can be between CAN_BIT_1TQ and CAN_BIT_8TQ
	CAN_BIT_TQ 	phaseSeg2Tq;           

    // Number of Time quanta in Phase Segment 1. 
    // This value can be between CAN_BIT_1TQ and CAN_BIT_8TQ
	CAN_BIT_TQ 	phaseSeg1Tq;

    // Number of Time quanta in Propagation Segment 2. 
    // This value can be between CAN_BIT_1TQ and CAN_BIT_8TQ
	CAN_BIT_TQ 	propagationSegTq;      
    
    // This determines if the Phase Segment 2  value is 
    // specified by code or set automatically by the module. 
    // TRUE - Phase Segment 2 can be set in code.
    // FALSE - Phase Segment 2 is set by module. 
	BOOL	 	phaseSeg2TimeSelect;    
                                        
    // This determines the number of times a bit is sampled by
    // the CAN module.. 
    // TRUE - bit is sampled 3 times.
    // FALSE - bit is sampled once. 
	BOOL 		sample3Time;

    // This determines the Synchronization jump width Time quanta. 
    // This value should be between CAN_BIT_1TQ and CAN_BIT_4TQ.
	CAN_BIT_TQ 	syncJumpWidth; 

}CAN_BIT_CONFIG;

// *****************************************************************************
/* CAN Event Code

  Summary:
    CAN Event Code returned by the CAN Module. 

  Description:
    This enumeration identifies all of the event codes returned by the 
    CANGetPendingEventCode() function. 
*/   

typedef enum 
{
	CAN_CHANNEL0_EVENT,     // An event on Channel 0 is active.
	CAN_CHANNEL1_EVENT,     // An event on Channel 1 is active.
	CAN_CHANNEL2_EVENT,     // An event on Channel 2 is active.
	CAN_CHANNEL3_EVENT,     // An event on Channel 3 is active.
	CAN_CHANNEL4_EVENT,     // An event on Channel 4 is active.
	CAN_CHANNEL5_EVENT,     // An event on Channel 5 is active.
	CAN_CHANNEL6_EVENT,     // An event on Channel 6 is active.
	CAN_CHANNEL7_EVENT,     // An event on Channel 7 is active.
	CAN_CHANNEL8_EVENT,     // An event on Channel 8 is active.
	CAN_CHANNEL9_EVENT,     // An event on Channel 9 is active.
	CAN_CHANNEL10_EVENT,    // An event on Channel 10  is active.
	CAN_CHANNEL11_EVENT,    // An event on Channel 11  is active.
	CAN_CHANNEL12_EVENT,    // An event on Channel 12  is active.
	CAN_CHANNEL13_EVENT,    // An event on Channel 13  is active.
	CAN_CHANNEL14_EVENT,    // An event on Channel 14  is active.
	CAN_CHANNEL15_EVENT,    // An event on Channel 15  is active.
	CAN_CHANNEL16_EVENT,    // An event on Channel 16  is active.
	CAN_CHANNEL17_EVENT,    // An event on Channel 17  is active.
	CAN_CHANNEL18_EVENT,    // An event on Channel 18  is active.
	CAN_CHANNEL19_EVENT,    // An event on Channel 19  is active.
	CAN_CHANNEL20_EVENT,    // An event on Channel 20  is active.
	CAN_CHANNEL21_EVENT,    // An event on Channel 21  is active.
	CAN_CHANNEL22_EVENT,    // An event on Channel 22  is active.
	CAN_CHANNEL23_EVENT,    // An event on Channel 23  is active.
	CAN_CHANNEL24_EVENT,    // An event on Channel 24  is active.
	CAN_CHANNEL25_EVENT,    // An event on Channel 25  is active.
	CAN_CHANNEL26_EVENT,    // An event on Channel 26  is active.
	CAN_CHANNEL27_EVENT,    // An event on Channel 27  is active.
	CAN_CHANNEL28_EVENT,    // An event on Channel 28  is active.
	CAN_CHANNEL29_EVENT,    // An event on Channel 29  is active.
	CAN_CHANNEL30_EVENT,    // An event on Channel 30  is active.
	CAN_CHANNEL31_EVENT,    // An event on Channel 31  is active.
	CAN_NO_EVENT = 0x40,    // No Event is active.
	CAN_ERROR_EVENT,        // CAN Bus Error Event is active.
	CAN_WAKEUP_EVENT,       // CAN Bus Wakeup Event is active.
	CAN_RX_CHANNEL_OVERFLOW_EVENT,  // CAN Receive Channel Overflow Event is active.
	CAN_ADDRESS_ERROR_EVENT,        // CAN Address Error Event is active.
	CAN_BUS_BANDWIDTH_ERROR,        // CAN Bus Bandwidth Error is active.
	CAN_TIMESTAMP_TIMER_EVENT,      // CAN Timestamp Timer Overflow event is active.
	CAN_MODE_CHANGE_EVENT,          // CAN Module Mode Change is active.
	CAN_INVALID_MESSAGE_RECEIVED_EVENT  // CAN Invalid Message Received Event active.

}CAN_EVENT_CODE;

// *****************************************************************************
/* CAN Filters

  Summary:
    Identifies the available CAN filters. 

  Description:
    This enumeration identifies the available filters in each CAN module.
*/   

typedef enum 
{
	CAN_FILTER0,        // CAN Filter 0 
	CAN_FILTER1,        // CAN Filter 1
	CAN_FILTER2,        // CAN Filter 2
	CAN_FILTER3,        // CAN Filter 3
	CAN_FILTER4,        // CAN Filter 4
	CAN_FILTER5,        // CAN Filter 5
	CAN_FILTER6,        // CAN Filter 6
	CAN_FILTER7,        // CAN Filter 7
	CAN_FILTER8,        // CAN Filter 8
	CAN_FILTER9,        // CAN Filter 9
	CAN_FILTER10,       // CAN Filter 10
	CAN_FILTER11,       // CAN Filter 11
	CAN_FILTER12,       // CAN Filter 12
	CAN_FILTER13,       // CAN Filter 13
	CAN_FILTER14,       // CAN Filter 14
	CAN_FILTER15,       // CAN Filter 15
	CAN_FILTER16,       // CAN Filter 16
	CAN_FILTER17,       // CAN Filter 17
	CAN_FILTER18,       // CAN Filter 18
	CAN_FILTER19,       // CAN Filter 19
	CAN_FILTER20,       // CAN Filter 20
	CAN_FILTER21,       // CAN Filter 21
	CAN_FILTER22,       // CAN Filter 22
	CAN_FILTER23,       // CAN Filter 23
	CAN_FILTER24,       // CAN Filter 24
	CAN_FILTER25,       // CAN Filter 25
	CAN_FILTER26,       // CAN Filter 26
	CAN_FILTER27,       // CAN Filter 27
	CAN_FILTER28,       // CAN Filter 28
	CAN_FILTER29,       // CAN Filter 29
	CAN_FILTER30,       // CAN Filter 30
	CAN_FILTER31,       // CAN Filter 31
    
    // Total number of filters in the 
    // module.
    
    CAN_NUMBER_OF_FILTERS   
                            

}CAN_FILTER;

// *****************************************************************************
/* CAN Filter Masks

  Summary:
    CAN Filter Masks Supported. 

  Description:
    This enumeration identifies the available filters masks in each CAN module.
*/   

typedef enum 
{
	CAN_FILTER_MASK0,   // CAN Filter Mask 0
	CAN_FILTER_MASK1,   // CAN Filter Mask 1
	CAN_FILTER_MASK2,   // CAN Filter Mask 2
	CAN_FILTER_MASK3,    // CAN Filter Mask 3
    
    // Total number os filter masks
    // in the module.
    
    CAN_NUMBER_OF_FILTER_MASKS

}CAN_FILTER_MASK;

// *****************************************************************************
/* CAN ID Type 

  Summary:
    Specifies the CAN ID Type. 

  Description:
    This enumeration specifies the two CAN ID types: Standard and Extended. The Standard
    Type ID is 11 bits long and the Extended ID is 29 bits long. This enumeration then
    specifies the type of the ID specified while configuring Filter and Filter masks.
*/   

typedef enum 
{
	CAN_EID,    // CAN Extended ID
	CAN_SID     // CAN Standard ID

}CAN_ID_TYPE;

// *****************************************************************************
/* CAN Transmit Channel Remote Transmit Request (RTR)

  Summary:
    Specifies the status of the CAN Remote Transmit Request (RTR) feature for
    a CAN TX Channel.

  Description:
    This enumeration specifies the status of the CAN Remote Transmit Request 
    feature for a CAN TX Channel. The RTR feature allows a node on the CAN Bus
    to request a transmission from another node on the bus. The responding node
    in this case should have a RTR enabled TX Channel in order to be able to
    respond to this request. 
*/

typedef enum  
{
	CAN_TX_RTR_ENABLED,   // CAN TX Channel RTR Feature is enabled.
	CAN_TX_RTR_DISABLED    // CAN TX Channel RTR Feature is disabled.

}CAN_TX_RTR;

// *****************************************************************************
/* CAN Receive Channel Data Only Mode

  Summary:
    Enables the Data Only Receive Mode or Full Receive Mode of a CAN Receive Channel.
    
  Description:
    This enumeration specifies the status of the CAN Receive Channel Data Only 
    feature. If the feature is enabled, the CAN module will store only the data
    payload portion of the received CAN message. If the Full Receive mode is 
    specified, the CAN module stores the entire CAN message (ID field plus data
    payload). The RX channel can either in Data Only mode or Full Receive Mode. 
*/

typedef enum  
{
	CAN_RX_DATA_ONLY,           // CAN RX Channel Data Only Mode is enabled.
	CAN_RX_FULL_RECEIVE    // CAN RX Channel Full Receive Mode is enabled.

}CAN_RX_DATA_MODE;

// *****************************************************************************
/* CAN Filter Mask Type 

  Summary:
    Specifies the CAN Filter Mask Type. 

  Description:
    This enumeration specifies the filter mask type. The filter mask can either
    process messages with any type of ID (extended or standard) or can only process
    by ID specified in the filter configuration. For example, if the filter associated
    with the mask only accepts EID type messages and if the mask is configured to process
    by ID type, then SID messages will not be accepted. If the mask is configured to 
    process any type of message, both SID and EID messages will be accepted on a filter
    match. 
*/

typedef enum 
{
	CAN_FILTER_MASK_IDE_TYPE,   // Mask processes only Filter type of message.
	CAN_FILTER_MASK_ANY_TYPE    // Mask processes any type (SID or EID) of message.

}CAN_FILTER_MASK_TYPE;

// *****************************************************************************
/* CAN TX Channel Priority 

  Summary:
    Specifies the priority of a TX channel. 

  Description:
    This enumeration identifies the available TX channel priorities. A TX channel
    has its own natural priority order, which determines priority when two or more
    TX channels are assigned the same priority level. Channel 1 has higher natural
    priority than Channel 0 and Channel 2 has a natural priority than Channel 1, and
    so on.
*/

typedef enum 
{
	CAN_LOWEST_PRIORITY,
	CAN_LOW_MEDIUM_PRIORITY,
	CAN_HIGH_MEDIUM_PRIORITY,
	CAN_HIGHEST_PRIORITY

}CAN_TXCHANNEL_PRIORITY;

// *****************************************************************************
/* CAN Device Net Filter Size 

  Summary:
    Specifies the size of the Device Net Filter. 

  Description:
    This enumeration identifies the size of the Device Net filter in bits. If the
    size of the Device Net filter is n, the n most significant bits of the data
    payload are compared with the EID field of enabled filters. 
*/

typedef enum 
{
	CAN_DNET_FILTER_DISABLE,        // Device Net Filtering is disabled.
	CAN_DNET_FILTER_SIZE_1_BIT,     // Device Net Filter is 1 bit long.
    CAN_DNET_FILTER_SIZE_2_BIT,     // Device Net Filter is 2 bits long.
    CAN_DNET_FILTER_SIZE_3_BIT,     // Device Net Filter is 3 bits long.
	CAN_DNET_FILTER_SIZE_4_BIT,     // Device Net Filter is 4 bits long.
	CAN_DNET_FILTER_SIZE_5_BIT,     // Device Net Filter is 5 bits long.
	CAN_DNET_FILTER_SIZE_6_BIT,     // Device Net Filter is 6 bits long.
	CAN_DNET_FILTER_SIZE_7_BIT,     // Device Net Filter is 7 bits long.
	CAN_DNET_FILTER_SIZE_8_BIT,     // Device Net Filter is 8 bits long.
	CAN_DNET_FILTER_SIZE_9_BIT,     // Device Net Filter is 9 bits long.
	CAN_DNET_FILTER_SIZE_10_BIT,     // Device Net Filter is 10 bits long.
	CAN_DNET_FILTER_SIZE_11_BIT,     // Device Net Filter is 11 bits long.
	CAN_DNET_FILTER_SIZE_12_BIT,     // Device Net Filter is 12 bits long.
	CAN_DNET_FILTER_SIZE_13_BIT,     // Device Net Filter is 13 bits long.
	CAN_DNET_FILTER_SIZE_14_BIT,     // Device Net Filter is 14 bits long.
	CAN_DNET_FILTER_SIZE_15_BIT,     // Device Net Filter is 15 bits long.
	CAN_DNET_FILTER_SIZE_16_BIT,     // Device Net Filter is 16 bits long.
	CAN_DNET_FILTER_SIZE_17_BIT,     // Device Net Filter is 17 bits long.
	CAN_DNET_FILTER_SIZE_18_BIT,     // Device Net Filter is 18 bits long.
	
}CAN_DNET_FILTER_SIZE;

// *****************************************************************************
/* CAN Module Events 

  Summary:
    Specifies the CAN module events. 

  Description:
    This enumeration identifies all of the CAN module events. A combination of listed
    events can be logically OR'ed to enable or disable module level events. Similarly,
    a combination of events can be checked if active.

    This enumeration is used with the CANEnableModuleEvent() and CANGetModuleEvent()
    functions. 
*/


typedef enum 
{
    // TX channel event. This event will occur
    // if any of the TX Channel events are active.  
	CAN_TX_EVENT 						= 0x1,

    // RX channel event. This event will occur
    // if any of the RX Channel events are active.
	CAN_RX_EVENT 						= 0x2,

    // CAN Timer Stamp Timer Overflow event occurs.
    // This event occurs when the Timestamp Timer has
    // overflowed. 
	CAN_TIMESTAMP_TIMER_OVERFLOW_EVENT 	= 0x4,

    // CAN Operation Mode Change Event. This event
    // occurs when the CAN module has changed it's
    // operating mode successfully.
	CAN_OPERATION_MODE_CHANGE_EVENT 	= 0x8,

    // CAN RX Channel Overflow Event. This event occurs
    // when any of the RX Channel has overflowed.
    CAN_RX_OVERFLOW_EVENT 				= 0x800,

    // CAN System Error Event. This event occurs when
    // CAN module tries to access an invalid Device RAM
    // location.
	CAN_SYSTEM_ERROR_EVENT 				= 0x1000,

    // CAN Bus Error Event. This event occurs when the 
    // CAN module cannot access the system bus.
	CAN_BUS_ERROR_EVENT 				= 0x2000,

    // CAN Bus Actvity Wakeup. This event occurs when the
    // device is in sleep mode and bus activity is detected
    // on the CAN bus.
	CAN_BUS_ACTIVITY_WAKEUP_EVENT		= 0x4000,

    // CAN Bus Invalid RX Message Event. This event occurs
    // when the CAN module receives an Invalid message.
	CAN_INVALID_RX_MESSAGE_EVENT 		= 0x8000

}CAN_MODULE_EVENT;

// *****************************************************************************
/* CAN Error States 

  Summary:
    Specifies the CAN Module Error States. 

  Description:
    This enumeration identifies all the CAN module error states events. The
    CAN module enters or exits an error state as the Transmit and Receive 
    Error Counter values change. Refer to the CAN specification for more 
    details on the error states.

    This enumeration is used with the CANGetErrorState() function. 
*/

typedef enum 
{
    // CAN Module is in a TX or RX warning state.
	CAN_TX_RX_WARNING_STATE 	= 0x10000,

    // CAN Module is in a RX warning state.
	CAN_RX_WARNING_STATE 		= 0x20000,

    // CAN Module is in a TX warning state.
	CAN_TX_WARNING_STATE 		= 0x40000,

    // CAN RX is in a Bus Passive state.
	CAN_RX_BUS_PASSIVE_STATE 	= 0x80000,
	
    // CAN TX is in a Bus Passive state.
    CAN_TX_BUS_PASSIVE_STATE 	= 0x100000,

    // CAN TX is in Bus Off state.
	CAN_TX_BUS_OFF_STATE 		= 0x200000

}CAN_ERROR_STATE;

// *****************************************************************************
/* CAN Module Features 

  Summary:
    Specifies other CAN Module features. 

  Description:
    This enumeration identifies some of the CAN module features that need to be
    configured as a part of the CAN module intialization. A combination of the
    enumeration members can be logically OR'ed as a parameter to enable or disable
    features.

    This enumeration is used with the CANEnableFeature() function.
*/

typedef enum 
{
    // Specifies if the CAN module is running
    // while CPU is in IDLE mode.
	CAN_STOP_IN_IDLE = 0x2000,

    // Specifies if the CAN module will timestamp
    // every received message.
	CAN_RX_TIMESTAMP = 0x100000,

    // Specifies if the CAN Wake up on bus activity
    // RX line filter is enabled.
	CAN_WAKEUP_BUS_FILTER = 0x400000

}CAN_MODULE_FEATURES;

// *****************************************************************************
/* CAN Channel Masks 

  Summary:
    Lists series of useful masks.  

  Description:
    This enumeration identifies a series of useful masks. Each mask represents a 
    CAN channel. These masks are used  with the CANGetAllChannelEventStatus() and
    CANGetAllChannelOverflowStatus() functions. The value returned by these functions
    can be logically AND'ed with any of these masks to check if an event or overflow
    event for that channel is active. 
*/

typedef enum 
{
	CAN_CHANNEL0_MASK  = 0x00000001,    // Channel 0 Mask
	CAN_CHANNEL1_MASK  = 0x00000002,    // Channel 1 Mask
	CAN_CHANNEL2_MASK  = 0x00000004,    // Channel 2 Mask
	CAN_CHANNEL3_MASK  = 0x00000008,    // Channel 3 Mask
	CAN_CHANNEL4_MASK  = 0x00000010,    // Channel 4 Mask
	CAN_CHANNEL5_MASK  = 0x00000020,    // Channel 5 Mask
	CAN_CHANNEL6_MASK  = 0x00000040,    // Channel 6 Mask
	CAN_CHANNEL7_MASK  = 0x00000080,    // Channel 7 Mask
	CAN_CHANNEL8_MASK  = 0x00000100,    // Channel 8 Mask
	CAN_CHANNEL9_MASK  = 0x00000200,    // Channel 9 Mask
	CAN_CHANNEL10_MASK = 0x00000400,    // Channel 10 Mask
	CAN_CHANNEL11_MASK = 0x00000800,    // Channel 11 Mask
	CAN_CHANNEL12_MASK = 0x00001000,    // Channel 12 Mask
	CAN_CHANNEL13_MASK = 0x00002000,    // Channel 13 Mask
	CAN_CHANNEL14_MASK = 0x00004000,    // Channel 14 Mask
	CAN_CHANNEL15_MASK = 0x00008000,    // Channel 15 Mask
	CAN_CHANNEL16_MASK = 0x00010000,    // Channel 16 Mask
	CAN_CHANNEL17_MASK = 0x00020000,    // Channel 17 Mask
	CAN_CHANNEL18_MASK = 0x00040000,    // Channel 18 Mask
	CAN_CHANNEL19_MASK = 0x00080000,    // Channel 19 Mask
	CAN_CHANNEL20_MASK = 0x00100000,    // Channel 20 Mask
	CAN_CHANNEL21_MASK = 0x00200000,    // Channel 21 Mask
	CAN_CHANNEL22_MASK = 0x00400000,    // Channel 22 Mask
	CAN_CHANNEL23_MASK = 0x00800000,    // Channel 23 Mask
	CAN_CHANNEL24_MASK = 0x01000000,    // Channel 24 Mask
	CAN_CHANNEL25_MASK = 0x02000000,    // Channel 25 Mask
	CAN_CHANNEL26_MASK = 0x04000000,    // Channel 26 Mask
	CAN_CHANNEL27_MASK = 0x08000000,    // Channel 27 Mask
	CAN_CHANNEL28_MASK = 0x10000000,    // Channel 28 Mask
	CAN_CHANNEL29_MASK = 0x20000000,    // Channel 29 Mask
	CAN_CHANNEL30_MASK = 0x40000000,    // Channel 30 Mask
	CAN_CHANNEL31_MASK = 0x80000000,    // Channel 31 Mask
	CAN_ANYCHANNEL_MASK = 0xFFFFFFFF    // Channel any channel Mask

}CAN_CHANNEL_MASK;

// *****************************************************************************
/* CAN TX Channel Condition 

  Summary:
    Possible TX Channel Specific Conditions.  

  Description:
    This enumeration identifies the possible TX channel condition. These masks can 
    be logically AND'ed with values returned by the CANGetTxChannelCondition() 
    function to check if a condition is active.
*/


typedef enum 
{
    // CAN TX Channel is currently Transmitting.
	CAN_TX_CHANNEL_TRANSMITTING = 0x8,

    // CAN TX Channel Error has occurred.
	CAN_TX_CHANNEL_ERROR = 0x10,

    // CAN TX Channel lost arbitration.
	CAN_TX_CHANNEL_ARBITRATION_LOST = 0x20

}CAN_TX_CHANNEL_CONDITION;

// *****************************************************************************
/* CAN TX Message SID Word  

  Summary:
    Defines the structure of the SID word section of the TX message.  

  Description:
    This data structure represents the SID section of the CAN TX message. The data
    data structure is an element of the CANTxMessageBuffer data structure. 
*/

typedef	struct 
{
    // CAN TX Message Standard ID. This value should
    // be between 0x0 - 0x7FF.
	unsigned SID:11;
	unsigned :21;
}CAN_TX_MSG_SID;

// *****************************************************************************
/* CAN Message EID Word  

  Summary:
    Defines the structure of the EID word section of the TX and RX message.  

  Description:
    This data structure represents the EID section of the CAN TX and RX message. 
    The data structure is an element of the CANTxMessageBuffer and CANRxMessageBuffer
    data structure. 
*/

typedef struct 
{
    // Data Length Control. Specifies the size of the
    // data payload section of the CAN packet. Valid 
    // values are 0x0 - 0x8.
	unsigned DLC:4;

    // Reserved bit. Should be always 0.
	unsigned RB0:1;
	unsigned :3;

    // Reserved bit. Should be always 0.
	unsigned RB1:1;

    // Remote Transmit Request bit. Should be set for
    // RTR messages, clear otherwise.
	unsigned RTR:1;

    // CAN TX and RX Extended ID field. Valid values
    // are in range 0x0 - 0x3FFFF. 
	unsigned EID:18;

    // Identifier bit. If 0 means that message is SID.
    // If 1 means that message is EID type.
	unsigned IDE:1;

    // Susbtitute Remote request bit. This bit should
    // always be clear for an EID message. It is ignored
    // for an SID message.
	unsigned SRR:1;
	unsigned :2;

}CAN_MSG_EID;

// *****************************************************************************
/* CAN TX Message Buffer  

  Summary:
    Defines the structure of the CAN TX Message Buffer.  

  Description:
    This data structure represents the CAN TX Message Buffer. This data structure
    should be used for writing data to a CAN TX channel and transmitting data. A 
    pointer to this type of data structure is returned by the CANGetTxMessageBuffer()
    function.

    The data structure allows the TX message buffer to be accessed as fields of a CAN
    TX message and also as an array of four 32-bit words. The latter allows for quick
    intialization of the message buffer.  
*/


typedef union {

	struct
	{
        // This is SID portion of the CAN TX message.
		CAN_TX_MSG_SID msgSID;

        // This is EID portion of the CAN TX message.
		CAN_MSG_EID msgEID;

        // This is the data portion of the CAN TX message.
		BYTE data[8];
	};

    // This is CAN TX message organized as a set of 32 bit 
    // words.
	UINT32 messageWord[4];

}CANTxMessageBuffer;

// *****************************************************************************
/* CAN RX Message SID Word  

  Summary:
    Defines the structure of the SID word section of the RX message.  

  Description:
    This data structure represents the SID section of the CAN RX message. The data
    data structure is an element of the CANRxMessageBuffer data structure. 
*/

typedef	struct 
{
    // SID of the Received CAN Message. 
	unsigned SID:11;

    // Filter which accepted this message.
	unsigned FILHIT:5;

    // Time stamp of the received message. This is
    // valid only if the Timestamping is enabled.
	unsigned CMSGTS:16;

}CAN_RX_MSG_SID;

// *****************************************************************************
/* CAN RX Message Buffer  

  Summary:
    Defines the structure of the CAN RX Message Buffer.  

  Description:
    This data structure represents the CAN RX Message Buffer. Received messages could
    be either full-receive messages or data-only messages. Full receive message contains
    the message header and data payload section.  For a full receive CAN RX channel, the
    caller should use the msgSID, msgEID and data members . A data-only message contains
    only a 8-byte data payload. While using this data structure with a Data-Only type of
    CAN RX channel, the caller should use the dataOnlyMsgData member of the structure and
    should read only 8 bytes of data.

     
*/

typedef union {

	struct
	{
        // This is SID portion of the CAN RX message.
		CAN_RX_MSG_SID msgSID;

        // This is EID portion of the CAN RX message
		CAN_MSG_EID msgEID;

        // This is the data payload section of the 
        // received message.
		BYTE data[8];
	};

    // This can be used if the message buffer is to 
    // be read from a Data-Only type of CAN RX Channel.
    BYTE dataOnlyMsgData[8];

    // This is CAN RX message organized as a set of 32 bit 
    // words.
	UINT32 messageWord[4];

}CANRxMessageBuffer;

// *****************************************************************************
// *****************************************************************************
// Section: Configuration and Related Functions
// *****************************************************************************
// *****************************************************************************

/********************************************************************************************
  Function:
      void CANAssignMemoryBuffer(CAN_MODULE module, void * buffer, UINT sizeInBytes);
    
  Summary:
    This routine assigns buffer memory to the CAN module.
  Description:
    This routine assigns buffer memory to the CAN module. The CAN module
    uses this buffer memory to store messages to be transmitted and
    received. The size of the memory buffer should be enough to accommodate
    the required number of message buffers and channels. Refer to <link Assign Buffer Memory>
    for more details on allocating buffer memory for use with the CAN
    module.
  
  PreCondition:
    The module should be in Configuration mode (using
    CANSetOperatingMode()).
  
  Parameters:
    module -       Identifies the desired CAN module.<p />
    
    buffer -       Pointer to the buffer memory area.<p />
    
    sizeInBytes -  Size of the buffer memory is bytes.
  
  Returns:
    None.  Example:
    <code>
    // Define and assign a CAN 1 memory buffer for 2 TX channels and 1 RX
    // channel, each with 4 message buffers.
    
    BYTE canMemoryBuffer [3 * 4 * CAN_TX_RX_MESSAGE_SIZE_BYTES];
    
    CANAssignMemoryBuffer(CAN1, canMemoryBuffer, (3 * 4 * CAN_TX_RX_MESSAGE_SIZE_BYTES));
    
    </code>
  Remarks:
    None.                                                                                    
  ********************************************************************************************/

void CANAssignMemoryBuffer(CAN_MODULE module, void * buffer, UINT sizeInBytes);

/*******************************************************************************
  Function:
    void CANSetOperatingMode(CAN_MODULE module, CAN_OP_MODE opmode);

  Summary:
    This routine sets the CAN operating mode. 

  Description:
    This routine sets the CAN operating mode. The CAN module requires itself to
    be in certain modes in order to gain access to module functionality. For 
    example, the module should be in Normal mode in order to send and receive
    messages. Note that after this function is called, it should be checked
    whether the mode was set by using the CANGetOperatingMode() function.

  Precondition:
    None.

  Parameters:
    module      - Identifies the desired CAN module.
    
    opmode      - Desired CAN_OP_MODE type of mode to be set.
    
  Returns:
    None.

  Example:
    <code>
    // Set the CAN1 operating mode to Configuration mode.
    
    CANSetOperatingMode(CAN1, CAN_CONFIGURATION); 

    </code>

  Remarks:
    None.
  *****************************************************************************/
void CANSetOperatingMode(CAN_MODULE module, CAN_OP_MODE opmode);

/*******************************************************************************
  Function:
    CAN_OP_MODE CANGetOperatingMode(CAN_MODULE module);

  Summary:
    This routine gets the current CAN operating mode. 

  Description:
    This routine gets the current CAN operating mode. This function is typically
    called after the CANSetOperatingMode() function to check if the requested 
    operation mode change is complete.
  
  Precondition:
    None.

  Parameters:
    module      - Identifies the desired CAN module.
    
  Returns:
    The current CAN_OP_MODE type of operation mode of the CAN module.

  Example:
    <code>
    // Check and wait until the CAN module is in Disable Mode.

    while(CANGetOperatingMode(CAN1) != CAN_DISABLE); 

    </code>

  Remarks:
    None.
  *****************************************************************************/

CAN_OP_MODE CANGetOperatingMode(CAN_MODULE module);

/*******************************************************************************
  Function:
    void CANEnableFeature(CAN_MODULE module, 
                    CAN_MODULE_FEATURES features, BOOL enable);

  Summary:
    This routine allows specified CAN module features to be enabled or disabled. 

  Description:
    This routine allows the specified CAN module features to be enabled or disabled. The
    features include CAN Bus Wake-up Line Filter, CAN RX Message Time Stamp Timer and
    the CAN Stop In CPU Idle Mode feature.  
  
  Precondition:
    The CAN module should preferrably be in Configuration Mode (using the 
    CANSetOperatingMode() function).

  Parameters:
    module      - Identifies the desired CAN module.
    
    features    - Single or OR'ed combination of features to be controlled.

    enable      - Determines if the specified features are enabled or disabled
                  * TRUE - Feature is enabled.
                  * FALSE - Feature is disabled.
    
  Returns:
    None.

  Example:
    <code>
    // Enable the CAN Stop in CPU Idle feature.

    CANEnableFeature(CAN1, CAN_STOP_IN_IDLE, TRUE);

    // Disable the CAN Bus Wake-up Bus Line Filter and the 
    // CAN RX Message Timestamp timer.

    CANEnableFeature(CAN1, (CAN_WAKEUP_BUS_FILTER|CAN_RX_TIMESTAMP), FALSE);

    </code>

  Remarks:
    None.
  *****************************************************************************/
void CANEnableFeature (CAN_MODULE module, CAN_MODULE_FEATURES features, BOOL enable);

/*******************************************************************************
  Function:
    void CANDeviceNetFilter(CAN_MODULE module, CAN_DNET_FILTER_SIZE dncnt); 

  Summary:
    This routine configures the CAN Module Device Net Filter feature. 

  Description:
    This routine configures the CAN Module Device Net Filter feature. Device Net
    Filtering allows a portion of the Data Payload to be used as a filter criteria.
    This routine allows the size of this filter to be configured in bits. The filter
    can also be disabled.  
  
  Precondition:
    The CAN module should preferably be in Configuration Mode (using the 
    CANSetOperatingMode() function).

  Parameters:
    module  - Identifies the desired CAN module.
    
    dncnt   - Specifies the CAN_DNET_FILTER_SIZE size of the Device Net
              filter in bits.

  Returns:
    None.

  Example:
    <code>
    // Disable the CAN1 Device Net Filter feature.

    CANDeviceNetFilter(CAN1, CAN_DNET_FILTER_DISABLE);

    // Set the CAN2 Device Net Filter Size to 10 bits.

    CANDeviceNetFilter(CAN1, CAN_DNET_FILTER_SIZE_10_BIT);

    </code>

  Remarks:
    None.
  *****************************************************************************/
void CANDeviceNetFilter(CAN_MODULE module, CAN_DNET_FILTER_SIZE dncnt);

/*******************************************************************************
  Function:
    void CANSetTimeStampValue(CAN_MODULE module,UINT value);

  Summary:
    This routine sets the CAN RX Message Timestamp Timer value. 

  Description:
    This routine sets the CAN RX Message Timestamp Timer value. The timer will 
    then start counting up from this value.
  
  Precondition:
    None.

  Parameters:
    module  - Identifies the desired CAN module.
    
    value   - Start value of the RX message Time stamp timer. This value
              should be between 0x0 and 0xFFFF.

  Returns:
    None.

  Example:
    <code>

    // Clear the CAN1 RX Message Timestamp Timer
    
    CANSetTimeStampValue(CAN1, 0x0);

    // Set start value of CAN1 RX Message Timestamp Timer
    // to 0x100
    
    CANSetTimeStampValue(CAN1, 0x0100);
    </code>

  Remarks:
    None.
  *****************************************************************************/
void CANSetTimeStampValue(CAN_MODULE module,	UINT value);

/*******************************************************************************
  Function:
    UINT CANGetTimeStampValue(CAN_MODULE module);

  Summary:
    This routine returns the current value of the CAN RX Message Timestamp Timer. 

  Description:
    This routine gets the current value of the CAN RX Message Timestamp Timer value.
  
  Precondition:
    None.

  Parameters:
    module  - Identifies the desired CAN module.
    
  Returns:
    The current value of the CAN RX Message Timestamp Timer.

  Example:
    <code>

    // Get the current timestamp timer value.
    
    UINT timeStampTimerVal;

    timeStampTimerVal = CANGetTimeStampValue(CAN1);

    </code>

  Remarks:
    None.
  *****************************************************************************/
UINT CANGetTimeStampValue(CAN_MODULE module);

/*******************************************************************************
  Function:
    void CANSetTimeStampPrescalar(CAN_MODULE module,UINT prescalar);

  Summary:
    This routine sets the CAN RX Message Timestamp Timer Prescalar. 

  Description:
    This routine sets the CAN RX Message Timestamp Timer Prescalar. This prescalar
    determines the rate at the which the Timestamp Timer is incremented. For example,
    if the prescalar value is 0xFF, the Timestamp Timer is incremented by 1 every
    255 system clock periods.
  
  Precondition:
    None.

  Parameters:
    module      - Identifies the desired CAN module.
    
    prescalar   - Prescalar for the CAN RX Message Timestamp Timer. This value
                  should be between 0x0 and 0xFFFF.

  Returns:
    None.

  Example:
    <code>

    // Set the CAN1 RX Message Timestamp Timer
    // prescalar to increment the Timestamp Timer
    // every 1024 system clock periods.
    
    CANSetTimeStampPrescalar(CAN1, 1024);

    </code>

  Remarks:
    None.
  *****************************************************************************/
void CANSetTimeStampPrescalar(CAN_MODULE module,	UINT prescalar);

/*******************************************************************************
  Function:
    void CANEnableModule(CAN_MODULE module, BOOL enable	);

  Summary:
    This routine enables or disables the CAN module. 

  Description:
    This routine enables or disables the CAN module. The CAN module needs to enabled
    in order to be configured and to communicate on the bus. 
  
  Precondition:
    None.

  Parameters:
    module - Identifies the desired CAN module.
    
    enable - Determines if the module is enabled or disabled.
             * TRUE - Module is enabled.
             * FALSE - Module is disabled.

  Returns:
    None.

  Example:
    <code>

    // Enable CAN1 Module
    
    CANEnableModule(CAN1, TRUE);

    // Disable CAN2 Module

    CANEnableModule(CAN2, FALSE);

    </code>

  Remarks:
    None.
  *****************************************************************************/
void CANEnableModule(CAN_MODULE module, BOOL enable	);

/*******************************************************************************
  Function:
    void CANSetSpeed(CAN_MODULE module, const CAN_BIT_CONFIG * canBitConfig,
                 UINT32 sysClock, UINT32 canBusSpeed	);

  Summary:
    This routine sets the CAN bus speed at which the module will operate. 

  Description:
    This routine sets the CAN bus speed at which the module will operate. All CAN nodes on
    the CAN bus must operate at the same speed. The CAN_BIT_CONFIG structure specifies the
    time quanta design for the CAN module. The caller must ensure that the specified 
    time quanta design, system clock frequency and desired CAN bus speed do not cause
    the CAN module to operate out of specification.

  Precondition:
    The CAN module should be in Configuration mode. This is done by calling the 
    CANSetOperatingMode() function. The canBitConfig parameter should be set up
    to reflect the desired number of time quanta per bit.

  Parameters:
    module             - Identifies the desired CAN module.
    
    canBitConfig       - Pointer to the CAN_BIT_CONFIG structure specifying the 
                         bit time quanta design for the CAN module.

    sysClock           - The device clock frequency specified in Hz.

    canBusSpeed        - The desired CAN bus speed specified in bits per second.


  Returns:
    None.

  Example:
    <code>

    // The device system clock speed is 
    // 80 MHz. Set up the CAN1 module for a 
    // bus speed of 500 Kbps. Configure the
    // CAN bit to have 10 Tq with each phase
    // specified to have 3 Tq.
    
    CAN_BIT_CONFIG canBitConfig;
    UINT baudRatePrescalar;

    canBitConfig.phaseSeg1Tq      = CAN_BIT_3TQ;
    canBitConfig.phaseSeg2Tq      = CAN_BIT_3TQ;
    canBitConfig.propagationSegTq = CAN_BIT_3TQ;
    canBitConfig.sample3Time      = TRUE;
    canBitConfig.syncJumpWidth    = CAN_BIT_2TQ;
    canBitConfig.phaseSeg2TimeSelect = TRUE;
    
    CANSetSpeed(CAN1,&canBitConfig,80000000,500000);

    </code>

  Remarks:
    None.
  *****************************************************************************/
void CANSetSpeed (CAN_MODULE module, const CAN_BIT_CONFIG * canBitConfig, 
                        UINT32 sysClock, UINT32 canBusSpeed	);

/*******************************************************************************
  Function:
    BOOL CANIsActive(CAN_MODULE module);

  Summary:
    This routine returns TRUE if the CAN module is active. 

  Description:
    This function returns TRUE if the CAN module is active. This function is   
    typically called after the CAN module is disabled using the CANEnableModule()
    function. The CAN module disable request does not complete immediately when 
    requested and depends on the CAN bus status. This function should be called to
    check if the module disable is completed.   

  Precondition:
    None.

  Parameters:
    module       - Identifies the desired CAN module.
    
  Returns:
    * TRUE - The module is still active.
    * FALSE - The module is completely disabled.

  Example:
    <code>

    // Disable CAN1 module. Wait
    // until the module is completely
    // disabled.

    CANEnableModule(CAN1, FALSE);

    while(CANIsActive(CAN1) == TRUE);

    </code>

  Remarks:
    The CAN module disable operation should not be confused with placing the 
    CAN module in the Disable mode using the CANSetOperatingMode(). The Disable
    mode is one of the operating modes of the CAN module. The CAN module is still
    enabled while in Disable mode. The module disable operation switches the CAN
    module off.
  *****************************************************************************/
BOOL CANIsActive (CAN_MODULE module);

/*******************************************************************************
  Function:
    void CANResetChannel(CAN_MODULE module, CAN_CHANNEL channel	);

  Summary:
    This routine resets a CAN channel. 

  Description:
    This routine resets a CAN channel. Resetting a CAN channel causes
    it to discard any unread received messages or any messages that have 
    not been transmitted yet. The reset operation will wait if a message
    is being currently transmitted or is being received. The CANIsChannelReset()
    function can be used to check if the channel reset is complete.  
    Attempting to read from a channel that is reset will return messages
    that may have already been read or may not have been read at all.

  Precondition:
    None.

  Parameters:
    module   - Identifies the desired CAN module.

    channel  - Identifies the CAN channel to be reset.  
    
  Returns:
    None.

  Example:
    <code>

    // Reset channel 4 of CAN1 module
    // and wait until the reset is complete

    CANResetChannel(CAN1,CAN_CHANNEL4);

    while(CANIsChannelReset(CAN1,CAN_CHANNEL4) != TRUE);

    </code>

  Remarks:
    None.

  *****************************************************************************/
void CANResetChannel(CAN_MODULE module, CAN_CHANNEL channel	);

/*******************************************************************************
  Function:
    BOOL CANIsChannelReset (CAN_MODULE module, CAN_CHANNEL channel );

  Summary:
    This routine returns TRUE if the specified channel reset is complete. 

  Description:
    This routine returns TRUE if the specified channel reset is complete. 
    This function should preferrably be called after calling the CANResetChannel()
    function.

  Precondition:
    None.

  Parameters:
    module   - Identifies the desired CAN module.

    channel  - Identifies the CAN Channel to be inspected for reset.  
    
  Returns:
    * TRUE  - Channel reset is complete.
    * FALSE - Channel reset is in progress.

  Example:
    <code>

    // Reset channel 4 of CAN1 module
    // and wait until the reset is complete

    CANResetChannel(CAN1,CAN_CHANNEL4);

    while(CANIsChannelReset(CAN1,CAN_CHANNEL4) != TRUE);

    </code>

  Remarks:
    None.

  *****************************************************************************/
BOOL CANIsChannelReset (CAN_MODULE module, CAN_CHANNEL channel );


/*******************************************************************************
  Function:
    void CANUpdateChannel(CAN_MODULE module, CAN_CHANNEL channel);

  Summary:
    This function updates the CAN Channel internal pointers.

  Description:
    This function updates the CAN Channel internal pointers. This function
    should be called when a message has been read or processed completely from
    a CAN RX Channel (using the CANGetRxMessage() function). It should be called
    after a new message has been written to a CAN TX Channel (using the
    CANGetTxMessageBuffer() function) and before the CANFlushTxChannel()
    function.
    
    Trying to read a CAN RX channel that has not been updated will cause the
    CANGetRxMessage() function to return the same message. Writing to a CAN
    TX Channel that has not been updated will cause the last written message to be
    overwritten.  

  Precondition:
    This function is effective only when the CAN module is not in Configuration
    mode or Disable mode.

  Parameters:
    module   - Identifies the desired CAN module.

    channel  - Identifies the CAN channel to be updated.  
    
  Returns:
    None.

  Example:
    <code>

    // CAN1 Channel 1 is a RX channel
    // and Channel 2 is a TX channel.
    // Read and update Channel 1. Write
    // a message to Channel 2 and then
    // update and flush the channel.
   
    CANTxMessageBuffer * txMessage;
    CANRxMessageBuffer * rxMessage;

    rxMessage = CANGetRxMessage(CAN1, CAN_CHANNEL1); 

    if(rxMessage != NULL)
    {
        // Process the received message.
        
        ProcessRxMessage(rxMessage);
        CANUpdateChannel(CAN1, CAN_CHANNEL1);
    }

    txMessage = CANGetTxMessageBuffer(CAN1, CAN_CHANNEL2);
    if(txMessage != NULL)
    {
        // Write a message to buffer

        WriteMessage(txMessage);
        CANUpdateChannel(CAN1, CAN_CHANNEL2);
        CANFlushTxChannel(CAN1, CAN_CHANNEL2);
    }

    </code>

  Remarks:
    The CANUpdateChannel() function should be called on a CAN RX Channel
    only after the message obtained using the CANGetRxMessage() function
    has been read or processed completely. The CAN module peripheral 
    library does not provide access to older messages once the CANUpdateChannel()
    function has been called. 

    When using the CANGetTxMessageBuffer() function to write to a CAN TX Channel
    the CANUpdateChannel() function should be called only when a valid message
    has been written to the channel. Calling the update function without 
    writing to the CAN channel will cause an incorrect message to be output on the
    CAN channel when the TX channel is flushed.

  *****************************************************************************/
void CANUpdateChannel(CAN_MODULE module, CAN_CHANNEL channel);

// *****************************************************************************
// *****************************************************************************
// Section: Event Management functions.
// *****************************************************************************
// *****************************************************************************


/*******************************************************************************
  Function:
    void CANEnableModuleEvent (CAN_MODULE module, CAN_MODULE_EVENT flags, BOOL enable);

  Summary:
    This routine enables or disables module level events. 

  Description:
    This routine enables or disables module level events. Any enabled module event
    will cause the CAN module to generate a CPU interrupt. An event can be active
    regardless of it being enabled or disabled.   

  Precondition:
    None.

  Parameters:
    module - Identifies the desired CAN module.

    flags  - Identifies the CAN module level events to be affected. Several events
             can be controlled by logically OR'ed combination of events.

    enable - Enables or disables the specified event.  
             * TRUE  - Module event is enabled.
             * FALSE - Module event is disabled.
    
  Returns:
    None.

  Example:
    <code>

    // Enable CAN1 TX Event and RX Events.
    // Disable RX Overflow event and operation
    // mode change event. 

    CANEnableModuleEvent(CAN1, (CAN_TX_EVENT | CAN_RX_EVENT), TRUE);
    CANEnableModuleEvent(CAN1, (CAN_OPERATION_MODE_CHANGE_EVENT | CAN_RX_OVERFLOW_EVENT), FALSE);
    
    </code>

  Remarks:
    None.

  *****************************************************************************/
void CANEnableModuleEvent(CAN_MODULE module, CAN_MODULE_EVENT flags, BOOL enable);

/*******************************************************************************
  Function:
    void CANClearModuleEvent (CAN_MODULE module, CAN_MODULE_EVENT flags);

  Summary:
    This routine clears the CAN module level events. 

  Description:
    This routine clears module level events. If the event condition is persistent, 
    clearing the event will have no effect. The event condition itself should be
    cleared. The CAN_SYSTEM_ERROR_EVENT can only be cleared by disabling the CAN module 
    using the CANEnableModule() function. 

  Precondition:
    None.

  Parameters:
    module - Identifies the desired CAN module.

    flags  - Identifies the CAN module level events to be affected. Several events
             can be cleared by specifying a logically OR'ed combination of events.
    
  Returns:
    None.

  Example:
    <code>

    // Clear CAN1 TX Event and RX Events.

    CANClearModuleEvent(CAN1, (CAN_TX_EVENT | CAN_RX_EVENT));
    
    </code>

  Remarks:
    None.

  *****************************************************************************/
void CANClearModuleEvent (CAN_MODULE module, CAN_MODULE_EVENT flags);

/*******************************************************************************
  Function:
    void CANEnableChannelEvent(CAN_MODULE module, CAN_CHANNEL channel,
                        CAN_CHANNEL_EVENT flags, BOOL enable);

  Summary:
    This routine enables or disables channel level events. 

  Description:
    This routine enables or disables channel level events. Any enabled channel event
    will cause a CAN module event. An event can be active regardless of it being 
    enabled or disabled. Enabling a TX type of event for a RX channel will have no
    any effect.   

  Precondition:
    None.

  Parameters:
    module - Identifies the desired CAN module.

    channel - Identifies the desired CAN Channel.

    flags  - Identifies the CAN channel event(s) to be affected. Several events
             can be controlled by logically OR'ed combination of events.

    enable - Enables or disables the specified event.  
             * TRUE  - Channel event is enabled.
             * FALSE - Channel event is disabled.
    
  Returns:
    None.

  Example:
    <code>

    // CAN1 Channel 1 and 3 are TX channels and 
    // Channel 2  and 4 are RX channels. Enable
    // Channel 1 empty event and channel
    // not full event. Disable Channel 2 full
    // and overflow event.  Enable all TX events
    // on Channel 2 and disable all RX events on
    // on Channel 4.  

    CANEnableChannelEvent(CAN1, CAN_CHANNEL1, (CAN_TX_CHANNEL_EMPTY | CAN_TX_CHANNEL_NOT_FULL), TRUE);
    CANEnableChannelEvent(CAN1, CAN_CHANNEL2, (CAN_RX_CHANNEL_FULL | CAN_RX_CHANNEL_OVERFLOW), FALSE);
    CANEnableChannelEvent(CAN1, CAN_CHANNEL3, CAN_TX_CHANNEL_ANY_EVENT, TRUE);
    CANEnableChannelEvent(CAN1, CAN_CHANNEL4, CAN_RX_CHANNEL_ANY_EVENT, FALSE);

    </code>

  Remarks:
    None.

  *****************************************************************************/
void CANEnableChannelEvent(CAN_MODULE module, CAN_CHANNEL channel,CAN_CHANNEL_EVENT flags, BOOL enable);

/*******************************************************************************
  Function:
    CAN_MODULE_EVENT CANGetModuleEvent(CAN_MODULE module);

  Summary:
    This routine returns the status of the CAN module events.

  Description:
    This routine returns the status of the CAN module events. The routine
    returns a status word. This word should be logically AND'ed with the
    desired CAN_MODULE_EVENT event mask. A non-zero result of such
    an operation would mean that the events specified in the event mask 
    are active. An event mask can contain one event or can be a logical OR
    combination of multiple events.

  Precondition:
    None.

  Parameters:
    module - Identifies the desired CAN module.
    
  Returns:
    A status word representing the status of the CAN module events. 

  Example:
    <code>

    // Check if the CAN1 Module RX event
    // or if TX event is active

    if((CANGetModuleEvent(CAN1) & (CAN_RX_EVENT | CAN_TX_EVENT)) != 0)
    {
        // Handle the RX or TX module Event
        // here.
       
    }

    // Check if the CAN2 System Error Event
    // is active

    if((CANGetModuleEvent(CAN2) & CAN_SYSTEM_ERROR_EVENT) != 0)
    {
        // CAN2 System error event is active.

    }
   
    </code>

  Remarks:
    None.

  *****************************************************************************/
CAN_MODULE_EVENT CANGetModuleEvent (CAN_MODULE module);

/*******************************************************************************
  Function:
    CAN_EVENT_CODE CANGetPendingEventCode(CAN_MODULE module);

  Summary:
    This routine returns a value representing the highest priority active event
    in the module.

  Description:
    This routine returns a value representing the highest priority active event
    in the module. The return value is a CAN_EVENT_CODE type.

  Precondition:
    None.

  Parameters:
    module - Identifies the desired CAN module.
    
  Returns:
    Returns a CAN_EVENT_CODE type representing the highest priority active event
    in the module.

  Example:
    <code>

    // Implement a switch to check and process
    // any active CAN module events.

    CAN_EVENT_CODE eventCode;
    
    eventCode = CANGetPendingEventCode(CAN1);

    switch(eventCode)
    {
        case CAN_NO_EVENT:
            
            // Procedure to handle no CAN events
            break;
        
        case CAN_WAKEUP_EVENT:
        
            // Procedure to handle device wake-up
            // on CAN bus activity event
            break;

        default:
            
            break
     }
    </code>

  Remarks:
    None.

  *****************************************************************************/
CAN_EVENT_CODE CANGetPendingEventCode (CAN_MODULE module);

/*******************************************************************************
  Function:
    CAN_CHANNEL_MASK CANGetAllChannelEventStatus(CAN_MODULE module);

  Summary:
    This routine returns a value representing the  event status of all the CAN 
    Channels. 

  Description:
    This routine returns a value representing the  event status of all the CAN 
    Channels. The return value can be logically AND'ed with a CAN_CHANNEL_MASK type
    to check if the channel has any active events. Only an enabled channel event
    will cause the bit to be updated.  

  Precondition:
    None.

  Parameters:
    module - Identifies the desired CAN module.
    
  Returns:
    Returns a value that can be logically AND'ed with a CAN_CHANNEL_MASK mask value
    to check if any event on a channel is active.

  Example:
    <code>

    // Check if Channel 2 or 3 of CAN1 module
    // have any active events

    CAN_CHANNEL_MASK channelEvents;

    channelEvents = CANGetAllChannelEventStatus(CAN1)

    if((channelEvents & (CAN_CHANNEL2_MASK | CAN_CHANNEL3_MASK)) != 0)
    {
        // Either Channel 2 or 3 has an active event.
        // The CANGetChannelEvent() function can be 
        // used to query the channel for more details.
    }

    // Check if Channel 31 of CAN2 module
    // has an any active events

    channelEvents = CANGetAllChannelEventStatus(CAN2);

    if((channelEvents & CAN_CHANNEL31_MASK) != 0)
    {
        // Channel 31 of CAN2 module
        // has an active event.
    }

    </code>

  Remarks:
    None.

  *****************************************************************************/
CAN_CHANNEL_MASK CANGetAllChannelEventStatus (CAN_MODULE module);

/*******************************************************************************
  Function:
    CAN_CHANNEL_MASK	CANGetAllChannelOverflowStatus	(CAN_MODULE module);

  Summary:
    This routine returns a value representing the RX overflow event status of 
    all the CAN Channels. 

  Description:
    This routine returns a value representing the RX overflow event status of all
    the CAN Channels. The return value can be logically AND'ed with a CAN_CHANNEL_MASK
    type to check if a channel has any active RX overflow events. The return value 
    will reflect the channel status only if the RX overflow event of the channel is
    enabled.

  Precondition:
    None.

  Parameters:
    module - Identifies the desired CAN module.
    
  Returns:
    Returns a value that can be logically AND'ed with a CAN_CHANNEL_MASK mask value
    to check if a RX channel overflow event is active.

  Example:
    <code>

    // Check if RX Channel 2 or 3 of CAN1 module
    // have overflowed

    CAN_CHANNEL_MASK channelOverflowEvent;

    channelOverflowEvent = CANGetAllChannelOverflowStatus(CAN1)

    if((channelOverflowEvent & (CAN_CHANNEL2_MASK | CAN_CHANNEL3_MASK)) != 0)
    {
        // Either RX Channel 2 or 3 has  overflowed.
        // The CANGetChannelEvent() function can be 
        // used to query the channel for more details.
    }

    // Check if RX Channel 31 of CAN2 module
    // has overflowed

    channelOverflowEvent = CANGetAllChannelOverflowStatus(CAN2);

    if((channelOverflowEvent & CAN_CHANNEL31_MASK) != 0)
    {
        // Channel 31 of CAN2 module
        // has overflowed.
    }

    </code>

  Remarks:
    None.

  *****************************************************************************/
CAN_CHANNEL_MASK CANGetAllChannelOverflowStatus	(CAN_MODULE module);

/*******************************************************************************
  Function:
    CAN_CHANNEL_EVENT CANGetChannelEvent (CAN_MODULE module, CAN_CHANNEL channel);

  Summary:
    This routine returns a value representing the event status of a CAN Channel. 

  Description:
    This routine returns a value representing the event status of a CAN Channel. 
    The return value can be logically AND'ed with CAN_CHANNEL_EVENT type to check
    for a specific event(s). Channels events are affected regardless of whether the
    event itself is enabled or disabled. 

  Precondition:
    None.

  Parameters:
    module  - Identifies the desired CAN module.

    channel - Identifies the desired CAN Channel. 
    
  Returns:
    Returns a value that can be logically AND'ed with a CAN_CHANNEL_EVENT type to check
    if specific CAN Channel events are active.

  Example:
    <code>

    // Check if RX Channel 2 of CAN1 module
    // is not empty or if its full.

    CAN_CHANNEL_EVENT channelEvent;

    channelEvent = CANGetChannelEvent(CAN1,CAN_CHANNEL2);

    if((channelEvent & (CAN_RX_CHANNEL_NOT_EMPTY | CAN_RX_CHANNEL_FULL)) != 0)
    {
        // This means that either RX Channel 2 is not empty
        // or the Channel is full.

        
    }

    // Check if TX Channel 3 of CAN2 module
    // has any active events

    channelEvent = CANGetChannelEvent(CAN2, CAN_CHANNEL3);

    if((channelEvent & CAN_TX_CHANNEL_ANY_EVENT) != 0)
    {
        // This means that some event is active

    }

    // Check if TX Channel 6 of CAN2 module is not full
    
    channelEvent = CANGetChannelEvent(CAN2, CAN_CHANNEL6);

    if((channelEvent & CAN_TX_CHANNEL_NOT_FULL) != 0)
    {
        // This means the Channel is not full.

    }

    </code>

   
  Remarks:
    None.

  *****************************************************************************/
CAN_CHANNEL_EVENT CANGetChannelEvent (CAN_MODULE module, CAN_CHANNEL channel);

/*******************************************************************************
  Function:
    void CANClearChannelEvent(CAN_MODULE module, CAN_CHANNEL channel, CAN_CHANNEL_EVENT events);

  Summary:
    This routine clears the CAN channel event(s). 

  Description:
    This routine clears channel event(s). The event(s) to be cleared are specified
    as mask. Note that only the RX Overflow event is clearable. Attempting to 
    clear other events will have no effect since these events are persistent
    and clear only when the event condition is cleared.  

  Precondition:
    None.

  Parameters:
    module  - Identifies the desired CAN module.

    channel - Identifies the desired CAN Channel. 

    events  - Mask specifying the events to be cleared.
    
  Returns:
    None.

  Example:
    <code>

    // Clear CAN2 RX Channel 3 overflow event

    CANClearChannelEvent(CAN2, CAN_CHANNEL3, CAN_RX_CHANNEL_OVERFLOW);

    </code> 
   
  Remarks:
    None.

  *****************************************************************************/
void CANClearChannelEvent(CAN_MODULE module, CAN_CHANNEL channel, CAN_CHANNEL_EVENT events);

// *****************************************************************************
// *****************************************************************************
// Section: CAN Message Transmit functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void CANConfigureChannelForTx(CAN_MODULE module,CAN_CHANNEL channel
								, UINT channelSize, CAN_TX_RTR rtren,
								CAN_TXCHANNEL_PRIORITY priority);

  Summary:
    This routine configures a CAN Channel for transmission.

  Description:
    This routine configures a CAN Channel for transmission. The size of
    the channel specifies the number of messages that the channel can 
    buffer. The channel is a First In First Out (FIFO) type of buffer. The 
    Remote Transmit Request feature allows the transmit channel to start
    transmitting when an associated filter has received a message. The TX channel
    priority determines the priority as compared to other TX channels. If 
    two TX channels have the same priority, the natural channel priority
    determines which channel transmits first.

  Precondition:
    The CAN Module should be in Configuration mode. This is achieved by using the
    CANSetOperatingMode() function.

  Parameters:
    module       - Identifies the desired CAN module.

    channel      - Identifies the desired CAN Channel. 

    channelSize  - Size of the channel in messages. This value should be
                   between 1 and 32.

    rtren        - Enables disables Remote Transmit Request:
                   * CAN_TX_RTR_ENABLED - Remote Transmit Request is enabled.
                   * CAN_TX_RTR_DISABLED - Remote Transmit Request is disabled.

    priority     - Specifies the priority of the TX channel.
  
  Returns:
    None.

  Example:
    <code>

    // Configure CAN 1 Channel 2 for TX operation. Set the channel size to 15
    // and enable remote transmit request. Set the priority to low medium
    // priority.

    CANConfigureChannelForTx(CAN1, CAN_CHANNEL2, 15, CAN_TX_RTR_ENABLED, CAN_LOW_MEDIUM_PRIORITY);

    </code> 
   
  Remarks:
    None.

  *****************************************************************************/
void CANConfigureChannelForTx(CAN_MODULE module,CAN_CHANNEL channel, UINT channelSize,
                             CAN_TX_RTR rtren, CAN_TXCHANNEL_PRIORITY priority);

/*******************************************************************************
  Function:
    void CANAbortPendingTx(CAN_MODULE module, CAN_CHANNEL channel );

  Summary:
    This routine aborts any pending TX operations.

  Description:
    This routine aborts any pending TX operations. Any messages that are yet
    to be transmitted will  not be transmitted. The messages will still be 
    present in the respective channel. Any message that is in the process of
    being transmitted will be transmitted completely. Either one channel or 
    all channels can be specified.  

  Precondition:
    None.

  Parameters:
    module       - Identifies the desired CAN module.

    channel      - Identifies the desired CAN Channel. By specifying 
                   CAN_ALL_CHANNELS, transmission on all TX channels will be
                   aborted. 

  Returns:
    None.

  Example:
    <code>
    
    // Abort any pending transmissions on CAN1 Channel 4 and
    // Channel 5.

    CANAbortPendingTx(CAN1, CAN_CHANNEL4);
    CANAbortPendingTx(CAN1, CAN_CHANNEL5);

    // Abort pending transmission on all CAN1 TX channels
    
    CANAbortPendingTx(CAN1, CAN_ALL_CHANNELS);

    </code> 
   
  Remarks:
    None.

  *****************************************************************************/
void CANAbortPendingTx(CAN_MODULE module, CAN_CHANNEL channel );

/*******************************************************************************
  Function:
    void CANFlushTxChannel(CAN_MODULE module, CAN_CHANNEL channel);

  Summary:
    This routine causes all messages in the specified TX channel to be transmitted.

  Description:
    This routine causes all messages in the specified TX channel to be transmitted.
    All messages in the channel at the time of the flush operation will be transmitted.
    The TX channel flush operation should preferrably be called immediately after
    the CANUpdateChannel() function. This will ensure that messages are transmitted
    promptly.

  Precondition:
    None.

  Parameters:
    module       - Identifies the desired CAN module.

    channel      - Identifies the desired CAN Channel.  

  Returns:
    None.

  Example:
    <code>
    
    // Flush CAN1 TX Channel 4.

    CANFlushTxChannel(CAN1, CAN_CHANNEL4);

    </code> 
   
  Remarks:
    None.

  *****************************************************************************/
void CANFlushTxChannel(CAN_MODULE module, CAN_CHANNEL channel);

/*******************************************************************************
  Function:
    CAN_TX_CHANNEL_CONDITION CANGetTxChannelCondition(CAN_MODULE module, CAN_CHANNEL channel);

  Summary:
    This routine returns the condition of the TX channel.

  Description:
    This routine returns the condition of the TX channel. The return value can
    be logically AND'ed with CAN_TX_CHANNEL_CONDITION type values.

  Precondition:
    None.

  Parameters:
    module       - Identifies the desired CAN module.

    channel      - Identifies the desired CAN Channel.  

  Returns:
    Returns a status word that can be logically AND'ed with the 
    CAN_TX_CHANNEL_CONDITION type to check if a condition exits.

  Example:
    <code>
    
    // Check if CAN1 TX Channel 4 
    // is still transmitting 

    CAN_TX_CHANNEL_CONDITION status;

    status = CANGetTxChannelCondition(CAN1, CAN_CHANNEL4);

    if((status & CAN_TX_CHANNEL_TRANSMITTING) != 0)
    {
        // This means that channel is still 
        // trasnmitting.

    }

    // Check if CAN2 TX Channel 5 has lost arbitration
    // or other TX errors.

    status = CANGetTxChannelCondition(CAN2, CAN_CHANNEL5);

    if((status & (CAN_TX_CHANNEL_ARBITRATION_LOST | CAN_TX_CHANNEL_ERROR)) != 0)
    {
        // This means that the TX channel has either
        // lost arbitration or a TX error has occurred.
    }
     

    </code> 
   
  Remarks:
    None.

  *****************************************************************************/
CAN_TX_CHANNEL_CONDITION CANGetTxChannelCondition(CAN_MODULE module, CAN_CHANNEL channel);

/*******************************************************************************
  Function:
    CANTxMessageBuffer * CANGetTxMessageBuffer(CAN_MODULE module, CAN_CHANNEL channel);

  Summary:
    This routine returns a pointer to an empty TX buffer.

  Description:
    This routine returns a pointer to an empty TX buffer. The routine will return a 
    null pointer if there aren't any empty TX buffers. In such a case, the application
    should flush the channel and wait until the TX channel has at least one empty 
    buffer. In order to function correctly, it is essential that the CANUpdateChannel()
    function is called in the proper sequence for the CANGetTxMessageBuffer() function to 
    return a pointer to an empty buffer. 

  Precondition:
    None.

  Parameters:
    module       - Identifies the desired CAN module.

    channel      - Identifies the desired CAN Channel.  

  Returns:
    Returns a CANTxMessageBuffer type pointer to an empty message buffer in the TX
    channel. Returns NULL if the channel is full and there aren't any empty message
    buffers. 

  Example:
    <code>
    
    // Transmit a message through
    // CAN1 Channel 4

    CANTxMessageBuffer * msgBuffer;

    msgBuffer = CANGetTxMessageBuffer(CAN1, CAN_CHANNEL4);

    if(msgBuffer != NULL)
    {
        // Load the message here 
        
    }
    else
    {
        // No space in the channel
        // wait until a message
        // buffer is free.

        while((CANGetChannelEvent(CAN1, CAN_CHANNEL4) & CAN_TX_CHANNEL_NOT_FULL) == 0);
    }

    </code> 
   
  Remarks:
    Calling the CANGetTxMessageBuffer() function on a channel that has not been 
    updated after a message was written to the channel, will cause the function
    to return a pointer to the written message. Therefore, a non-transmitted message
    could get overwritten.
    

  *****************************************************************************/
CANTxMessageBuffer * CANGetTxMessageBuffer(CAN_MODULE module, CAN_CHANNEL channel);

/*******************************************************************************
  Function:
    BOOL CANIsTxAborted(CAN_MODULE module, CAN_CHANNEL channel);

  Summary:
    This routine returns TRUE if TX abort operation is complete.

  Description:
    This routine returns TRUE if the TX abort operation is complete. Either 
    individual channels can be specified or all channels can be specified.

  Precondition:
    None.

  Parameters:
    module       - Identifies the desired CAN module.

    channel      - Identifies the desired CAN Channel. By specifying CAN_ALL_CHANNELS
                   the status of TX abort on all TX channels will be returned. 

  Returns:
    The status of TX abort operation:
    * TRUE  - If channel = CAN_ALL_CHANNELS, means TX Abort is complete.
              If channel = CAN_CHANNELx, means TX Abort was successful. 
    * FALSE - If channel = CAN_ALL_CHANNELS, means TX Abort is in progress.
              If channel = CAN_CHANNELx, means TX Abort was not successful. 

  Example:
    <code>
    
    // Abort any pending transmissions on CAN1 Channel 4 and
    // check if the current message transmission was aborted. 

    CANAbortPendingTx(CAN1, CAN_CHANNEL4);
    if(CANIsTxAborted(CAN1, CAN_CHANNEL4) == FALSE)
    {
        // The message was not aborted.
    }
    else
    {
        // The message was aborted.
    }

    // Abort any pending transmissions on all CAN2 TX channel and
    // wait until the abort operation is complete. 

    CANAbortPendingTx(CAN1, CAN_ALL_CHANNELS);
    while(CANIsTxAborted(CAN1, CAN_ALL_CHANNELS) == FALSE);

    </code> 
   
  Remarks:
    None.

  *****************************************************************************/
BOOL CANIsTxAborted(CAN_MODULE module, CAN_CHANNEL channel);

// *****************************************************************************
// *****************************************************************************
// Section: CAN Message Receive functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    CANRxMessageBuffer * CANGetRxMessage(CAN_MODULE module, CAN_CHANNEL channel);

  Summary:
    This routine returns a pointer to a message to be read from the CAN channel.

  Description:
    This routine returns a CANRxMessageBuffer pointer to a message to be read from
    the CAN channel. The routine will return NULL if there are no new messages to 
    be read. The CANUpdateChannel() routine should be called after the received message
    has been processed.  

  Precondition:
    None.

  Parameters:
    module       - Identifies the desired CAN module.

    channel      - Identifies the desired CAN RX channel. 

  Returns:
    Returns NULL if there are no messages in the channel; otherwise returns a
    CANRxMessageBuffer type pointer to a received CAN message. If the receive channel
    is a full CAN message receive channel, the caller should use the msgSID, msgEID
    and data members of the CANRxMessageBuffer data structure to access the received
    CAN message. If the receive channel is a data-only channel, themessage will only 
    contain 8 payload data bytes (even if the message was placed on the bus with less
    than 8 bytes). The caller in this case should use the dataOnlyMsgData member of 
    the CANRxMessageBuffer data structure to read the data contained in the received 
    CAN message. 

  Example:
    <code>
    
    // Read a message from the CAN1 Channel 8
    // which is configured as full CAN message
    // receive channel.

    CANRxMessageBuffer * rxMsg;

    rxMsg = (CANRxMessageBuffer *)CANGetRxMessage(CAN1, CAN_CHANNEL8);

    if(rxMsg != NULL)
    {
        // rxMsg is pointing to 
        // a CAN message. Process
        // the message and then update
        // the CAN channel.

        SomeFunction(rxMsg);

        CANUpdateChannel(CAN1, CAN_CHANNEL8);
    }
 
    // Read a message from the CAN2 Channel 9
    // which is configured as data only message
    // receive channel. Access the message
    // as bytes;

    CANRxMessageBuffer * rxMsg;

    rxMsg = CANGetRxMessage(CAN2, CAN_CHANNEL9);

    if(rxMsg != NULL)
    {
        // rxMsg is pointing to 
        // a CAN message. Process
        // the message and then update
        // the CAN channel.

        // rxMsg->dataOnlyMsgData[0] is the first byte of message
        // data payload. rxMsg->dataOnlyMsgData[0] is the second 
        // byte of message data payload and so on.


        CANUpdateChannel(CAN2, CAN_CHANNEL9);
    }
    </code>
   
  Remarks:
    The CAN Receive channel is configured as a full CAN message receive channel 
    or a data-Only channel while configuring the channel using the 
    CANConfigureChannelForRx() function.

  *****************************************************************************/
CANRxMessageBuffer * CANGetRxMessage(CAN_MODULE module, CAN_CHANNEL channel);

/*******************************************************************************
  Function:
    void CANConfigureChannelForRx(CAN_MODULE module, CAN_CHANNEL channel, 
                        UINT32 channelSize, CAN_RX_DATA_MODE dataOnly);

  Summary:
    This routine configures a CAN channel for Receive operation.

  Description:
    This routine configures a CAN channel for receive operation. A receive channel
    can be either a full CAN message receive channel, which receives an entire CAN
    message (Arbitration field + Data field) or a data only message channel, which 
    receives only the data payload section of the message. A receive channel can 
    buffer upto 32 messages. The number of messages to buffer (i.e. the size of the
    channel) is set by the channelSize parameter. 

  Precondition:
    The CAN module should be in Configuration mode. This is achieved by using the
    CANSetOperatingMode() function.

  Parameters:
    module       - Identifies the desired CAN module.

    channel      - Identifies the desired CAN RX channel. 
    
    channelSize  - Specifies the number of received messages that the channel
                   can buffer before it overflows. This should be a value between
                   1 and 32. 

    dataOnly     - Specifies a full CAN message Receive channel or a data-only message 
                   channel.
                   * CAN_RX_DATA_ONLY - Channel will be a data-only message receive channel.
                   * CAN_RX_FULL_RECEIVE - Channel will be a full CAN message receive channel. 


  Returns:
    None.

  Example:
    <code>

    // Configure channel 4 of CAN1 for receive 
    // operation. Set channel size to buffer 10
    // messages. Channel should be data only
    // receive channel

    CANConfigureChannelForRx(CAN1, CAN_CHANNEL4, 10, CAN_RX_DATA_ONLY);

    // Configure channel 8 of CAN2 for receive 
    // operation. Set channel size to buffer 23
    // messages. Channel should be a full CAN message
    // receive channel

    CANConfigureChannelForRx(CAN2, CAN_CHANNEL8, 23, CAN_RX_FULL_RECEIVE);
    </code>
   
  Remarks:
    None.

  *****************************************************************************/
void CANConfigureChannelForRx(CAN_MODULE module, CAN_CHANNEL channel, UINT32 channelSize,
        CAN_RX_DATA_MODE dataOnly);
  
// *****************************************************************************
// *****************************************************************************
// Section: CAN Message Filtering functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void CANConfigureFilterMask(CAN_MODULE module, CAN_FILTER_MASK mask, UINT32 maskbits,
                                CAN_ID_TYPE idType, CAN_FILTER_MASK_TYPE mide);

  Summary:
    This routine configures a CAN Filter Mask.

  Description:
    This routine configures a CAN Filter Mask. The mask bits determine which 
    message ID bits are ignored and compared during the filtering process. 
    
  Precondition:
    CAN Module should be in Configuration mode. This is achieved by using the
    CANSetOperatingMode() function.

  Parameters:
    module   - Identifies the desired CAN module.

    mask     - Identifies the desired CAN RX Filter Mask. 
    
    maskbits - A value in the range 0x0 to 0x7FF for SID range  or 0x0 to 
               0x1FFFFFFF for the EID range. Each set bit will mean that 
               the corresponding bit in the filter will be compared to the 
               corresponding bit in the message ID. A clear mask bit means
               the corresponding bit in the incoming message ID field will 
               be ignored.
    
    idType   - Specifies the value range of maskbits parameter. 
               * CAN_EID - Value range of maskbits parameter is 0x0 (ignore all 29 bits of 
                 the incoming message ID) to 0x1FFFFFFF (compare all 29 bits of the incoming
                 message ID).
               * CAN_SID - Value range of maskbits parameter is 0x0 (ignore all 11 bits of 
                 the incoming message ID) to 0x7FF (compare all 11 bits of the incoming
                 message ID).
    
    mide     - Specifies ID masking options
               * CAN_FILTER_MASK_IDE_TYPE - Masking will be performed
                 by Filter Type only. If the filter is set up for SID messages,
                 the mask will decline all incoming EID messages. If the filter is set
                 up for EID messages, the mask will decline all incoming
                 SID messages  
               * CAN_FILTER_MASK_ANY_TYPE - Masking will be performed
                 regardless of the incoming message ID type. The message will
                 be accepted on a Filter and Message SID match or a Filter
                 and Message SID/EID match.


  Returns:
    None.

  Example:
    <code>

    // Configure CAN1 Filter Mask 2 to accept
    // extended ID messages in the range 0x4F1DE8 - 0x4F1DEC.
    // On analyzing this address range it can be seen that only
    // the last two bits of the incoming CAN message should ignored.
    // Therefore the mask value should 0x1FFFFFFC.
    // This mask will be used with a extended ID filter.
    // Set the masking option to filter IDE type.

    CANConfigureFilterMask(CAN1, CAN_FILTER_MASK2, 0x1FFFFFFC, 
                                CAN_EID, CAN_FILTER_MASK_IDE_TYPE);

    </code>
   
  Remarks:
    A mask bit value of zero essentially means that all messages with any ID
    are accepted. The mide and idType input parameters are still relevant in such a case.

  *****************************************************************************/
void CANConfigureFilterMask(CAN_MODULE module, CAN_FILTER_MASK mask, UINT32 maskbits,
                                CAN_ID_TYPE idType, CAN_FILTER_MASK_TYPE mide);

/*******************************************************************************
  Function:
    void CANConfigureFilter(CAN_MODULE module, CAN_FILTER filter, 
                                        UINT32 id, CAN_ID_TYPE filterType);

  Summary:
    This routine configures a CAN Message Acceptance Filter.

  Description:
    This routine configures a CAN Message Acceptance  Filter. The ID field
    of the incoming message must match the filter bits in order for the CAN
    module to accept the message. A filter can be a EID type filter, which filters
    EID messages or a SID filter, which filters SID messages. The filter mask
    bits (configured using the CANConfigureFilterMask() function) addtionally
    allow specified message ID bits to be ignored in the filtering process. 
    
  Precondition:
    None.

  Parameters:
    module   - Identifies the desired CAN module.

    filter   - Identifies the desired CAN RX Filter. 
    
    id       - A value in the range 0x0 to 0x7FF for SID filter type or
               0x0 to 0x1FFFFFFF for EID filter type. 
    
    filterType - Specfies the type of filter
                 * CAN_EID - Filter is an extended ID message filter.    
                 * CAN_SID - Filter is an standard ID message filter.    

  Returns:
    None.

  Example:
    <code>
    
    // Configure CAN2 filter 4 to accept standard ID messages
    // with SID 0x100

    CANConfigureFilter(CAN2, CAN_FILTER4, 0x100, CAN_SID);
    
    // Configure CAN1 filter 3 to accept extended ID messages
    // with EID 0x1D400

    CANConfigureFilter(CAN1, CAN_FILTER3, 0x1D400, CAN_EID);

    </code>
   
  Remarks:
    A CAN Message Acceptance Filter can be configured in Normal 
    operation mode. The filter must be disabled before this is done.

  *****************************************************************************/
void CANConfigureFilter(CAN_MODULE module, CAN_FILTER filter, UINT32 id, CAN_ID_TYPE filterType);

/*******************************************************************************
  Function:
    void CANEnableFilter(CAN_MODULE module, CAN_FILTER filter, BOOL enable); 

  Summary:
    This routine enables or disables a CAN Message Acceptance Filter.

  Description:
    This routine enables or disables a CAN Message Acceptance Filter. At least
    one filter must be enabled in order for the CAN module to receive messages.
    A receive channel associated with a filter will not receive messages unless 
    the filter is enabled. After a filter is disabled, the CANIsFilterDisabled()
    function should be called to check if the filter is disabled. A filter
    should be disabled if it is to be configured. 
    
  Precondition:
    None.

  Parameters:
    module   - Identifies the desired CAN module.

    filter   - Identifies the desired CAN Message Acceptance Filter. 
    
    enable   - Enables or disables the filter.
               * TRUE - Enables the filter.
               * FALSE - Disables the filter.

  Returns:
    None.

  Example:
    <code>
    
    // Enable filter 6 of CAN2

    CANEnableFilter (CAN2, CAN_FILTER6, TRUE);

    // Disable filter 4 of CAN1 and wait
    // until it is disabled

    CANEnableFilter (CAN1, CAN_FILTER4, FALSE);
    while(CANIsFilterDisabled(CAN1, CAN_FILTER4) != TRUE);

    </code>
   
  Remarks:
    None.

  *****************************************************************************/
void CANEnableFilter(CAN_MODULE module, CAN_FILTER filter, BOOL enable); 

/*******************************************************************************
  Function:
    CAN_FILTER	CANGetLatestFilterHit(CAN_MODULE module);

  Summary:
    This routine returns the index of the filter that accepted the latest
    message.

  Description:
    This routine returns the index of the filter that accepted the latest
    message.     
    
  Precondition:
    None.

  Parameters:
    module   - Identifies the desired CAN module.

  Returns:
    Index of the filter that accepted the latest message.

  Example:
    <code>

    // Check if CAN2 module Receive Buffer event
    // is active and if so check which filter 
    // accepted the message. 
    
    CAN_FILTER filter;

    if((CANGetModuleEvent(CAN2) & CAN_RX_EVENT) != 0)
    {
        // Check which filter accepted the message

        filter = CANGetLatestFilterHit(CAN2);
    }

    </code>
   
  Remarks:
    None.

  *****************************************************************************/
CAN_FILTER CANGetLatestFilterHit(CAN_MODULE module);

/*******************************************************************************
  Function:
    void CANLinkFilterToChannel(CAN_MODULE module, CAN_FILTER filter, 
                    CAN_FILTER_MASK mask, CAN_CHANNEL channel);

  Summary:
    This routine links a filter to a channel.

  Description:
    This routine links a filter to a channel. A filter is typically linked to
    a RX channel. This allows the channel to receive messages accepted by
    the filter. A filter can also be linked to a TX channel if the TX channel
    is configured for Remote Request Transmit. In this case, a message accepted
    by the filter will automatically cause the linked TX channel to transmit
    CAN messages that are buffered in the channel. Note that a filter should 
    be enabled using the CANEnableFilter() function after the filter has been 
    linked to the desired channel.
    
  Precondition:
    Filter should have been disabled using the CANEnableFilter() function.

  Parameters:
    module  - Identifies the desired CAN module.

    filter  - Identifies the desired CAN Filter.

    mask    - Identifies the mask to be used with this filter.

    channel - Identifies the channel to be linked to this filter. If a TX channel
              is linked, the TX channel should have it's Remote Transmit Request 
              feature enabled.

  Returns:
    None.

  Example:
    <code>
    
    // Configure CAN1 filter 3 to accept extended ID messages
    // with EID 0x1D400 and link the filter to CAN1 Channel 5.
    // Note the sequence in which the steps are performed.
    // Disable the filter and check if its disabled.
    // Configure the filter. Link it to the Channel and then 
    // enable the filter. 

    CANEnableFilter(CAN1, CAN_FILTER3, FALSE);

    while(CANIsFilterDisabled(CAN1, CAN_FILTER3) == FALSE);

    CANConfigureFilter(CAN1, CAN_FILTER3, 0x1D400, CAN_EID);

    CANLinkFilterToChannel(CAN1, CAN_FILTER3, CAN_FILTER_MASK0, CAN_CHANNEL5);

    CANEnableFilter(CAN1, CAN_FILTER3, TRUE);

    </code>
   
  Remarks:
    None.

  *****************************************************************************/
void CANLinkFilterToChannel(CAN_MODULE module, CAN_FILTER filter, CAN_FILTER_MASK mask, CAN_CHANNEL channel);

/*******************************************************************************
  Function:
    BOOL CANIsFilterDisabled(CAN_MODULE module, CAN_FILTER filter);

  Summary:
    This routine returns TRUE if the specified filter is disabled.

  Description:
    Returns TRUE if the specified filter is disabled. This function should be 
    called to check if the filter is disabled before calling the CANConfigureFilter() 
    and CANLinkFilterToChannel() functions.
    
  Precondition:
    None.

  Parameters:
    module   - Identifies the desired CAN module.

    filter  - Identifies the desired CAN Filter

  Returns:
    Returns the enable disable status of the filter:
    * TRUE - Filter is disabled.
    * FALSE - Filer is enabled.

  Example:
    <code>

    // Disable CAN1 filter 3 and wait until the
    // filter is disabled.

    CANEnableFilter(CAN1, CAN_FILTER3, FALSE);

    while(CANIsFilterDisabled(CAN1, CAN_FILTER3) == FALSE);

    </code>
   
  Remarks:
    None.

  *****************************************************************************/
BOOL CANIsFilterDisabled(CAN_MODULE module, CAN_FILTER filter);


// *****************************************************************************
// *****************************************************************************
// Section: Error State Tracking
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    UINT CANGetRxErrorCount(CAN_MODULE module);

  Summary:
    This routine returns the CAN Receive Error Count.

  Description:
    Returns the CAN Receive Error Count. Refer to the CAN 2.0B specification
    for more details on the CAN Receive Error Count and its significance.
    
  Precondition:
    None.

  Parameters:
    module   - Identifies the desired CAN module.

  Returns:
    Returns the CAN Receive Error Count.

  Example:
    <code>

    // Check if CAN1 Receive error count
    // is more than 200.

    UINT errorCount;

    errorCount = CANGetRxErrorCount(CAN1);

    if(errorCount > 200)
    {
        // This error count is high.
        // Do some diagnostics.

    }

    </code>
   
  Remarks:
    There are multiple bus conditions, which could cause the RX error
    count to increase. Please refer to the CAN 2.0b specification for details. 

  *****************************************************************************/
UINT 			CANGetRxErrorCount(CAN_MODULE module);

/*******************************************************************************
  Function:
    UINT CANGetTxErrorCount(CAN_MODULE module);

  Summary:
    This routine returns the CAN Transmit Error Count.

  Description:
    Returns the CAN Transmit Error Count. Refer to CAN 2.0B specification for
    more details on the CAN Transmit Error Count and its significance.
    
  Precondition:
    None.

  Parameters:
    module   - Identifies the desired CAN module.

  Returns:
    Returns the CAN Transmit Error Count.

  Example:
    <code>

    // Check if the CAN1 Transmit error count
    // is more than 200.

    UINT errorCount;

    errorCount = CANGetTxErrorCount(CAN1);

    if(errorCount > 200)
    {
        // This error count is high.
        // Do some diagnostics.

    }

    </code>
   
  Remarks:
    There are mulitple bus conditions, which could cause the TX error
    count to increase. Please refer to the CAN 2.0b specification for details. 

  *****************************************************************************/
UINT CANGetTxErrorCount(CAN_MODULE module);

/*******************************************************************************
  Function:
    CAN_ERROR_STATE CANGetErrorState(CAN_MODULE module);

  Summary:
    This routine returns the CAN Error Status word.

  Description:
    Returns the CAN Error Status word. The return word can be logically AND'ed 
    with the desired CAN_ERROR_STATE member to check if the CAN module is 
    in a specific error state. 
    
  Precondition:
    None.

  Parameters:
    module   - Identifies the desired CAN module.

  Returns:
    Returns the CAN_ERROR_STATE word, which can be logically AND'ed with the desired
    CAN_ERROR_STATE member to check if the CAN module is in a specific error state.

  Example:
    <code>

    // Check if CAN1 is in the TX or RX warning state.
    
    CAN_ERROR_STATE errorState;

    errorState = CANGetErrorState(CAN1);

    if((errorState & CAN_TX_RX_WARNING_STATE) != 0)
    {
        // CAN1 is in either  TX or RX warning state.

    }

    // Check if CAN2 is in the RX Bus Passive or TX Bus passive
    // state.

    errorState = CANGetErrorState(CAN2);

    if((errorState & (CAN_TX_BUS_PASSIVE_STATE | CAN_RX_BUS_PASSIVE_STATE)) != 0)
    {
        // This means that the CAN module is in TX Bus Passive
        // or RX Bus Passive state.
     }

    </code>
   
  Remarks:
    None.

  *****************************************************************************/

CAN_ERROR_STATE CANGetErrorState(CAN_MODULE module);

// *****************************************************************************
// *****************************************************************************
// Section: Information Function
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    UINT CANTotalModules(void);

  Summary:
    This routine returns the total number of CAN modules on the device.

  Description:
    Returns the total number of CAN modules on the device.
    
  Precondition:
    None.

  Parameters:
    None.

  Returns:
    Returns the total number of CAN modules on the device.
   
  Remarks:
    None.

  *****************************************************************************/
UINT CANTotalModules(void);

/*******************************************************************************
  Function:
    UINT CANTotalChannels(void);

  Summary:
    This routine returns the total number of CAN Channels per CAN module.

  Description:
    Returns the total number of CAN Channels per CAN module.
    
  Precondition:
    None.

  Parameters:
    None.

  Returns:
    Returns the total number of CAN Channels per CAN module.
   
  Remarks:
    None.

  *****************************************************************************/
UINT CANTotalChannels(void);

/*******************************************************************************
  Function:
    UINT CANTotalFilters(void);

  Summary:
    This routine returns the total number of CAN Filters per CAN module.

  Description:
    Returns the total number of CAN Filters per CAN module.
    
  Precondition:
    None.

  Parameters:
    None.

  Returns:
    Returns the total number of CAN Filters per CAN module.
   
  Remarks:
    None.

  *****************************************************************************/
UINT CANTotalFilters(void);

/*******************************************************************************
  Function:
    UINT CANTotalMasks(void);

  Summary:
    This routine returns the total number of CAN Masks per CAN module.

  Description:
    Returns the total number of CAN Masks per CAN module.
    
  Precondition:
    None.

  Parameters:
    None.

  Returns:
    Returns the total number of CAN Masks per CAN module.
   
  Remarks:
    None.

  *****************************************************************************/
UINT CANTotalMasks(void);
#endif

