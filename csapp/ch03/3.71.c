#include <stdio.h>

int good_echo()
{
    char buf[8];

    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        printf("%s", buf);
    }

    if (!feof(stdin)) {
        return 0;
    }

    return 1;
}

int main()
{
    if (!good_echo()) {
        return 1;
    }

    return 0;
}
