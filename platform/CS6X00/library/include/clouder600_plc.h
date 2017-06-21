/*
 * clouder600_plc.h
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

#ifndef __CLOUDER600_PLC_H_
#define __CLOUDER600_PLC_H_

#include "clouder600.h"

#define PLC_MODE_SLAVE          0
#define PLC_MODE_ADHOC          1

/* plc multihopping mode */
#define PLC_HOP_OFF             0
#define PLC_HOP_MODE1           1
#define PLC_HOP_MODE2           2
#define PLC_HOP_MODE3           3
#define PLC_HOP_MODE4           4
#define PLC_HOP_MODE5           5

#define PLC_FLOODING_SLAVE      0
#define PLC_FLOODING_MASTER     1

typedef struct
{
    uint8_t     other_type;
    uint8_t     coordinator;
    uint8_t     max_preferred;
    uint8_t     max_hop;
    uint32_t    max_neighbour;
    uint32_t    max_route;
    uint32_t    hello_interval;
    uint32_t    hello_interval_fast;
    uint32_t    hello_jitter;
    uint32_t    report_interval;
    uint32_t    report_interval_fast;
    uint8_t     max_hello;
    uint8_t     max_notify;
    uint8_t     reserved[30];
}S_CNS_PARAM;

typedef struct
{
    uint16_t    pkg_count[8];
    uint8_t     array;
    uint8_t     role;
    uint8_t     reserved[30];
}S_FLOODING_PARAM;

typedef struct
{
    S_CNS_PARAM         cns;
    S_FLOODING_PARAM    flooding;
    uint8_t             debug;
    uint8_t             reserved[3];
}S_HOP_PARAM;


typedef struct
{
    uint8_t     qossetup;
    uint8_t     qostype;
    uint8_t     reserved[2];
    uint32_t    qosparam;
    uint8_t     priority;
    uint8_t     maxcon;
    uint8_t     minfrm;
    uint8_t     retrynum;
    uint32_t    waittm;
} S_QOS_TBL;

typedef struct
{
    uint16_t        uver;
    uint16_t        plc_mode;
    uint8_t         mac_addr[6];
    uint16_t        reserved1;
    uint32_t        class1_5;
    uint8_t         bssid[6];
    uint16_t        reserved2;
    uint8_t         pwk[16];
    uint32_t        tonemapnum;
    uint32_t        reserved4;
    uint8_t         notch[27];
    uint8_t         reserved5[5];
    uint8_t         power_ctrl[216];
    uint8_t         power_lvl;
    uint8_t         rssi;
    uint8_t         reserved6[2];
    uint32_t        zxoffset;
    uint32_t        zxrehdtm60;
    uint32_t        zxfehdtm60;
    uint32_t        zxrehdtm50;
    uint32_t        zxfehdtm50;

    uint8_t         powcon_index;
    uint8_t         reserved7[3];
    uint8_t         power_con0[216];
    uint8_t         power_level0;
    uint8_t         reserved8[3];
    uint8_t         power_con1[216];
    uint8_t         power_level1;
    uint8_t         reserved9[3];
    uint8_t         power_con2[216];
    uint8_t         power_level2;
    uint8_t         reserved10[3];
    uint8_t         power_con3[216];
    uint8_t         power_level3;
    uint8_t         reserved11[3];
    uint8_t         power_con4[216];
    uint8_t         power_level4;
    uint8_t         reserved12[3];
    uint8_t         power_con5[216];
    uint8_t         power_level5;
    uint8_t         reserved13[3];
    uint8_t         power_con6[216];
    uint8_t         power_level6;
    uint8_t         reserved14[3];
    uint8_t         power_con7[216];
    uint8_t         power_level7;
    uint8_t         reserved15[3];
    uint8_t         power_con8[216];
    uint8_t         power_level8;
    uint8_t         reserved16[3];
    uint8_t         power_con9[216];
    uint8_t         power_level9;
    uint8_t         reserved17[3];
    uint8_t         cmd_level;
    uint8_t         reserved18[3];
    uint8_t         factory_cmd_pass[16];
    uint8_t         vendor_id[8];
    uint8_t         param_id[8];
    uint16_t        kep_tim;
    uint16_t        reserved19;
    uint8_t         autorun;
    uint8_t         fast_ack_mode;
    uint8_t         reserved20[2];
    S_QOS_TBL       qos_tbl[4];
    uint32_t        sndbuf_quesize;
    uint32_t        rcvbuf_quesize;
    uint32_t        ceMode;
    
    S_HOP_PARAM     hop;                    /* plc hop */
} S_SYSTEM_FLASH, *PS_SYSTEM_FLASH;


