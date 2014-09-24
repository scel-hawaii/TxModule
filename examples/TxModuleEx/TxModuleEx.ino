#include <TxModule.h>
#include <XBee.h>



void setup()
{
  XbeeSerialInit();  
}

void loop()
{
  //sample data
  
  /* execute the following if the transmission interval has passed
  -generate a new payload
  -reset txAttempts and queueCount
  */
  if ( txTimer >= _TX_INTERVAL )
  {
    newPayloadRoutine();
  }
  
  /* check for incoming packets
  -if an ack was read
  -dequeue, decrement queueCount, reset TxAttempts
  */
  xbee.readPacket();
  
  if (xbee.getResponse().isAvailable())
  {
    RxPacketRoutine();
  }
  
  
  /* check if the queue isn't empty and the txAttempts isn't too high
  -transmit the oldest packet
  -increment txAttempts
  */
  TxPacketRoutine();
  
  
  
  txTimer++;
  delay(1000);
}
