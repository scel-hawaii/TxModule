#include "TxModule.h"

XBee xbee;
XBeeAddress64 addr64;
ZBRxResponse rxResponse;
ZBTxStatusResponse txResponse;


uint8_t queue[_MAX_PAYLOAD_SIZE * _MAX_QUEUE_COUNT];
uint8_t queueCount = 0;
uint8_t txAttempts = 0;

uint8_t txTimer = 0;


void XbeeSerialInit()
{
  xbee = XBee();
  addr64 = XBeeAddress64(0x0, 0X0);
  rxResponse = ZBRxResponse();
  txResponse = ZBTxStatusResponse();

  Serial.begin(9600); 
  xbee.begin(Serial);

}


void RxPacketRoutine()
{
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
}


void handleRxPacket()
{
  xbee.getResponse().getZBRxResponse(rxResponse);
}



void handleStatusPacket()
{
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
}




void TxPacketRoutine()
{
  if ( queueCount > 0 && txAttempts < _MAX_TX_ATTEMPTS )
  {
    ZBTxRequest zbTx = ZBTxRequest(addr64, queue, _MAX_PAYLOAD_SIZE);
    xbee.send(zbTx);
    txAttempts++;
  }
}



void newPayloadRoutine()
{
  int i;
  
  for (i = 0; i < _MAX_QUEUE_COUNT * _MAX_PAYLOAD_SIZE; i++)
  {
   queue[i] = i; 
  }
  
  txTimer = 0;
  txAttempts = 0;
  queueCount = _MAX_QUEUE_COUNT;
}