#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"

typedef struct SolutionNode {
  char letter;
  int seqno;
  int index;
  Sequence *seq;
  struct SolutionNode *left_nbr, *right_nbr;
  struct SolutionNode *prev, *next;
} SolutionNode;

typedef struct Solution {
  SolutionNode *first;
  SolutionNode *last;
  SolutionNode ***node_tbl;
  int sol_len;
} Solution;

Solution *ls_init(SequenceList list) {
  Solution *sol;
  SolutionNode *node;
  Sequence *seq;
  int n;
  int seqno, i;
  int count;

  n = get_size(list); 

  sol = (Solution*) malloc (sizeof(Solution));
  sol->first = NULL;
  sol->last = NULL;
  sol->node_tbl = (SolutionNode ***) malloc (sizeof(SolutionNode **) * n);

  seq = list; seqno = 0;
  sol->sol_len = 0;
  while (seq) {
    sol->sol_len += seq->len;
    sol->node_tbl[seqno] = (SolutionNode **) malloc (sizeof(SolutionNode *) * seq->len);
    for(i = 0; i < seq->len; i++) {
      node  = (SolutionNode *) malloc (sizeof(SolutionNode));
      sol->node_tbl[seqno][i] = node;
 
      node->letter = seq->seq[i];
      node->seqno = seqno;
      node->index = i;
      node->seq = seq;
      
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

/* Solution *lsearch (SequenceList list) {
}

int ls_victim (SolutionNode *node, SolutionNode *victim) {
  return 1;
}

int ls_insert (SolutionNode *node, SolutionNode *victim) {
  if(
  return 1;
}*/

int ls_evaluate (Solution *sol, char *seq) {
  SolutionNode *node;
  int val = 0;
  int seqno;
  char c;
  
  node = sol->first;
  while(node) {
    seqno = node->seqno;
    c = node->letter;
    seq[val++] = c;
    
    do {
      node = node->next;
    } while(node && node->seqno != seqno && node->letter == c);   
  }
  seq[val] = '\0';

  return val;
}

char *scs_lsearch (SequenceList list, char *alphabet) {
  Solution *sol;
  char *seq;

  sol = ls_init(list); 

  seq = (char*) malloc (sol->sol_len * sizeof(char));
  int val = ls_evaluate (sol, seq);

  return seq;
}






