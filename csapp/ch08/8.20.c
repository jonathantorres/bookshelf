#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
    if (execve("/usr/bin/ls", argv, envp) == -1) {
        perror("execv error");
        return 1;
    }

    return 0;
}
