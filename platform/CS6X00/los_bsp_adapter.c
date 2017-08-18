/*
    here we can include some standard header file
*/
#include <stdio.h>
#include <string.h>
/*
    here include some special hearder file you need
*/
//#include "cmsis_os.h"

#include "cr600_lib.h"
#include "los_bsp_adapter.h"
#include "los_bsp_led.h"
#include "los_bsp_key.h"
#include "los_bsp_uart.h"
#include "los_bsp_lwip.h"
#include "LM75A.h"

/* while use bsp code to start system tick, don't use LOS header */
#define INCLUDE_LOS_HEADER
#ifdef INCLUDE_LOS_HEADER
#include "los_tick.ph"
#include "los_base.h"
#include "los_task.ph"
#include "los_swtmr.h"
#include "los_hwi.h"
#endif

/*****************************************************************************
    global var
 *****************************************************************************/
/* current system Freq , should be set according to the microchip */
const unsigned int sys_clk_freq = 125000000;

/* tick count per second , don't change this */
const unsigned int tick_per_second = 1000;
static unsigned int g_ucycle_per_tick = 0;

/*
    if g_use_ram_vect == 1, we should use sct file STM32F429I-LiteOS.sct
    and we can use LOS_HwiCreate(), LOS_HwiDelete() dynamically regist a irq func
    if g_use_ram_vect == 0, we use default vector table in rom start at address 0x00000000
*/
const unsigned char g_use_ram_vect = 0;

/*****************************************************************************
    LOS function extern 
 *****************************************************************************/
extern void LOS_SetTickSycle(unsigned int);
extern void LOS_TickHandler(void);
extern unsigned int osGetVectorAddr(void);



/*****************************************************************************
 Function    : osTickStart
 Description : Set system tick reqister, and start system tick exception
              Note that This function is called by LOS_Start() In LiteOS kernel.
              so, please don't init system tick before LiteOS kernel Inited
              in your own system.
 Input       : None
 Output      : None
 Return      : LOS_OK
 *****************************************************************************/
unsigned int osTickStart(void)
{
    unsigned int uwRet = 0;
    
    /* This code section LOS need, so don't change it */
    g_ucycle_per_tick = sys_clk_freq / tick_per_second;
    LOS_SetTickSycle(g_ucycle_per_tick);
    
    /* 
      Set system tick relaod register valude, current register valude and start
      system tick exception.
      Note: here can be replaced by some function , for example in Stm32 bsp
      you can just call SysTick_Config(sys_clk_freq/tick_per_second);
    */

    /* configure the systick counter */
    SysTick_Config(g_ucycle_per_tick);

    /* configure the systick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
    
    return uwRet;

}

/*****************************************************************************
 Function    : SysTick_Handler
 Description : system tick interrupt handler.
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void SysTick_Handler(void)
{
    /*
        LOS need call LOS_TickHandler() in SysTick_Handler, don't change it,
        otherwise, LiteOS will not work.
    */
    LOS_TickHandler();
    
    /*add your code here */
    
    return;
}

/*****************************************************************************
 Function    : LosAdapIntInit
 Description : config vector table in ram. please see g_use_ram_vect illustration
               this is used for arm cortex-M3/M4
 Input       : None
 Output      : None
 Return      : LOS_OK
 *****************************************************************************/
void LosAdapIntInit(void)
{
    /* 
        1:ReLoad vector table address at ram . if do nothing , vector table is
        located in rom 0x00000000
        2:set nvic irq priority group

        Note: here can be replaced by some function , for example in Stm32 bsp
        you can just call SCB->VTOR = osGetVectorAddr(); and
        NVIC_SetPriorityGrouping(OS_NVIC_AIRCR_PRIGROUP);
    */
    if (g_use_ram_vect)
    {
        *(volatile UINT32 *)OS_NVIC_VTOR = osGetVectorAddr();
        *(volatile UINT32 *)OS_NVIC_AIRCR = (0x05FA0000 | OS_NVIC_AIRCR_PRIGROUP << 8);
    }

    return;
}

/*****************************************************************************
 Function    : LosAdapIrqEnable
 Description : external interrupt enable, and set priority
               this function is called by LOS_HwiCreate(),
               so here can use bsp func to inplemente it 
               Note : if don't use LOS_HwiCreate(), leave it empty.
 Input       : irqnum: external interrupt number
               prior: priority of this interrupt
 Output      : None
 Return      : None
 *****************************************************************************/
void LosAdapIrqEnable(unsigned int irqnum, unsigned short prior)
{
    /*
        enable irq , for example in stm32 bsp you can use
        NVIC_EnableIRQ((IRQn_Type)irqnum);
    */
    nvicSetIRQ(irqnum);
    /*
        set irq priority , for example in stm32 bsp you can use
        NVIC_SetPriority((IRQn_Type)irqnum, prior);
    */
    nvicSetIrqPRI(irqnum, prior << 4);
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
void LosAdapIrqDisable(unsigned int irqnum)
{
    /* 
        disable irq, for example in stm32 bsp you can use
        NVIC_DisableIRQ((IRQn_Type)irqnum);
    */
    nvicClrIRQ(irqnum);
    return;
}

static void LOS_EvbRccInit(void)
{
    RCC_PLL0Config(31250000, 32, 1, 1, ENABLE, ENABLE);
    RCC_PLL1Config(31250000, 221, 6, 1, ENABLE, ENABLE);
}

/*****************************************************************************
 Function    : LOS_EvbSetup
 Description : enable the device on the dev baord
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbSetup(void)
{
    __asm volatile("cpsid i");
    
    LOS_EvbRccInit();
    LOS_EvbUartInit();
    LOS_EvbLedInit();
    LOS_EvbKeyInit();
    LOS_EvbLwipInit();
    LM75A_Init();
    mqtt_client_init();
    return;
}

/*****************************************************************************
 Function    : LOS_EvbTrace
 Description : trace printf
 Input       : const char *str
 Output      : None
 Return      : None
 *****************************************************************************/
void LOS_EvbTrace(const char *str)
{
    LOS_EvbUartWriteStr(str);
    return;
}

/*!
 * @brief delay us
 *
 * 这是一个使用while循环的微妙延时函数，误差在1%以内，基于系统时钟167MHZ。
 * 但是会占用较多的cpu资源，所以使用在freertos启动前，freertos启动后可使用
 * vTaskDelay或vTaskDelayUntil进行延时，这样几乎不会占用cpu资源
 *
 * @param[in] time_us : number of delay us
 *
 * @return void
 */
void cr600_delay_us(uint32_t time_us)
{
    volatile uint32_t delay;
    volatile uint32_t us = time_us;

    while (us--)
    {
        delay = 12;
        while (delay--);
    }
}

/*!
 * @brief delay ms
 *
 * 这是一个使用while循环的微妙延时函数，误差在1%以内，基于系统时钟167MHZ。
 * 但是会占用较多的cpu资源，所以使用在freertos启动前，freertos启动后可使用
 * vTaskDelay或vTaskDelayUntil进行延时，这样几乎不会占用cpu资源
 *
 * @param[in] time_ms : number of delay ms
 *
 * @return void
 */
void cr600_delay_ms(uint32_t time_ms)
{
    volatile uint32_t ms = time_ms;
    while (ms--)
        cr600_delay_us(1000);
}
