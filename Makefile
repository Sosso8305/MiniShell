CC = gcc
CFLAGS = -Wall

CIBLES	= shell ls touch

all: $(CIBLES)

clean: 
	rm *.o 

run: all
	./shell