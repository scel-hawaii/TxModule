/*
* Driver which emulates the weatherbox behaviour
* and prints XBee debug statements.
*/



#ifdef BOX_DEBUG

#include "XBeeWrapper.h"
#include "TxModule.h"

//placeholder for struct of samples
uint8_t q[255];

uint8_t length;
uint16_t queueCount;
uint16_t txIndex;
uint8_t txAttempts;

uint8_t loopCount = 0;


int main(int argc, char* argv[])
{
	//initialize demo "struct"
	for ( int i = 0; i < 255; i++)
	{
		q[i] = i;
	}
	

	while (1)
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
}
#endif