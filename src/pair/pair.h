#ifndef __PAIR_H__
#define __PAIR_H__

typedef struct link {
  int len;
  char letter;
  struct link* next;
} link_t;

int scs_pair(char* x, char* y, char* out);

#endif
