#include "los_bsp_eth.h"

void ETH_ParaInit(ETH_InitPara* ETH_InitParaStruct);

void eth_gpio_config(void)
{

}

void eth_nvic_config(void)
{
    NVIC_InitPara   NVIC_InitStructure; 

    /* Enable the Ethernet global Interrupt */
    NVIC_InitStructure.NVIC_IRQ = ETH_IRQn;
    NVIC_InitStructure.NVIC_IRQPreemptPriority = 12;
    NVIC_InitStructure.NVIC_IRQSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQEnable = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void eth_mac_config(void)
{
    ETH_InitPara ETH_InitParaStruct;

      /* Enable ETHERNET clock  */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC | RCC_AHB1Periph_ETH_MAC_Tx |
                         RCC_AHB1Periph_ETH_MAC_Rx, ENABLE);
    ETH_ParaInit(&ETH_InitParaStruct);

    ETH_Init(&ETH_InitParaStruct, );
}


/*****************************************************************************
 Function    : LOS_EvbEthInit
 Description : ethernet init
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbEthInit(void)
{
    /* Configure the GPIO ports for ethernet pins */
    eth_gpio_config();

    /* Config NVIC for Ethernet */
    eth_nvic_config();

    /* Configure the Ethernet MAC */
    eth_mac_config();
}