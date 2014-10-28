OBJS = XBeeWrapper.o TxModule.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -DTX_DEBUG
boxFLAGS := $(CFLAGS) -DBOX_DEBUG
LFLAGS = -Wall $(DEBUG)



boxDriver: CFLAGS = $(boxFLAGS)



unitTests: unitTests.o $(OBJS)
	$(CC) $(LFLAGS) unitTests.o $(OBJS) -o unitTests

boxDriver: boxDriver.o $(OBJS)
	$(CC) $(LFLAGS) boxDriver.o $(OBJS) -o boxDriver



boxDriver.o: XBeeWrapper.h TxModule.h
	$(CC) $(CFLAGS) boxDriver.cpp

unitTests.o: XBeeWrapper.h TxModule.h
	$(CC) $(CFLAGS) unitTests.cpp

XBeeWrapper.o: XBeeWrapper.h
	$(CC) $(CFLAGS) XBeeWrapper.cpp

TxModule.o: XBeeWrapper.h TxModule.h
	$(CC) $(CFLAGS) TxModule.cpp



clean:
	rm *.o unitTests boxDriver
