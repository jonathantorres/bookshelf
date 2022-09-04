#include <stdio.h>

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 100; i++) {
        continue;
    }

    printf("Hello!\n");
    return 0;
}
