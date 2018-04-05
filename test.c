#include <stdio.h>
#include <stdlib.h>
#include "libflattree.h"

int TEST_RESULT = 0;

#define TEST(fn)                               \
  printf("# Testing " #fn "\n");               \
  fn();

#define ASSERT(A)                                         \
  if (!(A)) {                                             \
    printf(" [FAIL] " #A "(%s:%d)\n",                     \
           __FILE__, __LINE__);                           \
    TEST_RESULT = 1;                                      \
  } else {                                                \
    printf(" [OK] " #A "\n");                             \
  }


void test_index()
{
  ASSERT(lft_index(0, 0) == 0);
  ASSERT(lft_index(0, 1) == 2);
  ASSERT(lft_index(0, 2) == 4);
  ASSERT(lft_index(1, 0) == 1);
  ASSERT(lft_index(1, 1) == 5);
  ASSERT(lft_index(2, 0) == 3);
  ASSERT(lft_index(2, 1) == 11);
  ASSERT(lft_index(3, 0) == 7);
  ASSERT(lft_index(3, 1) == 23);
}

void test_depth()
{
  ASSERT(lft_depth(0) == 0);
  ASSERT(lft_depth(2) == 0);
  ASSERT(lft_depth(4) == 0);
  ASSERT(lft_depth(444) == 0);
  ASSERT(lft_depth(1) == 1);
  ASSERT(lft_depth(5) == 1);
  ASSERT(lft_depth(9) == 1);
  ASSERT(lft_depth(13) == 1);
  ASSERT(lft_depth(3) == 2);
  ASSERT(lft_depth(7) == 3);
}

int main(int argc, char** argv)
{
  TEST(test_index);
  TEST(test_depth);

  return TEST_RESULT;
}
