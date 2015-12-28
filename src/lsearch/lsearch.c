#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lsearch.h"

static int loop = 0;
void *temp;

Solution *ls_init(SequenceList list);
void ls_compress (Solution *sol, int start, int end);
int ls_localchange (Solution *sol, int pos, int offset, int lc_type, int *start, int *end);
int ls_shift (Solution *sol, int pos, int offset);
int ls_exchange (Solution *sol, int pos, int offset);

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
    }

    seq = seq->next; seqno++; 
  } 

  sol->sol = (SolutionNode **) malloc (sizeof(SolutionNode *) * sol->sol_len);
  temp = malloc (sol->sol_len * sizeof(SolutionNode*));

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
        node->pos = pos++;
        sol->sol[node->pos] = node;
      }

      seq = seq->next; seqno++;
    }

    i++;
  } while (count); 

  /*pos = 0;
  seq = list; seqno = 0;
  while (seq) {
    for (i = 0; i < seq->len; i++) {
      node = sol->node_tbl[seqno][i];
      node->pos = pos++;
      sol->sol[node->pos] = node; 
    }

    seq = seq->next; seqno++;
  }*/

  return sol;
}

Solution *lsearch (SequenceList list) {
  Solution *sol;
  SolutionNode *node;
  Sequence *seq;
  int pos, val, change, min, better;
  int start, end;
  int offsetmin, offsetmax;
  int offset, best_offset, best_type;
  int i, count, seqno, m = 0; 

  sol = ls_init(list);
  ls_compress (sol, 0, sol->sol_len);

  do {
    loop++;
    better = 0;
    seq = list; seqno = 0;
    while(seq) {
      for (i = 0; i < seq->len; i++) {
        min = 0; best_offset = 0;
	node = sol->node_tbl[seqno][i];
        pos = node->pos;

	offsetmin = i > 0 ? sol->node_tbl[seqno][i - 1]->pos - pos + 1 : -pos;
	offsetmax = i + 1 < seq->len ? 
	  sol->node_tbl[seqno][i + 1]->pos - pos - 1 : sol->sol_len - pos - 1;
 
	offset = offsetmin;
	while (offset <= offsetmax) {
	  if (offset != 0) {
	    val = ls_localchange (sol, pos, offset, 
				  LC_TYPE_SHIFT, &start, &end);
	    if (val) {
	      change = val - ls_evaluate (sol, start, end, NULL);
	      if (change <= min) {
		min = change;
		best_offset = offset;
		best_type = LC_TYPE_SHIFT;
	      }
	    } 
	  }
	  offset++;
	}

	if (best_offset) {
	  ls_localchange (sol, pos, best_offset, best_type, &start, &end);
	  best_type == LC_TYPE_EXCH ? ls_exchange (sol, pos, best_offset) : 
	    ls_shift (sol, pos, best_offset);
	  ls_compress (sol, start, end);
	  better = 1;
	}
      }

      seq = seq->next; seqno++;
    }
  } while (better && loop <= 20);

  printf ("loop: %d\n", loop);

  /*do {
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

	  offsetmin = i > 0 ? sol->node_tbl[seqno][i - 1]->pos - pos + 1 : -pos;
	  offsetmax = i + 1 < seq->len ? 
	    sol->node_tbl[seqno][i + 1]->pos - pos - 1 : sol->sol_len - pos - 1;
 
	  offset = offsetmin;
	  while (offset <= offsetmax) {
	    if (offset != 0) {
              val = ls_localchange (sol, pos, offset, 
				    LC_TYPE_SHIFT, &start, &end);
              if (val) {
                change = val - ls_evaluate (sol, start, end, NULL);
                if (change < min) {
                  min = change;
                  best_offset = offset;
                  best_type = LC_TYPE_SHIFT;
                }
              } 
	    }
	    offset++;
	  }

	  if (best_offset) {
            ls_localchange (sol, pos, best_offset, best_type, &start, &end);
	    best_type == LC_TYPE_EXCH ? ls_exchange (sol, pos, best_offset) : 
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

  printf ("loop: %d\n", loop);*/

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

int ls_localchange (Solution *sol, int pos, int offset, int lc_type, int *start, int *end) {
  if (!localchangeable (sol, pos, offset)) return 0; 

  SolutionNode *node;
  int *touchtable;
  int ptr, sym;
  int hi, lo;
  int count = 0;

  hi = offset > 0 ? pos + offset : pos;
  lo = offset > 0 ? pos : pos + offset;

  *start = lo ? sol->sol[lo - 1]->block->pos : sol->sol[lo]->block->pos;

  if ((lc_type == LC_TYPE_EXCH && !ls_exchange (sol, pos, offset)) || 
      (lc_type == LC_TYPE_SHIFT && !ls_shift (sol, pos, offset))) return 0;

  touchtable = (int*) malloc (sol->seqs * sizeof(int));
  node = sol->sol[*start]; ptr = *start;
  while (node && 
	 (ptr <= hi || 
	  ptr != node->block->pos)) {
    sym = node->seq->seq[node->index];
    count++;

    memset (touchtable, 0, sol->seqs * sizeof(int));
    touchtable[node->seqno] = 1; 
 
    do {
      node = (++ptr < sol->sol_len) ? sol->sol[ptr] : NULL;
    } while(node &&
	    node->seq->seq[node->index] == sym && 
	    !touchtable[node->seqno]++);
  }

  *end = node ? ptr : sol->sol_len;

  lc_type == LC_TYPE_EXCH ? ls_exchange (sol, pos + offset, -offset) : 
    ls_shift (sol, pos + offset, -offset);

  free(touchtable);

  return count;
}

int ls_shift (Solution *sol, int pos, int offset) {
  if (!localchangeable (sol, pos, offset)) return 0;

  SolutionNode *node;
  int n = offset > 0 ? offset : -offset; 

  node = sol->sol[pos];

  if (offset < 0) {
    memcpy (temp, &(sol->sol[pos + offset]), (n * sizeof (SolutionNode*)));
    memcpy (&(sol->sol[pos + offset + 1]), temp, (n * sizeof (SolutionNode*)));
  } else if (offset > 0) {
    memcpy (temp, &(sol->sol[pos + 1]), n * sizeof (SolutionNode*));
    memcpy (&(sol->sol[pos]), temp, n * sizeof (SolutionNode*));
  }

  sol->sol[pos + offset] = node;

  return 1;
}

int ls_exchange (Solution *sol, int pos, int offset) {
  if (!localchangeable (sol, pos, offset)) return 0;

  SolutionNode *node, *left, *right;
 
  node = sol->sol[pos + offset]; 
  left = node->index ? sol->node_tbl[node->seqno][node->index - 1] : NULL;
  right = node->index + 1 < node->seq->len ? sol->node_tbl[node->seqno][node->index + 1] : NULL;

  if ((offset < 0 && right && right->pos < pos) || 
      (offset > 0 && left && left->pos > pos)) 
    return 0;

  sol->sol[pos + offset] = sol->sol[pos]; sol->sol[pos] = node;

  return 1;
} 

void ls_compress (Solution *sol, int start, int end) {
  if (start >= end || start < 0 || end > sol->sol_len) return;

  SolutionNode *node;
  int *touchtable;
  int pos, sym;
  SolutionBlock *block;

  touchtable = (int*) malloc (sol->seqs * sizeof(int));
  node = sol->sol[start]; pos = start;
  while (node && pos < end) {
    memset (touchtable, 0, sol->seqs * sizeof(int));

    block = sol->block_tbl[pos];
    block->pos = pos;
    block->len = 0;

    sym = node->seq->seq[node->index];
    touchtable[node->seqno] = 1;
    
    do {
      block->len++;
      node->block = block;
      node->pos = pos;
      node = ++pos < sol->sol_len ? sol->sol[pos] : NULL;
    } while(node && pos < end &&
	    node->seq->seq[node->index] == sym && 
	    !touchtable[node->seqno]++);
  }

  free(touchtable);
}

int ls_evaluate (Solution *sol, int start, int end, int *seq) {
  if (start >= end || start < 0 || end > sol->sol_len) 
    return 0;
 
  int pos, val = 0;

  pos = start;

  while (pos < end) {
    if (seq) seq[val] = sol->sol[pos]->seq->seq[sol->sol[pos]->index];
    val++;
    pos += sol->sol[pos]->block->len;
  }

  return val;
}
