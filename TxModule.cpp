#include "TxModule.h"

/**
* Checks for a new packet.  If a new packet has been
* read, enter the appropriate function to handle it.
*/
void RxPacketRoutine(uint8_t * qCount, uint8_t * txAtt)
{
  int apiId = 0;
  
  if ( XBeeIsAvailable() )
  {
    apiId = XBeeGetApiId();
	
    if (apiId ==  ZB_TX_STATUS_RESPONSE)
    {
      handleStatusPacket(qCount, txAtt);
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
*/
void handleStatusPacket(uint8_t * qCount, uint8_t * txAtt)
{
  XBeeGetZBTxStatusResponse();
  
  if ( XBeeGetDeliveryStatus() == SUCCESS )
  {
    *qCount = *qCount - 1;
    *txAtt = 0;
  }
}



/**
* Transmit the next packet in the queue and increment
* the amount of Tx attempts.
*/
void TxPacketRoutine(uint8_t * qCount, uint8_t * txAtt, uint8_t q[])
{
  if ( *qCount > 0 && *txAtt < _MAX_TX_ATTEMPTS )
  {  
    XBeeSend(q + (_MAX_PAYLOAD_SIZE * (_MAX_QUEUE_COUNT - *qCount )), _MAX_PAYLOAD_SIZE);
    *txAtt++;
  }
}


/**
* Generate a new payload and reinitialize values.
*/
void newPayloadRoutine(uint8_t * qCount, uint8_t * txAtt, uint8_t q[], uint8_t * loops)
{
  int i;
  
  for (i = 0; i < _MAX_QUEUE_COUNT * _MAX_PAYLOAD_SIZE; i++)
  {
   q[i] = i; 
  }
  
  *loops= 0;
  *txAtt = 0;
  *qCount = _MAX_QUEUE_COUNT;

}