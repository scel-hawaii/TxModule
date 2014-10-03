#include "TxModule.h"

uint8_t queue[_MAX_PAYLOAD_SIZE * _MAX_QUEUE_COUNT];
uint8_t queueCount = 0;
uint8_t txAttempts = 0;

uint8_t loopCount = 0;

/**
* Checks for a new packet.  If a new packet has been
* read, enter the appropriate function to handle it.
*/
void RxPacketRoutine()
{

  int apiId = 0;
  
  if ( XBeeIsAvailable() )
  {
    apiId = XBeeGetApiId();
	
    if (apiId ==  ZB_TX_STATUS_RESPONSE)
    {
      handleStatusPacket();
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
void handleStatusPacket()
{

  int i;
  
  XBeeGetZBTxStatusResponse();
  
  if ( XBeeGetDeliveryStatus() == SUCCESS )
  {    
    queueCount--;
    txAttempts = 0;
  }

}



/**
* Transmit the next packet in the queue and increment
* the amount of Tx attempts.
*/
void TxPacketRoutine()
{

  if ( queueCount > 0 && txAttempts < _MAX_TX_ATTEMPTS )
  {  
    XBeeSend(queue + (_MAX_PAYLOAD_SIZE * (_MAX_QUEUE_COUNT - queueCount )), _MAX_PAYLOAD_SIZE);
    txAttempts++;
  }

}


/**
* Generate a new payload and reinitialize values.
*/
void newPayloadRoutine()
{

  int i;
  
  for (i = 0; i < _MAX_QUEUE_COUNT * _MAX_PAYLOAD_SIZE; i++)
  {
   queue[i] = i; 
  }
  
  loopCount = 0;
  txAttempts = 0;
  queueCount = _MAX_QUEUE_COUNT;

}