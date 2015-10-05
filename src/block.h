#ifndef __BLOCK_H__
#define __BLOCK_H__

typedef struct block_t {
  char letter;
  int len;
  struct block_t *next;
} Block;

typedef struct block_t *SequenceBlock; 

SequenceBlock convert(char *seq);
char *revert(SequenceBlock block);
Block *half_reduce(SequenceBlock block);
int run(SequenceBlock block);

#endif
