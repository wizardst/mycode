/*
 * $QNXLicenseC: 
 * Copyright 2007, QNX Software Systems.  
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
 * TI OMAP3530 processor with ARMv7 Cortex-A8 core
 */

#ifndef	__ARM_OMAP3530_H_INCLUDED
#define	__ARM_OMAP3530_H_INCLUDED

#define L4_35XX_BASE							0x48000000
#define L4_WK_35XX_BASE							0x48300000
#define L4_WK_OMAP_BASE							L4_WK_OMAP_BASE
#define L4_PER_35XX_BASE						0x49000000
#define L4_PER_OMAP_BASE						L4_PER_35XX_BASE
#define L4_35XX_EMU_BASE						0x54000000
#define L4_EMU_BASE								L4_35XX_EMU_BASE
#define L3_35XX_BASE							0x68000000
#define L3_OMAP_BASE							L3_35XX_BASE

#define OMAP3530_32KSYNCT_BASE					0x48320000
#define OMAP3530_CM_BASE						0x48004800
#define OMAP3530_PRM_BASE						0x48306800
#define OMAP353X_SMS_BASE						0x6C000000
#define OMAP353X_SDRC_BASE						0x6D000000
#define OMAP35XX_GPMC_BASE						0x6E000000
#define OMAP3530_SCM_BASE						0x48002000
#define OMAP3530_CTRL_BASE						OMAP3530_SCM_BASE

#define OMAP35XX_IC_BASE						0x48200000
#define OMAP35XX_IVA_INTC_BASE					0x40000000
#define IRQ_SIR_IRQ								0x0040

#define OMAP35XX_DSP_BASE						0x58000000
#define OMAP35XX_DSP_MEM_BASE					(OMAP35XX_DSP_BASE + 0x0)
#define OMAP35XX_DSP_IPI_BASE					(OMAP35XX_DSP_BASE + 0x1000000)
#define OMAP35XX_DSP_MMU_BASE					(OMAP35XX_DSP_BASE + 0x2000000)

/* 
 * System Control module
 */
#define	OMAP3530_SYSCTL_BASE					0x48002000
#define	OMAP3530_SYSCTL_SIZE					0x1000

/* 
 * System Control Registers, offset from base
 */
#define	OMAP3530_SYSCTL_REVISION				0x000
#define	OMAP3530_SYSCTL_SYSCONFIG				0x010
#define	OMAP3530_SYSCTL_PADCONF(x)				(0x030 + (x) * 4)
#define	OMAP3530_SYSCTL_PADCONF_OFF				0x270
#define	OMAP3530_SYSCTL_DEVCONF0				0x274
#define	OMAP3530_SYSCTL_MEM_DFTRW0				0x278
#define	OMAP3530_SYSCTL_MEM_DFTRW1				0x27C
#define	OMAP3530_SYSCTL_MSUSPENDMUX_0			0x290
#define	OMAP3530_SYSCTL_MSUSPENDMUX_1			0x294
#define	OMAP3530_SYSCTL_MSUSPENDMUX_2			0x298
#define	OMAP3530_SYSCTL_MSUSPENDMUX_3			0x29C
#define	OMAP3530_SYSCTL_MSUSPENDMUX_4			0x2A0
#define	OMAP3530_SYSCTL_MSUSPENDMUX_5			0x2A4
#define	OMAP3530_SYSCTL_SEC_CTRL				0x2B0
#define	OMAP3530_SYSCTL_DEVCONF1				0x2D8
#define	OMAP3530_SYSCTL_CSIRXFE					0x2DC
#define	OMAP3530_SYSCTL_SEC_STATUS				0x2E0
#define	OMAP3530_SYSCTL_SEC_ERR_STATUS			0x2E4
#define	OMAP3530_SYSCTL_SEC_ERR_STATUS_DEBUG	0x2E8
#define	OMAP3530_SYSCTL_STATUS					0x2F0
#define	OMAP3530_SYSCTL_GENERAL_PURPOSE_STATUS	0x2F4
#define	OMAP3530_SYSCTL_RPUB_KEY_H_0			0x300
#define OMAP3530_SYSCTL_RPUB_KEY_H_1			0x304
#define	OMAP3530_SYSCTL_RPUB_KEY_H_2			0x308
#define	OMAP3530_SYSCTL_RPUB_KEY_H_3			0x30C
#define	OMAP3530_SYSCTL_RPUB_KEY_H_4			0x310
#define	OMAP3530_SYSCTL_RAND_KEY_0				0x318
#define	OMAP3530_SYSCTL_RAND_KEY_1				0x31C
#define	OMAP3530_SYSCTL_RAND_KEY_2				0x320
#define	OMAP3530_SYSCTL_RAND_KEY_3				0x324
#define	OMAP3530_SYSCTL_CUST_KEY_0				0x328
#define	OMAP3530_SYSCTL_CUST_KEY_1				0x32C
#define	OMAP3530_SYSCTL_CUST_KEY_2				0x330
#define	OMAP3530_SYSCTL_CUST_KEY_3				0x334
#define	OMAP3530_SYSCTL_TEST_KEY_0				0x338
#define	OMAP3530_SYSCTL_TEST_KEY_1				0x33C
#define	OMAP3530_SYSCTL_TEST_KEY_2				0x340
#define	OMAP3530_SYSCTL_TEST_KEY_3				0x344
#define	OMAP3530_SYSCTL_TEST_KEY_4				0x348
#define	OMAP3530_SYSCTL_TEST_KEY_5				0x34C
#define	OMAP3530_SYSCTL_TEST_KEY_6				0x350
#define	OMAP3530_SYSCTL_TEST_KEY_7				0x354
#define	OMAP3530_SYSCTL_TEST_KEY_8				0x358
#define	OMAP3530_SYSCTL_TEST_KEY_9				0x35C
#define	OMAP3530_SYSCTL_TEST_KEY_10				0x360
#define	OMAP3530_SYSCTL_TEST_KEY_11				0x364
#define	OMAP3530_SYSCTL_TEST_KEY_12				0x368
#define	OMAP3530_SYSCTL_TEST_KEY_13				0x36C

