/*********************************************************************
 *
 *                  UART Library definitions
 *
 *********************************************************************
 * FileName:        uart.h
 * Dependencies:
 * Processor:       PIC32
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc..
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC32 Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PIC32 Microcontroller products.
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
 * $Id: uart.h,v 1.2 2006/10/24 18:42:33 C10737 Exp $
 * $Name: 1.6 $
 *
 ********************************************************************/
#ifndef _UART_H
#define _UART_H


#ifdef PIC24
	#define _UART1
	#define _UART2
    #include <p24Fxxxx.h>
#else
    #include <p32xxxx.h>
    #include <peripheral/int.h>
#endif // PIC24


#define UART2       UART3A
#define UART3       UART2A
#define UART4       UART1B
#define UART5       UART3B
#define UART6       UART2B


/* This file supports following types and instances of UART peripheral.
#define _UART1
#define _UART2
*/

/**************************************************************
 * config1 Parameter Values to be used with OpenUARTx()
 *************************************************************/
#define UART_EN                 (1<<15)                 /* Module enable */
#define UART_DIS                (0)                		/* Module disable */

#define UART_IDLE_STOP          (1<<13)                 /* Stop all functions in IDLE mode */
#define UART_IDLE_CON           (0)         			/* Work in IDLE mode */

#define UART_ALTRX_ALTTX        (1<<10)                 /* Communication through ALT pins */
#define UART_RX_TX              (0)       				/* Communication through the normal pins */

#define UART_EN_WAKE            (1<<7)                  /* Enable Wake-up on START bit Detect during SLEEP Mode bit */
#define UART_DIS_WAKE           (0)           			/* Disable Wake-up on START bit Detect during SLEEP Mode bit */

#define UART_EN_LOOPBACK        (1<<6)                  /* Loop back enabled */
#define UART_DIS_LOOPBACK       (0)      				/* Loop back disabled */

#define UART_EN_ABAUD           (1<<5)                  /* Input to Capture module from UxRX pin */
#define UART_DIS_ABAUD          (0)          			/* Input to Capture module from ICx pin */

#define UART_NO_PAR_9BIT        (3<<1)                  /* No parity 9 bit */
#define UART_ODD_PAR_8BIT       (2<<1)                  /* odd parity 8 bit */
#define UART_EVEN_PAR_8BIT      (1<<1)                  /* even parity 8 bit */
#define UART_NO_PAR_8BIT        (0)                  	/* no parity 8 bit */

#define UART_2STOPBITS          (1)                  	/* 2 stop bits */
#define UART_1STOPBIT           (0)                  	/* 1 stop bit */

#define UART_IRDA_EN            (1<<12)                 /* IRDA encoder and decoder enable */
#define UART_IRDA_DIS           (0)           			/* IRDA encoder and decoder disable */

#define UART_MODE_SIMPLEX      	(1<<11)                 /* UxRTS pin in Simplex mode */
#define UART_MODE_FLOWCTRL     	(0)     				/* UxRTS pin in Flow Control mode */

#define UART_EN_BCLK			(3<<8)					/* BCLKx pin is enabled. */
#define UART_EN_CTS_RTS			(2<<8)					/* CTS and RTS pins are enabled */
#define UART_EN_RTS				(1<<8)					/* RTS pin is enabled. */
#define UART_DIS_BCLK_CTS_RTS	(0)						/* Disable BCLKx, CTS, and RTS pins */

#define UART_INVERT_RX			(1<<4)					/* UxRX idle state is '0' */
#define UART_NORMAL_RX			(0)						/* UxRX idle state is '1' */

#define UART_BRGH_FOUR			(1<<3)					/* 4x baud clock - High speed */
#define UART_BRGH_SIXTEEN		(0)						/* 16x baud clock - Normal speed */


/**************************************************************
 * config2 Parameter Values to be used with OpenUARTx()
 *************************************************************/
#define UART_TX_PIN_NORMAL      (1<<13)                 /* IrDA encoded UxTX idle state is '1' */
#define UART_TX_PIN_LOW         (0)     				/* IrDA encoded UxTX idle state is '0' */

