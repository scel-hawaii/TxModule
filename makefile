driver: debugDriver.o XBeeWrapper.o TxModule.o
	g++ debugDriver.o XBeeWrapper.o TxModule.o -o driver

#

debugDriver.o:  config.h XBeeWrapper.h TxModule.h

XBeeWrapper.o:  config.h XBeeWrapper.h

TxModule.o:  config.h XBeeWrapper.h TxModule.h

#
clean:
	rm -f *.o driver
