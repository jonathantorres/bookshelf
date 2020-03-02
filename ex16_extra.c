#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person Person_create(char *name, int age, int height, int weight)
{
    struct Person who;
    who.name = name;
    who.age = age;
    who.height = height;
    who.weight = weight;

    return who;
}

void Person_print(struct Person who)
{
    printf("Name: %s\n", who.name);
    printf("Age: %d\n", who.age);
    printf("Height: %d\n", who.height);
    printf("Weight: %d\n", who.weight);
}

int main()
{
    // make two people structures
    struct Person john = Person_create("Jonathan Torres", 33, 65, 165);
    struct Person george = Person_create("George Torres", 36, 64, 175);

    // print them out and where they are in memory
    printf("John is at memory location: %p\n", &john);
    Person_print(john);
    printf("George is at memory location: %p\n", &george);
    Person_print(george);

    // make every person age 20 more years and print them again
    john.age += 20;
    john.height -= 2;
    john.weight += 40;
    Person_print(john);

    george.age += 20;
    george.weight += 20;
    Person_print(george);

    return 0;
}
