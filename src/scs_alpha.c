#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scs.h"

char* scs_alpha(SequenceList list, char* alphabet) {
  char *out;
  int i, len = 0;
  Sequence *p = list;

  while(p != NULL) {
    if(p->len > len) len = p->len;
    p = p->next;
  }

  out = strdup("");
  for(i = 0; i < len; i++) 
    strcat(out, alphabet);

  return out;
}

