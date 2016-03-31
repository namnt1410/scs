#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sequence.h"
#include "lsearch/lsearch.h"

int scs_lsearch (SequenceList list, int *super) {
  Solution *sol;

  sol = lsearch(list); 
  int val = ls_evaluate (sol, 0, sol->sol_len, super);

  return val;
}






