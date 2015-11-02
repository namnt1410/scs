#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "fields.h"

#include "input.h"

SequenceList readsequences (char* filename, char *alphabet) {
  SequenceList list;
  IS is ;

  is = new_inputstruct (filename); 

  if(get_line(is) >= 0) 
    alphabet = strdup(is->fields[0]);
  else return NULL;
  
  list = NULL;

  while(get_line(is) >= 0) {
    if (!strcmp(is->fields[0], "")) continue;
    if (!check_sequence(is->fields[0], alphabet)) {
      printf("input: invalid sequence.\n");
      exit(0);
    }
    add_sequence(&list, is->fields[0]);
  }

  jettison_inputstruct (is);

  return list;
}

SequenceList gensequences (int size, int min_len, int max_len, int alpha_len, char *alphabet) {
  SequenceList list;
  char *seq;
  int i, j, len;
  time_t t;

  srand((unsigned) time(&t));
  printf("rand: %d\n", (rand() % 100));

  //alphabet = (char*) malloc (alpha_len * sizeof(char));
  seq = (char*) malloc (max_len * sizeof(char));

  for (i = 0; i < alpha_len; i++) alphabet[i] = i + 1;
  alphabet[alpha_len] = '\0';

  printf("alpha_len: %d\n", strlen(alphabet));

  list = NULL;

  for (i = 0; i < size; i++) {
    if (min_len == max_len) len = min_len;
    else len = min_len + (rand() % ((max_len - min_len) + 1));

    for (j = 0; j < len; j++) 
      seq[j] = alphabet[(rand() % alpha_len)];
    seq[len] = '\0'; 
    add_sequence(&list, seq);
  }

  return list;
}
