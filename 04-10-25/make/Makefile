CC=gcc
CFLAGS=-c -Wall -Wextra

all: hello

hello: main-for-make.o
	$(CC) main-for-make.o -o myFavouriteProgramm
	./myFavouriteProgramm

main-for-make.o: main-for-make.c
	$(CC) $(CFLAGS) main-for-make.c

clean:
	rm -rf *.o myFavouriteProgramm