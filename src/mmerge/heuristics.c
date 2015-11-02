#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heuristics.h"
#include "mmerge.h"

#define MAX_LEN 100000

int heuristics_majority_H1(char **seq, int n, char *alphabet, int *count, int **index, int *wsum) {
  int i;
  int max = 0, maxval = -1;

  for(i = 0; i < strlen(alphabet); i++) 
    if(wsum[i] > max) {
      max = wsum[i]; maxval = i;
    }

  return maxval;
}

int heuristics_majority_H2(char **seq, int n, char *alphabet, int *count, int **index, int *wsum) {
  int i, j, idx;
  int max = 0, maxval = -1;
  int alpha_len = strlen(alphabet);
  int extra[alpha_len], extra_wsum[alpha_len];
  char ch;

  memset(extra, 0, alpha_len * sizeof(int));

  for(i = 0; i < alpha_len; i++) {
    if(!count[i]) continue;

    memcpy(extra_wsum, wsum, alpha_len * sizeof(int)); extra_wsum[i] = 0;
    for(j = 0; j < count[i]; j++) {
      idx = index[i][j];
      ch = seq[idx][1];
      if(ch != '\0') extra_wsum[(strchr(alphabet, ch) - alphabet)] += (strlen(seq[idx]) - 1); 
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

int heuristics_majority_H3(char **seq, int n, char *alphabet, int *count, int **index, int *wsum) {
  char *super;
  char **child_seq;
  int i, j, idx;
  int alpha_len = strlen(alphabet);
  int super_len[alpha_len], minlen = MAX_LEN;
  int max = -1, maxval = -1;

  child_seq = (char**)malloc(n * sizeof(char*));
  for(i = 0; i < n; i++) child_seq[i] = (char*)malloc(MAX_LEN * sizeof(char));
  super = (char*)malloc(MAX_LEN * sizeof(char));

  for(i = 0; i < alpha_len; i++) {
    if(!count[i]) continue;
    for(j = 0; j < n; j++) strcpy(child_seq[j], seq[j]);
    for(j = 0; j < count[i]; j++) ++child_seq[index[i][j]];
    strcpy(super, mmerge(child_seq, n, alphabet, heuristics_majority_H1));
    super_len[i] = strlen(super);
    if(super_len[i] < minlen) minlen = super_len[i];
  }

  for(i = 0; i < alpha_len; i++) {
    if(!count[i] || super_len[i] > minlen) continue;
    for(j = 0; j < count[i]; j++) {
      idx = index[i][j];
      strcpy(child_seq[j], seq[idx] + 1); 
    }

    strcpy(super, mmerge(child_seq, count[i], alphabet, heuristics_majority_H1));
    super_len[i] = strlen(super);
    if(super_len[i] > max) {
      max = super_len[i]; maxval = i;
    }
  }
 
  return maxval;
}
