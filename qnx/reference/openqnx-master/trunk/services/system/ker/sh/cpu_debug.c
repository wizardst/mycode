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



/*
 *	ker/sh/cpu_debug.c
 *		for process debuger
 
 
 */
/*
	H/W debug support in SH
	Two debug channels for two independant H/W generated break point/watch point
	Currently, breakpoint and single step will be generated by TRAPA code insertion
	Watch point will be generated by the two H/W debug channels.
*/
#include "externs.h"


#undef FILE_DEBUG
/* #define FILE_DEBUG */

/*
 * This routine does enables debugging on a thread. The thread
 * flag _NTO_TF_SSTEP is also set on this thread, so this could
 * be used by the fault handler code if needed. If single stepping
 * is done throught temporary breakpoints, the temp information could
 * be stored in the cpu area off the DEBUG structure so the 
 * cpu_debug_attach_brkpts() function can install them when the
 * thread is being executed.
 * On entry:
 *   dep
 *      DEBUG structure attached to the process being debugged
 *   thp
 *      thread to debug (_NTO_TF_SSTEP) will be set if function succeeds
 * On Exit:
 *   a errno is returned, single step will only occur if EOK is returned.
 */
int rdecl
cpu_debug_sstep(DEBUG *dep, THREAD *thp) {
	#ifdef FILE_DEBUG
	kprintf("\ncpu_debug_sstep:\n");
	#endif

	return EOK;
}

/*
 * This routine is called when adding or removing breakpoints from the
 * process debug list. It allows selecting of the type of breakpoints
 * and watchpoints supported by the cpu. The breakpoints are not actually
 * written to the address space during this function, but when the process
 * is switched to via cpu_debug_attach_brkpts(). It will only be called
 * after cpu_debug_detach_brkpts() has been called, so it does not need to
 * work about this case.
 * On entry:
 *   dep
 *      DEBUG structure of process for breakpoints.
 *   bpp
 *      BREAKPT structure with breakpoint to install.
 *      
 * On exit:
 *   a errno is returned, the breakpoint will not be added unless EOK is returned.
 * 
 */
int rdecl
cpu_debug_brkpt(DEBUG *dep, BREAKPT *bpp) {
	size_t							size;

	#ifdef FILE_DEBUG
	kprintf("\ncpu_debug_brkpts:size=%d\n",bpp->brk.size);
	#endif

	if(bpp->brk.size == -1) {
		return EOK;
	}

	switch(bpp->brk.type) {
	case _DEBUG_BREAK_MODIFY:
		if(		bpp->brk.size > sizeof bpp->cpu.data.value ||
		        (size = memmgr.mapinfo(dep->process, bpp->brk.addr, NULL, NULL, 0, NULL, NULL, NULL)) == 0 ||
		        bpp->brk.size > size) {
			return EINVAL;
		}
		memcpy(bpp->cpu.data.value, (void*)bpp->brk.addr, bpp->brk.size);
		break;

	case _DEBUG_BREAK_EXEC:
		if(bpp->brk.size == 0) {
			break;
		}
		/* Fall Through */
	default:
		return EINVAL;
	}
	return EOK;
}