/* 
 * Power, reset and clock management module
 */
#define	OMAP3530_PRCM_BASE						0x48004000
#define	OMAP3530_PRCM_SIZE						0x2000

/* 
 * Power, reset and Clock management Registers
 */
#define	OMAP3530_PRCM_IVA2_CM 					0x48004000 
#define	OMAP3530_PRCM_OCP_SYSREGS_CM 			0x48004800 
#define	OMAP3530_PRCM_MPU_CM 					0x48004900 
#define	OMAP3530_PRCM_CORE_CM 					0x48004A00 
#define	OMAP3530_PRCM_SGX_CM 					0x48004B00 
#define	OMAP3530_PRCM_WKUP_CM 					0x48004C00 
#define	OMAP3530_PRCM_CCR_CM 					0x48004D00 
#define	OMAP3530_PRCM_DSS_CM 					0x48004E00 
#define	OMAP3530_PRCM_CAM_CM 					0x48004F00 
#define	OMAP3530_PRCM_PER_CM 					0x48005000 
#define	OMAP3530_PRCM_EMU_CM 					0x48005100 
#define	OMAP3530_PRCM_GR_CM 					0x48005200 
#define	OMAP3530_PRCM_NEON_CM 					0x48005300 
#define	OMAP3530_PRCM_USBHOST_CM 				0x48005400

/* Turn all Clocks ON */
#define OMAP3530_FCK_IVA2_ON					0x00000001
#define OMAP3530_FCK_CORE1_ON					0x43fffe00
#define OMAP3530_FCK_CORE3_ON					0x00000007
#define OMAP3530_ICK_CORE1_ON					0x7ffffed2
#define OMAP3530_ICK_CORE2_ON					0x0000001f
#define OMAP3530_ICK_CORE3_ON					0x00000004
#define	OMAP3530_FCK_WKUP_ON					0x000002e9
#define OMAP3530_ICK_WKUP_ON					0x0000023f
#define OMAP3530_FCK_DSS_ON						0x00000005 /* tv+dss1 (not dss2) */
#define OMAP3530_ICK_DSS_ON						0x00000001
#define OMAP3530_FCK_CAM_ON						0x00000001
#define OMAP3530_ICK_CAM_ON						0x00000001
#define OMAP3530_FCK_PER_ON						0x0003ffff
#define OMAP3530_ICK_PER_ON						0x0003ffff
	
/* Module offsets from both CM_BASE & PRM_BASE */
/* Technically OCP_MOD is 35xx only, and PLL_MOD is CCR_MOD on 3530 */
#define OMAP3530_OCP_MOD						0x000
#define OMAP3530_MPU_MOD						0x100
#define OMAP3530_CORE_MOD						0x200
#define OMAP3530_GFX_MOD						0x300
#define OMAP3530_WKUP_MOD						0x400
#define OMAP3530_PLL_MOD						0x500

/* IVA2_CM Register */
#define	OMAP3530_CM_FCLKEN_IVA2					0x0000	
#define	OMAP3530_CM_CLKEN_PLL_IVA2				0x0004	
#define	OMAP3530_CM_IDLEST_IVA2					0x0020	
#define	OMAP3530_CM_IDLEST_PLL_IVA2				0x0024	
#define	OMAP3530_CM_AUTOIDLE_PLL_IVA2			0x0034	
#define	OMAP3530_CM_CLKSEL1_PLL_IVA2			0x0040	
#define	OMAP3530_CM_CLKSEL2_PLL_IVA2			0x0044	
#define	OMAP3530_CM_CLKSTCTRL_IVA2				0x0048
#define	OMAP3530_CM_CLKSTST_IVA2				0x004C

