#include <stdio.h>

char input[81];

int main(int argc, char const *argv[])
{
    puts("Enter some text, then press Enter: ");
    gets(input);
    printf("You entered: %s\n", input);

    return 0;
}
