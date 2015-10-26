#ifndef __LSEARCH_H__
#define __LSEARCH_H__

#include "sequence.h"

typedef struct SolutionNode SolutionNode;
typedef struct Solution Solution;

typedef struct SolutionNode {
  int seqno;
  int index;
  Sequence *seq;
  Solution *sol;
  struct SolutionNode *left_nbr, *right_nbr;
  struct SolutionNode *prev, *next;
} SolutionNode;

typedef struct Solution {
  SolutionNode *first;
  SolutionNode *last;
  SolutionNode ***node_tbl;
  int seqs;
  int sol_len;
} Solution;

Solution *lsearch (SequenceList list);
int ls_evaluate (Solution *sol, char *seq);  

#endif
