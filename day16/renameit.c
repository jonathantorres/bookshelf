#include <stdio.h>

int main(void)
{
    char oldname[80], newname[80];

    printf("Enter current filename: ");
    gets(oldname);
    printf("Enter new name for file: ");
    gets(newname);

    if (rename(oldname, newname) == 0) {
        printf("%s has been renamed to %s.\n", oldname, newname);
    } else {
        fprintf(stderr, "An error has ocurred renaming %s\n", oldname);
    }

    return 0;
}
