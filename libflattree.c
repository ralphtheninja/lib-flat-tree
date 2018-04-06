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
  return (offset << (depth + 1)) | ((1 << depth) - 1);
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

int lft_offset(size_t index)
{
  return lft_offset_2(index, lft_depth(index));
}

int lft_offset_2(size_t index, int depth)
{
  return is_even(index) ? index / 2 : index >> (depth + 1);
}

size_t lft_sibling(size_t index)
{
  return lft_sibling_2(index, lft_depth(index));
}

size_t lft_sibling_2(size_t index, int depth)
{
  return lft_index(depth, lft_offset_2(index, depth) ^ 1);
}

size_t lft_parent(size_t index)
{
  return lft_parent_2(index, lft_depth(index));
}

size_t lft_parent_2(size_t index, int depth)
{
  return lft_index(depth + 1, lft_offset_2(index, depth) >> 1);
}

size_t lft_left_child(size_t index)
{
  return lft_left_child_2(index, lft_depth(index));
}

size_t lft_left_child_2(size_t index, int depth)
{
  if (is_even(index)) return -1;
  return lft_index(depth - 1, lft_offset_2(index, depth) << 1);
}

size_t lft_right_child(size_t index)
{
  return lft_right_child_2(index, lft_depth(index));
}

size_t lft_right_child_2(size_t index, int depth)
{
  if (is_even(index)) return -1;
  return lft_index(depth - 1, 1 + (lft_offset_2(index, depth) << 1));
}

size_t lft_left_span(size_t index)
{
  return lft_left_span_2(index,lft_depth(index));
}

size_t lft_left_span_2(size_t index, int depth)
{
  if (is_even(index)) return index;
  return lft_offset_2(index, depth) * (1 << (depth + 1));
}

size_t lft_right_span(size_t index)
{
  return lft_right_span_2(index, lft_depth(index));
}

size_t lft_right_span_2(size_t index, int depth)
{
  if (is_even(index)) return index;
  return (lft_offset_2(index, depth) + 1) * (1 << (depth + 1)) - 2;
}

//
// lft_iterator
//

lft_iterator* lft_iterator_create(size_t index)
{
  lft_iterator *it = malloc(1 * sizeof (lft_iterator));

  lft_iterator_seek(it, index);

  return it;
}

void lft_iterator_seek(lft_iterator* it, size_t index)
{
  it->index = index;

  if (is_odd(index)) {
    it->offset = lft_offset(index);
    it->factor = 1 << (lft_depth(index) + 1);
  } else {
    it->offset = index / 2;
    it->factor = 2;
  }
}

bool lft_iterator_is_left(lft_iterator* it)
{
  return is_even(it->offset);
}

bool lft_iterator_is_right(lft_iterator* it)
{
  return is_odd(it->offset);
}

size_t lft_iterator_prev(lft_iterator* it)
{
  if (!it->offset) return it->index;
  it->offset--;
  it->index -= it->factor;
  return it->index;
}

size_t lft_iterator_next(lft_iterator* it)
{
  it->offset++;
  it->index += it->factor;

  return it->index;
}

size_t lft_iterator_sibling(lft_iterator* it)
{
  return (lft_iterator_is_left(it) ?
          lft_iterator_next(it) :
          lft_iterator_prev(it));
}

size_t lft_iterator_parent(lft_iterator* it)
{
  if (is_odd(it->offset)) {
    it->index -= it->factor / 2;
    it->offset = (it->offset - 1) / 2;
  } else {
    it->index += it->factor / 2;
    it->offset /= 2;
  }

  it->factor *= 2;

  return it->index;
}

size_t lft_iterator_left_span(lft_iterator* it)
{
  it->index = it->index - it->factor / 2 + 1;
  it->offset = it->index / 2;
  it->factor = 2;

  return it->index;
}

size_t lft_iterator_right_span(lft_iterator* it)
{
  it->index = it->index + it->factor / 2 - 1;
  it->offset = it->index / 2;
  it->factor = 2;

  return it->index;
}

size_t lft_iterator_left_child(lft_iterator* it)
{
  if (it->factor == 2) return it->index;

  it->factor /= 2;
  it->index -= it->factor / 2;
  it->offset *= 2;

  return it->index;
}

size_t lft_iterator_right_child(lft_iterator* it)
{
  if (it->factor == 2) return it->index;

  it->factor /= 2;
  it->index += it->factor / 2;
  it->offset = 2 * it->offset + 1;

  return it->index;
}
