/*
 * clouder600_sdio.h
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


#ifndef __CLOUDER600_SDIO_H__
#define __CLOUDER600_SDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"


/**
  * @brief  SDIO Init structure definition
  */

typedef struct
{
    uint32_t SDIO_BusWide;              // Specifies the SDIO bus width.                         //
    uint8_t SDIO_ClockDiv;              // Specifies the clock frequency of the SDIO controller. //
} SDIO_InitTypeDef;

typedef struct
{
    uint32_t SDIO_Argument;       // Specifies the SDIO command argument which is sent
    uint32_t SDIO_CmdIndex;       // Specifies the SDIO command index. It must be lower than 0x40
    uint32_t SDIO_Response;       // Specifies the SDIO response type
    uint32_t SDIO_Wait;           // Specifies whether SDIO wait-for-interrupt request is enabled or disabled
    uint32_t SDIO_RespChk ;       // whether check response crc
    uint32_t SDIO_DataExpect;     // whether check response crc
    uint32_t SDIO_TransferDir;    /*!< Specifies the data transfer direction, whether the transfer is read or write*/
    uint32_t SDIO_TransferMode;   /*!< Specifies whether data transfer is in stream or block mode.*/
    uint32_t SDIO_AutoStop;       // auto send stop after transfer finsished
    uint32_t SDIO_SendInitSeq;    // send initial seuqence
} SDIO_CmdInitTypeDef;

typedef struct
{
//uint32_t SDIO_DataTimeOut;    /*!< Specifies the data timeout period in card bus clock periods. */
    uint32_t SDIO_DataLength;     /*!< Specifies the number of data bytes to be transferred. */
    uint32_t SDIO_DataBlockSize;  /*!< Specifies the data block size for block transfer.*/
} SDIO_DataInitTypeDef;

/**
  * @}
  */

/** @defgroup SDIO_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @defgroup SDIO_Clock_Bypass
  * @{
  */

/** @defgroup SDIO_Bus_Wide
  * @{
  */

#define SDIO_BusWide_1b                     ((uint32_t)0x00000000)
#define SDIO_BusWide_4b                     ((uint32_t)0x00000001)
#define SDIO_BusWide_8b                     ((uint32_t)0x00010000)
#define IS_SDIO_BUS_WIDE(WIDE) (((WIDE) == SDIO_BusWide_1b) || ((WIDE) == SDIO_BusWide_4b) || \
                                ((WIDE) == SDIO_BusWide_8b))

/**
  * @}
  */

/** @defgroup SDIO_Power_State
  * @{
  */

#define SDIO_PowerState_OFF                 ((uint32_t)0x00000000)
#define SDIO_PowerState_ON                  ((uint32_t)0x00000001)
#define IS_SDIO_POWER_STATE(STATE) (((STATE) == SDIO_PowerState_OFF) || ((STATE) == SDIO_PowerState_ON))
/**
  * @}
  */


/** @defgroup SDIO_Interrupt_sources
  * @{
  */
///carddetect
#define SDIO_IT_RESPERR                     ((uint32_t)0x00000002)
#define SDIO_IT_CmdDone                     ((uint32_t)0x00000004)
#define SDIO_IT_DataSendFinish              ((uint32_t)0x00000008)
#define SDIO_IT_TXDVAL                      ((uint32_t)0x00000010)
#define SDIO_IT_RXDVAL                      ((uint32_t)0x00000020)
#define SDIO_IT_CCRCFAIL                    ((uint32_t)0x00000040)
#define SDIO_IT_DCRCFAIL                    ((uint32_t)0x00000080)
#define SDIO_IT_CTIMEOUT                    ((uint32_t)0x00000100)
#define SDIO_IT_DTIMEOUT                    ((uint32_t)0x00000200)
#define SDIO_IT_HWFLCon                     ((uint32_t)0x00000400)
#define SDIO_IT_FIFOERR                     ((uint32_t)0x00000800)
//#define SDIO_IT_HLE                         ((uint32_t)0x00001000)
#define SDIO_IT_STBITERR                    ((uint32_t)0x00002000)
#define SDIO_IT_StopAbortFinsih             ((uint32_t)0x00004000)
#define SDIO_IT_ENDERR                      ((uint32_t)0x00008000)
#define SDIO_IT_SDIOIT                      ((uint32_t)0x00010000)
#define SDIO_IT_All                         ((uint32_t)0xffffffff)
#define IS_SDIO_IT(IT) ((((IT) & (uint32_t)0xFFFE0000) == 0x00) && ((IT) != (uint32_t)0x00))

