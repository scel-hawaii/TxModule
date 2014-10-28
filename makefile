OBJS = XBeeWrapper.o TxModule.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -DTX_DEBUG
C2FLAGS := $(CFLAGS) -DBOX_DEBUG
LFLAGS = -Wall $(DEBUG)



boxDriver: CFLAGS = $(C2FLAGS)



unitTests: unitTests.o $(OBJS)
	$(CC) $(LFLAGS) unitTests.o $(OBJS) -o unitTests

boxDriver: boxDriver.o $(OBJS)
	$(CC) $(LFLAGS) boxDriver.o $(OBJS) -o boxDriver



boxDriver.o: XBeeWrapper.h TxModule.h
	$(CC) $(CFLAGS) boxDriver.cpp

unitTests.o: config.h XBeeWrapper.h TxModule.h
	$(CC) $(CFLAGS) unitTests.cpp

XBeeWrapper.o: config.h XBeeWrapper.h
	$(CC) $(CFLAGS) XBeeWrapper.cpp

TxModule.o:  config.h XBeeWrapper.h TxModule.h
	$(CC) $(CFLAGS) TxModule.cpp



clean:
	rm *.o unitTests boxDriver
