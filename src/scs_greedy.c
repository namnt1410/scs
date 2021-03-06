#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scs.h"
#include "pair/pair.h"

int min_elem (int *a, int n) {
  if (n <= 0) return -1;

  int i;
  int index = 0;
  int min = a[0]; 

  for(i = 1; i < n; i++) {
    if (a[i] < min) {
      min = a[i];
      index = i;
    } 
  }

  return index;
}

int scs_greedy(SequenceList list, int *super) {
  Sequence *node;
  Sequence **seq;
  Sequence *seq1, *seq2;

  int **super_len, len;
  int out[MAX_LEN];
  int i, j;
  int n;
  int *index;
  int min, ix, iy;
  
  n = get_size(list);

  seq = (Sequence**) malloc (n * sizeof(Sequence*));
  super_len = (int**) malloc (n * sizeof(int*));
  for(i = 0; i < n; i++) super_len[i] = (int*) malloc (n * sizeof(int));
  index = (int *) malloc (n * sizeof(int));

  i = 0; node = list;
  while(node) {
    seq[i++] = create_sequence(node->seq, node->len); 
    node = node->next; 
  }

  for(i = 0; i < n; i++) {
    index[i] = -1;
    for(j = 0; j < i; j++) {
      super_len[i][j] = scs_pair(seq[i]->seq, seq[i]->len, seq[j]->seq, seq[j]->len, NULL);
      if (index[i] == -1 || super_len[i][j] < super_len[i][index[i]]) index[i] = j;
    }
  }  
    
  while(n > 1) { 
    min = MAX_LEN;
    for(i = 0; i < n; i++)
      if (super_len[i][index[i]] < min) {
        ix = i; iy = index[i]; 
      } 

    seq1 = seq[ix]; seq2 = seq[iy];

    if(iy == n - 2) {
      seq[ix] = seq[n - 1];
      memcpy (&(super_len[ix][0]), &(super_len[n - 1][0]), ix * sizeof(int)); 
      index[ix] = index[n - 1] < ix ? index[n - 1] : min_elem (&(super_len[ix][0]), ix);
    } else {
      seq[ix] = seq[n - 2]; 
      seq[iy] = seq[n - 1];
      memcpy (&(super_len[ix][0]), &(super_len[n - 2][0]), ix * sizeof(int));
      index[ix] = index[n - 2] < ix ? index[n - 2] : min_elem (&(super_len[ix][0]), ix);
      memcpy (&(super_len[iy][0]), &(super_len[n - 1][0]), iy * sizeof(int));
      index[iy] = index[n - 1] < iy ? index[n - 1] : min_elem (&(super_len[iy][0]), iy);
    } 

    len = scs_pair(seq1->seq, seq1->len, seq2->seq, seq2->len, out);

    seq[n - 2] = create_sequence(out, len);

    for(i = 0; i < n - 2; i++) {
      super_len[n - 2][i] = scs_pair(seq[n - 2]->seq, seq[n - 2]->len, seq[i]->seq, seq[i]->len, NULL); 
    }
    index[n - 2] = min_elem (&(super_len[n - 2][0]), n - 2);

    n--;
  } 

  len = seq[0]->len;
  memcpy(super, seq[0]->seq, len * sizeof(int));

  return len;
}
