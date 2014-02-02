all: network.a

network.a: network.o
	ar rvs network.a network.o

network.o: network.cpp
	g++ -c network.cpp

clear:
	rm -f *.a
	rm -f *.o
