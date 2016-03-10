#ifndef __MMERGE_H__
#define __MMERGE_H__

#include "sequence.h"
#include "heuristics.h"

#define MM_MAJORITY_H0		def_majority
#define MM_MAJORITY_H1 		heuristics_majority_H1
#define MM_MAJORITY_H2		heuristics_majority_H2
#define MM_MAJORITY_H3		heuristics_majority_H3

int def_majority(Sequence **, int, int *, int, int *, int **, int *);
int mmerge(Sequence **, int, int *, int, int (*majority)(Sequence **, int, int *, int, int *, int **, int *), int *);

#endif
