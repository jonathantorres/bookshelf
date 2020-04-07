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
        if (rc == 0) {
            printf("Filename: %s\n", argv[i]);
            printf("File serial number (ino): %lld\n", st.st_ino);
            printf("Filesize: %lld bytes\n", st.st_size);
            printf("Blocks allocated: %lld\n", st.st_blocks);
            printf("Reference link count: %d\n", st.st_nlink);
            printf("\n");
        } else {
            printf("ERROR: could not process %s\n", argv[i]);
        }
    }
    return 0;
}
