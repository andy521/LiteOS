/*
 * clouder600_uart.h
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

#ifndef __CLOUDER600_USART_H__
#define __CLOUDER600_USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"

#ifndef DMA_PER_Uart0TX
#define DMA_PER_Uart0TX 6
#endif

#ifndef DMA_PER_Uart1TX
#define DMA_PER_Uart1TX 8
#endif

#ifndef DMA_PER_Uart2TX
#define DMA_PER_Uart2TX 10
#endif

#ifndef DMA_PER_Uart3TX
#define DMA_PER_Uart3TX 14
#endif

#define USART0 USART0_BASE
#define USART1 USART1_BASE
#define USART2 USART2_BASE
#define USART3 USART3_BASE
#define USART4 USART4_BASE

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**
  * @brief UART Init Structure definition
**/

typedef struct
{
    uint32_t USART_BaudRate;
    uint16_t USART_WordLength;
    uint16_t USART_StopBits;
    uint32_t USART_Parity;
    uint32_t USART_Mode;
    uint32_t USART_HardwareFlowControl;
} USART_InitTypeDef;

#define USART_WordLength_5b          ((uint16_t)0x0000)
#define USART_WordLength_6b          ((uint16_t)0x0001)
#define USART_WordLength_7b          ((uint16_t)0x0002)
#define USART_WordLength_8b          ((uint16_t)0x0003)

#define USART_StopBits_1             ((uint16_t)0x0000)
#define USART_StopBits_1_5           ((uint16_t)0x0004)
#define USART_StopBits_2             ((uint16_t)0x0004)

#define USART_Parity_No              ((uint16_t)0x0000)
#define USART_Parity_Even            ((uint16_t)0x0018)
#define USART_Parity_Odd             ((uint16_t)0x0008)

#define USART_Mode_Tx                ((uint16_t)0x0001)
#define USART_Mode_Rx                ((uint16_t)0x0000)

#define USART_HardwareFlowControl_None             ((uint16_t)0x0000)
#define USART_HardwareFlowControl_RTS_CTS          ((uint16_t)0x0022)

#define USART_IT_CTS                 ((uint16_t)0x0008)
#define USART_IT_RLS                 ((uint16_t)0x0004)
#define USART_IT_TXE                 ((uint16_t)0x0002)
#define USART_IT_RXNE                ((uint16_t)0x0001)
#define USART_IT_CHT                 ((uint16_t)0x0010)

//MSR
#define USART_FLAG_CTS               ((uint16_t)0x0010)
///LSR
#define USART_FLAG_RFE               ((uint16_t)0x0080)
#define USART_FLAG_TXE               ((uint16_t)0x0040)
#define USART_FLAG_RXNE              ((uint16_t)0x0001)
#define USART_FLAG_ORE               ((uint16_t)0x0002)
#define USART_FLAG_FE                ((uint16_t)0x0008)
#define USART_FLAG_PE                ((uint16_t)0x0004)
///
//uint8_t cr600_uart_hardwareflowctrl_flag;

/* Initialization and Configuration functions *********************************/
void USART_DeInit(uint32_t USARTx);
ErrorStatus USART_Init(uint32_t USARTx, USART_InitTypeDef *USART_InitStruct);
void USART_BaudRateCfg(uint32_t USARTx, uint16_t USART_DIV);
void USART_StructInit(USART_InitTypeDef *USART_InitStruct);

void USART_ITConfig(uint32_t USARTx, uint16_t USART_IT, FunctionalState NewState);
/* Data transfers functions ***************************************************/
void USART_SendData(uint32_t USARTx, uint8_t Data);
uint8_t USART_ReceiveData(uint32_t USARTx);
void USART_SendBreak(uint32_t USARTx);
ErrorStatus USART_DMA_M2PInit(uint32_t USARTx, uint32_t DMA_ch, uint32_t m_addr, uint32_t N_Data);
ErrorStatus USART_DMA_P2MInit(uint32_t USARTx, uint32_t DMA_ch, uint32_t m_addr, uint32_t N_Data);
uint16_t USART_GetFlagStatus(uint32_t USARTx);
ITStatus   USART_GetITStatus(uint32_t USARTx, uint16_t USART_IT);
void USART_ClearITPendingBit(uint32_t USARTx, uint16_t USART_IT);

#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_UART_H__ */

