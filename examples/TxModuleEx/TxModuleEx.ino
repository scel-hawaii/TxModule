#include <XBee.h>
#include <TxModule.h>


//size of data
#define _SIZE 255

uint8_t data[_SIZE];
uint8_t packetNum;
uint8_t totalPackets;
uint8_t length = 0;
uint16_t txIndex;
uint8_t txAtt;

uint8_t loopCount = 0;

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
	{
		newPayloadRoutine(_SIZE, &packetNum, &totalPackets, &length, &txIndex, &txAtt);
		loopCount = 0;
	}
		
	RxPacketRoutine(_SIZE, &packetNum, totalPackets, &length, &txIndex, &txAtt);
	
	TxPacketRoutine(packetNum, totalPackets, length, txIndex, &txAtt, data);
		
	loopCount++;
	delay(1000);	
}