#include <stdio.h>
#include <stdlib.h>
#include "node_modules/test.h/test.h"
#include "libflattree.h"

BEGIN_TEST();

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

void test_offset()
{
  ASSERT(lft_offset(0) == 0);
  ASSERT(lft_offset(1) == 0);
  ASSERT(lft_offset(3) == 0);
  ASSERT(lft_offset(7) == 0);
  ASSERT(lft_offset(2) == 1);
  ASSERT(lft_offset(4) == 2);
  ASSERT(lft_offset(444) == 222);
  ASSERT(lft_offset(11) == 1);
  ASSERT(lft_offset(19) == 2);
  ASSERT(lft_offset(13) == 3);
  ASSERT(lft_offset(39) == 2);
}

void test_sibling()
{
  ASSERT(lft_sibling(1) == 5);
  ASSERT(lft_sibling(5) == 1);
  ASSERT(lft_sibling(9) == 13);
  ASSERT(lft_sibling(13) == 9);
  ASSERT(lft_sibling(3) == 11);
  ASSERT(lft_sibling(7) == 23);
  ASSERT(lft_sibling(23) == 7);
  ASSERT(lft_sibling(19) == 27);
  ASSERT(lft_sibling(27) == 19);
}

void test_parent()
{
  ASSERT(lft_parent(0) == 1);
  ASSERT(lft_parent(2) == 1);
  ASSERT(lft_parent(1) == 3);
  ASSERT(lft_parent(3) == 7);
  ASSERT(lft_parent(11) == 7);
  ASSERT(lft_parent(29) == 27);
  ASSERT(lft_parent(27) == 23);
}

void test_left_child()
{
  ASSERT(lft_left_child(0) == -1);
  ASSERT(lft_left_child(444) == -1);
  ASSERT(lft_left_child(3) == 1);
  ASSERT(lft_left_child(11) == 9);
  ASSERT(lft_left_child(15) == 7);
  ASSERT(lft_left_child(21) == 20);
  ASSERT(lft_left_child(23) == 19);
  ASSERT(lft_left_child(27) == 25);
}

void test_right_child()
{
  ASSERT(lft_right_child(0) == -1);
  ASSERT(lft_right_child(444) == -1);
  ASSERT(lft_right_child(3) == 5);
  ASSERT(lft_right_child(11) == 13);
  ASSERT(lft_right_child(15) == 23);
  ASSERT(lft_right_child(21) == 22);
  ASSERT(lft_right_child(23) == 27);
  ASSERT(lft_right_child(27) == 29);
}

void test_left_span()
{
  ASSERT(lft_left_span(0) == 0);
  ASSERT(lft_left_span(1) == 0);
  ASSERT(lft_left_span(3) == 0);
  ASSERT(lft_left_span(11) == 8);
  ASSERT(lft_left_span(23) == 16);
  ASSERT(lft_left_span(27) == 24);
  ASSERT(lft_left_span(314) == 314);
  ASSERT(lft_left_span(56) == 56);
}

void test_right_span()
{
  ASSERT(lft_right_span(0) == 0);
  ASSERT(lft_right_span(1) == 2);
  ASSERT(lft_right_span(3) == 6);
  ASSERT(lft_right_span(7) == 14);
  ASSERT(lft_right_span(11) == 14);
  ASSERT(lft_right_span(19) == 22);
  ASSERT(lft_right_span(15) == 30);
  ASSERT(lft_right_span(23) == 30);
  ASSERT(lft_right_span(27) == 30);
}

int main(int argc, char** argv)
{
  TEST(index);
  TEST(depth);
  TEST(offset);
  TEST(sibling);
  TEST(parent);
  TEST(left_child);
  TEST(right_child);
  TEST(left_span);
  TEST(right_span);

  TEST_REPORT();

  return TEST_RESULT();
}