typedef struct
{
    S_SYSTEM_FLASH   param;
    uint16_t         sum;
} S_SYSTEM_FLASH_AND_SUM;

/* command head struct */
typedef enum {
    PLC_CMDTYPE_ETH,
    PLC_CMDTYPE_PLC,
    PLC_CMDTYPE_UART,
    PLC_CMDTYPE_USER,
    PLC_CMDTYPE_AT
} PLC_CmdType_T;

/* plc&eth data statistics package information */
typedef struct
{
    uint32_t pkg;
    uint32_t size;
    uint32_t pkgSpeed;
    uint32_t sizeSpeed;
}CR600_PkgInfo_T;

/* plc&eth data statistics */
typedef struct
{
    CR600_PkgInfo_T ethTxAll;
    CR600_PkgInfo_T ethTxCnf;
    CR600_PkgInfo_T ethRxAll;
    CR600_PkgInfo_T ethRxCast;
    CR600_PkgInfo_T ethRxLwip;
    CR600_PkgInfo_T ethRxPlc;
    CR600_PkgInfo_T ethOverFlow;
    CR600_PkgInfo_T ethMissFrame;
    CR600_PkgInfo_T ethRxErr;
    
    CR600_PkgInfo_T phyRxErr;
    
    CR600_PkgInfo_T plcTxAll;
    CR600_PkgInfo_T plcTxLink;
    CR600_PkgInfo_T plcTxHop;
    CR600_PkgInfo_T plcTxPhy;
    CR600_PkgInfo_T plcTxCnf;
    CR600_PkgInfo_T plcTxDrop;
    
    CR600_PkgInfo_T plcRxAll;
    CR600_PkgInfo_T plcRxCast;
    CR600_PkgInfo_T plcRxLwip;
    CR600_PkgInfo_T plcRxEth;
    CR600_PkgInfo_T plcRxMng;
    
    CR600_PkgInfo_T ucoreTx;
    CR600_PkgInfo_T ucoreTxErr;
    CR600_PkgInfo_T ucoreTxDrop;
    CR600_PkgInfo_T ucoreRx;
    CR600_PkgInfo_T ucoreRxErr;
} CR600_Statistics_T;

const uint8_t *PLC_GetLibVersion(void);
const uint8_t *PLC_GetUcoreVersion(void);
const uint8_t *PLC_GetCompileTime(void);

void PLC_InitParam(void *param, uint32_t flash_write(void));

void PLC_Init(uint32_t mode, MacAddr mac, uint32_t hopMode);

void PLC_HopDebugConfig(FunctionalState state);

void PLC_SetCheckPlcCommands(FunctionalState status);

FunctionalState PLC_GetCheckPlcCommands(void);

FlagStatus PLC_GetLinkStatus(void);

ErrorStatus PLC_PhySend(MacAddr dstMac, uint8_t *data, int len);
ErrorStatus PLC_HopSend(MacAddr dstMac, uint8_t *dma_addr, int len);
ErrorStatus PLC_LinkSend(uint8_t *data, uint32_t size);

void PLC_PhySwitch(FunctionalState state);
void PLC_HopSwitch(FunctionalState state);
void PLC_LinkSwitch(FunctionalState state);

void PLC_GetRelayList(void **list, uint16_t *num);

ErrorStatus PLC_FreeRxBuf(uint8_t *data);

ErrorStatus PLC_ChkQue(void);

ErrorStatus PLC_ReadAFE(uint8_t addr, uint8_t *data);
ErrorStatus PLC_WriteAFE(uint8_t addr, uint8_t data);

ErrorStatus PLC_CmdProc(PLC_CmdType_T cmd_type, uint8_t *data, uint32_t size);

ErrorStatus PLC_GetTml(uint8_t index, char * buffer);

void PLC_UsartSendCallback(void (*func)(const uint8_t *, uint32_t));

const CR600_Statistics_T *CR600_GetStatistics(void);
void CR600_StatisticsClr(void);

#endif /* __CLOUDER600_PLC_H_ */
