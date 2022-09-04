#include <stdio.h>
#include <string.h>

int main(void)
{
    char message[] = "Jonathan Torres De Jesus";
    char message_copy[strlen(message) + 1];
    char search[] = "es";
    char *loc;
    int times = 0;
    int index = 0;

    strcpy(message_copy, message);

    while ((loc = strstr(message_copy, search)) != NULL) {
        times++;
        index = loc - message_copy;

        for (int i = index; i < (strlen(search) + index); i++) {
            message_copy[i] = ' ';
        }
    }

    printf("The string %s appears %d times in %s\n", search, times, message);
    return 0;
}
