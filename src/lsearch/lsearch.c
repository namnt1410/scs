#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lsearch.h"

Solution *ls_init(SequenceList list);
int ls_neighborhood (SolutionNode *node, int *offsetmin, int *offsetmax);
int ls_shift (SolutionNode *node, int offset);

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
          sol->first = node;
          sol->last = node;
        } else {
          node->prev = sol->last;
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
  char *super;
  int val, min, best, better;
  int offsetmin, offsetmax;
  int offset, best_offset;
  int i, count, seqno, m = 0;  

  sol = ls_init(list);
  super = (char*) malloc (sol->sol_len * sizeof(char));
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
	    if (offset != 0 && ls_shift (node, offset)) {
	      val = ls_evaluate (sol, super);

              //printf("val: %d\n", val);

	      if (val < min) {
		min = val;
		best_offset = offset;
	      }
            
	      ls_shift (node, -offset);
	    }
	    offset++;
	  }

	  if (min < best) {
	    ls_shift (node, best_offset);
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

  printf("loop: %d\n", m);

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

int ls_shift (SolutionNode *node, int offset) {
  if (offset == 0) return 0;

  SolutionNode *victim, *prev, *next;
  int i;

  prev = node->prev; next = node->next;
 
  victim = node;

  if (offset < 0) {
    for (i = 0; i > offset && victim; i--) 
      victim = victim->prev;

    if (i > offset) return 0;
    
    node->prev = victim->prev;
    node->next = victim;
  } else if (offset > 0) {
    for (i = 0; i < offset && victim; i++)
      victim = victim->next;

    if (i < offset) return 0;

    node->prev = victim;
    node->next = victim->next;
  }

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

int ls_evaluate (Solution *sol, char *seq) {
  SolutionNode *node;
  int val = 0;
  int *touchtable;
  char c;
  
  touchtable = (int*) malloc (sol->seqs * sizeof(int));
  node = sol->first;
  while(node) {
    memset (touchtable, 0, sol->seqs * sizeof(int));
    c = node->seq->seq[node->index];
    seq[val++] = c;
    touchtable[node->seqno] = 1;
    
    do {
      node = node->next;
    } while(node && node->seq->seq[node->index] == c && !touchtable[node->seqno]++);
  }
  seq[val] = '\0';
  free(touchtable);

  return val;
}
