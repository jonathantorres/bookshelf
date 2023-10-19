#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "You must specify one file to copy\n");
        return 1;
    }

    char *file = argv[1];
    int fd     = open(file, O_RDWR);
    struct stat buf;
    size_t size = 0;

    if (fd < 0) {
        perror("open error");
        return 1;
    }

    if (fstat(fd, &buf) < 0) {
        perror("fstat error");
        return 1;
    }

    size = buf.st_size;

    char *p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (p == MAP_FAILED) {
        perror("mmap error");
        return 1;
    }

    *p = 'J';

    if (munmap(p, size) < 0) {
        perror("munmap error");
        return 1;
    }

    close(fd);

    return 0;
}