/* OCP_System_Registers_CM Register */
#define	OMAP3530_CM_REVISION					0x0000
#define	OMAP3530_CM_SYSCONFIG					0x0010

/* MPU_CM Register */
#define	OMAP3530_CM_CLKEN_PLL_MPU				0x0004
#define	OMAP3530_CM_IDLEST_MPU					0x0020
#define	OMAP3530_CM_IDLEST_PLL_MPU				0x0024
#define	OMAP3530_CM_AUTOIDLE_PLL_MPU			0x0034
#define	OMAP3530_CM_CLKSEL1_PLL_MPU				0x0040
#define	OMAP3530_CM_CLKSEL2_PLL_MPU				0x0044
#define	OMAP3530_CM_CLKSTCTRL_MPU				0x0048
#define	OMAP3530_CM_CLKSTST_MPU					0x004C

/* CORE_CM Register */
#define	OMAP3530_CM_FCLKEN1_CORE				0x0000
#define	OMAP3530_CM_FCLKEN3_CORE				0x0008
#define	OMAP3530_CM_ICLKEN1_CORE				0x0010
#define	OMAP3530_CM_ICLKEN2_CORE				0x0014
#define	OMAP3530_CM_ICLKEN3_CORE				0x0018
#define	OMAP3530_CM_IDLEST1_CORE				0x0020
#define	OMAP3530_CM_IDLEST2_CORE				0x0024
#define	OMAP3530_CM_IDLEST3_CORE				0x0028
#define	OMAP3530_CM_AUTOIDLE1_CORE				0x0030
#define	OMAP3530_CM_AUTOIDLE2_CORE				0x0034
#define	OMAP3530_CM_AUTOIDLE3_CORE				0x0038
#define	OMAP3530_CM_CLKSEL_CORE				    0x0040
#define	OMAP3530_CM_CLKSTCTRL_CORE				0x0048
#define	OMAP3530_CM_CLKSTST_CORE				0x004C

/* SGX_CM Register */
#define	OMAP3530_CM_FCLKEN_SGX					0x0000
#define	OMAP3530_CM_ICLKEN_SGX					0x0010
#define	OMAP3530_CM_IDLEST_SGX					0x0020
#define	OMAP3530_CM_CLKSEL_SGX					0x0040
#define	OMAP3530_CM_SLEEPDEP_SGX				0x0044
#define	OMAP3530_CM_CLKSTCTRL_SGX				0x0048
#define	OMAP3530_CM_CLKSTST_SGX					0x004C

/* WKUP_CM Register */
#define	OMAP3530_CM_FCLKEN_WKUP					0x0000
#define	OMAP3530_CM_ICLKEN_WKUP					0x0010
#define	OMAP3530_CM_IDLEST_WKUP					0x0020
#define	OMAP3530_CM_AUTOIDLE_WKUP				0x0030
#define	OMAP3530_CM_CLKSEL_WKUP					0x0040

/* Clock_Control_Registers_CM Register */
#define	OMAP3530_CM_CLKEN_PLL					0x0000
#define	OMAP3530_CM_CLKEN2_PLL					0x0004
#define	OMAP3530_CM_IDLEST_CKGEN				0x0020
#define	OMAP3530_CM_IDLEST2_CKGEN				0x0024
#define	OMAP3530_CM_AUTOIDLE_PLL				0x0030
#define	OMAP3530_CM_AUTOIDLE2_PLL				0x0034
#define	OMAP3530_CM_CLKSEL1_PLL					0x0040
#define	OMAP3530_CM_CLKSEL2_PLL					0x0044
#define	OMAP3530_CM_CLKSEL3_PLL					0x0048
#define	OMAP3530_CM_CLKSEL4_PLL					0x004C
#define	OMAP3530_CM_CLKSEL5_PLL					0x0050
#define	OMAP3530_CM_CLKOUT_CTRL					0x0070

/* DSS_CM Register */
#define	OMAP3530_CM_FCLKEN_DSS					0x0000
#define	OMAP3530_CM_ICLKEN_DSS					0x0010
#define	OMAP3530_CM_IDLEST_DSS					0x0020
#define	OMAP3530_CM_AUTOIDLE_DSS				0x0030
#define	OMAP3530_CM_CLKSEL_DSS					0x0040
#define	OMAP3530_CM_SLEEPDEP_DSS				0x0044
#define	OMAP3530_CM_CLKSTCTRL_DSS				0x0048
#define	OMAP3530_CM_CLKSTST_DSS					0x004C

/* CAM_CM Register */
#define	OMAP3530_CM_FCLKEN_CAM					0x0000
#define	OMAP3530_CM_ICLKEN_CAM					0x0010
#define	OMAP3530_CM_IDLEST_CAM					0x0020
#define	OMAP3530_CM_AUTOIDLE_CAM				0x0030
#define	OMAP3530_CM_CLKSEL_CAM					0x0040
#define	OMAP3530_CM_SLEEPDEP_CAM				0x0044
#define	OMAP3530_CM_CLKSTCTRL_CAM				0x0048
#define	OMAP3530_CM_CLKSTST_CAM					0x004C

