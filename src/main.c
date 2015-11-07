#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "input.h"
#include "scs.h"

int main(int argc, char **argv) {
  if (argc <= 2) {
    printf("scs: invalid input data.\n");
    return -1;
  }

  SequenceList list;
  char alphabet[1000];
  int i;
  int arg_size, arg_min, arg_max, arg_alpha;

  if (strcmp(argv[1], "r") == 0) {
    list = readsequences(argv[2], alphabet);
  } else if (strcmp(argv[1], "g") == 0 && argc >= 6) {
    arg_size = atoi(argv[2]); arg_min = atoi(argv[3]);
    arg_max = atoi(argv[4]); arg_alpha = atoi(argv[5]); 

    list = gensequences(arg_size, arg_min, arg_max, arg_alpha, alphabet);
  } else {
    printf("scs: invalid argument.\n");
    return -1;
  }

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

