all: pushnotifier.a 
	
pushnotifier.a: pushnotifier.o
	cd network; make
	cd jsmn; make
	cd exception; make
	ar rvs pushnotifier.a *.o network/*.o jsmn/*.o exception/exception.o

pushnotifier.o: pushnotifier.cpp pushnet.cpp
	g++ -c pushnotifier.cpp pushnet.cpp

clear:
	cd network; make clear
	cd jsmn; make clear
	cd exception; make clear
	rm -f *.a
	rm -f *.o

example:
	g++ -o example example.cpp pushnotifier.a
