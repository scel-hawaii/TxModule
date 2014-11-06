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
* @param packetNum - pointer to the current packet number
* @param totalPackets - total amount of packets to be sent
* @param length - pointer to size of data to be sent per packet
* @param txIndex - pointer to index of data to start transmitting from
* @param txAtt - pointer to tx attempts
*/
void RxPacketRoutine(int size, uint8_t * packetNum, uint8_t totalPackets, uint8_t * length, uint16_t * txIndex, uint8_t * txAtt)
{
	int apiId = 0;
	
	if ( XBeeIsAvailable() )
	{
		apiId = XBeeGetApiId();
	
		if (apiId ==  ZB_TX_STATUS_RESPONSE)
		{
			handleStatusPacket(size, packetNum, totalPackets, length, txIndex, txAtt);
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
* @param packetNum - pointer to the current packet number
* @param totalPackets - total amount of packets to be sent
* @param length - pointer to size of data to be sent per packet
* @param txIndex - pointer to index of data to start transmitting from
* @param txAtt - pointer to tx attempts
*/
void handleStatusPacket(int size, uint8_t * packetNum, uint8_t totalPackets, uint8_t * length, uint16_t * txIndex, uint8_t * txAtt)
{
  XBeeGetZBTxStatusResponse();
  
  if ( XBeeGetDeliveryStatus() == SUCCESS )
  {
		*txAtt = 0;
		*txIndex = *txIndex + *length;
		*packetNum = *packetNum + 1;
		

		if ( *packetNum == totalPackets )
		{
			*length = size - (*packetNum - 1) * *length;
		}
  }
}



/**
* Transmit the next packet in the queue and increment
* the amount of Tx attempts.
*
* @param packetNum - current packet number
* @param totalPackets - total amount of packets to be sent
* @param length - size of data to be sent per packet
* @param txIndex - index of data to start transmitting from
* @param txAtt - pointer to tx attempts
* @param data - array of data to be sent
*/
void TxPacketRoutine(uint8_t packetNum, uint8_t totalPackets, uint8_t length, uint16_t txIndex, uint8_t * txAtt, uint8_t data[])
{
	uint8_t payload[_MAX_PAYLOAD_SIZE];
	
	if ( length > 0 && packetNum <= totalPackets && *txAtt < _MAX_TX_ATTEMPTS )
	{  	
		payload[0] = _DATA_HEADER;
		payload[1] = totalPackets;
		payload[2] = packetNum;
		memcpy(payload+3, data + txIndex, length);
		XBeeSend(payload, length+3);
		*txAtt = *txAtt + 1;
	}
}


/**
* Reinitialize values when a new payload has been generated.
*
* @param size - total size of data to be sent
* @param packetNum - pointer to the current packet number
* @param totalPackets - pointer to total amount of packets to be sent
* @param length - pointer to size of data to be sent per packet
* @param txIndex - pointer to index of data to start transmitting from
* @param txAtt - pointer to tx attempts
*/
void newPayloadRoutine(int size, uint8_t * packetNum, uint8_t * totalPackets, uint8_t * length, uint16_t * txIndex, uint8_t * txAtt)
{

	if ( size > _MAX_PAYLOAD_SIZE - 3 )
	{
		*length = _MAX_PAYLOAD_SIZE - 3;
	}
	
	else
	{
		*length = size;
	}
	
	*txAtt = 0;
	*packetNum = 1;	
	*totalPackets = (size + *length - 1 ) / *length;
	*txIndex = 0;
}
