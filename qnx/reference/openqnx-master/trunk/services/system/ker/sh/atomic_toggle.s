#
# $QNXLicenseA:
# Copyright 2007, QNX Software Systems. All Rights Reserved.
# 
# You must obtain a written license from and pay applicable license fees to QNX 
# Software Systems before you may reproduce, modify or distribute this software, 
# or any work that includes all or part of this software.   Free development 
# licenses are available for evaluation and non-commercial purposes.  For more 
# information visit http://licensing.qnx.com or email licensing@qnx.com.
#  
# This file may contain contributions from others.  Please review this entire 
# file for other proprietary rights or license notices, as well as the QNX 
# Development Suite License Guide at http://licensing.qnx.com/license-guide/ 
# for other information.
# $
#

#
# atomic_toggle.s
#	atomicly toggle bit(s) in a memory location
#
 
 #
 # void atomic_toggle( volatile unsigned *loc, unsigned bits )
 #
	.global		atomic_toggle
	.section	".text"
	.type		atomic_toggle,@function
atomic_toggle:
# access the address before disable int
	stc		sr,r1
	mov.l	atomic_tog_1,r0
	or		r1,r0
	ldc		r0,sr
	
	mov.l	@r4,r0
	xor		r5,r0
	mov.l	r0,@r4
	
	ldc		r1,sr
	rts
	nop
	
	.align 2
atomic_tog_1:
	.long	0x000000f0
	