/* PER_CM Register */
#define	OMAP3530_CM_FCLKEN_PER					0x0000
#define	OMAP3530_CM_ICLKEN_PER					0x0010
#define	OMAP3530_CM_IDLEST_PER					0x0020
#define	OMAP3530_CM_AUTOIDLE_PER				0x0030
#define	OMAP3530_CM_CLKSEL_PER					0x0040
#define	OMAP3530_CM_SLEEPDEP_PER				0x0044
#define	OMAP3530_CM_CLKSTCTRL_PER				0x0048
#define	OMAP3530_CM_CLKSTST_PER					0x004C

/* EMU_CM Register */
#define	OMAP3530_CM_CLKSEL1_EMU					0x0040
#define	OMAP3530_CM_CLKSTCTRL_EMU				0x0048
#define	OMAP3530_CM_CLKSTST_EMU					0x004C
#define	OMAP3530_CM_CLKSEL2_EMU					0x0050
#define	OMAP3530_CM_CLKSEL3_EMU					0x0054

/* Global_Registers_CM Register */
#define	OMAP3530_CM_POLCTRL						0x009C

/* NEON_CM Register */
#define	OMAP3530_CM_IDLEST_NEON					0x0020
#define	OMAP3530_CM_CLKSTCTRL_NEON				0x0048

/* USBHOST_CM Register */
#define	OMAP3530_CM_FCLKEN_USBHOST				0x0000
#define	OMAP3530_CM_ICLKEN_USBHOST				0x0010
#define	OMAP3530_CM_IDLEST_USBHOST				0x0020
#define	OMAP3530_CM_AUTOIDLE_USBHOST			0x0030
#define	OMAP3530_CM_SLEEPDEP_USBHOST			0x0044
#define	OMAP3530_CM_CLKSTCTRL_USBHOST			0x0048
#define	OMAP3530_CM_CLKSTST_USBHOST				0x004C

/* PRCM */
#define OMAP35XX_CM_FCLKEN_IVA2      			0x48004000
#define OMAP35XX_CM_CLKEN_PLL_IVA2   			0x48004004
#define OMAP35XX_CM_IDLEST_PLL_IVA2  			0x48004024
#define OMAP35XX_CM_CLKSEL1_PLL_IVA2 			0x48004040
#define OMAP35XX_CM_CLKSEL2_PLL_IVA2 			0x48004044
#define OMAP35XX_CM_CLKEN_PLL_MPU    			0x48004904
#define OMAP35XX_CM_IDLEST_PLL_MPU   			0x48004924
#define OMAP35XX_CM_CLKSEL1_PLL_MPU  			0x48004940
#define OMAP35XX_CM_CLKSEL2_PLL_MPU 			0x48004944
#define OMAP35XX_CM_FCLKEN1_CORE     			0x48004a00
#define OMAP35XX_CM_FCLKEN3_CORE     			0x48004a08
#define OMAP35XX_CM_ICLKEN1_CORE     			0x48004a10
#define OMAP35XX_CM_ICLKEN2_CORE     			0x48004a14
#define OMAP35XX_CM_ICLKEN3_CORE     			0x48004a18
#define OMAP35XX_CM_CLKSEL_CORE      			0x48004a40
#define OMAP35XX_CM_FCLKEN_GFX      			0x48004b00
#define OMAP35XX_CM_ICLKEN_GFX       			0x48004b10
#define OMAP35XX_CM_CLKSEL_GFX       			0x48004b40
#define OMAP35XX_CM_FCLKEN_WKUP      			0x48004c00
#define OMAP35XX_CM_ICLKEN_WKUP      			0x48004c10
#define OMAP35XX_CM_CLKSEL_WKUP      			0x48004c40
#define OMAP35XX_CM_IDLEST_WKUP      			0x48004c20
#define OMAP35XX_CM_CLKEN_PLL        			0x48004d00
#define OMAP35XX_CM_IDLEST_CKGEN     			0x48004d20
#define OMAP35XX_CM_CLKSEL1_PLL      			0x48004d40
#define OMAP35XX_CM_CLKSEL2_PLL      			0x48004d44
#define OMAP35XX_CM_CLKSEL3_PLL      			0x48004d48
#define OMAP35XX_CM_FCLKEN_DSS       			0x48004e00
#define OMAP35XX_CM_ICLKEN_DSS       			0x48004e10
#define OMAP35XX_CM_CLKSEL_DSS       			0x48004e40
#define OMAP35XX_CM_FCLKEN_CAM       			0x48004f00
#define OMAP35XX_CM_ICLKEN_CAM      			0x48004f10
#define OMAP35XX_CM_CLKSEL_CAM       			0x48004F40
#define OMAP35XX_CM_FCLKEN_PER       			0x48005000
#define OMAP35XX_CM_ICLKEN_PER       			0x48005010
#define OMAP35XX_CM_CLKSEL_PER       			0x48005040
#define OMAP35XX_CM_CLKSEL1_EMU      			0x48005140

