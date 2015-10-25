CC = gcc
CFLAGS = -g -Wall
LIBS = -lm
INCLUDES = -Iinclude
OBJS = objs/*

SCS_SOURCEFILES = src/*.c src/pair/pair.c src/mmerge/mmerge.c src/mmerge/heuristics.c src/lsearch/lsearch.c

all: scs 

scs: $(OBJS)
	$(CC) $(CFLAGS) -o scs $(SCS_SOURCEFILES) $(OBJS) $(LIBS) $(INCLUDES)

clean:
	rm -rf *~ scs
