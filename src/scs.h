#ifndef __SCS_H__
#define __SCS_H__

#include "sequence.h"

#define MAX_ALPHABET_SIZE	10000

int scs_graph(SequenceList list, int *super);
int scs_alpha(SequenceList list, int *super);
int scs_alpha_leftmost(SequenceList list, int *super);
int scs_greedy(SequenceList list, int *super);
int scs_tour(SequenceList list, int *super);
int scs_lsearch(SequenceList list, int *super);

int scs_mmerge_H0(SequenceList list, int *super);
int scs_mmerge_H1(SequenceList list, int *super);
int scs_mmerge_H2(SequenceList list, int *super);
int scs_mmerge_H3(SequenceList list, int *super);

int scs_reduce_expand(SequenceList list, int *super, int (*scs)(SequenceList , int *));
int scs_deposition_reduction(SequenceList list, int *super, int (*scs)(SequenceList , int *));

#endif
