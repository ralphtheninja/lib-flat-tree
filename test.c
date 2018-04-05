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
  assert(lft_index(0, 0) == 0, "index 1");
  assert(lft_index(0, 1) == 2, "index 2");
  assert(lft_index(0, 2) == 4, "index 3");
  assert(lft_index(1, 0) == 1, "index 5");
  assert(lft_index(1, 1) == 5, "index 6");
  assert(lft_index(2, 0) == 3, "index 7");
  assert(lft_index(2, 1) == 11, "index 8");
  assert(lft_index(3, 0) == 7, "index 9");
  assert(lft_index(3, 1) == 23, "index 10");
}

int main(int argc, char** argv)
{
  test_index();

  return 0;
}
