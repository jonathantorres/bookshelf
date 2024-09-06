#include "apue.h"
#include <time.h>

int main(void)
{
    char buf[MAXLINE];
    time_t t = time(NULL);

    if (strftime(buf, sizeof(buf), "%a %b %e %I:%M:%S %p %Z %Y", localtime(&t)) <= 0) {
        err_quit("error writing the current date");
    }

    printf("%s\n", buf);

    return 0;
}
