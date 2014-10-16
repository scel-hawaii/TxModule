boxDriver: boxDriver.o XBeeWrapper.o TxModule.o
	g++ boxDriver.o XBeeWrapper.o TxModule.o -o boxDriver

unitTests:  unitTests.o XBeeWrapper.o TxModule.o
	g++ unitTests.o XBeeWrapper.o TxModule.o -o unitTests
#

boxDriver.o:  config.h XBeeWrapper.h TxModule.h

unitTests.o: config.h XBeeWrapper.h TxModule.h

XBeeWrapper.o:  config.h XBeeWrapper.h

TxModule.o:  config.h XBeeWrapper.h TxModule.h

#
clean:
	rm -f *.o boxDriver unitTests
