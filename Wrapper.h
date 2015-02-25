/**
*  Wrapper functions used to run the tx module in
*  different environments.
*/

#ifndef XBEE_WRAPPER_H
#define XBEE_WRAPPER_H

#define _MAX_PAYLOAD_SIZE 84  //max payload size for the XBee
#define STATUSPACKET 1
#define RXPACKET 2
#define ACK 1


#ifdef TX_DEBUG
#include <iostream>
#include <stdint.h>
#include "XBeeSim.h"
#endif

#ifndef TX_DEBUG
#include <XBee.h>
#endif



#ifndef TX_DEBUG
extern XBee xbee;
extern XBeeAddress64 addr64;
extern ZBRxResponse rxResponse;
extern ZBTxStatusResponse txResponse;
#endif

#ifdef TX_DEBUG
extern XBeeSim xbeeSim;
#endif



uint8_t packetIsAvailable();

uint8_t getPacketType();

uint8_t packetDelievered();

void transmit(uint8_t payload[], int size);

#endif