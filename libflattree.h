#ifndef __libflattree_h__
#define __libflattree_h__

#include <stdlib.h>

int64_t lft_index(int64_t depth, int64_t offset);
int64_t lft_depth(int64_t index);

int64_t lft_offset(int64_t index);
int64_t lft_offset_2(int64_t index, int64_t depth);

int64_t lft_sibling(int64_t index);
int64_t lft_sibling_2(int64_t index, int64_t depth);

int64_t lft_parent(int64_t index);
int64_t lft_parent_2(int64_t index, int64_t depth);

int64_t lft_left_child(int64_t index);
int64_t lft_left_child_2(int64_t index, int64_t depth);

int64_t lft_right_child(int64_t index);
int64_t lft_right_child_2(int64_t index, int64_t depth);

int64_t lft_left_span(int64_t index);
int64_t lft_left_span_2(int64_t index, int64_t depth);

int64_t lft_right_span(int64_t index);
int64_t lft_right_span_2(int64_t index, int64_t depth);

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

typedef struct lft_iterator {
  int64_t index;
  int64_t offset;
  int64_t factor;
} lft_iterator;

lft_iterator* lft_iterator_create(int64_t index);

void lft_iterator_seek(lft_iterator* it, int64_t index);

int64_t lft_iterator_is_left(lft_iterator* it);

int64_t lft_iterator_is_right(lft_iterator* it);

int64_t lft_iterator_prev(lft_iterator* it);

int64_t lft_iterator_next(lft_iterator* it);

int64_t lft_iterator_sibling(lft_iterator* it);

int64_t lft_iterator_parent(lft_iterator* it);

int64_t lft_iterator_left_span(lft_iterator* it);

int64_t lft_iterator_right_span(lft_iterator* it);

int64_t lft_iterator_left_child(lft_iterator* it);

int64_t lft_iterator_right_child(lft_iterator* it);

#endif // __libflattree_h__
