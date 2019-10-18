/*
 * $QNXLicenseC:
 * Copyright 2016, QNX Software Systems.
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
 * NXP LS1043A SOCs:
 */

#ifndef __AARCH64_LS1043A_H_INCLUDED
#define __AARCH64_LS1043A_H_INCLUDED

#include "aarch64/ls10xx.h"

/*
 * System Memory Map
 */

/*
 * CCSR address map
 */

/*
 * IFC
 */
#define LS1043A_IFC_BASE        0x01530000
#define LS1043A_IFC_SIZE        0x10000

/*
 * Enhanced secured digital host controller (eSHDC)
 */
#define LS1043A_eSDHC_BASE      0x01560000
#define LS1043A_eSDHC_SIZE      0x10000

/*
 * Device configuration and pin control (DCFG)
 */
#define LS1043A_DCFG_BASE       0x01EE0000
#define LS1043A_DCFG_SIZE       0x1000
    #define LS1043A_DCFG_SVR            0xA4
        #define DCFG_SVR_REV_MASK           0xFF
        #define DCFG_SVR_MAJOR_REV_MASK     0xF0
        #define DCFG_SVR_MAJOR_REV_1        0x10
        #define DCFG_SVR_MAJOR_REV(x)       ((x & DCFG_SVR_MAJOR_REV_MASK) >> 4)
        #define DCFG_SVR_MINOR_REV_MASK     0x0F
        #define DCFG_SVR_MINOR_REV_0        0x00
        #define DCFG_SVR_MINOR_REV_1        0x01
        #define DCFG_SVR_MINOR_REV(x)       (x & DCFG_SVR_MINOR_REV_MASK)
    #define LS1043A_DCFG_RCW            0x100

/*
 * Clocking module
 */
#define LS1043A_CM_BASE         0x01EE1000
#define LS1043A_CM_SIZE         0x200
    #define LS1043A_CM_CLKCCSR          0x0
    #define LS1043A_CM_CL1KCGHWACSR     0x10
    #define LS1043A_CM_CL2KCGHWACSR     0x30
    #define LS1043A_CM_PLLC1GSR         0x800
    #define LS1043A_CM_PLLC2GSR         0x820
    #define LS1043A_CM_PLLCNGSR_CFG(__val) ((__val >> 1) & 0xFF)
    #define LS1043A_CM_CLKPCSR          0xA00
    #define LS1043A_CM_PLLPGSR          0xC00
    #define LS1043A_CM_PLLDGSR          0xC20

/*
 * I2C controllers
 */
#define LS1043A_I2C1_BASE       0x02180000
#define LS1043A_I2C2_BASE       0x02190000
#define LS1043A_I2C3_BASE       0x021A0000
#define LS1043A_I2C4_BASE       0x021B0000
#define LS1043A_I2C_SIZE        0x10000

/*
 * DUART
 */
#define LS1043A_DUART1_BASE     0x021C0500
#define LS1043A_DUART2_BASE     0x021C0600
#define LS1043A_DUART_SIZE      0x100

/*
 * GPIOs
 */
#define LS1043A_GPIO1_BASE      0x02300000
#define LS1043A_GPIO2_BASE      0x02310000
#define LS1043A_GPIO3_BASE      0x02320000
#define LS1043A_GPIO4_BASE      0x02330000
#define LS1043A_GPIO_SIZE       0x10000

/*
 * Low Power universal asynchronous receiver transmitter (LPUART)
 */
#define LS1043A_LPUART1_BASE    0x02950000
#define LS1043A_LPUART2_BASE    0x02960000
#define LS1043A_LPUART3_BASE    0x02970000
#define LS1043A_LPUART4_BASE    0x02980000
#define LS1043A_LPUART5_BASE    0x02990000
#define LS1043A_LPUART6_BASE    0x029A0000
#define LS1043A_LPUART_SIZE     0x10000

/*
 * FlexTimer module (FTM)
 */
#define LS1043A_FTM1_BASE       0x029D0000
#define LS1043A_FTM2_BASE       0x029E0000
#define LS1043A_FTM3_BASE       0x029F0000
#define LS1043A_FTM4_BASE       0x02A00000
#define LS1043A_FTM5_BASE       0x02A10000
#define LS1043A_FTM6_BASE       0x02A20000
#define LS1043A_FTM7_BASE       0x02A30000
#define LS1043A_FTM8_BASE       0x02A40000
#define LS1043A_FTM_SIZE        0x10000

