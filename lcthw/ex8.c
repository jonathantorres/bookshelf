#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        puts("You only have one argument, you suck.");
    } else if (argc > 2 && argc < 4) {
        puts("Here's your arguments:");
        for (int i = 0; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
    } else {
        puts("You have too many arguments, you suck.");
    }

    return 0;
}
