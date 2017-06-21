/*
 * clouder600_spis.h
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


#ifndef __CLOUDER600_SPIS_H__
#define __CLOUDER600_SPIS_H__

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
    uint16_t SPIS_Direction;           /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref SPIS_data_direction */
    uint16_t SPIS_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be a value of @ref SPIS_data_size */
    uint16_t SPIS_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPIS_Clock_Polarity */
    uint16_t SPIS_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPIS_Clock_Phase */
    uint16_t SPIS_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPIS_BaudRate_Prescaler
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */
} SPIS_InitTypeDef;

/* Exported macro ------------------------------------------------------------*/
#define SPIS_Direction_TxRx_FullDuplex       0x00000000
#define SPIS_Direction_TxOnly                0x00000100
#define SPIS_Direction_RxOnly                0x00000200
#define SPIS_Direction_EEPROM_Read           0x00000300

#define SPIS_DataSize_04b                    0x00000003
#define SPIS_DataSize_05b                    0x00000004
#define SPIS_DataSize_06b                    0x00000005
#define SPIS_DataSize_07b                    0x00000006
#define SPIS_DataSize_08b                    0x00000007
#define SPIS_DataSize_09b                    0x00000008
#define SPIS_DataSize_10b                    0x00000009
#define SPIS_DataSize_11b                    0x0000000a
#define SPIS_DataSize_12b                    0x0000000b
#define SPIS_DataSize_13b                    0x0000000c
#define SPIS_DataSize_14b                    0x0000000d
#define SPIS_DataSize_15b                    0x0000000e
#define SPIS_DataSize_16b                    0x0000000f

#define SPIS_CPOL_High                       0x00000080
#define SPIS_CPOL_Low                        0x00000000

#define SPIS_CPHA_2Edge                      0x00000000
#define SPIS_CPHA_1Edge                      0x00000040

#define SPIS_TX                              0x00000002
#define SPIS_RX                              0x00000001

#define SPIS_IT_RXF                          0x00000010
#define SPIS_IT_RXO                          0x00000008
#define SPIS_IT_RXU                          0x00000004
#define SPIS_IT_TXO                          0x00000002
#define SPIS_IT_TXE                          0x00000001
#define SPIS_IT_All                          0x0000001f

#define SPIS_SS0                             0x00000001
#define SPIS_SS1                             0x00000002

#define SPIS_FLAG_BUSY                       0x00000001
#define SPIS_FLAG_TXNF                       0x00000002
#define SPIS_FLAG_TXE                        0x00000004
#define SPIS_FLAG_RXNE                       0x00000008
#define SPIS_FLAG_RXF                        0x00000010
#define SPIS_FLAG_TXERR                      0x00000040



/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void SPIS_Init(SPIS_InitTypeDef *SPIS_InitStruct);
void SPIS_StructInit(SPIS_InitTypeDef *SPIS_InitStruct);
void SPIS_Cmd(FunctionalState NewState);
void SPIS_DataFrameNumCfg(uint32_t  LoadValue);
void SPIS_TxFifoThrCfg(uint32_t TxFifoWaterMark);
void SPIS_RxFifoThrCfg(uint32_t RxFifoWaterMark);
uint8_t SPIS_GetTxFifoDatNum(void);
uint8_t SPIS_GetRxFifoDatNum(void);
void SPIS_ITConfig(uint32_t SPIS_IT, FunctionalState NewState);
void SPIS_DMACmd(uint16_t SPIS_TypeDMA, FunctionalState NewState);
void SPIS_SendData(uint16_t Data);
uint16_t SPIS_ReceiveData(void);
void SPIS_SSOutputCmd(uint16_t SPIS_SSx, FunctionalState NewState);
FlagStatus SPIS_GetFlagStatus(uint32_t SPIS_FLAG);
void SPIS_ClearFlag(void);
ITStatus SPIS_GetITStatus(uint32_t SPIS_IT);
void SPIS_ClearITPendingBit(uint32_t SPIS_IT);

ErrorStatus SPIS_DMA_M2PInit(uint32_t DMA_ch, uint32_t m_addr, uint32_t N_Data);
ErrorStatus SPIS_DMA_P2MInit(uint32_t DMA_ch, uint32_t m_addr, uint32_t N_Data);

#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_SPIS_H__ */

/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/