/* CM_IDLEST_MPU */
#define OMAP3530_ST_MPU							(1 << 0)

/* CM_CLKSEL1_PLL_MPU */
#define OMAP3530_MPU_CLK_SRC_SHIFT				19
#define OMAP3530_MPU_CLK_SRC_MASK				(0x3 << 19)
#define OMAP3530_MPU_DPLL_MULT_SHIFT			8
#define OMAP3530_MPU_DPLL_MULT_MASK				(0x7ff << 8)
#define OMAP3530_MPU_DPLL_DIV_SHIFT				0
#define OMAP3530_MPU_DPLL_DIV_MASK				(0x7f << 0)

/* CM_CLKSEL2_PLL_MPU */
#define OMAP3530_MPU_DPLL_CLKOUT_DIV_SHIFT		0
#define OMAP3530_MPU_DPLL_CLKOUT_DIV_MASK		(0x1f << 0)

/* CM_CLKSEL1_PLL */
#define OMAP35XX_DPLL_CLKOUT_DIV_SHIFT          27
#define OMAP35XX_DPLL_CLKOUT_DIV_MASK           (0x1f << 27)
#define OMAP35XX_DPLL_MULT_SHIFT                16
#define OMAP35XX_DPLL_MULT_MASK                 (0x7ff << 12)
#define OMAP35XX_DPLL_DIV_SHIFT                 8
#define OMAP35XX_DPLL_DIV_MASK                  (0x7f << 8)
#define OMAP35XX_96M_SOURCE_SHIFT               6
#define OMAP35XX_96M_SOURCE                     (1 << 6)
#define OMAP35XX_54M_SOURCE_SHIFT               5
#define OMAP35XX_54M_SOURCE                     (1 << 5)
#define OMAP35XX_48M_SOURCE_SHIFT               3
#define OMAP35XX_48M_SOURCE                     (1 << 3)

/*
 * Watchdog Timer
 */
#define	OMAP3530_WDT1_BASE						0x4830C000
#define	OMAP3530_WDT2_BASE						0x48314000
#define	OMAP3530_WDT3_BASE						0x49030000
#define	OMAP3530_WDT2_WKUP_BASE					0x54714000
#define	OMAP3530_WDT_SIZE						0x1000

/*
 * Watchdog Timer Registers, offset from base
 */
#define	OMAP3530_WD_SYSCONFIG		0x10
#define	OMAP3530_WD_SYSSTATUS		0x14
#define	OMAP3530_WD_WISR			0x18
#define	OMAP3530_WD_WIER			0x1C
#define	OMAP3530_WCLR				0x24
#define	OMAP3530_WCRR				0x28
#define	OMAP3530_WLDR				0x2C
#define	OMAP3530_WTGR				0x30
#define	OMAP3530_WWPS				0x34
#define	OMAP3530_WSPR				0x48


/*
 * General-Purpose Timer
 */
#define	OMAP3530_GPT1_BASE			0x48318000
#define	OMAP3530_GPT2_BASE			0x49032000
#define	OMAP3530_GPT3_BASE			0x49034000
#define	OMAP3530_GPT4_BASE			0x49036000
#define	OMAP3530_GPT5_BASE			0x49038000
#define	OMAP3530_GPT6_BASE			0x4903A000
#define	OMAP3530_GPT7_BASE			0x4903C000
#define	OMAP3530_GPT8_BASE			0x4903E000
#define	OMAP3530_GPT9_BASE			0x49040000
#define	OMAP3530_GPT10_BASE			0x48086000
#define	OMAP3530_GPT11_BASE			0x48088000
#define	OMAP3530_GPT12_BASE			0x48304000
#define	OMAP3530_GPT1_WKUP_BASE		0x54718000
#define	OMAP3530_GPT_SIZE			0x1000

/*
 * General-Purpose Timer Registers, offset from base
 */
/* Defs for GPTIMER5 to GPTIMER8 */
#define	OMAP3530_GPT_TIOCP_CFG		0x10
#define	OMAP3530_GPT_TISTAT			0x14
#define	OMAP3530_GPT_TISR			0x18
#define	OMAP3530_GPT_TIER			0x1C
#define	OMAP3530_GPT_TWER			0x20
#define	OMAP3530_GPT_TCLR			0x24
#define	OMAP3530_GPT_TCRR			0x28
#define	OMAP3530_GPT_TLDR			0x2C
#define	OMAP3530_GPT_TTGR			0x30
#define	OMAP3530_GPT_TWPS			0x34
#define	OMAP3530_GPT_TMAR			0x38
#define	OMAP3530_GPT_TCAR1			0x3C
#define	OMAP3530_GPT_TSICR			0x40
#define	OMAP3530_GPT_TCAR2			0x44

