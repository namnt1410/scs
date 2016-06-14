#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jval.h"
#include "dllist.h"

#include "scs.h"
#include "dag.h"

int scs_graph(SequenceList list, int *super) {
  JRB g = make_jrb();
  char *out;
  int i, n;
  int len, temp;
  int *tup;
  node_t *node, *root;
  node_t *prev, *cur;
  Dllist dnode, queue;
  JRB bnode;
  
  out = malloc((MAX_LEN + 1) * sizeof(char));
  n = get_size(list);
  tup = (int*) malloc (n * sizeof(int));
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
        p->sym = jval_i(bnode->val);
	dll_append(queue, new_jval_v(p));
      } 
    }
  }

  cur = node; len = 0;
  while (cur != root) {
    prev = cur->parent;
    super[len++] = cur->sym;
    cur = prev;
  }

  for (i = 0; i < len/2; i++) {
    temp = super[i]; super[i] = super[len - i - 1]; super[len - i - 1] = temp;
  }

  free(tup);

  return len;
}
