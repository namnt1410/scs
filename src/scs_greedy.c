#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scs.h"
#include "pair/pair.h"

int scs_greedy(SequenceList list, int *super) {
  Sequence *node;
  Sequence **seq;
  Sequence *seq1, *seq2;

  int **super_len, len;
  int out[MAX_LEN];
  int i, j;
  int n;
  int min, ix, iy;
  
  n = get_size(list);

  seq = (Sequence**)malloc(n * sizeof(Sequence*));
  super_len = (int**)malloc(n * sizeof(int*));
  for(i = 0; i < n; i++) super_len[i] = (int*)malloc(n * sizeof(int));

  i = 0; node = list;
  while(node) {
    seq[i++] = create_sequence(node->seq, node->len); 
    node = node->next; 
  }

  for(i = 0; i < n; i++) 
    for(j = 0; j < i; j++) super_len[i][j] = scs_pair(seq[i]->seq, seq[i]->len, seq[j]->seq, seq[j]->len, NULL);
    
  while(n > 1) { 
    min = MAX_LEN;
    for(i = 0; i < n; i++)
      for(j = 0; j < i; j++) {  
        if(super_len[i][j] < min) {
          min = super_len[i][j];
          ix = i; iy = j;
        }
      }

    seq1 = seq[ix]; seq2 = seq[iy];

    if(iy == n - 2) {
      seq[ix] = seq[n - 1];
      for(i = 0; i < ix; i++) super_len[ix][i] = super_len[n - 1][i];
    } else {
      seq[ix] = seq[n - 2]; 
      seq[iy] = seq[n - 1];
      for(i = 0; i < ix; i++) super_len[ix][i] = super_len[n - 2][i];
      for(i = 0; i < iy; i++) super_len[iy][i] = super_len[n - 1][i];
    } 

    len = scs_pair(seq1->seq, seq1->len, seq2->seq, seq2->len, out);

    seq[n - 2] = create_sequence(out, len);

    for(i = 0; i < n - 2; i++) 
      super_len[n - 2][i] = scs_pair(seq[n - 2]->seq, seq[n - 2]->len, seq[i]->seq, seq[i]->len, NULL);

    n--;
  } 

  len = seq[0]->len;
  memcpy(super, seq[0]->seq, len * sizeof(int));

  /* for(i = 0; i < get_size(list); i++) {
    free(seq[i]);
    free(super_len[i]);
  }

  free(seq); 
  free(super_len);*/ 

  return len;
}
