/*********************************************************************
 *
 *              Default NMI Handler Implementation
 *
 *********************************************************************
 * Filename:        default-nmi-handler.S
 *
 * Processor:       PIC32
 *
 * Compiler:        chipKIT for PIC32 MCUs
 *
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * This software is developed by Microchip Technology Inc. and its
 * subsidiaries ("Microchip").
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1.      Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2.      Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3.      Microchip's name may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING BUT NOT LIMITED TO
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWSOEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ********************************************************************/

#include <p32xxxx.h>
#ifdef __LIBBUILD__
	.file 1 "Microchip PIC32 Library"
	.loc 1 0
#endif
	.text
	.align	2
	.weak	_nmi_handler
	.set	nomips16
	.ent	_nmi_handler
_nmi_handler:
	.frame	sp,0,$31		# vars= 0, regs= 0/0, args= 0, gp= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder

        mfc0    k0, _CP0_STATUS                   # retrieve STATUS
        lui     k1, ~(_CP0_STATUS_BEV_MASK >> 16) & 0xffff
        ori     k1, k1, ~_CP0_STATUS_BEV_MASK & 0xffff
        and     k0, k0, k1                        # Clear BEV
        mtc0    k0, _CP0_STATUS                   # store STATUS
        eret

	.set	macro
	.set	reorder
	.end	_nmi_handler
	.size	_nmi_handler, .-_nmi_handler
