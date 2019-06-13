Projekt: main.c functions.o list.o
	gcc main.c functions.o list.o -g -pthread -o Mutex
	rm *.o


functions.o: ./Headers/functions.h ./Source/functions.c
	gcc ./Source/functions.c -g -c -pthread -o  functions.o 

list.o: ./Headers/list.h ./Source/list.c
	gcc ./Source/list.c -g -c -pthread -o  list.o 