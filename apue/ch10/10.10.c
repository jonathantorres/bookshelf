#include "apue.h"
#include <time.h>

int main(void)
{
    int i = 0;

    while (1) {
        i++;

        if (i % 5 == 0) {
            time_t t         = time(NULL);
            struct tm *local = localtime(&t);

            printf("%d\n", local->tm_sec);
        }

        sleep(60);
    }

    return 0;
}
