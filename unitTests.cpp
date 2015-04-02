#ifdef TX_DEBUG
#ifndef BOX_DEBUG

#include <iostream>
#include "XBeeSim.h"
#include "Wrapper.h"
#include "TxModule.h"

using namespace std;

int initTest();
int txTest();


int main(int argc, char* argv[])
{
	int err;

	cout << "Testing initialization function...";
	if ( (err = initTest()) )	cout << "test failed. Error " << err << ".\n";
	else								cout << "test passed!\n";

	cout << "Testing transmit function...";
	if ( (err = txTest()) )		cout << "test failed. Error " << err << ".\n";
	else								cout << "test passed!\n";

}



/*
* Verify that the initializeTxAttr function
* initializes values properly.
*
* return error code if the test fails
*/
int initTest()
{
	int err = 0;
	TxAttributes txAttr1;

	//multi packet payload
	initializeTxAttr((_MAX_PAYLOAD_SIZE-3)*10, &txAttr1);
	if ( txAttr1.totalPackets != 10 )			err = 1;
	if ( txAttr1.length != 81 )					err = 2;

	//single packet payload
	initializeTxAttr(5, &txAttr1);
	if ( txAttr1.totalPackets != 1 )				err = 4;
	if ( txAttr1.length != 5 )						err = 8;

	//no payload
	if ( initializeTxAttr(0, &txAttr1) )			err = 16;

	return err;
}



int txTest()
{
	TxAttributes txAttr1;
	XBeeSim xbeeSim = new XBeeSim();

	initializeTxAttr(10, &txAttr1);

}



int transmitPacket(TxAttributes * tx, uint8_t data[])
{
	static uint8_t payload[_MAX_PAYLOAD_SIZE];

	if ( tx->length > 0 && tx->packetNum <= tx->totalPackets && tx->txAttempt < _MAX_TX_ATTEMPTS )
	{
		payload[0] = _DATA_HEADER;
		payload[1] = tx->totalPackets;
		payload[2] = tx->packetNum;
		memcpy(payload+3, data + tx->txIndex, tx->length);
		transmit(payload, tx->length+3);
		tx->txAttempt = tx->txAttempt + 1;

    return 1;
	}

	return 0;
}


#endif
#endif
