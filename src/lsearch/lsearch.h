#ifndef __LSEARCH_H__
#define __LSEARCH_H__

#include "sequence.h"	

#ifdef LS_CONF_MAX_LOOP_COUNT
#define LS_MAX_LOOP_COUNT LS_CONF_MAX_LOOP_COUNT
#else
#define LS_MAX_LOOP_COUNT 50
#endif

#ifdef LS_CONF_MAX_NONIMPROVED_CONTINUOUS_LOOP_COUNT
#define LS_MAX_NONIMPROVED_CONTINUOUS_LOOP_COUNT LS_CONF_MAX_NONIMPROVED_CONTINUOUS_LOOP_COUNT
#else
#define LS_MAX_NONIMPROVED_CONTINUOUS_LOOP_COUNT 2
#endif

#define LC_TYPE_SHIFT		0
#define LC_TYPE_EXCH		1

#ifdef LC_CONF_TYPE
#define LC_TYPE LC_CONF_TYPE
#else 
#define LC_TYPE LC_TYPE_SHIFT
#endif 

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
