#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    int pipea[2];
    int pipeb[2];
    cpu_set_t cpu;

    // run program in a single CPU
    CPU_ZERO(&cpu);
    CPU_SET(1, &cpu);

    if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpu) < 0) {
        perror("sched_setaffinity error");
        exit(1);
    }

    if (pipe(pipea) < 0) {
        perror("pipe error");
        exit(1);
    }

    if (pipe(pipeb) < 0) {
        perror("pipe error");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork error");
        exit(1);
    }

    if (pid == 0) {
        // close descriptors the child won't use
        close(pipea[0]);
        close(pipeb[1]);
    } else {
        // close descriptors the parent won't use
        close(pipea[1]);
        close(pipeb[0]);
    }

    char rbuf[0];
    clock_t t1;
    int runs = 1000000;

    // measure only on the parent
    if (pid > 0) {
        t1 = clock();
    }

    for (int i = 0; i < runs; ++i) {
        if (pid == 0) {
            // child
            if (write(pipea[1], NULL, 0) < 0) {
                perror("write error");
                exit(1);
            }

            int r = read(pipeb[0], rbuf, 0);

            if (r < 0) {
                perror("read error");
                exit(1);
            }
        } else {
            // parent
            int r = read(pipea[0], rbuf, 0);

            if (r < 0) {
                perror("read error");
                exit(1);
            }

            if (write(pipeb[1], NULL, 0) < 0) {
                perror("write error");
                exit(1);
            }
        }
    }

    // the parent waits for the child and prints the results
    if (pid > 0) {
        clock_t t2      = clock();
        double duration = (1000000.0 * (t2 - t1) / CLOCKS_PER_SEC) / (double)runs;

        printf("results: %.5f μs\n", duration);

        if (wait(NULL) < 0) {
            perror("wait error");
            exit(1);
        }
    }

    return 0;
}
