#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("usage: dd2hex <ip>\n");
        return 1;
    }

    struct in_addr addr;
    char *ip_str = argv[1];

    int res = inet_pton(AF_INET, ip_str, &addr);

    if (res != 1) {
        perror("inet_ntop error");
        return 1;
    }

    printf("0x%x\n", ntohl(addr.s_addr));

    return 0;
}
