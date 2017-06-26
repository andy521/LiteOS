#include "lwip/mem.h"
#include "lwip/memp.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "netif/etharp.h"
#include "lwip/dhcp.h"
#include "ethernetif.h"
#include "stdint.h"
#include "main.h"
#include "netconf.h"
#include <stdio.h>
#include "lwip/timeouts.h"
#include "lwip/priv/tcp_priv.h"

struct netif netif;
uint32_t tcp_timer = 0;
uint32_t arp_timer = 0;
ip_addr_t ip_address = {0};

void LOS_EvbLwipInit(void)
{
    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gw;

    /* initializes the dynamic memory heap defined by MEM_SIZE */
    mem_init();

    /* initializes the memory pools defined by MEMP_NUM_x */
    memp_init();
  
#ifdef TIMEOUT_CHECK_USE_LWIP
    sys_timeouts_init();
#endif /* TIMEOUT_CHECK_USE_LWIP */
  
#ifdef USE_DHCP
    ipaddr.addr = 0;
    netmask.addr = 0;
    gw.addr = 0;
#else
    IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
    IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1 , NETMASK_ADDR2, NETMASK_ADDR3);
    IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);

#endif /* USE_DHCP */

    /* - netif_add(struct netif *netif, struct ip_addr *ipaddr,
              struct ip_addr *netmask, struct ip_addr *gw,
              void *state, err_t (* init)(struct netif *netif),
              err_t (* input)(struct pbuf *p, struct netif *netif))
      
     Adds your network interface to the netif_list. Allocate a struct
    netif and pass a pointer to this structure as the first argument.
    Give pointers to cleared ip_addr structures when using DHCP,
    or fill them with sane numbers otherwise. The state pointer may be NULL.

    The init function pointer must point to a initialization function for
    your ethernet netif interface. The following code illustrates it's use.*/
    netif_add(&netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input);

    /* registers the default network interface */
    netif_set_default(&netif);

    /* when the netif is fully configured this function must be called */
    netif_set_up(&netif);
}