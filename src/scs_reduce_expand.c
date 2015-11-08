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
    blist[i++] = convert(node->seq, node->len);
    node = node->next;
  }

  return blist;
}

SequenceList revert_sequencelist(SequenceBlock *blist, int n) {
  SequenceList list = NULL;
  int seq[MAX_LEN];
  int len;
  int i;

  for(i = 0; i < n; i++) {
    len = revert(blist[i], seq); 
    add_sequence(&list, seq, len);
  } 

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

  rlist = (SequenceList*) malloc ((*m + 1) * sizeof(SequenceList));
  rlist[*m] = revert_sequencelist(blist, n); 

  half = blist; 

  for(i = *m; i >= 1; i--) {
    for(j = 0; j < n ; j++) half[j] = half_reduce(half[j]);
    rlist[i - 1] = revert_sequencelist(half, n);
  } 

  free(half);
   
  return rlist;
}

int expand(SequenceList *rlist, int m, int *aux_seq, int aux_len, int *super) {
  int i;
  Block *bnode;
  SequenceBlock block;
  int len;
  int temp[MAX_LEN];
  
  block = convert(aux_seq, aux_len);
  for(i = 1; i <= m; i++) {
    bnode = block;
    while(bnode) {
      bnode->len *= 2;
      bnode =  bnode->next;
    }
    bnode = block;
    while(bnode) {
      len = revert(block, temp);
      while(check_common_supersequence(rlist[i], temp, len) && bnode->len >= 0) {
        bnode->len--;
        len = revert(block, temp);
      }
      bnode->len++; bnode = bnode->next;
    }
  }

  len = revert(block, super);

  return len;
} 

int scs_reduce_expand(SequenceList list, int *super) {
  int m;
  int len;
  int aux_seq[MAX_LEN], aux_len;
  SequenceList *rlist;

  rlist = reduce(list, &m);
  aux_len = scs_greedy(rlist[0], aux_seq);

  len = expand(rlist, m, aux_seq, aux_len, super);

  /*for (i = 0; i <= m; i++) free_list(&rlist[i]);
  free(rlist);*/ 

  return len;
}
