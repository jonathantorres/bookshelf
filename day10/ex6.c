#include <stdio.h>
#include <string.h>

char *longer(char *s1, char *s2);

int main(int argc, char const *argv[])
{
    char *s1 = "My first message";
    char *s2 = "The second";
    char *longer_string;

    longer_string = longer(s1, s2);

    puts(longer_string);
    return 0;
}

char *longer(char *s1, char *s2)
{
    int s1_length = strlen(s1);
    int s2_length = strlen(s2);

    if (s1_length > s2_length) {
        return s1;
    }

    return s2;
}
