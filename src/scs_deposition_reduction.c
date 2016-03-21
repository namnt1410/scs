#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "scs.h"

int scs_deposition_reduction(SequenceList list, int *super, int (*scs)(SequenceList , int *)) {
  Sequence *seq, *temp;
  SequenceList tmp;  
  int left[MAX_LEN], right[MAX_LEN], better;
  int len, left_len, right_len;
  int i, j;

  len = scs (list, super);

  tmp = NULL; seq = list;
  while (seq) {
    add_sequence (&tmp, seq->seq, seq->len);
    seq = seq->next;
  }

  do {
    better = 0; 
    seq = tmp;
    while (seq) {
      seq->len = 0; seq = seq->next;
    } 

    for (i = 1; i < len; i++) {
      right_len = len - i;
      memcpy (right, super + i, right_len * sizeof(int));
 
      temp = tmp; seq = list; j = 0;
      while (seq) {
        if (seq->seq[temp->len] == super[i - 1]) {
          if (!check_supersequence (seq->seq + temp->len, seq->len - temp->len, right, right_len)) temp->len++; 
        }
        seq = seq->next; temp = temp->next; j++;
      } 

      left_len = scs_mmerge_H1 (tmp, left);
      if (left_len < i) {
        better = 1;
        memcpy (super + left_len, right, right_len * sizeof(int));
        len = left_len + right_len;
        memcpy (super, left, left_len * sizeof(int));
        break;          
      }
    }
  } while (better);
  
  return len;
}
