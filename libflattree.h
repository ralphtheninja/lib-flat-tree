#ifndef __libflattree_h__
#define __libflattree_h__

#include <stdlib.h>

size_t lft_index(int depth, int offset);
int lft_depth(size_t index);
int lft_offset(size_t index);

#endif // __libflattree_h__
