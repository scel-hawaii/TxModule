#include "TxModule.h"

/**
* Checks for a new packet.  If a new packet has been
* read, enter the appropriate function to handle it.
*
* @param qCount - pointer to amount of bytes left in queue
* @param txIndex - pointer to index of the queue to start transmitting from
* @param length - pointer size of data to be sent
* @param txAtt - pointer to tx attempts
*/
void RxPacketRoutine(uint16_t * qCount, uint16_t * txIndex, uint8_t * length, uint8_t * txAtt)
{
  int apiId = 0;
  
  if ( XBeeIsAvailable() )
  {
    apiId = XBeeGetApiId();
	
    if (apiId ==  ZB_TX_STATUS_RESPONSE)
    {
      handleStatusPacket(qCount, txIndex, length, txAtt);
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
* @param qCount - pointer to amount of bytes left in queue
* @param txIndex - pointer to index of the queue to start transmitting from
* @param length - pointer size of data to be sent
* @param txAtt - pointer to tx attempts
*/
void handleStatusPacket(uint16_t * qCount, uint16_t * txIndex, uint8_t * length, uint8_t * txAtt)
{
  XBeeGetZBTxStatusResponse();
  
  if ( XBeeGetDeliveryStatus() == SUCCESS )
  {
		*txAtt = 0;
		*txIndex = *txIndex + *length;
		*qCount = *qCount - *length;

		if ( *qCount < *length )
			*length = *qCount;
  }
}



/**
* Transmit the next packet in the queue and increment
* the amount of Tx attempts.
*
* @param qCount - pointer to amount of bytes left in queue
* @param txIndex - index of the queue to start transmitting from
* @param length - size of data to be sent
* @param txAtt - pointer to tx attempts
* @param q - queue
*/
void TxPacketRoutine(uint16_t qCount, uint16_t txIndex, uint8_t length, uint8_t * txAtt, uint8_t * q)
{
  if ( qCount > 0 && *txAtt < _MAX_TX_ATTEMPTS )
  {  
    XBeeSend(q + txIndex, length);
    *txAtt = *txAtt + 1;
  }
}


/**
* Reinitialize values.
*
* @param qCount - pointer to amount of bytes left in queue
* @param txIndex - pointer to index of the queue to start transmitting from
* @param length - pointer size of data to be sent
* @param txAtt - pointer to tx attempts
* @param loops - pointer to loop count
*/
void newPayloadRoutine(uint16_t * qCount, uint16_t * txIndex, uint8_t * length, uint8_t * txAtt, uint8_t * loops)
{  
  *loops = 0;
  *txAtt = 0;
   *txIndex = 0;
//  *qCount = sizeof(schema);
*qCount = 255;  //demo qCount
  
//  if ( sizeof(schema) < _MAX_PAYLOAD_SIZE )
  *length = _MAX_PAYLOAD_SIZE;  //demo length
  
 // else
 // *length = *qCount;
}