/* Extra defs for GPTIMER1 to GPTIMER4 Register, and for GPTIMER9 to GPTIMER12 */
#define	OMAP3530_GPT_TPIR			0x048
#define	OMAP3530_GPT_TNIR			0x04C
#define	OMAP3530_GPT_TCVR			0x050
#define	OMAP3530_GPT_TOCR			0x054
#define	OMAP3530_GPT_TOWR			0x058

/*
 * SDMA4
 */
#define OMAP3530_DMA4_GENERAL_BASE           0x48056000
#define OMAP3530_DMA4_GENERAL_REGION_LEN	 0x80

#define OMAP3530_DMA4_IRQSTATUS_L0           0x08 
#define OMAP3530_DMA4_IRQSTATUS_L1           0x0c 
#define OMAP3530_DMA4_IRQSTATUS_L2           0x10 
#define OMAP3530_DMA4_IRQSTATUS_L3           0x14 

#define OMAP3530_DMA4_IRQENABLE_L0           0x18 
#define OMAP3530_DMA4_IRQENABLE_L1           0x1c 
#define OMAP3530_DMA4_IRQENABLE_L2           0x20 
#define OMAP3530_DMA4_IRQENABLE_L3           0x24 

#define OMAP3530_DMA4_SYSSTATUS              0x28 
#define OMAP3530_DMA4_OCP_SYSCONFIG          0x2C 

#define OMAP3530_DMA4_CAPS_0_REG             0x64 
#define OMAP3530_DMA4_CAPS_2_REG             0x6c 
#define OMAP3530_DMA4_CAPS_3_REG             0x70 
#define OMAP3530_DMA4_CAPS_4_REG             0x74 

#define OMAP3530_DMA4_GCR_REG                0x78 
	
#define GCR_ARBITRATION_RATE				0xff0000
#define DMA_DEFAULT_FIFO_DEPTH     			0x10

#define	OMAP3530_SDMA_IRQ			256

/*
 * USB
 */
#define	OMAP3530_USB_BASE			0x48064000
#define	OMAP3530_USB_SIZE			0x1000

/*
 * UARTs
 */
#define	OMAP3530_UART1_BASE			0x4806A000
#define	OMAP3530_UART2_BASE			0x4806C000
#define	OMAP3530_UART3_BASE			0x49020000 /* UART/IrDA/CIR */
#define	OMAP3530_UART_SIZE			0x1000

/* 
 * Interrupt Controller
 */
#define	OMAP3530_INTC_BASE			0x48200000
#define	OMAP3530_INTC_SIZE			0x280

/* 
 * Interrupt controller registers,
 * offset from base
 */
#define	OMAP3530_INTC_IRQ_PRIORITY	0x060
#define	OMAP3530_INTC_FIQ_PRIORITY	0x064
#define	OMAP3530_INTC_THRESHOLD		0x068

/*
 * GPIOs 
 */
#define	OMAP3530_GPIO1_BASE			0x48310000
#define	OMAP3530_GPIO2_BASE			0x49050000
#define	OMAP3530_GPIO3_BASE			0x49052000
#define	OMAP3530_GPIO4_BASE			0x49054000
#define	OMAP3530_GPIO5_BASE			0x49056000
#define	OMAP3530_GPIO6_BASE			0x49058000
#define	OMAP3530_GPIO_SIZE			0x1000

/*
 * SMS
 */
#define	OMAP3530_SMS_BASE			0x68008000
#define	OMAP3530_SMS_SIZE			0x10000


/*
 * SDRC
 */
#define	OMAP3530_SDRC_BASE			0x6D000000
#define	OMAP3530_SDRC_SIZE			0x10000


/*
 * GPMC
 */
#define	OMAP3530_GPMC_BASE			0x6E000000
#define	OMAP3530_GPMC_SIZE			0x1000000

/*
 * GPMC registers, offset from base address
 */
