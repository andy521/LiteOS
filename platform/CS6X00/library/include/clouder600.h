/*
 * clouder600.h
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


#ifndef __CLOUDER600__H__
#define __CLOUDER600__H__

#include "stdint.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined  USE_STDPERIPH_DRIVER
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will
   be based on direct access to peripherals registers
   */
/*#define USE_STDPERIPH_DRIVER*/
#endif /* USE_STDPERIPH_DRIVER */

#define __CM0_REV                 0 /*!< Core Revision r0p0                            */
#define __MPU_PRESENT             0 /*!< CLOUDER600 do not provide MPU                  */
#define __NVIC_PRIO_BITS          2 /*!< CLOUDER600 uses 4 Bits for the Priority Levels */
//#define __Vendor_SysTickConfig    0 /*!< Set to 1 if different SysTick Config is used  */

/*!< Interrupt Number Definition */
typedef enum IRQn
{
    /******  Cortex-M0 Processor Exceptions Numbers *****************************/
    NonMaskableInt_IRQn       = -14,    /*!< 2  Non Maskable Interrupt          */
    HardFault_IRQn            = -13,    /*!< 3  Cortex-M0 Hard Fault Interrupt  */
    SVC_IRQn                  = -5,     /*!< 11 Cortex-M0 SV Call Interrupt     */
    PendSV_IRQn               = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt     */
    SysTick_IRQn              = -1,     /*!< 15 Cortex-M0 System Tick Interrupt */

    /* -------------------  Extern Specific Interrupt Numbers  ---------------- */
    WDT_IRQn                  =  0,     /*!<  Window WatchDog Interrupt         */
    RTC_IRQn                  =  1,     /*!<  RTC through EXTI Line Interrupt   */
    TIMER_IRQn                =  2,     /*!<  TIMER Interrupt                   */
    ETH_IRQn                  =  3,     /*!<  ETHERNET Interrupt                */
    PLC_IRQn                  =  4,     /*!<  PLC Interrupt                     */
    SDIO_IRQn                 =  5,     /*!<  SDIO Interrupt                    */
    USB_IRQn                  =  6,     /*!<  USB Interrupt                     */
    DMA_IRQn                  =  7,     /*!<  DMA Interrupt                     */
    SPIM0_IRQn                =  10,     /*!<  SPIM0 Interrupt                  */
    SPIM1_IRQn                =  11,        /*!<  SPIM1 Interrupt                   */
    SPIS_IRQn                 =  12,    /*!<  SPIS Interrupt                    */
    USART0_IRQn               =  14,    /*!<  UART0 Interrupt                   */
    USART1_IRQn               =  15,    /*!<  UART1 Interrupt                   */
    USART2_IRQn               =  16,    /*!<  UART2 Interrupt                   */
    USART3_IRQn               =  29,    /*!<  UART3 Interrupt                   */
    USART4_IRQn               =  30,    /*!<  UART4 Interrupt                   */
    I2S_IRQn                  =  17,    /*!<  I2S Interrupt                     */
    I2C0_IRQn                 =  18,    /*!<  I2C0 Interrupt                    */
    I2C1_IRQn                 =  19,    /*!<  I2C1 Interrupt                    */
    GPIO0_IRQn                =  20,    /*!<  GPIO0 Interrupt                   */
    GPIO1_IRQn                =  21,    /*!<  GPIO1 Interrupt                   */
    GPIO2_IRQn                =  22,    /*!<  GPIO2 Interrupt                   */
    GPIO3_IRQn                =  23,    /*!<  GPIO3 Interrupt                   */
    GPIO4_IRQn                =  24,    /*!<  GPIO4 Interrupt                   */
    GPIO5_IRQn                =  25,    /*!<  GPIO5 Interrupt                   */
    GPIO6_IRQn                =  26     /*!<  GPIO6 Interrupt                   */
} IRQn_Type;

/**
  * @}
  */

#include "core_cm0.h"
//#include "system_clouder600.h"
//#include <stdint.h>
//#include "arm_comm.h"
/** @addtogroup Exported_types
  * @{
  */

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
//#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;
typedef enum {UNSELECTED = 0, SELECTED = !UNSELECTED} SelectState;

typedef struct
{
    uint8_t mac[6];
} MacAddr;

#ifdef CR600_LIB_RELEASE
    #define LIB_PRINTF(...)
#else
    #include <stdio.h>
    #define LIB_PRINTF(...)    printf(__VA_ARGS__)
#endif

