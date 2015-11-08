#ifndef __PAIR_H__
#define __PAIR_H__

typedef struct link {
  int len;
  int sym;
  struct link* next;
} link_t;

int scs_pair(int *seq1, int len1, int *seq2, int len2, int *super);

#endif
