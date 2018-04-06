#ifndef __libflattree_h__
#define __libflattree_h__

#include <stdlib.h>

size_t lft_index(int depth, int offset);
int lft_depth(size_t index);

int lft_offset(size_t index);
int lft_offset_2(size_t index, int depth);

size_t lft_sibling(size_t index);
size_t lft_sibling_2(size_t index, int depth);

size_t lft_parent(size_t index);
size_t lft_parent_2(size_t index, int depth);

size_t lft_left_child(size_t index);
size_t lft_left_child_2(size_t index, int depth);

size_t lft_right_child(size_t index);
size_t lft_right_child_2(size_t index, int depth);

size_t lft_left_span(size_t index);

size_t lft_right_span(size_t index);

// NOTE!
// The following functions have not been ported from js/rust because
// it's currently unclear if they are needed at all

// count(index, depth)
// spans(index, depth)

// The following function has not been ported because afaik it's only
// used in `print-flat-tree` functionality, so that functionality should
// probably be moved up a level (basically just doing left_child() /
// right_child())

// children(index, depth)

#endif // __libflattree_h__
