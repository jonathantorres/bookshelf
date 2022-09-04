#include <stdio.h>

void func1(void (*ptr)(void));
void one(void);
void two(void);
void other(void);

int main(int argc, char const *argv[])
{
    void (*ptr)(void);
    int nbr;

    for (;;) {
        puts("Enter an integer between 1 and 10, 0 to exit: ");
        scanf("%d", &nbr);

        if (nbr == 0) {
            break;
        } else if (nbr == 1) {
            ptr = one;
        } else if (nbr == 2) {
            ptr = two;
        } else {
            ptr = other;
        }

        func1(ptr);
    }

    return 0;
}

void func1(void (*ptr)(void))
{
    ptr();
}

void one(void)
{
    puts("You entered 1.");
}

void two(void)
{
    puts("You entered 2.");
}

void other(void)
{
    puts("You entered something other than 1 or 2.");
}
