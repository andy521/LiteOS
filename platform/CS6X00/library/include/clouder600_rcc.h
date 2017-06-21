/*
 * clouder600_rcc.h
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


#ifndef __CLOUDER600_RCC_H__
#define __CLOUDER600_RCC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"

/**
  * @lcl RCC definition
*/
#define RCC_Remap_SWD             ((uint32_t)0xf0000000) /*!<Ethernet CPU SWD     mode mapping 0x54*/

#define RCC_PLL0Source            ((uint32_t)0x00000001)
#define RCC_PLL0_N                ((uint32_t)0x0000000f)//                         
#define RCC_PLL0_M                ((uint32_t)0x00000ff0)//                       
#define RCC_PLL0_PDRST            ((uint32_t)0x00001000)//                       
#define RCC_PLL0_OD               ((uint32_t)0x00030000)//                       
#define RCC_PLL0_BP               ((uint32_t)0x00100000)//                       
#define RCC_PLL0_LKDT             ((uint32_t)0x01000000)//                       

#define RCC_PLL1Source            ((uint32_t)0x00000002)
#define RCC_PLL1_N                ((uint32_t)0x0000000f)//                         
#define RCC_PLL1_M                ((uint32_t)0x00000ff0)//                       
#define RCC_PLL1_PDRST            ((uint32_t)0x00001000)//                       
#define RCC_PLL1_OD               ((uint32_t)0x00030000)//                       
#define RCC_PLL1_BP               ((uint32_t)0x00100000)//                       
#define RCC_PLL1_LKDT             ((uint32_t)0x01000000)//                       



#define RCC_DRV0                  ((uint32_t)0x00000000)//
#define RCC_DRV90                 ((uint32_t)0x00000003)//
#define RCC_DRV180                ((uint32_t)0x00000002)//
#define RCC_DRV270                ((uint32_t)0x00000001)//
#define RCC_SMP0                  ((uint32_t)0x00000000)//
#define RCC_SMP90                 ((uint32_t)0x00000003)//
#define RCC_SMP180                ((uint32_t)0x00000002)//
#define RCC_SMP270                ((uint32_t)0x00000001)//



#define RCC_PLCAFE_CLKSource      ((uint32_t)0x00000020)//
#define RCC_CLK_DIV_BUS_TOG       ((uint32_t)0x00000001)// 
#define RCC_CLK_PHS_SDIO_TOG      ((uint32_t)0x00000002)//
#define RCC_CLK_DIV_I2S_TOG        ((uint32_t)0x00000004)//
#define RCC_CLK_DIV_USART0_TOG     ((uint32_t)0x00000008)//
#define RCC_CLK_DIV_USART1_TOG     ((uint32_t)0x00000010)//
#define RCC_CLK_DIV_USART2_TOG     ((uint32_t)0x00000020)//
#define RCC_CLK_DIV_CLKOUT1_TOG    ((uint32_t)0x00000040)//
#define RCC_CLK_DIV_CLKOUT2_TOG    ((uint32_t)0x00000080)//
#define RCC_CLK_PLC_PHS_TOG        ((uint32_t)0x00000100)//
#define RCC_CLK_DIV_PWM_TOG        ((uint32_t)0x00000200)//
#define RCC_CLK_DIV_SSIM0_TOG      ((uint32_t)0x00000400)//
#define RCC_CLK_DIV_USART3_TOG     ((uint32_t)0x00000800)//
#define RCC_CLK_DIV_USART4_TOG     ((uint32_t)0x00001000)//
//
#define RCC_CLK_BUS_DIV            ((uint32_t)0x000001ff)// 
#define RCC_CLK_PHS_SDIO_DRV       ((uint32_t)0x00030000)//
#define RCC_CLK_PHS_SDIO_SMP       ((uint32_t)0x00300000)//
#define RCC_CLK_I2S_MCLK_DIV       ((uint32_t)0x000003ff)//
#define RCC_CLK_I2S_SCLK_DIV       ((uint32_t)0x3fff0000)//
#define RCC_CLK_USART0_DIV         ((uint32_t)0x000003ff)//
#define RCC_CLK_USART1_DIV         ((uint32_t)0x03ff0000)//
#define RCC_CLK_USART2_DIV         ((uint32_t)0x000003ff)//
#define RCC_CLK_CLKOUT1_DIV        ((uint32_t)0x00ff0000)//
#define RCC_CLK_CLKOUT2_DIV        ((uint32_t)0xff000000)//
#define RCC_CLK_PWM_DIV            ((uint32_t)0x00000fff)//
#define RCC_CLK_SSIM0_DIV          ((uint32_t)0x03ff0000)//
#define RCC_CLK_USART3_DIV         ((uint32_t)0x000003ff)//
#define RCC_CLK_USART4_DIV         ((uint32_t)0x03ff0000)//




