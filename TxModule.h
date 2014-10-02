
#ifndef TX_MODULE_H
#define TX_MODULE_H

#define _MAX_PAYLOAD_SIZE 84  //max payload size for the xbee
#define _MAX_QUEUE_COUNT 4  //arbitrary value for the amount of max payloads in the "queue"
#define _MAX_TX_ATTEMPTS 5  //arbitrary value for the amount of tx retries per packet
#define _TX_INTERVAL 60  //delay before generating the next payload

#ifndef TX_TEST

#include <Arduino.h>
#include <XBee.h>

extern XBee xbee;
extern XBeeAddress64 addr64;
extern ZBRxResponse rxResponse;
extern ZBTxStatusResponse txResponse;

#endif


extern uint8_t queue[_MAX_PAYLOAD_SIZE * _MAX_QUEUE_COUNT];
extern uint8_t queueCount;
extern uint8_t txAttempts;

extern uint8_t loopCount;



void XbeeSerialInit(int baud);

void handleStatusPacket();

void handleRxPacket();

void TxPacketRoutine();

void RxPacketRoutine();

void newPayloadRoutine();

#endif