CC = gcc
CFLAGS = -Wall
CFLAGS  += -D_GNU_SOURCE
CFLAGS  += -g


CIBLES	= shell ls touch mkdir mv cp rm rmdir cat chmod quickdiff head clean ln wc

all: $(CIBLES)

clean2: 
	$(RM) -f core *.o $(CIBLES) *~

run: all
	./shell