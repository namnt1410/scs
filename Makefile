CC = gcc
CFLAGS = -g -Wall
LIBS = -lm
INCLUDES = -Iinclude -include project-conf.h 
OBJS = objs/libfdr.a objs/sequence.o objs/dag.o

SCS_SOURCEFILES = src/main.c src/input.c src/scs_graph.c src/scs_alpha.c src/scs_greedy.c src/scs_tour.c src/pair/pair.c src/scs_lsearch.c src/lsearch/lsearch.c src/scs_mmerge.c src/mmerge/*.c src/scs_reduce_expand.c src/scs_deposition_reduction.c src/RE/*.c

all: scs 

scs: $(OBJS)
	$(CC) $(CFLAGS) -o scs $(SCS_SOURCEFILES) $(OBJS) $(LIBS) $(INCLUDES) 

clean:
	find . -type f -name "*~" -delete
	rm -rf *~ scs
