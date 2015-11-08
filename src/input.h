#ifndef __INPUT_H__
#define __INPUT_H__

#include "sequence.h"

//SequenceList readsequences(char* filename, char* alphabet);
SequenceList gensequences(int size, int min_len, int max_len, int alpha_len, int *alphabet);

#endif
