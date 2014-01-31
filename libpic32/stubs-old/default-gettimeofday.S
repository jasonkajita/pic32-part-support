/*********************************************************************
 *
 *              Default Get Time of Day Implementation
 *
 *********************************************************************
 * Filename:        default-gettimeofday.S
 *
 * Processor:       PIC32
 *
 * Compiler:        MPLAB C Compiler for PIC32 MCUs
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the 'Company') for its PIC32/PIC24F Microcontroller is intended
 * and supplied to you, the Company's customer, for use solely and
 * exclusively on Microchip PIC32/PIC24F Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ********************************************************************/
#ifdef __LIBBUILD__
	.file	1 "/MPLAB XC32 -- math-library weak-function gettimeofday"
	.loc 1 0
	.section .mdebug.abi32
	.previous
	.ident	"Weak gettimeofday() definition: Microchip MPLAB C Compiler for PIC32"
	
	.section	.gnu.warning.gettimeofday
	.align	2
	.ascii	"Linking code with default gettimeofday"
	.ascii	" routine. Hint: Write an app-specific version.\000"
#endif
	.text
	.align	2
	.weak	gettimeofday
	.set	nomips16
	.ent	gettimeofday

gettimeofday:
	.set	noreorder
	.set	nomacro

	li	$2,-1			# always fail, return -1
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	gettimeofday
	.size	gettimeofday, .-gettimeofday

