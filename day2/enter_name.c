#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char buffer[256];

    printf("Enter your name and press <Enter>:\n");
    gets(buffer);
    printf("\nYour name has %ld characters and spaces!\n", strlen(buffer));
    return 0;
}
