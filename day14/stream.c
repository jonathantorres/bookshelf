#include <stdio.h>

int main(int argc, char const *argv[])
{
    char buffer[256];

    puts(gets(buffer));

    return 0;
}
