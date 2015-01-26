#include "TxModule.h"

#ifdef TX_DEBUG
#include <cstring>
using namespace std;
#endif


void initTxAttributes(TxAttributes * tx)
{
	tx->length = 0;
	
}


/**
* Checks for a new packet.  If a new packet has been
* read, enter the appropriate function to handle it.
*
* @param size - total size of data to be sent
* @param tx - pointer to attributes of packet
*/
void RxPacketRoutine(int size, TxAttributes * tx)
{
 	int apiId = 0;
	
	if ( XBeeIsAvailable() )
	{
		apiId = XBeeGetApiId();
	
		if (apiId ==  ZB_TX_STATUS_RESPONSE)
		{
			handleStatusPacket(size, tx);
		}

		else if (apiId == ZB_RX_RESPONSE)
		{
			handleRxPacket();
		}
	}
 }
 

/**
* Handle a standard Rx packet.
*/
void handleRxPacket()
{
  XBeeGetZBRxResponse();
}
  

/**
* Handles a Tx Status packet.  Reinitialize/decrement
* appropriate variables if it was a success.
*
* @param size - total size of data to be sent
* @param tx - pointer to attributes of packet
*/
void handleStatusPacket(int size, TxAttributes * tx)
{

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
  }
}


/**
* Transmit the next packet in the queue and increment
* the amount of Tx attempts.
*
* @param tx - pointer to attributes of packet
*/
void TxPacketRoutine(TxAttributes * tx, uint8_t data[])
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

}



/**
* Reinitialize values when a new payload has been generated.
*
* @param size - total size of data to be sent
* @param tx - pointer to attributes of packet
*/
void newPayloadRoutine(int size, TxAttributes * tx)
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
}