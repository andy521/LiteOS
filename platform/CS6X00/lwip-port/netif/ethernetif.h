#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__

#include "lwip/err.h"
#include "lwip/netif.h"

/* define those to better describe your network interface. */
#define ETH_IFNAME0 'e'
#define ETH_IFNAME1 't'

/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
struct ethernetif
{
    struct eth_addr *ethaddr;
    /* Add whatever per-interface state that is needed here. */
};

#define NET_IF_LINKDOWN     0x00
#define NET_IF_LINKUP       0x01

extern err_t ethernetif_init(struct netif *netif);

#endif
