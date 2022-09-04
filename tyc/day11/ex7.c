#include <stdio.h>

typedef struct {
    char *address1;
    char *address2;
    char *city;
    char *state;
    char *zip;
} record;

int main(int argc, char const *argv[])
{
    record myaddress = {
        "Coral Way 123",
        "",
        "Ft. Lauderdale",
        "Florida",
        "33309",
    };

    printf("%s\n", myaddress.zip);
    return 0;
}
