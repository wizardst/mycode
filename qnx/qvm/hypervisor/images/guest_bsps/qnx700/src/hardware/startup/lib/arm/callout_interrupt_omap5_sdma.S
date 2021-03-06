/*
 * $QNXLicenseC:
 * Copyright 2010, QNX Software Systems. 
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"). You 
 * may not reproduce, modify or distribute this software except in 
 * compliance with the License. You may obtain a copy of the License 
 * at: http://www.apache.org/licenses/LICENSE-2.0 
 * 
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" basis, 
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as 
 * contributors under the License or as licensors under other terms.  
 * Please review this entire file for other proprietary rights or license 
 * notices, as well as the QNX Development Suite License Guide at 
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */




/*
 * TI OMAP5 specific SDMA interrupt callouts.
 *
 * interrupt_id_* and interrupt_eoi_* are copied and intermixed with other
 * kernel code during initialisation.
 *
 * They do not follow normal calling conventions, and must fall through
 * to the end, rather than attempting to perform a return instruction.
 *
 * The INTR_GENFLAG_* bits in the intrinfo_entry defines which of the
 * following values can be loaded on entry to these code fragments:
 *
 *	r5 - holds the syspageptr				(INTR_GENFLAG_SYSPAGE  set)
 *	r6 - holds the intrinfo_entry pointer	(INTR_GENFLAG_INTRINFO set)
 *	r7 - holds the interrupt mask count		(INTR_GENFLAG_INTRMASK set)
 *
 * The interrupt_id_* routine returns the (controller-relative) level in r4
 */

#include "callout.ah"

#define SDMA_SIZE               0x1000
#define SDMA_IRQSTATUS          0x08
#define SDMA_IRQENABLE          0x18

/*
 * -----------------------------------------------------------------------
 * Patch callout code (for SDMA)
 *
 * On entry:
 *	r0 - physical address of syspage
 *	r1 - virtual  address of syspage
 *	r2 - offset from start of syspage to start of the callout routine
 *	r3 - offset from start of syspage to read/write data used by callout
 * -----------------------------------------------------------------------
 */
