#include <stdio.h>
#include <time.h>

void sleep(int nbr_seconds);

int main(void)
{
    puts("start sleep(5);");
    sleep(5);
    puts("end sleep(5);");

    return 0;
}

void sleep(int seconds)
{
    clock_t goal;

    goal = (seconds * CLOCKS_PER_SEC) + clock();

    while (goal > clock()) {
        ;
    }
}
