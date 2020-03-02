#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char buf1[80], buf2[80];
    size_t loc;

    printf("Enter the string to be searched: ");
    gets(buf1);
    printf("Enter the string containing target characters: ");
    gets(buf2);

    loc = strspn(buf1, buf2);

    if (loc == 0) {
        printf("Not match was found.\n");
    } else {
        printf("Characters match up to position %zu.\n", loc-1);
    }

    return 0;
}
