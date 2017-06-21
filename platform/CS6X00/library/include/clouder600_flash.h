/*
 * clouder600_flash.h
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


#ifndef __CLOUDER600_FLASH_H__
#define __CLOUDER600_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"

/**
  * @brief  FLASH Init structure definition
  */

typedef struct
{
    uint8_t FLASH_SPIMode;          /*!< standard or dual or quad wire mode> !*/

    FunctionalState FLASH_TimeOut;      /*!< whether use timeout >! */

} FLASH_InitTypeDef;

typedef enum
{
    FLASH_ERROR_WRP,
    FLASH_ERROR_ADDR,
    FLASH_COMPLETE,
    FLASH_TIMEOUT
} FLASH_Status;


/* Exported macro ------------------------------------------------------------*/
#define FLASH_SPIMode_Standard  0x1
#define FLASH_SPIMode_Dual      0x2
#define FLASH_SPIMode_Quad      0x4

#define FLASH_TimeOut_Enable    0x1
#define FLASH_TimeOut_Disable   0x0

#define FLASH_SectorTimeOut     ((uint32_t)0x0002A000)
#define FLASH_BlockTimeOut      ((uint32_t)0x00200000)
#define FLASH_PageTimeOut       ((uint32_t)0x0002A000)

/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/

void FLASH_StructInit(FLASH_InitTypeDef *FLASH_InitStruct);

#if defined(__ICCARM__)

__ramfunc void FLASH_Init(FLASH_InitTypeDef *FLASH_InitStruct);

__ramfunc void   FLASH_Unlock(void);

__ramfunc void   FLASH_Lock(void);
/* Data transfers functions ***************************************************/
__ramfunc FLASH_Status FLASH_EraseSector(uint32_t addr);

__ramfunc FLASH_Status FLASH_Erase64K(uint32_t addr);

__ramfunc FLASH_Status FLASH_Erase32K(uint32_t addr);

__ramfunc FLASH_Status FLASH_EraseAll(void);

__ramfunc FLASH_Status FLASH_ProgramWord(uint32_t addr, uint32_t Data);

__ramfunc FLASH_Status FLASH_ProgramHalfWord(uint32_t addr, uint16_t Data);

__ramfunc FLASH_Status FLASH_ProgramByte(uint32_t addr, uint8_t Data);

__ramfunc FLASH_Status FLASH_ProgramPage(uint32_t addr, uint8_t *Data, uint32_t len);

__ramfunc uint32_t FLASH_Read_ID(void);

#elif defined(__CC_ARM)

#pragma arm section code = "__RAM_FUNC"
void FLASH_Init(FLASH_InitTypeDef *FLASH_InitStruct);

void FLASH_Unlock(void);

void FLASH_Lock(void);
/* Data transfers functions ***************************************************/
FLASH_Status FLASH_EraseSector(uint32_t addr);

FLASH_Status FLASH_Erase64K(uint32_t addr);

FLASH_Status FLASH_Erase32K(uint32_t addr);

FLASH_Status FLASH_EraseAll(void);

FLASH_Status FLASH_ProgramWord(uint32_t addr, uint32_t Data);

FLASH_Status FLASH_ProgramHalfWord(uint32_t addr, uint16_t Data);

FLASH_Status FLASH_ProgramByte(uint32_t addr, uint8_t Data);

FLASH_Status FLASH_ProgramPage(uint32_t addr, uint8_t *Data, uint32_t len);

uint32_t FLASH_Read_ID(void);
#pragma arm section

#else
		#error "not supported compiler"
#endif

#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_FLASH_H__ */

/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/