/*
 * Watchdog timer
 */
#define LS1043A_WDOG1_BASE      0x02AD0000
#define LS1043A_WDOG2_BASE      0x02AE0000
#define LS1043A_WDOG3_BASE      0x02A70000
#define LS1043A_WDOG4_BASE      0x02A80000
#define LS1043A_WDOG5_BASE      0x02A90000
#define LS1043A_WDOG_SIZE       0x10000

/*
 * USB3.0 Controllers
 */
#define LS1043A_USB1_BASE       0x02F00000
#define LS1043A_USB2_BASE       0x03000000
#define LS1043A_USB3_BASE       0x03100000
#define LS1043A_USB_SIZE        0x100000

#define LS1043A_USB1_PHY_BASE   0x084F0000
#define LS1043A_USB2_PHY_BASE   0x08500000
#define LS1043A_USB3_PHY_BASE   0x08510000
#define LS1043A_USB_PHY_SIZE    0x10000

/*
 * Queue direct memory access controller (qDMA)
 */
#define LS1043A_QDMA_BASE       0x08380000
#define LS1043A_QDMA_SIZE       0x100000

/*
 * IRQ assignments
 */
#define LS1043A_IRQ_FTM5        32
#define LS1043A_IRQ_FTM6        33
#define LS1043A_IRQ_TMU_ALARM   65      /* Thermal monitor unit alarm */
#define LS1043A_IRQ_TMU_CALARM  66      /* Thermal monitor unit critical alarm */
#define LS1043A_IRQ_qDMA_INT0   71      /* Virtualized qDMA INT0 */
#define LS1043A_IRQ_qDMA_INT1   72      /* Virtualized qDMA INT1 */
#define LS1043A_IRQ_qDMA_INT2   73      /* Virtualized qDMA INT2 */
#define LS1043A_IRQ_qDMA_INT3   74      /* Virtualized qDMA INT3 */
#define LS1043A_IRQ_IFC         75
#define LS1043A_IRQ_FMAN        76      /* Frame manager */
#define LS1043A_IRQ_FQBMAN_ERR  77      /* FMAN/QMAN/BMAN error */
#define LS1043A_IRQ_MDIO1       78      /* MDIO management interrupt 1 (1G) */
#define LS1043A_IRQ_MDIO2       79      /* MDIO management interrupt 2 (10 G)(XFI) */
#define LS1043A_IRQ_LPUART1     80
#define LS1043A_IRQ_LPUART2 81
#define LS1043A_IRQ_LPUART3     82
#define LS1043A_IRQ_LPUART4     83
#define LS1043A_IRQ_LPUART5     84
#define LS1043A_IRQ_LPUART6     85
#define LS1043A_IRQ_DUART1      86
#define LS1043A_IRQ_DUART2      87
#define LS1043A_IRQ_I2C1        88
#define LS1043A_IRQ_I2C2        89
#define LS1043A_IRQ_I2C3        90
#define LS1043A_IRQ_I2C4        91
#define LS1043A_IRQ_USB1        92
#define LS1043A_IRQ_USB2        93
#define LS1043A_IRQ_eSDHC       94
#define LS1043A_IRQ_USB3        95
#define LS1043A_IRQ_SPI1        96
#define LS1043A_IRQ_GPIO1       98
#define LS1043A_IRQ_GPIO2       99
#define LS1043A_IRQ_GPIO3       100
#define LS1043A_IRQ_SATA        101
#define LS1043A_IRQ_EPU         102
#define LS1043A_IRQ_SEC_QUE1    103
#define LS1043A_IRQ_SEC_QUE2    104
#define LS1043A_IRQ_SEC_QUE3    105
#define LS1043A_IRQ_SEC_QUE4    106
#define LS1043A_IRQ_SEC_GLOBAL  107
#define LS1043A_IRQ_uQE         109     /* uQE (QE interrupt + QE critical + QE error) */
#define LS1043A_IRQ_CSU         112
#define LS1043A_IRQ_WDOG3       113
#define LS1043A_IRQ_WDOG4       114
#define LS1043A_IRQ_WDOG1       115
#define LS1043A_IRQ_WDOG2       116
#define LS1043A_IRQ_WDOG5       117
#define LS1043A_IRQ_FTM1        118
#define LS1043A_IRQ_FTM2        119
#define LS1043A_IRQ_FTM3        120
#define LS1043A_IRQ_FTM4        121
#define LS1043A_IRQ_FTM7        123
#define LS1043A_IRQ_FTM8        124
#define LS1043A_IRQ_TZASC       125
#define LS1043A_IRQ_CORE2_CTI   126
#define LS1043A_IRQ_CORE2_PMU   127
#define LS1043A_IRQ_CORE3_CTI   128
#define LS1043A_IRQ_CORE3_PMU   129
#define LS1043A_IRQ_QSPI        131
#define LS1043A_IRQ_EDMA        135
#define LS1043A_IRQ_CORE0_CTI   136
#define LS1043A_IRQ_CORE1_CTI   137
#define LS1043A_IRQ_CORE0_PMU   138
#define LS1043A_IRQ_CORE1_PMU   139
#define LS1043A_IRQ_AXI_ERR     140
#define LS1043A_IRQ_CCI400      141
#define LS1043A_IRQ_PEX1_INTA   142
#define LS1043A_IRQ_PEX1_INTB   143
#define LS1043A_IRQ_PEX1_INTC   144
#define LS1043A_IRQ_PEX1_INTD   145
#define LS1043A_IRQ_PEX1_MSI    148
#define LS1043A_IRQ_PEX1_PME    149
#define LS1043A_IRQ_PEX1_CFGERR 150
#define LS1043A_IRQ_PEX2_INTA   152
#define LS1043A_IRQ_PEX2_INTB   153
#define LS1043A_IRQ_PEX2_INTC   154
#define LS1043A_IRQ_PEX2_INTD   155
#define LS1043A_IRQ_PEX2_MSI    158
#define LS1043A_IRQ_PEX2_PME    159
#define LS1043A_IRQ_PEX2_CFGERR 160
#define LS1043A_IRQ_EXTIRQ0     163
#define LS1043A_IRQ_EXTIRQ1     164
#define LS1043A_IRQ_EXTIRQ2     165
#define LS1043A_IRQ_GPIO4       166
#define LS1043A_IRQ_EXTIRQ3     167
#define LS1043A_IRQ_EXTIRQ4     168
#define LS1043A_IRQ_EXTIRQ5     169
#define LS1043A_IRQ_qDMA        170
#define LS1043A_IRQ_EXTIRQ6     177
#define LS1043A_IRQ_EXTIRQ7     178
#define LS1043A_IRQ_EXTIRQ8     179
#define LS1043A_IRQ_EXTIRQ9     181
#define LS1043A_IRQ_EXTIRQ10    182
#define LS1043A_IRQ_EXTIRQ11    183
#define LS1043A_IRQ_qDMA_ERROR  185
#define LS1043A_IRQ_PEX3_INTA   186
#define LS1043A_IRQ_PEX3_INTB   187
#define S1043A_IRQ_PEX3_INTC    188
#define S1043A_IRQ_PEX3_INTD    189
#define LS1043A_IRQ_PEX3_MSI    192
#define LS1043A_IRQ_PEX3_PME    193
#define LS1043A_IRQ_PEX3_CFGERR 194