#define	OMAP3530_GPMC_BCH_RESULT0_0	0x240
#define	OMAP3530_GPMC_BCH_RESULT0_1	0x250
#define	OMAP3530_GPMC_BCH_RESULT0_2	0x260
#define	OMAP3530_GPMC_BCH_RESULT0_3	0x270
#define	OMAP3530_GPMC_BCH_RESULT0_4	0x280
#define	OMAP3530_GPMC_BCH_RESULT0_5	0x290
#define	OMAP3530_GPMC_BCH_RESULT0_6	0x2A0
#define	OMAP3530_GPMC_BCH_RESULT0_7	0x2B0
#define	OMAP3530_GPMC_BCH_RESULT1_0	0x244
#define	OMAP3530_GPMC_BCH_RESULT1_1	0x254
#define	OMAP3530_GPMC_BCH_RESULT1_2	0x264
#define	OMAP3530_GPMC_BCH_RESULT1_3	0x274
#define	OMAP3530_GPMC_BCH_RESULT1_4	0x284
#define	OMAP3530_GPMC_BCH_RESULT1_5	0x294
#define	OMAP3530_GPMC_BCH_RESULT1_6	0x2A4
#define	OMAP3530_GPMC_BCH_RESULT1_7	0x2B4
#define	OMAP3530_GPMC_BCH_RESULT2_0	0x248
#define	OMAP3530_GPMC_BCH_RESULT2_1	0x258
#define	OMAP3530_GPMC_BCH_RESULT2_2	0x268
#define	OMAP3530_GPMC_BCH_RESULT2_3	0x278
#define	OMAP3530_GPMC_BCH_RESULT2_4	0x288
#define	OMAP3530_GPMC_BCH_RESULT2_5	0x298
#define	OMAP3530_GPMC_BCH_RESULT2_6	0x2A8
#define	OMAP3530_GPMC_BCH_RESULT2_7	0x2B8
#define	OMAP3530_GPMC_BCH_RESULT3_0	0x24C
#define	OMAP3530_GPMC_BCH_RESULT3_1	0x25C
#define	OMAP3530_GPMC_BCH_RESULT3_2	0x26C
#define	OMAP3530_GPMC_BCH_RESULT3_3	0x27C
#define	OMAP3530_GPMC_BCH_RESULT3_4	0x28C
#define	OMAP3530_GPMC_BCH_RESULT3_5	0x29C
#define	OMAP3530_GPMC_BCH_RESULT3_6	0x2AC
#define	OMAP3530_GPMC_BCH_RESULT3_7	0x2BC
#define	OMAP3530_GPMC_BCH_SWDATA	0x2D0

/*
 * L4 Peripherals - L4 Wakeup and L4 Core now
 */
#define OMAP35XX_CORE_L4_IO_BASE	0x48000000
#define OMAP35XX_WAKEUP_L4_IO_BASE	0x48300000

/* Clock_Control_Registers_PRM */
#define OMAP35XX_PRM_CLKSEL         0x48306d40

/* Global_Registers_PRM */
#define OMAP35XX_GR_PRM_BASE        0x48307200
#define OMAP35XX_GR_PRM_SIZE        0x100

#define OMAP35XX_GR_PRM_RSTCTRL     0x50

#define OMAP35XX_PRM_RSTCTRL        0x48307250
#define OMAP35XX_PRM_CLKSRC_CTRL    0x48307270

#define OMAP35XX_L4_PER				0x49000000

#define OMAP35XX_L4_IO_BASE			OMAP35XX_CORE_L4_IO_BASE

/* Fuse bits indicating max clock rate */
#define OMAP35XX_720M_DEVICE_ID               0x4830a20c
#define OMAP35XX_720M_DEVICE_ID_SKUID_MASK          0x0f
#define OMAP35XX_DEVICE_IS_720M_CAPABLE             0x08

/* omap37xx device id registers */
#define OMAP_CONTROL_ID_CODE		0x4830a204
#define OMAP37XX_DEVICE_FAMILY		0x0b89102f
#define OMAP37XX_DEVICE_FAMILY_MASK	0x0fffffff
#define OMAP37XX_CONT_DEV_STAT_REG	0x4800244c
#define OMAP37XX_DEVICE_ID_MASK		0x0f00
#define OMAP37XX_1000M_CAPABLE		0x0e00
#define OMAP37XX_800M_CAPABLE		0x0c00

/* 32KTIMER */
#define OMAP35XX_SYNC_32KTIMER_BASE	0x48320000

/* I2C base */
#define OMAP35XX_I2C_BASE1			(OMAP35XX_CORE_L4_IO_BASE + 0x70000)
#define OMAP35XX_I2C_BASE2			(OMAP35XX_CORE_L4_IO_BASE + 0x72000)
#define OMAP35XX_I2C_BASE3			(OMAP35XX_CORE_L4_IO_BASE + 0x60000)

#define OMAP3530_I2C_1_IRQ           56	/*Interrupt number for I2C 1 */
#define OMAP3530_I2C_2_IRQ           57	/*Interrupt number for I2C 2 */
#define OMAP3530_I2C_3_IRQ           61	/*Interrupt number for I2C 3 */

/* Stuff on L3 Interconnect */
#define OMAP35XX_OMAP35XX_SMX_APE_BASE			0x68000000

/* SMX-APE */
#define OMAP35XX_PM_RT_APE_BASE_ADDR_ARM		(OMAP35XX_SMX_APE_BASE + 0x10000)
#define OMAP35XX_PM_GPMC_BASE_ADDR_ARM			(OMAP35XX_SMX_APE_BASE + 0x12400)
#define OMAP35XX_PM_OCM_RAM_BASE_ADDR_ARM		(OMAP35XX_SMX_APE_BASE + 0x12800)
#define OMAP35XX_PM_OCM_ROM_BASE_ADDR_ARM		(OMAP35XX_SMX_APE_BASE + 0x12C00)
#define OMAP35XX_PM_IVA2_BASE_ADDR_ARM			(OMAP35XX_SMX_APE_BASE + 0x14000)

