#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "scs.h"
#include "block.h"

SequenceBlock *convert_sequencelist(SequenceList list) {
  SequenceBlock *blist;
  Sequence *node;
  int i = 0, n;

  n = get_size(list);
  blist = (SequenceBlock*)malloc(n * sizeof(SequenceBlock));
  
  node = list;
  while(node) {
    blist[i++] = convert(node->seq);
    node = node->next;
  }

  return blist;
}

SequenceList revert_sequencelist(SequenceBlock *blist, int n) {
  SequenceList list = NULL;
  int i;

  for(i = 0; i < n; i++) 
    add_sequence(&list, revert(blist[i])); 

  return list;
}

SequenceList *reduce(SequenceList list, int *m) {
  SequenceList *rlist;
  SequenceBlock *half, *blist;
  int i, j, n, r, maxrun;

  n = get_size(list);
  blist = convert_sequencelist(list);

  maxrun = 0;
  for(i = 0; i < n; i++) {
    r = run(blist[i]); 
    if(r > maxrun) maxrun = r;
  }  
  *m = ceil(log(maxrun));

  rlist = (SequenceList*)malloc((*m + 1) * sizeof(SequenceList));
  rlist[*m] = revert_sequencelist(blist, n); 

  half = blist; 

  for(i = *m; i >= 1; i--) {
    for(j = 0; j < n ; j++) half[j] = half_reduce(half[j]);
    rlist[i - 1] = revert_sequencelist(half, n);
  } 

  free(half);
   
  return rlist;
}

char *expand(SequenceList *rlist, int m, char *aux_seq) {
  int i;
  Block *bnode;
  SequenceBlock block;
  
  block = convert(aux_seq);
  for(i = 1; i <= m; i++) {
    bnode = block;
    while(bnode) {
      bnode->len *= 2;
      bnode =  bnode->next;
    }
    bnode = block;
    while(bnode) {
      while(check_common_supersequence(rlist[i], revert(block)) && bnode->len >= 0)
        bnode->len--;
      bnode->len++; bnode = bnode->next;
    }
  }

  return revert(block);
} 

char* scs_reduce_expand(SequenceList list, char* alphabet) {
  int i, m;
  char *out;
  char aux_seq[MAX_LEN];
  SequenceList *rlist;

  rlist = reduce(list, &m);
  strcpy(aux_seq, scs_greedy(rlist[0], alphabet));

  out = expand(rlist, m, aux_seq);

  for (i = 0; i <= m; i++) free_list(&rlist[i]);
  free(rlist); 

  return out;
}
