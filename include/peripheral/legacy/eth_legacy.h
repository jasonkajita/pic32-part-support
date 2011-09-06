/*******************************************************************************
  Ethernet Library Interface Legacy Definition

  Summary:
    This file contains older Application Program Interface (API) definitions  for 
    the Ethernet peripheral library.
    The functions in this file are obsolete and not maintained anymore.
    Any new project should use the API in peripheral/eth.h
    
  Description:
    This library provides a low-level abstraction of the Ethernet module 
    on Microchip PIC32MX family microcontrollers with a convenient C language 
    interface.  It can be used to simplify low-level access to the module 
    without the necessity of interacting directly with the module's registers, 
    thus hiding differences from one microcontroller variant to another.
FileName:       eth_lagacy.h
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


#ifndef _ETH_LEGACY_H_
#define _ETH_LEGACY_H_

#include <stdlib.h>
#include <p32xxxx.h>

#ifdef _ETH // The Ethernet device is present

/**************************************
 *  obsolete types
 **************************************************/

#define sBuffDcpt               sEthPktDcpt


#define eBuffFlags              eEthBuffFlags
#define BUFF_FLAG_RX_STICKY     ETH_BUFF_FLAG_RX_STICKY 


#define sTxPktStat              sEthTxPktStat
#define sRxPktStat              sEthRxPktStat

typedef enum
{
    MAC_PAUSE_TYPE_NONE     = 0x0,

    MAC_PAUSE_TYPE_PAUSE    = 0x1,

    MAC_PAUSE_TYPE_ASM_DIR  = 0x2,

    MAC_PAUSE_TYPE_EN_TX    = 0x4,

    MAC_PAUSE_TYPE_EN_RX    = 0x8,

    MAC_PAUSE_ALL       = (MAC_PAUSE_TYPE_PAUSE|MAC_PAUSE_TYPE_ASM_DIR|
                           MAC_PAUSE_TYPE_EN_TX|MAC_PAUSE_TYPE_EN_RX),

    MAC_PAUSE_CPBL_MASK = MAC_PAUSE_ALL

} eMacPauseType;


/**************************************
 *  obsolete MIIM functions
 **************************************************/

/****************************************************************************
 * Function:        EthMIIMInit
 *
 * PreCondition:    None
 *
 * Input:           hostClock: the value of the host clock, Hz
 *                  miimClock: the maximum clock frequency that the PHY can use for the MIIM transactions 
 *                  oFlags:    opening flags to select the 10/100 Mbps RMII/MII speed
 *                  isRmii:    boolean to select the RMII/MII operation mode
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function initializes the MIIM interface for access of a PHY.
 *
 * Note:            - Any previous MIIM operation will be aborted!
 *                  - only ETH_OPEN_RMII and ETH_OPEN_100/ETH_OPEN_10 flags are relevant.
 *****************************************************************************/
void		EthMIIMInit(unsigned int hostClock, unsigned int miimClock, eEthOpenFlags oFlags, int isRmii);

/*******************************************************************************
  Function:
    unsigned short EthMIIMReadReg ( unsigned int rIx, unsigned int phyAdd )

  Summary:
    Performs a read operation from a PHY register

  Description:
    This function performs a read operation from a PHY register using the MIIM
    interface.

  Precondition:
    EthMIIMConfig called
    
    rIx a valid PHY register, 0-31
    
    phyAdd a valid PHY address, 0-31

  Parameters:
    rIx         - PHY register to be accessed
    
    phyAdd      - PHY address

  Returns:
    PHY register value 

  Example:
    <code>
    phyReg = EthMIIMReadReg(12, 0);
    </code>

  Remarks:
    It assumes that no scan operation is in progress!

    Before starting the read operation it waits for interface not to be busy.
    It waits for the read operation complete.   
 *****************************************************************************/

unsigned short EthMIIMReadReg ( unsigned int rIx, unsigned int phyAdd );

