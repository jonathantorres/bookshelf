#include "apue.h"

void update_and_write();

int main(void)
{
    FILE *f = fopen("sync.txt", "w");

    if (!f) {
        err_sys("fopen error");
    }

    char buf[1] = {'0'};

    fwrite(buf, sizeof(buf), 1, f);
    fclose(f);

    int rc = fork();

    if (rc < 0) {
        err_sys("fork error");
    }

    if (rc == 0) {
        // child
        update_and_write();
        exit(EXIT_SUCCESS);
    } else {
        // parent
        update_and_write();
    }

    return 0;
}

void update_and_write()
{
    FILE *f = fopen("sync.txt", "w");

    if (!f) {
        err_sys("fopen error");
    }

    char buf[2] = {0, 0};
    fread(buf, sizeof(buf), 1, f);

    int v = atoi(buf);
    v += 1;

    char buf2[1] = {'0'};
    buf2[0]      = (char)v;

    fwrite(buf2, sizeof(buf2), 1, f);
    fclose(f);
}
