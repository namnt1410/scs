#ifndef __SCS_H__
#define __SCS_H__

#include "sequence.h"

#define MAX_ALPHABET_SIZE	10000

int scs_alpha(SequenceList list, int *alphabet, int alpha_len, int *super);
int scs_greedy(SequenceList list, int *super);
int scs_reduce_expand(SequenceList list, int *super);
int scs_mmerge(SequenceList list, int *alphabet, int alpha_len, int *super);
int scs_lsearch(SequenceList list, int *super);

#endif
