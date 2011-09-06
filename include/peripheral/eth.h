/*******************************************************************************
  Ethernet Library Interface Definition

  Summary:
    This file contains the Application Program Interface (API) definition  for 
    the Ethernet peripheral library.
    
  Description:
    This library provides a low-level abstraction of the Ethernet module 
    on Microchip PIC32MX family microcontrollers with a convenient C language 
    interface.  It can be used to simplify low-level access to the module 
    without the necessity of interacting directly with the module's registers, 
    thus hiding differences from one microcontroller variant to another.
*******************************************************************************/
//DOM-IGNORE-BEGIN
/*******************************************************************************
FileName:       eth.h
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


#ifndef _ETH_H_
#define _ETH_H_

#include <stdlib.h>
#include <p32xxxx.h>

#ifdef _ETH // The Ethernet device is present


// *****************************************************************************
// *****************************************************************************
// Section: Constants & Data Types
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Ethernet Operation Result Codes

  Summary:
    Defines the possible results of Ethernet operations that can succeed or fail

  Description:
    This enumeration defines the possible results of any of the Ethernet library operations
    that have the possibilty of failing.  This result should be checked to 
    ensure that the operation achieved the desired result.
*/
typedef enum
{
    // Everything ok
    ETH_RES_OK,

    // Ethernet RX, TX, acknowledge packets:

    // No such packet exist
    ETH_RES_NO_PACKET,

    // Packet is queued (not transmitted or received and not processed)
    ETH_RES_PACKET_QUEUED,

    // Ethernet buffers, descriptors errors:

    // Some memory allocation failed
    ETH_RES_OUT_OF_MEMORY,

    // Not enough descriptors available
    ETH_RES_NO_DESCRIPTORS,
    
    // We don't support user space buffers.
    ETH_RES_USPACE_ERR,

    // The size of the receive buffers too small
    ETH_RES_RX_SIZE_ERR,

    // A received packet spans more buffers/descriptors than supplied 
    ETH_RES_RX_PKT_SPLIT_ERR,

    // Negotiation errors:

    // No negotiation support
    ETH_RES_NEGOTIATION_UNABLE,

    // No negotiation active
    ETH_RES_NEGOTIATION_INACTIVE,

    // Negotiation not started yet
    ETH_RES_NEGOTIATION_NOT_STARTED,

    // Negotiation active
    ETH_RES_NEGOTIATION_ACTIVE,

    // Link down after negotiation, negotiation failed
    ETH_RES_NEGOTIATION_LINKDOWN,

    // PHY errors:

    // No Phy was detected or it failed to respond to reset command
    ETH_RES_DTCT_ERR,

    // No match between the capabilities: the Phy supported and the open 
    // requested ones
    ETH_RES_CPBL_ERR,

    // Hardware configuration doesn't match the requested open mode
    ETH_RES_CFG_ERR,

} eEthRes;


// *****************************************************************************
/* Ethernet Open Configuration Settings

  Summary:
    Supported open configuration flags for the Ethernet module (EthMACOpen).

  Description:
    This enumeration defines the various configuration options for the Ethernet 
    module.  These values can be OR-ed together to create a configuration mask
    passed to the EthMACOpen routine.
    
  Remarks:
    When Auto negotiation is specified:
        - If multiple capability flags are set (ETH_OPEN_FDUPLEX, 
          ETH_OPEN_HDUPLEX, ETH_OPEN_100, ETH_OPEN_10 ) they are all advertised
          as this link side capabilities.
        - If no setting is passed, the lowest one is taken, i.e. 
          ETH_OPEN_HDUPLEX and ETH_OPEN_10.
        - Auto-MDIX requires Auto-Negotiation; ETH_OPEN_MDIX_NORM or 
          ETH_OPEN_MDIX_SWAP setting irrelevant.
          
    When No Auto negotiation is specified:
        - If multiple settings, the highest priority setting is taken, i.e. 
          ETH_OPEN_FDUPLEX over ETH_OPEN_HDUPLEX and ETH_OPEN_100 over 
          ETH_OPEN_10.
        - If no setting, the lowest setting is taken, i.e. ETH_OPEN_HDUPLEX and
          ETH_OPEN_10.
        - The MDIX is set based on the ETH_OPEN_MDIX_NORM/ETH_OPEN_MDIX_SWAP
          setting.
*/
typedef enum
{
    // Link capabilities flags:

    // Use auto negotiation. set the following flags to specify your choices
    ETH_OPEN_AUTO
        /*DOM-IGNORE-BEGIN*/ = 0x1 /*DOM-IGNORE-END*/,

    // Use full duplex or full duplex negotiation capability needed
    ETH_OPEN_FDUPLEX
        /*DOM-IGNORE-BEGIN*/ = 0x2 /*DOM-IGNORE-END*/,

    // Use half duplex or half duplex negotiation capability needed
    ETH_OPEN_HDUPLEX
        /*DOM-IGNORE-BEGIN*/ = 0x4 /*DOM-IGNORE-END*/,

    // Use 100MBps or 100MBps negotiation capability needed
    ETH_OPEN_100
        /*DOM-IGNORE-BEGIN*/ = 0x8 /*DOM-IGNORE-END*/,

    // Use 10MBps or 10MBps negotiation capability needed
    ETH_OPEN_10
        /*DOM-IGNORE-BEGIN*/ = 0x10 /*DOM-IGNORE-END*/,

    // MAC flags:

    // Allow huge packets RX/TX
    ETH_OPEN_HUGE_PKTS
        /*DOM-IGNORE-BEGIN*/ = 0x20 /*DOM-IGNORE-END*/,

    // Loopbacked at the MAC level
    ETH_OPEN_MAC_LOOPBACK
        /*DOM-IGNORE-BEGIN*/ = 0x40 /*DOM-IGNORE-END*/,

    // When PHY is loopback-ed, negotiation will be disabled!
    ETH_OPEN_PHY_LOOPBACK
        /*DOM-IGNORE-BEGIN*/ = 0x80 /*DOM-IGNORE-END*/,

    // MDIX flags:

    // Use Auto MDIX
    ETH_OPEN_MDIX_AUTO
        /*DOM-IGNORE-BEGIN*/ = 0x100 /*DOM-IGNORE-END*/,

    // Use normal MDIX when Auto MDIX disabled
    ETH_OPEN_MDIX_NORM
        /*DOM-IGNORE-BEGIN*/ = 0x0 /*DOM-IGNORE-END*/,

    // Use swapped MDIX when Auto MDIX disabled
    ETH_OPEN_MDIX_SWAP
        /*DOM-IGNORE-BEGIN*/ = 0x200 /*DOM-IGNORE-END*/,

    // MII/RMII flags:

    // RMII connection
    ETH_OPEN_RMII
        /*DOM-IGNORE-BEGIN*/ = 0x400 /*DOM-IGNORE-END*/,

    // MII connection
    ETH_OPEN_MII
        /*DOM-IGNORE-BEGIN*/ = 0x000 /*DOM-IGNORE-END*/,

    
    // All capabilities default
    ETH_OPEN_DEFAULT = (ETH_OPEN_AUTO|ETH_OPEN_FDUPLEX|ETH_OPEN_HDUPLEX|
                        ETH_OPEN_100|ETH_OPEN_10|ETH_OPEN_MDIX_AUTO)

} eEthOpenFlags;


// *****************************************************************************
/* Ethernet Link Status Codes

  Summary:
    Defines the possible status flags of Ethernet link.

  Description:
    This enumeration defines the flags describing the status of the Ethernet 
    link.
  
  Remarks:
    Multiple flags can be set
*/
typedef enum
{
    // No connection to the LinkPartner
    ETH_LINK_ST_DOWN
        /*DOM-IGNORE-BEGIN*/ = 0x0 /*DOM-IGNORE-END*/,

    // Link is up
    ETH_LINK_ST_UP
        /*DOM-IGNORE-BEGIN*/ = 0x1 /*DOM-IGNORE-END*/,

    // LP non negotiation able
    ETH_LINK_ST_LP_NEG_UNABLE
        /*DOM-IGNORE-BEGIN*/ = 0x2 /*DOM-IGNORE-END*/,

    // LP fault during negotiation
    ETH_LINK_ST_REMOTE_FAULT
        /*DOM-IGNORE-BEGIN*/ = 0x4 /*DOM-IGNORE-END*/,

    // Parallel Detection Fault encountered (when ETH_LINK_ST_LP_NEG_UNABLE)
    ETH_LINK_ST_PDF
        /*DOM-IGNORE-BEGIN*/ = 0x8 /*DOM-IGNORE-END*/,

    // LP supports symmetric pause
    ETH_LINK_ST_LP_PAUSE
        /*DOM-IGNORE-BEGIN*/ = 0x10 /*DOM-IGNORE-END*/,

    // LP supports asymmetric TX/RX pause operation
    ETH_LINK_ST_LP_ASM_DIR
        /*DOM-IGNORE-BEGIN*/ = 0x20 /*DOM-IGNORE-END*/,

    // LP not there
    ETH_LINK_ST_NEG_TMO
        /*DOM-IGNORE-BEGIN*/ = 0x1000 /*DOM-IGNORE-END*/,

    // An unexpected fatal error occurred during the negotiation
    ETH_LINK_ST_NEG_FATAL_ERR
        /*DOM-IGNORE-BEGIN*/ = 0x2000 /*DOM-IGNORE-END*/,
    
} eEthLinkStat;


// *****************************************************************************
/* Ethernet Controller Status Codes

  Summary:
    Defines the possible status codes of Ethernet controller.

  Description:
    This enumeration defines the flags describing the status of the Ethernet 
    controller.
*/
typedef enum
{
    // A packet is currently received
    ETH_ST_RXBUSY   /*DOM-IGNORE-BEGIN*/ = 0x1 /*DOM-IGNORE-END*/,

    // A packet is currently transmitted
    ETH_ST_TXBUSY   /*DOM-IGNORE-BEGIN*/ = 0x2 /*DOM-IGNORE-END*/,

    // Module is on or completing a transaction
    ETH_ST_BUSY     /*DOM-IGNORE-BEGIN*/ = 0x4 /*DOM-IGNORE-END*/,

} eEthStat;


// *****************************************************************************
/* Ethernet Module Disable

  Summary:
    Defines the possible disable codes of Ethernet controller "EthClose" call.

  Description:
    This enumeration defines the close capabilities of the Ethernet module.
*/
typedef enum
{
    // Wait for the current TX/RX op to finish
    ETH_CLOSE_GRACEFUL  /*DOM-IGNORE-BEGIN*/ = 0x1 /*DOM-IGNORE-END*/,

    // Default close options
    ETH_CLOSE_DEFAULT = (0)

} eEthCloseFlags;


// *****************************************************************************
/* Ethernet MAC Pause Types

  Summary:
    Defines the possible Ethernet MAC pause types.

  Description:
    This enumeration defines the Ethernet MAC's pause capabilities.
*/
typedef enum
{
    // No PAUSE capabilities
    ETH_MAC_PAUSE_TYPE_NONE     /*DOM-IGNORE-BEGIN*/ = 0x0 /*DOM-IGNORE-END*/,

    // Supports symmetric PAUSE
    ETH_MAC_PAUSE_TYPE_PAUSE    /*DOM-IGNORE-BEGIN*/ = 0x1 /*DOM-IGNORE-END*/,

    // Supports ASM_DIR
    ETH_MAC_PAUSE_TYPE_ASM_DIR  /*DOM-IGNORE-BEGIN*/ = 0x2 /*DOM-IGNORE-END*/,

    // The previous two values converted to TX/RX capabilities:

    // Enable MAC TX pause support
    ETH_MAC_PAUSE_TYPE_EN_TX    /*DOM-IGNORE-BEGIN*/ = 0x4 /*DOM-IGNORE-END*/,

    // Enable MAC RX pause support
    ETH_MAC_PAUSE_TYPE_EN_RX    /*DOM-IGNORE-BEGIN*/ = 0x8 /*DOM-IGNORE-END*/,

    // All types of pause
    ETH_MAC_PAUSE_ALL       = (ETH_MAC_PAUSE_TYPE_PAUSE|ETH_MAC_PAUSE_TYPE_ASM_DIR|
                           ETH_MAC_PAUSE_TYPE_EN_TX|ETH_MAC_PAUSE_TYPE_EN_RX),

    // All pause capabilities our MAC supports
    ETH_MAC_PAUSE_CPBL_MASK = ETH_MAC_PAUSE_ALL

} eEthMacPauseType;


// *****************************************************************************
// *****************************************************************************
// Section: Ethernet Peripheral Library Interface Routines
// *****************************************************************************
// *****************************************************************************

// Section:  Open and Configuration Functions

/*******************************************************************************
  Function:
    eEthRes EthInit ( void )

  Summary:
    Ethernet initialization routine

  Description:
    This function performs the initialization of the Ethernet Controller.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    ETH_RES_OK

  Example:
    <code>
    EthInit();
    </code>

  Remarks:
    This function should be called before the EthMACOpen() routine.
 *****************************************************************************/

eEthRes EthInit ( void );


/*******************************************************************************
  Function:
    eEthRes EthClose( eEthCloseFlags cFlags )

  Summary:
    Aborts any transactions and disables the Ethernet controller

  Description:
    This function performs an abort of any current Ethernet transactions, disables
    the Ethernet controller and interrupts.  It should be called after the PHY
    close/reset procedure.

  Precondition:
    None.

  Parameters:
    cFlags      - closing flags

  Returns:
    ETH_RES_OK

  Example:
    <code>
    EthClose(ETH_CLOSE_DEFAULT);
    </code>

  Remarks:
    It does not free any allocated memory.
 *****************************************************************************/

eEthRes EthClose ( eEthCloseFlags cFlags );


/*******************************************************************************
  Function:
    void EthMACOpen( eEthOpenFlags oFlags, eEthMacPauseType pauseType )

  Summary:
    Initializes and configures the Ethernet MAC.

  Description:
    This function performs the open and configuration of the Ethernet MAC.  It needs
    to be called after the EthInit() was called and the PHY initialized.


  Precondition:
    EthInit must have been called.

  Parameters:
    oFlags      - Open flags
    pauseType   - Pause type to be supported by the MAC


  Returns:
    Ethernet operation result code.

  Example:
    <code>
    // Enable loopback at the MAC level
    oFlags    = ETH_OPEN_FDUPLEX|ETH_OPEN_100|ETH_OPEN_HUGE_PKTS|ETH_OPEN_MAC_LOOPBACK;
    // Use both TX and RX pause type for Full Duplex
    pauseType = ETH_MAC_PAUSE_ALL;
    
    // Start the initialization sequence
    EthInit();

    // Open and configure the MAC.
    //
    // Since we're not connected to an external PHY there's no negotiation
    // going on and we know all our opening flags
    EthMACOpen(oFlags, pauseType);
    </code>

  Remarks:
    If no auto-negotiation is performed, the EthMACOpen() could be called
    immediately after EthInit() and PHY initialization.  Otherwise the open
    flags and the pause type should be the ones obtained as a result of the
    PHY negotiation procedure! 
 *****************************************************************************/

