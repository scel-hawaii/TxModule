#include "XBeeSim.h"

/**
* Default constructor for XBeeSim class.
*/
XBeeSim::XBeeSim()
{
	XBeeSim(0, 0, 0);
}

/**
* Constructor for XBeeSim class.
*
* @param availability - value to set the available flag to
* @ id - value to set the api Id to
* @param dStatus - value to set the delivery flag to
*/
XBeeSim::XBeeSim(int availability, int id, int dStatus)
{
	isAvailable = availability;
	apiId = id;
	deliveryStatus = dStatus;
}

/**
* Destructor for XBeeSim class.
*/
XBeeSim::~XBeeSim()
{
}

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