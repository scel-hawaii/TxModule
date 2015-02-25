/**
*  Class used to simulate XBee behaviour and
*  allow for controlled testing.
*/

#ifndef XBEE_SIM_H
#define XBEE_SIM_H

#define SUCCESS 0x00
#define ZB_RX_RESPONSE 0x90
#define ZB_TX_STATUS_RESPONSE 0x8B

class XBeeSim
{
	public:
		int getAvailability();
		void setAvailability(int val);
		int getApiId();
		void setApiId(int val);
		int getDeliveryStatus();
		void setDeliveryStatus(int val);
		void send();
		
	private:
		int apiId;
		int isAvailable;
		int deliveryStatus;
};
#endif