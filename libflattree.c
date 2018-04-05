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

static int offset_with_depth(size_t index, int depth)
{
  return is_even(index) ? index / 2 : index >> (depth + 1);
}

int lft_offset(size_t index)
{
  return offset_with_depth(index, lft_depth(index));
}

static int sibling_with_depth(size_t index, int depth)
{
  return lft_index(depth, lft_offset(index) ^ 1);
}

size_t lft_sibling(size_t index)
{
  return sibling_with_depth(index, lft_depth(index));
}
