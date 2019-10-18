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

.include "sh/util.ah"
.include "asmoff.def"

	.text

	# Handle calling a hook routine from in the kernel

	##
	## void hook_idle(struct timespec *, struct qtime_entry *, INTERRUPT *)
	##

routine_start hook_idle, 1
		# get hook routine address
		mov.l	@(INTR_HANDLER,r6),r0
		# and invoke it
		jmp		@r0
		nop
routine_end hook_idle
