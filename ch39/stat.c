#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        puts("usage: ./stat filename");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < argc; i++) {
        struct stat st;
        int rc = stat(argv[i], &st);
        assert(rc == 0);
        printf("rc=%d\n", rc);
        printf("ino=%ld\n", st.st_ino);
        printf("filename given: %s\n", argv[i]);
    }
    return 0;
}
