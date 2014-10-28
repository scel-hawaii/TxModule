#include <XBee.h>
#include <TxModule.h>


uint8_t q[255];

uint8_t length;
uint16_t queueCount;
uint16_t txIndex;
uint8_t txAttempts;

uint8_t loopCount = 0;

void setup()
{
  Serial.begin(9600);
  XBeeInit();
  
  	for ( int i = 0; i < 255; i++)
	{
		q[i] = i;
	}
}


void loop()
{
		if ( loopCount >= _TX_INTERVAL )
		{
			newPayloadRoutine(&queueCount, &txIndex, &length, &txAttempts, &loopCount);
		}
		
		RxPacketRoutine(&queueCount, &txIndex, &length, &txAttempts);
		
		TxPacketRoutine(queueCount, txIndex, length, &txAttempts, q);
		
		loopCount++;
		delay(1000);		
}