#include <stdio.h>
#include <unistd.h>

int menu(void);

int main(int argc, char const *argv[])
{
    int choice;

    while(1) {
        choice = menu();

        if (choice == 1) {
            puts("\nExecuting task A...");
            sleep(5);
        } else if (choice == 2) {
            puts("\nExecuting task B...");
            sleep(5);
        } else if (choice == 3) {
            puts("\nExecuting task C...");
            sleep(5);
        } else if (choice == 4) {
            puts("\nExecuting task D...");
            sleep(5);
        } else if (choice == 5) {
            puts("\nExiting program now...\n");
            sleep(5);
            break;
        } else {
            puts("\nInvalid choice, try again.");
            sleep(5);
        }
    }

    return 0;
}

int menu(void)
{
    int reply;

    puts("\nEnter 1 for task A.");
    puts("Enter 2 for task B.");
    puts("Enter 3 for task C.");
    puts("Enter 4 for task D.");
    puts("Enter 5 to exit the program.");

    scanf("%d", &reply);

    return reply;
}
