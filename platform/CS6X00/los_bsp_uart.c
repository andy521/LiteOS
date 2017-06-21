#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "cr600_lib.h"

#include "los_bsp_uart.h"

int fputc(int ch, FILE *f)
{
    USART_SendData(USART2, ch);
    return ch;
}

/*****************************************************************************
 Function    : LOS_EvbUartInit
 Description : usart init
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbUartInit(void)
{
    USART_InitTypeDef USART_InitS;

    RCC_PeriphClockCmd(RCC_Periph_USART2Clock, ENABLE);

    USART_InitS.USART_BaudRate    = 115200;
    USART_InitS.USART_WordLength  = USART_WordLength_8b;
    USART_InitS.USART_StopBits    = USART_StopBits_1;
    USART_InitS.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitS.USART_Parity      = USART_Parity_No;
    USART_InitS.USART_Mode        = USART_Mode_Tx | USART_Mode_Rx;

    USART_DeInit(USART2);
    
    USART_Init(USART2, &USART_InitS);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);   // enable the rx interrupt

    NVIC_EnableIRQ(USART2_IRQn);
}

/*****************************************************************************
 Function    : LOS_EvbUartWriteStr
 Description : send str to usart
 Input       : str      --- string need to send
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbUartWriteStr(const char* str)
{
    while (*str)
    {
        USART_SendData(USART2, *str);
        str++;
    }
    
    return;
}
