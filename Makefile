CC = gcc
CFLAGS = -Wall

CIBLES	= shell ls touch mkdir mv

all: $(CIBLES)

clean: 
	rm *.o 

run: all
	./shell