#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lsearch.h"

Solution *ls_init(SequenceList list);
int ls_neighborhood (SolutionNode *node, int *offsetmin, int *offsetmax);
int ls_localchange (SolutionNode *node, int offset, int change_type);
int ls_shift (SolutionNode *node, int offset);
int ls_exchange (SolutionNode *node, int offset);

Solution *ls_init(SequenceList list) {
  Solution *sol;
  SolutionNode *node;
  Sequence *seq;
  int seqno, i;
  int count;

  sol = (Solution*) malloc (sizeof(Solution));

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
      node->sol = sol;
      
      if(i > 0) {
        node->left_nbr = sol->node_tbl[seqno][i - 1];
        node->left_nbr->right_nbr = node;
      } else node->left_nbr = NULL;
      
      node->right_nbr = NULL;
      node->prev = NULL; node->next = NULL;
    }

    seq = seq->next; seqno++; 
  } 

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
	  ls_neighborhood (node, &offsetmin, &offsetmax);
	  offset = offsetmin;
          //printf("offset: %d %d\n", offsetmin, offsetmax);
	  while (offset <= offsetmax) {
	    if (offset != 0 && ls_exchange (node, offset)) {
	      val = ls_evaluate (sol, super);

              //printf("val: %d\n", val);

	      if (val < min) {
		min = val;
		best_offset = offset;
	      }
            
	      ls_exchange (node, -offset);
	    }
	    offset++;
	  }

	  if (min < best) {
	    ls_exchange (node, best_offset);
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

  // printf("loop: %d\n", m);
  free(super);

  return sol;
}

int ls_neighborhood (SolutionNode *node, int *offsetmin, int *offsetmax) {
  if (!node) return 0;

  SolutionNode *left, *right;

  *offsetmin = 0;
  *offsetmax = 0;

  left = node->prev;
  
  while (left && left != node->left_nbr) {
    (*offsetmin)--;
    left = left->prev;
  }

  right = node->next;

  while (right && right != node->right_nbr) {
    (*offsetmax)++;
    right = right->next;
  }

  return 1;
} 

int ls_localchange (SolutionNode *node, int offset, int change_type) {
  if (change_type == LOCALCHANGE_TYPE_SHIFT) {
    return ls_shift (node, offset);
  } else if (change_type == LOCALCHANGE_TYPE_EXCHANGE) {
    return ls_exchange (node, offset);
  }

  return 0;
}

int ls_shift (SolutionNode *node, int offset) {
  if (offset == 0 || node->pos + offset < 0 || node->pos + offset >= node->sol->sol_len) return 0;

  SolutionNode *victim, *prev, *next;
  int i;

  prev = node->prev; next = node->next;
 
  victim = node;

  if (offset < 0) {
    for (i = 0; i > offset; i--) { 
      victim = victim->prev; victim->pos++;
    }
    node->prev = victim->prev;
    node->next = victim;
  } else if (offset > 0) {
    for (i = 0; i < offset; i++) {
      victim = victim->next; victim->pos--;
    }
    node->prev = victim;
    node->next = victim->next;
  }

  node->pos = node->pos + offset;

  if (prev) prev->next = next;
  else node->sol->first = next;
  if (next) next->prev = prev;
  else node->sol->last = prev;

  if(node->prev) node->prev->next = node;
  else node->sol->first = node; 
  if(node->next) node->next->prev = node;
  else node->sol->last = node;

  return 1;
}

int ls_exchange (SolutionNode *node, int offset) {
  //printf("1111\n");
  if (offset == 0 || node->pos + offset < 0 || node->pos + offset >= node->sol->sol_len) return 0;

  SolutionNode *victim;
  SolutionNode *left, *right, *prev, *next;
  int i, temp;
 
  victim = node;

  if (offset < 0) {
    for (i = 0; i > offset; i--) 
      victim = victim->prev;
    if (victim->right_nbr && victim->right_nbr->pos < node->pos) return 0;
    left = victim; right = node;
  } else if (offset > 0) {
    for (i = 0; i < offset; i++) 
      victim = victim->next;
    if (victim->left_nbr && victim->left_nbr->pos > node->pos) return 0;
    left = node; right = victim; 
  }

  //printf ("3333\n");

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

  if (left == left->sol->first) left->sol->first = right;
  if (right == right->sol->last) right->sol->last = left;

  temp = left->pos; left->pos = right->pos; right->pos = temp;

  //printf ("2222\n");

  return 1;
  
} 

int ls_evaluate (Solution *sol, int *seq) {
  SolutionNode *node;
  int val = 0;
  int *touchtable;
  int sym;
  
  touchtable = (int*) malloc (sol->seqs * sizeof(int));
  node = sol->first;
  while(node) {
    memset (touchtable, 0, sol->seqs * sizeof(int));
    sym = node->seq->seq[node->index];
    seq[val++] = sym;
    touchtable[node->seqno] = 1;
    
    do {
      node = node->next;
    } while(node && node->seq->seq[node->index] == sym && !touchtable[node->seqno]++);
  }

  free(touchtable);

  return val;
}