/*
 * DMA Channels assignments
 */
#define LS1043A_DMAMUX1_CHANNEL_OFFSET   0
#define LS1043A_DMAMUX2_CHANNEL_OFFSET   (1 * LS10XX_DMAMUX_NUM_SLOTS)

#define LS1043A_DMA_FLEX_TIMER6_0       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 3)
#define LS1043A_DMA_FLEX_TIMER6_1       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 4)
#define LS1043A_DMA_FLEX_TIMER6_2       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 5)
#define LS1043A_DMA_FLEX_TIMER6_3       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 6)
#define LS1043A_DMA_FLEX_TIMER6_4       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 7)
#define LS1043A_DMA_FLEX_TIMER6_5       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 8)
#define LS1043A_DMA_FLEX_TIMER6_6       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 9)
#define LS1043A_DMA_FLEX_TIMER6_7       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 10)
#define LS1043A_DMA_FLEX_TIMER5_0       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 11)
#define LS1043A_DMA_FLEX_TIMER5_1       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 12)
#define LS1043A_DMA_FLEX_TIMER5_2       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 13)
#define LS1043A_DMA_FLEX_TIMER5_3       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 14)
#define LS1043A_DMA_FLEX_TIMER5_4       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 15)
#define LS1043A_DMA_FLEX_TIMER5_5       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 16)
#define LS1043A_DMA_FLEX_TIMER5_6       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 17)
#define LS1043A_DMA_FLEX_TIMER5_7       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 18)
#define LS1043A_DMA_FLEX_TIMER4_0       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 19)
#define LS1043A_DMA_FLEX_TIMER4_1       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 20)
#define LS1043A_DMA_FLEX_TIMER4_2       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 21)
#define LS1043A_DMA_FLEX_TIMER4_3       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 22)
#define LS1043A_DMA_FLEX_TIMER4_4       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 23)
#define LS1043A_DMA_FLEX_TIMER4_5       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 24)
#define LS1043A_DMA_FLEX_TIMER4_6       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 25)
#define LS1043A_DMA_FLEX_TIMER4_7       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 26)
#define LS1043A_DMA_FLEX_TIMER3_0       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 27)
#define LS1043A_DMA_FLEX_TIMER3_1       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 28)
#define LS1043A_DMA_FLEX_TIMER3_2       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 29)
#define LS1043A_DMA_FLEX_TIMER3_3       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 30)
#define LS1043A_DMA_FLEX_TIMER3_4       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 31)
#define LS1043A_DMA_FLEX_TIMER3_5       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 32)
#define LS1043A_DMA_FLEX_TIMER3_6       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 33)
#define LS1043A_DMA_FLEX_TIMER3_7       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 34)
#define LS1043A_DMA_FLEX_TIMER2_0       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 35)
#define LS1043A_DMA_FLEX_TIMER2_1       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 36)
#define LS1043A_DMA_FLEX_TIMER2_2       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 37)
#define LS1043A_DMA_FLEX_TIMER2_3       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 38)
#define LS1043A_DMA_FLEX_TIMER2_4       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 39)
#define LS1043A_DMA_FLEX_TIMER2_5       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 40)
#define LS1043A_DMA_FLEX_TIMER2_6       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 41)
#define LS1043A_DMA_FLEX_TIMER2_7       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 42)
#define LS1043A_DMA_FLEX_TIMER1_0       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 43)
#define LS1043A_DMA_FLEX_TIMER1_1       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 44)
#define LS1043A_DMA_FLEX_TIMER1_2       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 45)
#define LS1043A_DMA_FLEX_TIMER1_3       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 46)
#define LS1043A_DMA_FLEX_TIMER1_4       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 47)
#define LS1043A_DMA_FLEX_TIMER1_5       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 48)
#define LS1043A_DMA_FLEX_TIMER1_6       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 49)
#define LS1043A_DMA_FLEX_TIMER1_7       (LS1043A_DMAMUX1_CHANNEL_OFFSET + 50)
#define LS1043A_DMA_SPI2                (LS1043A_DMAMUX1_CHANNEL_OFFSET + 55)
#define LS1043A_DMA_SPI2_RFDF           (LS1043A_DMAMUX1_CHANNEL_OFFSET + 56)
#define LS1043A_DMA_SPI2_CMD            (LS1043A_DMAMUX1_CHANNEL_OFFSET + 57)
#define LS1043A_DMA_SPI2_TF             (LS1043A_DMAMUX1_CHANNEL_OFFSET + 58)
#define LS1043A_DMA_SPI1                (LS1043A_DMAMUX1_CHANNEL_OFFSET + 59)
#define LS1043A_DMA_SPI1_RFDF           (LS1043A_DMAMUX1_CHANNEL_OFFSET + 60)
#define LS1043A_DMA_SPI1_CMD            (LS1043A_DMAMUX1_CHANNEL_OFFSET + 61)
#define LS1043A_DMA_SPI1_TF             (LS1043A_DMAMUX1_CHANNEL_OFFSET + 62)
#define LS1043A_DMA_MUX1_ALWAYS_ENABLED (LS1043A_DMAMUX1_CHANNEL_OFFSET + 63)

