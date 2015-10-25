#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scs.h"
#include "mmerge/mmerge.h"
#include "mmerge/heuristics.h"

int def_majority(char **seq, int n, char *alphabet, int *count, int **index, int *wsum) {
  int i;
  int max = 0, maxval = -1;

  for(i = 0; i < strlen(alphabet); i++) 
    if(count[i] > max) {
      max = count[i]; maxval = i;
    }

  return maxval;
}

char* scs_mmerge(SequenceList list, char* alphabet) {
  Sequence *node;
  char **seq;
  int n; 
  int i; 

  n = get_size(list);

  seq = (char**)malloc(n * sizeof(char*));

  node = list; i = 0; 
  while(node) {
    seq[i++] = strdup(node->seq);
    node = node->next;
  }

  return mmerge(seq, n, alphabet, heuristics_majority_H3);
}
