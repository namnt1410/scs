#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

typedef struct Sequence_t {
  int len;
  char *seq;
  struct Sequence_t *next;
} Sequence;

typedef struct Sequence_t *SequenceList;

int check_sequence(char *seq, char *alphabet);
int check_supersequence(char *seq, char *super);
int check_common_supersequence(SequenceList list, char *super);

Sequence *create_sequence(char *seq);
Sequence* add_sequence(SequenceList *list, char *seq);
int get_size(SequenceList list);
char* pop(SequenceList *list);

#endif
