driver: debugDriver.o XBeeWrapper.o TxModule.o
	g++ debugDriver.o XBeeWrapper.o TxModule.o -o driver

#

debugDriver.o:  XBeeWrapper.h TxModule.h

XBeeWrapper.o:  XBeeWrapper.h

TxModule.o:  XBeeWrapper.h TxModule.h

#
clean:
	rm -f *.o driver
