# Makefile for all dependencies / source files
CC = gcc
CFLAGS += -std=c99 -g -Wall -c
OBJS = card.o deck.o player.o match.o utils.o

all: $(OBJS)

%: %.c
	$(CC) $(CFLAGS) $@ $<

clean:
	rm -f *.o
