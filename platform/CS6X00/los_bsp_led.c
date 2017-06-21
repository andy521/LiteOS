#include "cr600_lib.h"

#include "los_bsp_led.h"

/*****************************************************************************
 Function    : LOS_EvbLedInit
 Description : init led gpio
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbLedInit(void)
{
    GPIO_InitTypeDef GPIO_InitS;
    
    /* Enable GPIO4 Clock */
    RCC_PeriphClockCmd(RCC_Periph_GPIO4Clock, ENABLE);

    /* Configure GPIO4_6 as LED */
    GPIO_InitS.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitS.GPIO_Mode = GPIO_Mode_Output;
    GPIO_Init(GPIO4, &GPIO_InitS);
    
    GPIO_ResetBits(GPIO4, GPIO_Pin_6);
    GPIO_ResetBits(GPIO4, GPIO_Pin_7);
    return ;
}

/*****************************************************************************
 Function    : LOS_EvbLedControl
 Description : control leds on/off
 Input       : index        --- which led to control
             : cmd          --- LED_ON/LED_OFF
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbLedControl(int index, int cmd)
{
    void (*gpioCtrl)(uint32_t , uint8_t );

    /* param check */
    if(index > LOS_LED1 | cmd != LED_ON && cmd != LED_OFF)
        return;
    
    if(cmd == LED_ON)
        gpioCtrl = GPIO_SetBits;

    if(cmd == LED_OFF)
        gpioCtrl = GPIO_ResetBits;

    switch (index)
    {
        case LOS_LED1:
            gpioCtrl(GPIO4, GPIO_Pin_6);
            break;
        case LOS_LED2:
            gpioCtrl(GPIO4, GPIO_Pin_7);
            break;
        default:
            break;
    }

    return ;
}
