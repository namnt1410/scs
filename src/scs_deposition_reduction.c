#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "scs.h"

int scs_deposition_reduction(SequenceList list, int *super, int (*scs)(SequenceList , int *)) {
  Sequence* seq;
  SequenceList left;  
  int temp[MAX_LEN], better;
  int len, left_len;
  int i, j;

  len = scs (list, super);

  left = NULL; seq = list;
  while (seq) {
    add_sequence (&left, seq->seq, seq->len);
    seq = seq->next;
  }

  do {
    better = 0; 
    seq = left;
    while (seq) {
      seq->len = 0; seq = seq->next;
    } 

    for (i = 1; i < len; i++) {
      seq = left; j = 0;
      while (seq) {
        if (seq->seq[seq->len] == super[i - 1]) {
          seq->len++; 
        }
        seq = seq->next; j++;
      } 

      left_len = scs_mmerge_H1 (left, temp);
      if (left_len < i) {
        better = 1;
        memcpy (temp + left_len, super + i, (len - i) * sizeof(int));
        len = left_len + len - i;
        memcpy (super, temp, len * sizeof(int));
        break;          
      }
    }
  } while (better);
  
  return len;
}
