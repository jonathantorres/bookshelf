#include <stdio.h>
#include <dlfcn.h>
#include "dbg.h"

typedef int (*lib_function) (const char *data);

char *lib_file = "build/libex29.so";

int test_print_a_message(void *lib)
{
    char *func_to_run = "print_a_message";
    char *data = "This is a message";

    lib_function func = dlsym(lib, func_to_run);
    check(func != NULL, "Did not find %s function in the library %s: %s", func_to_run, lib_file, dlerror());

    int rc = func(data);
    check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);

    return 0;

error:
    return -1;
}

int test_uppercase(void *lib)
{
    char *func_to_run = "uppercase";
    char *data = "Jonathan";

    lib_function func = dlsym(lib, func_to_run);
    check(func != NULL, "Did not find %s function in the library %s: %s", func_to_run, lib_file, dlerror());

    int rc = func(data);
    check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);

    return 0;

error:
    return -1;
}

int main()
{
    int rc = 0;

    void *lib = dlopen(lib_file, RTLD_NOW);
    check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());

    rc = test_print_a_message(lib);
    check(rc == 0, "Print a message failed!");

    rc = test_uppercase(lib);
    check(rc == 0, "Print uppercase failed!");

    rc = dlclose(lib);
    check(rc == 0, "Failed to close %s", lib_file);

    return 0;

error:
    return -1;
}
