#include <stdio.h>

int main(int argc, char const *argv[])
{
    char string[31];
    char ch;
    int ctr = 0;

    while ((ch = getchar()) != '\n' && ctr < 30) {
        if (ch == '*') {
            break;
        }

        string[ctr++] = ch;
    }
    string[ctr] = '\0';
    puts(string);
    return 0;
}
