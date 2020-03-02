#include <stdio.h>
#include <stdlib.h>

struct kilo {
    struct kilo *next;
    char dummy[1020];
};

int FreeMem(void);

int main(void)
{
    printf("You have %d kilobytes free.\n", FreeMem());
    return 0;
}

int FreeMem(void)
{
    long counter;
    struct kilo *head, *current, *nextone;

    current = head = (struct kilo*) malloc(sizeof(struct kilo));

    if (head == NULL) {
        return 0;
    }

    counter = 0;

    do {
        counter++;
        current->next = (struct kilo*) malloc(sizeof(struct kilo));
        current = current->next;
        printf("\r%ld", counter);
    } while (current != NULL);

    current = head;

    do {
        nextone = current->next;
        free(current);
        current = nextone;
    } while (nextone != NULL);

    return counter;
}
