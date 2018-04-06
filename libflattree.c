#include "libflattree.h"

static inline int64_t pow_2(int64_t n)
{
  return (int64_t)1 << n;
}

static inline int64_t is_even(int64_t n)
{
  return n % 2 == 0;
}

static inline int64_t is_odd(int64_t n)
{
  return n % 2 != 0;
}

int64_t lft_index(int64_t depth, int64_t offset)
{
  return (offset * pow_2(depth + 1)) | (pow_2(depth) - 1);
}

int64_t lft_depth(int64_t index)
{
  int64_t depth = 0;

  while (is_odd(index)) {
    index >>= 1;
    depth++;
  }

  return depth;
}

int64_t lft_offset(int64_t index)
{
  return lft_offset_2(index, lft_depth(index));
}

int64_t lft_offset_2(int64_t index, int64_t depth)
{
  return is_even(index) ? index / 2 : index >> (depth + 1);
}

int64_t lft_sibling(int64_t index)
{
  return lft_sibling_2(index, lft_depth(index));
}

int64_t lft_sibling_2(int64_t index, int64_t depth)
{
  return lft_index(depth, lft_offset_2(index, depth) ^ 1);
}

int64_t lft_parent(int64_t index)
{
  return lft_parent_2(index, lft_depth(index));
}

int64_t lft_parent_2(int64_t index, int64_t depth)
{
  return lft_index(depth + 1, lft_offset_2(index, depth) >> 1);
}

int64_t lft_left_child(int64_t index)
{
  return lft_left_child_2(index, lft_depth(index));
}

int64_t lft_left_child_2(int64_t index, int64_t depth)
{
  if (is_even(index)) return -1;
  return lft_index(depth - 1, lft_offset_2(index, depth) << 1);
}

int64_t lft_right_child(int64_t index)
{
  return lft_right_child_2(index, lft_depth(index));
}

int64_t lft_right_child_2(int64_t index, int64_t depth)
{
  if (is_even(index)) return -1;
  return lft_index(depth - 1, 1 + (lft_offset_2(index, depth) << 1));
}

int64_t lft_left_span(int64_t index)
{
  return lft_left_span_2(index,lft_depth(index));
}

int64_t lft_left_span_2(int64_t index, int64_t depth)
{
  if (is_even(index)) return index;
  return lft_offset_2(index, depth) * pow_2(depth + 1);
}

int64_t lft_right_span(int64_t index)
{
  return lft_right_span_2(index, lft_depth(index));
}

int64_t lft_right_span_2(int64_t index, int64_t depth)
{
  if (is_even(index)) return index;
  return (lft_offset_2(index, depth) + 1) * pow_2(depth + 1) - 2;
}

//
// lft_iterator
//

lft_iterator* lft_iterator_create(int64_t index)
{
  lft_iterator *it = malloc(1 * sizeof (lft_iterator));

  lft_iterator_seek(it, index);

  return it;
}

void lft_iterator_seek(lft_iterator* it, int64_t index)
{
  it->index = index;

  if (is_odd(index)) {
    it->offset = lft_offset(index);
    it->factor = pow_2(lft_depth(index) + 1);
  } else {
    it->offset = index / 2;
    it->factor = 2;
  }
}

int64_t lft_iterator_is_left(lft_iterator* it)
{
  return is_even(it->offset);
}

int64_t lft_iterator_is_right(lft_iterator* it)
{
  return is_odd(it->offset);
}

int64_t lft_iterator_prev(lft_iterator* it)
{
  if (!it->offset) return it->index;
  it->offset--;
  it->index -= it->factor;
  return it->index;
}

int64_t lft_iterator_next(lft_iterator* it)
{
  it->offset++;
  it->index += it->factor;

  return it->index;
}

int64_t lft_iterator_sibling(lft_iterator* it)
{
  return (lft_iterator_is_left(it) ?
          lft_iterator_next(it) :
          lft_iterator_prev(it));
}

int64_t lft_iterator_parent(lft_iterator* it)
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

int64_t lft_iterator_left_span(lft_iterator* it)
{
  it->index = it->index - it->factor / 2 + 1;
  it->offset = it->index / 2;
  it->factor = 2;

  return it->index;
}

int64_t lft_iterator_right_span(lft_iterator* it)
{
  it->index = it->index + it->factor / 2 - 1;
  it->offset = it->index / 2;
  it->factor = 2;

  return it->index;
}

int64_t lft_iterator_left_child(lft_iterator* it)
{
  if (it->factor == 2) return it->index;

  it->factor /= 2;
  it->index -= it->factor / 2;
  it->offset *= 2;

  return it->index;
}

int64_t lft_iterator_right_child(lft_iterator* it)
{
  if (it->factor == 2) return it->index;

  it->factor /= 2;
  it->index += it->factor / 2;
  it->offset = 2 * it->offset + 1;

  return it->index;
}
