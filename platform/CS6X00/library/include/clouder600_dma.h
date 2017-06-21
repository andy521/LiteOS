/*
 * clouder600_dma.h
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


#ifndef __CLOUDER600_DMA_H__
#define __CLOUDER600_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"
/**
  * @brief  DMA Init structure definition
  */


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/

// the number of dma max channel
#define DMA_MAX_CH  8



typedef struct
{
    uint32_t    DMA_SrcAddr;
    uint32_t    DMA_DstAddr;
    uint8_t     DMA_Type;
    uint16_t    DMA_BlockSize;
    uint8_t     DMA_SrcInc;
    uint8_t     DMA_DstInc;
    uint8_t     DMA_SrcMSize;
    uint8_t     DMA_DstMSize;
    uint8_t     DMA_SrcWidth;
    uint8_t     DMA_DstWidth;
    uint8_t     DMA_SrcPer;
    uint8_t     DMA_DstPer;
    uint8_t     DMA_SrcHS;
    uint8_t     DMA_DstHS;
} DMA_InitTypeDef;

typedef struct
{
    uint32_t sar;
    uint32_t dar;
    uint32_t llp;
    uint32_t ctllo;
    uint32_t ctlhi;
    uint32_t  sstat;
    uint32_t  dstat;
} DMA_LLPTypeDef;

#define DMA_Channel0    0
#define DMA_Channel1    1
#define DMA_Channel2    2
#define DMA_Channel3    3
#define DMA_Channel4    4
#define DMA_Channel5    5
#define DMA_Channel6    6
#define DMA_Channel7    7

#define DMA_Addr_SPIM0TX    (uint32_t)(SSIM0_BASE + 0x30)
#define DMA_Addr_SPIM0RX    (uint32_t)(SSIM0_BASE + 0x34)
#define DMA_Addr_SPIM1TX    (uint32_t)(SSIM1_BASE + 0x60)
#define DMA_Addr_SPIM1RX    (uint32_t)(SSIM1_BASE + 0x60)
#define DMA_Addr_SPISTX     (uint32_t)(SSIS0_BASE + 0x60)
#define DMA_Addr_SPISRX     (uint32_t)(SSIS0_BASE + 0x60)
#define DMA_Addr_UART0TX    (uint32_t)(USART0_BASE)
#define DMA_Addr_UART0RX    (uint32_t)(USART0_BASE)
#define DMA_Addr_UART1TX    (uint32_t)(USART1_BASE)
#define DMA_Addr_UART1RX    (uint32_t)(USART1_BASE)
#define DMA_Addr_UART2TX    (uint32_t)(USART2_BASE)
#define DMA_Addr_UART2RX    (uint32_t)(USART2_BASE)
#define DMA_Addr_UART3TX    (uint32_t)(USART3_BASE)
#define DMA_Addr_UART3RX    (uint32_t)(USART3_BASE)
#define DMA_Addr_I2STX      (uint32_t)(I2S_BASE + 0x1c8)
#define DMA_Addr_I2SRX      (uint32_t)(I2S_BASE + 0x1c0)

#define DMA_dmac_M2M    0
#define DMA_dmac_M2P    1
#define DMA_dmac_P2M    2
#define DMA_dmac_P2P    3

#define DMA_ADDR_INC    0
#define DMA_ADDR_DEC    1
#define DMA_ADDR_HOLD   2

#define DMA_MSIZE_1     0
#define DMA_MSIZE_4     1
#define DMA_MSIZE_8     2
#define DMA_MSIZE_16    3
#define DMA_MSIZE_32    4
#define DMA_MSIZE_64    5
#define DMA_MSIZE_128   6
#define DMA_MSIZE_256   7

#define DMA_WIDTH_Byte  0
#define DMA_WIDTH_HalfWord  0x1
#define DMA_WIDTH_Word  0x2

#define DMA_HS_HW		0
#define DMA_HS_SW		1

#define DMA_PER_Spim0Tx 0
#define DMA_PER_Spim0Rx 1
#define DMA_PER_Spim1Tx 2
#define DMA_PER_Spim1Rx 3
#define DMA_PER_SpisTx  4
#define DMA_PER_SpisRx  5
#define DMA_PER_Uart0Tx 6
#define DMA_PER_Uart0Rx 7
#define DMA_PER_Uart1Tx 8
#define DMA_PER_Uart1Rx 9
#define DMA_PER_Uart2Tx 10
#define DMA_PER_Uart2Rx 11
#define DMA_PER_I2sTx   12
#define DMA_PER_I2sRx   13
#define DMA_PER_Uart3Tx 14
#define DMA_PER_Uart3Rx 15

#define DMA_IT_TC       1   //transfer complete
#define DMA_IT_BC       2   //Block complete
#define DMA_IT_SrcTran  4
#define DMA_IT_DstTran  8
#define DMA_IT_TE       16  //transfer error

void     DMA_DeInit(uint32_t DMA_Channelx);
ErrorStatus  DMA_Init(uint32_t DMA_Channelx, DMA_InitTypeDef *DMA_InitStruct);
void     DMA_StructInit(DMA_InitTypeDef *DMA_InitStruct);
void     DMA_Cmd(uint32_t DMA_Channelx, FunctionalState NewState);
uint32_t DMA_GetCurrDataCount(uint32_t DMA_Channelx);
void     DMA_ITEn(uint32_t DMA_Channelx, FunctionalState NewState);
void     DMA_ITConfig(uint32_t DMA_Channelx, uint32_t    DMA_IT, FunctionalState NewState);
ITStatus DMA_GetITStatus(uint32_t DMA_Channelx, uint32_t DMA_IT);
ITStatus DMA_GetRawITStatus(uint32_t DMA_Channelx, uint32_t DMA_IT);
ITStatus DMA_GetCmbITStatus(uint32_t DMA_IT);
void     DMA_ClearITPendingBit(uint32_t DMA_Channelx, uint32_t DMA_IT);
void     DMA_ClearAllITPendingBit(uint32_t DMA_Channelx);

#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_DMA_H__ */

/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/