static void
code_modify(BREAKPT *d, unsigned new, ADDRESS* adp) {
	paddr_t paddr = d->cpu.paddr;
	uintptr_t   vaddr = d->brk.addr;
	
	// Can we access the instruction through the 1-1 area?
	if ( SH_PHYS_IN_1TO1(paddr) ) {
		// yes, we can.  That makes it easy...
		uint16_t	*p = PHYS_TO_PTR(paddr);
		*p = new;

		if(SYSP_GETCOLOR(vaddr) != SYSP_GETCOLOR(p)) {
			CacheControl(p, 2, MS_SYNC);
		}

	} else {
		// We can't access the instruction through the P1 area.  Create
		// a temporary TLB entry for it.  Run with interrupts disabled 
		// to ensure that the TLB doesn't get swapped out before we
		// get a chance to use it.  Map it in as a 4K page
		unsigned ptel = (paddr & (~(__PAGESIZE-1))) | SH_CCN_PTEL_SZ0 | SH_CCN_PTEL_V | SH_CCN_PTEL_D | SH_CCN_PTEL_PR(3);
		
		InterruptDisable();
		
		// Ensure there aren't any mappings for vaddr already in the TLBs
		tlb_flush_va( adp, vaddr, vaddr+2 );

		// Add the new map.
		sh4_update_tlb( vaddr & (~(__PAGESIZE-1)), ptel );
		
		// Modify the code
		*(uint16_t *)vaddr = new;
		
		// We clear the TLB entry so we don't leave the address writable.
		tlb_flush_va( adp, vaddr, vaddr+2 );
		
		InterruptEnable();
	}
	
	CacheControl((void *)vaddr, 2, MS_INVALIDATE_ICACHE);

}

/*
 * Plant one breakpoint.
 */
static void
one_break(BREAKPT *d, PROCESS* prp) {
	if(memmgr.vaddrinfo(prp, d->brk.addr, &d->cpu.paddr, NULL, VI_PGTBL) != PROT_NONE) {
		if(d->planted++ == 0) {

			d->cpu.data.ins = *(uint16_t *)d->brk.addr;
			code_modify(d, SH_KER_TRAP_CODE(SH_KER_TRAP_PDBREAK), prp->memory);
		}
	}
}

/*
 * This routine is called at process switch time from the kernel.
 * It is responsible for modifying the processes address space to
 * plant breakpoints. It needs to take care if the region is not
 * mapped writable, probably calling memmgr.vaddrinfo() to get
 * physical memory that it can write to. If there is no physical
 * memory there (i.e. the page hasn't been faulted in yet) it should
 * skip this breakpoint quietly. When the page is faulted in, it
 * will get another chance to plant the breakpoint and it can't
 * be referenced untill it is faulted in anyhow.
 * On entry:
 *   dep
 *      DEBUG structure of process with breakpoint list.
 */
void rdecl
cpu_debug_attach_brkpts(DEBUG *dep) {
	BREAKPT		*d;
	THREAD		*act;
	char		step = 0;
	extern uintptr_t next_instruction(CPU_REGISTERS *ctx);

	#ifdef FILE_DEBUG
	kprintf("\ncpu_debug_attach_brkpts:\n");
	#endif

	act = actives[KERNCPU];

	for(d = dep->brk; d; d = d->next) {
		#ifdef FILE_DEBUG
		kprintf("\nbreak point %x flag %x\n",d->brk.addr,d->brk.type);
		#endif

		if(d != dep->skip_brk) {
			if(d->brk.type & _DEBUG_BREAK_EXEC) {
				#ifdef FILE_DEBUG
				kprintf("\nbrk.size=%d\n",d->brk.size);
				#endif

				d->brk.size = 2;
				one_break(d, dep->process);
			} else if(d->brk.type & _DEBUG_BREAK_MODIFY) {
				step = 1;
			}
		}
	}

	if((act->flags & _NTO_TF_SSTEP) || step) {
		dep->cpu.step.brk.addr = next_instruction(&act->reg);
		#ifdef FILE_DEBUG
		kprintf("\nsingle step. addr %x\n",dep->cpu.step.brk.addr);
		#endif

		if(dep->cpu.step.brk.addr != ~0U) {
			one_break(&dep->cpu.step, dep->process);
		}
	}

}

/*
 * This routine is called at process switch time from the kernel.
 * It is responsible for modifying the processes address space to
 * remove breakpoints. It needs to take care if the region is not
 * mapped writable, probably calling memmgr.vaddrinfo() to get
 * physical memory that it can write to. It should only remove
 * things that where modified during cpu_debug_attach_brkpts().
 * On entry:
 *   dep
 *      DEBUG structure of process with breakpoint list.
 */