#define UART_RX_ENABLE			(1<<12)					/* Enable UxRX pin */
#define UART_RX_DISABLE			(0)

#define UART_TX_ENABLE         	(1<<10)                 /* Enable UxTX pin */
#define UART_TX_DISABLE        	(0)         			/* Disable UxTX pin */

#define UART_INT_TX_BUF_EMPTY   (2<<14)  				/* Interrupt on TXBUF becoming empty */
#define UART_INT_TX_LAST_CH		(1<<14)					/* Interrupt when last character shifted out*/
#define UART_INT_TX             (0)  					/* Interrupt on transfer of every character to TSR */

#define UART_INT_RX_BUF_FUL     (3<<6)                 	/* Interrupt on RXBUF full */
#define UART_INT_RX_3_4_FUL     (2<<6)                 	/* Interrupt on RXBUF 3/4 full */
#define UART_INT_RX_CHAR        (0)                  	/* Interrupt on every char received */\


#define UART_ADR_DETECT_EN		(1<<5)					/* Enable 9-bit address detect*/
#define UART_ADR_DETECT_DIS		(0)

#define UART_RX_OVERRUN_CLEAR   (0)                  	/* Rx buffer Over run status bit clear */

/******************************************************************************
 * <combinewith OpenUART2>
 * 
 * Function:        void OpenUARTx(unsigned int config1,
 *									unsigned int config2,
 *									unsigned int ubrg)
 *
 * Description:		Configures UARTx
 *
 * PreCondition:    None
 *
 * Inputs:			config1: Bit-wise OR value of config1 parameters as defined
 *							above. Must use only one from each group.
 *					config2: Bit-wise OR value of config2 parameters as defined
 *							above. Must use only one from each group.
 *
 *					An absent symbol is automatically taken as off or default value.
 *
 * Output:          None
 *
 * Example:			OpenUART1(UART_EN | UART_BRGH_FOUR,
 *							  UART_TX_PIN_NORMAL | UART_RX_EN | UART_TX_ENABLE,
 *							  123)
 *
 *****************************************************************************/
#if defined(_UART1)
#define OpenUART1(config1, config2, ubrg)	(U1BRG = (ubrg), U1MODE = (config1), U1STA = (config2))
#endif

#if defined(_UART2)
#define OpenUART2(config1, config2, ubrg)	(U2BRG = (ubrg), U2MODE = (config1), U2STA = (config2))
#endif

/******************************************************************************
 * Function:        int mUARTBRG(int pb_clk, int baud_rate)
 *
 * Description:		Calculates the BRG values needed for the UART configuration
 *
 * PreCondition:    None
 *
 * Inputs:		pb_clk:		- the PB clock frequency, HZ
 * 			baud_rate:	- the derired baud rate
 *
 * Output:          The proper BRG value
 *
 * Example:	OpenUART1(UART_EN | UART_BRGH_FOUR, UART_TX_PIN_NORMAL | UART_RX_EN | UART_TX_ENABLE, mUARTBRG(72000000, 38400));
 *
 *****************************************************************************/
#define mUARTBRG(pb_clk, baud_rate)	(((pb_clk)/16/(baud_rate)-1))


/******************************************************************************
 * <combinewith EnableIntU2RX>
 * 
 * Function:        void EnableIntUxRX(void)
 *
 * Description:		Enables UARTx Receive Interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			EnableIntU1RX;
 *
 *****************************************************************************/
#if defined(_UART1)
#define EnableIntU1RX                   mU1RXIntEnable(1)
#endif
#if defined(_UART2)
#define EnableIntU2RX                   mU2RXIntEnable(1)
#endif


/******************************************************************************
 * <combinewith DisableIntU2RX>
 * 
 * Function:        void DisableIntUxRX(void)
 *
 * Description:		Enables UARTx Receive Interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			DisableIntU1RX;
 *
 *****************************************************************************/
