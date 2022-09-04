#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char str1[] = "The first string.";
    char str2[] = "The second string.";

    size_t n, x;

    puts(str1);
    puts(str2);

    while (1) {
        puts("\nEnter number of characters to compare, 0 to exit");
        scanf("%zd", &n);

        if (n <= 0) {
            break;
        }

        x = strncmp(str1, str2, n);

        printf("\nComparing %zu characters, strncmp() returns %zu.", n, x);
    }

    return 0;
}
