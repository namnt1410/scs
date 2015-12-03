#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sequence.h"
#include "lsearch/lsearch.h"

int scs_lsearch (SequenceList list, int *super) {
  Solution *sol;
  SolutionNode *node;
  int i, pos = -1; 

  sol = lsearch(list); 
  int val = ls_evaluate (sol, 0, sol->sol_len - 1, super);

  /*node = sol->first;
  while (node) {
    if (node->pos < pos) printf("valid: 0\n");   
    pos = node->pos; node = node->next;
  }*/

  printf("val: %d\n", val);
  printf("check: %d\n", check_common_supersequence(list, super, val));

  return val;
}