#if defined(_UART1)
#define DisableIntU1RX                  mU1RXIntEnable(0)
#endif
#if defined(_UART2)
#define DisableIntU2RX                  mU2RXIntEnable(0)
#endif


/******************************************************************************
 * <combinewith EnableIntU2TX>
 * 
 * Function:        void EnableIntUxTX(void)
 *
 * Description:		Enables UARTx Transmit Interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			EnableIntU1TX;
 *
 *****************************************************************************/
#if defined(_UART1)
#define EnableIntU1TX                   mU1TXIntEnable(1)
#endif
#if defined(_UART2)
#define EnableIntU2TX                   mU2TXIntEnable(1)
#endif

/******************************************************************************
 * <combinewith DisableIntU2TX>
 * 
 * Function:        void DisableIntUxTX(void)
 *
 * Description:		Disables UARTx Transmit Interrupt
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			DisableIntU1TX;
 *
 *****************************************************************************/
#if defined(_UART1)
#define DisableIntU1TX                  mU1TXIntEnable(0)
#endif
#if defined(_UART2)
#define DisableIntU2TX                  mU2TXIntEnable(0)
#endif

/**************************************************************
 * Parameter values to be used with SetPriorityIntUx() and
 * ConfigIntUARTx()
 *************************************************************/
#define UART_INT_PR0					(0)
#define UART_INT_PR1					(1)
#define UART_INT_PR2					(2)
#define UART_INT_PR3					(3)
#define UART_INT_PR4					(4)
#define UART_INT_PR5					(5)
#define UART_INT_PR6					(6)
#define UART_INT_PR7					(7)

/**************************************************************
 * Parameter values to be used with SetSubPriorityIntUx()
 *************************************************************/
#define UART_INT_SUB_PR0				(0 << 4)
#define UART_INT_SUB_PR1				(1 << 4)
#define UART_INT_SUB_PR2				(2 << 4)
#define UART_INT_SUB_PR3				(3 << 4)

/**************************************************************
* Parameter values to be used with ConfigIntUARTx() only
*************************************************************/
#define UART_ERR_INT_EN     			(1 << 6)  	/* Error interrupt enabled */
#define UART_ERR_INT_DIS    			(0)  		/* Error interrupt disabled */

#define UART_RX_INT_EN      			(1 << 7)  	/* Receive interrupt enabled */
#define UART_RX_INT_DIS     			(0)  		/* Receive interrupt disabled */

#define UART_TX_INT_EN      			(1 << 8)  	/* Transmit interrupt enabled */
#define UART_TX_INT_DIS     			(0)  		/* Transmit interrupt disabled */

/******************************************************************************
 * <combinewith ConfigIntUART2>
 * 
 * Function:        void ConfigIntUART1(int config)
 *
 * Description:		Configures interrupt settings for UART x
 *
 * PreCondition:    None
 *
 * Inputs:			Bit-wise OR value of UART_RX_INT_XX, UART_TX_INT_XX,
 *					UART_ERR_INT_XXX, UART_INT_PRx, UART_INT_SUB_PRx
 *
 * Output:          None
 *
 * Example:			ConfigIntUART1(UART_RX_INT_EN | UART_ERR_INT_EN |
 *									 | UART_INT_PR0 | UART_INT_SUB_PR2);
 *
 *****************************************************************************/
#if defined(_UART1)
#define ConfigIntUART1(config)	( mU1ClearAllIntFlags(), SetPriorityIntU1(config), \
	SetSubPriorityIntU1(config), mU1SetIntEnable((((config)>> 6) & 7)) )
#endif

#if defined(_UART2)
#define ConfigIntUART2(config) ( mU2ClearAllIntFlags(), SetPriorityIntU2(config), \
	SetSubPriorityIntU2(config), mU2SetIntEnable((((config)>> 6) & 7)) )
#endif

/******************************************************************************
 * <combinewith SetPriorityIntU2>
 * 
 * Function:        void SetPriorityIntUx(int pri)
 *
 * Description:		Sets priority for UARTx
 *
 * PreCondition:    None
 *
 * Inputs:			pri:   A value from UART_INT_PRx
 *
 *
 * Output:          None
 *
 * Example:			SetPriorityIntUx(UART_INT_PR3)
 *
 *****************************************************************************/
