#include <stdio.h>
#include <string.h>

int main(void)
{
    char first_name[80];
    char middle_name[80];
    char last_name[80];

    printf("Please enter your first name: ");
    gets(first_name);
    printf("Please enter your middle name: ");
    gets(middle_name);
    printf("Please enter your last name: ");
    gets(last_name);

    printf("%c. %c. %s\n", first_name[0], middle_name[0], last_name);

    return 0;
}
