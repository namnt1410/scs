#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scs.h"
#include "pair/pair.h"

char* scs_greedy(SequenceList list, char* alphabet) {
  Sequence *node;
  char** seq;
  char *out;
  int** len;
  char tmp[MAX_LEN + 1];
  int i, j;
  int n;
  int min, ix, iy;
  char x[MAX_LEN + 1], y[MAX_LEN + 1];
  
  n = get_size(list);

  seq = (char**)malloc(n * sizeof(char*));
  len = (int**)malloc(n * sizeof(int*));
  for(i = 0; i < n; i++) len[i] = (int*)malloc(n * sizeof(int));

  i = 0; node = list;
  while(node) {
    seq[i] = (char*) malloc (MAX_LEN * sizeof(char)); 
    strcpy(seq[i], node->seq); 
    node = node->next; i++;
  }

  for(i = 0; i < n; i++)
    for(j = 0; j < i; j++) {
      len[i][j] = scs_pair(seq[i], seq[j], tmp);
    }
    
  while(n > 1) { 
    min = MAX_LEN;
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

  out = strdup(seq[0]); 

  for(i = 0; i < get_size(list); i++) {
    free(seq[i]);
    free(len[i]);
  }

  free(seq); 
  free(len); 

  return out;
}
