#ifndef __SCS_H__
#define __SCS_H__

#include "sequence.h"

#define MAX_LEN 	10000

int scs_alpha(SequenceList list, int *alphabet, int alpha_len, int *super);
int scs_greedy(SequenceList list, int *super);
int scs_reduce_expand(SequenceList list, int *super);
/*char* scs_mmerge(SequenceList list, char* alphabet);
char* scs_graph(SequenceList list, char* alphabet);
char* scs_lsearch(SequenceList list, char* alphabet);*/

#endif
