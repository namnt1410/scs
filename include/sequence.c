#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sequence.h"

int check_sequence(char *seq, char *alphabet) {
  char ch;
  int i = 0;

  ch = seq[0]; 
  while(ch != '\0' && strchr(alphabet, ch) != NULL) ch = seq[i++];

  return (ch == '\0');
}

int check_supersequence(char *seq, char *super) {
  int i = 0, j = 0;

  while(seq[i] != '\0' && super[j] != '\0') {
    if(seq[i] == super[j]) i++;
    j++;
  }

  return (seq[i] == '\0'); 
}

int check_common_supersequence(SequenceList list, char *super) {
  Sequence *seq;

  seq = list;
  while(seq) {
    if(!check_supersequence(seq->seq, super)) return 0;
    seq =  seq->next;
  }

  return 1; 
}

Sequence *create_sequence(char *seq) {
  Sequence *new = (Sequence*)malloc(sizeof(Sequence));

  new->seq = strdup(seq);
  new->len = strlen(seq);
  new->next = NULL;

  return new;
}

Sequence *add_sequence(SequenceList *list, char *seq) {
  Sequence *new_seq = create_sequence(seq); 
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

char *pop(SequenceList *list) {
  if((*list) == NULL) return NULL;
  
  char *seq = strdup((*list)->seq);

  Sequence *tmp = *list; 
  *list = (*list)->next;
  free(tmp); 

  return seq;
}