/*******************************************************************************
  Function:
    void EthMIIMWriteReg ( unsigned int rIx, unsigned int phyAdd, 
                           unsigned short wData )

  Summary:
    Performs a write operation to a PHY register

  Description:
    This function performs a write operation to a PHY register using the MIIM 
    interface.  It doesn't wait for the write to take effect.

  Precondition:
    EthMIIMConfig called
    
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
    EthMIIMWriteReg(12, 0, 0x001F);
    </code>

  Remarks:
    It assumes that no scan operation is in progress!

    Before starting the write operation it waits for interface not to be busy.    
 *****************************************************************************/

void EthMIIMWriteReg ( unsigned int rIx, unsigned int phyAdd, unsigned short wData );

/*******************************************************************************
  Function:
    void EthMIIMWriteRegWait ( unsigned int rIx, unsigned int phyAdd, 
                               unsigned short wData )

  Summary:
    Performs a blocking write operation to a PHY register

  Description:
    This function performs a write operation to a PHY register using the MIIM 
    interface.  It waits for the write to take effect.

  Precondition:
    EthMIIMConfig called
    
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
    EthMIIMWriteRegWait(12, 0, 0x001F);
    </code>

  Remarks:
    It assumes that no scan operation is in progress!

    Before starting the write operation it waits for interface not to be busy.
    It waits for the write operation to complete.       
 *****************************************************************************/

void EthMIIMWriteRegWait ( unsigned int rIx, unsigned int phyAdd, unsigned short wData );

/*******************************************************************************
  Function:
    unsigned short  EthMIIMScanRead ( void )

  Summary:
    Reads the result of a previously initiated scan operation

  Description:
    This function reads the result of a previously initiated scan operation 
    from a PHY register using the MIIM interface.

  Precondition:
    EthMIIMConfig called
    
    EthMIIMScanStart called

  Parameters:
    None.

  Returns:
    Result of previous scan operation

  Example:
    <code>
    if ( EthMIIMScanValid() )
    {
        value = EthMIIMScanRead();
    }
    </code>

  Remarks:
    It assumes that a scan operation is in progress!

    It waits for the scan operation result to be available.         
 *****************************************************************************/

unsigned short EthMIIMScanRead ( void );

/*******************************************************************************
  Function:
    void EthMIIMScanStopWait ( void )

  Summary:
    Stops for a previously initiated scan operation (blocking)

  Description:
    This function stops a previously initiated scan operation from a PHY 
    register using the MIIM interface.  It waits for the scan operation to 
    finish.

  Precondition:
    EthMIIMConfig called
    
    EthMIIMScanStart called

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    EthMIIMScanStopWait();
    </code>

  Remarks:
    It assumes that a scan operation is in progress!

    It waits for the scan operation to be effectively stopped.         
 *****************************************************************************/

void EthMIIMScanStopWait ( void );

/**************************************
 *  obsolete Ethernet descriptor functions
 **************************************************/

// *****************************************************************************
/* Ethernet Descriptor Allocation Function Pointer

  Function:
    void* <FunctionName> ( size_t nitems, size_t size )

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

  Returns:
    On success  - A pointer to the requested space.
    On failure  = A null pointer.
    
  Remarks:
    This function will be called for allocation of descriptors only.  
    Therefore, the size parameter will be the one returned by 
    EthDescriptorsGetSize();
*/

typedef void* ( *pEthDcptAllocF )( size_t nitems, size_t size );


// *****************************************************************************
/* Ethernet Descriptor Free Function

  Function:
    void <FunctionName> ( void* ptr )

  Summary:
    Pointer to a function that deallocates the memory previously allocated by a
    pEthDcptAllocF function.

  Description:
    Pointer to a function that deallocates the memory previously allocated by a
    pEthDcptAllocF function.
    
  Precondition:
    The pEthDcptAllocF would have been previously called.

  Parameters:
    ptr         - Points to the space that was previously allocated with a 
                  pEthDcptAllocF function.

  Returns:
    None.
    
  Remarks:
    None.
*/

typedef void ( *pEthDcptFreeF ) ( void* ptr );


