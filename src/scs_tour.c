#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scs.h"
#include "pair/pair.h"

int scs_tour(SequenceList list, int *super) {
  Sequence *node;
  Sequence **seq;

  int len;
  int out[MAX_LEN];
  int i, j;
  int m, n;
  int min, minp;
  int *lock;
  
  n = get_size(list);

  seq = (Sequence **) malloc (n * sizeof(Sequence *));
  lock = (int *) malloc (n * sizeof(int));

  i = 0; node = list;
  while(node) {
    seq[i++] = create_sequence(node->seq, node->len); 
    node = node->next; 
  }
    
  while(n > 1) { 
    memset (lock, 0, n * sizeof(int));
    m = 0;

    for (i = 0; i < n; i++) {
      if (!lock[i]) {
        lock[i] = 1;
        min = MAX_LEN; minp = i;

        for (j = i + 1; j < n; j++) {
          if (!lock[j]) {
            len = scs_pair(seq[i]->seq, seq[i]->len, seq[j]->seq, seq[j]->len, NULL);

            if (len < min) {
              min = len;
              minp = j;
            }
          }
        }

        if (minp != i) {
          lock[minp] = 1;
          len = scs_pair(seq[i]->seq, seq[i]->len, seq[minp]->seq, seq[minp]->len, out);
          seq[m] = create_sequence (out, len);
          //memcpy (seq[m]->seq, out, len * sizeof(int));
          //seq[m]->len = len;
        } else seq[m] = seq[i];

        m++; 
      }
    }

    n = m;
  } 

  len = seq[0]->len;
  memcpy(super, seq[0]->seq, len * sizeof(int));

  return len;
}
