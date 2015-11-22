#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lsearch.h"

Solution *ls_init(SequenceList list);
int ls_shift (Solution *sol, SolutionNode *node, int offset);
int ls_exchange (Solution *sol, SolutionNode *node, int offset);

Solution *ls_init(SequenceList list) {
  Solution *sol;
  SolutionNode *node;
  Sequence *seq;
  int seqno, i;
  int count;

  sol = (Solution *) malloc (sizeof(Solution));

  sol->first = NULL;
  sol->last = NULL;
  sol->seqs = get_size(list); 
  sol->node_tbl = (SolutionNode ***) malloc (sizeof(SolutionNode **) * sol->seqs);

  seq = list; seqno = 0;
  sol->sol_len = 0;
  while (seq) {
    sol->sol_len += seq->len;
    sol->node_tbl[seqno] = (SolutionNode **) malloc (sizeof(SolutionNode *) * seq->len);
    for(i = 0; i < seq->len; i++) {
      node  = (SolutionNode *) malloc (sizeof(SolutionNode));
      sol->node_tbl[seqno][i] = node;
 
      node->seqno = seqno;
      node->index = i;
      node->seq = seq;
      node->block = NULL;

      node->prev = NULL; node->next = NULL;
    }

    seq = seq->next; seqno++; 
  } 

  sol->sol = (SolutionNode **) malloc (sizeof(SolutionNode *) * sol->sol_len);

  sol->block_tbl = (SolutionBlock **) malloc (sol->sol_len * sizeof(SolutionBlock *));
  for (i = 0; i < sol->sol_len; i++) sol->block_tbl[i] = (SolutionBlock *) malloc (sizeof(SolutionBlock));

  i = 0;
  do {
    count = 0;
    seq = list; seqno = 0;
    while (seq) {
      if (i < seq->len) {
        count++;
        node = sol->node_tbl[seqno][i];
        if (!sol->first) {
          node->pos = 0;
          sol->first = node;
          sol->last = node;
        } else {
          node->prev = sol->last;
          node->pos = node->prev->pos + 1;
          sol->last->next = node;
          sol->last = node;
        }
        sol->sol[node->pos] = node;
      }

      seq = seq->next; seqno++;
    }

    i++;
  } while (count); 

  return sol;
}

Solution *lsearch (SequenceList list) {
  Solution *sol;
  SolutionNode *node;
  Sequence *seq;
  int *super;
  int val, min, best, better;
  int offsetmin, offsetmax;
  int offset, best_offset;
  int i, count, seqno, m = 0;  

  sol = ls_init(list);
  super = (int*) malloc (sol->sol_len * sizeof(int));
  best = ls_evaluate(sol, super);

  do {
    better = 0;
    i = 0;
    do {
      seq = list;
      count = 0; seqno = 0;
      while(seq) {
        min = best; best_offset = 0;
	if(i < seq->len) {
	  count++;
	  node = sol->node_tbl[seqno][i];
          if (i > 0) 
	    offsetmin = sol->node_tbl[seqno][i - 1]->pos - node->pos + 1;
          else offsetmin = -node->pos;
          if ((seq->len - i) > 1) 
	    offsetmax = sol->node_tbl[seqno][i + 1]->pos - node->pos - 1;
          else offsetmax = sol->sol_len - node->pos - 1;
 
	  offset = offsetmin;
	  while (offset <= offsetmax) {
	    if (offset != 0 && ls_shift (sol, node, offset)) {
	      val = ls_evaluate (sol, super);

	      if (val < min) {
		min = val;
		best_offset = offset;
	      }
            
	      ls_shift (sol, node, -offset);
	    }
	    offset++;
	  }

	  if (min < best) {
	    ls_shift (sol, node, best_offset);
	    best = ls_evaluate (sol, super);
            better = 1;
	  }
	}
 
	seq = seq->next; seqno++;
      } 

      i++;
    } while (count);
    m++;
  } while (better);

  free(super);

  return sol;
}

int check_solution (Solution *sol) {
  int i;

  for (i = 0; i < sol->sol_len; i++)
    if (sol->sol[i]->pos != i) return 0;

  return 1;
}

int changeable (Solution *sol, SolutionNode *node, int offset) {
  return (node && offset != 0 && 
	  node->pos >= 0 && node->pos < sol->sol_len && 
	  node->pos + offset >= 0 && node->pos + offset <= sol->sol_len); 
} 

int ls_shift (Solution *sol, SolutionNode *node, int offset) {
  if (!changeable (sol, node, offset)) return 0;

  SolutionNode *victim, *prev, *next;
  int i;

  prev = node->prev; next = node->next;
 
  victim = node;

  if (offset < 0) {
    for (i = 0; i > offset; i--) { 
      victim = victim->prev; sol->sol[++victim->pos] = victim;
    }
    node->prev = victim->prev;
    node->next = victim;
  } else if (offset > 0) {
    for (i = 0; i < offset; i++) {
      victim = victim->next; sol->sol[--victim->pos] = victim;
    }
    node->prev = victim;
    node->next = victim->next;
  }

  node->pos = node->pos + offset;
  sol->sol[node->pos] = node;

  if (prev) prev->next = next;
  else sol->first = next;
  if (next) next->prev = prev;
  else sol->last = prev;

  if(node->prev) node->prev->next = node;
  else sol->first = node; 
  if(node->next) node->next->prev = node;
  else sol->last = node;

  return 1;
}

int ls_exchange (Solution *sol, SolutionNode *node, int offset) {
  if (!changeable (sol, node, offset)) return 0;

  SolutionNode *victim;
  SolutionNode *left, *right, *prev, *next;
  int pos1, pos2;
  int i;
 
  victim = node;

  if (offset < 0) {
    for (i = 0; i > offset; i--) 
      victim = victim->prev;
    if ((victim->seq->len - victim->index) > 1 && sol->node_tbl[victim->seqno][victim->index + 1]->pos < node->pos) return 0;
    left = victim; right = node;
  } else if (offset > 0) {
    for (i = 0; i < offset; i++) 
      victim = victim->next;
    if (victim->index && sol->node_tbl[victim->seqno][victim->index - 1]->pos > node->pos) return 0;
    left = node; right = victim; 
  }

  pos1 = left->pos; pos2 = right->pos;

  prev = right->prev;
  right->prev = left->prev;
  if (right->prev) right->prev->next = right;

  next = left->next;
  left->next = right->next;
  if (right->next) right->next->prev = left;

  if (left == prev) {
    right->next = left;
    left->prev = right;
  } else {
    right->next = next;
    next->prev = right;
    left->prev = prev;
    prev->next = left;
  } 

  if (left == sol->first) sol->first = right;
  if (right == sol->last) sol->last = left;

  right->pos = pos1; sol->sol[pos1] = right; 
  left->pos = pos2; sol->sol[pos2] = left;

  return 1;
} 

int ls_evaluate (Solution *sol, int *seq) {
  SolutionNode *node;
  int val = 0;
  int *touchtable;
  int sym;
  SolutionBlock *block;
  
  touchtable = (int*) malloc (sol->seqs * sizeof(int));
  node = sol->first;
  while(node) {
    memset (touchtable, 0, sol->seqs * sizeof(int));

    block = sol->block_tbl[node->pos];
    block->pos = node->pos;
    block->len = 0;

    sym = node->seq->seq[node->index];
    seq[val++] = sym;
    touchtable[node->seqno] = 1;
    
    do {
      block->len++;
      node->block = block;
      node = node->next;
    } while(node && 
	    node->seq->seq[node->index] == sym && 
	    !touchtable[node->seqno]++);
  }

  free(touchtable);

  return val;
}
