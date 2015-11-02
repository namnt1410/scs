#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pair.h"

int min(int x, int y) {
  return x < y ? x : y;
}

int scs_pair(char* x, char* y, char* out) {
  int lx = strlen(x), ly = strlen(y);
  int i, j, len;

  link_t*  lp;
  link_t** lnk;

  lnk = (link_t**) malloc ((ly + 1) * sizeof(link_t*));
  for(i = 0; i < ly + 1; i++) lnk[i] = (link_t*) malloc ((lx + 1) * sizeof(link_t));

  for(i = 0; i < ly; i++) lnk[i][lx] = (link_t){ly - i, y[i], &lnk[i + 1][lx]};
  for(i = 0; i < lx; i++) lnk[ly][i] = (link_t){lx - i , x[i], &lnk[ly][i + 1]};
  
  lnk[ly][lx] = (link_t) {0};

  for(i = ly - 1; i >= 0; i--) 
    for(j = lx - 1; j >= 0; j--) {
      lp = &lnk[i][j];
      if(y[i] == x[j]) {
	lp->next = &lnk[i + 1][j + 1];
	lp->letter = x[j];
      } else if(lnk[i][j + 1].len < lnk[i + 1][j].len ) {
	lp->next = &lnk[i][j + 1];
	lp->letter = x[j];
      } else {
	lp->next = &lnk[i + 1][j];
	lp->letter = y[i];
      }
      lp->len = lp->next->len + 1; 
    }  

  len = 0;
  for(lp = &lnk[0][0]; lp != &lnk[ly][lx]; lp=lp->next)
    out[len++] = lp->letter;

  out[len] = '\0';

  for (i = 0; i < ly + 1; i++) free(lnk[i]);
  free(lnk);

  return len;
}
