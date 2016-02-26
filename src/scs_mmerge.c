#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scs.h"
#include "mmerge/mmerge.h"
#include "mmerge/heuristics.h"

int scs_mmerge(SequenceList list, int *super) {
  Sequence *node;
  Sequence **seq;
  int n; 
  int i;
  int alphabet[MAX_ALPHABET_SIZE], alpha_len; 

  alpha_len = get_alphabet_set(list, alphabet);
  n = get_size(list);

  seq = (Sequence**) malloc (n * sizeof(Sequence*));

  node = list; i = 0; 
  while(node) {
    seq[i++] = create_sequence (node->seq, node->len);
    node = node->next;
  }

  return mmerge(seq, n, alphabet, alpha_len, MM_MAJORITY, super);
}
