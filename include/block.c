#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "block.h"

#define MAX_LEN		1000

Block *make_block(char letter) {
  Block *new;

  new = (Block*)malloc(sizeof(Block));
  new->letter = letter;
  new->len = 1;
  new->next = NULL;

  return new;
}

SequenceBlock convert(char *seq) {
  Block *head = NULL, *cur = NULL;
  Block *new;
  char ch;
  int i = 0, changed = 1; 

  ch = seq[0];
  while(ch != '\0') {
    if(changed) {
      new = make_block(ch);
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

    ch = seq[++i];
  }

  return head;
}  

char *revert(SequenceBlock block) {
  char *seq;
  Block *b;
  int i, len = 0;
  
  seq = malloc(MAX_LEN * sizeof(char));
  
  b = block;
  while(b) {
    for(i = 0; i < b->len; i++) *(seq + (len++)) = b->letter;
    b = b->next;
  }

  *(seq + len) = '\0';

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
    b->len = ceil(((double)b->len) / 2.0);
    b = b->next;
  }

  return block;
}
