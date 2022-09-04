#include <stdio.h>

unsigned char mychar;

int main(int argc, char const *argv[])
{
    for (mychar = 180; mychar < 204; mychar++) {
        printf("ASCII code %d is character %c\n", mychar, mychar);
    }

    return 0;
}
