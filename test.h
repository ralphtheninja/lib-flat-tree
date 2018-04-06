#define BEGIN_TEST()                            \
  int __test_failed_count = 0;                  \
  int __test_success_count = 0;

#define TEST(fn)                               \
  printf("# Testing " #fn "\n");               \
  test_##fn();

#define ASSERT(A)                                         \
  if (!(A)) {                                             \
    printf(" [FAIL] " #A " (%s:%d)\n",                    \
           __FILE__, __LINE__);                           \
    ++__test_failed_count;                                \
  } else {                                                \
    printf(" [OK] " #A "\n");                             \
    ++__test_success_count;                               \
  }

#define TEST_REPORT()                                            \
  const char *__res_str = __test_failed_count ? "FAILED" : "OK"; \
  printf("\n# Results %d/%d [%s]\n",                             \
         __test_success_count,                                   \
         __test_success_count +                                  \
         __test_failed_count,                                    \
         __res_str);

#define TEST_RESULT() \
  __test_failed_count == 0 ? 0 : 1
