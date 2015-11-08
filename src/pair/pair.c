#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pair.h"

int min(int x, int y) {
  return x < y ? x : y;
}

int scs_pair(int *seq1, int len1, int *seq2, int len2, int *super) {
  int i, j, len;

  link_t*  lp;
  link_t** lnk;

  lnk = (link_t**) malloc ((len2 + 1) * sizeof(link_t*));
  for(i = 0; i < len2 + 1; i++) lnk[i] = (link_t*) malloc ((len1 + 1) * sizeof(link_t));

  for(i = 0; i < len2; i++) lnk[i][len1] = (link_t){len2 - i, seq2[i], &lnk[i + 1][len1]};
  for(i = 0; i < len1; i++) lnk[len2][i] = (link_t){len1 - i , seq1[i], &lnk[len2][i + 1]};
  
  lnk[len2][len1] = (link_t) {0};

  for(i = len2 - 1; i >= 0; i--) 
    for(j = len1 - 1; j >= 0; j--) {
      lp = &lnk[i][j];
      if(seq2[i] == seq1[j]) {
	lp->next = &lnk[i + 1][j + 1];
	lp->sym = seq1[j];
      } else if(lnk[i][j + 1].len < lnk[i + 1][j].len ) {
	lp->next = &lnk[i][j + 1];
	lp->sym = seq1[j];
      } else {
	lp->next = &lnk[i + 1][j];
	lp->sym = seq2[i];
      }
      lp->len = lp->next->len + 1; 
    }  

  len = 0;
  for(lp = &lnk[0][0]; lp != &lnk[len2][len1]; lp = lp->next)
    super[len++] = lp->sym;

  /* for (i = 0; i < len2 + 1; i++) free(lnk[i]);
  free(lnk); */

  return len;
}
