CC = gcc
CFLAGS = -Wall

CIBLES	= shell ls touch mkdir mv cp rm rmdir cat chmod

all: $(CIBLES)

clean: 
	rm *.o 

run: all
	./shell