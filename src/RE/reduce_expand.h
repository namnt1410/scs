#ifndef __REDUCE_EXPAND_H__
#define __REDUCE_EXPAND_H__

SequenceList *reduce(SequenceList list, int *m);
int expand (SequenceList *rlist, int m, int *aux_seq, int aux_len, int *super);

#endif
