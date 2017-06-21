/*
 * clouder600_pwm.h
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


#ifndef __CLOUDER600_PWM_H__
#define __CLOUDER600_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"
#define PWM0 PWM0_BASE
#define PWM1 PWM1_BASE
#define PWM2 PWM2_BASE
#define PWM3 PWM3_BASE

#define PWM_Mode_Norm   0
#define PWM_Mode_Sin    1


/**
  * @brief  PWM Init structure definition
  */

typedef struct
{
    uint16_t PWM_HighCycle;  /* High pulse cycle number */
    uint16_t PWM_Cycle;     /* Cycle number*/
    uint8_t PWM_Mode;       /* Mode of the PWM signal, 0:normal 1:sin*/
} PWM_InitTypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void PWM_Init(uint32_t PWMx, PWM_InitTypeDef *PWM_InitStruct); //x=0,1,2,3
void PWM_StructInit(PWM_InitTypeDef *PWM_InitStruct);

/* Data transfers functions ***************************************************/
void PWM_SetCycle(uint32_t PWMx, uint16_t PWM_Cycle);  //
void PWM_SetHighCycle(uint32_t PWMx, uint16_t PWM_HighCycle);  //
void PWM_SetMode(uint32_t PWMx, uint8_t PWM_Mode);
void PWM_Cmd(uint32_t PWMx, FunctionalState NewState);
uint16_t PWM_SRAM_Rd(uint16_t PWM_Addr);
void PWM_SRAM_Wr(uint16_t PWM_Addr, uint16_t PWM_Data);

#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_PWM_H__ */

/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/
