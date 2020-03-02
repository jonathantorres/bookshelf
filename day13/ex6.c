#include <stdio.h>

int main(int argc, char const *argv[])
{
    int choice = 1;

    if (choice == 1) {
        printf("You answered 1\n");
    } else if  (choice == 2) {
        printf("You answered 2\n");
    } else {
        printf("You did not choose 1 or 2\n");
    }

    return 0;
}
