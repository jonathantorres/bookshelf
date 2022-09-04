#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char dest[] = "..........................";
    char source[] = "abcdefghijklmnopqrstuvwxyz";

    size_t n;

    while (1) {
        puts("Enter the number of characters to copy (1-26)");
        scanf("%zd", &n);

        if (n > 0 && n < 27) {
            break;
        }
    }

    printf("Before strncpy destination = %s\n", dest);
    strncpy(dest, source, n);
    printf("After strncpy destination = %s\n", dest);
    return 0;
}
