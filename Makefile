CC = gcc
CFLAGS = -g -Wall
LIBS = -lm
INCLUDES = -Iinclude
OBJS = objs/libfdr.a objs/sequence.o objs/block.o

SCS_SOURCEFILES = src/main.c src/input.c src/scs_alpha.c src/scs_greedy.c src/pair/pair.c 
#src/mmerge/mmerge.c src/mmerge/heuristics.c src/lsearch/lsearch.c

all: scs 

scs: $(OBJS)
	$(CC) $(CFLAGS) -o scs $(SCS_SOURCEFILES) $(OBJS) $(LIBS) $(INCLUDES)

clean:
	find . -type f -name "*~" -delete
	rm -rf *~ scs
