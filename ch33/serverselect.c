#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

#define ONE_MILLION 1000000
#define BUFFSIZE 1024
#define PORT 9999
#define LISTEN_BACKLOG 80

int main(int argc, char * argv[]) {
    int sfd;
    struct sockaddr_in my_addr, peer_addr;
    socklen_t peer_addr_size;
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket() An error ocurred");
        exit(1);
    }

    int test_reqs, num_reqs = 0, open_reqs = 0;
    struct timeval start, end;
    if (argc == 2) {
        test_reqs = atoi(argv[1]);
    }

    memset(&my_addr, 0, sizeof(struct sockaddr_in));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    int reuse_addr = 1;
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int)) < 0) {
        perror("server: setsockopt()");
        close(sfd);
        exit(1);
    }

    if (bind(sfd, (struct sockaddr*) &my_addr, sizeof(struct sockaddr_in)) < 0) {
        perror("bind() An error ocurred");
        exit(1);
    }
    if (listen(sfd, LISTEN_BACKLOG) < 0) {
        perror("listen() An error ocurred");
        exit(1);
    }

    peer_addr_size = sizeof(struct sockaddr_in);
    char buff[BUFFSIZE];
    fd_set afds, rfds;
    FD_ZERO(&afds);
    FD_SET(sfd, &afds);
    while (1) {
        rfds = afds;
        if (select(FD_SETSIZE, &rfds, NULL, NULL, NULL) < 0) {
            perror("select() An error ocurred");
            exit(1);
        }

        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &rfds)) {
                if (i == sfd) {
                    int cfd;
                    if ((cfd = accept(sfd, (struct sockaddr*) &peer_addr, &peer_addr_size)) < 0) {
                        perror("accept() An error ocurred");
                        exit(1);
                    }
                    FD_SET(cfd, &afds);
                    if (num_reqs == 0) {
                        gettimeofday(&start, NULL);
                    }
                    num_reqs++;
                    open_reqs++;
                } else {
                    memset(buff, 0, BUFFSIZE);
                    if (recv(i, buff, BUFFSIZE, 0) < 0) {
                        perror("recv() An error ocurred");
                        exit(1);
                    }

                    int fd;
                    if ((fd = open(buff, O_RDONLY)) < 0) {
                        perror("open() An error ocurred");
                        exit(1);
                    }

                    memset(buff, 0, BUFFSIZE);
                    if (read(fd, buff, BUFFSIZE) < 0) {
                        perror("read() An error ocurred");
                        exit(1);
                    }

                    printf("Send file contents %s\n", buff);
                    if (send(i, buff, strlen(buff), 0) < 0) {
                        perror("send() An error ocurred");
                        exit(1);
                    }

                    close(i);
                    FD_CLR(i, & afds);
                    open_reqs--;
                }
            }
        }

        if (argc == 2 && num_reqs == test_reqs && open_reqs == 0) {
            gettimeofday(&end, NULL);
            printf("Sync I/O %d requests, time (seconds): %f\n\n", test_reqs,
                (float)(end.tv_usec - start.tv_usec + (end.tv_sec - start.tv_sec) * ONE_MILLION) / ONE_MILLION);
            close(sfd);
            printf("done");
            exit(0);
        }
    }
    return 0;
}
