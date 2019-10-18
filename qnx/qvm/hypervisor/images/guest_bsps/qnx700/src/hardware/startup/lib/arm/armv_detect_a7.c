/*
 * $QNXLicenseC:
 * Copyright 2017, QNX Software Systems.
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

#include "startup.h"

/*
 * Determine which variant of A7 we should use
 */

const struct armv_chip *
armv_detect_a7(void)
{
	unsigned	scu;

	/*
	 * Figure out if we're an MPCore implementation by reading the
	 * Configuration Base Address register
	 */
	__asm__ __volatile__("mrc	p15, 4, %0, c15, c0, 0" : "=r"(scu));
	if (scu != 0) {
		mpcore_scu_base = scu & 0xFFFF8000;
	}

	return &armv_chip_a7;
}


#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/hardware/startup/lib/arm/armv_detect_a7.c $ $Rev: 847636 $")
#endif
