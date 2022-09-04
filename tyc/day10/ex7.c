#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate(char *s1, char *s2);

int main(int argc, char const *argv[])
{
    char *s1 = "Hello,";
    char *s2 = "World";
    char *msg;

    msg = concatenate(s1, s2);

    printf("%s\n", msg);

    free(msg);

    return 0;
}

char *concatenate(char *s1, char *s2)
{
    char *new_string = malloc(
        (strlen(s1) * sizeof(char)) + (strlen(s2) * sizeof(char))
    );

    if (new_string == NULL) {
        puts("Memory allocation error. Not enough memory.");
        exit(1);
    }

    for (int i = 0; i < strlen(s1); i++) {
        new_string[i] = s1[i];
    }

    for (int i = 0; i < strlen(s2); i++) {
        new_string[i + strlen(s1)] = s2[i];
    }

    return new_string;
}
