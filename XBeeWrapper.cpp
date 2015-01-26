#include "XBeeWrapper.h"

#ifndef TX_DEBUG
XBee xbee;
XBeeAddress64 addr64;
ZBRxResponse rxResponse;
ZBTxStatusResponse txResponse;
#endif

#ifdef TX_DEBUG
int transmitFlag = 0;//used to flag that a "packet" has been successfully sent
#endif

/**
* Initializes Serial and necessary XBee classes.
*
* @param baud - baudrate for Serial and XBee
*/
void XBeeInit()
{
#ifndef TX_DEBUG
  xbee = XBee();
  addr64 = XBeeAddress64(0x0, 0X0);
  rxResponse = ZBRxResponse();
  txResponse = ZBTxStatusResponse();
  xbee.begin(Serial);
#endif
}


/**
* Determines whether or not there is an available packet
*
*@return 1 if there is a packet, 0 otherwise
*/
int XBeeIsAvailable()
{
  int available = 0;

#ifndef TX_DEBUG
  xbee.readPacket();
  
  if ( xbee.getResponse().isAvailable() )
  {
    available = 1;
  }
#endif

#ifdef TX_DEBUG
  if (transmitFlag)
  {
     available = 1;
	 transmitFlag = 0;
#ifdef BOX_DEBUG	 
	 std::cout << "A packet is available...\n";
 #endif
  }
#endif
  
  return available;
}


/**
* Determines the api ID of the packet being read.
*
* @return api ID of packet
*/
int XBeeGetApiId()
{
  int apId = 0;
  
#ifndef TX_DEBUG  
  apId = xbee.getResponse().getApiId();
#endif

#ifdef TX_DEBUG
  apId = ZB_TX_STATUS_RESPONSE;
#ifdef BOX_DEBUG
  std::cout << "...it's a Tx status packet.\n";
#endif
#endif
  
  return apId;
}

/**
* Fills the Rx object with data from the packet being read.
*/
void XBeeGetZBRxResponse()
{
#ifndef TX_DEBUG
  xbee.getResponse().getZBRxResponse(rxResponse);
#endif  
}

/**
* Fills the Tx Status object with data from the packet being read.
*/
void XBeeGetZBTxStatusResponse()
{
#ifndef TX_DEBUG
    xbee.getResponse().getZBTxStatusResponse(txResponse);
#endif

#ifdef BOX_DEBUG
  std::cout << "Reading Tx status packet...\n";
#endif
}

/**
* Determines the delivery status of a packet based off of the
* Tx Status object.
*
* @return value representing delivery status
*/
int XBeeGetDeliveryStatus()
{
  int dStatus = -1;
  
#ifndef TX_DEBUG  
  dStatus = txResponse.getDeliveryStatus();
#endif

#ifdef TX_DEBUG
  dStatus = SUCCESS;
 #ifdef BOX_DEBUG 
  std::cout << "...it was a success!\n";
#endif  
#endif
  
  return dStatus;
 }
 
 
 
/**
* Creates and sends a new Tx packet.
*
* @param q - array holding the data to be sent
* @param size - the amount of data to be sent
*/
 void XBeeSend(uint8_t q[], int size)
 {
 int i;
 
#ifndef TX_DEBUG  
  ZBTxRequest zbTx = ZBTxRequest(addr64, q, size);
  xbee.send(zbTx);
#endif

#ifdef TX_DEBUG
  transmitFlag = 1;
#ifdef BOX_DEBUG
  std::cout << "Sending new packet...\n";
  
  std::cout << "Packet header: " << (int)q[0]  <<  "\n";
  std::cout << "Packet number: " << (int)q[2] << " of " << (int)q[1] << "\n";
  std::cout << "Data: ";
  
  for ( i = 3; i < size; i++ )
  {
	std::cout << (int)q[i]  <<  " ";
  }
  std::cout << "\n\n\n";
#endif
#endif
 }
 

#ifdef TX_DEBUG
void delay(int n)
{
	int i;

	for (i = 0; i < 10000 * n; i++)
	{
	
	}
}
#endif