/*******************************************************************************
  Function:
    int EthDescriptorsAdd ( int nDescriptors, eEthDcptType dType, 
                            pEthDcptAllocF fAlloc )

  Summary:
    Adds transmit & receive descriptors to the pool.

  Description:
    This function adds the specified number of transmit/receive descriptors to 
    the pool of descriptors.  These descriptors are used whenever a new 
    transmission or a reception is initiated.  The needed memory per descriptor
    is returned by EthDescriptorsGetSize.   Descriptors can be freed with 
    EthDescriptorsRemove.

  Precondition:
    EthInit should have been called.

  Parameters:
    nDescriptors    - Number of descriptors to be added
    
    dType           - TX/RX descriptors requested
    
    fAlloc          - Function to be called to allocate the needed memory or 
                      NULL. 

  Returns:
    The number of descriptors successfully created.

  Example:
    <code>
    if( EthDescriptorsAdd(txDcptNo, ETH_DCPT_TYPE_TX, NULL) != txDcptNo )
    {
        // Handle allocation error
    }
    </code>

  Remarks:
    The number of created descriptors is different from the number of 
    requested ones only if the memory allocation failed.  If fAlloc is NULL 
    then the standard calloc() is used to get the needed memory.
          
    The complete clean-up is done by EthDescriptorsCleanUp();
    
    ETH_DCPT_TYPE_ALL use is invalid. A proper descriptor type (RX or TX) has
    to be used.
 *****************************************************************************/

int EthDescriptorsAdd ( int nDescriptors, eEthDcptType dType, pEthDcptAllocF fAlloc );


/*******************************************************************************
  Function:
    int EthDescriptorsRemove ( int nDescriptors, eEthDcptType dType, 
                               pEthDcptFreeF fFree )

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
    fFree           - Function to release the the memory or NULL


  Returns:
    The number of descriptors removed.

  Example:
    <code>
    if ( EthDescriptorsRemove(txDcptNo, ETH_DCPT_TYPE_TX, NULL) != txDcptNo)
    {
        // Handle de-allocation error.
    }
    </code>

  Remarks:
    If fFree is NULL then the standard free() is used to release the allocated 
    memory.  The allocation/deallocation memory functions should be 
    consistent.
    
    The complete clean-up is done by EthDescriptorsCleanUp.
    
    ETH_DCPT_TYPE_ALL use is invalid. A proper descriptor type (RX or TX) has
    to be used.
 *****************************************************************************/

int EthDescriptorsRemove ( int nDescriptors, eEthDcptType dType, pEthDcptFreeF fFree );


/*******************************************************************************
  Function:
    void EthDescriptorsCleanUp ( eEthDcptType dType, pEthDcptFreeF fFree )

  Summary:
    Removes all the specified descriptors from the pool.

  Description:
    This function performs descriptors clean-up and removes all the specified
    descriptors from the pool of transmit/receive descriptors.

  Precondition:
    EthClose should have been called. 

  Parameters:
    dType        - TX/RX/All descriptors requested
    fFree        - Function to release the the memory or NULL

  Returns:
    None.

  Example:
    <code>
    EthDescriptorsCleanUp(ETH_DCPT_TYPE_ALL, NULL);
    </code>

  Remarks:
    If fFree is NULL then the standard free() is used to release the allocated
    memory.  The allocation/deallocation memory functions should be consistent.
    
    It does not free the memory allocated for the application supplied "sticky"
    buffers.  It is the calling application responsibility.
    
    EthClose should have been called or no TX/RX activity should be enabled at
    the time this function is called.
    
    If ETH_DCPT_TYPE_ALL is supplied the function will perform the clean-up of
    both types of descriptors.
 *****************************************************************************/

void EthDescriptorsCleanUp ( eEthDcptType dType, pEthDcptFreeF fFree );

/**************************************
 *  obsolete Ethernet TX/RX functions
 **************************************************/
