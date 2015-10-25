CC = gcc
CFLAGS = -g -Wall
LIBS = -lm
INCLUDES = -I../include
OBJS = ../objs/*

SCS_SOURCEFILES = scs_alpha.c scs_mmerge.c scs_greedy.c pair/pair.c scs_graph.c scs_reduce_expand.c scs_lsearch.c mmerge/mmerge.c mmerge/heuristics.c lsearch/lsearch.c

all: scs 

scs: $(OBJS)
	$(CC) $(CFLAGS) -o scs main.c input.c $(OBJS) $(SCS_SOURCEFILES) $(LIBS) $(INCLUDES)

clean:
	rm -f *.o *~ scs
