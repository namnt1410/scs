#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jval.h"
#include "dllist.h"

#include "scs.h"
#include "dag.h"

char* scs_graph(SequenceList list, char* alphabet) {
  JRB g = make_jrb();
  char *out;
  int i;
  int n;
  int *tup;
  node_t *node, *root;
  node_t *prev, *cur;
  Dllist dnode, queue;
  JRB bnode;
  
  out = malloc(MAX_SEQUENCE_LEN * sizeof(char));
  n = get_size(list);
  tup = (int*)malloc(n * sizeof(int));
  memset(tup, 0, n * sizeof(int));

  root = make_node(tup, n);
  gen_succ (g, list, root);

  queue = new_dllist();

  dll_append(queue, new_jval_v(root));
  root->visited = 1;

  while (!dll_empty(queue)) {
    dnode = dll_first(queue);
    node = (node_t*)jval_v(dnode->val);
    dll_delete_node (dnode);

    if (memcmp(node->tup, end_tuple(list), n * sizeof(int)) == 0) break; 

    jrb_traverse(bnode, node->succ) {
      node_t *p = (node_t*)jval_v(bnode->key);
      if (!p->visited) {
	p->visited = 1; 
	p->parent = node;
        p->letter = jval_c(bnode->val);
	dll_append(queue, new_jval_v(p));
      } 
    }
  }

  cur = node; out = strdup("");
  while (cur != root) {
    prev = cur->parent;
    for (i = strlen(out); i >= 0; i--) out[i + 1] = out[i];
    out[0] = cur->letter;
    cur = prev ;
  }

  return out;
}
