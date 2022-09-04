#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *loc, buf1[80], buf2[80];

    printf("Enter the string to be searched: ");
    gets(buf1);
    printf("Enter the target string: ");
    gets(buf2);

    loc = strstr(buf1, buf2);

    if (loc == NULL) {
        printf("Not match was found.\n");
    } else {
        printf("%s was found at position %zu.\n", buf2, loc - buf1);
    }

    return 0;
}
