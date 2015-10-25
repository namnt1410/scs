#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scs.h"
#include "pair/pair.h"

char* scs_greedy(SequenceList list, char* alphabet) {
  Sequence *node;
  char **seq;
  int **len;
  char tmp[MAX_SEQUENCE_LEN];
  int i, j;
  int n;
  int min, ix, iy;
  char x[MAX_SEQUENCE_LEN], y[MAX_SEQUENCE_LEN];
  
  n = get_size(list);

  seq = (char**)malloc(n * sizeof(char*));
  len = (int**)malloc(n * sizeof(int*));
  for(i = 0; i < n; i++) len[i] = (int*)malloc(n * sizeof(int)); 

  i = 0; node = list;
  while(node) {
    seq[i++] = strdup(node->seq); 
    node = node->next;
  }

  for(i = 0; i < n; i++)
    for(j = 0; j < i; j++) len[i][j] = scs_pair(seq[i], seq[j], tmp);
    
  while(n > 1) { 
    min = MAX_SEQUENCE_LEN;
    for(i = 0; i < n; i++)
      for(j = 0; j < i; j++) {  
        if(len[i][j] < min) {
          min = len[i][j];
          ix = j; iy = i;
        }
      }

    strcpy(x, seq[ix]); strcpy(y, seq[iy]);

    if(iy == n - 2) {
      strcpy(seq[ix], seq[n - 1]);
      for(i = 0; i < ix; i++) len[ix][i] = len[n - 1][i];
    } else {
      strcpy(seq[ix], seq[n - 2]); 
      strcpy(seq[iy], seq[n - 1]);
      for(i = 0; i < ix; i++) len[ix][i] = len[n - 2][i];
      for(i = 0; i < iy; i++) len[iy][i] = len[n - 1][i];
    } 

    scs_pair(x, y, tmp);

    strcpy(seq[n - 2], tmp);

    for(i = 0; i < n - 2; i++) 
      len[n - 2][i] = scs_pair(seq[n - 2], seq[i], tmp);

    n--;
  }

  return seq[0];
}
