#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "fields.h"

#include "input.h"

SequenceList readsequences (char* filename, int *alphabet, int *alpha_len) {
  SequenceList list;
  IS is;
  int *seq;
  int sym;
  int *tbl;
  int len;

  is = new_inputstruct (filename);
  seq = (int*) malloc (MAXLEN * sizeof(int)); 
  tbl = (int*) calloc (128, sizeof(int));  

  *alpha_len = 0;
  list = NULL;

  while(get_line(is) >= 0) {
    len = 0; sym = is->text1[0];
    while (sym != '\n') {
      if (!tbl[sym]) {
        tbl[sym] = 1; alphabet[(*alpha_len)++] = sym;
      }
      seq[len++] = sym;
      sym = is->text1[len];
    }
    add_sequence(&list, seq, len);
  }

  jettison_inputstruct (is);

  return list;
}

SequenceList gensequences (int size, int min_len, int max_len, int alpha_len, int *alphabet) {
  SequenceList list;
  int *seq;
  int i, j, len;
  time_t t;

  srand((unsigned) time(&t));
  printf("rand: %d\n", (rand() % 100));

  //alphabet = (int*) malloc (alpha_len * sizeof(char));
  seq = (int*) malloc (max_len * sizeof(int));

  for (i = 0; i < alpha_len; i++) alphabet[i] = i;

  list = NULL;

  for (i = 0; i < size; i++) {
    if (min_len == max_len) len = min_len;
    else len = min_len + (rand() % ((max_len - min_len) + 1));

    for (j = 0; j < len; j++) seq[j] = alphabet[(rand() % alpha_len)];
     
    add_sequence(&list, seq, len);
  }

  return list;
}
