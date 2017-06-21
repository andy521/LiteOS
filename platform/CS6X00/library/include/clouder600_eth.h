/*
 * clouder600_eth.h
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


#ifndef __CLOUDER600_ETH_H__
#define __CLOUDER600_ETH_H__

#include "clouder600.h"

#define ETH_LINK_DOWN       0   /* link down */
#define ETH_LINK_UP         1   /* link up */

#define ETH_SPEED_10M       1   /* 10Mbps */
#define ETH_SPEED_100M      2   /* 100Mbps */
#define ETH_SPEED_1000M     3   /* 1000Mbps */

#define ETH_HALF_DUPLEX     1   /* half duplex */
#define ETH_FULL_DUPLEX     2   /* full duplex */

#define ETH_NO_PHY          0   /* 没有接PHY，也没有使用CROSS模式 */
#define ETH_MII             1   /* MII phy interface */
#define ETH_RMII            2   /* RMII phy interface */
#define ETH_MII_CROSS_INNER 3   /* MII Cross模式，CR600 MAC RX和TX时钟由内部产生 */
#define ETH_MII_CROSS_EXT   4   /* MII Cross模式，CR600 MAC RX和TX时钟由外部提供 */

/*!
 * @brief ethernet init
 *
 * @param[in] phyif: set phy interface to MII or RMII
 *
 * @param[in] phy_init: pointer of phy init function
 *
 * @param[in] mac: mac address
 *
 * @return null
 */
void ETH_Init(uint32_t phyif, void(*phy_init)(void), MacAddr mac);

/*!
 * @brief ethernet send
 *
 * @param[in] data: pointer of the data that need to send from ethernet
 *
 * @param[in] size: size of the data
 *
 * @return null
 */
void ETH_LinkSend(uint8_t *data, uint32_t size);

/*!
 * @brief ethernet send, using ETH hardware to fill checksum
 *
 * @param[in] data: pointer of the data that need to send from ethernet
 *
 * @param[in] size: size of the data
 *
 * @return null
 */
void ETH_LinkSendHwChk(uint8_t *data, uint32_t size);

/*!
 * @brief eth transparent switch
 *
 * @param[in] state: ENABLE/DISABLE
 *
 * @return void
 */
void ETH_TranspSwitch(FunctionalState state);

/*!
 * @brief eth free receive buffer
 *
 * @param[in] data: pointer to recv data
 *
 * @return SUCCESS: free success
 *         ERROR:   free failed
 */
ErrorStatus ETH_FreeRxBuf(uint8_t *data);

/*!
 * @brief set the mac address to ETH register
 *
 * @param[in] mac: pointer of the mac data that will be set
 *
 * @return SUCCESS: set success
 *         ERROR:   set failed
 */
ErrorStatus ETH_SetMacAddr(MacAddr mac);

/*!
 * @brief get the mac address from ETH register
 *
 * @param[in] void
 *
 * @return MacAddr: the mac address
 */
MacAddr ETH_GetMacAddr(void);

/*!
 * @brief read phy register
 *
 * @param[in] PhyAddr: phy address
 *
 * @param[in] RegOffset: phy register address
 *
 * @param[out] data: phy register data will be store to this pointer
 *
 * @return SUCCESS: read success
 *         ERROR:   read failed
 */
ErrorStatus ETH_ReadPhy(uint32_t PhyAddr, uint32_t RegOffset, int16_t *data);

/*!
 * @brief write data to phy register
 *
 * @param[in] PhyAddr: phy address
 *
 * @param[in] RegOffset: phy register address
 *
 * @param[in] data: the data that need to write to the phy register
 *
 * @return SUCCESS: write success
 *         ERROR:   write failed
 */
ErrorStatus ETH_WritePhy(uint32_t PhyAddr, uint32_t RegOffset, int16_t data);

/*!
 * @brief set ethernet link status
 *
 * @param[in] status: ETH_LINK_DOWN
 *                    ETH_LINK_UP
 *
 * @return SUCCESS: set success
 *         ERROR:   set failed
 */
ErrorStatus ETH_SetLinkStatus(uint32_t status);

uint32_t ETH_GetLinkStatus(void);
/*!
 * @brief set ethernet link speed
 *
 * @param[in] speed:  ETH_SPEED_10M (10Mbps)
 *                    ETH_SPEED_100M (100Mbps)
 *                    ETH_SPEED_1000M (1000Mbps)
 *
 * @return SUCCESS: set success
 *         ERROR:   set failed
 */
ErrorStatus ETH_SetLinkSpeed(uint32_t speed);

/*!
 * @brief set ethernet link duplex mode
 *
 * @param[in] duplex: ETH_HALF_DUPLEX (half duplex)
 *                    ETH_FULL_DUPLEX (full duplex)
 *
 * @return SUCCESS: set success
 *         ERROR:   set failed
 */
ErrorStatus ETH_SetLinkDuplexMode(uint32_t duplex);

void (*ETH_GetPhyInitFun(void))(void);

uint32_t ETH_GetETHMode(void);

#endif /* __CLOUDER600_ETH_H__ */
