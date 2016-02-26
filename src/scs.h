#ifndef __SCS_H__
#define __SCS_H__

#include "sequence.h"

#define MAX_ALPHABET_SIZE	10000

#ifdef MM_CONF_MAJORITY
#define MM_MAJORITY MM_CONF_MAJORITY
#else 
#define MM_MAJORITY def_majority
#endif

int scs_alpha(SequenceList list, int *super);
int scs_greedy(SequenceList list, int *super);
int scs_tour(SequenceList list, int *super);
int scs_mmerge(SequenceList list, int *super);
int scs_lsearch(SequenceList list, int *super);
int scs_reduce_expand(SequenceList list, int *super, int (*scs)(SequenceList , int *));

#endif
