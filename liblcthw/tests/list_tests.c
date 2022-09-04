#include "minunit.h"
#include "lcthw/list.h"
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create()
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}

char *test_destroy()
{
    List_clear_destroy(list);

    return NULL;
}

char *test_push_pop()
{
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value.");

    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_unshift()
{
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong first value.");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong first value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    char *val = List_remove(list, list->first->next);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");

    return NULL;
}

char *test_shift()
{
    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong count after shift.");

    return NULL;
}

char *test_copy()
{
    List *cur_list = List_create();
    int val1 = 100;
    int val2 = 200;
    int val3 = 300;

    List_push(cur_list, &val1);
    List_push(cur_list, &val2);
    List_push(cur_list, &val3);

    List *list_copy = List_copy(cur_list);
    mu_assert(list_copy != NULL, "List copy must not be NULL.");
    mu_assert(List_count(list_copy) == 3, "List copy must have 3 integers.");
    mu_assert(List_first(list_copy) == &val1, "First item in list must be &val1");
    mu_assert(List_last(list_copy) == &val3, "Last item in list must be &val3");

    return NULL;
}

char *test_join()
{
    List *list1 = List_create();
    int val1 = 100;
    int val2 = 200;
    int val3 = 300;

    List_push(list1, &val1);
    List_push(list1, &val2);
    List_push(list1, &val3);

    List *list2 = List_create();
    int val4 = 400;
    int val5 = 500;
    int val6 = 600;

    List_push(list2, &val4);
    List_push(list2, &val5);
    List_push(list2, &val6);

    List *joined_list = List_join(list1, list2);
    mu_assert(joined_list != NULL, "List copy must not be NULL.");
    mu_assert(List_count(joined_list) == 6, "List copy must have 6 integers.");
    mu_assert(List_first(joined_list) == &val1, "First item in list must be &val1");
    mu_assert(List_last(joined_list) == &val6, "Last item in list must be &val6");

    return NULL;
}

char *test_split()
{
    List *list = List_create();
    int val1 = 1;
    int val2 = 2;
    int val3 = 3;
    int val4 = 4;
    List_push(list, &val1);
    List_push(list, &val2);
    List_push(list, &val3);
    List_push(list, &val4);

    List **list_split = List_split(list);
    mu_assert(list_split != NULL, "Splitted list must not be NULL.");
    mu_assert(list_split[0] != NULL, "First splitted list must not be NULL.");
    mu_assert(list_split[1] != NULL, "Second splitted list must not be NULL.");
    mu_assert(List_count(list_split[0]) == 2, "List must have 2 integers.");
    mu_assert(List_count(list_split[1]) == 2, "List must have 2 integers.");
    mu_assert(List_first(list_split[0]) == &val1, "First item in list_split[0] must be &val1.");
    mu_assert(List_last(list_split[0]) == &val2, "Last item in list_split[0] must be &val2.");
    mu_assert(List_first(list_split[1]) == &val3, "First item in list_split[1] must be &val3.");
    mu_assert(List_last(list_split[1]) == &val4, "Last item in list_split[1] must be &val4.");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);
    mu_run_test(test_copy);
    mu_run_test(test_join);
    mu_run_test(test_split);

    return NULL;
}

RUN_TESTS(all_tests);
