#include "cr600_lib.h"

#include "los_bsp_key.h"
#include "los_bsp_led.h"


/*****************************************************************************
 Function    : LOS_EvbKeyInit
 Description : key init
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbKeyInit(void)
{
    /* configure User key */
    GPIO_InitTypeDef GPIO_InitS;
    
    /* Enable GPIO4 Clock */
    RCC_PeriphClockCmd(RCC_Periph_GPIO4Clock, ENABLE);

    /* Configure GPIO4_5 pin */
    GPIO_InitS.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitS.GPIO_Mode = GPIO_Mode_Input;
    GPIO_InitS.GPIO_IntEn = GPIO_Func_Int;
    GPIO_InitS.GPIO_IntType = GPIO_Int_Level;
    GPIO_InitS.GPIO_IntPolarity = GPIO_Int_Low;
    GPIO_Pull_Cmd(GPIO4,GPIO_Pin_5,ENABLE);
    GPIO_ITConfig(GPIO4,GPIO_Pin_5,ENABLE);
    GPIO_Init(GPIO4, &GPIO_InitS);

    /* Enable GPIO4_IRQn */
    NVIC_EnableIRQ(GPIO4_IRQn);
    
    return;
}

/*****************************************************************************
 Function    : LosAdapIrqDisable
 Description : external interrupt disable
               this function is called by LOS_HwiDelete(), so use bsp func
               to inplemente it
               Note : if don't use LOS_HwiDelete(), leave it empty
 Input       : irqnum: external interrupt number
 Output      : None
 Return      : None
 *****************************************************************************/

void GPIO4_IRQHandler(){
    GPIO_ITConfig(GPIO4,GPIO_Pin_5,DISABLE);
};

/*****************************************************************************
 Function    : LOS_EvbGetKeyVal
 Description : Get GIOP Key value
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
unsigned int LOS_EvbGetKeyVal(int KeyNum)
{
    unsigned int KeyVal = LOS_GPIO_ERR;

    if(GPIO_ReadInputDataBit(GPIO4, GPIO_Pin_5) == Bit_RESET)
        KeyVal = LOS_KEY_PRESS;

    return KeyVal;
}
