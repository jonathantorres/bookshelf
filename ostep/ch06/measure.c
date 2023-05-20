#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    char *buf = "Jonathan\n";
    printf("clock: %ld\n", clock());
    write(STDOUT_FILENO, buf, strlen(buf));
    printf("clock: %ld\n", clock());
    return 0;
}