void EthMACOpen ( eEthOpenFlags oFlags, eEthMacPauseType pauseType );


/*******************************************************************************
  Function:
    void EthMACSetAddress ( unsigned char bAddress[6] )

  Summary:
    Sets the MAC address

  Description:
    This function sets the MAC address.

  Precondition:
    None.

  Parameters:
    bAddress    - standard MAC address, 6 bytes, Network order!

  Returns:
    None.

  Example:
    <code>
    unsigned char hostAddress[6]= { 0x00, 0x04, 0xa3, 0x00, 0x00, 0x02};
    
    EthMACSetAddress(hostAddress);
    </code>

  Remarks:
    The default MAC address is loaded by the device at reset from the
    factory pre-programmed unique MAC address value.
 *****************************************************************************/

void EthMACSetAddress ( unsigned char bAddress[6] );


/*******************************************************************************
  Function:
    void EthMACGetAddress ( unsigned char bAddress[6] )

  Summary:
    Returns the current MAC address

  Description:
    This function returns the current MAC address.

  Precondition:
    None.

  Parameters:
    bAddress    - Address to store a standard MAC address, 6 bytes, Network 
                  order!

  Returns:
    None.

  Example:
    <code>
    unsigned char currentMacAddress;
    
    EthMACGetAddress(&currentMacAddress);
    </code>

  Remarks:
 *****************************************************************************/

void EthMACGetAddress ( unsigned char bAddress[6] );


/*******************************************************************************
  Function:
    void EthMACSetMaxFrame ( unsigned short maxFrmSz )

  Summary:
    Sets the MAC maximum frame size

  Description:
    This function sets the MAC maximum frame size.

  Precondition:
    Should be called after EthInit().

  Parameters:
    maxFrmSz    - Maximum frame for the MAC to transmit or receive.

  Returns:
    None.

  Example:
    <code>
    EthMACSetMaxFrame(0x800);
    </code>

  Remarks:
    The default MAC frame size (0x600) is set by the EthInit() call.
 *****************************************************************************/

void EthMACSetMaxFrame ( unsigned short maxFrmSz );


// Section: Descriptors and Buffers Functions


// *****************************************************************************
/* Ethernet Descriptor Allocation Function Pointer

  Function:
    void* <FunctionName> ( size_t nitems, size_t size, void* param )

  Summary:
    Pointer to a function that allocates the requested memory and returns a 
    pointer to it.

  Description:
    Pointer to a function that allocates enough memory for "nitems" each of 
    "size" bytes in length (total memory requested is nitems*size).
    The allocated space should be initialized to zero.
    
  Precondition:
    None

  Parameters:
    nitems      - number of items to be allocated
    size        - size of each item, in bytes
    param       - extra parameter that will be used by the function call    

  Returns:
    On success  - A pointer to the requested space.
    On failure  = A null pointer.
    
  Remarks:
    This function will be invoked for allocation of descriptors only.  
    Therefore, the size parameter will be the one returned by 
    EthDescriptorsGetSize();
*/

typedef void* ( *pEthDcptAlloc )( size_t nitems, size_t size, void* param );


// *****************************************************************************
/* Ethernet Descriptor Free Function

  Function:
    void <FunctionName> ( void* ptr, void* param )

  Summary:
    Pointer to a function that deallocates the memory previously allocated by a
    pEthDcptAlloc function.

  Description:
    Pointer to a function that deallocates the memory previously allocated by a
    pEthDcptAlloc function.
    
  Precondition:
    The pEthDcptAlloc would have been previously called.

  Parameters:
    ptr         - Points to the space that was previously allocated with a 
                  pEthDcptAlloc function.
    param       - extra parameter that will be used by the function call    

  Returns:
    None.
    
  Remarks:
    None.
*/

typedef void ( *pEthDcptFree ) ( void* ptr, void* param );


// *****************************************************************************
/* Ethernet Descriptor Types

  Summary:
    Enumeration defining the Ethernet descriptor types.

  Description:
    This enumeration defines the Ethernet descriptor types.
  
  Remarks:
    Most descriptor operations support just one type, but multiple flags can be
    set.
*/

typedef enum
{
    // TX descriptor
    ETH_DCPT_TYPE_RX    /*DOM-IGNORE-BEGIN*/ = 0x1 /*DOM-IGNORE-END*/,

    // RX descriptor
    ETH_DCPT_TYPE_TX    /*DOM-IGNORE-BEGIN*/ = 0x2 /*DOM-IGNORE-END*/,

    // All (both) types.  Some descriptor operations support multiple types.
    ETH_DCPT_TYPE_ALL   = (ETH_DCPT_TYPE_RX|ETH_DCPT_TYPE_TX)

}eEthDcptType;      // descriptor types



// *****************************************************************************
/* Ethernet Descriptor Query Structure

  Summary:
    Structure used for a query of the Ethernet descriptors

  Description:
    This structure holds a snapshot of the current status of RX/TX descriptors.
*/

typedef struct
{
    // The number of idle (unused) descriptors available in the TX/RX pool of descriptors.
    int dIdle;

    // The number of descriptors not acknowledged
    // Provides the number of descriptors that have valid transmitted/received packets
    // but haven't been acknowledged
    int dUnack;

    // The number of queued descriptors 
    // Provides the number of descriptors that are just
    // queued for transmission (but not transmitted yet) or
    // receiving (but without a valid load).
    int dQueued;

}sEthDcptQuery;


// *****************************************************************************
/*  Buffer Flags

  Summary:
    Flags for buffer attributes.

  Description:
    Some buffers can have special attributes, as defined by this enumeration.
*/

typedef enum
{
    // The receive buffer is sticky, going to be used across multiple RX
    // operations once it's acknowledged
    ETH_BUFF_FLAG_RX_STICKY /*DOM-IGNORE-BEGIN*/ = 0x1 /*DOM-IGNORE-END*/,

    // The receive descriptor associated to this buffer should not be
    // automatically acknowledged when EthRxAcknowledgeBuffer/EthRxAcknowledgePacket
    // is called.
    // User is responsible for specifically calling EthAckRxDcpt() to acknowledge
    // the RX descriptor
    ETH_BUFF_FLAG_RX_UNACK /*DOM-IGNORE-BEGIN*/ = 0x2 /*DOM-IGNORE-END*/,
} eEthBuffFlags;


/*******************************************************************************
  Function:
    int EthDescriptorsPoolAdd ( int nDescriptors, eEthDcptType dType, 
                            pEthDcptAlloc fAlloc, void* fParam )

  Summary:
    Adds transmit & receive descriptors to the pool.

  Description:
    This function adds the specified number of transmit/receive descriptors to 
    the pool of descriptors.  These descriptors are used whenever a new 
    transmission or a reception is initiated.  The needed memory per descriptor
    is returned by EthDescriptorsGetSize.   Descriptors can be freed with 
    EthDescriptorsPoolRemove.

  Precondition:
    EthInit should have been called.

  Parameters:
    nDescriptors    - Number of descriptors to be added
    
    dType           - TX/RX descriptors requested
    
    fAlloc          - Function to be called to allocate the needed memory 

    fParam          - parameter to be used when fAlloc is called                       

  Returns:
    The number of descriptors successfully created.

  Example:
    <code>
    if( EthDescriptorsPoolAdd(txDcptNo, ETH_DCPT_TYPE_TX, fMemAlloc, &myInstanceData) != txDcptNo )
    {
        // Handle allocation error
    }
    </code>

  Remarks:
    The number of created descriptors is different from the number of 
    requested ones only if the memory allocation failed.

    The first time the specific pool is initialized an extra descriptor is added to the pool
    so that the actual memory requested will be (nDescriptors+1)*EthDescriptorsGetSize().
  
    fAlloc should not be NULL. 
          
    The complete clean-up is done by EthDescriptorsPoolCleanUp();
    
    ETH_DCPT_TYPE_ALL use is invalid. A proper descriptor type (RX or TX) has
    to be used.
 *****************************************************************************/

int EthDescriptorsPoolAdd ( int nDescriptors, eEthDcptType dType, pEthDcptAlloc fAlloc, void* fParam );


/*******************************************************************************
  Function:
    int EthDescriptorsPoolRemove ( int nDescriptors, eEthDcptType dType, 
                               pEthDcptFree fFree, void* fParam )

  Summary:
    Tries to remove the specified number of descriptors from the pool.

  Description:
    This function tries to remove the specified number of descriptors from the
    pool of transmit/receive descriptors.  These descriptors that are NOT used
    at the time of call can be freed (i.e. the TX descriptors not queued for a
    transmission or the not busy RX descriptors).

  Precondition:
    EthInit should have been called.

  Parameters:
    nDescriptors    - Number of descriptors to be removed
    dType           - TX/RX descriptors requested
    fFree           - Function to release the the memory
    fParam          - parameter to be used when fFree is called                       


  Returns:
    The number of descriptors removed.

  Example:
    <code>
    if ( EthDescriptorsPoolRemove(txDcptNo, ETH_DCPT_TYPE_TX, ffree, 0) != txDcptNo)
    {
        // Handle de-allocation error.
    }
    </code>

  Remarks:
    If fFree is NULL then the descriptors are removed from the specified pool but no de-allocation
    function is called.
    The allocation/deallocation memory functions should be consistent.
    
    The complete clean-up is done by EthDescriptorsPoolCleanUp.
    
    ETH_DCPT_TYPE_ALL use is invalid. A proper descriptor type (RX or TX) has
    to be used.
 *****************************************************************************/

int EthDescriptorsPoolRemove ( int nDescriptors, eEthDcptType dType, pEthDcptFree fFree, void* fParam );


/*******************************************************************************
  Function:
    void EthDescriptorsPoolCleanUp ( eEthDcptType dType, pEthDcptFree fFree, void* fParam )

  Summary:
    Removes all the specified descriptors from the pool.

  Description:
    This function performs descriptors clean-up and removes all the specified
    descriptors from the pool of transmit/receive descriptors.

  Precondition:
    EthClose should have been called. 

  Parameters:
    dType        - TX/RX/All descriptors requested
    fFree        - Function to release the the memory
    fParam       - parameter to be used when fFree is called                       

  Returns:
    None.

  Example:
    <code>
    EthDescriptorsPoolCleanUp(ETH_DCPT_TYPE_ALL, fFree, &myInstanceData);
    </code>

  Remarks:
    If fFree is NULL then the descriptors are removed from the pools but no de-allocation
    function is called.
    The allocation/deallocation memory functions should be consistent.
    
    It does not free the memory allocated for the application supplied "sticky"
    buffers.  It is the calling application responsibility.
    
    EthClose should have been called or no TX/RX activity should be enabled at
    the time this function is called.
    
    If ETH_DCPT_TYPE_ALL is supplied the function will perform the clean-up of
    both types of descriptors.
 *****************************************************************************/

void EthDescriptorsPoolCleanUp ( eEthDcptType dType, pEthDcptFree fFree, void* fParam );


/*******************************************************************************
  Function:
    int EthDescriptorsGetSize ( eEthDcptType dType )

  Summary:
    Returns the number of bytes needed for the storage of a descriptor.

  Description:
    This function returns the number of bytes needed for the storage of a 
    descriptor in the transmit/receive engine.

  Precondition:
    None.

  Parameters:
    dType       - TX/RX/All descriptors requested

  Returns:
    The size of a descriptor.

  Example:
    <code>
    maxSize = EthDescriptorsGetSize(ETH_DCPT_TYPE_ALL);
    </code>

  Remarks:
    If ETH_DCPT_TYPE_ALL supplied the function will return them size that 
    accommodates both descriptors (maximum of the two values). 
 *****************************************************************************/

int EthDescriptorsGetSize ( eEthDcptType dType );


/*******************************************************************************
  Function:
    void EthDescriptorsQuery ( eEthDcptType dType, sEthDcptQuery *pQuery )

  Summary:
    Takes a snapshot of the current status of RX/TX descriptors.

  Description:
    This function takes a snapshot of the current status of RX/TX descriptors
    and provides the query result.

  Precondition:

  Parameters:
    dType       - TX/RX descriptors requested

    pQuery      - Address to store the result of the query

                  See the sEthDcptQuery for details.

  Returns:
    None.

  Example:
    <code>
    sEthDcptQuery queryResult;
    
    EthDescriptorsQuery(ETH_DCPT_TYPE_RX, &queryResult);
    </code>

  Remarks:
    The returned numbers are info only. They can dynamically change.

    No protection against interrupts, multithreading, etc.

    ETH_DCPT_TYPE_ALL use is invalid. A proper descriptor type (RX or TX) has
    to be used.
 
    Whenever the automatic flow control is turned on, the reception will come
    to a halt once the number of unacknowledged RX descriptors (dUnack for 
    query using ETH_DCPT_TYPE_RX) reaches 256.  Also the number of currently
    received and unacknowledged descriptors control the behavior of the 
    automatic flow control.  See EthFCEnable for details.
 *****************************************************************************/

void EthDescriptorsQuery ( eEthDcptType dType, sEthDcptQuery *pQuery );


/*******************************************************************************
  Function:
    int EthDescriptorsGetRxUnack( void )

  Summary:
    Provides the number of RX descriptors that are properly received and not 
    acknowledged.

  Description:
    This function returns the number of RX descriptors that have been properly
    received by the receive engine and not acknowledged.
    These descriptors have to be acknowledged by software by calling
    EthRxAcknowledgePacket/EthRxAcknowledgeBuffer.

  Precondition:
    EthInit should have been called.

  Parameters:
    None.

  Returns:
    The number of RX descriptors that are currently unacknowledged.

  Example:
    <code>
    if ( EthDescriptorsGetRxUnack()) >= 256 )
    {
        // Handle RX halt
    }
    </code>

  Remarks:
    Fast shortcut for getting the number of un-acknowledged RX descriptors.
    
    Whenever the automatic flow control is turned on, the reception will come
    to a halt once this number reaches 256.  The number of currently received
    descriptors control the behavior of the automatic flow control.  See 
    EthFCEnable for details.
 *****************************************************************************/

int EthDescriptorsGetRxUnack ( void );

// DOM-IGNORE-BEGIN
extern __inline__ int __attribute__((always_inline)) EthDescriptorsGetRxUnack( void )
{
    return ETHSTATbits.BUFCNT;
}
// DOM-IGNORE-END