#define RCC_Periph_DMAClock       ((uint32_t)0x00000001)//                         
#define RCC_Periph_ETHClock       ((uint32_t)0x00000002)//                       
#define RCC_Periph_SDIOClock      ((uint32_t)0x00000004)//                       
#define RCC_Periph_USBClock       ((uint32_t)0x00000008)//                       
#define RCC_Periph_PLCClock       ((uint32_t)0x00000010)//                       
#define RCC_Periph_CCHClock       ((uint32_t)0x00000020)//                       
//#define                         ((uint32_t)0x00000040)//
#define RCC_Periph_SSIM0Clock     ((uint32_t)0x00000080)//                             
#define RCC_Periph_SSIM1Clock     ((uint32_t)0x00000100)//                             
#define RCC_Periph_SSISClock      ((uint32_t)0x00000200)//                            
#define RCC_Periph_USART0Clock    ((uint32_t)0x00000400)//                             
#define RCC_Periph_USART1Clock    ((uint32_t)0x00000800)//                             
#define RCC_Periph_USART2Clock    ((uint32_t)0x00001000)//                             
#define RCC_Periph_I2C0Clock      ((uint32_t)0x00002000)//                            
#define RCC_Periph_I2C1Clock      ((uint32_t)0x00004000)//                            
#define RCC_Periph_I2SClock       ((uint32_t)0x00008000)//                           
#define RCC_Periph_TIMER1Clock    ((uint32_t)0x00010000)//                              
#define RCC_Periph_TIMER2Clock    ((uint32_t)0x00020000)//                              
#define RCC_Periph_TIMER3Clock    ((uint32_t)0x00040000)//                              
#define RCC_Periph_TIMER4Clock    ((uint32_t)0x00080000)//                              
#define RCC_Periph_WDTClock       ((uint32_t)0x00100000)//                           
#define RCC_Periph_RTCClock       ((uint32_t)0x00200000)//                           
#define RCC_Periph_GPIO0Clock     ((uint32_t)0x00400000)//                             
#define RCC_Periph_GPIO1Clock     ((uint32_t)0x00800000)//                             
#define RCC_Periph_GPIO2Clock     ((uint32_t)0x01000000)//                             
#define RCC_Periph_GPIO3Clock     ((uint32_t)0x02000000)//                             
#define RCC_Periph_GPIO4Clock     ((uint32_t)0x04000000)//                             
#define RCC_Periph_GPIO5Clock     ((uint32_t)0x08000000)//                             
#define RCC_Periph_GPIO6Clock     ((uint32_t)0x10000000)//                             
#define RCC_Periph_PWMClock       ((uint32_t)0x20000000)//                           
#define RCC_Periph_USART3Clock    ((uint32_t)0x40000000)//                             
#define RCC_Periph_USART4Clock    ((uint32_t)0x80000000)//                             
////no clock gate ,only for pin share
#define RCC_Periph_CLKOUTClock    ((uint32_t)0x00000040)/// 
//#define RCC_Periph_CLKOUT1Clock   ((uint32_t)0x00000f40)///
//#define RCC_Periph_CLKOUT2Clock   ((uint32_t)0x0000f040)///

#define RCC_Periph_DMAReset      ((uint32_t)0x00000001)//  
#define RCC_Periph_ETHReset      ((uint32_t)0x00000002)//
#define RCC_Periph_SDIOReset     ((uint32_t)0x00000004)//
#define RCC_Periph_USBReset      ((uint32_t)0x00000008)//
#define RCC_Periph_PLCReset      ((uint32_t)0x00000010)//
#define RCC_Periph_CCHReset      ((uint32_t)0x00000020)//
#define RCC_Periph_USART3Reset   ((uint32_t)0x00000040)//      
#define RCC_Periph_SSIM0Reset    ((uint32_t)0x00000080)//      
#define RCC_Periph_SSIM1Reset    ((uint32_t)0x00000100)//      
#define RCC_Periph_SSISReset     ((uint32_t)0x00000200)//     
#define RCC_Periph_USART0Reset   ((uint32_t)0x00000400)//      
#define RCC_Periph_USART1Reset   ((uint32_t)0x00000800)//      
#define RCC_Periph_USART2Reset   ((uint32_t)0x00001000)//      
#define RCC_Periph_I2C0Reset     ((uint32_t)0x00002000)//     
#define RCC_Periph_I2C1Reset     ((uint32_t)0x00004000)//     
#define RCC_Periph_I2SReset      ((uint32_t)0x00008000)//    
#define RCC_Periph_TIMERReset    ((uint32_t)0x00010000)//      
#define RCC_Periph_TIMER0Reset   ((uint32_t)0x00020000)//       
#define RCC_Periph_TIMER1Reset   ((uint32_t)0x00040000)//       
#define RCC_Periph_TIMER2Reset   ((uint32_t)0x00080000)//       
#define RCC_Periph_TIMER3Reset   ((uint32_t)0x00100000)//       
#define RCC_Periph_WDTReset      ((uint32_t)0x00200000)//    
#define RCC_Periph_RTCReset      ((uint32_t)0x00400000)//    
#define RCC_Periph_GPIO0Reset    ((uint32_t)0x00800000)//      
#define RCC_Periph_GPIO1Reset    ((uint32_t)0x01000000)//      
#define RCC_Periph_GPIO2Reset    ((uint32_t)0x02000000)//      
#define RCC_Periph_GPIO3Reset    ((uint32_t)0x04000000)//      
#define RCC_Periph_GPIO4Reset    ((uint32_t)0x08000000)//      
#define RCC_Periph_GPIO5Reset    ((uint32_t)0x10000000)//      
#define RCC_Periph_GPIO6Reset    ((uint32_t)0x20000000)//      
#define RCC_Periph_PWMReset      ((uint32_t)0x40000000)//    
#define RCC_Periph_USART4Reset   ((uint32_t)0x80000000)// 

