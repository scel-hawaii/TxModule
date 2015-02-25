OBJS = XBeeSim.o Wrapper.o TxModule.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG) -DTX_DEBUG
boxFLAGS := $(CFLAGS) -DBOX_DEBUG
LFLAGS = -Wall $(DEBUG)

#To do: remove XBeeSim when using XBee

boxDriver: CFLAGS = $(boxFLAGS)



unitTests: unitTests.o $(OBJS)
	$(CC) $(LFLAGS) unitTests.o $(OBJS) -o unitTests

boxDriver: boxDriver.o $(OBJS)
	$(CC) $(LFLAGS) boxDriver.o $(OBJS) -o boxDriver



boxDriver.o: Wrapper.h TxModule.h
	$(CC) $(CFLAGS) boxDriver.cpp

unitTests.o: Wrapper.h TxModule.h
	$(CC) $(CFLAGS) unitTests.cpp

XBeeSim.o: XBeeSim.h
	$(CC) $(CFLAGS) XBeeSim.cpp

Wrapper.o: Wrapper.h
	$(CC) $(CFLAGS) Wrapper.cpp

TxModule.o: Wrapper.h TxModule.h
	$(CC) $(CFLAGS) TxModule.cpp



clean:
	rm *.o unitTests boxDriver