/*******************************************************************************
  Function:
    void* EthDescriptorGetBuffer ( void *pDcpt )

  Summary:
    Returns the associated descriptor buffer.

  Description:
    This function returns the buffer currently associated with the specified descriptor.

  Precondition:

  Parameters:
    pDcpt       - Pointer to a Ethernet Descriptor


  Returns:
    The address of the buffer associated with this descriptor or NULL if no such descriptor/buffer
    exists.

  Example:
    <code>
    
    EthDescriptorsPoolRemove ( 1, ETH_DCPT_TYPE_RX, myRxFreeFnc, 0 );

    void myRxFreeFnc( void* ptr, void* param)
    {
        void* pBuff = EthDescriptorGetBuffer(ptr);
        if(pBuff)
        {
            // De-allocate the associated buffer
        }
    }

    </code>

  Remarks:
    The function is a helper that returns the buffer associated with a descriptor.
    It can be used to perform the queued RX/TX buffers clean-up since this list is
    maintained by the Ethernet library anyway.

    The pointer for a descriptor is returned by one of the
    EthDescriptorsPoolRemove() or EthDescriptorsPoolCleanUp() calls as the 
    first parameter of the fFree function.

    No protection against interrupts, multithreading, etc.

 *****************************************************************************/

void*      EthDescriptorGetBuffer ( void *pDcpt );



/*******************************************************************************
  Function:
    eEthRes EthRxBuffersAppend ( void *ppBuff[], int nBuffs, 
                                 eEthBuffFlags rxFlags )
                                 
  Summary:
    Supplies buffers to the receiving process and enables the receiving part of
    the controller.

  Description:
    This function supplies buffers to the receiving process and enables the
    receiving part of the controller.  As soon as the controller starts
    receiving data packets these will be stored into memory at the addresses
    specified by these buffers.  A received packet can consist of multiple
    buffers, split across buffers with the SAME size, as specified in the 
    EthRxSetBufferSize.  Each buffer needs an associated receive descriptor.
    Therefore, the number of needed receive descriptors should be available for
    this function to succeed.  Once a receive operation is scheduled,
    EthRxGetPacket() can be called to get the received packet.  

  Precondition:
    EthInit, EthDescriptorsPoolAdd, EthRxSetBufferSize should have been called.
    Each buffer supplied should be >= EthRxSetBufferSize().

  Parameters:
    ppBuff      - Pointer to an array of buffers (could be NULL terminated) to
                  be appended to the receiving process
                  
    nBuffs      - Number of buffers supplied (or 0 if ppBuff is NULL 
                  terminated)
                  
    rxFlags     - Flags applied to all RX buffers passed

  Returns:
    ETH_RES_OK              - success

    ETH_RES_NO_DESCRIPTORS  - no enough RX descriptors 

    ETH_RES_USPACE_ERR      - buffers in user space not supported


  Example:
    <code>
    ethRes = EthRxBuffersAppend(rxBuffers, rxDcptNo, ETH_BUFF_FLAG_RX_STICKY);
    if ( ethRes != ETH_RES_OK )
    {
        // Handle error
    }
    </code>

  Remarks:
    Not multithreaded safe. Don't call from from both ISR -non ISR code or 
    multiple ISR's!
    
    This function enables the Ethernet receiving.
    
    When a packet is split into multiple buffers, all buffers have the same
    size, set by the EthRxSetBufferSize().
    
    The append process continues until a NULL buffer pointer is retrieved or
    nBuffs buffers are appended.
    
    Only RX eEthBuffFlags are relevant for this function 
 *****************************************************************************/

eEthRes EthRxBuffersAppend ( void *ppBuff[], int nBuffs, eEthBuffFlags rxFlags );

/*******************************************************************************
  Function:
    eEthRes EthRxSetBufferSize ( int rxBuffSize )

  Summary:
    Sets the required buffer size for the receive operation.

  Description:
    This function sets the required buffer size for the receive operation.  In
    this implementation, all receive descriptors use the same buffer size
    (unlike the transmission flow where each descriptor can have a different
    buffer size).

  Precondition:
    0 < rxBuffSize <= 2032

    rxBuffSize multiple of 16

  Parameters:
    rxBuffSize      - size of the RX buffers

  Returns:
    ETH_RES_OK              - success

    ETH_RES_RX_SIZE_ERR     - the requested size is invalid

  Example:
    <code>
    EthRxSetBufferSize(rxBuffSize);
    </code>

  Remarks:
    This function should be part of the initialization process and shoult NOT
    be called when the RX process is active!
    
    The receive buffer size is always TRUNCATED to a multiple of 16 bytes.
 *****************************************************************************/

eEthRes EthRxSetBufferSize ( int rxBuffSize );


// Section:  TX/RX Functions


// *****************************************************************************
/*  Packet Descriptor

  Summary:
    Descriptor of a packet accepted by the TX/RX Ethernet engine.

  Description:
    A packet handled by the Ethernet TX/RX engine is a list of buffer 
    descriptors.  A packet consists of multiple buffers and each buffer needs a
    descriptor.  Although the number of buffers per packet is not limited, note 
    that the hardware overhead is higher when many buffers have to be handled
    for one packet.  The list ends when the next field is NULL or when the pBuff
    is NULL. 
*/

typedef struct _tag_sEthPktDcpt 
{
    // Next descriptor in chain. NULL to end
    struct _tag_sEthPktDcpt  *next;

    // Buffer to be transmitted
    void                   *pBuff;

    // Number of bytes in the buffer 0-2047 allowed
    unsigned short int      nBytes;

} /*DOM-IGNORE-BEGIN*/ __attribute__ ((__packed__)) /*DOM-IGNORE-END*/ sEthPktDcpt;    


// *****************************************************************************
/*  Transmitted Packet Status

  Summary:
    Status of a transmitted packet.

  Description:
    This structure contains the status of a transmitted packet.
  
  Notes:
    Status is always two "words" (64-bits) long.
*/

typedef union
{
    struct
    {
        // Total bytes transmitted
        unsigned short  totTxBytes;

        // Control frame transmitted
        unsigned        txCtrl      : 1;

        // Pause control frame transmitted
        unsigned        txPause     : 1;

        // Transmit backpressure applied
        unsigned        txBPres     : 1;

        // Transmit VLAN tagged frame
        unsigned        txVLAN      : 1;

        unsigned                    : 12;

        // Transmit bytes count
        unsigned short  bCount;

        // Transmit collision count
        unsigned        collCount   : 4;

        // Transmit CRC error
        unsigned        crcError    : 1;

        // Tansmit length check error
        unsigned        lenError    : 1;

        // Tansmit length out of range
        unsigned        lenRange    : 1;

        // Transmit done
        unsigned        txDone      : 1;

        // Transmit multicast
        unsigned        mcast       : 1;

        // Transmit broadcast
        unsigned        bcast       : 1;

        // Transmit packet defer
        unsigned        defer       : 1;

        // Transmit excessive packet defer
        unsigned        excDefer    : 1;

        // Transmit maximum collision
        unsigned        maxColl     : 1;

        // Transmit late collision
        unsigned        lateColl    : 1;

        // Transmit giant frame (set when pktSz>MaxFrameSz && HugeFrameEn==0)
        unsigned        giant       : 1;

        // Transmit underrun
        unsigned        underrun    : 1;

    }__attribute__ ((__packed__));

    // Status is 2 words always
    unsigned long long  w;

} sEthTxPktStat;


// *****************************************************************************
/*  Received Packet Status

  Summary:
    Status of a received packet.

  Description:
    This structure contains the status of a received packet.
  
  Notes:
    Status is always two "words" (64-bits) long.
*/

typedef union
{
    struct 
    {
        // Packet payload checksum
        unsigned        pktChecksum     :16;

        unsigned                        : 8;

        // Runt packet received
        unsigned        runtPkt         : 1;

        // Unicast, not me packet,
        unsigned        notMeUcast      : 1;

        // Hash table match
        unsigned        htMatch         : 1;

        // Magic packet match
        unsigned        magicMatch      : 1;

        // Pattern match match
        unsigned        pmMatch         : 1;

        // Unicast match
        unsigned        uMatch          : 1;

        // Broadcast match
        unsigned        bMatch          : 1;

        // Multicast match
        unsigned        mMatch          : 1;

        // Received bytes
        unsigned        rxBytes         :16;

        // Packet previously ignored
        unsigned        prevIgnore      : 1;

        // RX data valid event previously seen
        unsigned        prevDV          : 1;

        // Carrier event previously seen
        unsigned        prevCarrier     : 1;

        // RX code violation
        unsigned        rxCodeViol      : 1;

        // CRC error in packet
        unsigned        crcError        : 1;

        // Receive length check error
        unsigned        lenError        : 1;

        // Receive length out of range
        unsigned        lenRange        : 1;

        // Receive OK
        unsigned        rxOk            : 1;

        // Multicast packet
        unsigned        mcast           : 1;

        // Broadcast packet
        unsigned        bcast           : 1;

        // Dribble nibble
        unsigned        dribble         : 1;

        // Control frame received
        unsigned        rxCtrl          : 1;

        // Pause control frame received
        unsigned        rxPause         : 1;

        // Received unsupported code
        unsigned        rxCodeErr       : 1;

        // Received VLAN tagged frame
        unsigned        rxVLAN          : 1;

        unsigned                        : 1;

    }__attribute__ ((__packed__));

    // Status is 2 words always
    unsigned long long  w;

} sEthRxPktStat;



// *****************************************************************************
/* Ethernet Buffer Acknowledge Callback Function

  Function:
    void <Function Name> ( void *pPktBuff, int buffIx, void* param )

  Summary:
    Pointer to an function called to acknowledge a buffer/packet.

  Description:
    Pointer to a function called to acknowledge the completion of a buffer/packet.
    
  Precondition:
    A TX or RX packet must have been queued.

  Parameters:
    pPktBuff    - Pointer to the currently acknowledged transmitted or received
                  buffer.
    
    buffIx      - The 0-based buffer index for a packet that spans multiple 
                  buffers.

    param       - extra parameter that will be used by the function call    
                  

  Returns:
    None.
    
  Remarks:
    This function is meant to be used for both RX and TX packets acknowledge.
    It allows the caller to pass an extra parameter that will be used in the
    function call.
    
*/

typedef void ( *pEthBuffAck ) ( void *pPktBuff, int buffIx, void* param );


/*******************************************************************************
  Function:
    eEthRes EthTxSendBuffer ( const void *pBuff, unsigned short int nBytes )

  Summary:
    Schedules the supplied buffer for transmission

  Description:
    This function schedules the supplied buffer for transmission.  To transmit
    this buffer an associated transmit descriptor is needed.  Therefore, a 
    transmit descriptor should be available for this function to succeed.  Once
    a transmission is scheduled and done, EthTxGetBufferStatus can be called to
    check the transmission result.  

  Precondition:
    EthMACOpen, EthDescriptorsPoolAdd should have been called.
    Valid buffer pointer required.
    Buffers specified should be > 0 and < 2048 bytes in size.

  Parameters:
    pBuff       - Adress of buffer to be sent
    
    nBytes      - Size of the buffer in bytes

  Returns:
    ETH_RES_OK              - success

    ETH_RES_NO_DESCRIPTORS  - no descriptors available

    ETH_RES_USPACE_ERR      - user space buffers not supported

  Example:
    <code>
    EthTxSendBuffer(txBuffer, pktSize);
    </code>

  Remarks:
    Not multithreaded safe.  Don't call from from both ISR and non ISR code
    or multiple ISR's!
    
    This function enables the Ethernet transmission.
    
    This function is for transmission of packets completely assembled in one 
    buffer.
 *****************************************************************************/

eEthRes EthTxSendBuffer ( const void *pBuff, unsigned short int nBytes );


/*******************************************************************************
  Function:
    eEthRes EthTxSendPacket ( const sEthPktDcpt *pPkt )

  Summary:
    Schedules the supplied packet for transmission.

  Description:
    This function schedules the supplied packet for transmission.  Each packet
    can consist of multiple buffers, each having a different size, as specified
    in the packet descriptor.  Each buffer will need an associated transmit
    descriptor. Therefore, the number of needed transmit descriptors should be
    available for this function to succeed.  Once a transmission is scheduled
    and done, EthTxGetPacketStatus can be called to check the transmission 
    result.  

  Precondition:
    EthMACOpen, EthDescriptorsPoolAdd should have been called.
    Valid packet descriptor pointer required.
    Buffers specified should be >0 and < 2048 bytes in size.

  Parameters:
    pPkt        - Packet descriptor consisting of a list of buffer descriptors,
                  terminated by a NULL pointer.

  Returns:
    ETH_RES_OK              - success

    ETH_RES_NO_DESCRIPTORS  - no descriptors available

    ETH_RES_USPACE_ERR      - user space buffers not supported

  Example:
    <code>
    ethRes = EthTxSendPacket(&txDcpt);
    if ( ethRes != ETH_RES_OK )
    {
        // Transmission failed
    }
    </code>

  Remarks:
    Not multithreaded safe. Don't call from from both ISR and non-ISR code or
    multiple ISR's!
    
    This function enables the Ethernet transmission.
    
    The packet construction from buffers stops when a descriptor with NULL buffer
    or 0 size is retrieved or the list ends.
 *****************************************************************************/

eEthRes EthTxSendPacket ( const sEthPktDcpt *pPkt );


/*******************************************************************************
  Function:
    eEthRes EthTxGetBufferStatus ( const void *pBuff, const sEthTxPktStat **pTxStat )

  Summary:
    Provides the status of a transmitted buffer/packet.

  Description:
    This function provides the status of a transmitted buffer/packet.  The 
    transmission of this packet has to have been completed otherwise the call
    will fail.

  Precondition:
    EthTxSendBuffer/EthTxSendPacket should have been called and the pBuff pointer must be valid.

  Parameters:
    pBuff       - Buffer part of the packet whose status is being queried.
    
    pTxStat     - Address to store the pointer to the packet status or NULL if
                  status not needed

  Returns:
    ETH_RES_OK              - the packet was transmitted OK,
    
    ETH_RES_PACKET_QUEUED   - the packet is not done yet
    
    ETH_RES_NO_PACKET       - no such packet exists

  Example:
    <code>
    ethRes = EthTxGetBufferStatus(pTxBuff, NULL);
    if ( ethRes != ETH_RES_OK )
    {
        // Handle packet not transmitted 
    }
    </code>

  Remarks:
    The returned pointer to the packet status is invalid after the 
    EthTxAcknowledgeBuffer/EthTxAcknowledgePacket is called.
    
    pBuff must be the pointer to the first buffer
    in the packet, if the packet spans multiple buffers. 
 *****************************************************************************/

