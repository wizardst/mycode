/*
 * $QNXLicenseC:
 * Copyright 2007, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to QNX 
 * Software Systems before you may reproduce, modify or distribute this software, 
 * or any work that includes all or part of this software.   Free development 
 * licenses are available for evaluation and non-commercial purposes.  For more 
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *  
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/ 
 * for other information.
 * $
 */




#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/param.h>

int
sethostname(const char *name, size_t namelen)
{
	char hname[MAXHOSTNAMELEN + 1];

	memset(hname, 0, sizeof(hname));
	strncpy(hname, name, min(sizeof(hname) - 1, namelen));

	if (confstr(_CS_SET_HOSTNAME, hname, 0) == 0) {
		return -1;
	}
	return 0;
}

__SRCVERSION("sethostname.c $Rev: 153052 $");
