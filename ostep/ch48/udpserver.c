#define _GNU_SOURCE
#define _DARWIN_C_SOURCE

#include "udp.h"

int main(void)
{
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;
    ssize_t bytes_read;
    char buf[BUFFER_SIZE];
    int success;
    int sfd = udp_open(NULL, "10000", 1);
    assert(sfd > -1);

    while (1) {
        peer_addr_len = sizeof(struct sockaddr_storage);
        bytes_read = udp_read(sfd, buf, (struct sockaddr *) &peer_addr, &peer_addr_len);
        if (bytes_read == -1) {
            continue;
        }

        char host[NI_MAXHOST];
        char service[NI_MAXSERV];
        success = getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV);

        if (success == 0) {
            printf("Received %zd bytes from %s:%s: %s\n", bytes_read, host, service, buf);
        } else {
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(success));
        }
    }
}