eEthRes EthTxGetBufferStatus ( const void *pBuff, const sEthTxPktStat **pTxStat );

/*******************************************************************************
  Function:
    eEthRes EthTxGetPacketStatus(const sEthPktDcpt* pPkt, const sEthTxPktStat** pTxStat)

  Summary:
    Provides the status of a transmitted packet.

  Description:
    This function provides the status of a transmitted packet.  The 
    transmission of this packet has to have been completed otherwise the call
    will fail.

  Precondition:
    EthTxSendPacket should have been called and the pPkt pointer must be valid.

  Parameters:
    pPkt        - Packet whose status is being queried.
    
    pTxStat     - Address to store the pointer to the packet status or NULL if
                  status not needed

  Returns:
    ETH_RES_OK              - the packet was transmitted OK,
    
    ETH_RES_PACKET_QUEUED   - the packet is not done yet
    
    ETH_RES_NO_PACKET       - no such packet exists

  Example:
    <code>
    ethRes = EthTxGetPacketStatus(pTxPacket, NULL);
    if ( ethRes != ETH_RES_OK )
    {
        // Handle packet not transmitted 
    }
    </code>

  Remarks:
    The returned pointer to the packet status is invalid after the 
    EthTxAcknowledgeBuffer/EthTxAcknowledgePacket is called.
   
 *****************************************************************************/

eEthRes EthTxGetPacketStatus(const sEthPktDcpt* pPkt, const sEthTxPktStat** pTxStat);

// DOM-IGNORE-BEGIN
extern __inline__ eEthRes __attribute__((always_inline)) EthTxGetPacketStatus(const sEthPktDcpt* pPkt, const sEthTxPktStat** pTxStat)
{
    return  EthTxGetBufferStatus(pPkt?pPkt->pBuff:0, pTxStat);
}
// DOM-IGNORE-END


/*******************************************************************************
  Function:
    eEthRes EthTxAcknowledgeBuffer ( const void *pBuff, pEthBuffAck ackFnc, void* fParam )

  Summary:
    Acknowledges a transmitted buffer/packet

  Description:
    This function acknowledges a transmitted buffer/packet.  The transmission
    of this packet has to have been completed otherwise the call will fail.
    When pBuff==NULL, all currently transmitted packets will be acknowledged.
    The ackFnc, if !NULL, will be called for each buffer within the packet in
    turn.  

  Precondition:
    EthTxSendBuffer/EthTxSendPacket should have been called.

  Parameters:
    pBuff           - Buffer of the packet to be acknowledged or NULL.
    
    ackFnc          - Function to be called for the acknowledged buffers or 
                      NULL

    fParam          - Parameter to be used in the ackFnc callback                      

  Returns:
    ETH_RES_OK              - Success
    
    ETH_RES_PACKET_QUEUED   - The packet is scheduled for transmission/
                              There are packets scheduled to be transmitted
    
    ETH_RES_NO_PACKET       - No such packet exists in the transmit queue/
                              No packets scheduled for transmit

  Example:
    <code>
    ethRes=EthTxAcknowledgeBuffer(pTxBuff, myAckFnc, &myInstanceData);

    void myAckFnc(void* pBuff, int buffIx, void* param)
    {
        myInstanceType* pType=(myInstanceType*)param;
        // Handle each buffer acknowledgement
    }
    </code>

  Remarks:
    Any transmitted packet has to be acknowledged, otherwise the Ethernet library will
    run out of transmission descriptors.
    
    pBuff must be the pointer to the first buffer in the packet, if the packet
    spans multiple buffers.
    
    ackFnc is just a helper that allows the application to acknowledge the
    transmitted buffers without the need to maintain a list of buffers 
    scheduled for transmission (this list is maintained by the Ethernet library
    anyway).
    
    Useful especially when the transmission result is not really needed and
    the function is called with pBuff=0.
 *****************************************************************************/

eEthRes EthTxAcknowledgeBuffer ( const void *pBuff, pEthBuffAck ackFnc, void* fParam );


/*******************************************************************************
  Function:
    eEthRes EthTxAcknowledgePacket(const sEthPktDcpt* pPkt, pEthBuffAck ackFnc, void* fParam )

  Summary:
    Acknowledges a transmitted packet

  Description:
    This function acknowledges a transmitted packet.  The transmission
    of this packet has to have been completed otherwise the call will fail.
    When pPkt==NULL, all currently transmitted packets will be acknowledged.
    The ackFnc, if !NULL, will be called for each buffer within the packet in
    turn.  

  Precondition:
    EthTxSendPacket should have been called.

  Parameters:
    pPkt            - Packet to be acknowledged or NULL.
    
    ackFnc          - Function to be called to acknowledge each buffer
                      within the packet or NULL
                      
    fParam          - Parameter to be used in the ackFnc callback                      


  Returns:
    ETH_RES_OK              - Success
    
    ETH_RES_PACKET_QUEUED   - The packet is queued for transmission/
                              There are packets scheduled to be transmitted
    
    ETH_RES_NO_PACKET       - No such packet exist sin th etransmit queue/
                              No packets scheduled for transmit

  Example:
    <code>
    ethRes=EthTxAcknowledgePacket(pTxPkt, 0, 0);
    </code>

  Remarks:
    Any transmitted packet has to be acknowledged, otherwise the Ethernet library will
    run out of transmission descriptors.
    
    ackFnc is just a helper that allows the application to acknowledge the
    transmitted buffers without the need to maintain a list of buffers 
    scheduled for transmission (this list is maintained by the Ethernet library
    anyway).
    
    Useful especially when the transmission result is not really needed and
    the function is called with pPkt=0.
 *****************************************************************************/

eEthRes EthTxAcknowledgePacket(const sEthPktDcpt* pPkt, pEthBuffAck ackFnc, void* fParam );

// DOM-IGNORE-BEGIN
extern __inline__ eEthRes __attribute__((always_inline)) EthTxAcknowledgePacket(const sEthPktDcpt* pPkt, pEthBuffAck ackFnc, void* fParam )
{
    return  EthTxAcknowledgeBuffer(pPkt?pPkt->pBuff:0, ackFnc, fParam); 
}
// DOM-IGNORE-END


/*******************************************************************************
  Function:
    eEthRes EthRxGetBuffer ( void **ppBuff, const sEthRxPktStat **pRxStat )

  Summary:
     Returns a pointer to the data and the status of the next available 
     received packet.

  Description:
    This function returns a pointer to the data and the status of the next
    available received packet.  If there's no available fully received packet
    the call will fail (ETH_RES_PACKET_QUEUED/ETH_RES_NO_PACKET).  If the 
    received packet spans multiple buffers/descriptors (i.e. when the size of
    the buffer, EthRxSetBufferSize() is less than the packet size) 
    ETH_RES_RX_PKT_SPLIT_ERR will be returned.  However, if the ppBuff is NULL,
    then the caller can use the returned pRxStat to check the total size of the
    packet. Then using the size of the set buffers, the number of buffers used
    in the packet will result.

  Precondition:
    EthRxSetBufferSize, EthRxBuffersAppend should have been called.

  Parameters:
    ppBuff          - Address of a pointer to packet buffer data or NULL
    
    pRxStat         - Address to store the pointer to the packet status or 
                      NULL

  Returns:
    ETH_RES_OK                  - For success
    
    ETH_RES_PACKET_QUEUED       - The packet is in the reception queus/
                                  There are packets queued for receive but not
                                  completed yet
                                  
    ETH_RES_NO_PACKET           - No such packet is in the receiving queue/
                                  No packets available in the receiving queue
    
    ETH_RES_RX_PKT_SPLIT_ERR    - Packet spans accross multiple buffers 

  Example:
    <code>
    // Wait to receive a packet
    do
    {
        ethRes = EthRxGetBuffer(&pBuff, &pRxPktStat);
    } while ( ethRes == ETH_RES_PACKET_QUEUED );
    </code>

  Remarks:
    The returned status pointer is invalid once the EthRxAcknowledgeBuffer/EthRxAcknowledgePacket
    is called.
    
    Also the associated packet buffer if it was appended with a 
    ETH_BUFF_FLAG_RX_STICKY flag.
    
    The returned buffer, if existent, will be marked as reported only when the
    result returned is ETH_RES_OK.
    
    In this case a new call to the function will not return the same buffer.
    
    If the call failed for some reason (result!=ETH_RES_OK) the returned 
    buffer is not marked as reported.
    
    A new call to this function will return the same buffer.
 *****************************************************************************/

eEthRes EthRxGetBuffer ( void **ppBuff, const sEthRxPktStat **pRxStat );


/*******************************************************************************
  Function:
    eEthRes EthRxGetPacket ( sEthPktDcpt *pPkt, int *pnBuffs, 
                             const sEthRxPktStat **pRxStat )

  Summary:
    Provides the layout and the status of the next available received packet.

  Description:
    This function returns the layout and the status of the next available
    received packet.  If there's no available fully received packet the call
    will fail (ETH_RES_PACKET_QUEUED/ETH_RES_NO_PACKET).  The supplied pPkt has
    to be large enough to accommodate the packet layout in the case of packets
    split across multiple buffers/descriptors (i.e. when the size of the buffer,
    EthRxSetBufferSize() is less than the packet size) otherwise
    ETH_RES_RX_PKT_SPLIT_ERR will be returned.  However, if the pPkt is NULL, 
    then the caller can use the returned pRxStat to check the total size of the
    packet. Then using the size of the set buffers, the number of buffers in
    pPkt will result.  pnBuffs can be used for the same purpose. If pnBuffs is
    supplied, the numbers of buffers in the packet will be returned.

  Precondition:
    EthRxSetBufferSize, EthRxBuffersAppend should have been called.

  Parameters:
    pPkt            - Pointer to a packet descriptor: a list of buffer
                      descriptors large enough to receive the packet layout or
                      NULL.
                      
    pnBuffs         - Pointer to store the number of buffers in the packet or
                      NULL.
                      
    pRxStat         - Address to store the pointer to the packet status or 
                      NULL.

  Returns:
    ETH_RES_OK                  - For success.
    
    ETH_RES_PACKET_QUEUED       - The packet is queued for reception/
                                  There are packets queued for receive but not
                                  completed yet.
                                  
    ETH_RES_NO_PACKET           - No such packet in the receiving queue/
                                  No packets available in the receiving queue.
    
    ETH_RES_RX_PKT_SPLIT_ERR    - Packet descriptor not large enough to store
                                  the whole packet.

  Example:
    <code>
    // Wait to receive a packet
    do
    {
        ethRes = EthRxGetPacket(&rxPktDcpt, &buffsPerRxPkt, &pRxPktStat);
        
    } while ( ethRes== ETH_RES_PACKET_QUEUED );
    </code>

  Remarks:
    The packet list, when supplied, is terminated with a NULL buffer
    
    The returned status pointer is invalid after the EthRxAcknowledgePacket() is
    called.  Also any buffers that were appended with a ETH_BUFF_FLAG_RX_STICKY
    flag associated to the packet buffers. 
    
    The returned packet, if existent, will be marked as reported only when the
    result returned is ETH_RES_OK.  In this case a new call to the function
    will not return the same packet.
    
    If the call failed for some reason (result!=ETH_RES_OK) the returned
    packet is not marked as reported.
    
    A new call to this function will return the same packet.
 *****************************************************************************/

eEthRes EthRxGetPacket ( sEthPktDcpt *pPkt, int *pnBuffs, const sEthRxPktStat **pRxStat );


/*******************************************************************************
  Function:
    eEthRes EthRxAcknowledgeBuffer ( const void *pBuff, pEthBuffAck ackFnc, void* fParam )

  Summary:
    Acknowledges a received buffer/packet.

  Description:
    This function acknowledges a received buffer/packet.  The supplied packet
    has to have been previously received otherwise the call will fail.
    When pBuff==NULL, all currently received packets will be acknowledged.
    The ackFnc, if !NULL, will be called for each buffer within the packet in turn.  

  Precondition:
    EthRxSetBufferSize, EthRxBuffersAppend, EthRxGetPacket should have been
    called.

  Parameters:
    pBuff       - Buffer/packet to be acknowledged or NULL
    
    ackFnc      - Function to be called for the acknowledged buffers or NULL

    fParam      - Parameter to be used in the ackFnc callback                      

  Returns:
    ETH_RES_OK              - Success
    
    ETH_RES_PACKET_QUEUED   - The packet is in the receiving queue/
                              There are packets in the receiving queue
    
    ETH_RES_NO_PACKET       - No such packet in the receiving queue/
                              No packets available in the receiving queue

  Example:
    <code>
    ethRes = EthRxAcknowledgeBuffer(pRxBuff, myAckFnc, &myInstanceData);
    if ( ethRes != ETH_RES_OK )
    {
        // Handle buffer not acknowledged 
    }
    
    void myAckFnc(void* pBuff, int buffIx, void* param)
    {
        myInstanceType* pType=(myInstanceType*)param;
        // Handle each buffer acknowledgement
    }
    </code>

  Remarks:
    Any received packet has to be acknowledged, otherwise the Ethernet library will run
    out of descriptors.
    
    pBuff must be the pointer to the first buffer in the packet, if the packet
    spans multiple buffers.
    
    ackFnc is just a helper that allows the application to call an acknowledge
    function for each received buffer in turn.
 *****************************************************************************/

eEthRes EthRxAcknowledgeBuffer ( const void *pBuff, pEthBuffAck ackFnc, void* fParam );


/*******************************************************************************
  Function:
    eEthRes EthRxAcknowledgePacket ( const sEthPktDcpt* pPkt, pEthBuffAck ackFnc, void* fParam )

  Summary:
    Acknowledges a received packet.

  Description:
    This function acknowledges a received packet.  The supplied packet
    has to have been previously received otherwise the call will fail.
    When pPkt==NULL, all currently received packets will be acknowledged.
    The ackFnc, if !NULL, will be called for each buffer within the packet in turn.  

  Precondition:
    EthRxSetBufferSize, EthRxBuffersAppend, EthRxGetPacket should have been
    called.

  Parameters:
    pPkt        - Packet to be acknowledged or NULL
    
    ackFnc      - Function to be called for the each buffer within the packet or NULL

    fParam      - Parameter to be used in the ackFnc callback                      

  Returns:
    ETH_RES_OK              - Success
    
    ETH_RES_PACKET_QUEUED   - The packet is in the receiving queue/
                              There are packets in the receiving queue
    
    ETH_RES_NO_PACKET       - No such packet in the receiving queue/
                              No packets available in the receiving queue

  Example:
    <code>
    ethRes = EthRxAcknowledgePacket(pRxPkt, NULL, 0);
    if ( ethRes != ETH_RES_OK )
    {
        // Handle packet not acknowledged 
    }
    </code>

  Remarks:
    Any received packet has to be acknowledged, otherwise the Ethernet library will run
    out of descriptors.
        
    ackFnc is just a helper that allows the application to call an acknowledge
    function for each received buffer in turn.
 *****************************************************************************/

