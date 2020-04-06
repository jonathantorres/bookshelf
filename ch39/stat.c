#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    struct stat st;
    int rc = stat("answers.md", &st);
    // assert(rc == 0);
    printf("rc=%d\n", rc);
    printf("ino=%ld\n", st.st_ino);
    return 0;
}
