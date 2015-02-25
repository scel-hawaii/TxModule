#include "Wrapper.h"

#ifndef TX_MODULE_H
#define TX_MODULE_H

#define _MAX_TX_ATTEMPTS 5  //arbitrary value for the amount of tx retries per packet

#define _DATA_HEADER 10


/**
* packetNum - the number of the current packet
* totalPackets - the total amount of packets to be sent
* length - the amount of bytes in the current packet
* txIndex - the position of the array at which the current packet starts
* txAttempt - the amount of attempts made to transmit the current packet
*/

typedef struct txAttr
{
	uint8_t packetNum;
	uint8_t totalPackets;
	uint8_t length;
	uint16_t txIndex;
	uint8_t txAttempt;

} TxAttributes;


uint8_t handleRxPacket(int size, TxAttributes * tx);

uint8_t RxPacketRoutine();

uint8_t statusPacketRoutine(int size, TxAttributes * tx);

uint8_t transmitPacket(TxAttributes * tx, uint8_t data[]);

uint8_t initializeTxAttr(int size, TxAttributes * tx);

#endif