eEthRes EthRxAcknowledgePacket ( const sEthPktDcpt* pPkt, pEthBuffAck ackFnc, void* fParam );

// DOM-IGNORE-BEGIN
extern __inline__ eEthRes __attribute__((always_inline)) EthRxAcknowledgePacket(const sEthPktDcpt* pPkt, pEthBuffAck ackFnc, void* fParam )
{
    return EthRxAcknowledgeBuffer(pPkt?pPkt->pBuff:0, ackFnc, fParam);
}
// DOM-IGNORE-END


// Section: Status Functions

/*******************************************************************************
  Function:
    eEthStat EthStatusGet ( void )

  Summary:
    Returns the current controller status.

  Description:
    This function returns the current controller status.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    Current Ethernet controller status.

  Example:
    <code>
    ethStat = EthStatusGet();
    </code>

  Remarks:
    None.
 *****************************************************************************/
 
eEthStat EthStatusGet ( void );


// Section:  Flow Control Functions

// *****************************************************************************
/* Ethernet Flow Control

  Summary:
    Defines the possible Ethernet flow control types.

  Description:
    This enumeration defines the Ethernet flow control types.
*/

typedef enum
{
    // Auto flow control
    ETH_FC_AUTO = 0,

    // Software flow control
    ETH_FC_SOFTWARE

} eEthFc;


/*******************************************************************************
  Function:
    void EthFCSetPauseValue ( unsigned int pauseBytes )

  Summary:
    Sets the pause value to be used with manual or auto flow control.

  Description:
    This function sets the pause value to be used with manual or auto flow 
    control.  The pause time is calculated as being the time needed to transmit
    pauseBytes bytes.

  Precondition:
    EthInit should have been called.
    
    64 < pauseBytes < 4194304

  Parameters:
    pauseBytes      - The number of bytes to pause

  Returns:
    None.

  Example:
    <code>
    EthFCSetPauseValue(128);
    </code>

  Remarks:
    The pauseBytes value is relevant for full duplex mode only.
    
    In half duplex, back pressure is applied.
    
    Should be called only when receive is not enabled (i.e. before 
    EthRxBuffersAppend() is called, for example).
 *****************************************************************************/

void EthFCSetPauseValue ( unsigned int pauseBytes );


/*******************************************************************************
  Function:
    void EthFCEnable ( eEthFc fcType, int enable )

  Summary:
    Enables or disables selected flow control.

  Description:
    When enabling software flow control:
    *   In full duplex mode, this function immediately enables the manual flow
        control and sends a pause frame with the desired pause time.
    *   Further on, a pause frame is resent, every interval corresponding to
        pause time/2.
    *   In half duplex mode, back pressure is applied.
       
    When disabling software flow control:
    *   In full duplex, this function immediately disables the manual flow
        control and sends a pause frame with the pause time set to 0.
    *   In half duplex, the back pressure is removed.
    
    When enabling the auto flow control:
    *   As soon as the number of the unacknowledged received descriptors 
        ( BUFCNT = EthDescriptorsGetRxUnack() ) becomes >= fullWM:
        *   In full duplex mode a pause frame is sent with the specified pause
            time (EthFCSetPauseValue).
        *   Further on, a pause frame is resent, every interval corresponding
            to pause time/2.
        *   In half duplex mode, back pressure is applied.
        *   As soon as the BUFCNT becomes = emptyWM:
            *   In full duplex mode a pause frame is sent with the pause
                value set to 0.
            *   In half duplex mode, the back pressure is removed.
            
    *   When disabling auto flow control:
        *   In full duplex, this function immediately disables the flow control
            and sends a pause frame with the pause time set to 0.
        *   In half duplex, the back pressure is removed.

  Precondition:
    EthInit, EthFCSetPauseValue should have been called.

  Parameters:
    fcType      - Type of the flow control desired: auto or software (manual)
    
    enable      - Boolean to enable/disable the flow control

  Returns:
    None.

  Example:
    <code>
    EthFCEnable(ETH_FC_AUTO, 1);
    </code>

  Remarks:
    BUFCNT is decremented by a call to EthRxAcknowledgePacket/EthRxAcknowledgeBuffer.
 *****************************************************************************/

void EthFCEnable ( eEthFc fcType, int enable );


/*******************************************************************************
  Function:
    void EthFCSetRxWMark ( int fullWM, int emptyWM )

  Summary:
    Sets the automatic flow control watermarks.

  Description:
    This function sets the values for the watermarks used in the automatic flow
    control.

  Precondition:
    EthInit, should have been called.
    
    0 <= emptyWM < fullWM < 256

  Parameters:
    fullWM          - The full watermark value
    
    emptyWM         - The empty watermark value

  Returns:
    None.

  Example:
    <code>
    EthFCSetRxWMark(4, 64);
    </code>

  Remarks:
    See the description of the automatic flow control in the EthFCEnable
    description.  To take into account the delays inherent to the traffic
    stop, the value for fullWM should be set in such a way that the automatic
    flow control kicks in when there's less than 3 frames (3*1536 bytes) 
    available in the receive descriptors.
 *****************************************************************************/

void EthFCSetRxWMark ( int fullWM, int emptyWM );


// Section: RX Filtering Functions


// *****************************************************************************
/* Ethernet Receive Filter Flags

  Summary:
    Defines the receive filter flags

  Description:
    This enumeration defines the receive filter flags.
    
  Remarks:
    Multiple values can be OR-ed together.
    
    The values in this enumeration are displayed in the order of priority
    that the receive filter state machine works, with the highest priority first.
    Once a filter accepts or rejects a packet, further filters are not tried.
    If a packet isn't rejected/accepted after all filters are tried, it will be rejected by
    default!
*/

typedef enum
{
    // Frames with wrong CRC are accepted
    ETH_FILT_CRC_ERR_ACCEPT
        /*DOM-IGNORE-BEGIN*/ = _ETHRXFC_CRCERREN_MASK /*DOM-IGNORE-END*/,

    // Runt frames accepted
    ETH_FILT_RUNT_ACCEPT
        /*DOM-IGNORE-BEGIN*/ = _ETHRXFC_RUNTERREN_MASK /*DOM-IGNORE-END*/,  

    // Frames with wrong CRC are rejected
    ETH_FILT_CRC_ERR_REJECT
        /*DOM-IGNORE-BEGIN*/ = _ETHRXFC_CRCOKEN_MASK /*DOM-IGNORE-END*/,

    // Runt frames rejected
    ETH_FILT_RUNT_REJECT
        /*DOM-IGNORE-BEGIN*/ = _ETHRXFC_RUNTEN_MASK /*DOM-IGNORE-END*/,

    // Me unicast accepted
    ETH_FILT_ME_UCAST_ACCEPT
        /*DOM-IGNORE-BEGIN*/ = _ETHRXFC_UCEN_MASK /*DOM-IGNORE-END*/,

    // Not me unicast accepted
    ETH_FILT_NOTME_UCAST_ACCEPT
        /*DOM-IGNORE-BEGIN*/ = _ETHRXFC_NOTMEEN_MASK /*DOM-IGNORE-END*/,

    // Multicast accepted
    ETH_FILT_MCAST_ACCEPT
        /*DOM-IGNORE-BEGIN*/ = _ETHRXFC_MCEN_MASK /*DOM-IGNORE-END*/,

    // Broadcast accepted
    ETH_FILT_BCAST_ACCEPT
        /*DOM-IGNORE-BEGIN*/ = _ETHRXFC_BCEN_MASK /*DOM-IGNORE-END*/,

    // Hash table matches destination address accepted
    ETH_FILT_HTBL_ACCEPT
        /*DOM-IGNORE-BEGIN*/ = _ETHRXFC_HTEN_MASK /*DOM-IGNORE-END*/,

    // Magic packet accepted
    ETH_FILT_MAGICP_ACCEPT
        /*DOM-IGNORE-BEGIN*/ = _ETHRXFC_MPEN_MASK /*DOM-IGNORE-END*/,


    // All Filters
    ETH_FILT_ALL_FILTERS     = ETH_FILT_CRC_ERR_ACCEPT  | ETH_FILT_RUNT_ACCEPT        | 
                               ETH_FILT_CRC_ERR_REJECT  | ETH_FILT_RUNT_REJECT        |
                               ETH_FILT_ME_UCAST_ACCEPT | ETH_FILT_NOTME_UCAST_ACCEPT |
                               ETH_FILT_MCAST_ACCEPT    | ETH_FILT_BCAST_ACCEPT       |
                               ETH_FILT_HTBL_ACCEPT     | ETH_FILT_MAGICP_ACCEPT

} eEthRxFilters;


// *****************************************************************************
/* Ethernet Pattern Match Modes

  Summary:
    Defines pattern match modes

  Description:
    This enumeration defines the Ethernet pattern match modes.
    
  Remarks:
    These are mutually exclusive modes, not flags.  However, 
    ETH_FILT_PMATCH_INVERT act as a flag and can be applied to any value.
*/

typedef enum
{
    // Simple Pattern Match accepted
    ETH_FILT_PMATCH_ACCEPT = 1,

    // Pattern Match AND destination==me
    ETH_FILT_PMATCH_ME_UCAST_ACCEPT,

    // Pattern Match AND destination!=me
    ETH_FILT_PMATCH_NOTME_UCAST_ACCEPT,

    // Pattern Match AND destination!=unicast
    ETH_FILT_PMATCH_MCAST_ACCEPT,

    // Pattern Match AND destination==unicast
    ETH_FILT_PMATCH_NOT_MCAST_ACCEPT,

    // Pattern Match AND destination==broadcast
    ETH_FILT_PMATCH_BCAST_ACCEPT,

    // Pattern Match AND destination!=broadcast
    ETH_FILT_PMATCH_NOT_BCAST_ACCEPT,

    // Pattern Match AND hash table filter match (irrespective of the 
    // ETH_FILT_HTBL_ACCEPT setting)
    ETH_FILT_PMATCH_HTBL_ACCEPT,

    // Pattern Match AND packet ==magic packet
    ETH_FILT_PMATCH_MAGICP_ACCEPT,

    // If set, the pattern must NOT match for a successful Pattern Match to 
    // occur!
    ETH_FILT_PMATCH_INVERT = 0x80000000

} eEthPMatchMode;


/*******************************************************************************
  Function:
    void EthRxFiltersSet ( eEthRxFilters rxFilters )

  Summary:
    Sets the acceptance/rejection filters for the Ethernet receive.

  Description:
    This function sets the acceptance/rejection filters for the Ethernet receive 
    mechanism.  Multiple filters can be OR-ed together.  All filter specified
    in rxFilters will be set.          

  Precondition:
    This function should not be called when Ethernet RX operation is enabled.

  Parameters:
    rxFilters       - RX filters that are to be set

  Returns:
    None.

  Example:
    <code>
    EthRxFiltersSet(ETH_FILT_CRC_ERR_REJECT | ETH_FILT_RUNT_REJECT  |
                    ETH_FILT_ME_UCAST_ACCEPT| ETH_FILT_MCAST_ACCEPT |
                    ETH_FILT_BCAST_ACCEPT   | ETH_FILT_NOTME_UCAST_ACCEPT);
    </code>

  Remarks:  
    All filters except Pattern Match can be set. Use EthRxFiltersPMSet().
    
    Before enabling the Hash Table filter, the hash table values should be set
    using EthRxFiltersHTSet().

    See the definition of the eEthRxFilters for the priority of the
    RX filters.
 *****************************************************************************/

void EthRxFiltersSet ( eEthRxFilters rxFilters );


/*******************************************************************************
  Function:
    void EthRxFiltersClr ( eEthRxFilters rxFilters )

  Summary:
    Clears the acceptance/rejection filters for the Ethernet receive.

  Description:
    This function clears the acceptance/rejection filters for the Ethernet receive
    mechanism.  Multiple filters can be OR-ed together.  All filters specified
    in rxFilters will be cleared.          

  Precondition:
    This function should not be called when Ethernet RX operation is enabled.

  Parameters:
    rxFilters       - RX filters that are to be cleared

  Returns:
    None.

  Example:
    <code>
    EthRxFiltersClr(ETH_FILT_ALL_FILTERS);
    </code>

  Remarks:
    All filters except Pattern Match can be cleared. Use EthRxFiltersPMClr();
 *****************************************************************************/

void EthRxFiltersClr ( eEthRxFilters rxFilters );


/*******************************************************************************
  Function:
    void EthRxFiltersWrite ( eEthRxFilters rxFilters )

  Summary:
    Updates the acceptance/rejection filters for the Ethernet receive.

  Description:
    This function updates the acceptance/rejection filters for the Ethernet receive 
    mechanism to the required value.

  Precondition:
    This function should not be called when Ethernet RX operation is enabled.

  Parameters:
    rxFilters       - RX filters that are to be written

  Returns:
    None.

  Example:
    <code>
    EthRxFiltersWrite(ETH_FILT_ALL_FILTERS);
    </code>

  Remarks:
    All filters except Pattern Match can be updated.
    
    The Pattern Match filter will be disabled by this call.  Use 
    EthRxFiltersPMSet();
    
    Before enabling the Hash Table filter, the hash table values should be set
    using EthRxFiltersHTSet().

    See the definition of the eEthRxFilters for the priority of the
    RX filters.    
 *****************************************************************************/

void EthRxFiltersWrite ( eEthRxFilters rxFilters );


/*******************************************************************************
  Function:
    void  EthRxFiltersHTSet ( unsigned long long htable )

  Summary:
    Sets the hash table for the hash table RX filter.

  Description:
    This function sets the hash table for the hash table RX filter.       

  Precondition:
    This function should not be called when Ethernet RX operation is enabled and the
    hash filter is active.

  Parameters:
    htable      - The hash table itself

  Returns:
    None.

  Example:
    <code>
    </code>

  Remarks:
    Properly set the hash table with this function before enabling the Hash 
    Table filter.
 *****************************************************************************/

void  EthRxFiltersHTSet ( unsigned long long htable );