#define OMAP35XX_RT_REQ_INFO_PERMISSION_1		(OMAP35XX_PM_RT_APE_BASE_ADDR_ARM + 0x68)
#define OMAP35XX_RT_READ_PERMISSION_0			(OMAP35XX_PM_RT_APE_BASE_ADDR_ARM + 0x50)
#define OMAP35XX_RT_WRITE_PERMISSION_0			(OMAP35XX_PM_RT_APE_BASE_ADDR_ARM + 0x58)
#define OMAP35XX_RT_ADDR_MATCH_1				(OMAP35XX_PM_RT_APE_BASE_ADDR_ARM + 0x60)

#define OMAP35XX_GPMC_REQ_INFO_PERMISSION_0		(OMAP35XX_PM_GPMC_BASE_ADDR_ARM + 0x48)
#define OMAP35XX_GPMC_READ_PERMISSION_0			(OMAP35XX_PM_GPMC_BASE_ADDR_ARM + 0x50)
#define OMAP35XX_GPMC_WRITE_PERMISSION_0		(OMAP35XX_PM_GPMC_BASE_ADDR_ARM + 0x58)

#define OMAP35XX_OCM_REQ_INFO_PERMISSION_0		(OMAP35XX_PM_OCM_RAM_BASE_ADDR_ARM + 0x48)
#define OMAP35XX_OCM_READ_PERMISSION_0			(OMAP35XX_PM_OCM_RAM_BASE_ADDR_ARM + 0x50)
#define OMAP35XX_OCM_WRITE_PERMISSION_0			(OMAP35XX_PM_OCM_RAM_BASE_ADDR_ARM + 0x58)
#define OMAP35XX_OCM_ADDR_MATCH_2				(OMAP35XX_PM_OCM_RAM_BASE_ADDR_ARM + 0x80)

#define OMAP35XX_IVA2_REQ_INFO_PERMISSION_0		(OMAP35XX_PM_IVA2_BASE_ADDR_ARM + 0x48)
#define OMAP35XX_IVA2_READ_PERMISSION_0			(OMAP35XX_PM_IVA2_BASE_ADDR_ARM + 0x50)
#define OMAP35XX_IVA2_WRITE_PERMISSION_0		(OMAP35XX_PM_IVA2_BASE_ADDR_ARM + 0x58)

#define OMAP35XX_IVA2_REQ_INFO_PERMISSION_1		(OMAP35XX_PM_IVA2_BASE_ADDR_ARM + 0x68)
#define OMAP35XX_IVA2_READ_PERMISSION_1			(OMAP35XX_PM_IVA2_BASE_ADDR_ARM + 0x70)
#define OMAP35XX_IVA2_WRITE_PERMISSION_1		(OMAP35XX_PM_IVA2_BASE_ADDR_ARM + 0x78)

#define OMAP35XX_IVA2_REQ_INFO_PERMISSION_2		(OMAP35XX_PM_IVA2_BASE_ADDR_ARM + 0x88)
#define OMAP35XX_IVA2_READ_PERMISSION_2			(OMAP35XX_PM_IVA2_BASE_ADDR_ARM + 0x90)
#define OMAP35XX_IVA2_WRITE_PERMISSION_2		(OMAP35XX_PM_IVA2_BASE_ADDR_ARM + 0x98)

#define OMAP35XX_IVA2_REQ_INFO_PERMISSION_3		(OMAP35XX_PM_IVA2_BASE_ADDR_ARM + 0xA8)
#define OMAP35XX_IVA2_READ_PERMISSION_3			(OMAP35XX_PM_IVA2_BASE_ADDR_ARM + 0xB0)
#define OMAP35XX_IVA2_WRITE_PERMISSION_3		(OMAP35XX_PM_IVA2_BASE_ADDR_ARM + 0xB8)

/* CONTROL */
#define OMAP35XX_CTRL_BASE						(OMAP35XX_L4_IO_BASE + 0x2000)

/* Register offsets of common modules */
/* Control */
#define OMAP35XX_CONTROL_STATUS					(OMAP35XX_CTRL_BASE + 0x2F0)
#define OMAP35XX_MCR							(OMAP35XX_CTRL_BASE + 0x8C)
#define OMAP35XX_CONTROL_SCALABLE_OMAP_STATUS	(OMAP35XX_CTRL_BASE + 0x44C)
#define OMAP35XX_CONTROL_SCALABLE_OMAP_OCP		(OMAP35XX_CTRL_BASE + 0x534)


#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/hardware/startup/lib/public/arm/omap3530.h $ $Rev: 716263 $")
#endif
