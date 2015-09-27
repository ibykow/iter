#include <string.h>
#include "debug.h"
#include "iter.h"

static void test_int_iter(void *e, size_t i, void *arr, size_t len, void *ctx)
{
    TEST(i < len);
    TEST(arr);
    TEST(*(int *) e == (int) (i + 1));
    TEST((*((int *) arr) + (int) i) == *(int *) e);
    TEST(ctx == 0);
}

static void test_char_iter(void *e, size_t i, void *arr, size_t len, void *ctx)
{
    TEST(i < len);
    TEST(*(char *) e == (*(char *) arr + (int) i));
    TEST(*(char *) e == (*(char *) ctx + (int) i));
}

TEST_DEF(iter_next)
{
    int i, arr[] = { 1, 2, 3, 4, 5, 6 }, len = sizeof(arr) / sizeof(int);
    struct iter_info_s info;
    iter_info_init(&info, arr, 0, test_int_iter, sizeof(int), len);

    for (i = 0; i < len; i++) {
        TEST(iter_remaining(&info));
        iter_next(&info);
    }

    TEST(!iter_remaining(&info));
}


TEST_DEF(for_each)
{
    char str[] = "abcdefghijklmnop";
    size_t len = strlen(str);

    for_each(str, sizeof(char), len, str, test_char_iter);
}

int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;

    TEST_RUN(iter_next);
    TEST_RUN(for_each);
    return 0;
}