/*******************************************************************************
  Function:
    void EthRxFiltersPMSet ( eEthPMatchMode mode, unsigned long long matchMask, 
                             unsigned int matchOffs, unsigned int matchChecksum )

  Summary:
    Enables the Pattern Match filter with the specified settings.

  Description:
    This function enables the Pattern Match filter with the specified settings 
    for the offset and window mask. The calculated checksum of the 64 bytes 
    window starting at matchOffs and using the matchMask bytes in the window, 
    is compared against matchChecksum.  If ETH_FILT_PMATCH_INVERT is used in 
    the mode, then the calculated checksum must not match the passed 
    matchChecksum in order for the Pattern Match to succeed.         

  Precondition:
    This function should not be called when Ethernet RX operation is enabled.

  Parameters:
    mode            - The required Pattern Match Mode
    
    matchMask       - Mask in the 64 byte window
    
    matchOffs       - The offset applied to the incoming data (0 to 8128)
    
    matchChecksum   - The 16 bit checksum used for comparison

  Returns:

  Example:
    <code>
    EthRxFiltersPMSet(ETH_FILT_PMATCH_ACCEPT, MY_PATTERN, 0, MY_CHECKSUM);
    </code>

  Remarks:
    None.
 *****************************************************************************/

void EthRxFiltersPMSet ( eEthPMatchMode mode, unsigned long long matchMask, 
                         unsigned int matchOffs, unsigned int matchChecksum );


/*******************************************************************************
  Function:
    void EthRxFiltersPMClr ( void )

  Summary:
    Disables the Pattern Match receive filter.

  Description:
    This function disables the Pattern Match receive filter.        

  Precondition:
    This function should not be called when Ethernet RX operation is enabled.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    EthRxFiltersPMClr();
    </code>

  Remarks:
    None.
 *****************************************************************************/

void EthRxFiltersPMClr ( void );


// Section: Ethernet Event Functions

// *****************************************************************************
/* Ethernet Event Flags

  Summary:
    Ethernet event flags

  Description:
    This enumeration defines flags for the possible Ethernet events that can 
    cause interrupts.
*/

typedef enum
{
    // RX FIFO overflow
    ETH_EV_RXOVFLOW
        /*DOM-IGNORE-BEGIN*/ = _ETHIRQ_RXOVFLW_MASK /*DOM-IGNORE-END*/,

    // RX buffer not available (descriptor overrun)
    ETH_EV_RXBUFNA
        /*DOM-IGNORE-BEGIN*/ = _ETHIRQ_RXBUFNA_MASK /*DOM-IGNORE-END*/,

    // TX abort condition
    ETH_EV_TXABORT
        /*DOM-IGNORE-BEGIN*/ = _ETHIRQ_TXABORT_MASK /*DOM-IGNORE-END*/,

    // TX done
    ETH_EV_TXDONE
        /*DOM-IGNORE-BEGIN*/ = _ETHIRQ_TXDONE_MASK  /*DOM-IGNORE-END*/,

    // RX activity
    ETH_EV_RXACT
        /*DOM-IGNORE-BEGIN*/ = _ETHIRQ_RXACT_MASK   /*DOM-IGNORE-END*/,

    // RX packet pending
    ETH_EV_PKTPEND
        /*DOM-IGNORE-BEGIN*/ = _ETHIRQ_PKTPEND_MASK /*DOM-IGNORE-END*/,

    // RX packet successfully received
    ETH_EV_RXDONE
        /*DOM-IGNORE-BEGIN*/ = _ETHIRQ_RXDONE_MASK  /*DOM-IGNORE-END*/,

    // Full watermark reached
    ETH_EV_FWMARK
        /*DOM-IGNORE-BEGIN*/ = _ETHIRQ_FWMARK_MASK  /*DOM-IGNORE-END*/,

    // Empty watermark reached
    ETH_EV_EWMARK
        /*DOM-IGNORE-BEGIN*/ = _ETHIRQ_EWMARK_MASK  /*DOM-IGNORE-END*/,

    // RX bus error
    ETH_EV_RXBUSERR
        /*DOM-IGNORE-BEGIN*/ = _ETHIRQ_RXBUSE_MASK  /*DOM-IGNORE-END*/,

    // TX bus error
    ETH_EV_TXBUSERR
        /*DOM-IGNORE-BEGIN*/ = _ETHIRQ_TXBUSE_MASK  /*DOM-IGNORE-END*/,

    // All events
    ETH_EV_ALL     = (ETH_EV_RXOVFLOW | ETH_EV_RXBUFNA | ETH_EV_TXABORT | 
                      ETH_EV_TXDONE   | ETH_EV_RXACT   | ETH_EV_PKTPEND |
                      ETH_EV_RXDONE   | ETH_EV_FWMARK  | ETH_EV_EWMARK  | 
                      ETH_EV_RXBUSERR | ETH_EV_TXBUSERR)
} eEthEvents;


/*******************************************************************************
  Function:
    void EthEventsEnableSet ( eEthEvents eEvents )

  Summary:
    Enables the events that will generate interrupts for the Ethernet controller.

  Description:
    The function enables the events that will generate interrupts for the Ethernet 
    controller.  Multiple events can be OR-ed together.  Any event that is set
    in the eEvents will be enabled , the other events won't be touched.

  Precondition:
    None.

  Parameters:
    eEvents         - Events with the significance described in the eEthEvents
                      definition.

  Returns:
    None.

  Example:
    <code>
    EthEventsEnableSet(ETH_EV_ALL);
    </code>

  Remarks:
    None.
 *****************************************************************************/

void EthEventsEnableSet ( eEthEvents eEvents );


/*******************************************************************************
  Function:
    void EthEventsEnableClr ( eEthEvents eEvents )

  Summary:
    Disables the events that will generate interrupts.

  Description:
    The function disables the events that will generate interrupts for the Ethernet 
    controller.  Multiple events can be OR-ed together.  Any event that is set 
    in the eEvents will be disabled , the other events won't be touched.

  Precondition:
    None.

  Parameters:
    eEvents         - Events with the significance described in the eEthEvents
                      definition.

  Returns:
    None.

  Example:
    <code>
    EthEventsEnableClr(ETH_EV_ALL);
    </code>

  Remarks:
    None.
 *****************************************************************************/
 
void EthEventsEnableClr ( eEthEvents eEvents );


/*******************************************************************************
  Function:
    void EthEventsEnableWrite ( eEthEvents eEvents )

  Summary:
    Enables the events that will generate interrupts for the Ethernet controller.

  Description:
    This function enables the events that will generate interrupts for the Ethernet
    controller.  The enabled events are forced to the eEvents value.

  Precondition:
    None.

  Parameters:
    eEvents     - Events with the significance described in the eEthEvents 
                  definition.

  Returns:
    None.

  Example:
    <code>
    EthEventsEnableWrite( ETH_EV_RXOVFLOW | ETH_EV_RXBUFNA | ETH_EV_TXABORT  |
                          ETH_EV_RXACT    | ETH_EV_PKTPEND | ETH_EV_RXBUSERR | 
                          ETH_EV_TXBUSERR );
    </code>

  Remarks:
    None.
 *****************************************************************************/

void EthEventsEnableWrite ( eEthEvents eEvents );


/*******************************************************************************
  Function:
    eEthEvents EthEventsEnableGet ( void )

  Summary:
    Returns the enabled events for the Ethernet controller.

  Description:
    This function returns the enabled events for the Ethernet controller.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    eEvents - events with the significance described in the eEthEvents 
    definition.

  Example:
    <code>
    ethEnabledEvents = EthEventsEnableGet();
    </code>

  Remarks:
    None.
 *****************************************************************************/
 
eEthEvents EthEventsEnableGet ( void );


/*******************************************************************************
  Function:
    void EthEventsClr ( eEthEvents eEvents )

  Summary:
    Clears the selected events for the Ethernet controller.

  Description:
    The function clears the selected events for the Ethernet controller.  Multiple
    events can be OR-ed together. Any event that is set in the eEvents will be
    cleared, the other events won't be touched.

  Precondition:
    None.

  Parameters:
    eEvents         - Events with the significance described in the eEthEvents 
                      definition.

  Returns:
    None.

  Example:
    <code>
    EthEventsClr(ETH_EV_TXDONE);
    </code>

  Remarks:
    The ETH_EV_FWMARK cannot be cleared directly. It is cleared indirectly by
    EthRxAcknowledgePacket/EthRxAcknowledgeBuffer.
    
    The ETH_EV_EWMARK cannot be cleared directly. It is cleared by hardware when 
    receiving a new packet.
    
    The ETH_EV_PKTPEND cannot be cleared directly. It is cleared indirectly by 
    EthRxAcknowledgePacket/EthRxAcknowledgeBuffer.
 *****************************************************************************/

void EthEventsClr ( eEthEvents eEvents );

// DOM-IGNORE-BEGIN
extern __inline__ void __attribute__((always_inline)) EthEventsClr(eEthEvents eEvents)
{
    ETHIRQCLR=eEvents;  
}
// DOM-IGNORE-END


/*******************************************************************************
  Function:
    eEthEvents EthEventsGet ( void )

  Summary:
    Returns the active events for the Ethernet controller.

  Description:
    This function returns the active events for the Ethernet controller.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    Events with the significance described in the eEthEvents definition.

  Example:
    <code>
    ethEvents = EthEventsGet();
    </code>

  Remarks:
    None.
 *****************************************************************************/

eEthEvents EthEventsGet ( void );

// DOM-IGNORE-BEGIN
extern __inline__ eEthEvents __attribute__((always_inline)) EthEventsGet(void)
{
    return (eEthEvents)ETHIRQ;
}
// DOM-IGNORE-END


// Section: Ethernet Statistics Functions

/*******************************************************************************
  Function:
    int EthStatRxOvflCnt ( void )

  Summary:
    Returns the current number of dropped receive frames.

  Description:
    This function returns the current number of dropped receive frames by the 
    Ethernet controller.  These are frames accepted by the RX filter but dropped due
    to internal receive error (RX FIFO overrun).

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    The number of dropped receive frames

  Example:
    <code>
    droppedFrames = EthStatRxOvflCnt();
    </code>

  Remarks:
    This statistics register is cleared by the read operation.
    
    An RX overflow event is signalled by the ETH_EV_RXOVFLOW event (see 
    eEthEvents definition).
 *****************************************************************************/

int EthStatRxOvflCnt ( void );

// DOM-IGNORE-BEGIN
#define EthStatRxOvflCnt()  (ETHRXOVFLOW)
// DOM-IGNORE-END


/*******************************************************************************
  Function:
    int EthStatRxOkCnt ( void )

  Summary:
    Returns the current number of successfully received frames.

  Description:
    This function returns the current number of successfully received frames by 
    the Ethernet controller.  These are frames accepted by the RX filter (some of 
    them may still be dropped because of an RX FIFO overrun).

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    The number of frames received OK 

  Example:
    <code>
    numReceived = EthStatRxOkCnt();
    </code>

  Remarks:
    This statistics register is cleared by the read operation.
    
    Frames with FCS or alignment errors will not increment this count.
 *****************************************************************************/

int EthStatRxOkCnt ( void );

// DOM-IGNORE-BEGIN
#define     EthStatRxOkCnt()    (ETHFRMRXOK)
// DOM-IGNORE-END


/*******************************************************************************
  Function:
    int EthStatRxFcsErrCnt ( void )

  Summary:
    Returns the current number of frames with FCS received errors.

  Description:
    The function returns the current number of frames with FCS errors received 
    by the Ethernet controller.  These are received frames that have an integral 
    number of bytes.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    The number of received frames having FCS errors 

  Example:
    <code>
    numRxFcsErrors = EthStatRxFcsErrCnt();
    </code>

  Remarks:
    This statistics register is cleared by the read operation.
    
    Frames with alignment error do not increment this count.
 *****************************************************************************/

int EthStatRxFcsErrCnt ( void );

// DOM-IGNORE-BEGIN
#define     EthStatRxFcsErrCnt()    (ETHFCSERR)
// DOM-IGNORE-END


/*******************************************************************************
  Function:
    int EthStatRxAlgnErrCnt ( void )

  Summary:
    Returns the current number of frames with alignment received errors

  Description:
    The function returns the current number of frames with alignment errors 
    received by the Ethernet controller.  These are received frames that have FCS 
    error and they do not contain an integral number of bytes (aka 
    dribble-nibble).

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    The number of received frames having alignment errors 

  Example:
    <code>
    numAlignErrors = EthStatRxAlgnErrCnt();
    </code>

  Remarks:
    This statistics register is cleared by the read operation.
 *****************************************************************************/

int EthStatRxAlgnErrCnt ( void );

// DOM-IGNORE-BEGIN
#define     EthStatRxAlgnErrCnt()   (ETHALGNERR)
// DOM-IGNORE-END


/*******************************************************************************
  Function:
    int EthStatTxOkCnt ( void )

  Summary:
    Returns the current number of frames transmitted successfully

  Description:
    The function returns the current number of frames transmitted successfully by
    the Ethernet controller.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    The number of frames transmitted OK 

  Example:
    <code>
    numFramesTx = EthStatTxOkCnt();
    </code>

  Remarks:
    This statistics register is cleared by the read operation.
 *****************************************************************************/

int EthStatTxOkCnt ( void );

// DOM-IGNORE-BEGIN
#define     EthStatTxOkCnt()    (ETHFRMTXOK)
// DOM-IGNORE-END


/*******************************************************************************
  Function:
    int EthStatTxSColCnt ( void )

  Summary:
    Returns the current number of successfully transmitted frames on the second try

  Description:
    This function returns the current number of transmitted frames that had
    a collision but were successfully transmitted by the Ethernet controller
    on the second try.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    The number of single collision frames

  Example:
    <code>
    numSingleCollisions = EthStatTxSColCnt();
    </code>

  Remarks:
    This statistics register is cleared by the read operation.
 *****************************************************************************/

int EthStatTxSColCnt ( void );

// DOM-IGNORE-BEGIN
#define     EthStatTxSColCnt()  (ETHSCOLFRM)
// DOM-IGNORE-END


/*******************************************************************************
  Function:
    int EthStatTxMColCnt( void )

  Summary:
    Returns the number of current frames transmitted after more than one 
    collision occurred.

  Description:
    The function returns the current number of frames successfully transmitted 
    by the Ethernet controller after there was more than one collision.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    The number of multiple collision frames

  Example:
    <code>
    numMultiCollisions = EthStatTxMColCnt();
    </code>

  Remarks:
    This statistics register is cleared by the read operation.
 *****************************************************************************/

int EthStatTxMColCnt( void );

// DOM-IGNORE-BEGIN
#define     EthStatTxMColCnt()  (ETHMCOLFRM)
// DOM-IGNORE-END


// Section: MIIM Access Functions

/*******************************************************************************
  Function:
    void EthMIIMConfig ( unsigned int hostClock, unsigned int miimClock )

  Summary:
    Configures and initializes the MIIM interface clock

  Description:
    This function initializes and configures the MIIM interface for access of a PHY.

  Precondition:
    None.

  Parameters:
    hostClock       - The value of the host clock, Hz

    miimClock       - The maximum clock frequency that the PHY can use for the
                      MIIM transactions, Hz 

  Returns:
    None.

  Example:
    <code>
    EthMIIMConfig(MY_HOST_CLOCK_HZ, MY_MIIM_CLOCK_HZ);
    </code>

  Remarks:
    Any previous MIIM operation will be aborted!
 *****************************************************************************/