interrupt_patch_sdma:
	stmdb	sp!, {r4, lr}
	add		r4, r0, r2			// address of callout routine

    /*
     * Align base address to SDMA physical base address for backward
     * compatibility with other BPS using directly the IRQSTATUS register
     * offset as physical base address.
     */
	ldr		r2, [sp, #8]
	ldrd	r0, [r2]			// r0,r1 = *patch_data
.ifdef	VARIANT_le
	bic		r0, r0, #0x0ff
	bic		r0, r0, #0xf00		// r0 &= ~0xfff
.else
	bic		r1, r1, #0x0ff
	bic		r1, r1, #0xf00		// r1 &= ~0xfff
.endif

	/*
	 * Check if we have already mapped this paddr
	 */
	adr 	r2, Lpaddr
	ldrd 	r2, [r2] 			// r2,r3 = Lpaddr
	cmp 	r0, r2
	cmpeq 	r1, r3
	ldreq 	r0, Lvaddr 			// get previous mapped vaddr
	beq 	1f
	adr 	r2, Lpaddr
	strd 	r0, [r2]

    /*
	 * Map interrupt controller registers
	 */
    mov     r0, #SDMA_SIZE
	adr		r1, Lpaddr
	bl		callout_io_map_indirect
	str		r0, Lvaddr

1:
	/*
	 * Patch the callout routine
	 */
	CALLOUT_PATCH	r4, r0, r1, r2, ip
	ldmia	sp!, {r4, pc}

		.align	3
Lpaddr:	.quad	0xFFFFFFFF		// SDMA interrupt status register base address
Lvaddr:	.word	0xFFFFFFFF

/*
 * -----------------------------------------------------------------------
 * Identify SDMA interrupt source.
 *
 * Returns interrupt number in r4
 * -----------------------------------------------------------------------
 */
CALLOUT_START(interrupt_id_omap5_sdma, 0, interrupt_patch_sdma)
	/*
	 * Get the interrupt controller base address (patched)
	 */
	mov		ip,     #0x000000ff
	orr		ip, ip, #0x0000ff00
	orr		ip, ip, #0x00ff0000
	orr		ip, ip, #0xff000000

	/*
	 * Read Interrupt Mask and Status
	 */
	ldr		r3, [ip, #SDMA_IRQSTATUS]		// Status
	ldr		r2, [ip, #SDMA_IRQENABLE]		// Mask
	and		r3, r3, r2

	/*
	 * Scan for first set bit
	 */
	clz		r4, r3
	rsbs	r4, r4, #31
	blt		1f

    /*
	 * Mask the interrupt source
	 */
	mov		r1, #1
	mov		r1, r1, lsl r4
	bic		r2, r2, r1
	str		r2, [ip, #SDMA_IRQENABLE]
	ldr		r2, [ip, #SDMA_IRQENABLE]

	/*
	 * Clear interrupt status
	 * 09.17.2014: clearing the staus bit is moved to the eoi-callout since the status bit related
	 * to a channel can only be claered if the channel status register of the associated
	 * channel is cleared. Clearing the csr can't be done in a generic way here because the attached
	 * isterrupt service routines need to know the interrupt reason (block, fram, drop etc. ...)
	 */
	//str		r1, [ip, #SDMA_IRQSTATUS]
1:
CALLOUT_END(interrupt_id_omap5_sdma)

/*
 * -----------------------------------------------------------------------
 * Acknowledge specified SDMA interrupt
 *
 * On entry:
 *	r4 contains the interrupt number
 *	r7 contains the interrupt mask count
 * -----------------------------------------------------------------------
 */
CALLOUT_START(interrupt_eoi_omap5_sdma, 0, interrupt_patch_sdma)
	/*
	 * Get the interrupt controller base address (patched)
	 */
	mov		ip,     #0x000000ff
	orr		ip, ip, #0x0000ff00
	orr		ip, ip, #0x00ff0000
	orr		ip, ip, #0xff000000

    /*
     * Only unmask interrupt if mask count is zero
     */
	teq		r7, #0
	bne		0f
	
	/*
	 * Clear interrupt status
	 * see comment in the id-callout
	 */
	mov		r2, #1
	mov		r2, r2, lsl r4
	str		r2, [ip, #SDMA_IRQSTATUS]

	ldr		r1, [ip, #SDMA_IRQENABLE]
	orr		r1, r1, r2
	str		r1, [ip, #SDMA_IRQENABLE]

0:
CALLOUT_END(interrupt_eoi_omap5_sdma)

/*
 * -----------------------------------------------------------------------
 * Mask specified SDMA interrupt
 *
 * On entry:
 *	r0 - syspage_ptr
 *	r1 - interrupt number
 *
 * Returns:
 *	r0 - error status
 * -----------------------------------------------------------------------
 */
CALLOUT_START(interrupt_mask_omap5_sdma, 0, interrupt_patch_sdma)
	/*
	 * Get the interrupt controller base address (patched)
	 */
	mov		ip,     #0x000000ff
	orr		ip, ip, #0x0000ff00
	orr		ip, ip, #0x00ff0000
	orr		ip, ip, #0xff000000

    /*
     * Mask the interrupt
     */
	mov		r2, #1
	mov		r2, r2, lsl r1
	ldr		r1, [ip, #SDMA_IRQENABLE]
	bic		r1, r1, r2
	str		r1, [ip, #SDMA_IRQENABLE]

    mov     r0, #0
    mov     pc, lr
CALLOUT_END(interrupt_mask_omap5_sdma)

/*
 * -----------------------------------------------------------------------
 * Unmask specified SDMA interrupt
 *
 * On entry:
 *	r0 - syspage_ptr
 *	r1 - interrupt number
 *
 * Returns:
 *	r0 - error status
 * -----------------------------------------------------------------------
 */
CALLOUT_START(interrupt_unmask_omap5_sdma, 0, interrupt_patch_sdma)
	/*
	 * Get the interrupt controller base address (patched)
	 */
	mov		ip,     #0x000000ff
	orr		ip, ip, #0x0000ff00
	orr		ip, ip, #0x00ff0000
	orr		ip, ip, #0xff000000

    /*
     * Unmask the interrupt
     */
	mov		r2, #1
	mov		r2, r2, lsl r1
	
	// clear interrupt status, the status bit won't be cleared unless the interrupt source is cleared
	str		r2, [ip, #SDMA_IRQSTATUS]
	
	// unmask the interrupt
	ldr		r1, [ip, #SDMA_IRQENABLE]
	orr		r1, r1, r2
	str		r1, [ip, #SDMA_IRQENABLE]

	mov		r0, #0
	mov		pc, lr
CALLOUT_END(interrupt_unmask_omap5_sdma)

#ifdef __QNXNTO__
#ifdef __USESRCVERSION
.section .ident, "SM",%progbits,1;
.asciz "$URL: http://svn.ott.qnx.com/product/mainline/hardware/startup/lib/arm/callout_interrupt_omap5_sdma.S $ $Rev: 781278 $";
.previous
#endif
#endif 
