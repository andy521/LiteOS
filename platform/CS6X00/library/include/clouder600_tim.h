/*
 * clouder600_tim.h
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


#ifndef __CLOUDER600_TIM_H__
#define __CLOUDER600_TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"
#define TIM1 TIM1_BASE
#define TIM2 TIM2_BASE
#define TIM3 TIM3_BASE
#define TIM4 TIM4_BASE

#define Usr_Prgm_Mode   1
#define Free_Mode       0

/**
  * @brief  TIM Init structure definition
  */

typedef struct
{
    FunctionalState Timer_State;  /* 0:diable 1:enable */
    uint8_t Timer_Mode;           /* 0:free-running mode 1:user-defined count mode */
    FunctionalState TimerIntMask;  /* 0:not masked 1:masked */
    uint32_t LoadCountValue;      /* Value to be loaded into TimerN */
} TIM_InitTypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void TIM_Init(uint32_t TIMx, TIM_InitTypeDef *TIM_InitStruct);  /* n=1,2,3,4,5,6,7,8 */
void TIM_StructInit(TIM_InitTypeDef *TIM_InitStruct);
void TIM_Cmd(uint32_t TIMx, FunctionalState NewState);
/* Data transfers functions ***************************************************/
void TIM_LoadCount(uint32_t TIMx, uint32_t LoadValue);
uint32_t TIM_GetCurrentValue(uint32_t TIMx);
void TIM_ITConfig(uint32_t TIMx, FunctionalState NewState);
uint8_t TIM_GetITStatus(uint32_t TIMx);
void TIM_ClearITPendingBit(uint32_t TIMx);

#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_TIM_H__ */
