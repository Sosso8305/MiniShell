CC = gcc
CFLAGS = -Wall
CIBLES	= shell LS

all: $(CIBLES)

clean: 
	rm *.o 

run: all
	./shell