void rdecl
cpu_debug_detach_brkpts(DEBUG *dep) {
	BREAKPT				*d;

	#ifdef FILE_DEBUG
	kprintf("\ncpu_debug_detach_brkpts:\n");
	#endif

	if(dep->cpu.step.planted) {
		dep->cpu.step.planted = 0;
		code_modify(&dep->cpu.step, dep->cpu.step.cpu.data.ins, dep->process->memory);
	}

	for(d = dep->brk; d; d = d->next) {
		if(d != dep->skip_brk) {
			if(d->planted) {
				if(--d->planted == 0) {
					code_modify(d, d->cpu.data.ins, dep->process->memory);
				}
			}
		}
	}

}

/*
 * This routine is called to allow cpu specific modifying and identifying
 * during a fault. If it is reporting a fault, it must turn off any
 * single step that was enabled by cpu_debug_sstep. If needed, this routine
 * could scan "MODIFY" breakpoints (if they aren't done with hardware) to
 * see if they changed.
 * On entry:
 *   dep
 *      DEBUG structure attached to the process (for cpu specific information)
 *   thp
 *      thread that had the fault (KIP(thp) is the ip that had the faulting instruction)
 *   psigno
 *      Pointer to signal number (This can be modified if nessessary)
 *   psigcode
 *      Pointer to signal code (This can be modified if nessessary)
 *   pfault
 *      Pointer to fault code (This can be modified if nessessary)
 *   pflags
 *      Pointer to debug flags (_DEBUG_FLAG_*). If a data watchpoint was
 *      triggered, the corresponding _DEBUG_FLAG_TRACE_* flag should be set.
 *      If it was an execution breakpoint, _DEBUG_FLAG_ISTOP should be set.
 *      If it was a single step fault, _DEBUG_FLAGS_SSTEP should be set.
 * On Exit (non-zero):
 *   A non-zero return value, causes the fault to be ignored, and the thread
 *   will try to restart at the faulting instruction. This could be used to
 *   make watchpoints by having all the threads in a process single step, then
 *   check after each instruction for the modified memory. If nothing is modified,
 *   continue the thread so the single step occurs after the next instruction.
 * On Exit (zero):
 *   psigno
 *   psigcode
 *   psigfault
 *       These should be modified if nessessary to reflect the real values.
 *   pflags
 *       This should have all _DEBUG_FLAGS set that this fault matches
 */
int rdecl
cpu_debug_fault(DEBUG *dep, THREAD *thp, siginfo_t *info, unsigned *pflags) {

	#ifdef FILE_DEBUG
	kprintf("\ncpu_debug_fault:thp=%x,ip=%x,sr=%x,pr=%x,r11=%x,r12=%x,info=%x\n",thp,thp->reg.pc,thp->reg.sr,thp->reg.pr,thp->reg.gr[11],thp->reg.gr[12],info->si_fltno);
	#endif

	// if watchtype == singlestep and no singlestep flag set and no watchpoints changed return 1
	if(info->si_fltno == FLTBPT) {
		BREAKPT					*d;

		for(d = dep->brk; d; d = d->next) {
			if(d->brk.type & _DEBUG_BREAK_MODIFY) {
				if(memcmp((void*)d->brk.addr, d->cpu.data.value, d->brk.size)) {
					*pflags |= _DEBUG_FLAG_TRACE_MODIFY;
				}
			}
		}
	}

	if(thp->flags & _NTO_TF_SSTEP) {
		if(info->si_fltno == FLTBPT) {
			*pflags |= _DEBUG_FLAG_SSTEP;
		}
		thp->flags &= ~_NTO_TF_SSTEP;
	}

	if(info->si_fltno == FLTBPT) {
		*pflags |= _DEBUG_FLAG_TRACE_EXEC;
	}

	return 0;
}

int rdecl
cpu_debug_get_altregs(THREAD *thp, debug_altreg_t *reg) {

	return EINVAL;
}

int rdecl
cpu_debug_set_altregs(THREAD *thp, debug_altreg_t *reg) {

	return EINVAL;
}

__SRCVERSION("cpu_debug.c $Rev: 199396 $");
