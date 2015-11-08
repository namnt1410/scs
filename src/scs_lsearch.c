#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sequence.h"
#include "lsearch/lsearch.h"

int scs_lsearch (SequenceList list, int *super) {
  Solution *sol;

  sol = lsearch(list); 
  int val = ls_evaluate (sol, super);

  printf("val: %d\n", val);
  printf("check: %d\n", check_common_supersequence(list, super, val));

  return val;
}






