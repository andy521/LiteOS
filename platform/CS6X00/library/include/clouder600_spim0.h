/*
 * clouder600_spim0.h
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


#ifndef __CLOUDER600_SPIM0_H__
#define __CLOUDER600_SPIM0_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"

/* Exported macro ------------------------------------------------------------*/
#define SPIM0_Mode_Standard             0x1
#define SPIM0_Mode_Dual                 0x2
#define SPIM0_Mode_Quad                 0x3

#define SPIM0_CPOL_Low                  0
#define SPIM0_CPOL_High                 1

#define SPIM0_CPHA_1Edge                0
#define SPIM0_CPHA_2Edge                1

#define SPIM0_FIFO_TX                   1
#define SPIM0_FIFO_RX                   2

#define SPIM0_IT_RXF                    1
#define SPIM0_IT_RXO                    2
#define SPIM0_IT_TXO                    4
#define SPIM0_IT_TXE                    8
#define SPIM0_IT_TC                     0x10

//SSIM0_TX_ALMOST_EMPTY_LEVEL experimence value
#define SPIM0_TX_WaterMaker             0x10

/* Exported functions ------------------------------------------------------- */

typedef struct
{
    uint8_t SPIM0_Mode;             /*!< 1/2/4 wire or tx/rx/fullduplex >!*/

    FunctionalState SPIM0_IOMode;     /*!< use 1 output or multi IO in 2/4 wire mode to send addr >!*/

    uint8_t SPIM0_CPOL;             /*!< the voltage of sclk in idle state, low or high >!*/

    uint8_t SPIM0_CPHA;             /*!< sample at first edge or second edge of sclk >!*/

    uint8_t SPIM0_CmdLen;           /*!< length of cmd >!*/

    uint8_t SPIM0_AddrLen;          /*!< length of address >!*/

    uint8_t SPIM0_TXDataLen;        /*!< length of tx data >!*/

    uint8_t SPIM0_RXDataLen;        /*!< length of rx data >!*/
} SPIM0_InitTypeDef;



/* Initialization and Configuration functions *********************************/

void SPIM0_StructInit(SPIM0_InitTypeDef *SPIM0_InitStruct);

#if defined(__ICCARM__)

__ramfunc void SPIM0_Init(SPIM0_InitTypeDef   *SPIM0_InitStruct);
/* Data transfers functions ***************************************************/
__ramfunc void  SPIM0_WCmd_Only(uint8_t cmd);
__ramfunc void  SPIM0_WCmd_Data(uint8_t cmd, uint8_t *pBuffer, uint32_t N_Byte);
__ramfunc void  SPIM0_WCmd_Addr_Data(uint8_t cmd, uint32_t WriteAddr, uint8_t *pBuffer, uint32_t N_Byte);
__ramfunc void  SPIM0_RCmd_Data(uint8_t cmd, uint8_t *pBuffer, uint32_t N_Byte);
__ramfunc void  SPIM0_RCmd_Addr_Data(uint8_t cmd, uint32_t ReadAddr, uint8_t *pBuffer,  uint32_t N_Byte);
__ramfunc void SPIM0_SetFifoThreshold(uint32_t SPIM0_Fifo_type, uint32_t SPIM0_Fifo_level);
__ramfunc uint32_t SPIM0_GetRXFifoStatus(void);
__ramfunc void SPIM0_ITEn(FunctionalState NewState);
__ramfunc void SPIM0_ITConfig(uint32_t SPIM0_IT, FunctionalState NewState);
__ramfunc ITStatus SPIM0_GetITStatus(uint32_t SPIM0_IT);
__ramfunc void SPIM0_ClearFinishBit(void);

__ramfunc void SPIM0_RegSave(void);
__ramfunc void SPIM0_RegRestore(void);

#elif defined(__CC_ARM)

#pragma arm section code = "__RAM_FUNC"
void SPIM0_Init(SPIM0_InitTypeDef   *SPIM0_InitStruct);
void  SPIM0_WCmd_Only(uint8_t cmd);
void  SPIM0_WCmd_Data(uint8_t cmd, uint8_t *pBuffer, uint32_t N_Byte);
void  SPIM0_WCmd_Addr_Data(uint8_t cmd, uint32_t WriteAddr, uint8_t *pBuffer, uint32_t N_Byte);
void  SPIM0_RCmd_Data(uint8_t cmd, uint8_t *pBuffer, uint32_t N_Byte);
void  SPIM0_RCmd_Addr_Data(uint8_t cmd, uint32_t ReadAddr, uint8_t *pBuffer,  uint32_t N_Byte);
void SPIM0_SetFifoThreshold(uint32_t SPIM0_Fifo_type, uint32_t SPIM0_Fifo_level);
uint32_t SPIM0_GetRXFifoStatus(void);
void SPIM0_ITEn(FunctionalState NewState);
void SPIM0_ITConfig(uint32_t SPIM0_IT, FunctionalState NewState);
ITStatus SPIM0_GetITStatus(uint32_t SPIM0_IT);
void SPIM0_ClearFinishBit(void);
void SPIM0_RegSave(void);
void SPIM0_RegRestore(void);
#pragma arm section

#else
		#error "not supported compiler"
#endif

ErrorStatus  SPIM0_DMA_M2PInit(uint32_t DMA_ch, uint32_t m_addr, uint32_t N_Data);
ErrorStatus  SPIM0_DMA_P2MInit(uint32_t DMA_ch, uint32_t m_addr, uint32_t N_Data);



#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_SPIM0_H__ */

/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/
