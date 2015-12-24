#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "input.h"

#define MAX_LEN 100000

SequenceList readsequences (char* filename, int *alphabet, int *alpha_len) {
  SequenceList list;
  FILE *fp;
  int *seq;
  int *check;
  int ch;
  int len = 0;

  fp = fopen (filename, "r");

  if (fp == NULL) {
    printf ("input: Can't access data file!\n");
    exit (0);
  }

  seq = (int*) malloc (MAX_LEN * sizeof(int)); 
  check = (int*) calloc (128, sizeof(int));  

  *alpha_len = 0;
  list = NULL;

  ch = fgetc(fp);
  while(ch != EOF) {
    if (ch != '\n') {
      if (!check[ch]) {
        check[ch] = 1; alphabet[(*alpha_len)++] = ch;
      }
      seq[len++] = ch;
    } else {
      add_sequence(&list, seq, len);
      len = 0;
    }

    ch = fgetc (fp);
  }

  fclose (fp);

  return list;
}

SequenceList gensequences (int size, int min_len, int max_len, int alpha_len, int *alphabet) {
  SequenceList list;
  int *seq;
  int i, j, len;
  time_t t;

  srand((unsigned) time(&t));
  printf("rand: %d\n", (rand() % 100));
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
