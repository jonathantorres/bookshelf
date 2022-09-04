#include "minunit.h"
#include "lcthw/darray_algos.h"
#include <string.h>

int testcmp(char **a, char **b)
{
    return strcmp(*a, *b);
}

int testcmp2(char *a, char *b)
{
    return strcmp(a, b);
}

DArray *create_words()
{
    DArray *result = DArray_create(0, 5);
    char *words[] = { "asdfasfd", "werwar", "13234", "asdfasfd", "oioj" };
    int i = 0;

    for (i = 0; i < 5; i++) {
        DArray_push(result, words[i]);
    }

    return result;
}

int is_sorted(DArray *array)
{
    int i = 0;

    for (i = 0; i < DArray_count(array) - 1; i++) {
        if (strcmp(DArray_get(array, i), DArray_get(array, i + 1)) > 0) {
            return 0;
        }
    }

    return 1;
}

char *run_sort_test(int (*func) (DArray *, DArray_compare), const char *name)
{
    DArray *words = create_words();
    mu_assert(!is_sorted(words), "Words should start not sorted");

    DArray_compare cmp_function = NULL;

    if (strstr(name, "custom") != NULL) {
        cmp_function = (DArray_compare) testcmp2;
    } else {
        cmp_function = (DArray_compare) testcmp;
    }

    debug("--- Testing %s sorting algorithm", name);
    int rc = func(words, (DArray_compare) cmp_function);
    mu_assert(rc == 0, "sort failed");
    mu_assert(is_sorted(words), "didn't sort it");

    DArray_destroy(words);

    return NULL;
}

char *test_qsort()
{
    return run_sort_test(DArray_qsort, "qsort");
}

char *test_heapsort()
{
    return run_sort_test(DArray_heapsort, "heapsort");
}

char *test_mergesort()
{
    return run_sort_test(DArray_mergesort, "mergesort");
}

char *test_custom_mergesort()
{
    // TODO!
    return NULL;
}

char *test_custom_quicksort()
{
    return run_sort_test(DArray_custom_qsort, "custom_qsort");
}

char *test_custom_heapsort()
{
    // TODO!
    return NULL;
}

char *test_find()
{
    DArray *words = create_words();
    mu_assert(words != NULL, "Words could not be created");

    void *rc = DArray_find(words, "werwar", (DArray_compare) testcmp, (DArray_compare) testcmp2);
    mu_assert(is_sorted(words), "Words are not sorted");
    mu_assert(rc != NULL, "Could not find the word in the array");

    rc = DArray_find(words, "test1", (DArray_compare) testcmp, (DArray_compare) testcmp2);
    mu_assert(is_sorted(words), "Words are not sorted");
    mu_assert(rc == NULL, "The word should not be in the array");

    DArray_destroy(words);
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_qsort);
    mu_run_test(test_heapsort);
    mu_run_test(test_mergesort);
    mu_run_test(test_custom_mergesort);
    mu_run_test(test_custom_quicksort);
    mu_run_test(test_custom_heapsort);
    mu_run_test(test_find);

    return NULL;
}

RUN_TESTS(all_tests);
