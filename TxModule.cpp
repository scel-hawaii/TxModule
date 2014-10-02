#include "TxModule.h"


#ifndef TX_TEST
XBee xbee;
XBeeAddress64 addr64;
ZBRxResponse rxResponse;
ZBTxStatusResponse txResponse;
#endif

uint8_t queue[_MAX_PAYLOAD_SIZE * _MAX_QUEUE_COUNT];
uint8_t queueCount = 0;
uint8_t txAttempts = 0;

uint8_t loopCount = 0;

/**
* Initializes Serial and necessary XBee classes.
*
* @param baud - baudrate for Serial and XBee
*/
void XbeeSerialInit(int baud)
{
#ifndef TX_TEST
  xbee = XBee();
  addr64 = XBeeAddress64(0x0, 0X0);
  rxResponse = ZBRxResponse();
  txResponse = ZBTxStatusResponse();
#endif


  Serial.begin(baud); 
  
#ifndef TX_TEST
  xbee.begin(Serial);
#endif
}


/**
* Checks for a new packet.  If a new packet has been
* read, enter the appropriate function to handle it.
*/
void RxPacketRoutine()
{
#ifndef TX_TEST
  xbee.readPacket();
  
  if (xbee.getResponse().isAvailable())
  {
    if (xbee.getResponse().getApiId() ==  ZB_TX_STATUS_RESPONSE)
    {
      handleStatusPacket();
    }

    else if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE)
    {
      handleRxPacket();
    }
  }	
#endif
}


/**
* Handle a standard Rx packet.
*/
void handleRxPacket()
{
#ifndef TX_TEST
  xbee.getResponse().getZBRxResponse(rxResponse);
#endif
}


/**
* Handles a Tx Status packet.  Reinitialize/decrement
* appropriate variables if it was a success.
*/
void handleStatusPacket()
{
#ifndef TX_TEST
  int i;
  
  xbee.getResponse().getZBTxStatusResponse(txResponse);
  
  if ( txResponse.getDeliveryStatus() == SUCCESS )
  {
    for (i = 0; i < _MAX_PAYLOAD_SIZE; i++)
    {
      queue[i] = queue[i + _MAX_PAYLOAD_SIZE];
    }
    
    queueCount--;
    txAttempts = 0;
  }
#endif
}



/**
* Transmit the first packet in the queue and increment
* the amount of Tx attempts.
*/
void TxPacketRoutine()
{
#ifndef TX_TEST
  if ( queueCount > 0 && txAttempts < _MAX_TX_ATTEMPTS )
  {
    ZBTxRequest zbTx = ZBTxRequest(addr64, queue, _MAX_PAYLOAD_SIZE);
    xbee.send(zbTx);
    txAttempts++;
  }
#endif
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