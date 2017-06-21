/*
 * clouder600_spim1.h
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


#ifndef __CLOUDER600_SPIM1_H__
#define __CLOUDER600_SPIM1_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"


/**
  * @brief  SPI Init structure definition
  */

typedef struct
{
    uint16_t SPIM1_Direction;           /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref SPIM1_data_direction */
    uint16_t SPIM1_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be a value of @ref SPIM1_data_size */
    uint16_t SPIM1_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPIM1_Clock_Polarity */
    uint16_t SPIM1_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPIM1_Clock_Phase */
    uint16_t SPIM1_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPIM1_BaudRate_Prescaler
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */
} SPIM1_InitTypeDef;

/* Exported macro ------------------------------------------------------------*/
#define SPIM1_Direction_TxRx_FullDuplex       0x00000000
#define SPIM1_Direction_TxOnly                0x00000100
#define SPIM1_Direction_RxOnly                0x00000200
#define SPIM1_Direction_EEPROM_Read           0x00000300

#define SPIM1_DataSize_04b                    0x00000003
#define SPIM1_DataSize_05b                    0x00000004
#define SPIM1_DataSize_06b                    0x00000005
#define SPIM1_DataSize_07b                    0x00000006
#define SPIM1_DataSize_08b                    0x00000007
#define SPIM1_DataSize_09b                    0x00000008
#define SPIM1_DataSize_10b                    0x00000009
#define SPIM1_DataSize_11b                    0x0000000a
#define SPIM1_DataSize_12b                    0x0000000b
#define SPIM1_DataSize_13b                    0x0000000c
#define SPIM1_DataSize_14b                    0x0000000d
#define SPIM1_DataSize_15b                    0x0000000e
#define SPIM1_DataSize_16b                    0x0000000f

#define SPIM1_CPOL_High                       0x00000080
#define SPIM1_CPOL_Low                        0x00000000

#define SPIM1_CPHA_2Edge                      0x00000000
#define SPIM1_CPHA_1Edge                      0x00000040

#define SPIM1_TX                              0x00000002
#define SPIM1_RX                              0x00000001

#define SPIM1_IT_MST                          0x00000020
#define SPIM1_IT_RXF                          0x00000010
#define SPIM1_IT_RXO                          0x00000008
#define SPIM1_IT_RXU                          0x00000004
#define SPIM1_IT_TXO                          0x00000002
#define SPIM1_IT_TXE                          0x00000001
#define SPIM1_IT_All                          0x0000003f

#define SPIM1_SS0                             0x00000001
#define SPIM1_SS1                             0x00000002

#define SPIM1_FLAG_BUSY                       0x00000001
#define SPIM1_FLAG_TXNF                       0x00000002
#define SPIM1_FLAG_TXE                        0x00000004
#define SPIM1_FLAG_RXNE                       0x00000008
#define SPIM1_FLAG_RXF                        0x00000010
#define SPIM1_FLAG_DATERR                     0x00000040



/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void SPIM1_Init(SPIM1_InitTypeDef *SPIM1_InitStruct);
void SPIM1_StructInit(SPIM1_InitTypeDef *SPIM1_InitStruct);
void SPIM1_Cmd(FunctionalState NewState);
void SPIM1_DataFrameNumCfg(uint32_t  LoadValue);
void SPIM1_TxFifoThrCfg(uint32_t TxFifoWaterMark);
void SPIM1_RxFifoThrCfg(uint32_t RxFifoWaterMark);
uint8_t SPIM1_GetTxFifoDatNum(void);
uint8_t SPIM1_GetRxFifoDatNum(void);
void SPIM1_ITConfig(uint32_t SPIM1_IT, FunctionalState NewState);
void SPIM1_DMACmd(uint16_t SPIM1_TypeDMA, FunctionalState NewState);
void SPIM1_SendData(uint16_t Data);
uint16_t SPIM1_ReceiveData(void);
void SPIM1_SSOutputCmd(uint16_t SPIM1_SSx, FunctionalState NewState);
FlagStatus SPIM1_GetFlagStatus(uint32_t SPIM1_FLAG);
void SPIM1_ClearFlag(void);
ITStatus SPIM1_GetITStatus(uint32_t SPIM1_IT);
void SPIM1_ClearITPendingBit(uint32_t SPIM1_IT);

//dma func
ErrorStatus SPIM1_DMA_M2PInit(uint32_t DMA_ch, uint32_t m_addr, uint32_t N_Data);
ErrorStatus SPIM1_DMA_P2MInit(uint32_t DMA_ch, uint32_t m_addr, uint32_t N_Data);

#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_SPIM1_H__ */

/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/
