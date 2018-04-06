#include "libflattree.h"

static inline int is_even(int n)
{
  return n % 2 == 0;
}

static inline int is_odd(int n)
{
  return n % 2 != 0;
}

size_t lft_index(int depth, int offset)
{
  return (offset << depth + 1) | ((1 << depth) - 1);
}

int lft_depth(size_t index)
{
  int depth = 0;

  while (is_odd(index)) {
    index >>= 1;
    depth++;
  }

  return depth;
}

static int offset(size_t index, int depth)
{
  return is_even(index) ? index / 2 : index >> (depth + 1);
}

int lft_offset(size_t index)
{
  return offset(index, lft_depth(index));
}

size_t lft_sibling(size_t index)
{
  int depth = lft_depth(index);
  return lft_index(depth, offset(index, depth) ^ 1);
}

size_t lft_parent(size_t index)
{
  int depth = lft_depth(index);
  return lft_index(depth + 1, offset(index, depth) >> 1);
}

size_t lft_left_child(size_t index)
{
  if (is_even(index)) return -1;
  int depth = lft_depth(index);
  return lft_index(depth - 1, offset(index, depth) << 1);
}

size_t lft_right_child(size_t index)
{
  if (is_even(index)) return -1;
  int depth = lft_depth(index);
  return lft_index(depth - 1, 1 + (offset(index, depth) << 1));
}

size_t lft_left_span(size_t index)
{
  if (is_even(index)) return index;
  int depth = lft_depth(index);
  return offset(index, depth) * (1 << depth + 1);
}
