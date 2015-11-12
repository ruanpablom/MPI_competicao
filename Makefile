CC=gcc
CFLAGS= -c -Wall
EFLAGS= -lcrypt
OBJECTS= crack.o

all: crack

crack: $(OBJECTS) 
	$(CC) -o crack $(OBJECTS) $(EFLAGS)

crack.o: crack.c
	$(CC) $(CFLAGS) crack.c

clean:
	rm crack crack.o
