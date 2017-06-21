/*
 * clouder600_i2s.h
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


#ifndef __CLOUDER600_I2S_H__
#define __CLOUDER600_I2S_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"

/**
  * @brief  I2S Init structure definition
  */

typedef struct
{
    uint8_t I2S_Mode;               /*!< master or slave, in slave mode, without clk out */

    uint8_t I2S_TX_Resolution;      /*!< TX resolution, 12,16, 20. 24 or 32bits */

    uint8_t I2S_RX_Resolution;      /*!< RX resolution, 12,16, 20. 24 or 32bits */

    uint8_t I2S_WS_Len;            /*!< word select length, 16, 24, 32 cycles, must not less than resolution    */

} I2S_InitTypeDef;

/* Exported macro ------------------------------------------------------------*/
#define I2S_Mode_Master 0
#define I2S_Mode_Slave 1
#define I2S_Resolution_none 0
#define I2S_Resolution_12bit 1
#define I2S_Resolution_16bit 2
#define I2S_Resolution_20bit 3
#define I2S_Resolution_24bit 4
#define I2S_Resolution_32bit 5
#define I2S_WS_16   0
#define I2S_WS_24   1
#define I2S_WS_32   2
#define I2S_FIFO_TX 1
#define I2S_FIFO_RX 2
#define I2S_IT_RXNE 0x1
#define I2S_IT_RXO  0x2
#define I2S_IT_TXE  0x10
#define I2S_IT_TXO  0x20


/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void I2S_Init(I2S_InitTypeDef *I2S_InitStruct);

void I2S_StructInit(I2S_InitTypeDef *I2S_InitStruct);

/* Data transfers functions ***************************************************/
void I2S_Cmd(FunctionalState NewState);

void I2S_TXCmd(FunctionalState NewState);

void I2S_RXCmd(FunctionalState NewState);

void I2S_ActiveSendData(uint32_t LData, uint32_t RData);

void I2S_ActiveReceiveData(uint32_t *LData, uint32_t *RData);

void I2S_SendData(uint32_t LData, uint32_t RData);

void I2S_ReceiveData(uint32_t *LData, uint32_t *RData);

void I2S_SetFifoThreshold(uint8_t I2S_FIFO_Type, uint32_t I2S_FIFO_Level);

void I2S_FlushFifo(uint8_t I2S_FIFO_Type);

void I2S_ITConfig(uint32_t I2S_IT, FunctionalState NewState);

ITStatus I2S_GetITStatus(uint32_t I2S_IT);

void I2S_ClearITPendingBit(uint32_t I2S_IT);


/* DMA functions ***************************************************/
ErrorStatus  I2S_DMA_M2PInit(uint32_t DMA_ch, uint32_t m_addr, uint32_t N_Data);

ErrorStatus  I2S_DMA_P2MInit(uint32_t DMA_ch, uint32_t m_addr, uint32_t N_Data);

#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_I2S_H__ */

/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/
