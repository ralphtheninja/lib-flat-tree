#include "libflattree.h"

size_t lft_index(int depth, int offset)
{
  return (offset << depth + 1) | ((1 << depth) - 1);
}
