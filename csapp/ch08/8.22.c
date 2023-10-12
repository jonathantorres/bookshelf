#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int mysystem(char *command)
{
    pid_t pid;
    int status;

    if ((pid = fork()) == 0) {
        char *argv[4] = {"", "-c", command, NULL};

        if (execve("/bin/sh", argv, NULL) == -1) {
            exit(1);
        }
    }

    if (waitpid(pid, &status, 0) > 0) {
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }

        if (WIFSIGNALED(status)) {
            return WTERMSIG(status);
        }
    }
}

int main(int argc, char **argv)
{
    return mysystem(argv[1]);
}
