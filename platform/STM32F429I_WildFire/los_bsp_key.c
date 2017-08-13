#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#include "los_bsp_key.h"

//������������������
#define KEY1_PIN                  GPIO_Pin_0                 
#define KEY1_GPIO_PORT            GPIOA                      
#define KEY1_GPIO_CLK             RCC_AHB1Periph_GPIOA

void LOS_EvbKeyInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	/*��������GPIO�ڵ�ʱ��*/
	RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK,ENABLE);
    /*ѡ�񰴼�������*/
	GPIO_InitStructure.GPIO_Pin = KEY1_PIN; 
    /*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
    /*�������Ų�����Ҳ������*/
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	/* ���������ٶ� */
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_2MHz;
    /*ʹ������Ľṹ���ʼ������*/
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);

    return;
}

/*****************************************************************************
 Function    : LOS_EvbGetKeyVal
 Description : Get GIOP Key value
 Input       : int KeyNum
 Output      : None
 Return      : KeyVal
 *****************************************************************************/
unsigned int LOS_EvbGetKeyVal(int KeyNum)
{
    unsigned int KeyVal = LOS_GPIO_ERR; 

    if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_PIN)==1)
        KeyVal = LOS_KEY_PRESS;
    //add you code here.

    return KeyVal;
}

