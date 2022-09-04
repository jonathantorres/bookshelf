#include "udp.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [hostname]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sfd = udp_open(argv[1], "10000", 0);
    ssize_t read_bytes;
    char buf[BUFFER_SIZE] = "hello!";

    for (size_t i = 0; i < 2; i++) {
        printf("Send: %s\n", buf);
        if (udp_write(sfd, buf, strlen(buf), NULL, 0) != (ssize_t)strlen(buf)) {
            fprintf(stderr, "partial/failed write\n");
            exit(EXIT_FAILURE);
        }

        read_bytes = udp_read(sfd, buf, NULL, 0);
        if (read_bytes == -1) {
            perror("udp_read() failed");
            exit(EXIT_FAILURE);
        }

        printf("Received %zd bytes: %s\n", read_bytes, buf);
        strncpy(buf, "hello", 6);
    }

    close(sfd);
    close_sem();
    exit(EXIT_SUCCESS);
}
