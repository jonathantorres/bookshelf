#include "minunit.h"
#include "lcthw/darray.h"
#include "lcthw/darray_algos.h"
#include <stdlib.h>

static DArray *array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

int testcmp(int **a, int **b)
{
    return **a - **b;
}

int is_sorted(DArray *array)
{
    int i = 0;

    for (i = 0; i < DArray_count(array) - 1; i++) {
        if (*((int *)DArray_get(array, i)) > *((int*)DArray_get(array, i + 1))) {
            return 0;
        }
    }

    return 1;
}

char *test_create()
{
    array = DArray_create(sizeof(int), 100);
    mu_assert(array != NULL, "DArray_create failed");
    mu_assert(array->contents != NULL, "contents are wrong in darray");
    mu_assert(array->end == 0, "end isn't at the right spot");
    mu_assert(array->element_size == sizeof(int), "element size is wrong");
    mu_assert(array->max == 100, "wrong max length on initial size");

    return NULL;
}

char *test_destroy()
{
    DArray_destroy(array);

    return NULL;
}

char *test_new()
{
    val1 = DArray_new(array);
    mu_assert(val1 != NULL, "failed to make a new element");

    val2 = DArray_new(array);
    mu_assert(val2 != NULL, "failed to make a new element");

    return NULL;
}

char *test_set()
{
    DArray_set(array, 0, val1);
    DArray_set(array, 1, val2);

    return NULL;
}

char *test_get()
{
    mu_assert(DArray_get(array, 0) == val1, "Wrong first value");
    mu_assert(DArray_get(array, 1) == val2, "Wrong second value");

    return NULL;
}

char *test_remove()
{
    int *val_check = DArray_remove(array, 0);
    mu_assert(val_check != NULL, "Should not get NULL");
    mu_assert(*val_check == *val1, "Should get the first value");
    mu_assert(DArray_get(array, 0) == NULL, "Should be gone");
    DArray_free(val_check);

    val_check = DArray_remove(array, 1);
    mu_assert(val_check != NULL, "Should not get NULL");
    mu_assert(*val_check == *val2, "Should get the second value");
    mu_assert(DArray_get(array, 1) == NULL, "Should be gone");
    DArray_free(val_check);

    return NULL;
}

char *test_expand_contract()
{
    int old_max = array->max;
    DArray_expand(array);
    mu_assert((unsigned int)array->max == old_max + array->expand_rate, "Wrong size after expand");

    DArray_contract(array);
    mu_assert((unsigned int)array->max == array->expand_rate + 1, "Should stay at the same expand rate at least");

    DArray_contract(array);
    mu_assert((unsigned int)array->max == array->expand_rate + 1, "Should stay at the same expand rate at least");

    return NULL;
}

char *test_push_pop()
{
    int i = 0;
    for (i = 0; i < 1000; i++) {
        int *val = DArray_new(array);
        *val = i * 333;
        DArray_push(array, val);
    }

    mu_assert(array->max == 1201, "Wrong max size");

    for (i = 999; i >= 0; i--) {
        int *val = DArray_pop(array);
        mu_assert(val != NULL, "Shouldn't get a NULL");
        mu_assert(*val == i * 333, "Wrong value");
        DArray_free(val);
    }

    return NULL;
}

char *test_push_sorted()
{
    DArray *numbers = DArray_create(sizeof(int), 10);
    int nums_to_push[10] = {
        3, 5, 7, 1, 2,
        32, 55, 17, 11, 9,
    };

    for (int i = 0; i < 10; i++) {
        int *val = DArray_new(numbers);
        *val = nums_to_push[i];
        DArray_push_sorted(numbers, val, (DArray_compare) testcmp);
    }

    mu_assert(is_sorted(numbers), "Numbers are not sorted");
    mu_assert(DArray_count(numbers) == 10, "Wrong count of numbers");
    DArray_destroy(numbers);

    return NULL;
}

char *test_print()
{
    DArray *nums = DArray_create(sizeof(int), 10);

    for (int i = 0; i < 10; i++) {
        int *val = DArray_new(nums);
        *val = i * 999;
        DArray_push(nums, val);
    }

    DArray_print(nums, 'i');
    DArray_destroy(nums);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_new);
    mu_run_test(test_set);
    mu_run_test(test_get);
    mu_run_test(test_remove);
    mu_run_test(test_expand_contract);
    mu_run_test(test_push_pop);
    mu_run_test(test_push_sorted);
    mu_run_test(test_destroy);
    mu_run_test(test_print);

    return NULL;
}

RUN_TESTS(all_tests);
