/*
 * KSZ8041.h
 *
 * Created by Cloudersemi CR600 SDK Team 2017-03-09
 *
 * Copyright (c) 2016-2017, Shanghai Clouder Semiconductor Co.,Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * o Neither the name of Shanghai Clouder Semiconductor Co.,Ltd. nor the names
 *   of its contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __KSZ8041_H_
#define __KSZ8041_H_

#define KSZ8041_ADDR            0x01UL
#define KSZ8041_ID_H(value)    (0x0022 == value)
#define KSZ8041_ID_L(value)    (0x1510 == (value & 0xfff0))

#define KSZ8041_LINKDOWN        0x00UL
#define KSZ8041_LINKUP          0x01UL

/* 查找并初始化ksz8041 phy芯片*/
void KSZ8041_Init(void);

uint32_t KSZ8041_GetLinkStatus(void);
uint32_t KSZ8041_GetRxErrCounter(void);

enum KSZ8041_Reg
{
    KSZ8041_BASE_CTL_REG          = 0x0000,     /* Base Control Register*/
    KSZ8041_BASE_STATUS_REG       = 0x0001,     /* Base Status Register */
    KSZ8041_ID_HI_REG             = 0x0002,     /*PHY Identifier High Register*/
    KSZ8041_ID_LOW_REG            = 0x0003,     /*PHY Identifier Low Register*/
    KSZ8041_AN_A_REG              = 0x0004,       /* auto-negotiation advertisement */
    KSZ8041_AN_L_REG              = 0x0005,       /* auto-negotiation link partner ability */
    KSZ8041_AN_E_REG              = 0x0006,       /* auto-negotiation expansion */
    KSZ8041_AN_N_REG              = 0x0007,       /* auto-negotiation next page */
    KSZ8041_LINK_NEXT_PAGE_REG    = 0x0008,       /* link partner next page ability */
    KSZ8041_MII_CTL_REG           = 0x0014,       /* MII control */
    KSZ8041_RXER_COUNTER_REG      = 0x0015,       /* RXER counter */
    KSZ8041_INT_CTL_REG           = 0x001B,       /* interrupt control/status */
    KSZ8041_CTL1_REG              = 0x001E,       /* PHY control 1 register */
    KSZ8041_CTL2_REG              = 0x001F       /* PHY control 2 register */
};

#endif
