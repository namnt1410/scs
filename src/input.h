#ifndef __INPUT_H__
#define __INPUT_H__

#include "sequence.h"

#define MAX_ALPHABET_SIZE 128
#define MAX_SET_SIZE 100

typedef struct {
  char **str_set; 
  int num_str;  
}InputData;

SequenceList readsequences(char* filename, char* alphabet);
SequenceList gensequences(int size, int min_len, int max_len, int alpha_len, char* alphabet);

#endif
