CC = gcc
CFLAGS = -Wall
CFLAGS  += -D_GNU_SOURCE
CFLAGS  += -g


CIBLES	= shell ls touch mkdir mv cp rm rmdir cat chmod quickdiff head clean

all: $(CIBLES)

clean_all: 
	rm *.o 

run: all
	./shell