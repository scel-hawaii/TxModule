/*
* Driver which emulates the weatherbox behaviour
* and prints XBee debug statements.
*/



#ifdef BOX_DEBUG

#include "XBeeWrapper.h"
#include "TxModule.h"

//size of data
#define _SIZE 255

uint8_t data[_SIZE];
uint8_t packetNum;
uint8_t totalPackets;
uint8_t length = 0;
uint16_t txIndex;
uint8_t txAtt;

uint8_t loopCount = 0;


int main(int argc, char* argv[])
{
	//initialize demo "struct"
	for ( int i = 0; i < _SIZE; i++)
	{
		data[i] = i;
	}
	

	while (1)
	{
		if ( loopCount >= 60 )
		{
			newPayloadRoutine(_SIZE, &packetNum, &totalPackets, &length, &txIndex, &txAtt);
			loopCount = 0;
		}
		
		RxPacketRoutine(_SIZE, &packetNum, totalPackets, &length, &txIndex, &txAtt);
		
		TxPacketRoutine(packetNum, totalPackets, length, txIndex, &txAtt, data);
		
		loopCount++;
		delay(1000);
	}		
}
#endif