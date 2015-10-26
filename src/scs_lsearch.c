#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sequence.h"
#include "lsearch/lsearch.h"

char *scs_lsearch (SequenceList list, char *alphabet) {
  Solution *sol;
  char *seq;

  sol = lsearch(list); 
  seq = (char*) malloc (sol->sol_len * sizeof(char));
  // ls_evaluate (sol, NULL);
  int val = ls_evaluate (sol, seq);

  printf("val: %d\n", val);
  printf("check: %d\n", check_common_supersequence(list, seq));

  return seq;
}






