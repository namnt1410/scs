#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

#define MAX_LEN 	100000

typedef struct Sequence_t {
  int *seq;
  int len;
  int offset;
  struct Sequence_t *next;
} Sequence;

typedef struct Sequence_t *SequenceList;

int get_serial (int sym, int *alphabet, int alpha_len);
int check_sequence(int *seq, int len, int *alphabet, int alpha_len);
int check_supersequence(int *seq, int len, int *super, int super_len);
int check_common_supersequence(SequenceList list, int *super, int super_len);
int get_alphabet_set (SequenceList list, int *alphabet);

Sequence *create_sequence(int *seq, int len);
Sequence *add_sequence(SequenceList *list, int *seq, int len);
int get_size(SequenceList list);
void free_list(SequenceList *list);

#endif
