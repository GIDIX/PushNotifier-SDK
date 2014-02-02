all: exception.a

exception.a: exception.o
	ar rvs exception.a exception.o

exception.o: exception.cpp
	g++ -c exception.cpp

clear:
	rm -f *.a
	rm -f *.o
