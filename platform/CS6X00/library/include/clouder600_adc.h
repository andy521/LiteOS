/*
 * clouder600_adc.h
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


#ifndef __CLOUDER600_ADC_H__
#define __CLOUDER600_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Data transfers functions ***************************************************/

void ADC_Cmd(FunctionalState NewState);
void ADC_ConvertStart(uint32_t ADCx);
void ADC_ConvertWaitStart(uint32_t ADCx);
uint16_t ADC_GetConversionValue(uint32_t ADCx);
uint16_t ADC_Read(uint32_t ADCx);  /* n=0,1,2,3 */


#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_ADC_H__ */

/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/