/**
  * @}
  */

/** @defgroup SDIO_Command_Index
  * @{
  */

#define IS_SDIO_CMD_INDEX(INDEX)            ((INDEX) < 0x40)
/**
  * @}
  */

/** @defgroup SDIO_Response_Type
  * @{
  */

#define SDIO_Response_No                    ((uint32_t)0x00000000)
#define SDIO_Response_Short                 ((uint32_t)0x00000040)
#define SDIO_Response_Long                  ((uint32_t)0x000000C0)
#define IS_SDIO_RESPONSE(RESPONSE) (((RESPONSE) == SDIO_Response_No) || \
                                    ((RESPONSE) == SDIO_Response_Short) || \
                                    ((RESPONSE) == SDIO_Response_Long))
///
#define SDIO_RespChk_Yes                    ((uint32_t)0x00000100)
#define SDIO_RespChk_No                     ((uint32_t)0x00000000)

/**
  * @}
  */

/** @defgroup SDIO_Wait_Interrupt_State
  * @{
  */
#define SDIO_DataExpect_No                  ((uint32_t)0x00000000)
#define SDIO_DataExpect_Yes                 ((uint32_t)0x00000200)
/**
  * @}
  */

/** @defgroup SDIO_Transfer_Direction
  * @{
  */

#define SDIO_TransferDir_ToCard             ((uint32_t)0x00000400)
#define SDIO_TransferDir_ToSDIO             ((uint32_t)0x00000000)
#define IS_SDIO_TRANSFER_DIR(DIR)			(((DIR) == SDIO_TransferDir_ToCard) || \
												((DIR) == SDIO_TransferDir_ToSDIO))
/**
  * @}
  */

/** @defgroup SDIO_Transfer_Type
  * @{
  */

#define SDIO_TransferMode_Block             ((uint32_t)0x00000000)
#define SDIO_TransferMode_Stream            ((uint32_t)0x00000800)
#define IS_SDIO_TRANSFER_MODE(MODE)			(((MODE) == SDIO_TransferMode_Stream) || \
												((MODE) == SDIO_TransferMode_Block))

///
#define SDIO_AutoStop_Yes                   ((uint32_t)0x00001000)
#define SDIO_AutoStop_No                    ((uint32_t)0x00000000)

///
#define SDIO_SendInitSeq_Yes                ((uint32_t)0x00008000)
#define SDIO_SendInitSeq_No                 ((uint32_t)0x00000000)
/**
  * @}
  */

/** @defgroup SDIO_Wait_Interrupt_State
  * @{
  */

#define SDIO_Wait_Clear                     ((uint32_t)0x00000000) /*!< SDIO No Wait, TimeOut is enabled */
#define SDIO_Wait_Assert                    ((uint32_t)0x00000100) /*!< SDIO Wait Interrupt Request */

/** @defgroup SDIO_Response_Registers
  * @{
  */

#define SDIO_RESP1                          MMC_RESP0
#define SDIO_RESP2                          MMC_RESP1
#define SDIO_RESP3                          MMC_RESP2
#define SDIO_RESP4                          MMC_RESP3
#define IS_SDIO_RESP(RESP)					(((RESP) == SDIO_RESP1) || ((RESP) == SDIO_RESP2) || \
												((RESP) == SDIO_RESP3) || ((RESP) == SDIO_RESP4))
/**
  * @}
  */

/** @defgroup SDIO_Data_Length
  * @{
  */

#define IS_SDIO_DATA_LENGTH(LENGTH) ((LENGTH) <= 0x01FFFFFF)
/**
  * @}
  */

/** @defgroup SDIO_Data_Block_Size
  * @{
  */