// *****************************************************************************
/* Ethernet Buffer Acknowledge Callback Function

  Function:
    void <Function Name> ( void *pPktBuff, int buffIx )

  Summary:
    Pointer to a function called to acknowledge a packet.

  Description:
    Pointer to a function called to ackowldege the completion of a packet.
    
  Precondition:
    A TX or RX packet must have been queued.

  Parameters:
    pPktBuff    - Pointer to the currently acknowledged transmitted or received
                  buffer.
    
    buffIx      - The 0-based buffer index for a packet that spans multiple 
                  buffers.

  Returns:
    None.
    
  Remarks:
    This function is meant to be used for both RX and TX packets acknowledge.
*/

typedef void ( *pEthPktAckF ) ( void *pPktBuff, int buffIx );



/*******************************************************************************
  Function:
    eEthRes EthTxAckBuffer ( const void *pBuff, pEthPktAckF ackFnc )

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

  Returns:
    ETH_RES_OK              - Success
    
    ETH_RES_PACKET_QUEUED   - The packet is scheduled for transmission/
                              There are packets scheduled to be transmitted
    
    ETH_RES_NO_PACKET       - No such packet exists in the transmit queue/
                              No packets scheduled for transmit

  Example:
    <code>
    ethRes=EthTxAckBuffer(pTxBuff, 0);
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

eEthRes EthTxAckBuffer ( const void *pBuff, pEthPktAckF ackFnc );

/*******************************************************************************
  Function:
    eEthRes EthTxAckPacket(const sEthPktDcpt* pPkt, pEthPktAckF ackFnc)

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

  Returns:
    ETH_RES_OK              - Success
    
    ETH_RES_PACKET_QUEUED   - The packet is queued for transmission/
                              There are packets scheduled to be transmitted
    
    ETH_RES_NO_PACKET       - No such packet exist sin th etransmit queue/
                              No packets scheduled for transmit

  Example:
    <code>
    ethRes=EthTxAckPacket(pTxPkt, 0);
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

eEthRes EthTxAckPacket(const sEthPktDcpt* pPkt, pEthPktAckF ackFnc);

extern __inline__ eEthRes __attribute__((always_inline)) EthTxAckPacket(const sEthPktDcpt* pPkt, pEthPktAckF ackFnc)
{
    return  EthTxAckBuffer(pPkt?pPkt->pBuff:0, ackFnc); 
}

/*******************************************************************************
  Function:
    eEthRes EthRxAckBuffer ( const void *pBuff, pEthPktAckF ackFnc )

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

  Returns:
    ETH_RES_OK              - Success
    
    ETH_RES_PACKET_QUEUED   - The packet is in the receiving queue/
                              There are packets in the receiving queue
    
    ETH_RES_NO_PACKET       - No such packet in the receiving queue/
                              No packets available in the receiving queue

  Example:
    <code>
    ethRes = EthRxAckBuffer(pRxBuff, NULL);
    if ( ethRes != ETH_RES_OK )
    {
        // Handle buffer not acknowledged 
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

eEthRes EthRxAckBuffer ( const void *pBuff, pEthPktAckF ackFnc );

/*******************************************************************************
  Function:
    eEthRes EthRxAckPacket ( const sEthPktDcpt* pPkt, pEthPktAckF ackFnc )

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

  Returns:
    ETH_RES_OK              - Success
    
    ETH_RES_PACKET_QUEUED   - The packet is in the receiving queue/
                              There are packets in the receiving queue
    
    ETH_RES_NO_PACKET       - No such packet in the receiving queue/
                              No packets available in the receiving queue

  Example:
    <code>
    ethRes = EthRxAckPacket(pRxPkt, NULL);
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

eEthRes EthRxAckPacket ( const sEthPktDcpt* pPkt, pEthPktAckF ackFnc );

extern __inline__ eEthRes __attribute__((always_inline)) EthRxAckPacket(const sEthPktDcpt* pPkt, pEthPktAckF ackFnc)
{
    return EthRxAckBuffer(pPkt?pPkt->pBuff:0, ackFnc);
}


#endif  // _ETH

#endif  // _ETH_LEGACY_H_

