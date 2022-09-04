#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    size_t length;
    char buf[80];

    while (1) {
        puts("Enter a line of text, a blank line to exit.");
        gets(buf);

        length = strlen(buf);

        if (length != 0) {
            printf("\nThat line is %zu characters long.\n", length);
        } else {
            break;
        }
    }

    return 0;
}
