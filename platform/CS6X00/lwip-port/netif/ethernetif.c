/**
 * @file
 * Ethernet Interface for standalone applications (without RTOS)
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

#include "cr600_lib.h"

#include "lwip/mem.h"
#include "netif/etharp.h"
#include "ethernetif.h"
#include "KSZ8041.h"
#include "los_event.h"
#include "los_task.h"
#include "los_queue.h"

#include <string.h>


/* network interface name */
#define IFNAME0 'G'
#define IFNAME1 'D'

#define MAC_ADDR    "\xF4\x83\xE1\x01\x01\x14"

static struct netif *cr600_netif;

/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
static void low_level_init(struct netif *netif)
{
    /* set MAC hardware address length */
    netif->hwaddr_len = ETHARP_HWADDR_LEN;

    /* set MAC hardware address */
    netif->hwaddr[0] =  MAC_ADDR[0];
    netif->hwaddr[1] =  MAC_ADDR[1];
    netif->hwaddr[2] =  MAC_ADDR[2];
    netif->hwaddr[3] =  MAC_ADDR[3];
    netif->hwaddr[4] =  MAC_ADDR[4];
    netif->hwaddr[5] =  MAC_ADDR[5];
    
    /* maximum transfer unit */
    netif->mtu = 1500;

    /* device capabilities */
    /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;
    
    printf("MAC: %02X-%02X-%02X-%02X-%02X-%02X\r\n", MAC_ADDR[0], MAC_ADDR[1], MAC_ADDR[2], MAC_ADDR[3], MAC_ADDR[4], MAC_ADDR[5]);

    ETH_Init(ETH_MII, KSZ8041_Init, *(MacAddr *)MAC_ADDR);
    
    return;
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

static uint8_t payload_assembly[1514];

static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
    struct pbuf *q;

#if ETH_PAD_SIZE
    pbuf_header(p, -ETH_PAD_SIZE);   /* drop the padding word */
#endif

    if (p->next != NULL) // it has more than one pbuf, then package should be send together
    {
        q = p;
        int len = q->tot_len;
        
        if(len > 1514)
        {
            printf("package is too large\r\n");
            while(1);
        }
        uint8_t *k = payload_assembly;

        for (; q != NULL; q = q->next)
        {
            memcpy(k, q->payload, q->len);
            k += q->len;
        }

        /* send to ethernet, using hardware checksum */
        ETH_LinkSend(payload_assembly, len);
    }
    else    // (q->next != NULL)
    {
        /* Send the data from the pbuf to the interface, one pbuf at a
        time. The size of the data in each pbuf is kept in the ->len
        variable. */

        /* send to ethernet, using hardware checksum */
        ETH_LinkSend(p->payload, p->len);
    }

#if ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE);   /* reclaim the padding word */
#endif

    LINK_STATS_INC(link.xmit);

    return ERR_OK;
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
void ETH_LinkReceiveToStack(uint8_t *data, uint32_t size)
{
    err_t err;
    struct pbuf *p, *q;
    int l =0;
     
    p = NULL;
    
    /* input parameter check */
    if (NULL == data)
    {
        LINK_STATS_INC(link.err);
        LINK_STATS_INC(link.drop);
        //PLC_FreeRxBuf(data);
        return;
    }

    /* check data size */
    if (size > 1514)
    {
        LINK_STATS_INC(link.drop);
        LINK_STATS_INC(link.lenerr);
        ETH_FreeRxBuf(data);
        return;
    }
    
    /* send queue error, need to free rx buffer */
    ETH_FreeRxBuf(data);
    
    /* we allocate a pbuf chain of pbufs from the Lwip buffer pool */
    p = pbuf_alloc(PBUF_RAW, size, PBUF_POOL);
    
    /* copy received frame to pbuf chain */
    if (p != NULL){
        for (q = p; q != NULL; q = q->next){
            memcpy((uint8_t *)q->payload, &data[l], q->len);
            l = l + q->len;
        }
    }
    
    /* no packet could be read, silently ignore this */
    if (p == NULL) return;

    /* entry point to the LwIP stack */
    err = cr600_netif->input(p, cr600_netif);
    
    if (err != ERR_OK){
        LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
        pbuf_free(p);
        p = NULL;
    }
    return;
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t ethernetif_init(struct netif *netif)
{
    LWIP_ASSERT("netif != NULL", (netif != NULL));
  
#if LWIP_NETIF_HOSTNAME
    /* Initialize interface hostname */
    netif->hostname = "Gigadevice.COM_lwip";
#endif /* LWIP_NETIF_HOSTNAME */

    netif->name[0] = IFNAME0;
    netif->name[1] = IFNAME1;
    /* We directly use etharp_output() here to save a function call.
     * You can instead declare your own function an call etharp_output()
     * from it if you have to do some checks before sending (e.g. if link
     * is available...) */
    netif->output = etharp_output;
    netif->linkoutput = low_level_output;

    /* initialize the hardware */
    low_level_init(netif);

    cr600_netif = netif;
    
    return ERR_OK;
}
