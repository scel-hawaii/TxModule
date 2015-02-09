#ifndef XBEE_WRAPPER_H
#define XBEE_WRAPPER_H

#ifndef TX_DEBUG
#include <Arduino.h>
#include <XBee.h>
#endif

#ifdef TX_DEBUG
#include <iostream>
#include <stdint.h>

//the following are defined in the XBee library
#define SUCCESS 0x00
#define ZB_RX_RESPONSE 0x90
#define ZB_TX_STATUS_RESPONSE 0x8B
#endif


#ifndef TX_DEBUG
extern XBee xbee;
extern XBeeAddress64 addr64;
extern ZBRxResponse rxResponse;
extern ZBTxStatusResponse txResponse;
#endif

#ifdef TX_DEBUG
extern int transmitFlag; //used to flag that a "packet" has been successfully sent

void delay(int n);
#endif

void XBeeInit();

int XBeeIsAvailable(int * isAvailable);

int XBeeGetApiId(int id);

void XBeeGetZBRxResponse();

void XBeeGetZBTxStatusResponse();

int XBeeGetDeliveryStatus(int isSuccess);

void XBeeSend(uint8_t q[], int size, int * isAvailable);

#endif
