#ifndef __LSEARCH_H__
#define __LSEARCH_H__

#include "sequence.h"

#define LC_TYPE_SHIFT		0
#define LC_TYPE_EXCHANGE	1

typedef struct SolutionNode SolutionNode;
typedef struct Solution Solution;

typedef struct SolutionNode {
  int pos;
  int seqno;
  int index;
  Sequence *seq;
  struct SolutionNode *prev, *next;
} SolutionNode;

typedef struct Solution {
  SolutionNode *first;
  SolutionNode *last;
  SolutionNode ***node_tbl;
  SolutionNode **sol;
  int sol_len;
  int seqs;
} Solution;

Solution *lsearch (SequenceList list);
int ls_evaluate (Solution *sol, int *seq);  

#endif
