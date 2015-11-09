#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "input.h"
#include "scs.h"

int main(int argc, char **argv) {
  SequenceList list;
  int alphabet[1000];
  int i;
  int arg_size, arg_min, arg_max, alpha_len;
  int super[10000];
  int len;

  if (strcmp(argv[1], "r") == 0 && argc >= 3) {
    //list = readsequences(argv[2], alphabet);
    list = gensequences(10, 5, 5, 10, alphabet);
  } else if (strcmp(argv[1], "g") == 0 && argc >= 6) {
    arg_size = atoi(argv[2]); arg_min = atoi(argv[3]);
    arg_max = atoi(argv[4]); alpha_len = atoi(argv[5]); 

    list = gensequences(arg_size, arg_min, arg_max, alpha_len, alphabet);
  } else {
    printf("scs: invalid argument.\n");
    return -1;
  }

  clock_t begin, end;
  double time_spent;

  begin = clock();

  len = scs_mmerge(list, alphabet, alpha_len, super);
  printf("mmerge: %d %d\n", len, check_common_supersequence(list, super, len));
  //for (i = 0; i < len; i++) printf("%d ", super[i]);
  //printf("\n");  
 
  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Elapsed time: %lf ms\n", time_spent * 1000);

  /* begin = clock();

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

  printf("Elapsed time: %lf ms\n", time_spent * 1000);*/

  //free_list(&list);

  return 0;
}

