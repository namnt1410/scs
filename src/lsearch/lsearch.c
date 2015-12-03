#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lsearch.h"

static int loop = 0;

Solution *ls_init(SequenceList list);
void ls_compress (Solution *sol, int start, int end);
int ls_localchange (Solution *sol, int pos, int offset, int *start, int *end);
int ls_shift (Solution *sol, int pos, int offset);
//int ls_exchange (Solution *sol, SolutionNode *node, int offset);

Solution *ls_init(SequenceList list) {
  Solution *sol;
  SolutionNode *node;
  Sequence *seq;
  int seqno, i;
  int count, pos;

  sol = (Solution *) malloc (sizeof(Solution));
  sol->seqs = get_size(list); 
  sol->node_tbl = 
    (SolutionNode ***) malloc (sizeof(SolutionNode **) * sol->seqs);

  seq = list; seqno = 0;
  sol->sol_len = 0;
  while (seq) {
    sol->sol_len += seq->len;
    sol->node_tbl[seqno] = 
      (SolutionNode **) malloc (sizeof(SolutionNode *) * seq->len);
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

  sol->block_tbl = 
    (SolutionBlock **) malloc (sol->sol_len * sizeof(SolutionBlock *));
  for (i = 0; i < sol->sol_len; i++) 
    sol->block_tbl[i] = (SolutionBlock *) malloc (sizeof(SolutionBlock));

  pos = 0; i = 0;
  do {
    count = 0;
    seq = list; seqno = 0;
    while (seq) {
      if (i < seq->len) {
        count++;
        node = sol->node_tbl[seqno][i];
        if (pos) {
          node->prev = sol->sol[pos - 1];
          node->prev->next = node;
        }
        node->pos = pos++;
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
  int val, pos, val1, val2, min, better;
  int start, end;
  int offsetmin, offsetmax;
  int offset, best_offset;
  int i, count, seqno, m = 0; 

  sol = ls_init(list);
  ls_compress (sol, 0, sol->sol_len - 1);

  do {
    loop++;
    better = 0;
    i = 0;
    do {
      seq = list;
      count = 0; seqno = 0;
      while(seq) {
        min = 0; best_offset = 0;
	if(i < seq->len) {
	  count++;
	  node = sol->node_tbl[seqno][i];
          pos = node->pos;

          if (i > 0) 
	    offsetmin = sol->node_tbl[seqno][i - 1]->pos - pos + 1;
          else offsetmin = -pos;
          if ((seq->len - i) > 1) 
	    offsetmax = sol->node_tbl[seqno][i + 1]->pos - pos - 1;
          else offsetmax = sol->sol_len - pos - 1;
 
	  offset = offsetmin;
	  while (offset <= offsetmax) {
	    if (offset != 0) {
              val1 = ls_localchange (sol, pos, offset, &start, &end);
              val2 = ls_evaluate (sol, start, end, NULL);

              val = val1 - val2;
              if (val < min) {
                min = val;
                best_offset = offset;
              } 
	    }
	    offset++;
	  }

	  if (min < 0) {
            ls_localchange (sol, pos, best_offset, &start, &end);
	    ls_shift (sol, pos, best_offset);
	    ls_compress (sol, start, end);
            better = 1;
	  }
	}
 
	seq = seq->next; seqno++;
      } 

      i++;
    } while (count);
    m++;
  } while (better);

  printf ("loop: %d\n", loop);

  return sol;
}

int check_solution (Solution *sol) {
  int i;

  for (i = 0; i < sol->sol_len; i++) {
    if (sol->sol[i]->pos != i) return 0;
  }

  return 1;
}

int localchangeable (Solution *sol, int pos, int offset) {
  return (offset && 
	  pos >= 0 && pos < sol->sol_len && 
	  pos + offset >= 0 && pos + offset < sol->sol_len); 
} 

int ls_localchange (Solution *sol, int pos, int offset, int *start, int *end) {
  if (!localchangeable (sol, pos, offset)) return 0; 

  SolutionNode *node;
  int *touchtable;
  int ptr, sym;
  int count = 0;

  if (offset > 0) {
    if (pos) 
      *start = sol->sol[pos - 1]->block->pos;
    else *start = sol->sol[pos]->block->pos; 
    
    *end = pos + offset;
  } else { 
    if (pos + offset) 
      *start = sol->sol[pos + offset - 1]->block->pos;
    else *start = sol->sol[pos + offset]->block->pos;
    
    *end = pos;
  }

  ls_shift (sol, pos, offset);

  touchtable = (int*) malloc (sol->seqs * sizeof(int));
  node = sol->sol[*start]; ptr = *start;
  while (node && 
	 (ptr <= *end || 
	  ptr != node->block->pos)) {
    sym = node->seq->seq[node->index];
    count++;

    memset (touchtable, 0, sol->seqs * sizeof(int));
    touchtable[node->seqno] = 1; 
 
    do {
      if (++ptr < sol->sol_len) node = sol->sol[ptr]; 
      else node = NULL;
    } while(node &&
	    node->seq->seq[node->index] == sym && 
	    !touchtable[node->seqno]++);
  }

  if (node) *end = ptr - 1;
  else *end = sol->sol_len - 1;

  ls_shift (sol, pos + offset, -offset);

  free(touchtable);

  return count;
}

int ls_shift (Solution *sol, int pos, int offset) {
  if (!localchangeable (sol, pos, offset)) return 0;

  SolutionNode *node, *victim, *prev, *next;
  int i;

  node = sol->sol[pos];
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

  node->pos = pos + offset;
  sol->sol[pos + offset] = node;

  if (prev) prev->next = next;
  if (next) next->prev = prev;

  if(node->prev) node->prev->next = node;
  if(node->next) node->next->prev = node;

  if (!check_solution (sol)) printf("Invalid!\n");

  return 1;
}

/*int ls_exchange (Solution *sol, SolutionNode *node, int offset) {
  if (!localchangeable (sol, node, offset)) return 0;

  SolutionNode *victim;
  SolutionNode *left, *right, *prev, *next;
  int pos1, pos2;
  int i;
 
  victim = node;

  if (offset < 0) {
    for (i = 0; i > offset; i--) 
      victim = victim->prev;
    if ((victim->seq->len - victim->index) > 1 && 
	sol->node_tbl[victim->seqno][victim->index + 1]->pos < node->pos) 
      return 0;
    left = victim; right = node;
  } else if (offset > 0) {
    for (i = 0; i < offset; i++) 
      victim = victim->next;
    if (victim->index && 
	sol->node_tbl[victim->seqno][victim->index - 1]->pos > node->pos) 
      return 0;
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

  right->pos = pos1; sol->sol[pos1] = right; 
  left->pos = pos2; sol->sol[pos2] = left;

  return 1;
}*/ 

void ls_compress (Solution *sol, int start, int end) {
  if (start >= end || start < 0 || end >= sol->sol_len) return;

  SolutionNode *node;
  int *touchtable;
  int pos, sym;
  SolutionBlock *block;

  touchtable = (int*) malloc (sol->seqs * sizeof(int));
  node = sol->sol[start]; pos = start;
  while (node && pos <= end) {
    memset (touchtable, 0, sol->seqs * sizeof(int));

    block = sol->block_tbl[node->pos];
    block->pos = pos;
    block->len = 0;

    sym = node->seq->seq[node->index];
    touchtable[node->seqno] = 1;
    
    do {
      block->len++;
      node->block = block;
      node->pos = pos;
      if (++pos < sol->sol_len) node = sol->sol[pos];
      else node = NULL;
    } while(node && pos <= end &&
	    node->seq->seq[node->index] == sym && 
	    !touchtable[node->seqno]++);
  }

  //if (!check_solution (sol)) printf("Invalid!\n");

  free(touchtable);
}

int ls_evaluate (Solution *sol, int start, int end, int *seq) {
  if (start >= end || start < 0 || end >= sol->sol_len) 
    return 0;
 
  SolutionNode *node;
  int i, val = 1;
  int sym;

  node = sol->sol[start];
  sym = node->seq->seq[node->index];
  if (seq) seq[0] = sym;

  for (i = start; i < end; i++) {
    if (sol->sol[i]->block != sol->sol[i + 1]->block) {
      node = sol->sol[i + 1];
      sym = node->seq->seq[node->index];
      if (seq) seq[val] = sym;
      val++;
    }
  }

  return val;
}
