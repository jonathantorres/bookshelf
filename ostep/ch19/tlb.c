#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define DEFAULT_PAGESIZE 4
#define DEFAULT_NUMPAGES 100

int main(int argc, char *argv[])
{
    if (argc < 3) {
        puts("usage: tlb <pagesize> <numpages>");
        exit(1);
    }
    int pagesize = atoi(argv[1]);
    int numpages = atoi(argv[2]);
    if (pagesize <= 0) {
        pagesize = DEFAULT_PAGESIZE;
    }
    if (numpages <= 0) {
        numpages = DEFAULT_NUMPAGES;
    }
    struct timeval tp;
    int jump = pagesize / sizeof(int);
    int len = numpages * jump;
    int arr[len];
    for (int i = 0; i < len; i+=jump) {
        arr[i] += 1;
        gettimeofday(&tp, NULL);
        printf("%d\n", tp.tv_usec);
    }
    return 0;
}
