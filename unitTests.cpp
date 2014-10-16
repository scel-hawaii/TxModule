#include "config.h"

#ifdef TX_DEBUG
#ifndef BOX_DEBUG

#include <iostream>
#include "XBeeWrapper.h"
#include "TxModule.h"

using namespace std;


/*
remember to test all cases, eg what happens when packets are not
sent successfully
*/

void NPRTest(uint8_t qCount, uint8_t txAtt, uint8_t loops);

void HSPTest(uint8_t qCount, uint8_t txAtt);

void TxPRTest(uint8_t qCount, uint8_t txAtt, uint8_t q[]);

void RxPRTest(uint8_t qCount, uint8_t txAtt);


int main(int argc, char* argv[])
{

	NPRTest(3, 4, 5);
	HSPTest(1,2);


}



void NPRTest(uint8_t qCount, uint8_t txAtt, uint8_t loopCount)
{
	int eQC = _MAX_QUEUE_COUNT;
	int eTxA = 0;
	int  eLC = 0;
	uint8_t arr[_MAX_QUEUE_COUNT * _MAX_PAYLOAD_SIZE];
	
	cout << "Creating a new payload...\n";
	cout << "...ensuring that the queue count, Tx counter and loop counter are reinitialized.\n";
	cout<< "Status:  ";
	
	newPayloadRoutine(&qCount, &txAtt, arr, &loopCount);
	
	if ( eQC == qCount && eTxA == txAtt && eLC == loopCount )
	{
		cout << "Pass!\n\n\n";
	}
	
	else
	{
		cout << "Fail!\n\n\n";
	}
}



void HSPTest(uint8_t qCount, uint8_t txAtt)
{
	int eQC = qCount-1;
	int eTxA = 0;
	
	cout << "Handling a new status packet...\n";
	cout << "...ensuring that the queue count has been decremented, and the Tx counter has been reset.\n";
	cout << "Status: ";
	
	handleStatusPacket(&qCount, &txAtt);
	
	if ( eQC == qCount && eTxA == txAtt )
	{
		cout << "Pass!\n\n\n";
	}
	
	else
	{
		cout << "Fail!\n\n\n";
	}

}




#endif
#endif