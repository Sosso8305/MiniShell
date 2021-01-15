CC = gcc
CFLAGS = -Wall

CIBLES	= shell ls

all: $(CIBLES)

clean: 
	rm *.o 

run: all
	./shell