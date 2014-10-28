#include "XBeeWrapper.h"

#ifndef TX_MODULE_H
#define TX_MODULE_H

#define _MAX_PAYLOAD_SIZE 84  //max payload size for the XBee
#define _MAX_TX_ATTEMPTS 5  //arbitrary value for the amount of tx retries per packet
#define _TX_INTERVAL 60  //delay before generating the next payload



void handleStatusPacket(uint16_t * qCount, uint16_t * txIndex, uint8_t * length, uint8_t * txAtt);

void handleRxPacket();

void TxPacketRoutine(uint16_t qCount, uint16_t txIndex, uint8_t length, uint8_t * txAtt, uint8_t * q);

void RxPacketRoutine(uint16_t * qCount, uint16_t * txIndex, uint8_t * length, uint8_t * txAtt);

void newPayloadRoutine(uint16_t * qCount, uint16_t * txIndex, uint8_t * length, uint8_t * txAtt, uint8_t * loops);

#endif