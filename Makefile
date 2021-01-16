CC = gcc
CFLAGS = -Wall

CIBLES	= shell ls touch mkdir

all: $(CIBLES)

clean: 
	rm *.o 

run: all
	./shell