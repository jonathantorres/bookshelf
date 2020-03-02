#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *loc, buf[80];
    int ch;

    printf("Enter the string to be searched: ");
    gets(buf);
    printf("Enter the character to search for: ");
    ch = getchar();

    loc = strchr(buf, ch);

    if (loc == NULL) {
        printf("The character %c was not found.\n", ch);
    } else {
        printf("The character %c was found at position %d.\n", ch, loc);
    }

    return 0;
}
