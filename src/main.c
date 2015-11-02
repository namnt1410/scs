#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "input.h"
#include "scs.h"

int main(int argc, char **argv) {
  /*if (argc <= 1) {
    printf("scs: no input file.\n");
    return -1;
  }*/

  SequenceList list;
  char alphabet[100];
  int i;

  list = gensequences(5, 10, 10, 10, alphabet);

  clock_t begin, end;
  double time_spent;

  begin = clock();

  printf("lsearch: %d\n", strlen(scs_lsearch(list, alphabet)));
 
  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Elapsed time: %lf ms\n", time_spent * 1000);

  begin = clock();

  printf("mmerge: %d\n", strlen(scs_mmerge(list, alphabet)));
 
  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Elapsed time: %lf ms\n", time_spent * 1000);

  begin = clock();

  printf("greedy: %d\n", strlen(scs_greedy(list, alphabet)));
 
  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Elapsed time: %lf ms\n", time_spent * 1000);

  begin = clock();

  printf("reduce expand: %d\n", strlen(scs_reduce_expand(list, alphabet)));
 
  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Elapsed time: %lf ms\n", time_spent * 1000);

  free_list(&list);

  return 0;
}