#if defined(_UART1)
#define SetPriorityIntU1(pri)    	mU1SetIntPriority(((pri) & 0x7))
#endif

#if defined(_UART2)
#define SetPriorityIntU2(pri)    	mU2SetIntPriority(((pri) & 0x7))
#endif

/******************************************************************************
 * <combinewith SetSubPriorityIntU2>
 * 
 * Function:        void SetSubPriorityIntUx(int sub)
 *
 * Description:		Sets subpriority for UARTx
 *
 * PreCondition:    None
 *
 * Inputs:			sub:	A value from UART_INT_SUB_PRx
 *
 *
 * Output:          None
 *
 * Example:			SetPriorityIntUx(UART_INT_SUB_PR3)
 *
 *****************************************************************************/
#if defined(_UART1)
#define SetSubPriorityIntU1(sub)    mU1SetIntSubPriority((((sub)>> 4) & 3))
#endif

#if defined(_UART2)
#define SetSubPriorityIntU2(sub)    mU2SetIntSubPriority((((sub)>> 4) & 3))
#endif




/******************************************************************************
 * <combinewith UART1ClearAllErrors, UART1ClearError, UART2GetErrors, UART2ClearAllErrors, UART2ClearError>
 * 
 * Function:        int UARTxGetErrors(void)
 *					void UARTxClearErrors(void)
 *
 * Description:		UARTxGetErrrors() retrives bitmap of various error values
 *					UARTxClearAllErrors() clears all error flags.
 *                  UART1ClearError(error) clear specific error flag.
 *
 * PreCondition:    None
 *
 * Inputs:
 *
 * Output:          Overflow Error - _UxSTA_OERR_MASK
 *					Frame error - _UxSTA_FERR_MASK
 *					Parity error - _UxSTA_PERR_MASK
 *
 * Example:			// hande an overflow error on UART 1
 *                  if(UART1GetErrors() & _U1STA_FERR_MASK)
 *                  {
 *                     // handle error...
 *                      UARTClearError(_U1STA_FERR_MASK);
 *                  }
 *
 * NOTES: See device header file for output defines
 *
 *****************************************************************************/
#if defined(_UART1)
#define UART1GetErrors()		(U1STA & (_U1STA_OERR_MASK | _U1STA_FERR_MASK | _U1STA_PERR_MASK))
#define UART1ClearAllErrors()	(U1STACLR = (_U1STA_OERR_MASK | _U1STA_FERR_MASK | _U1STA_PERR_MASK))
#define UART1ClearError(error)	(U1STACLR = (error))
#endif

#if defined(_UART2)
#define UART2GetErrors()		(U2STA & (_U2STA_OERR_MASK | _U2STA_FERR_MASK | _U2STA_PERR_MASK))
#define UART2ClearAllErrors()	(U2STACLR = (_U2STA_OERR_MASK | _U2STA_FERR_MASK | _U2STA_PERR_MASK))
#define UART2ClearError(error)	(U2STACLR = (error))
#endif

/******************************************************************************
 * <combinewith getcUART2>
 * 
 * Function:        void getcUARTx(void)
 *
 * Description:		Reads one character from UART x receive buffer
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			getcUART1;
 *
 *****************************************************************************/
#if defined(_UART1)
#define getcUART1           (char)ReadUART1
#endif

#if defined(_UART2)
#define getcUART2           (char)ReadUART2
#endif


/******************************************************************************
 * <combinewith putcUART2>
 * 
 * Function:        void putcUARTx(char c)
 *
 * Description:		Writes one character to UART x transmit buffer
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			putcUART1('m');
 *
 *****************************************************************************/
#if defined(_UART1)
#define putcUART1(c)           do{while(!U1STAbits.TRMT); WriteUART1((int)(c));}while(0)
#endif

