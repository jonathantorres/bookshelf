#include <stdio.h>

int main(int argc, char const *argv[])
{
    char *message[8] = {
        "Four", "score", "and", "seven",
        "years", "ago", "our", "forefathers"
    };
    int count;

    for (count = 0; count < 8; count++) {
        printf("%s ", message[count]);
    }
    printf("\n");
    return 0;
}
