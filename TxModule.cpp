#include "TxModule.h"
#include "Wrapper.h"

#ifdef TX_DEBUG
#include <cstring>
#include <stdint.h>
using namespace std;
#endif





/**
* Checks for a new packet.  If a new packet has been
* read, enter the appropriate function to handle it.
*
* @param size - total size of data to be sent
* @param tx - pointer to attributes of packet
* @return value corresponding to a predefined message
*/
int handleRxPacket(int size, TxAttributes * tx)
{
 	uint8_t packetType;
	uint8_t flag;

	if ( packetIsAvailable() )
	{
		packetType = getPacketType();

		if ( packetType == STATUSPACKET )
			flag = statusPacketRoutine(size, tx);

		else if ( packetType == RXPACKET )
			flag = RxPacketRoutine();
	}

	return flag;
 }



/**
* Handle a standard Rx packet.
*
* @return value corresponding to a predefined message
*/
int RxPacketRoutine()
{
	return 0;
}



/**
* Handles a Tx Status packet.  Reinitialize/decrement
* appropriate variables if it was a success.
*
* @param size - total size of data to be sent
* @param tx - pointer to attributes of packet
* @return whether or not an acknowledgement was received
*/
int statusPacketRoutine(int size, TxAttributes * tx)
{

	if ( packetDelievered() )
	{
		tx->txAttempt = 0;
		tx->txIndex = tx->txIndex + tx->length;
		tx->packetNum = tx->packetNum + 1;

		if ( tx->packetNum == tx->totalPackets )
		{
			tx->length = size - (tx->packetNum - 1) * tx->length;
		}

		return 1;
	}

	return 0;
}



/**
* Transmit the next packet in the queue and increment
* the amount of Tx attempts.
*
* @param tx - pointer to attributes of packet
* @return value corresponding to a predefined message
*/
int transmitPacket(TxAttributes * tx, uint8_t data[])
{
	static uint8_t payload[_MAX_PAYLOAD_SIZE];

	if ( tx->length > 0 && tx->packetNum <= tx->totalPackets && tx->txAttempt < _MAX_TX_ATTEMPTS )
	{
		payload[0] = _DATA_HEADER;
		payload[1] = tx->totalPackets;
		payload[2] = tx->packetNum;
		memcpy(payload+3, data + tx->txIndex, tx->length);
		transmit(payload, tx->length+3);
		tx->txAttempt = tx->txAttempt + 1;

    return 1;
	}

	return 0;
}



/**
* Initialize values when a new payload has been generated.
*
* @param size - total size of data to be sent
* @param tx - pointer to attributes of packet
* @return value corresponding to a predefined message
*/
int initializeTxAttr(int size, TxAttributes * tx)
{
  if ( size <= 0 )
    return 0;

	if ( size > _MAX_PAYLOAD_SIZE - _HEADER_LENGTH )
	{
		tx->length = _MAX_PAYLOAD_SIZE - _HEADER_LENGTH;
	}

	else
	{
		tx->length = size;
	}

	tx->txAttempt = 0;
	tx->packetNum = 1;
	tx->totalPackets = (size + tx->length - 1 ) / tx->length;
	tx->txIndex = 0;

	return 1;
}