#if defined(_UART2)
#define putcUART2(c)           do{while(!U2STAbits.TRMT); WriteUART2((int)(c));}while(0)
#endif


/******************************************************************************
 * <combinewith putsUART2>
 * 
 * Function:        void putsUARTx(const char *buffer)
 *
 * Description:		Transmit a NULL transmitted string via UARTx
 *
 * PreCondition:    None
 *
 * Inputs:			buffer:		NULL terminated string to be transmitted
 *
 * Output:          None
 *
 * Example:			putsUART1(myString);
 *					putsUART1("Hello World!");
 *
 *****************************************************************************/
#if defined(_UART1)
void putsUART1(const char* buffer);
#endif

#if defined(_UART2)
void putsUART2(const char* buffer);
#endif


/******************************************************************************
 * <combinewith WriteUART2>
 * 
 * Function:        void WriteUART1(unsigned int data)
 *
 * Description:		Transmit a character via UARTx
 *
 * PreCondition:    None
 *
 * Inputs:			data:    A character to be transmitted
 *
 * Output:          None
 *
 * Example:			WriteUART1('a');
 *					WriteUART1(myChar);
 *
 *****************************************************************************/
#if defined(_UART1)
#define WriteUART1(data)	U1TXREG = (data)
#endif

#if defined(_UART2)
#define WriteUART2(data)	U2TXREG = (data)
#endif

/******************************************************************************
 * <combinewith ReadUART2>
 * 
 * Function:        char ReadUART1(void)
 *
 * Description:		Read a character from UARTx receive buffer
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          Data from UARTx receive buffer
 *
 * Example:			myData = ReadUART1();
 *
 *****************************************************************************/
#if defined(_UART1)
#define ReadUART1()		(U1RXREG)
#endif

#if defined(_UART2)
#define ReadUART2()		(U2RXREG)
#endif

/******************************************************************************
 * <combinewith CloseUART2>
 * 
 * Function:        void CloseUARTx(void)
 *
 * Description:		Disables UART interrupt and closes UART x
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			CloseUART1();
 *
 *****************************************************************************/
#if defined(_UART1)
#define CloseUART1()	    U1MODECLR = (1<<_U1MODE_UARTEN_POSITION)
#endif

#if defined(_UART2)
#define CloseUART2()	    U2MODECLR = (1<<_U2MODE_UARTEN_POSITION);
#endif


/******************************************************************************
 * <combinewith DataRdyUART2>
 * 
 * Function:        int DataRdyUARTx(void)
 *
 * Description:		Checks to see if a data is ready is in UARTx
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          If ‘0’ is returned, it indicates that receive buffer does
 *                  not have any new data to be read.
 *                  If Non-Zero value is returned, it indicates that the receive
 *                  buffer has a data to be read.
 *
 * Example:			DataRdyUART1();
 *
 *****************************************************************************/
#if defined(_UART1)
#define DataRdyUART1()		(U1STAbits.URXDA)
#endif

#if defined(_UART2)
#define DataRdyUART2()		(U2STAbits.URXDA)
#endif

/******************************************************************************
 * <combinewith BusyUART2>
 * 
 * Function:        int BusyUARTx(void)
 *
 * Description:		Checks to see if a UARTx transmitter is empty
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          '0' if UART1 transmitter is not busy
 *					Non-zero if UART1 transmitter is busy
 *
 * Example:			if ( BusyUART1() == 0)		// Is it not busy?
 *
 *****************************************************************************/
#if defined(_UART1)
#define BusyUART1()		(!U1STAbits.TRMT)
#endif

#if defined(_UART2)
#define BusyUART2()		(!U2STAbits.TRMT)
#endif

/******************************************************************************
 * <combinewith getsUART2>
 * 
 * Function:        unsigned int getsUART1(unsigned int length,
 *											char* buffer,
 *											unsigned int uart_data_wait);
 *
 * Description:		Checks to see if a data is ready is in UARTx
 *
 * PreCondition:    None
 *
 * Inputs:			length:	This is the length of the string to be received
 *                  buffer:	This is the pointer to the location where the data
 *                          received have to be stored.
 *                  uart_data_wait:	This is the time-out count for which the module
 *                          has to wait before return.  If the time-out count is ‘N’,
 *                          the actual time out would be about (19 * N – 1) instruction cycles.
 * Output:          None
 *
 * Example:			getsUART1(12, myBuffer, 123);
 *
 *****************************************************************************/
