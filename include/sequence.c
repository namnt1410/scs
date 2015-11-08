#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sequence.h"

int get_serial (int sym, int *alphabet, int alpha_len) {
  int i;
  
  for (i = 0; i < alpha_len; i++) 
    if (alphabet[i] == sym) return i;

  return -1;
}

int check_sequence(int *seq, int len, int *alphabet, int alpha_len) {
  int i;
 
  for (i = 0; i < len; i++) 
    if (get_serial(seq[i], alphabet, alpha_len) == -1) return 0; 

  return 1;
}

int check_supersequence(int *seq, int len, int *super, int super_len) {
  int i = 0, j = 0;

  while(i < len && j < super_len) {
    if(seq[i] == super[j]) i++;
    j++;
  }

  return (i == len); 
}

int check_common_supersequence(SequenceList list, int *super, int super_len) {
  Sequence *seq;

  seq = list;
  while(seq) {
    if(!check_supersequence(seq->seq, seq->len, super, super_len)) return 0;
    seq =  seq->next;
  }

  return 1; 
}

Sequence *create_sequence(int *seq, int len) {
  Sequence *new = (Sequence*)malloc(sizeof(Sequence));

  new->len = len;
  new->seq = (int*) malloc (len * sizeof(int));
  memcpy (new->seq, seq, len * sizeof(int));

  new->next = NULL;

  return new;
}

Sequence *add_sequence(SequenceList *list, int *seq, int len) {
  Sequence *new_seq = create_sequence(seq, len); 
  Sequence *curr_seq, *prev_seq;
  
  if(new_seq == NULL) return (new_seq);

  if((*list) == NULL) { 
    *list = new_seq;
  } else if(new_seq->len < (*list)->len) {
    new_seq->next = (*list);
    *list = new_seq;
  } else {
    curr_seq = *list;
    
    while (curr_seq != NULL && new_seq->len >= curr_seq->len) {
      prev_seq = curr_seq;
      curr_seq = curr_seq->next; 
    } 

    prev_seq->next = new_seq;
    new_seq->next = curr_seq;
  }

  return new_seq;  
}

int get_size(SequenceList list) {
  Sequence *node = list;
  int len = 0;

  while(node) {
    len++;
    node = node->next;
  }

  return len;
}

void free_list(SequenceList *list) {
  Sequence *seq;

  seq = *list;
  while (seq) {
    (*list) = (*list)->next;
    free(seq);
    seq = (*list);
  }
} 

