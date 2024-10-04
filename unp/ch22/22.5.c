#include "unp.h"
#include <net/if.h>

#define IFI_NAME  16
#define IFI_HADDR 8

struct ifi_info {
    char ifi_name[IFI_NAME];      /* interface name, null-terminated */
    short ifi_index;              /* interface index */
    short ifi_mtu;                /* interface MTU */
    u_char ifi_haddr[IFI_HADDR];  /* hardware address */
    u_short ifi_hlen;             /* # bytes in hardware address: 0, 6, 8 */
    short ifi_flags;              /* IFF_xxx constants from <net/if.h> */
    short ifi_myflags;            /* our own IFI_xxx flags */
    struct sockaddr *ifi_addr;    /* primary address */
    struct sockaddr *ifi_brdaddr; /* broadcast address */
    struct sockaddr *ifi_dstaddr; /* destination address */
    struct ifi_info *ifi_next;    /* next of these structures */
};

#define IFI_ALIAS 1

struct ifi_info *get_ifi_info(int, int);
struct ifi_info *Get_ifi_info(int, int);
void free_ifi_info(struct ifi_info *);

void mydg_echo(int, SA *, socklen_t);

int main(int argc, char **argv)
{
    int sockfd, family, port;
    const int on = 1;
    pid_t pid;
    socklen_t salen;
    struct sockaddr *sa, *wild;
    struct ifi_info *ifi, *ifihead;

    if (argc == 2) {
        sockfd = Udp_client(NULL, argv[1], (void **)&sa, &salen);
    } else if (argc == 3) {
        sockfd = Udp_client(argv[1], argv[2], (void **)&sa, &salen);
    } else {
        err_quit("usage: udpserv04 [ <host> ] <service or port>");
    }

    family = sa->sa_family;
    port   = sock_get_port(sa, salen);
    Close(sockfd);

    for (ifihead = ifi = Get_ifi_info(family, 1); ifi != NULL; ifi = ifi->ifi_next) {
        sockfd = Socket(family, SOCK_DGRAM, 0);
        Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

        sock_set_port(ifi->ifi_addr, salen, port);
        Bind(sockfd, ifi->ifi_addr, salen);
        printf("bound %s\n", Sock_ntop(ifi->ifi_addr, salen));

        if ((pid = Fork()) == 0) { /* child */
            mydg_echo(sockfd, ifi->ifi_addr, salen);
            exit(0);
        }

        if (ifi->ifi_flags & IFF_BROADCAST) {
            sockfd = Socket(family, SOCK_DGRAM, 0);
            Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
            sock_set_port(ifi->ifi_brdaddr, salen, port);

            if (bind(sockfd, ifi->ifi_brdaddr, salen) < 0) {
                if (errno == EADDRINUSE) {
                    printf("EADDRINUSE: %s\n", Sock_ntop(ifi->ifi_brdaddr, salen));
                    Close(sockfd);
                    continue;
                } else {
                    err_sys("bind error for %s", Sock_ntop(ifi->ifi_brdaddr, salen));
                }
            }

            printf("bound %s\n", Sock_ntop(ifi->ifi_brdaddr, salen));

            if ((pid = Fork()) == 0) { /* child */
                mydg_echo(sockfd, ifi->ifi_brdaddr, salen);
                exit(0);
            }
        }
    }

    sockfd = Socket(family, SOCK_DGRAM, 0);
    Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    wild = Malloc(salen);
    memcpy(wild, sa, salen);
    sock_set_wild(wild, salen);

    Bind(sockfd, wild, salen);
    printf("bound %s\n", Sock_ntop(wild, salen));

    if ((pid = Fork()) == 0) { /* child */
        mydg_echo(sockfd, wild, salen);
        exit(0);
    }

    return 0;
}

void mydg_echo(int sockfd, SA *myaddr, socklen_t salen)
{
    int n;
    char mesg[MAXLINE];
    socklen_t len;
    struct sockaddr *cli;

    cli = Malloc(salen);

    for (;;) {
        len = salen;
        n   = Recvfrom(sockfd, mesg, MAXLINE, 0, cli, &len);

        printf("child %d, datagram from %s", getpid(), Sock_ntop(cli, len));
        printf(", to %s\n", Sock_ntop(myaddr, salen));

        Sendto(sockfd, mesg, n, 0, cli, len);
    }
}
