#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fields.h"

#include "input.h"

void create_input_data(char* filename) {
  IS is ;

  is = new_inputstruct (filename); 

  if(get_line(is) >= 0) 
    strcpy(alphabet, is->fields[0]);
  
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
}