#define LS1043A_DMA_FLEX_TIMER7_7       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 18)
#define LS1043A_DMA_QSPI_RFDF           (LS1043A_DMAMUX2_CHANNEL_OFFSET + 19)
#define LS1043A_DMA_LPUART6_RX          (LS1043A_DMAMUX2_CHANNEL_OFFSET + 22)
#define LS1043A_DMA_LPUART6_TX          (LS1043A_DMAMUX2_CHANNEL_OFFSET + 23)
#define LS1043A_DMA_LPUART5_RX          (LS1043A_DMAMUX2_CHANNEL_OFFSET + 24)
#define LS1043A_DMA_LPUART5_TX          (LS1043A_DMAMUX2_CHANNEL_OFFSET + 25)
#define LS1043A_DMA_LPUART4_RX          (LS1043A_DMAMUX2_CHANNEL_OFFSET + 26)
#define LS1043A_DMA_LPUART4_TX          (LS1043A_DMAMUX2_CHANNEL_OFFSET + 27)
#define LS1043A_DMA_LPUART3_RX          (LS1043A_DMAMUX2_CHANNEL_OFFSET + 28)
#define LS1043A_DMA_LPUART3_TX          (LS1043A_DMAMUX2_CHANNEL_OFFSET + 29)
#define LS1043A_DMA_LPUART2_RX          (LS1043A_DMAMUX2_CHANNEL_OFFSET + 30)
#define LS1043A_DMA_LPUART2_TX          (LS1043A_DMAMUX2_CHANNEL_OFFSET + 31)
#define LS1043A_DMA_LPUART1_RX          (LS1043A_DMAMUX2_CHANNEL_OFFSET + 32)
#define LS1043A_DMA_LPUART1_TX          (LS1043A_DMAMUX2_CHANNEL_OFFSET + 33)
#define LS1043A_DMA_I2C3_RX             (LS1043A_DMAMUX2_CHANNEL_OFFSET + 34)
#define LS1043A_DMA_I2C3_TX             (LS1043A_DMAMUX2_CHANNEL_OFFSET + 35)
#define LS1043A_DMA_I2C2_RX             (LS1043A_DMAMUX2_CHANNEL_OFFSET + 36)
#define LS1043A_DMA_I2C2_TX             (LS1043A_DMAMUX2_CHANNEL_OFFSET + 37)
#define LS1043A_DMA_I2C1_RX             (LS1043A_DMAMUX2_CHANNEL_OFFSET + 38)
#define LS1043A_DMA_I2C1_TX             (LS1043A_DMAMUX2_CHANNEL_OFFSET + 39)
#define LS1043A_DMA_I2C4_RX             (LS1043A_DMAMUX2_CHANNEL_OFFSET + 40)
#define LS1043A_DMA_I2C4_TX             (LS1043A_DMAMUX2_CHANNEL_OFFSET + 41)
#define LS1043A_DMA_FLEX_TIMER8_0       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 48)
#define LS1043A_DMA_FLEX_TIMER8_1       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 49)
#define LS1043A_DMA_FLEX_TIMER8_2       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 50)
#define LS1043A_DMA_FLEX_TIMER8_3       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 51)
#define LS1043A_DMA_FLEX_TIMER8_4       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 52)
#define LS1043A_DMA_FLEX_TIMER8_5       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 53)
#define LS1043A_DMA_FLEX_TIMER8_6       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 54)
#define LS1043A_DMA_FLEX_TIMER8_7       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 55)
#define LS1043A_DMA_FLEX_TIMER7_0       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 56)
#define LS1043A_DMA_FLEX_TIMER7_1       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 57)
#define LS1043A_DMA_FLEX_TIMER7_2       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 58)
#define LS1043A_DMA_FLEX_TIMER7_3       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 59)
#define LS1043A_DMA_FLEX_TIMER7_4       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 60)
#define LS1043A_DMA_FLEX_TIMER7_5       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 61)
#define LS1043A_DMA_FLEX_TIMER7_6       (LS1043A_DMAMUX2_CHANNEL_OFFSET + 62)
#define LS1043A_DMA_MUX2_ALWAYS_ENABLED (LS1043A_DMAMUX2_CHANNEL_OFFSET + 63)

#endif  /* __AARCH64_LS1043A_H_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/mainline/hardware/startup/lib/public/aarch64/ls1043a.h $ $Rev: 851860 $")
#endif
