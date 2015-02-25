#include "Wrapper.h"


#ifndef TX_DEBUG
XBee xbee;
XBeeAddress64 addr64;
ZBRxResponse rxResponse;
ZBTxStatusResponse txResponse;
#endif

#ifdef TX_DEBUG
XBeeSim xbeeSim;
#endif

/**
* Initializes XBee objects.
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

#ifdef TX_DEBUG
	xbeeSim = XBeeSim();
#endif	
}


/**
* Determines whether or not there is an available packet
*
*@return 1 if there is a packet, 0 otherwise
*/
uint8_t packetIsAvailable()
{
	int available = 0;

#ifndef TX_DEBUG
	xbee.readPacket();
  
	if ( xbee.getResponse().isAvailable() )  available = 1;
#endif

#ifdef TX_DEBUG
	if ( xbeeSim.getAvailability() )
	{
		available = 1;
		xbeeSim.setAvailability(0);
#ifdef BOX_DEBUG	 
		std::cout << "A packet is available...\n";
#endif
	}
#endif
  
	return available;
}


/**
* Determines the type of packet being read.
*
* @return packet type
*/
uint8_t getPacketType()
{
	int packetType = 0;
  
#ifndef TX_DEBUG 
	packetType = xbee.getResponse().getApiId();
	
	if ( packetType == ZB_TX_STATUS_RESPONSE ) packetType = STATUSPACKET;
	else if ( packetType == ZB_RX_RESPONSE ) packetType = RXPACKET;
#endif	

#ifdef TX_DEBUG	
	packetType = xbeeSim.getApiId();
	
	if ( packetType == ZB_TX_STATUS_RESPONSE ) packetType = STATUSPACKET;
	else if ( packetType == ZB_RX_RESPONSE ) packetType = RXPACKET;
#ifdef BOX_DEBUG
	if ( packetType == STATUSPACKET )	std::cout << "...it's a Tx status packet.\n";
	else	std::cout << "...it's not a Tx status packet.\n";
#endif
#endif
  
	return packetType;
}




/**
* Determines the delivery status of a packet.
*
* @return whether or not pack was delivered
*/
uint8_t packetDelievered()
{
	int delivered = 0;
  
#ifndef TX_DEBUG
	xbee.getResponse().getZBTxStatusResponse(txResponse);
	
	if ( txResponse.getDeliveryStatus() == SUCCESS )	delivered = 1
#endif

#ifdef TX_DEBUG
	if ( xbeeSim.getDeliveryStatus() == SUCCESS )	delivered = 1;
#ifdef BOX_DEBUG
	if ( delivered )	std::cout << "...it was a success!\n";
	else std::cout << "...it was not received.\n";
#endif  
#endif
  
	return delivered;
}
 
 
 
/**
* Creates and sends a new Tx packet.
*
* @param payload - array holding the data to be sent
* @param size - the amount of data to be sent
*/
void transmit(uint8_t payload[], int size)
{
#ifndef TX_DEBUG  
	ZBTxRequest zbTx = ZBTxRequest(addr64, payload, size);
	xbee.send(zbTx);
#endif

#ifdef TX_DEBUG
	xbeeSim.send();
#ifdef BOX_DEBUG
	std::cout << "Sending new packet...\n";
  
	std::cout << "Packet header: " << (int)payload[0]  <<  "\n";
	std::cout << "Packet number: " << (int)payload[2] << " of " << (int)payload[1] << "\n";
	std::cout << "Data: ";
  
	for ( int i = 3; i < size; i++ )
		std::cout << (int)payload[i]  <<  " ";

	std::cout << "\n\n\n";
#endif
#endif
}