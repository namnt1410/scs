#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heuristics.h"
#include "mmerge.h"

#define MAX_LEN 100000

int heuristics_majority_H1(Sequence **seq, int n, int *alphabet, int alpha_len, int *count, int **index, int *wsum) {
  int i;
  int max = 0, maxval = -1;

  for(i = 0; i < alpha_len; i++) 
    if(wsum[i] > max) {
      max = wsum[i]; maxval = i;
    }

  return maxval;
}

int heuristics_majority_H2(Sequence **seq, int n, int *alphabet, int alpha_len, int *count, int **index, int *wsum) {
  Sequence *tmp;
  int i, j;
  int max = 0, maxval = -1;
  int *extra, *extra_wsum;

  extra = (int*) calloc (alpha_len, sizeof(int));
  extra_wsum = (int*) malloc (alpha_len * sizeof(int));

  for(i = 0; i < alpha_len; i++) {
    if(!count[i]) continue;

    memcpy(extra_wsum, wsum, alpha_len * sizeof(int)); 
    extra_wsum[i] = 0;
    for(j = 0; j < count[i]; j++) {
      tmp = seq[index[i][j]];
      if((tmp->offset + 1) < tmp->len) extra_wsum[tmp->seq[tmp->offset + 1]] += (tmp->len - tmp->offset - 1); 
    }

    for(j = 0; j < alpha_len; j++)
      if(extra_wsum[j] > extra[i]) extra[i] = extra_wsum[j];
  }

  
  for(i = 0; i < alpha_len; i++)  
    if(count[i] && (wsum[i] + extra[i]) > max) {
      max = wsum[i] + extra[i]; maxval = i;
    }
 
  return maxval;
}

int heuristics_majority_H3(Sequence **seq, int n, int *alphabet, int alpha_len, int *count, int **index, int *wsum) {
  Sequence **child_seq;
  int *super;
  int i, j, idx;
  int super_len[alpha_len], minlen = MAX_LEN;
  int max = -1, maxval = -1;

  super = (int*) malloc (MAX_LEN * sizeof(int));
  child_seq = (Sequence**) malloc (n * sizeof(Sequence*));
  for(i = 0; i < n; i++) child_seq[i] = (Sequence*) malloc (sizeof(Sequence));

  for(i = 0; i < alpha_len; i++) {
    if(!count[i]) continue;
    for(j = 0; j < n; j++) memcpy(child_seq[j], seq[j], sizeof(Sequence));
    for(j = 0; j < count[i]; j++) child_seq[index[i][j]]->offset++;
    super_len[i] = mmerge(child_seq, n, alphabet, alpha_len, heuristics_majority_H1, super);
    if(super_len[i] < minlen) minlen = super_len[i];
  }

  for(i = 0; i < alpha_len; i++) {
    if(!count[i] || super_len[i] > minlen) continue;
    for(j = 0; j < count[i]; j++) {
      idx = index[i][j];
      memcpy(child_seq[j], seq[idx], sizeof(Sequence));
      child_seq[j]->offset++; 
    }

    super_len[i] = mmerge(child_seq, count[i], alphabet, alpha_len, heuristics_majority_H1, super);
    if(super_len[i] > max) {
      max = super_len[i]; maxval = i;
    }
  }

  free (super);
 
  return maxval;
}
