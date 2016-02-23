#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "scs.h"
#include "RE/reduce_expand.h"

int scs_reduce_expand(SequenceList list, int *super, int (*scs)(SequenceList , int *)) {
  int m;
  int len;
  int aux_seq[MAX_LEN], aux_len;
  SequenceList *rlist;

  rlist = reduce (list, &m);
  aux_len = scs (rlist[0], aux_seq);

  len = expand (rlist, m, aux_seq, aux_len, super);

  return len;
}