#define SDIO_DataBlockSize_4b               ((uint32_t)0x00000004)
#define SDIO_DataBlockSize_8b               ((uint32_t)0x00000008)
#define SDIO_DataBlockSize_16b              ((uint32_t)0x00000010)
#define SDIO_DataBlockSize_32b              ((uint32_t)0x00000020)
#define SDIO_DataBlockSize_64b              ((uint32_t)0x00000040)
#define SDIO_DataBlockSize_128b             ((uint32_t)0x00000080)
#define SDIO_DataBlockSize_256b             ((uint32_t)0x00000100)
#define SDIO_DataBlockSize_512b             ((uint32_t)0x00000200)
#define SDIO_DataBlockSize_1024b            ((uint32_t)0x00000400)
#define SDIO_DataBlockSize_2048b            ((uint32_t)0x00000800)
#define SDIO_DataBlockSize_4096b            ((uint32_t)0x00001000)
#define IS_SDIO_BLOCK_SIZE(SIZE) (((SIZE) == SDIO_DataBlockSize_4b) || \
                                  ((SIZE) == SDIO_DataBlockSize_8b) || \
                                  ((SIZE) == SDIO_DataBlockSize_16b) || \
                                  ((SIZE) == SDIO_DataBlockSize_32b) || \
                                  ((SIZE) == SDIO_DataBlockSize_64b) || \
                                  ((SIZE) == SDIO_DataBlockSize_128b) || \
                                  ((SIZE) == SDIO_DataBlockSize_256b) || \
                                  ((SIZE) == SDIO_DataBlockSize_512b) || \
                                  ((SIZE) == SDIO_DataBlockSize_1024b) || \
                                  ((SIZE) == SDIO_DataBlockSize_2048b) || \
                                  ((SIZE) == SDIO_DataBlockSize_4096b)
////
///IDMA interrupt
#define SDIO_IDMA_IT_TxInt                  ((uint32_t)0x00000001)
#define SDIO_IDMA_IT_RxInt                  ((uint32_t)0x00000002)
#define SDIO_IDMA_IT_BusError               ((uint32_t)0x00000004)
#define SDIO_IDMA_IT_DescriptError          ((uint32_t)0x00000010)
#define SDIO_IDMA_IT_CardError              ((uint32_t)0x00000020)
#define SDIO_IDMA_IT_TransInt               ((uint32_t)0x00000100)
#define SDIO_IDMA_IT_ErrInt                 ((uint32_t)0x00000200)
#define SDIO_IDMA_IT_All                    ((uint32_t)0x00000337)
/**
  * @}
  */
/** @defgroup SDIO_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup SDIO_Exported_Functions
  * @{
  */
void SDIO_ControllerReset(void);
void SDIO_DeInit(void);
void SDIO_Init(SDIO_InitTypeDef *SDIO_InitStruct);
void SDIO_StructInit(SDIO_InitTypeDef *SDIO_InitStruct);
void SDIO_ClockCmd(FunctionalState NewState);
void SDIO_SetPowerState(uint32_t SDIO_PowerState);
uint32_t SDIO_GetPowerState(void);
void SDIO_ITConfig(uint32_t SDIO_IT, FunctionalState NewState);
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct);
void SDIO_CmdStructInit(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct);
uint8_t SDIO_GetCommandResponse(void);
uint32_t SDIO_GetResponse(uint32_t SDIO_RESP);
void SDIO_DataConfig(SDIO_DataInitTypeDef *SDIO_DataInitStruct);
void SDIO_DataStructInit(SDIO_DataInitTypeDef *SDIO_DataInitStruct);
uint32_t SDIO_GetDataTransCount(void);
uint32_t SDIO_ReadData(void);
void SDIO_WriteData(uint32_t Data);
uint32_t SDIO_GetFIFOCount(void);
void SDIO_StartSDIOReadWait(void);
void SDIO_StopSDIOReadWait(void);
void SDIO_CommandCompletionCmd(FunctionalState NewState);
void SDIO_CEATAITCmd(FunctionalState NewState);
ErrorStatus SDIO_WaitTfrOver(void);
ITStatus SDIO_GetITStatus(uint32_t SDIO_IT);
void SDIO_ClearITPendingBit(uint32_t SDIO_IT);

//Interanl DMAcontroller
void SDIO_IDMACmd(FunctionalState NewState);
void SDIO_IDMA_ITConfig(uint32_t SDIO_IT, FunctionalState NewState);
ITStatus SDIO_GetIDMAITStatus(uint32_t SDIO_IDMA_IT);
void SDIO_IDMA_ClearITPendingBit(uint32_t SDIO_IDMA_IT);
uint32_t SDIO_DES_Init(uint32_t blocksize, uint32_t blocknum, uint32_t descr_addr, uint32_t block_addr);
void SDIO_IDMA_Read(uint32_t blocksize, uint32_t blocknum, uint32_t descr_addr, uint32_t dst_addr);
void SDIO_IDMA_Write(uint32_t blocksize, uint32_t blocknum, uint32_t descr_addr, uint32_t src_addr);

//uint32_t SDIO_GetShortResponse(void);
//uint32_t SDIO_GetLongResponse0(void);
//uint32_t SDIO_GetLongResponse1(void);
//uint32_t SDIO_GetLongResponse2(void);
//uint32_t SDIO_GetLongResponse3(void);

#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_SDIO_H__ */

/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/