void EthMIIMConfig ( unsigned int hostClock, unsigned int miimClock );


/*******************************************************************************
  Function:
    void EthMIIMReadStart ( unsigned int rIx, unsigned int phyAdd )

  Summary:
    Initiates a read operation from a PHY register

  Description:
    This function initiates a read operation from a PHY register using the MIIM
    interface.  It returns immediately without waiting for the transactions to 
    be performed.

  Precondition:
    EthMIIMConfig() called
    
    rIx a valid PHY register, 0-31
    
    phyAdd a valid PHY address, 0-31

  Parameters:
    rIx         - PHY register to be accessed
    
    phyAdd      - PHY address

  Returns:
    None.

  Example:
    <code>
    while(EthMIIMBusy());   // wait device not busy
    EthMIIMReadStart(12, 1);
    </code>

  Remarks:
    It assumes that no scan operation is in progress!
    
    Before initiating the read operation it waits for the MIIM interface not busy.
    Call EthMIIMBusy() before if no polling needed!
 *****************************************************************************/

void EthMIIMReadStart ( unsigned int rIx, unsigned int phyAdd );


/*******************************************************************************
  Function:
    unsigned short EthMIIMReadResult ( void )

  Summary:
    Returns the result of a previously started read operation

  Description:
    This function returns the result of a previously started read operation 
    (using EthMIIMReadStart()).

  Precondition:
    EthMIIMConfig() called
    
    EthMIIMReadStart() called

  Parameters:
    None.

  Returns:
    PHY register value 

  Example:
    <code>
    while(EthMIIMBusy());   // wait read operation complete
    regValue = EthMIIMReadResult();
    </code>

  Remarks:
    It assumes that no scan operation is in progress!
    
    It waits for the read operation to be complete.
    Call EthMIIMBusy() before if no polling needed!
 *****************************************************************************/

unsigned short EthMIIMReadResult ( void );


/*******************************************************************************
  Function:
    void EthMIIMWriteStart ( unsigned int rIx, unsigned int phyAdd, 
                           unsigned short wData )

  Summary:
    Performs a write operation to a PHY register

  Description:
    This function performs a write operation to a PHY register using the MIIM 
    interface.  It doesn't wait for the write to take effect.

  Precondition:
    EthMIIMConfig() called
    
    rIx a valid PHY register, 0-31
    
    phyAdd a valid PHY address, 0-31

  Parameters:
    rIx         - PHY register to be accessed
    
    phyAdd      - PHY address
    
    wData       - Data to be written

  Returns:
    None.

  Example:
    <code>
    EthMIIMWriteStart(12, 1, 0x001F);
    </code>

  Remarks:
    It assumes that no scan operation is in progress!

    Before initiating the write operation it waits for the MIIM interface not busy.
    Call EthMIIMBusy() before if no polling needed!

    After write started call EthMIIMBusy() to check if the operation
    has been completed. 
 *****************************************************************************/

void EthMIIMWriteStart ( unsigned int rIx, unsigned int phyAdd, unsigned short wData );

    

/*******************************************************************************
  Function:
    void EthMIIMScanStart ( unsigned int rIx, unsigned int phyAdd )

  Summary:
    Initiates a scan operation to a PHY register

  Description:
    This function initiates a scan operation to a PHY register using the MIIM 
    interface.

  Precondition:
    EthMIIMConfig() called
    
    rIx a valid PHY register, 0-31
    
    phyAdd a valid PHY address, 0-31

  Parameters:
    rIx         - PHY register to be accessed
    
    phyAdd      - PHY address

  Returns:
    None.

  Example:
    <code>
    while(EthMIIMBusy());   // wait device not busy
    EthMIIMScanStart(12, 1);
    </code>

  Remarks:
    It assumes that no scan operation is in progress!

    Before initiating the scan operation it waits for the MIIM interface not busy.
    Call EthMIIMBusy() before if no polling needed!
 *****************************************************************************/

void EthMIIMScanStart ( unsigned int rIx, unsigned int phyAdd );


/*******************************************************************************
  Function:
    unsigned short  EthMIIMScanResult ( void )

  Summary:
    Reads the result of a previously initiated scan operation

  Description:
    This function reads the result of a previously initiated scan operation 
    from a PHY register using the MIIM interface.

  Precondition:
    EthMIIMConfig() called
    
    EthMIIMScanStart() called

  Parameters:
    None.

  Returns:
    Result of previous scan operation

  Example:
    <code>
    if ( EthMIIMScanValid() )
    {
        value = EthMIIMScanResult();
    }
    </code>

  Remarks:
    It assumes that a scan operation is in progress!

    Before returning it waits for the scan result to be valid.
    Call EthMIIMScanValid() before if no polling needed!    
 *****************************************************************************/

unsigned short EthMIIMScanResult ( void );


/*******************************************************************************
  Function:
    void EthMIIMScanStop ( void )

  Summary:
    Stops a previously initiated scan operation

  Description:
    This function stops a previously initiated scan operation from a PHY 
    register using the MIIM interface.  It doesn't wait for the scan operation 
    to finish.

  Precondition:
    EthMIIMConfig() called
    
    EthMIIMScanStart() called

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    EthMIIMScanStop();
    while(EthMIIMBusy());   // wait scan stop is in effect
    </code>

  Remarks:
    It assumes that a scan operation is in progress!

    After call use EthMIIMBusy() to check if the scan
    has been effectively stopped. 
 *****************************************************************************/

void EthMIIMScanStop ( void );

// DOM-IGNORE-BEGIN
extern __inline__ void __attribute__((always_inline)) EthMIIMScanStop(void)
{
	EMACxMCMD=0;			// cancel scan
}
// DOM-IGNORE-END


/*******************************************************************************
  Function:
    int EthMIIMScanValid ( void )

  Summary:
    Returns the current state of the MIIM scan operation

  Description:
    This function returns the current validity state of the MIIM scan operation.

  Precondition:
    EthMIIMConfig() called

    EthMIIMScanStart() called

  Parameters:
    None.

  Returns:
    TRUE        - If the result of a MIIM scan result is valid 
    
    FALSE       - Otherwise

  Example:
    <code>
    if ( !EthMIIMScanValid()) )
    {
        // Handle invalid scan
    }
    </code>

  Remarks:
    None.
 *****************************************************************************/

int EthMIIMScanValid ( void );

// DOM-IGNORE-BEGIN
extern __inline__ int __attribute__((always_inline)) EthMIIMScanValid(void)
{
    return EMACxMINDbits.NOTVALID==0;
}
// DOM-IGNORE-END


/*******************************************************************************
  Function:
    int EthMIIMBusy ( void )

  Summary:
    Returns the current busy state of the MIIM interface

  Description:
    This function returns the current busy state of the MIIM interface.

  Precondition:
    EthMIIMConfig() called

  Parameters:
    None.

  Returns:
    TRUE        - If the MIIM is busy with some transaction
    
    FALSE       - Otherwise

  Example:
    <code>
    do
    {
        ; // Nothing
        
    } while ( EthMIIMBusy() );
    </code>

  Remarks:
    Use EthMIIMBusy() to check:
        - if a read/write/scan operation can be started
        - if a read/write operation has been completed
        - if a scan operation has been stopped
 *****************************************************************************/

int EthMIIMBusy ( void );

// DOM-IGNORE-BEGIN
extern __inline__ int __attribute__((always_inline)) EthMIIMBusy(void)
{
    return EMACxMINDbits.MIIMBUSY!=0;
}
// DOM-IGNORE-END


// Section:  Ethernet Controller Low Level Access Functions

// *****************************************************************************
/* Ethernet Configuration Flags

  Summary:
    Defines the Ethernet configuration flags

  Description:
    This enumeration defines the Ethernet configuration flags.
*/

typedef enum
{
    // Configure manual flow control
    ETH_CONFIG_MANFC
        /*DOM-IGNORE-BEGIN*/ = _ETHCON1_MANFC_MASK   /*DOM-IGNORE-END*/,

    // Configure auto flow control
    ETH_CONFIG_AUTOFC
        /*DOM-IGNORE-BEGIN*/ = _ETHCON1_AUTOFC_MASK  /*DOM-IGNORE-END*/,

    // RX enabled
    ETH_CONFIG_RXEN
        /*DOM-IGNORE-BEGIN*/ = _ETHCON1_RXEN_MASK    /*DOM-IGNORE-END*/,

    // Activate the TX logic and send packets
    ETH_CONFIG_TXRTS
        /*DOM-IGNORE-BEGIN*/ = _ETHCON1_TXRTS_MASK   /*DOM-IGNORE-END*/,

    // Stop in idle
    ETH_CONFIG_SIDL
        /*DOM-IGNORE-BEGIN*/ = _ETHCON1_SIDL_MASK    /*DOM-IGNORE-END*/,

    // Turn on/off the Ethernet controller
    ETH_CONFIG_ON
        /*DOM-IGNORE-BEGIN*/ = _ETHCON1_ON_MASK      /*DOM-IGNORE-END*/

} eEthConfigFlags;



/*******************************************************************************
  Function:
    void EthEnable ( int enable )

  Summary:
    Gives access to low level Ethernet controller configuration.

  Description:
    The function gives access to low level Ethernet controller configuration.  It can
    turn on/off the controller.

  Precondition:
    None.

  Parameters:
    enable      - Boolean to enable/disable the Ethernet Controller.

  Returns:
    None.

  Example:
    <code>
    EthEnable(FALSE);
    </code>

  Remarks:
    The Ethernet controller should be disabled before being configured.
 *****************************************************************************/

void EthEnable ( int enable );


/*******************************************************************************
  Function:
    void EthConfig ( eEthConfigFlags cFlags )

  Summary:
    Configures the Ethernet Controller.

  Description:
    The function gives access to low level Ethernet controller configuration.  It 
    configures the Ethernet Controller.

  Precondition:
    The Ethernet controller must be disabled.

  Parameters:
    cFlags      - Configuration flags

  Returns:
    None.

  Example:
    <code>
    EthEnable(FALSE);
    EthConfig(ETH_CONFIG_MANFC|ETH_CONFIG_RXEN|ETH_CONFIG_SIDL);
    EthEnable(TRUE); 
    </code>

  Remarks:
    The Ethernet controller should be configured when disabled.
 *****************************************************************************/

void EthConfig ( eEthConfigFlags cFlags );
 

/*******************************************************************************
  Function:
    void EthConfigSetFlags ( eEthConfigFlags cFlags )

  Summary:
    Sets Ethernet controller configuration flags.

  Description:
    The function gives access to low level Ethernet controller configuration.  Any 
    flag set in the cFlags will be set, the other flags won't be touched. 

  Precondition:
    The Ethernet controller must be disabled.

  Parameters:
    cFlags      - Configuration flags to be set

  Returns:
    None.

  Example:
    <code>
    EthEnable(FALSE);
    EthConfigSetFlags(ETH_CONFIG_MANFC|ETH_CONFIG_RXEN|ETH_CONFIG_SIDL);
    EthEnable(TRUE); 
    </code>

  Remarks:
    The Ethernet controller should be configured when disabled.
 *****************************************************************************/

void EthConfigSetFlags ( eEthConfigFlags cFlags );


/*******************************************************************************
  Function:
    void EthConfigClrFlags ( eEthConfigFlags cFlags )

  Summary:
    Clears Ethernet controller configuration flags.

  Description:
    The function gives access to low level Ethernet controller configuration.  Any 
    flag set in the cFlags will be cleared, the other flags won't be touched. 

  Precondition:
    The Ethernet controller must be disabled.

  Parameters:
    cFlags      - Configuration flags to be cleared

  Returns:
    None.

  Example:
    <code>
    EthEnable(FALSE);
    EthConfigClrFlags(ETH_CONFIG_MANFC|ETH_CONFIG_RXEN|ETH_CONFIG_SIDL);
    EthEnable(TRUE); 
    </code>

  Remarks:
    The Ethernet controller should be configured when disabled.
 *****************************************************************************/

void EthConfigClrFlags ( eEthConfigFlags cFlags );


/*******************************************************************************
  Function:
    void EthConfigTxStAddress ( void *address )

  Summary:
    Sets the address of the TX descriptors.

  Description:
    The function gives access to low level Ethernet controller configuration.  It 
    sets the address of the TX descriptors in memory.

  Precondition:
    There must not be a transmit or DMA engine operation in progress.

  Parameters:
    address     - Starting physical address of the first TX descriptor

  Returns:
    None.

  Example:
    <code>
    EthConfigTxStAddress(VirtToPhys(myTxDcpt));
    </code>

  Remarks:
    The address must be 4-byte aligned.
    
    The address must be a physical address.
    
    The address must not be written while any transmit or DMA engine operations are 
    in progress.
 *****************************************************************************/

void EthConfigTxStAddress ( void *address );


/*******************************************************************************
  Function:
    void EthConfigRxStAddress ( void *address )

  Summary:
    Sets the address of the RX descriptors in memory.

  Description:
    The function gives access to low level Ethernet controller configuration.  It 
    sets the address of the RX descriptors in memory.

  Precondition:
    There must not be a receive or DMA engine operation in progress.

  Parameters:
    address     - Starting physical address of the first RX descriptor

  Returns:
    None.

  Example:
    <code>
    EthConfigRxStAddress(VirtToPhys(myRxDcpt));
    </code>

  Remarks:
    The address must be 4-byte aligned.
    
    The address must be a physical address.
    
    The address must not be written while any receive or DMA engine operations are in 
    progress.
 *****************************************************************************/

void EthConfigRxStAddress ( void *address );


/*******************************************************************************
  Function:
    void EthAckRxDcpt ( void )

  Summary:
    Acknowledges a RX descriptor.

  Description:
    The function gives access to low level Ethernet controller functionality.
    It acknowledges a receiver descriptor.  When called, the number 
    of un-acknowledged RX descriptors(BUFCNT=EthDescriptorsGetRxUnack()) will 
    be decremented by one.

  Precondition:
    The RX packet associated with the corresponding descriptor must have already been processed
    and the RX descriptor should be available for the hardware DMA RX engine re-use.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    EthAckRxDcpt();
    </code>

  Remarks:
    The function should be called after a RX packet is processed and the RX 
    descriptor is available for the hardware re-use.
    
    BUFCNT is also decremented by a call to EthRxAcknowledgePacket/EthRxAcknowledgeBuffer.
    
    BUFCNT value also directs the auto flow control behavior.
 *****************************************************************************/

