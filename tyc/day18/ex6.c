#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

char *concat(int num, ...);

int main(int argc, char const *argv[])
{
    char str1[] = "Hi, ";
    char str2[] = "My name is ";
    char str3[] = "Jonathan Torres ";
    char str4[] = "and this is jackass!";
    char *msg;

    msg = concat(4, str1, str2, str3, str4);

    puts(msg);
    return 0;
}

char *concat(int num, ...)
{
    va_list args_ptr;
    int size = 0;
    char *str;

    // calculate the size of the total string
    va_start(args_ptr, num);
    for (int i = 0; i < num; i++) {
        char *current_str = va_arg(args_ptr, char*);
        size += strlen(current_str);
    }
    va_end(args_ptr);

    // allocate space for it
    str = (char*)malloc(size + 1);

    if (str == NULL) {
        puts("Error: Not enough memory for the string.");
        exit(1);
    }

    str[0] = '\0';

    // concatenate the strings
    va_start(args_ptr, num);
    for (int i = 0; i < num; i++) {
        char *current_str = va_arg(args_ptr, char*);
        strcat(str, current_str);
    }
    va_end(args_ptr);

    return str;
}
