#include <stdio.h>

char my_char = 7;
char *char_ptr;

int main(int argc, char const *argv[])
{
    char_ptr = &my_char;
    printf("Character is: %d\n", my_char);
    printf("Character is: %d\n", *char_ptr);
    return 0;
}
