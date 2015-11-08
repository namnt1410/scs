#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "block.h"

#define MAX_LEN		10000

Block *make_block(int sym) {
  Block *new;

  new = (Block*)malloc(sizeof(Block));
  new->sym = sym;
  new->len = 1;
  new->next = NULL;

  return new;
}

SequenceBlock convert(int *seq, int len) {
  Block *head = NULL, *cur = NULL;
  Block *new;
  int i, changed = 1; 

  for (i = 0; i < len; i++) {
    if(changed) {
      new = make_block(seq[i]);
      if(head == NULL) {
        head = new;
        cur = head;
      } else {
        cur->next = new;
        cur = new;
      }
    } else cur->len++;

    if(seq[i] == seq[i + 1]) changed = 0;
    else changed = 1;
  }

  return head;
}  

int *revert(SequenceBlock block, int *len) {
  int *seq;
  Block *b;
  int i;

  seq = (int*) malloc (MAX_LEN * sizeof(int));
  *len = 0;
  
  b = block;
  while(b) {
    for(i = 0; i < b->len; i++) {
      seq[(*len)] = b->sym;
      *len++;
    }
  
    b = b->next;
  }

  return seq;
}

int run(SequenceBlock block) {
  Block *b;
  int maxlen = 0;

  b = block;
  while(b) {
    if(b->len > maxlen) maxlen = b->len;
    b = b->next;
  }

  return maxlen;
}

SequenceBlock half_reduce(SequenceBlock block) {
  Block *b;

  b = block;
  while(b) {
    b->len = ceil(b->len / 2.0);
    b = b->next;
  }

  return block;
}
