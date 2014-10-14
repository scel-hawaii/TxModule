#include "config.h"

#ifdef TX_DEBUG

#include "XBeeWrapper.h"
#include "TxModule.h"


uint8_t queue[_MAX_PAYLOAD_SIZE * _MAX_QUEUE_COUNT];
uint8_t queueCount = 0;
uint8_t txAttempts = 0;

uint8_t loopCount = 0;


int main(int argc, char* argv[])
{
	while (1)
	{
		if ( loopCount >= _TX_INTERVAL )
		{
			newPayloadRoutine(&queueCount, &txAttempts, queue, &loopCount);
		}
		
		RxPacketRoutine(&queueCount, &txAttempts);
		
		TxPacketRoutine(&queueCount, &txAttempts, queue);
		
		loopCount++;
		delay(1000);
	}		
}
#endif