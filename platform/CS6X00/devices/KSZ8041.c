/*
 * KSZ8041.c
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

#include "stdint.h"
#include "stdio.h"
#include "cr600_lib.h"
#include "KSZ8041.h"
#include "clouder600_eth.h"
#include "los_bsp_adapter.h"
     
#define PHY_DEBUG       0

#if PHY_DEBUG
#define phy_printf  printf
#else
#define phy_printf(...)
#endif

static void KSZ8041_CTL_GPIO_Init(void);


/*!
 * @brief Initial GPIO
 *
 * set MCU GPIO to control KSZ8041
 *
 * @return void
 */
static void KSZ8041_CTL_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitS;

    RCC_PeriphClockCmd(RCC_Periph_GPIO3Clock, ENABLE);

    GPIO_InitS.GPIO_Pin     = GPIO_Pin_5;
    GPIO_InitS.GPIO_Mode    = GPIO_Mode_Output;
    GPIO_Init(GPIO3, &GPIO_InitS);
}

/*!
 * @brief Initial KSZ8041
 *
 * @return void
 */
void KSZ8041_Init(void)
{
    int16_t data;
    ErrorStatus status;
    int cycle_time;
    int16_t ksz8041_id_h = 0;
    int16_t ksz8041_id_l = 0;
    int32_t loop_count = 0x18ffff;

    KSZ8041_CTL_GPIO_Init();
    
    GPIO_ResetBits(GPIO3,GPIO_Pin_5); //LOW

    /*pull down reset gpio for 10ms*/
    cr600_delay_ms(20);

    GPIO_SetBits(GPIO3,GPIO_Pin_5); //HIGH
    
    /*wait for 1ms to read phy register */
    cr600_delay_ms(1);

    /* get KSZ8041 ID */
    for (cycle_time = 0; cycle_time < 200; cycle_time++)
    {
        status = ETH_ReadPhy(KSZ8041_ADDR, KSZ8041_ID_HI_REG, &ksz8041_id_h);
        status = ETH_ReadPhy(KSZ8041_ADDR, KSZ8041_ID_LOW_REG, &ksz8041_id_l);

        if (KSZ8041_ID_H(ksz8041_id_h) && KSZ8041_ID_L(ksz8041_id_l))
        {
            goto FOUND_PHY_ADDRESS;
        }
        cr600_delay_ms(10);
    }

    if (cycle_time >= 200)
    {
        CR600_PANIC("can not find eth phy!\r\n");
    }

FOUND_PHY_ADDRESS:
    ETH_WritePhy(KSZ8041_ADDR, KSZ8041_BASE_CTL_REG, 0x3100);
    do
    {
        status = ETH_ReadPhy(KSZ8041_ADDR, KSZ8041_BASE_STATUS_REG, &data);

        if (SUCCESS != status)
        {
            printf("read phy fail\n");
        }

        loop_count--;

        if (loop_count == 0)
        {
            printf("Auto Negotiation fail\r\n");
            break;
        }

        if ((data & 0x0020) != 0)
        {
            phy_printf("Auto Negotiation Complete\r\n");
            break;
        }

        cr600_delay_ms(500);

    }
    while ((data & 0x0020) == 0);

    //ETH_WritePhy(KSZ8041_ADDR, KSZ8041_INT_CTL_REG, 0x0500);     //Ê¹ÄÜÖÐ¶Ï

    status = ETH_ReadPhy(KSZ8041_ADDR, KSZ8041_BASE_STATUS_REG, &data);

    if (SUCCESS != status)
    {
        phy_printf("read phy fail\n");
    }

    if ((data & (1 << 2)) == 0)
    {
        phy_printf("No Link\r\n");
        ETH_SetLinkStatus(ETH_LINK_DOWN);
    }

    else
    {
        ETH_SetLinkStatus(ETH_LINK_UP);
        phy_printf("Link UP\r\n");
        status = ETH_ReadPhy(KSZ8041_ADDR, KSZ8041_BASE_CTL_REG, &data);

        if (SUCCESS != status)
        {
            phy_printf("read phy fail\n");
        }

        if (data & (1 << 8))
        {
            ETH_SetLinkDuplexMode(ETH_FULL_DUPLEX);
            phy_printf("Link is full duplex.\r\n");
        }
        else
        {
            ETH_SetLinkDuplexMode(ETH_HALF_DUPLEX);
            phy_printf("Link is half duplex.\r\n");
        }

        if (data & (1 << 13))
        {
            ETH_SetLinkSpeed(ETH_SPEED_100M);
            phy_printf("Link is with 100M Speed.\r\n");
        }
        else
        {
            ETH_SetLinkSpeed(ETH_SPEED_10M);
            phy_printf("Link is with 10M Speed.\r\n");
        }
        printf("phy init ok\r\n");
    }
}

/*!
 * @brief get KSZ8041 status 
 *
 * @return KSZ8041_LINKDOWN/KSZ8041_LINKUP
 */
uint32_t KSZ8041_GetLinkStatus(void)
{
    int16_t data;
    ErrorStatus status;
    status = ETH_ReadPhy(KSZ8041_ADDR, KSZ8041_BASE_STATUS_REG, &data);

    if (SUCCESS != status)
    {
        return KSZ8041_LINKDOWN;
    }
    else
    {
        if (0 == ((1 << 2) & data))
        {
            return KSZ8041_LINKDOWN;
        }
        else
        {
            return KSZ8041_LINKUP;
        }
    }
}

/*!
 * @brief get KSZ8041 receive error counter 
 *
 * @return counter
 */
uint32_t KSZ8041_GetRxErrCounter(void)
{
    /* RXER REG is SC(self clear), so need to count */
    static uint32_t data_cnt = 0;
    int16_t data = 0;
    ErrorStatus status;
    
    status = ETH_ReadPhy(KSZ8041_ADDR, KSZ8041_RXER_COUNTER_REG, &data);

    if (SUCCESS != status)
    {
        return 0;
    }
    else
    {
        data_cnt += data;
        
        return data_cnt;
    }
}
