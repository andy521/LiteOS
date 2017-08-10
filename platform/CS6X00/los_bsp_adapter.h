#ifndef _LOS_BSP_ADAPTER_H
#define _LOS_BSP_ADAPTER_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern void LOS_EvbSetup(void);
extern void LOS_EvbTrace(const char *str);

extern void cr600_delay_us(uint32_t time_us);
extern void cr600_delay_ms(uint32_t time_ms);
#endif
