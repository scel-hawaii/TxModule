/*
* Driver which emulates the weatherbox behaviour
* and prints XBee debug statements.
*/



#ifdef BOX_DEBUG

#include "XBeeWrapper.h"
#include "TxModule.h"

//size of data
#define _SIZE 255

TxAttributes tx;
uint8_t data[_SIZE];

uint8_t loopCount = 0;

int main(int argc, char* argv[])
{
	//initialize demo "struct"
	for ( int i = 0; i < _SIZE; i++)
	{
		data[i] = i;
	}
	
	initTxAttributes(&tx);
	
	while (1)
	{
		if ( loopCount >= 60 )
		{
			newPayloadRoutine(_SIZE, &tx);
			loopCount = 0;
		}
		
		RxPacketRoutine(_SIZE, &tx);
		
		TxPacketRoutine(&tx, data);
		
		loopCount++;
		delay(1000);
	
	}	
	
}
#endif