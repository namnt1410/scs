#ifndef __BLOCK_H__
#define __BLOCK_H__

typedef struct block_t {
  int sym;
  int len;
  struct block_t *next;
} Block;

typedef struct block_t *SequenceBlock; 

SequenceBlock convert(int *seq, int len);
int *revert(SequenceBlock block, int *len);
Block *half_reduce(SequenceBlock block);
int run(SequenceBlock block);

#endif
