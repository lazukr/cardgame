# Makefile for the whole project
#
CC = gcc
CFLAGS += -std=c99 -g -Wall
OBJDIR = src
OBJS = $(addprefix $(OBJDIR)/, card.o deck.o player.o match.o)

game: $(OBJS) game.o
	$(CC) $(CFLAGS) -o $@ game.c $(OBJS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f *.o
