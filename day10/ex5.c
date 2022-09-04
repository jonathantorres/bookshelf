#include <stdio.h>
#include <stdlib.h>

char *copy_array(char *source_array);

int main(int argc, char const *argv[])
{
    char *msg = "Jonathan Torres";
    char *msg_copy = copy_array(msg);

    puts(msg);
    puts(msg_copy);

    return 0;
}

char *copy_array(char *source_array)
{
    char *dest_array = malloc(80 * sizeof(char));

    for (int i = 0; i < 16; i++) {
        dest_array[i] = source_array[i];
    }

    return dest_array;
}
