#ifndef __LSEARCH_H__
#define __LSEARCH_H__

#include "sequence.h"

#define LC_TYPE_SHIFT		0
#define LC_TYPE_EXCHANGE	1

typedef struct SolutionNode SolutionNode;
typedef struct SolutionBlock SolutionBlock;
typedef struct Solution Solution;

typedef struct SolutionNode {
  int pos;
  int seqno;
  int index;
  Sequence *seq;
  SolutionBlock *block;
} SolutionNode;

typedef struct SolutionBlock {
  int pos;
  int len;
} SolutionBlock;

typedef struct Solution {
  SolutionNode ***node_tbl;
  SolutionNode **sol;
  SolutionBlock **block_tbl;
  int sol_len;
  int seqs;
} Solution;

Solution *lsearch (SequenceList list);
int ls_evaluate (Solution *sol, int start, int end, int *seq);  

#endif
