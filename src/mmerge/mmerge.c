#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mmerge.h"

int mmerge(Sequence **seq, int n, int *alphabet, int alpha_len, int (*majority)(Sequence **, int, int *, int, int *, int **, int *), int *super) {
  int* count;
  int** index;
  int* wsum;
  int i, j, k, m; 
  int nextval;
  int len = 0;

  index = (int**) malloc (alpha_len * sizeof(int*));
  for(i = 0; i < alpha_len; i++) index[i] = (int*)malloc(n * sizeof(int));

  count = (int*) malloc (alpha_len * sizeof(int));
  memset(count, 0, alpha_len * sizeof(int));

  wsum = (int*) malloc (alpha_len * sizeof(int));
  memset(wsum, 0, alpha_len * sizeof(int));

  for(i = 0; i < n; i++) {
    if(seq[i]->offset < seq[i]->len) {
      j = get_serial (seq[i]->seq[seq[i]->offset], alphabet, alpha_len);
      index[j][count[j]] = i;
      count[j]++;
      wsum[j] += (seq[i]->len - seq[i]->offset);
    }
  } 

  while(1) {
    nextval = majority(seq, n, alphabet, alpha_len, count, index, wsum);
    if(nextval == -1) break;
    super[len++] = alphabet[nextval];
    m = count[nextval]; 

    count[nextval] = 0; wsum[nextval] = 0;
    for(i = 0; i < m; i++) {
      j = index[nextval][i];
      if(++seq[j]->offset < seq[j]->len) {
        k = get_serial (seq[j]->seq[seq[j]->offset], alphabet, alpha_len);
        index[k][count[k]++] = j;
        wsum[k] += (seq[j]->len - seq[j]->offset); 
      }
    }
  }
     
  return len;
}
