#include <stdio.h>
#include <stdlib.h>

int display_menu(void);

int main(int argc, char const *argv[])
{
    int option = display_menu();

    while (option < 5 && option > 0) {
        switch (option) {
            case 1:
                system("ls");
                break;
            case 2:
                system("ls -al");
                break;
            case 3:
                system("whoami");
                break;
            case 4:
                system("which php");
                break;
        }

        option = display_menu();
    }

    puts("Exiting...");

    return 0;
}

int display_menu(void)
{
    int option = 0;

    puts("Welcome to the menu, here are your options.");
    puts("[1] Execute ls");
    puts("[2] Execute ls -al");
    puts("[3] Execute whoami");
    puts("[4] Execute which php");
    puts("[5] Quit");

    printf("Choose an option: ");
    scanf("%d", &option);

    return option;
}
