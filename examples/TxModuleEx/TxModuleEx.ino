#include <TxModule.h>
#include <XBee.h>



void setup()
{
  XbeeSerialInit(9600);  
}

void loop()
{
  //sample data
  
  /* execute the following if the transmission interval has passed
  -generate a new payload
  -reset txAttempts and queueCount
  */
  if ( loopCount >= _TX_INTERVAL )
  {
    newPayloadRoutine();
  }
  
  /* check for incoming packets
  -if an ack was read
  -dequeue, decrement queueCount, reset TxAttempts
  */
  RxPacketRoutine();

  
  
  /* check if the queue isn't empty and the txAttempts isn't too high
  -transmit the oldest packet
  -increment txAttempts
  */
  TxPacketRoutine();
  
  
  
  loopCount++;
  delay(1000);
}
