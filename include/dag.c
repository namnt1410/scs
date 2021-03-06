#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jval.h"
#include "dllist.h"

#include "dag.h"

int ucomp(Jval j1, Jval j2);

node_t* make_node (int* tup, int n) {
  node_t *new;

  new = (node_t*)malloc(sizeof(node_t));

  new->tup = (int*)malloc(n * sizeof(int));
  memcpy(new->tup, tup, n * sizeof(int));

  new->len = n ;
  new->visited = 0 ;

  new->succ = make_jrb();
  new->parent = NULL;

  return new;
}

int* end_tuple (SequenceList list) {
  int i = 0, n;
  int* tup;
  Sequence *node;
 
  n = get_size(list);
  tup = (int*)malloc(n * sizeof(int)) ;

  node = list;
  while(node) {
    tup[i++] = node->len;
    node =  node->next;
  }

  return tup;
}

void gen_succ(JRB g, SequenceList list, node_t* root) {
  Sequence *node;
  node_t *p, *tmp;
  int n;
  int i = 0;
  int sym;
  JRB b;

  n = get_size(list);
  tmp = make_node(root->tup, n); 

  JRB table = make_jrb();
  JRB bnode;

  Dllist rnode, newlist;

  jrb_insert_gen(g, new_jval_v(root), new_jval_v(NULL), ucomp);

  node = list;
  while(node) {
    if(root->tup[i] < node->len) {
      sym = node->seq[root->tup[i]];
      bnode = jrb_find_int(table, sym); 
      if(bnode == NULL) {
        newlist = new_dllist();
        jrb_insert_int(table, sym, new_jval_v(newlist));
      } else newlist = (Dllist)jval_v(bnode->val);
      dll_append(newlist, new_jval_i(i));
    }
    node = node->next; i++;
  }

  jrb_traverse(bnode, table) {
    sym = jval_i(bnode->key);
    newlist = (Dllist)jval_v(bnode->val);

    dll_traverse(rnode, newlist) {
      i = jval_i(dll_val(rnode));
      tmp->tup[i] = root->tup[i] + 1;
    }

    b = jrb_find_gen(g, new_jval_v(tmp), ucomp);
    if(b == NULL) p = make_node(tmp->tup, n);
    else p = (node_t*)jval_v(b->key);

    jrb_insert_gen(root->succ, new_jval_v(p), new_jval_i(sym), ucomp); 
    
    if(b == NULL) gen_succ(g, list, p);
    
    memcpy(tmp->tup, root->tup, n * sizeof(int));
  }

  free(tmp);
}

int ucomp(Jval j1, Jval j2) {
  node_t *x, *y;

  x = (node_t*)jval_v(j1);
  y = (node_t*)jval_v(j2);

  if(x->len != y->len)  return (x->len - y->len);

  return memcmp(x->tup, y->tup, x->len * sizeof(int));  
}
