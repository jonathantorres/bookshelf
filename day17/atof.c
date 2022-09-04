#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char buf[80];
    double d;

    while (1) {
        printf("\nEnter the string to convert, (blank to exit): ");
        gets(buf);

        if (strlen(buf) == 0) {
            break;
        }

        d = atof(buf);

        printf("The converted value id %f.\n", d);
    }

    return 0;
}
