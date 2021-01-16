CC = gcc
CFLAGS = -Wall

CIBLES	= shell ls touch mkdir mv cp rm

all: $(CIBLES)

clean: 
	rm *.o 

run: all
	./shell