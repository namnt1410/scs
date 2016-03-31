#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scs.h"

int scs_alpha (SequenceList list, int *super) {
  int i, max_len = 0;
  Sequence *seq;
  int alphabet[MAX_ALPHABET_SIZE], alpha_len;

  alpha_len = get_alphabet_set (list, alphabet); 

  seq = list;
  while(seq != NULL) {
    if(seq->len > max_len) max_len = seq->len;
    seq = seq->next;
  }

  for(i = 0; i < max_len; i++) memcpy (super + i * alpha_len, alphabet, alpha_len * sizeof(int)); 

  return (max_len * alpha_len);
}

int scs_alpha_leftmost (SequenceList list, int *super) {
  Sequence *node;
  Sequence **seq;
  int *count;
  int **index;
  int i, j, k, l, m, n; 
  int len = 0, nseq;
  int sym;
  int alphabet[MAX_ALPHABET_SIZE], alpha_len; 

  alpha_len = get_alphabet_set (list, alphabet);
  n = get_size (list);

  index = (int **) malloc (alpha_len * sizeof(int *));
  for(i = 0; i < alpha_len; i++) index[i] = (int *) calloc(n, sizeof(int));
  count = (int *) calloc (alpha_len, sizeof(int));

  seq = (Sequence **) malloc (n * sizeof(Sequence*));

  node = list; i = 0; 
  while(node) {
    seq[i++] = create_sequence (node->seq, node->len);
    node = node->next;
  }

  nseq = n;
  for(i = 0; i < n; i++) {
    if(seq[i]->offset < seq[i]->len) {
      sym = seq[i]->seq[seq[i]->offset];
      j = get_serial (sym, alphabet, alpha_len);
      index[j][count[j]++] = i;
    } else nseq--;
  } 

  i = 0;
  while (nseq) {
    super[len++] = alphabet[i];
    m = count[i]; count[i] = 0;
    for(j = 0; j < m; j++) {
      k = index[i][j];
      if(++seq[k]->offset < seq[k]->len) {
        sym = seq[k]->seq[seq[k]->offset];
        l = get_serial (sym, alphabet, alpha_len);
        index[l][count[l]++] = k;
      } else nseq--;
    }

    i = (i + 1) % alpha_len; 
  }

  return len;
}

