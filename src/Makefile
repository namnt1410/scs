CC = gcc
CFLAGS = -g -Wall
LIBS = -lm
INCLUDES = -I../include
OBJS = block.o dag.o sequence.o ../objs/*.a

SCS_SOURCEFILES = scs_alpha.c scs_mmerge.c scs_greedy.c pair.c scs_graph.c scs_reduce_expand.c mmerge.c heuristics.c 

all: scs 

scs: $(OBJS)
	$(CC) $(CFLAGS) -o scs main.c input.c $(OBJS) $(SCS_SOURCEFILES) $(LIBS) $(INCLUDES)

dag.o: dag.c
	$(CC) $(CFLAGS) $(INCLUDES) -c dag.c

sequence.o: sequence.c
	$(CC) $(CFLAGS) $(INCLUDES) -c sequence.c

block.o: block.c
	$(CC) $(CFLAGS) $(INCLUDES) -c block.c

clean:
	rm -f *.o *~
