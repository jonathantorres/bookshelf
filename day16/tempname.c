#include <stdio.h>

int main(void)
{
    char buffer[10], *c;

    tempnam(buffer, buffer);
    c = tempnam(NULL, NULL);

    printf("Temporary name 1: %s\n", buffer);
    printf("Temporary name 2: %s\n", c);

    return 0;
}
