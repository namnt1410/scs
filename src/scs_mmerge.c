#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scs.h"
#include "mmerge/mmerge.h"

int mmerge_process (SequenceList list, int *super, int (*majority)(Sequence **, int, int *, int, int *, int **, int *)) {
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

  return mmerge(seq, n, alphabet, alpha_len, majority, super);
}

int scs_mmerge_H0(SequenceList list, int *super) {
  return mmerge_process (list, super, MM_MAJORITY_H0);
}

int scs_mmerge_H1(SequenceList list, int *super) {
  return mmerge_process (list, super, MM_MAJORITY_H1);
}

int scs_mmerge_H2(SequenceList list, int *super) {
  return mmerge_process (list, super, MM_MAJORITY_H2);
}

int scs_mmerge_H3(SequenceList list, int *super) {
  return mmerge_process (list, super, MM_MAJORITY_H3);
}
