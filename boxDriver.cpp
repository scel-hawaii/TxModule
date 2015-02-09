/*
* Driver which emulates the weatherbox behaviour
* and prints XBee debug statements.
*/



#ifdef BOX_DEBUG

#include "XBeeWrapper.h"
#include "TxModule.h"

//size of data
#define _SIZE 256

void setup();
void boxLoop();


uint8_t data[_SIZE];
uint8_t flag;
uint8_t loopCount = 0;

TxAttributes tx;

int main(int argc, char* argv[])
{
	setup();
	boxLoop();
}

/*
*	Initializes values and creates a demo set of data.
*/
void setup()
{
	for ( int i = 0; i < _SIZE; i++)
	{
		data[i] = i;
	}
}


/*
*	Module used in a typical weatherbox loop.  After
*  enough samples are collected, an initialization is 
*  executed to prepare for the transmission of data.
*  Incoming packets are read and decisions are made
*  based off of what was received.  If there are packets
*  available in the buffer, the packet on top is transmitted.
*/
void boxLoop()
{
	//flags if a new packet is available
	int isAvailable = 0;
	//flags if an ack was received
	int isSuccess = 1;

	while (1)
	{
		if ( loopCount >= 60 )
		{	//reinitialize values when a new packet is ready
			initializeTxAttr(_SIZE, &tx);
			loopCount = 0;
		}
		
		//read any incoming packet
		flag = handleRxPacket(_SIZE, &tx, &isAvailable, ZB_TX_STATUS_RESPONSE, isSuccess);
		
		//transmit a packet if available
		transmitPacket(&tx, data, &isAvailable);
		
		loopCount++;
		delay(1000);
	}	
}
#endif