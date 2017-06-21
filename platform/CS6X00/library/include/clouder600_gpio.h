/*
 * clouder600_gpio.h
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


#ifndef __CLOUDER600_GPIO_H__
#define __CLOUDER600_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO0 GPIO0_BASE
#define GPIO1 GPIO1_BASE
#define GPIO2 GPIO2_BASE
#define GPIO3 GPIO3_BASE
#define GPIO4 GPIO4_BASE
#define GPIO5 GPIO5_BASE
#define GPIO6 GPIO6_BASE

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"

/**
  * @brief  GPIO Init structure definition
  */
typedef struct
{
    uint8_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
                                       This parameter can be any value of @ref GPIO_pins_define */

    uint8_t GPIO_Mode;              /*!< Specifies the operating mode for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef
                                        0: input  1: output  */


    uint8_t GPIO_IntEn;             /*!< Specifies the int enable function for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef
                                        0 每 Configure Port A bit as normal GPIO signal (default)
                                                                                1 每 Configure Port A bit as interrupt  */


    uint8_t GPIO_IntType;               /*!< Specifies the int type selection for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef
                    0 每 Level-sensitive (default)
                                        1 每 Edge-sensitive  */


    uint8_t GPIO_IntPolarity;           /*!< Specifies the int polarity of edge or level sensitivity
                                       for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef
                    0 每 falling edge or low level sensitive(default)
                                        1 每 rising edge or high level sensitive*/

    uint8_t GPIO_IntDebounce;           /*!< Specifies the int debounced function for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef
                    0 每 No debounce (default)
                                        1 每 Enable debounce*/

} GPIO_InitTypeDef;


#define GPIO_Pin_None           ((uint16_t)0x0000)
#define GPIO_Pin_0              ((uint16_t)0x0001)
#define GPIO_Pin_1              ((uint16_t)0x0002)
#define GPIO_Pin_2              ((uint16_t)0x0004)
#define GPIO_Pin_3              ((uint16_t)0x0008)
#define GPIO_Pin_4              ((uint16_t)0x0010)
#define GPIO_Pin_5              ((uint16_t)0x0020)
#define GPIO_Pin_6              ((uint16_t)0x0040)
#define GPIO_Pin_7              ((uint16_t)0x0080)
#define GPIO_Pin_All            ((uint16_t)0x00ff)

#define GPIO_Mode_Input         ((uint16_t)0x0000)
#define GPIO_Mode_Output        ((uint16_t)0x0001)

#define GPIO_Func_Norm          ((uint16_t)0x0000)
#define GPIO_Func_Int           ((uint16_t)0x0001)

#define GPIO_Int_Level          ((uint16_t)0x0000)
#define GPIO_Int_Edge           ((uint16_t)0x0001)

#define GPIO_Int_Low            ((uint16_t)0x0000)
#define GPIO_Int_High           ((uint16_t)0x0001)

#define GPIO_Debounce_No        ((uint16_t)0x0000)
#define GPIO_Debounce_Yes       ((uint16_t)0x0001)

#define GPIO_Remap_USART0        ((uint32_t)0x00060000)
#define GPIO_Remap_USART1        ((uint32_t)0x18000000)

typedef enum
{
    Bit_RESET = 0,
    Bit_SET
} BitAction;


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void	GPIO_Init(uint32_t GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);  //n=0,1,2,3,4,5,6
void	GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct);
uint8_t GPIO_ReadInputDataBit(uint32_t GPIOx, uint8_t GPIO_Pin);
uint8_t GPIO_ReadInputData(uint32_t GPIOx);
uint8_t GPIO_ReadOutputDataBit(uint32_t GPIOx, uint8_t GPIO_Pin);
uint8_t GPIO_ReadOutputData(uint32_t GPIOx);
void	GPIO_SetBits(uint32_t GPIOx, uint8_t GPIO_Pin);
void	GPIO_ResetBits(uint32_t GPIOx, uint8_t GPIO_Pin);
void	GPIO_WriteBit(uint32_t GPIOx, uint8_t GPIO_Pin, BitAction BitVal);
void	GPIO_Write(uint32_t GPIOx, uint8_t PortVal);
void	GPIO_ITConfig(uint32_t GPIOx, uint8_t GPIO_Pin, FunctionalState NewState);
uint8_t GPIO_GetITStatus(uint32_t GPIOx, uint8_t GPIO_Pin);
void	GPIO_ClearITPendingBit(uint32_t GPIOx, uint8_t GPIO_Pin);
void	GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);
void	GPIO_Pull_Cmd(uint32_t GPIOx, uint8_t GPIO_Pin, FunctionalState NewState);
/*
void GPIO_GrpPin_Pull_Cmd(uint32_t GPIO_Grp,FunctionalState NewState);
void GPIO_SepPin_Pull_Cmd(uint32_t GPIO_Grp,uint8_t GPIO_Pin,FunctionalState NewState);
*/

#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_GPIO_H__ */

/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/
