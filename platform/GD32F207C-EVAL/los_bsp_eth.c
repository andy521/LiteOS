#include "los_bsp_eth.h"
#include "los_bsp_lwip.h"
#include "gd32f20x_rcu.h"
#include "gd32f20x_gpio.h"
static volatile uint32_t enet_init_status = 0;

static void eth_gpio_config(void);
static void eth_dma_config(void);
static void eth_nvic_config(void);

/*****************************************************************************
 Function    : LOS_EvbEthInit
 Description : mac init
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbEthInit(void)
{
    __disable_irq();
#ifdef USE_ENET_INTERRUPT
    eth_nvic_config();
#endif /* USE_ENET_INTERRUPT */
  
    /* configure the GPIO ports for ethernet pins */
    eth_gpio_config();
    
    /* configure the ethernet MAC/DMA */
    eth_dma_config();

    if (enet_init_status == 0){
        while(1){
        }
    }

#ifdef USE_ENET_INTERRUPT
    enet_interrupt_enable(ENET_DMA_INT_NIE);
    enet_interrupt_enable(ENET_DMA_INT_RIE);
#endif /* USE_ENET_INTERRUPT */  

    /* configure systick clock source as HCLK */
    systick_clksource_set(SYSTICK_CLKSOURCE_HCLK);

    return;
}

/*****************************************************************************
 Function    : eth_gpio_config
 Description : eth gpio configuration
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
static void eth_gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
  
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8);
  
    /* enable SYSCFG clock */
    rcu_periph_clock_enable(RCU_AF);

    rcu_pll2_config(RCU_PLL2_MUL10);
    rcu_osci_on(RCU_PLL2_CK);
    rcu_osci_stab_wait(RCU_PLL2_CK);
    /* get 50MHz from CK_PLL2 on CKOUT0 pin (PA8) to clock the PHY */
    rcu_ckout0_config(RCU_CKOUT0SRC_CKPLL2,RCU_CKOUT0_DIV1);
    gpio_ethernet_phy_select(GPIO_ENET_PHY_RMII);

    /* PA1: ETH_RMII_REF_CLK */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
    /* PA2: ETH_MDIO */    
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);
    /* PA7: ETH_RMII_CRS_DV */    
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_7);

    /* PC1: ETH_MDC */
    gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
    /* PC4: ETH_RMII_RXD0 */    
    gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_4);
    /* PC5: ETH_RMII_RXD1 */    
    gpio_init(GPIOC, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_5);

    /* PB11: ETH_RMII_TX_EN */
    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_11);
    /* PB12: ETH_RMII_TXD0 */    
    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
    /* PB13: ETH_RMII_TXD1 */    
    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);    
}

/*****************************************************************************
 Function    : eth_dma_config
 Description : eth dma configuration
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
static void eth_dma_config(void)
{
    ErrStatus reval_state = ERROR;
    
    /* enable ethernet clock  */
    rcu_periph_clock_enable(RCU_ENET);
    rcu_periph_clock_enable(RCU_ENETTX);
    rcu_periph_clock_enable(RCU_ENETRX);
    
    /* reset ethernet on AHB bus */
    enet_deinit();

    reval_state = enet_software_reset();
    if(reval_state == ERROR){
        while(1){}
    }

    enet_init_status = enet_init(ENET_AUTO_NEGOTIATION, ENET_NO_AUTOCHECKSUM, ENET_BROADCAST_FRAMES_PASS);
}

/*****************************************************************************
 Function    : eth_nvic_config
 Description : eth NVIC configuration
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
static void eth_nvic_config(void)
{
    nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x0);
    nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
    nvic_irq_enable(ENET_IRQn, 0, 0);
}

/*****************************************************************************
 Function    : ETH_IRQHandler
 Description : eth interrupt handler
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void ETH_IRQHandler(void)
{
    /* clear the enet DMA Rx interrupt pending bits */
    enet_interrupt_flag_clear(ENET_DMA_INT_FLAG_RS_CLR);
    enet_interrupt_flag_clear(ENET_DMA_INT_FLAG_NI_CLR);
    /* handles all the received frames */
    while(enet_rxframe_size_get()){   
        lwip_pkt_handle();
    }    
}
