#include "TxModule.h"

#ifdef TX_DEBUG
#include <cstring>
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
uint8_t handleRxPacket(int size, TxAttributes * tx)
{
 	uint8_t apiId;
	uint8_t flag;
	
	if ( XBeeIsAvailable() )
	{
		apiId = XBeeGetApiId();
	
		if (apiId ==  ZB_TX_STATUS_RESPONSE)
		{
			flag = statusPacketRoutine(size, tx);
		}

		else if (apiId == ZB_RX_RESPONSE)
		{
			flag = RxPacketRoutine();
		}
	}
	
	return flag;
 }
 
 

/**
* Handle a standard Rx packet.
*
* @return value corresponding to a predefined message
*/
uint8_t RxPacketRoutine()
{
	XBeeGetZBRxResponse();
	
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
uint8_t statusPacketRoutine(int size, TxAttributes * tx)
{
	uint8_t ack = 0;

	XBeeGetZBTxStatusResponse();
	
	if ( XBeeGetDeliveryStatus() == SUCCESS )
	{
		tx->txAttempt = 0;
		tx->txIndex = tx->txIndex + tx->length;
		tx->packetNum = tx->packetNum + 1;
		

		if ( tx->packetNum == tx->totalPackets )
		{
			tx->length = size - (tx->packetNum - 1) * tx->length;
		}
		
		ack = 1;
	}
	
	return ack;
}



/**
* Transmit the next packet in the queue and increment
* the amount of Tx attempts.
*
* @param tx - pointer to attributes of packet
* @return value corresponding to a predefined message
*/
uint8_t transmitPacket(TxAttributes * tx, uint8_t data[])
{

	uint8_t payload[_MAX_PAYLOAD_SIZE];
	
	if ( tx->length > 0 && tx->packetNum <= tx->totalPackets && tx->txAttempt < _MAX_TX_ATTEMPTS )
	{  	
		payload[0] = _DATA_HEADER;
		payload[1] = tx->totalPackets;
		payload[2] = tx->packetNum;
		memcpy(payload+3, data + tx->txIndex, tx->length);
		XBeeSend(payload, tx->length+3);
		tx->txAttempt = tx->txAttempt + 1;
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
uint8_t initializeTxAttr(int size, TxAttributes * tx)
{
	if ( size > _MAX_PAYLOAD_SIZE - 3 )
	{
		tx->length = _MAX_PAYLOAD_SIZE - 3;
	}
	
	else
	{
		tx->length = size;
	}
	
	tx->txAttempt = 0;
	tx->packetNum = 1;	
	tx->totalPackets = (size + tx->length - 1 ) / tx->length;
	tx->txIndex = 0;
	
	return 0;
}