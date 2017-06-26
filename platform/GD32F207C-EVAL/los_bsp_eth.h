#ifndef _LOS_BSP_ETH_H
#define _LOS_BSP_ETH_H

#define USE_ENET_INTERRUPT

/* MII and RMII mode selection */
#define RMII_MODE  // user have to provide the 50 MHz clock by soldering a 50 MHz oscillator
//#define MII_MODE

extern void LOS_EvbEthInit(void);

#endif//_LOS_BSP_ETH_H
