#ifndef __libflattree_h__
#define __libflattree_h__

#include <stdlib.h>

size_t lft_index(int depth, int offset);
int lft_depth(size_t index);
int lft_offset(size_t index);
size_t lft_sibling(size_t index);
size_t lft_parent(size_t index);
size_t lft_left_child(size_t index);
size_t lft_right_child(size_t index);

#endif // __libflattree_h__
