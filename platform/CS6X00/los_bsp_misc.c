#include "stdint.h"
/* IAR includes. */
#include "intrinsics.h"

#include "cr600_lib.h"

#include "los_sys.h"

/* Each task maintains its own interrupt status in the critical nesting
variable. */
static uint32_t uxCriticalNesting = 0xaaaaaaaa;

long xQueueGenericSendFromISR(void *xQueue, const void * const pvItemToQueue, long * const pxHigherPriorityTaskWoken, const long xCopyPosition)
{
    return (long)1;
}
    
void vPortEnterCritical(void)
{
    __asm volatile("cpsid i");
    uxCriticalNesting++;
	__DSB();
	__ISB();
}

void vPortExitCritical(void)
{
	if(uxCriticalNesting == 0)
    {
        __asm volatile("cpsid i");
        while(1);
    }
    
	uxCriticalNesting--;
	if( uxCriticalNesting == 0 )
	{
		__asm volatile("cpsie i");
	}
}

uint32_t xTaskGetTickCount(void)
{
    return LOS_TickCountGet();
}

void ETH_LinkReceive(uint8_t *data, uint32_t size)
{
    /* do nothing */
    
    /* free the eth rx buffer */
    ETH_FreeRxBuf(data);
}

void ETH_TranspReceive(uint8_t *data, uint32_t size)
{
    /* do nothing */
    
    /* free the eth rx buffer */
    ETH_FreeRxBuf(data);
}
