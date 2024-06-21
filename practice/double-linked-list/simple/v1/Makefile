CC=gcc
CFLAGS=-I.
build: main.o list.o
	$(CC) -o list main.o list.o

debug: main.c list.c
	$(CC) -g -o list main.c list.c

test: test.o
	$(CC) -o test test.o
clean:
	rm *.o *.out list test
