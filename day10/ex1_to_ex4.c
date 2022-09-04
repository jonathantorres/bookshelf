#include <stdio.h>
#include <stdlib.h>

char letter = '$';
char msg[100] = "Pointers are fun!";
char *message = "Pointers are fun!";
char input[80];
char *input2;

int main(int argc, char const *argv[])
{
    printf("Enter something: ");
    input2 = malloc(81);
    gets(input2);
    // gets(input);
    // printf("You entered: %s\n", input);
    printf("You entered: %s\n", input2);
    free(input2);
    return 0;
}
