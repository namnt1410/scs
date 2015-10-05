#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mmerge.h"

#define MAX_LEN 1000

char* mmerge(char **seq, int n, char *alphabet, int (*majority)(char **, int, char *, int *, int **, int *)) {
  int count[strlen(alphabet)];
  int *index[strlen(alphabet)];
  int wsum[strlen(alphabet)];
  int i, j, k, m; 
  int nextval;
  int len = 0;
  char ch;
  char *out;

  out = malloc(MAX_LEN * sizeof(char));
  for(i = 0; i < sizeof(alphabet); i++) index[i] = (int*)malloc(n * sizeof(int));
  memset(count, 0, sizeof(count));
  memset(wsum, 0, sizeof(wsum));

  for(i = 0; i < n; i++) {
    if(seq[i][0]) {
      j = strchr(alphabet, seq[i][0]) - alphabet;
      index[j][count[j]] = i;
      count[j]++;
      wsum[j] += strlen(seq[i]);
    }
  } 

  while(1) {
    nextval = majority(seq, n, alphabet, count, index, wsum);
    if(nextval == -1) break;

    out[len++] = alphabet[nextval];
    m = count[nextval]; 

    count[nextval] = 0; wsum[nextval] = 0;
    for(i = 0; i < m; i++) {
      j = index[nextval][i];
      ch = *(++seq[j]);
      if(ch != '\0') {
        k = strchr(alphabet, ch) - alphabet;
        index[k][count[k]++] = j;
        wsum[k] += strlen(seq[j]); 
      }
    }
  }

  out[len] = '\0';
     
  return out;
}
