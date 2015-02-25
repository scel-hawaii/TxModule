#include "XBeeSim.h"

/**
* Returns the packet available flag.
*
* @return whether or not a packet is available
*/
int XBeeSim::getAvailability()
{
	return isAvailable;
}

/**
* Sets the packet available flag.
*
* @param val - value to set the flag to
*/
void XBeeSim::setAvailability(int val)
{
	isAvailable = val;
}

/**
* Returns the api Id of the received packet
*
* @return the api Id of the packet
*/
int XBeeSim::getApiId()
{
	return apiId;
}

/**
* Sets the packet available flag.
*
* @param val - value to set the flag to
*/
void XBeeSim::setApiId(int val)
{
	apiId = val;
}

/**
* Returns the delivery status of the transmitted packet.
*
* @return the delivery status of the packet
*/
int XBeeSim::getDeliveryStatus()
{
	return deliveryStatus;
}

/**
* Sets the delivery status flag.
*
* @param val - value to set the flag to
*/
void XBeeSim::setDeliveryStatus(int val)
{
	deliveryStatus = val;
}

/**
*  "Sends" a new packet and automatically
*  sets flags to mimic the successful transmission
*  of a packet.
*/
void XBeeSim::send()
{
	isAvailable = 1;
	apiId = ZB_TX_STATUS_RESPONSE;
	deliveryStatus = SUCCESS;
}