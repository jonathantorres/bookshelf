#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sleep(int nbr_seconds);

int main(int argc, char const *argv[])
{
    int ctr;
    int wait = 5;

    printf("Delay for %d seconds\n", wait);
    printf(">");

    for (ctr = 1; ctr <= wait; ctr++) {
        printf(".");
        fflush(stdout);
        sleep((int) 1);
    }

    printf("Done!\n");

    return 0;
}

void sleep(int nbr_seconds)
{
    clock_t goal;

    goal = (nbr_seconds * CLOCKS_PER_SEC) + clock();

    while(goal > clock()) {
        ;
    }
}