#define RCC_ETHSPEED100M         ((uint32_t)0x00000000)//        
#define RCC_ETHSPEED10M          ((uint32_t)0x00000004)//        
#define RCC_ETHCLK_INNER         ((uint32_t)0x00000000)//        
#define RCC_ETHCLK_EXT           ((uint32_t)0x00000010)//        

///PLL0 default setting:500MHz
///PLL1 default setting:576MHz
///ADDA clock,fixed to 1.5Mhz
extern uint32_t cr600_osc_clk;
extern uint32_t cr600_pll0_clk;
extern uint32_t cr600_pll1_clk;
extern uint32_t cr600_adda_clk;

///
static uint8_t cr600_uart_hardwareflowctrl_flag;

//void RCC_PinRemapConfig(uint32_t RCC_Remap, FunctionalState NewState);

void RCC_SrstSysn(void);

ErrorStatus RCC_PLL0Config(uint32_t OSC, uint8_t PLLm, uint8_t PLLn, uint8_t PLLod, FunctionalState OldState, FunctionalState NewState);
ErrorStatus RCC_PLL1Config(uint32_t OSC, uint8_t PLLm, uint8_t PLLn, uint8_t PLLod, FunctionalState OldState, FunctionalState NewState);

void RCC_ETHCLKConfig(uint32_t RCC_ETHCLKSrc, uint32_t RCC_ETHCLKSpeed);

void RCC_BUSHCLKConfig(uint32_t RCC_CLK);
void RCC_SDIOCLKConfig(uint32_t RCC_SDIOCLKDrvPhase, uint32_t RCC_SDIOCLKSmpPhase);
void RCC_I2SCLKConfig(uint32_t RCC_I2SCLKSource1, uint32_t RCC_I2SCLKSource2);
void RCC_USART0CLKConfig(uint32_t RCC_USART0CLKSource);
void RCC_USART1CLKConfig(uint32_t RCC_USART1CLKSource);
void RCC_USART2CLKConfig(uint32_t RCC_USART2CLKSource);
void RCC_USART3CLKConfig(uint32_t RCC_USART3CLKSource);
void RCC_USART4CLKConfig(uint32_t RCC_USART4CLKSource);
void RCC_CLKOUT1_Config(uint32_t RCC_CLKOUT1Source);
void RCC_CLKOUT2_Config(uint32_t RCC_CLKOUT2Source);
void RCC_PWMCLKConfig(uint32_t RCC_PWMCLKSource);
void RCC_SPIM0CLKConfig(uint32_t RCC_SPIM0CLKSource);

void RCC_PeriphClockCmd(uint32_t RCC_PeriphClock, FunctionalState NewState);
void RCC_PeriphResetCmd(uint32_t RCC_PeriphReset, FunctionalState NewState);


uint32_t RCC_PLL0_FreqRd(void);
uint32_t RCC_PLL1_FreqRd(void);
uint32_t RCC_BUSCLK_FreqRd(void);
uint32_t RCC_SDIOCLK_FreqRd(void);
uint32_t RCC_SDIOCLK_DrvPhsRd(void);
uint32_t RCC_SDIOCLK_SmpPhsRd(void);
uint32_t RCC_I2SMCLK_FreqRd(void);
uint32_t RCC_I2SSCLK_FreqRd(void);
uint32_t RCC_USARTCLK_FreqRd(uint32_t USARTx);
uint32_t RCC_PWMCLK_FreqRd(void);
uint32_t RCC_SPIM0CLK_FreqRd(void);
uint32_t RCC_CLKOUT1_FreqRd(void);
uint32_t RCC_CLKOUT2_FreqRd(void);
uint32_t RCC_GPIOCLK_FreqRd(void);
uint32_t RCC_RTCCLK_FreqRd(void);
uint32_t RCC_ADCCLK_FreqRd(void);
uint32_t RCC_DACCLK_FreqRd(void);
uint32_t RCC_OSC_FreqRd(void);
uint32_t RCC_ETH_RMII_FreqRd(void);
uint32_t RCC_ETH_MII_FreqRd(void);
uint32_t RCC_PLC_250M_FreqRd(void);
uint32_t RCC_PLC_125M_FreqRd(void);
uint32_t RCC_PLC_62M5_FreqRd(void);
uint32_t RCC_PLC_31M25_FreqRd(void);
FunctionalState RCC_PeriphClock_EnChk(uint32_t RCC_PeriphClock);
SelectState RCC_ETH_PHYCLK_SelChk(void);
SelectState RCC_PLC_62M5_PHSCLK_SelChk(void);
SelectState RCC_PLL0_Select_Chk(void);
SelectState RCC_PLL1_Select_Chk(void);

#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_RCC_H__ */

/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/

