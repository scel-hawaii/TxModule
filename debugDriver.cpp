#include "config.h"

#ifdef TX_DEBUG

#include <iostream>
#include "XBeeWrapper.h"
#include "TxModule.h"


int main(int argc, char* argv[])
{
	while (1)
	{
		if ( loopCount >= _TX_INTERVAL )
		{
			newPayloadRoutine();
		}
		
		RxPacketRoutine();
		
		TxPacketRoutine();
		
		loopCount++;
		delay(1000);
	}		
}
#endif
