#ifndef __INPUT_H__
#define __INPUT_H__

#include "sequence.h"

#define MAX_ALPHABET_SIZE 128
#define MAX_SET_SIZE 100

typedef struct {
  char **str_set; 
  int num_str;  
}InputData;

char alphabet[MAX_ALPHABET_SIZE + 1];
SequenceList list;

void create_input_data(char* filename);

#endif
