#include <XBee.h>
#include <TxModule.h>


//size of data
#define _SIZE 255

uint8_t data[_SIZE];
uint8_t flag;
uint8_t loopCount = 0;

TxAttributes tx;


void setup()
{
  Serial.begin(9600);
  XBeeInit();
  
  	for ( int i = 0; i < _SIZE; i++)
	{
		data[i] = i;
	}
}


void loop()
{
	if ( loopCount >= 60 )
	{	//reinitialize values when a new packet is ready
		initializeTxAttr(_SIZE, &tx);
		loopCount = 0;
	}
		
	//read any incoming packet
	flag = handleRxPacket(_SIZE, &tx, NULL, 0, 0);
		
	//transmit a packet if available
	transmitPacket(&tx, data, NULL);
		
	loopCount++;
	delay(1000);
}	