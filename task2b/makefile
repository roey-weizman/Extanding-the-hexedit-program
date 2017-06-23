all: hexeditplus
 
hexeditplus: hexeditplus.o 
	gcc -Wall  -g  -o hexeditplus hexeditplus.o 
hexeditplus.o : hexeditplus.c
	gcc -Wall  -g -c hexeditplus.c
clean:
	rm -f *.o  hexeditplus
