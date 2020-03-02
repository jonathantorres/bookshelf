#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char input[40];

    while (1) {
        puts("\nInput the desired system command, blank to exit");
        gets(input);

        if (input[0] == '\0') {
            exit(0);
        }

        system(input);
    }

    return 0;
}