#define CR600_PANIC(text)       \
    {LIB_PRINTF("PANIC!\n%s\n", text);  \
      while(1);}

#define CR600_FATAL()       \
    while(1){};
/** @addtogroup Peripheral_registers_structures
  * @{
  */

/* ************************************************************************** */
/*                                                                            */
/*                           CLOUDER600 REG MEM_MAP                           */
/*                                                                            */
/* ************************************************************************** */
#define FLASH_BASE         ((uint32_t)0x20000000) /*!< FLASH base address in the alias region  clouder600 cch_data*/
#define SRAM_BASE          ((uint32_t)0x10000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE        ((uint32_t)0x40040000) /*!< Peripheral base address in the alias region */
#define PLC_BASE           ((uint32_t)0x30000000) /*!< PLC base address in the alias region*/

/*!clouder600 < Peripheral memory map */

#define APBPERIPH_BASE        PERIPH_BASE
//#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000)
//#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x08000000)

#define USB_BASE           (APBPERIPH_BASE + 0x00000000)
#define ETH_BASE           (APBPERIPH_BASE + 0x00040000)
#define DMA_BASE           (APBPERIPH_BASE + 0x00042000)
#define MMC_BASE           (APBPERIPH_BASE + 0x00043000)
#define CCH_BASE           (APBPERIPH_BASE + 0x00044000)
#define SSIM0_BASE         (APBPERIPH_BASE + 0x00045000)

#define SSIM1_BASE         (APBPERIPH_BASE + 0x00050000)
#define SSIS0_BASE         (APBPERIPH_BASE + 0x00051000)

#define USART0_BASE        (APBPERIPH_BASE + 0x00052000)
#define USART1_BASE        (APBPERIPH_BASE + 0x00053000)
#define USART2_BASE        (APBPERIPH_BASE + 0x00054000)
#define USART3_BASE        (APBPERIPH_BASE + 0x0005d000)
#define USART4_BASE        (APBPERIPH_BASE + 0x0005e000)

#define I2C0_BASE          (APBPERIPH_BASE + 0x00055000)
#define I2C1_BASE          (APBPERIPH_BASE + 0x00056000)

#define I2S_BASE           (APBPERIPH_BASE + 0x00057000)

#define TIM_BASE           (APBPERIPH_BASE + 0x00058000)
#define WDT_BASE           (APBPERIPH_BASE + 0x00059000)
#define RTC_BASE           (APBPERIPH_BASE + 0x0005A000)
#define SYSCFG_BASE        (APBPERIPH_BASE + 0x0005B000)

#define PWM_BASE           (APBPERIPH_BASE + 0x0005C000)
#define PWM0_BASE          (APBPERIPH_BASE + 0x0005C000)
#define PWM1_BASE          (APBPERIPH_BASE + 0x0005C020)
#define PWM2_BASE          (APBPERIPH_BASE + 0x0005C040)
#define PWM3_BASE          (APBPERIPH_BASE + 0x0005C060)

#define GPIO0_BASE         (APBPERIPH_BASE + 0x00060000)
#define GPIO1_BASE         (APBPERIPH_BASE + 0x00061000)
#define GPIO2_BASE         (APBPERIPH_BASE + 0x00062000)
#define GPIO3_BASE         (APBPERIPH_BASE + 0x00063000)
#define GPIO4_BASE         (APBPERIPH_BASE + 0x00064000)
#define GPIO5_BASE         (APBPERIPH_BASE + 0x00065000)
#define GPIO6_BASE		   (APBPERIPH_BASE + 0x00066000)

#define TIM1_BASE		   (TIM_BASE + 0x00)
#define TIM2_BASE		   (TIM_BASE + 0x14)
#define TIM3_BASE		   (TIM_BASE + 0x28)
#define TIM4_BASE		   (TIM_BASE + 0x3C)
#define TIM5_BASE		   (TIM_BASE + 0x50)
#define TIM6_BASE		   (TIM_BASE + 0x64)
#define TIM7_BASE		   (TIM_BASE + 0x78)
#define TIM8_BASE		   (TIM_BASE + 0x8C)

#ifdef CR600_LIB
#include "clouder600_reg.h"
#endif

/**
  * @brief Analog to Digital Converter
  */
/**
  * @}
  */

/**
 * @}
 */

#ifdef USE_STDPERIPH_DRIVER
#include "clouder600_conf.h"
#endif

/** @addtogroup Exported_macro
  * @{
  */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600__H__ */


/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/
