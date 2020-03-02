#include <stdio.h>

int main(int argc, char const *argv[])
{
    char buffer[255];
    int current_line = 1;

    while (fgets(buffer, 255, stdin) != NULL) {
        fprintf(stdout, "%d: ", current_line++);
        fprintf(stdout, "%s", buffer);
    }

    return 0;
}
