# libflattree

> Map a binary tree to a list (c version of [mafintosh/flat-tree]).

## Usage

```c
#include <libflattree.h>

int main(void)
{
  printf("index: %d\n", lft_index(0, 0));
  printf("index: %d\n", lft_index(2, 1));
  printf("index: %d\n", lft_index(3, 1));
  return 0;
}
```

Outputs:

```
index: 0
index: 11
index: 23
```

## API

### `size_t lft_index(int depth, int offset);`

Returns an array index for the tree element at the given depth and offset.

### `int lft_depth(size_t index);`

Returns the depth of an element.

### `int lft_offset(size_t index);`

Returns the relative offset of an element.

### `size_t lft_sibling(size_t index);`

Returns the index of this elements sibling.

## License

MIT

[mafintosh/flat-tree]: https://github.com/mafintosh/flat-tree
