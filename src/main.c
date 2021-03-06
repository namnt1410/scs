#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "input.h"
#include "scs.h"

int main(int argc, char **argv) {
  SequenceList list;
  int alphabet[MAX_ALPHABET_SIZE];
  int i;
  int arg_size, arg_min, arg_max, alpha_len;
  int super[MAX_LEN];
  int len;
  extern int max_loop_count;
  extern int max_nonimproved_continous_loop_count;

  if (strcmp(argv[1], "r") == 0 && argc >= 3) {
    list = readsequences(argv[2], alphabet, &alpha_len);
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

  len = scs_alpha_leftmost (list, super);
  printf("alpha_leftmost: %d %d\n", len, check_common_supersequence(list, super, len));
 
  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Elapsed time: %lf ms\n", time_spent * 1000);

  begin = clock();

  max_loop_count = 10;
  max_nonimproved_continous_loop_count = 3;

  len = scs_lsearch (list, super);
  printf("lsearch: %d %d\n", len, check_common_supersequence(list, super, len));
  /*for (i = 0; i < len; i++) {
    printf ("%c\n", super[i]);
  }*/
 
  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Elapsed time: %lf ms\n", time_spent * 1000);

  begin = clock();

  max_loop_count = 200;
  max_nonimproved_continous_loop_count = 100;

  len = scs_lsearch (list, super);
  printf("lsearch: %d %d\n", len, check_common_supersequence(list, super, len));
 
  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Elapsed time: %lf ms\n", time_spent * 1000);

  begin = clock();

  len = scs_mmerge_H0 (list, super);
  printf("mmerge: %d %d\n", len, check_common_supersequence(list, super, len));
 
  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Elapsed time: %lf ms\n", time_spent * 1000);

  return 0;
}

