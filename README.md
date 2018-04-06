# libflattree

[![Build Status](https://travis-ci.org/ralphtheninja/libflattree.svg?branch=master)](https://travis-ci.org/ralphtheninja/libflattree)

> Map a binary tree to a list (c version of [mafintosh/flat-tree]).

**NOTE!** The API can change at any time. Do not use.

## Usage

```c
#include <libflattree.h>

int main(void)
{
  printf("index: %d\n", lft_index(3, 1));
  printf("parent: %d\n", lft_parent(5));
  return 0;
}
```

Outputs:

```
index: 23
parent: 3
```

## API

The functions below ending with a `_2` takes a pre computed `depth` parameter. Since calculating `depth` is an iterative process, these functions are an optimization to avoid having to re-calculate `depth`.

### `int64_t lft_index(int64_t depth, int64_t offset);`

Returns an array index for the tree element at the given depth and offset.

### `int64_t lft_depth(int64_t index);`

Returns the depth of an element.

### `int64_t lft_offset(int64_t index);`

Returns the relative offset of an element.

### `int64_t lft_offset_2(int64_t index, int64_t depth);`

As above but with pre computed depth.

### `int64_t lft_sibling(int64_t index);`

Returns the index of this elements sibling.

### `int64_t lft_sibling_2(int64_t index, int64_t depth);`

As above but with pre computed depth.

### `int64_t lft_parent(int64_t index);`

Returns the index of the parent element.

### `int64_t lft_parent_2(int64_t index, int64_t depth);`

As above but with pre computed depth.

### `int64_t lft_left_child(int64_t index);`

Returns the index of the left child. Returns `-1` if `index` is even, i.e. if the element is a leaf.

### `int64_t lft_left_child_2(int64_t index, int64_t depth);`

As above but with pre computed depth.

### `int64_t lft_right_child(int64_t index);`

Returns the index of the right child. Returns `-1` if `index` is even, i.e. if the element is a leaf.

### `int64_t lft_right_child_2(int64_t index, int64_t depth);`

As above but with pre computed depth.

### `int64_t lft_left_span(int64_t index);`

Returns the left spanning index in the tree `index` spans.

### `int64_t lft_left_span_2(int64_t index, int64_t depth);`

As above but with pre computed depth.

### `int64_t lft_right_span(int64_t index);`

Returns the right spanning index in the tree `index` spans.

### `int64_t lft_right_span_2(int64_t index, int64_t depth);`

As above but with pre computed depth.

### `lft_iterator* lft_iterator_create(int64_t index);`

Create an iterator starting at `index`.

The `lft_iterator*` is dynamically allocated so you need to call `free()` when you're done using it.

### `void lft_iterator_seek(lft_iterator* it, int64_t index);`

Move the iterator to `index`.

### `int64_t lft_iterator_is_left(lft_iterator* it);`

Returns `1` if the iterator is at a left sibling, otherwise `0`.

### `int64_t lft_iterator_is_right(lft_iterator* it);`

Returns `1` if the iterator is at a right sibling, otherwise `0`.

### `int64_t lft_iterator_prev(lft_iterator* it);`

Move the iterator to the previous item in the tree. Returns current `index` if `offset` is `0`.

### `int64_t lft_iterator_next(lft_iterator* it);`

Move the iterator to the next item in the tree.

### `int64_t lft_iterator_sibling(lft_iterator* it);`

Move the iterator to the current sibling index.

### `int64_t lft_iterator_parent(lft_iterator* it);`

Move the iterator to the current parent index.

### `int64_t lft_iterator_left_span(lft_iterator* it);`

Move the iterator to the current left span index.

### `int64_t lft_iterator_right_span(lft_iterator* it);`

Move the iterator to the current right span index.

### `int64_t lft_iterator_left_child(lft_iterator* it);`

Move the iterator to the current left child index.

### `int64_t lft_iterator_right_child(lft_iterator* it);`

Move the iterator to the current right child index.

## Also see

- [mafintosh/flat-tree]: Original node module
- [datrs/flat-tree]: A port of the node module to rust
- [bcomnes/flattree]: A port of the node module to Go

## License

MIT

[mafintosh/flat-tree]: https://github.com/mafintosh/flat-tree
[datrs/flat-tree]: https://github.com/datrs/flat-tree
[bcomnes/flattree]: https://github.com/bcomnes/flattree
