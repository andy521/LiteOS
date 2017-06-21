/*
 * clouder600_i2c.h
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


#ifndef __CLOUDER600_I2C_H__
#define __CLOUDER600_I2C_H__

#define I2C0 I2C0_BASE
#define I2C1 I2C1_BASE

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"

#define DUMMY_WRITE 0xA5
/**
  * @brief  I2C Init structure definition
  */

typedef struct
{
    uint8_t I2C_Mode;               /*!< Specifies the I2C mode */

    uint32_t I2C_ClkSpeed;          /*!< Specifies the I2C I2C_Speed. 4~3400000 */

    uint8_t I2C_AddrMode;           /*!< Specifies the device own address mode*/

    uint8_t I2C_OwnAddress;         /*!< Specifies the device own address. */

    uint8_t I2C_MasterCode;         /*!< Specifies the device Master code at High Speed mode */
} I2C_InitTypeDef;

extern uint8_t  i2c0_stop_bit;
extern uint8_t  i2c1_stop_bit;

/* Exported macro ------------------------------------------------------------*/
#define GET_I2C_STOP(n) (n == I2C0 ? i2c0_stop_bit : i2c1_stop_bit)

#define SET_I2C_STOP(n, value) {            \
    if(n == I2C0) i2c0_stop_bit = value;    \
    else i2c1_stop_bit = value;}

#define I2C_Mode_Master 0x1
#define I2C_Mode_Slave 0

#define I2C_AddrMode_7B 0
#define I2C_AddrMode_10B    0x1

#define I2C_FIFO_TX         0x1
#define I2C_FIFO_RX         0

#define I2C_IT_RXU          0x1
#define I2C_IT_RXO          0x2
#define I2C_IT_RXF          0x4
#define I2C_IT_TXO          0x8
#define I2C_IT_TXE          0x10
#define I2C_IT_RDREQ        0x20
#define I2C_IT_TX_ABRT      0x40
#define I2C_IT_RXC          0x80
#define I2C_IT_WORKING      0x100
#define I2C_IT_STOP         0x200
#define I2C_IT_START        0x400
#define I2C_IT_GENCALL      0x800


#define I2C_Status_Working      0x1
#define I2C_Status_TFNF         0x2
#define I2C_Status_TFE          0x4
#define I2C_Status_RFNE         0x8
#define I2C_Status_RFF          0x10
#define I2C_Status_MWorking     0x20
#define I2C_Status_SWorking     0x40
#define I2C_Status_EN           0x80

/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
ErrorStatus I2C_Init(uint32_t I2Cn, I2C_InitTypeDef *I2C_InitStruct);  /* n=0,1 */

void I2C_StructInit(I2C_InitTypeDef *I2C_InitStruct);

/* Data transfers functions ***************************************************/
void I2C_SendAddr(uint32_t I2Cn, uint32_t TarAddr);

ErrorStatus I2C_ActiveSendBuffer(uint32_t I2Cn, uint8_t *wBuf, uint32_t len);

ErrorStatus I2C_ActiveReceiveBuffer(uint32_t I2Cn, uint8_t *rBuf, uint32_t len);

ErrorStatus I2C_ActiveSendData(uint32_t I2Cn, uint8_t Data);

void I2C_SendData(uint32_t I2Cn, uint8_t Data);

uint8_t I2C_ActiveReceiveData(uint32_t I2Cn);

uint8_t I2C_ReceiveData(uint32_t I2Cn);

void I2C_Cmd(uint32_t I2Cn, FunctionalState NewState);

void I2C_GenerateSTART(uint32_t I2Cn, FunctionalState NewState);

void I2C_GenerateSTOP(uint32_t I2Cn, FunctionalState NewState);

void I2C_GeneralCallCmd(uint32_t I2Cn, FunctionalState NewState);

void I2C_AcknowledgeConfig(uint32_t I2Cn, FunctionalState NewState);

void I2C_GeneralCallAckConfig(uint32_t I2Cn, FunctionalState NewState);

void I2C_SetFifoThreshold(uint32_t I2Cn, uint32_t I2C_FIFO_type, uint32_t I2C_FIFO_level);

uint32_t I2C_GetFifoStatus(uint32_t I2Cn, uint32_t I2C_FIFO_type);

void I2C_ITConfig(uint32_t I2Cn, uint32_t I2C_IT, FunctionalState NewState);

ITStatus I2C_GetITStatus(uint32_t I2Cn, uint32_t I2C_IT);

ITStatus I2C_GetRawITStatus(uint32_t I2Cn, uint32_t I2C_IT);

FlagStatus I2C_GetStatus(uint32_t I2Cn, uint32_t I2C_Status);

void I2C_ClearITPendingBit(uint32_t I2Cn, uint32_t I2C_IT);

void I2C_ClearAllITPendingBit(uint32_t I2Cn);

#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_I2C_H__ */

/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/
