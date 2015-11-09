#ifndef __MMERGE_H__
#define __MMERGE_H__

#include "sequence.h"

int mmerge(Sequence **, int, int *, int, int (*majority)(Sequence **, int, int *, int, int *, int **, int *), int *);

#endif
