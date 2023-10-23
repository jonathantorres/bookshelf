#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("usage: hex2dd <hex>\n");
        return 1;
    }

    char buf[255];
    char *hex_str = argv[1];
    uint32_t hex  = 0x0;

    if (strlen(hex_str) > 8) {
        // discard the 0x
        hex_str += 2;
    }

    sscanf(hex_str, "%x", &hex);
    hex = htonl(hex);

    const char *res = inet_ntop(AF_INET, &hex, buf, 255);

    if (!res) {
        perror("inet_ntop error");
        return 1;
    }

    printf("%s\n", res);

    return 0;
}
