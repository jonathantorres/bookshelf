#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct data {
    char name[20];
    struct data *next;
};

typedef struct data PERSON;
typedef PERSON *LINK;

int main(void)
{
    LINK head = NULL;
    LINK new = NULL;
    LINK current = NULL;

    // Add the first element
    new = (LINK)malloc(sizeof(PERSON));
    new->next = head;
    head = new;
    strcpy(new->name, "Abigail");

    // add an element to the end of the list
    current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    new = (LINK)malloc(sizeof(PERSON));
    current->next = new;
    new->next = NULL;
    strcpy(new->name, "Carolyn");

    // add a new element at the second position in the list
    new = (LINK)malloc(sizeof(PERSON));
    new->next = head->next;
    head->next = new;
    strcpy(new->name, "Beatrice");

    // Print all data items in order
    current = head;
    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }

    return 0;
}
