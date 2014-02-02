all: jsmn.a 

jsmn.a: jsmn.o
	ar rvs jsmn.a jsmn.o

jsmn.o:
	gcc -c jsmn.c    

clear:
	rm -f *.o
	rm -f *.a
