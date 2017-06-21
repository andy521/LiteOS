/*
 * clouder600_iomux.h
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


#ifndef __CLOUDER600_IOMUX_H__
#define __CLOUDER600_IOMUX_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"

/**
  * @brief IOMUX definition
*/
#define PIN_ETH_RMII        ((uint32_t)0x00000001) /*!<Ethernet ETH_RMII    mode mapping 0x50*/
#define PIN_USB             ((uint32_t)0x00000002) /*!<Ethernet USB         mode mapping 0x50*/
#define PIN_SPIM0_1LINE     ((uint32_t)0x00000004) /*!<Ethernet SPIM0_1LINE mode mapping 0x50*/
#define PIN_SPIM0_2LINE     ((uint32_t)0x0000000c) /*!<Ethernet SPIM0_2LINE mode mapping 0x50*/
#define PIN_SPIM0_3LINE     ((uint32_t)0x0000001c) /*!<Ethernet SPIM0_3LINE mode mapping 0x50*/
#define PIN_SPIM0_4LINE     ((uint32_t)0x0000003c) /*!<Ethernet SPIM0_4LINE mode mapping 0x50*/
#define PIN_SPIM1_2CS       ((uint32_t)0x000000c0) /*!<Ethernet SPIM1_2CS   mode mapping 0x50*/
#define PIN_SPIM1_1CS       ((uint32_t)0x00000080) /*!<Ethernet SPIM1_1CS   mode mapping 0x50*/
#define PIN_SDIO            ((uint32_t)0x00000100) /*!<Ethernet SDIO        mode mapping 0x50*/
#define PIN_SPIS            ((uint32_t)0x00000200) /*!<Ethernet SPIS        mode mapping 0x50*/
#define PIN_USART00         ((uint32_t)0x00006000) /*!<Ethernet USART00      mode mapping 0x50*/
#define PIN_USART01         ((uint32_t)0x00060000) /*!<Ethernet USART01      mode mapping 0x50*/
#define PIN_USART00_FC      ((uint32_t)0x00007800) /*!<Ethernet USART00_FC   mode mapping 0x50*/
#define PIN_USART01_FC      ((uint32_t)0x00078000) /*!<Ethernet USART01_FC   mode mapping 0x50*/
#define PIN_I2S_M           ((uint32_t)0x00180000) /*!<Ethernet I2S_M       mode mapping 0x50*/
#define PIN_I2S_S           ((uint32_t)0x00100000) /*!<Ethernet I2S_S       mode mapping 0x50*/
#define PIN_USART10         ((uint32_t)0x01800000) /*!<Ethernet USART10      mode mapping 0x50*/
#define PIN_USART11         ((uint32_t)0x18000000) /*!<Ethernet USART11      mode mapping 0x50*/
#define PIN_USART10_FC      ((uint32_t)0x01e00000) /*!<Ethernet USART10_FC   mode mapping 0x50*/
#define PIN_USART11_FC      ((uint32_t)0x1e000000) /*!<Ethernet USART11_FC   mode mapping 0x50*/
#define PIN_PLC_SPIS        ((uint32_t)0x20000000) /*!<Ethernet PLC_SPIS    mode mapping 0x50*/
#define PIN_I2C_0           ((uint32_t)0x40000000) /*!<Ethernet I2C_0       mode mapping 0x50*/
#define PIN_I2C_1           ((uint32_t)0x80000000) /*!<Ethernet I2C_1       mode mapping 0x50*/

#define PIN_PWM0            ((uint32_t)0xf0000001) /*!<Ethernet PWM0        mode mapping 0x54*/
#define PIN_PWM1            ((uint32_t)0xf0000002) /*!<Ethernet CLKOUT1     mode mapping 0x54*/
#define PIN_CLKOUT1         ((uint32_t)0xf0000004) /*!<Ethernet CLKOUT2     mode mapping 0x54*/
#define PIN_CLKOUT2         ((uint32_t)0xf0000008) /*!<Ethernet PWM1        mode mapping 0x54*/
#define PIN_USART2          ((uint32_t)0xf0000030) /*!<Ethernet USART2       mode mapping 0x54*/
#define PIN_USART2_FC       ((uint32_t)0xf00000f0) /*!<Ethernet USART2_FC    mode mapping 0x54*/
#define PIN_PWM2            ((uint32_t)0xf0000400) /*!<Ethernet PWM2        mode mapping 0x54*/
#define PIN_PWM3            ((uint32_t)0xf0000800) /*!<Ethernet PWM3        mode mapping 0x54*/
#define PIN_PLC_AFE         ((uint32_t)0xf0006000) /*!<Ethernet PLC_AFE     mode mapping 0x54*/
#define PIN_PLC_RXSEL       ((uint32_t)0xf0008000) /*!<Ethernet PLC_RXSEL   mode mapping 0x54*/
#define PIN_ETH_MII         ((uint32_t)0xf0010000) /*!<Ethernet ETH_MII     mode mapping 0x54*/
#define PIN_USART3          ((uint32_t)0xf0060000) /*!<Ethernet USART3       mode mapping 0x54*/
#define PIN_USART4          ((uint32_t)0xf0600000) /*!<Ethernet USART4       mode mapping 0x54*/
#define PIN_USART3_FC       ((uint32_t)0xf01e0000) /*!<Ethernet USART3_FC    mode mapping 0x54*/
#define PIN_USART4_FC       ((uint32_t)0xf1e00000) /*!<Ethernet USART4_FC    mode mapping 0x54*/
#define PIN_SWD             ((uint32_t)0xf0000000) /*!<Ethernet CPU SWD     mode mapping 0x54*/
#define PIN_GPIO6_2         ((uint32_t)0xf0000100) /*!<Ethernet GPIO6_2     mode mapping 0x54*/
#define PIN_GPIO6_3         ((uint32_t)0xf0000200) /*!<Ethernet GPIO6_3     mode mapping 0x54*/

