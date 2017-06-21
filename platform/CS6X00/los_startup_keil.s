;/**
;  ******************************************************************************
;  * @file    startup_cr600.s
;  * @author  MCU Device
;  * @version V1.0.0   
;  * @date    22-Feb-2017
;  * @brief   CR600 startup code.
;  ******************************************************************************
;;  */
; Amount of memory (in bytes) allocated for Stack and Heap
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000800

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector table entries with the exceptions ISR address
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                   ; Top of Stack
                DCD     Reset_Handler                  ; Reset Handler
                DCD     NMI_Handler                    ; NMI Handler
                DCD     HardFault_Handler              ; Hard Fault Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     SVC_Handler                    ; SVCall Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     PendSV_Handler                 ; PendSV Handler
                DCD     SysTick_Handler                ; SysTick Handler

                ; External Interrupts
                DCD     IWDG_IRQHandler                	; IWDG Handler 
                DCD     RTC_IRQHandler                 	; RTC Handler  
                DCD     TIMER_IRQHandler                ; TIMER Handler
                DCD     ETH_IRQHandler               	; ETH Handler  
                DCD     PLC_IRQHandler             		; PLC Handler  
                DCD     SDIO_IRQHandler             	; SDIO Handler 
                DCD     USB_IRQHandler            		; USB Handler  
                DCD     DMA_IRQHandler                  ; DMA Handler  
                DCD     0       						; Reserved
                DCD     0     							; Reserved
                DCD     SPIM0_IRQHandler     			; SPIM0 Handler
                DCD     SPIM1_IRQHandler           		; SPIM1 Handler
                DCD     SPIS_IRQHandler 				; SPIS Handler 
                DCD     0             					; Reserved
                DCD     USART0_IRQHandler               ; USART0 Handler
                DCD     USART1_IRQHandler               ; USART1 Handler
                DCD     USART2_IRQHandler            	; USART2 Handler
                DCD     I2S_IRQHandler                  ; I2S Handler
                DCD     I2C0_IRQHandler                	; I2C0 Handler
                DCD     I2C1_IRQHandler                	; I2C1 Handler
                DCD     GPIO0_IRQHandler               	; GPIO0 Handler
                DCD     GPIO1_IRQHandler               	; GPIO1 Handler
                DCD     GPIO2_IRQHandler               	; GPIO2 Handler
                DCD     GPIO3_IRQHandler               	; GPIO3 Handler
                DCD     GPIO4_IRQHandler               	; GPIO4 Handler
                DCD     GPIO5_IRQHandler               	; GPIO5 Handler
                DCD     GPIO6_IRQHandler              	; GPIO6 Handler
                DCD     0                             	; Reserved
                DCD     0                              	; Reserved
                DCD     0                              	; Reserved
                DCD     0                              	; Reserved
                DCD     0               				; Reserved
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler   PROC
                EXPORT  Reset_Handler                 [WEAK]
				IMPORT  __main
				IMPORT  SystemInit  
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                    [WEAK]
                B       .
                ENDP
				
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler              [WEAK]
                B       .
                ENDP
				
SVC_Handler     PROC
                EXPORT  SVC_Handler                    [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                 [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  IWDG_IRQHandler                [WEAK]
                EXPORT  RTC_IRQHandler                 [WEAK]
                EXPORT  TIMER_IRQHandler               [WEAK]
                EXPORT  ETH_IRQHandler                 [WEAK]
                EXPORT  PLC_IRQHandler                 [WEAK]
                EXPORT  SDIO_IRQHandler                [WEAK]
                EXPORT  USB_IRQHandler                 [WEAK]
                EXPORT  DMA_IRQHandler                 [WEAK]
                EXPORT  SPIM0_IRQHandler               [WEAK]
                EXPORT  SPIM1_IRQHandler               [WEAK]
                EXPORT  SPIS_IRQHandler                [WEAK]
                EXPORT  USART0_IRQHandler              [WEAK]
                EXPORT  USART1_IRQHandler              [WEAK]
                EXPORT  USART2_IRQHandler              [WEAK]
                EXPORT  I2S_IRQHandler                 [WEAK]
                EXPORT  I2C0_IRQHandler                [WEAK]
                EXPORT  I2C1_IRQHandler                [WEAK]
                EXPORT  GPIO0_IRQHandler               [WEAK]
                EXPORT  GPIO1_IRQHandler               [WEAK]
                EXPORT  GPIO2_IRQHandler               [WEAK]
                EXPORT  GPIO3_IRQHandler               [WEAK]
                EXPORT  GPIO4_IRQHandler               [WEAK]
                EXPORT  GPIO5_IRQHandler               [WEAK]
                EXPORT  GPIO6_IRQHandler               [WEAK]

IWDG_IRQHandler  
RTC_IRQHandler   
TIMER_IRQHandler 
ETH_IRQHandler   
PLC_IRQHandler   
SDIO_IRQHandler  
USB_IRQHandler   
DMA_IRQHandler   
SPIM0_IRQHandler 
SPIM1_IRQHandler 
SPIS_IRQHandler  
USART0_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
I2S_IRQHandler   
I2C0_IRQHandler  
I2C1_IRQHandler  
GPIO0_IRQHandler 
GPIO1_IRQHandler 
GPIO2_IRQHandler 
GPIO3_IRQHandler 
GPIO4_IRQHandler 
GPIO5_IRQHandler 
GPIO6_IRQHandler 

                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;************************ (C) COPYRIGHT 2017 Cloudersemi *****END OF FILE*****