void EthAckRxDcpt ( void );

// DOM-IGNORE-BEGIN
extern __inline__ void __attribute__((always_inline))   EthAckRxDcpt(void)
{
    ETHCON1SET=_ETHCON1_BUFCDEC_MASK;
}
// DOM-IGNORE-END


// Section:  Ethernet MAC Low Level Access Functions

// *****************************************************************************
/* Ethernet MAC Configuration 1 Flags

  Summary:
    Ethernet MAC configuration flags (set 1)

  Description:
    This enumeration defines set 1 of the Ethernet MAC configuration flags.
    
  Remarks:
    These flags can be OR-ed together to create configuration mask values.
*/

typedef enum
{
    // Enable RX
    ETH_MAC_CONFIG1_RXEN
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG1_RXENABLE_MASK  /*DOM-IGNORE-END*/,

    // Pass all RX frames (normal and control)
    ETH_MAC_CONFIG1_PASS_ALL
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG1_PASSALL_MASK   /*DOM-IGNORE-END*/,

    // Enable acting on RX-ed PAUSE control frames
    ETH_MAC_CONFIG1_RX_PAUSE
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG1_RXPAUSE_MASK   /*DOM-IGNORE-END*/,

    // Enable TX of PAUSE control frames
    ETH_MAC_CONFIG1_TX_PAUSE
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG1_TXPAUSE_MASK   /*DOM-IGNORE-END*/,

    // Enable the loopback mode
    ETH_MAC_CONFIG1_LOOPBACK
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG1_LOOPBACK_MASK  /*DOM-IGNORE-END*/,

    // Put the TX logic in reset
    ETH_MAC_CONFIG1_RESET_TFUN
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG1_RESETTFUN_MASK /*DOM-IGNORE-END*/,

    // Put the MAC Control SUblayer/TX domain logic in reset
    ETH_MAC_CONFIG1_RESET_TMCS
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG1_RESETTMCS_MASK /*DOM-IGNORE-END*/,

    // Put the RX logic in reset
    ETH_MAC_CONFIG1_RESET_RFUN
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG1_RESETRFUN_MASK /*DOM-IGNORE-END*/,

    // Put the MAC Control SUblayer/RX domain logic in reset
    ETH_MAC_CONFIG1_RESET_RMCS
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG1_RESETRMCS_MASK /*DOM-IGNORE-END*/,

    // Reset the random generator within the TX function 
    ETH_MAC_CONFIG1_RESET_SIM
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG1_SIMRESET_MASK  /*DOM-IGNORE-END*/,

    // Put the MAC in reset 
    ETH_MAC_CONFIG1_RESET_MAC
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG1_SOFTRESET_MASK /*DOM-IGNORE-END*/

} eEthMACConfig1Flags;


// *****************************************************************************
/* Ethernet MAC Configuration 2 Flags

  Summary:
    Ethernet MAC configuration flags (set 2)

  Description:
    This enumeration defines set 2 of the Ethernet MAC configuration flags.
    
  Remarks:
    These flags can be OR-ed together to create configuration mask values.
    
    If disabled the MAC will abort when the excessive deferral limit is reached 
    and provide feedback to the host system.
*/

typedef enum
{
    // Enable full duplex functionality
    ETH_MAC_CONFIG2_FDUPLEX
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG2_FULLDPLX_MASK  /*DOM-IGNORE-END*/,

    // Enable length frame check
    ETH_MAC_CONFIG2_LEN_CHECK
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG2_LENGTHCK_MASK  /*DOM-IGNORE-END*/,

    // Enable huge frames RX/TX
    ETH_MAC_CONFIG2_HUGE_FRAME
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG2_HUGEFRM_MASK   /*DOM-IGNORE-END*/,

    // Enable 4 bytes of proprietary header (ignored by the CRC)
    ETH_MAC_CONFIG2_DELAY_CRC
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG2_DELAYCRC_MASK  /*DOM-IGNORE-END*/,

    // Enable CRC append to each TX frame
    ETH_MAC_CONFIG2_CRC_ENABLE
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG2_CRCENABLE_MASK /*DOM-IGNORE-END*/,

    // PAD/CRC enable used together with ETH_MAC_CONFIG2_VLAN_PAD and 
    // ETH_MAC_CONFIG2_AUTO_PAD
    ETH_MAC_CONFIG2_PAD_ENABLE
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG2_PADENABLE_MASK /*DOM-IGNORE-END*/,

    // Enable padding of al frames to 64 bytes and append valid CRC
    ETH_MAC_CONFIG2_VLAN_PAD
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG2_VLANPAD_MASK   /*DOM-IGNORE-END*/,

    // Enable automatic detection by the MAC of the type of frame and pad 
    // accordingly
    ETH_MAC_CONFIG2_AUTO_PAD
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG2_AUTOPAD_MASK   /*DOM-IGNORE-END*/,

    // Enable preamble verification and discard packets with preamble errors
    ETH_MAC_CONFIG2_PURE_PRE
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG2_PUREPRE_MASK   /*DOM-IGNORE-END*/,

    // Allow only packets having preamble fields less than 12 bytes in length
    ETH_MAC_CONFIG2_LONG_PRE
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG2_LONGPRE_MASK   /*DOM-IGNORE-END*/,

    // Do not use Binary Exponential Backoff algorithm following a collision, 
    // transmit immediately
    ETH_MAC_CONFIG2_NO_BACKOFF
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG2_NOBKOFF_MASK   /*DOM-IGNORE-END*/,

    // After incidentally causing a collision during backpressure the MAC will 
    // immediately retransmit without backoff
    ETH_MAC_CONFIG2_BP_NO_BACKOFF
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG2_BPNOBKOFF_MASK /*DOM-IGNORE-END*/,

    // If enabled the MAC will defer to carrier indefinitely as per the standard.
    ETH_MAC_CONFIG2_EXCESS_DEFER
        /*DOM-IGNORE-BEGIN*/ = _EMACxCFG2_EXCESSDFR_MASK /*DOM-IGNORE-END*/,

} eEthMACConfig2Flags;


// *****************************************************************************
/* Ethernet MAC Configuration Supplemental Flags

  Summary:
    Ethernet MAC configuration supplemental flags

  Description:
    This enumeration defines the supplemental Ethernet MAC configuration flags.
    
  Remarks:
    These flags can be OR-ed together to create configuration mask values.
*/

typedef enum
{
    // Reset RMII module
    ETH_MAC_CONFIG_SUPP_RMII_RESET
        /*DOM-IGNORE-BEGIN*/ = _EMACxSUPP_RESETRMII_MASK /*DOM-IGNORE-END*/,

    // 100 Mbps RMII operation
    ETH_MAC_CONFIG_SUPP_RMII_SPEED
        /*DOM-IGNORE-BEGIN*/ = _EMACxSUPP_SPEEDRMII_MASK /*DOM-IGNORE-END*/

} eEthMACConfigSuppFlags;


/*******************************************************************************
  Function:
    void EthMACConfig ( eEthMACConfig1Flags    c1Flags, 
                        eEthMACConfig2Flags    c2Flags, 
                        eEthMACConfigSuppFlags sFlags )

  Summary:
    Configures the MAC

  Description:
    This function gives access to low level Ethernet MAC configuration.  It 
    configures the MAC.

  Precondition:
    None.

  Parameters:
    c1Flags         - Configuration flags from set 1
    
    c2Flags         - Configuration flags from set 2
    
    sFlags          - Suplemental configuration flags

  Returns:
    None.

  Example:
    <code>
    EthMACConfig( ETH_MAC_CONFIG1_RXEN|ETH_MAC_CONFIG1_RX_PAUSE|ETH_MAC_CONFIG1_TX_PAUSE,
                  ETH_MAC_CONFIG2_FDUPLEX|ETH_MAC_CONFIG2_HUGE_FRAME, 
                  ETH_MAC_CONFIG_SUPP_RMII_SPEED ); 
    </code>

  Remarks:
    When connected to an external PHY the MAC and PHY configurations have to be consistent.
 *****************************************************************************/

void EthMACConfig ( eEthMACConfig1Flags c1Flags, eEthMACConfig2Flags c2Flags, 
                    eEthMACConfigSuppFlags sFlags );
 

/*******************************************************************************
  Function:
    void EthMACConfigSetFlags ( eEthMACConfig1Flags    c1Flags,
                                eEthMACConfig2Flags    c2Flags,
                                eEthMACConfigSuppFlags sFlags );

  Summary:
    Sets Ethernet MAC configuration flags

  Description:
    The function gives access to low level Ethernet MAC configuration.  Any flag set
    in the c1Flags, c2Flags, sFlags will be set, the other flags won't be 
    touched. 

  Precondition:
    None.

  Parameters:
    c1Flags         - Configuration flags from set 1 to be set
    
    c2Flags         - Configuration flags from set 2 to be set
    
    sFlags          - Suplemental configuration flags to be set

  Returns:
    None.

  Example:
    <code>
    EthMACConfigSetFlags( ETH_MAC_CONFIG1_RXEN|ETH_MAC_CONFIG1_RX_PAUSE|ETH_MAC_CONFIG1_TX_PAUSE, 
                          ETH_MAC_CONFIG2_FDUPLEX|ETH_MAC_CONFIG2_HUGE_FRAME, 
                          ETH_MAC_CONFIG_SUPP_RMII_RESET);
    </code>

  Remarks:
    When connected to an external PHY the MAC and PHY configurations have to be consistent.
 *****************************************************************************/

void EthMACConfigSetFlags ( eEthMACConfig1Flags c1Flags, eEthMACConfig2Flags c2Flags,
                            eEthMACConfigSuppFlags sFlags );


/*******************************************************************************
  Function:
    void EthMACConfigClrFlags ( eEthMACConfig1Flags    c1Flags, 
                                eEthMACConfig2Flags    c2Flags, 
                                eEthMACConfigSuppFlags sFlags );

  Summary:
    Clears Ethernet MAC configuration flags

  Description:
    The function gives access to low level Ethernet MAC configuration.  Any flag set 
    in the c1Flags, c2Flags, sFlags will be cleared, the other flags won't be 
    touched. 

  Precondition:
    None.

  Parameters:
    c1Flags         - Configuration flags from set 1 to be cleared
    
    c2Flags         - Configuration flags from set 2 to be cleared
    
    sFlags          - Suplemental configuration flags to be cleared

  Returns:
    None.

  Example:
    <code>
    EthMACConfigClrFlags( ETH_MAC_CONFIG1_RXEN|ETH_MAC_CONFIG1_RX_PAUSE|ETH_MAC_CONFIG1_TX_PAUSE, 
                          ETH_MAC_CONFIG2_FDUPLEX|ETH_MAC_CONFIG2_HUGE_FRAME, 
                          ETH_MAC_CONFIG_SUPP_RMII_RESET );
    </code>

  Remarks:
    When connected to an external PHY the MAC and PHY configurations have to be consistent.
 *****************************************************************************/

void EthMACConfigClrFlags ( eEthMACConfig1Flags c1Flags, eEthMACConfig2Flags c2Flags, 
                            eEthMACConfigSuppFlags sFlags );


/*******************************************************************************
  Function:
    void EthMACConfigB2BIpGap ( unsigned int ipGap )

  Summary:
    Sets the back to back inter packet gap

  Description:
    The function sets the back to back inter packet gap value (the nibble time 
    offset of the minimum possible period between the end of any transmitted 
    packet to the beginning of the next).

  Precondition:
    0 < ipGap < 128

  Parameters:
    ipGap       - The back to back inter packet gap

  Returns:
    None.

  Example:
    <code>
    EthMACConfigB2BIpGap(0x15);
    </code>

  Remarks:
    In full duplex the recommended value is 0x15.
    
    In half duplex the recommended value is 0x12.
 *****************************************************************************/

void EthMACConfigB2BIpGap ( unsigned int ipGap );


/*******************************************************************************
  Function:
    void EthMACConfigNB2BIpGap ( unsigned int ipgr1, unsigned int ipgr2 )

  Summary:
    Sets the non-back-to-back inter-packet gap value.

  Description:
    The function sets the non back to back inter packet gap value part 1 and 2.

    The ipgr1 represents the optional carrierSense window referenced in IEEE 
    802.3/4.2.3.2.1 Carrier Deference.  If carrier is detected during the 
    timing of IPGR1, the MAC defers to carrier. If, however, carrier becomes 
    active after IPGR1, the MAC continues timing IPGR2 and transmits,
    knowingly causing a collision, thus ensuring fair access to medium.
    The ipgr2 represents the non back to back inter packet gap.

  Precondition:
    0 < carrDefer < 128
    
    0 < nB2BIpGap < 128

  Parameters:
    carrDefer       - The carrier deference
    
    nB2BIpGap       - Non back to back inter packet gap

  Returns:
    None.

  Example:
    <code>
    EthMACConfigNB2BIpGap(0xc, 0x12);
    </code>

  Remarks:
    The ipgr1 recommended value is 0xc. Its range of values is 0x0 to ipgr2.
    
    The ipgr2 recommended value is 0x12.
 *****************************************************************************/

void EthMACConfigNB2BIpGap ( unsigned int ipgr1, unsigned int ipgr2 );

 
/*******************************************************************************
  Function:
    void EthMACConfigCollWinRetry ( unsigned int collWin, unsigned int retMax )

  Summary:
    Sets the collision window and the retransmission maximum.

  Description:
    The function sets the collision window and the retransmission maximum.
    
    The collision window is a programmable field representing the slot time or 
    collision window during which collisions occur in properly configured 
    networks.  Since the collision window starts at the beginning of 
    transmission, the preamble and SFD is included. The retransmission maximum 
    is a programmable field specifying the number of retransmission attempts
    following a collision before aborting the packet due to excessive 
    collisions.

  Precondition:
    0 < collWin < 64
    
    0 < retMax < 16

  Parameters:
    collWin         - The collision window
    
    retMax          - Retransmission maximum

  Returns:
    None.

  Example:
    <code>
    EthMACConfigCollWinRetry(0x37, 0xf);
    </code>

  Remarks:
    The collWin recommended value is 0x37 which corresponds to the count of 
    frame bytes at the end of the window. 
    
    The retMax recommended value is 0xf.
 *****************************************************************************/

void EthMACConfigCollWinRetry ( unsigned int collWin, unsigned int retMax );



/********************************************************************
 * Include legacy Ethernet functions
 * New projects should not use them!
 * The functions in the eth.h should be used instead.
 ********************************************************************/
#ifndef _PLIB_DISABLE_LEGACY
    #include <peripheral/legacy/eth_legacy.h>
#endif


#endif  // _ETH


#endif  // _ETH_H_

