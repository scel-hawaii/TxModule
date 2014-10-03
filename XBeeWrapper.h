#define TX_DEBUG

#ifndef XBEE_WRAPPER_H
#define XBEE_WRAPPER_H

#include <Arduino.h>
#include <XBee.h>

#ifndef TX_DEBUG
extern XBee xbee;
extern XBeeAddress64 addr64;
extern ZBRxResponse rxResponse;
extern ZBTxStatusResponse txResponse;
#endif

#ifdef TX_DEBUG
extern int transmitFlag; //used to flag that a "packet" has been successfully sent
#endif

void XBeeInit();

int XBeeIsAvailable();

int XBeeGetApiId();

void XBeeGetZBRxResponse();

void XBeeGetZBTxStatusResponse();

int XBeeGetDeliveryStatus();

void XBeeSend(uint8_t q[], int size);

#endif