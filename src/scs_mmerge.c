#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scs.h"
#include "mmerge/mmerge.h"
#include "mmerge/heuristics.h"

int def_majority(Sequence **seq, int n, int *alphabet, int alpha_len, int *count, int **index, int *wsum) {
  int i;
  int max = 0, maxval = -1;

  for(i = 0; i < alpha_len; i++) 
    if(count[i] > max) {
      max = count[i]; maxval = i;
    }

  return maxval;
}

int scs_mmerge(SequenceList list, int *alphabet, int alpha_len, int *super) {
  Sequence *node;
  Sequence **seq;
  int n; 
  int i; 

  n = get_size(list);

  seq = (Sequence**) malloc (n * sizeof(Sequence*));

  node = list; i = 0; 
  while(node) {
    seq[i++] = create_sequence (node->seq, node->len);
    node = node->next;
  }

  return mmerge(seq, n, alphabet, alpha_len, def_majority, super);
}
