#include <stdio.h>

int main()
{
    int ages[] = {12, 55, 23, 82, 45};
    char *names[] = {
        "Chris", "John", "George",
        "Melissa", "Marty",
    };

    // using array index notation
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }

    printf("----- \n");

    // using pointer math
    int *cur_age = ages;
    char **cur_name = names;

    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n", *(cur_name + i), *(cur_age + i));
    }

    printf("----- \n");

    // using pointers as arrays
    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n", cur_name[i], cur_age[i]);
    }

    printf("----- \n");

    // another stupid and complicated way
    for (cur_age = ages, cur_name = names; (cur_age - ages) < count; cur_age++, cur_name++) {
        printf("%s has %d years alive.\n", *cur_name, *cur_age);
    }

    printf("----- \n");

    // break it: from end to beginning
    cur_age = ages + (count - 1);
    cur_name = names + (count - 1);

    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n", *(cur_name--), *(cur_age--));
    }

    return 0;
}
