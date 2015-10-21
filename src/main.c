#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "input.h"
#include "scs.h"

int main(int argc, char **argv) {
  if (argc <= 1) {
    printf("scs: no input file.\n");
    return -1;
  }

  create_input_data(argv[1]);

  clock_t begin, end;
  double time_spent;

  begin = clock();

  printf("%s\n", scs_lsearch(list, alphabet));
 
  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Elapsed time: %lf ms\n", time_spent * 1000);

  return 0;
}

