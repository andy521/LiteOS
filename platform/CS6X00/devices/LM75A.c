/*
 * LM75A.c
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


#include "LM75A.h"

void LM75A_Init(void)
{
    I2C_InitTypeDef I2C_InitS;
    I2C_InitS.I2C_Mode = I2C_Mode_Master;       //Master
    I2C_InitS.I2C_AddrMode = I2C_AddrMode_7B;   //7bit
    I2C_InitS.I2C_ClkSpeed = 300000;
    I2C_Init(I2C1_BASE, &I2C_InitS);
    I2C_Cmd(I2C1_BASE, ENABLE);
}

void I2C_Write(uint8_t Reg_Addr, uint8_t *buf, uint8_t len)
{
    I2C_GenerateSTART(I2C1_BASE, ENABLE);
    I2C_SendAddr(I2C1_BASE, Reg_Addr);
    I2C_ActiveSendBuffer(I2C1_BASE, buf, len);
    I2C_GenerateSTOP(I2C1_BASE, ENABLE);
}

void I2C_Read(uint8_t Reg_Addr, uint8_t *buf, uint8_t len)
{
    I2C_GenerateSTART(I2C1_BASE, ENABLE);
    I2C_SendAddr(I2C1_BASE, Reg_Addr);
    I2C_ActiveReceiveBuffer(I2C1_BASE, buf, len);
    I2C_GenerateSTOP(I2C1_BASE, ENABLE);
}

int16_t LM75A_ReadTemperature(void)
{
    uint8_t temp[3];
    int16_t temperature;

    temp[0] = 0x00; //temperature reg

    I2C_Write(LM75A_ADDR, temp, 1);
    I2C_Read(LM75A_ADDR, (temp + 1), 2);
    if (temp[1] & 0x80)
        temperature = ~(((((temp[1] & 0x7F) << 8) | temp[2]) >> 5) * LM75A_ACCURACY / 8) + 1;
    else
        temperature = ((((temp[1] & 0x7F) << 8) | temp[2]) >> 5) * LM75A_ACCURACY / 8;

    return temperature;
}



