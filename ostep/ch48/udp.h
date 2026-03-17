#define _POSIX_C_SOURCE 201112L

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <time.h>
#include <errno.h>
#include <assert.h>

#define BUFFER_SIZE 65507
#define TIMEOUT_SECONDS 10

char *client_sem_name = "/client_sem";
sem_t *client_sem;
struct timespec ts;

int udp_open(char *hostName, char *port, int server)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, status;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family    = AF_UNSPEC;
    hints.ai_socktype  = SOCK_DGRAM;
    hints.ai_flags     = AI_PASSIVE;
    hints.ai_protocol  = 0;
    hints.ai_canonname = NULL;
    hints.ai_addr      = NULL;
    hints.ai_next      = NULL;

    status = getaddrinfo(hostName, port, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1) {
            continue;
        }

        if (server && bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) {
            break;
        } else if (!server && connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1) {
            break;
        }
        close(sfd);
    }

    if (rp == NULL) {
        char *error_message = server ? "Could not bind" : "Could not connect";
        fprintf(stderr, "%s\n", error_message);
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(result);

    if (!server && (client_sem = sem_open(client_sem_name, O_CREAT, S_IRWXU, 1)) == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    return sfd;
}

ssize_t udp_write(int sfd, char *buffer, int bytes_read, struct sockaddr *peer_addr, int peer_addr_len)
{
    if (bytes_read > BUFFER_SIZE) {
        fprintf(stderr, "Exceed max buffer size\n");
        exit(EXIT_FAILURE);
    }

    int status = 0;
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        perror("clock_gettime");
        exit(EXIT_FAILURE);
    }
    ts.tv_sec += TIMEOUT_SECONDS;
    errno = 0;
    int is_ask = 0;
    // if ((is_ask = strncmp(buffer, "ack", 4)) != 0) {
    //     status = sem_timedwait(client_sem, &ts);
    // }
    if (status == -1) {
        if (errno == ETIMEDOUT) {
            return udp_write(sfd, buffer, bytes_read, peer_addr, peer_addr_len);
        } else {
            perror("sem_timedwait");
            exit(EXIT_FAILURE);
        }
    } else {
        if (is_ask != 0) {
            sem_post(client_sem);
        }
        return sendto(sfd, buffer, bytes_read, 0, peer_addr, peer_addr_len);
    }
}

ssize_t udp_read(int sfd, char *buffer, struct sockaddr *peer_addr, socklen_t *peer_addr_len)
{
    memset(buffer, 0, BUFFER_SIZE);
    ssize_t recv_bytes = recvfrom(sfd, buffer, BUFFER_SIZE, 0, peer_addr, peer_addr_len);
    if (recv_bytes > 0 && strncmp(buffer, "ack", 4) != 0) {
        printf("Send ack\n");
        udp_write(sfd, "ack", 4, peer_addr, *peer_addr_len);
    }
    return recv_bytes;
}

void close_sem()
{
    if (sem_close(client_sem) != 0) {
        perror("sem_close failed");
        exit(EXIT_FAILURE);
    }
    if (sem_unlink(client_sem_name) != 0) {
        perror("sem_close failed");
        exit(EXIT_FAILURE);
    }
}
