#ifndef __SCS_H__
#define __SCS_H__

#include "sequence.h"

#define MAX_SEQUENCE_LEN 	1000

char* scs_alpha(SequenceList list, char* alphabet);
char* scs_mmerge(SequenceList list, char* alphabet);
char* scs_greedy(SequenceList list, char* alphabet);
char* scs_graph(SequenceList list, char* alphabet);
char* scs_reduce_expand(SequenceList list, char* alphabet);

#endif