/*
#define GPIO0_GRP                   ((uint32_t)0x10000000)
#define GPIO0_Pin0                  ((uint32_t)0x00000000)
#define GPIO0_Pin1                  ((uint32_t)0x00000000)
#define GPIO0_Pin2                  ((uint32_t)0x00000000)
#define GPIO0_Pin3                  ((uint32_t)0x00000000)
#define GPIO0_Pin4                  ((uint32_t)0x00000000)
#define GPIO0_Pin5                  ((uint32_t)0x00000000)
#define GPIO0_Pin6                  ((uint32_t)0x00000000)
#define GPIO0_Pin7                  ((uint32_t)0x00000000)
#define GPIO1_GRP                   ((uint32_t)0x00000000)
#define GPIO1_Pin0                  ((uint32_t)0x00000000)
#define GPIO1_Pin1                  ((uint32_t)0x00000000)
#define GPIO1_Pin2                  ((uint32_t)0x00000000)
#define GPIO1_Pin3                  ((uint32_t)0x00000000)
#define GPIO1_Pin4                  ((uint32_t)0x00000000)
#define GPIO1_Pin5                  ((uint32_t)0x00000000)
#define GPIO1_Pin6                  ((uint32_t)0x00000000)
#define GPIO1_Pin7                  ((uint32_t)0x00000000)
#define GPIO2_GRP                   ((uint32_t)0x00000000)
#define GPIO0_Pin0                  ((uint32_t)0x00000000)
#define GPIO0_Pin1                  ((uint32_t)0x00000000)
#define GPIO0_Pin2                  ((uint32_t)0x00000000)
#define GPIO0_Pin3                  ((uint32_t)0x00000000)
#define GPIO0_Pin4                  ((uint32_t)0x00000000)
#define GPIO0_Pin5                  ((uint32_t)0x00000000)
#define GPIO0_Pin6                  ((uint32_t)0x00000000)
#define GPIO0_Pin7                  ((uint32_t)0x00000000)
#define GPIO3_GRP                   ((uint32_t)0x00000000)
#define GPIO0_Pin0                  ((uint32_t)0x00000000)
#define GPIO0_Pin1                  ((uint32_t)0x00000000)
#define GPIO0_Pin2                  ((uint32_t)0x00000000)
#define GPIO0_Pin3                  ((uint32_t)0x00000000)
#define GPIO0_Pin4                  ((uint32_t)0x00000000)
#define GPIO0_Pin5                  ((uint32_t)0x00000000)
#define GPIO0_Pin6                  ((uint32_t)0x00000000)
#define GPIO0_Pin7                  ((uint32_t)0x00000000)
#define GPIO4_GRP                   ((uint32_t)0x00000000)
#define GPIO0_Pin0                  ((uint32_t)0x00000000)
#define GPIO0_Pin1                  ((uint32_t)0x00000000)
#define GPIO0_Pin2                  ((uint32_t)0x00000000)
#define GPIO0_Pin3                  ((uint32_t)0x00000000)
#define GPIO0_Pin4                  ((uint32_t)0x00000000)
#define GPIO0_Pin5                  ((uint32_t)0x00000000)
#define GPIO0_Pin6                  ((uint32_t)0x00000000)
#define GPIO0_Pin7                  ((uint32_t)0x00000000)
#define GPIO5_GRP                   ((uint32_t)0x00000000)
#define GPIO0_Pin0                  ((uint32_t)0x00000000)
#define GPIO0_Pin1                  ((uint32_t)0x00000000)
#define GPIO0_Pin2                  ((uint32_t)0x00000000)
#define GPIO0_Pin3                  ((uint32_t)0x00000000)
#define GPIO0_Pin4                  ((uint32_t)0x00000000)
#define GPIO0_Pin5                  ((uint32_t)0x00000000)
#define GPIO0_Pin6                  ((uint32_t)0x00000000)
#define GPIO0_Pin7                  ((uint32_t)0x00000000)
#define GPIO6_GRP                   ((uint32_t)0x00000000)
#define GPIO0_Pin0                  ((uint32_t)0x00000000)
#define GPIO0_Pin1                  ((uint32_t)0x00000000)
#define GPIO0_Pin2                  ((uint32_t)0x00000000)
#define GPIO0_Pin3                  ((uint32_t)0x00000000)
#define GPIO0_Pin4                  ((uint32_t)0x00000000)
#define GPIO0_Pin5                  ((uint32_t)0x00000000)
#define GPIO0_Pin6                  ((uint32_t)0x00000000)
#define GPIO0_Pin7                  ((uint32_t)0x00000000)
*/

void PIN_Config(uint32_t PIN_Cfg, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_IOMUX_H__ */

/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/
