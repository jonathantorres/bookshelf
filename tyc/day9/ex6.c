#include <stdio.h>

// This is one way to initialize the array
int data[] = {0,0,100};

// The other way to initialize it
int data_another[3];

int main(int argc, char const *argv[])
{
    data_another[2] = 100;

    for (int i = 0; i < 3; i++)
    {
        printf("%d\t%d\n", data[i],data_another[i]);
    }
    return 0;
}
