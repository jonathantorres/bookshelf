#include "csapp.h"

int main(int argc, char **argv)
{
    struct stat stat;
    char *type, *readok;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <fd>\n", argv[0]);
        return 1;
    }

    Fstat(atoi(argv[1]), &stat);

    /* Determine file type */
    if (S_ISREG(stat.st_mode)) {
        type = "regular";
    } else if (S_ISDIR(stat.st_mode)) {
        type = "directory";
    } else {
        type = "other";
    }

    /* Check read access */
    if ((stat.st_mode & S_IRUSR)) {
        readok = "yes";
    } else {
        readok = "no";
    }

    printf("type: %s, read: %s\n", type, readok);

    return 0;
}
