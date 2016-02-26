#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scs.h"

int scs_alpha(SequenceList list, int *super) {
  int i, max_len = 0;
  Sequence *seq;
  int alphabet[MAX_ALPHABET_SIZE], alpha_len;

  alpha_len = get_alphabet_set(list, alphabet); 

  seq = list;
  while(seq != NULL) {
    if(seq->len > max_len) max_len = seq->len;
    seq = seq->next;
  }

  for(i = 0; i < max_len; i++) memcpy (super + i * alpha_len, alphabet, alpha_len * sizeof(int)); 

  return (max_len * alpha_len);
}

