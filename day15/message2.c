#include <stdio.h>

void print_strings(char *p[], int n);

int main(int argc, char const *argv[])
{
    char *message[8] = {
        "Four", "score", "and", "seven",
        "years", "ago", "our", "forefathers"
    };

    print_strings(message, 8);
    return 0;
}

void print_strings(char *p[], int n)
{
    int count;

    for (count = 0; count < n; count++) {
        printf("%s ", p[count]);
    }
    printf("\n");
}
