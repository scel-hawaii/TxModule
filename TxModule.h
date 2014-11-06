#include "XBeeWrapper.h"

#ifndef TX_MODULE_H
#define TX_MODULE_H

#define _MAX_PAYLOAD_SIZE 84  //max payload size for the XBee
#define _MAX_TX_ATTEMPTS 5  //arbitrary value for the amount of tx retries per packet

//com definitions
#define _DATA_HEADER 10



void handleStatusPacket(int size, uint8_t * packetNum, uint8_t totalPackets, uint8_t * length, uint16_t * txIndex, uint8_t * txAtt);

void handleRxPacket();

void TxPacketRoutine(uint8_t packetNum, uint8_t totalPackets, uint8_t length, uint16_t txIndex, uint8_t * txAtt, uint8_t data[]);

void RxPacketRoutine(int size, uint8_t * packetNum, uint8_t totalPackets, uint8_t * length, uint16_t * txIndex, uint8_t * txAtt);

void newPayloadRoutine(int size, uint8_t * packetNum, uint8_t * totalPackets, uint8_t * length, uint16_t * txIndex, uint8_t * txAtt);

#endif