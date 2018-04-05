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