#if defined(_UART1)
unsigned int getsUART1(unsigned int length, char* buffer, unsigned int uart_data_wait);
#endif

#if defined(_UART2)
unsigned int getsUART2(unsigned int length, char* buffer, unsigned int uart_data_wait);
#endif


/******************************************************************************
 * <combinewith UART2EnableAutoAddr>
 * 
 * Function:        void UARTxEnableAutoAddr(int address)
 *
 * Description:		Enables the automatic address matching mode of UARTx
 *
 * PreCondition:    None
 *
 * Inputs:			address:	The 9-bit address for this UART
 *
 * Output:          None
 *
 * Example:			UART1EnableAutoAddr(0x18);
 *
 *****************************************************************************/
#if defined(_UART1)
#define UART1EnableAutoAddr(address) (U1STA |= ((1 << _U1STA_ADM_EN_POSITION) | (address << _U1STA_ADDR_POSITION) | (1 << _U1STA_ADDEN_POSITION)))
#endif

#if defined(_UART2)
#define UART2EnableAutoAddr(address) ((U2STA |= (1 << _U2STA_ADM_EN_POSITION) | (address << _U2STA_ADDR_POSITION) | (1 << _U2STA_ADDEN_POSITION)))
#endif

/******************************************************************************
 * <combinewith UART2SendBreak>
 * 
 * Function:        void UARTxSendBreak(void);
 *
 * Description:		Initiates Break sequence on UARTx
 *
 * PreCondition:    None
 *
 * Inputs:			None
 *
 * Output:          None
 *
 * Example:			UART1SendBreak();
 *
 *****************************************************************************/
#if defined(_UART1)
#define UART1SendBreak()	(U1STASET = (1<<_U1STA_UTXBRK_POSITION), WriteUART1(0))
#endif

#if defined(_UART2)
#define UART2SendBreak()	(U2STASET = (1<<_U2STA_UTXBRK_POSITION), WriteUART2(0))
#endif


/******************************************************************************
 * Following defines are provided for PIC24/dsPIC backward compatibility only.
 * Do not use these defines for PIC32MX native applications.
 *****************************************************************************/
	#define UART_RX_INT_PR0         UART_INT_PR0
	#define UART_RX_INT_PR1         UART_INT_PR1
	#define UART_RX_INT_PR2         UART_INT_PR2
	#define UART_RX_INT_PR3         UART_INT_PR3
	#define UART_RX_INT_PR4         UART_INT_PR4
	#define UART_RX_INT_PR5         UART_INT_PR5
	#define UART_RX_INT_PR6         UART_INT_PR6
	#define UART_RX_INT_PR7         UART_INT_PR7
	#define UART_TX_INT_PR0         UART_INT_PR0
	#define UART_TX_INT_PR1         UART_INT_PR1
	#define UART_TX_INT_PR2         UART_INT_PR2
	#define UART_TX_INT_PR3         UART_INT_PR3
	#define UART_TX_INT_PR4         UART_INT_PR4
	#define UART_TX_INT_PR5         UART_INT_PR5
	#define UART_TX_INT_PR6         UART_INT_PR6
	#define UART_TX_INT_PR7         UART_INT_PR7

	// On PIC32MX, there are no separate priorities for RX and TX interrupt
	// Each UART has its own priority and all interrupts (TX, RX and Error)
	// for that UART have the same priority
	#define SetPriorityIntU1RX		SetPriorityIntU1
	#define SetPriorityIntU2RX		SetPriorityIntU2
	#define SetPriorityIntU1TX		SetPriorityIntU1
	#define SetPriorityIntU2TX		SetPriorityIntU2


#endif /*_UART_H */
