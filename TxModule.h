#include "XBeeWrapper.h"

#ifndef TX_MODULE_H
#define TX_MODULE_H

#define _MAX_PAYLOAD_SIZE 84  //max payload size for the xbee
#define _MAX_QUEUE_COUNT 4  //arbitrary value for the amount of max payloads in the "queue"
#define _MAX_TX_ATTEMPTS 5  //arbitrary value for the amount of tx retries per packet
#define _TX_INTERVAL 60  //delay before generating the next payload



void handleStatusPacket(uint8_t * qCount, uint8_t * txAtt);

void handleRxPacket();

void TxPacketRoutine(uint8_t * qCount, uint8_t * txAtt, uint8_t q[]);

void RxPacketRoutine(uint8_t * qCount, uint8_t * txAtt);

void newPayloadRoutine(uint8_t * qCount, uint8_t * txAtt, uint8_t q[], uint8_t * loops);

#endif