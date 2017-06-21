/*
 * clouder600_cch.h
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


#ifndef __CLOUDER600_CCH_H__
#define __CLOUDER600_CCH_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "clouder600.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Data transfers functions ***************************************************/
void CCH_Cmd(FunctionalState NewState);

#if defined(__ICCARM__)

__ramfunc void CCH_Flush(uint32_t addr, uint32_t len);
__ramfunc void CCH_FlushAll(void);
__ramfunc void CCH_WaitUntilIdle(void);

#elif defined(__CC_ARM)

#pragma arm section code = "__RAM_FUNC"
void CCH_Flush(uint32_t addr, uint32_t len);
void CCH_FlushAll(void);
void CCH_WaitUntilIdle(void);
#pragma arm section

#else
    #error "not supported compiler"
#endif
	
#ifdef __cplusplus
}
#endif

#endif  /* __CLOUDER600_CCH_H__ */

/********(C) COPYRIGHT Cloudersemi *****END OF FILE**************/
