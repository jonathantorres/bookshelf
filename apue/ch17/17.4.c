#include "apue.h"

int buf_args(char *buf, int (*optfunc)(int, char **));
int print_args(int argc, char *argv[]);

#define MAXARGC 50      /* max number of arguments in buf */
#define WHITE   " \t\n" /* white space for tokenizing arguments */

int main(void)
{
    char *buf = malloc(MAXLINE);

    strcpy(buf, "this is a test");

    if (buf_args(buf, print_args) < 0) {
        err_sys("buf_args error");
    }

    return 0;
}

/*
 * buf[] contains white-space-separated arguments.  We convert it to an
 * argv-style array of pointers, and call the user's function (optfunc)
 * to process the array.  We return -1 if there's a problem parsing buf,
 * else we return whatever optfunc() returns.  Note that user's buf[]
 * array is modified (nulls placed after each token).
 */
int buf_args(char *buf, int (*optfunc)(int, char **))
{
    char *ptr;
    int argc;

    int argv_len = MAXARGC;
    char **argv  = calloc(argv_len, sizeof(char *));

    if (argv == NULL) {
        return -1;
    }

    if (strtok(buf, WHITE) == NULL) /* an argv[0] is required */
        return -1;

    argv[argc = 0] = buf;

    while ((ptr = strtok(NULL, WHITE)) != NULL) {
        if (++argc >= argv_len - 1) { /* -1 for room for NULL at end */
            argv_len *= 2;
            argv = realloc(argv, argv_len * sizeof(char *));

            if (argv == NULL) {
                return -1;
            }
        }
        argv[argc] = ptr;
    }

    argv[++argc] = NULL;

    /*
     * Since argv[] pointers point into the user's buf[],
     * user's function can just copy the pointers, even
     * though argv[] array will disappear on return.
     */
    int ret = ((*optfunc)(argc, argv));
    free(argv);

    return ret;
}

int print_args(int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i) {
        printf("%d: %s\n", i, argv[i]);
    }

    return 0;
}
