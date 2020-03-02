#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char buf[80], *message;

    puts("Enter a line of text.");
    gets(buf);

    message = realloc(NULL, strlen(buf) + 1);
    strcpy(message, buf);

    puts(message);

    puts("Enter another line of text.");
    gets(buf);

    message = realloc(message, (strlen(message) + strlen(buf) + 1));
    strcat(message, buf);

    puts(message);
    return 0;
}
