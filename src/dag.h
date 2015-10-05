#ifndef __DAG_H__
#define __DAG_H__

#include "jrb.h"

#include "sequence.h"

typedef struct node {
  char letter;
  int* tup;
  int len;
  struct node* parent;
  JRB succ;
  int visited;
} node_t;

node_t* make_node (int* tup, int n);
int* end_tuple (SequenceList in);
void gen_succ(JRB g, SequenceList in, node_t *root);

#endif
