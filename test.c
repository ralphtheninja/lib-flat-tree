#include <stdio.h>
#include <stdlib.h>
#include "libflattree.h"

#define assert(A, M, ...)                      \
  if (!(A)) {                                  \
    fprintf(stderr,                            \
            "[FAIL] (%s:%d) " M "\n",          \
            __FILE__, __LINE__,                \
            ##__VA_ARGS__);                    \
    exit(1);                                   \
  } else {                                     \
    printf("[OK] " M "\n");                    \
  }

void test_index()
{
  assert(lft_index(0, 0) == 0, "index");
  assert(lft_index(0, 1) == 2, "index");
  assert(lft_index(0, 2) == 4, "index");
  assert(lft_index(1, 0) == 1, "index");
  assert(lft_index(1, 1) == 5, "index");
  assert(lft_index(2, 0) == 3, "index");
  assert(lft_index(2, 1) == 11, "index");
  assert(lft_index(3, 0) == 7, "index");
  assert(lft_index(3, 1) == 23, "index");
}

void test_depth()
{
  assert(lft_depth(0) == 0, "depth");
  assert(lft_depth(2) == 0, "depth");
  assert(lft_depth(4) == 0, "depth");
  assert(lft_depth(444) == 0, "depth");
  assert(lft_depth(1) == 1, "depth");
  assert(lft_depth(5) == 1, "depth");
  assert(lft_depth(9) == 1, "depth");
  assert(lft_depth(13) == 1, "depth");
  assert(lft_depth(3) == 2, "depth");
  assert(lft_depth(7) == 3, "depth");
}

int main(int argc, char** argv)
{
  test_index();
  test_depth();

  return 0;
}
