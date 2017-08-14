#include "stdint.h"
/* IAR includes. */
#include "intrinsics.h"

#include "cr600_lib.h"

#include "los_sys.h"

void LOS_EvbMiscInit(void)
{
    /*init Flash*/
    FLASH_InitTypeDef FLASH_InitStruct;
    FLASH_InitStruct.FLASH_SPIMode = FLASH_SPIMode_Quad;
    FLASH_InitStruct.FLASH_TimeOut = ENABLE;
    FLASH_Init(&FLASH_InitStruct);
    
    RCC_PLL0Config(31250000, 32, 1, 1, ENABLE, ENABLE);
    RCC_PLL1Config(31250000, 221, 6, 1, ENABLE, ENABLE);
}