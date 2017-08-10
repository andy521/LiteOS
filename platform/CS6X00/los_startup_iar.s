/* 
	The Clouder600 Startup Asm File 
	Cortex-M version
*/
        MODULE  ?cstartup
	
        ; forward declaration of sections
        SECTION CSTACK : DATA : NOROOT( 3 )
        SECTION .intvec : CODE : NOROOT( 2 )
	
        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
		PUBLIC  Reset_Handler
        
		DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler             ; Reset Handler
        DCD     NMI_Handler               ; NMI Handler
        DCD     HardFault_Handler         ; Hard Fault Handler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
       	DCD		SVC_Handler				  ; SVCall Handler
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD		PendSV_Handler			  ; PendSV Handler
        DCD     SysTick_Handler           ; SysTick Handler
        
                 ; External Interrupts
        DCD     IWDG_IRQHandler           ; Window Watchdog
        DCD     RTC_IRQHandler            ; RTC
        DCD     TIMER_IRQHandler          ; TIMER
        DCD     ETH_IRQHandler            ; RTC
        DCD     0                         ; PLC
        DCD     SDIO_IRQHandler            ; MMC
        DCD     USB_IRQHandler            ; USB
        DCD     DMA_IRQHandler            ; DMA
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved        
        DCD     SPIM0_IRQHandler          ; SSIM0
        DCD     SPIM1_IRQHandler          ; SSIM1
        DCD     SPIS_IRQHandler           ; SSIS
        DCD     0                         ; Reserved
        DCD     USART0_IRQHandler          ; UART 0
        DCD     USART1_IRQHandler          ; UART 1
        DCD     USART2_IRQHandler          ; UART 2
        DCD     I2S_IRQHandler            ; I2S
        DCD     I2C0_IRQHandler           ; I2C0
        DCD     I2C1_IRQHandler           ; I2C1
        DCD     GPIO0_IRQHandler          ; GPIO 0
        DCD     GPIO1_IRQHandler          ; GPIO 1
        DCD     GPIO2_IRQHandler          ; GPIO 2
        DCD     GPIO3_IRQHandler          ; GPIO 3
        DCD     GPIO4_IRQHandler          ; GPIO 4
        DCD     GPIO5_IRQHandler          ; GPIO 5
        DCD     GPIO6_IRQHandler          ; GPIO 6
        DCD     0                         ; Reserved
        DCD     0                         ; Reserved
        DCD     USART3_IRQHandler          ; Reserved
        DCD     USART4_IRQHandler          ; Reserved
        DCD     0                         ; Reserved

		THUMB
		;PUBWEAK Reset_Handler
		SECTION .text:CODE:REORDER( 2 )
Reset_Handler

        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0
		
        SECTION .text:CODE:REORDER(1)
NMI_Handler
        B NMI_Handler
        
        SECTION .text:CODE:REORDER(1)
HardFault_Handler
        B HardFault_Handler

		PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler
        
	PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler     

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler
        
        PUBWEAK IWDG_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
IWDG_IRQHandler
        B IWDG_IRQHandler
        
        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_IRQHandler       
        B RTC_IRQHandler
        
        PUBWEAK TIMER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER_IRQHandler
        B TIMER_IRQHandler
        
        PUBWEAK ETH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ETH_IRQHandler
        B ETH_IRQHandler
        
;        PUBWEAK PLC_IRQHandler
;        SECTION .text:CODE:REORDER:NOROOT(1)
;PLC_IRQHandler
;        B PLC_IRQHandler
;        
        PUBWEAK SDIO_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SDIO_IRQHandler
        B SDIO_IRQHandler
        
        PUBWEAK USB_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USB_IRQHandler
        B USB_IRQHandler
        
        PUBWEAK DMA_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA_IRQHandler
        B DMA_IRQHandler
        
        PUBWEAK SPIM0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPIM0_IRQHandler
        B SPIM0_IRQHandler
        
        PUBWEAK SPIM1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPIM1_IRQHandler
        B SPIM1_IRQHandler
        
        PUBWEAK SPIS_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPIS_IRQHandler
        B SPIS_IRQHandler
        
        PUBWEAK USART0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART0_IRQHandler
        B USART0_IRQHandler
        
        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART1_IRQHandler
        B USART1_IRQHandler
        
        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART2_IRQHandler
        B USART2_IRQHandler
        
        PUBWEAK I2S_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2S_IRQHandler
        B I2S_IRQHandler
        
        PUBWEAK I2C0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C0_IRQHandler
        B I2C0_IRQHandler
        
        PUBWEAK I2C1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_IRQHandler
        B I2C1_IRQHandler
        
        PUBWEAK GPIO0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIO0_IRQHandler
        B GPIO0_IRQHandler
        
        PUBWEAK GPIO1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIO1_IRQHandler
        B GPIO1_IRQHandler
        
        PUBWEAK GPIO2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIO2_IRQHandler
        B GPIO2_IRQHandler
        
        PUBWEAK GPIO3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIO3_IRQHandler
        B GPIO3_IRQHandler
        
        PUBWEAK GPIO4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIO4_IRQHandler
        B GPIO4_IRQHandler
        
        PUBWEAK GPIO5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIO5_IRQHandler
        B GPIO5_IRQHandler
        
        PUBWEAK GPIO6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIO6_IRQHandler
        B GPIO6_IRQHandler

        PUBWEAK USART3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART3_IRQHandler
        B USART3_IRQHandler
        
        PUBWEAK USART4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART4_IRQHandler
        B USART4_IRQHandler
	
        END
