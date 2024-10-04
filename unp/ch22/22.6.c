#include "unp.h"
#include <net/if.h>
#include <sys/param.h>

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

#undef MAXLINE
#define MAXLINE 20

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen);
ssize_t Recvfrom_flags(int fd, void *ptr, size_t nbytes, int *flagsp, SA *sa, socklen_t *salenptr,
                       struct unp_in_pktinfo *pktp);
ssize_t recvfrom_flags(int fd, void *ptr, size_t nbytes, int *flagsp, SA *sa, socklen_t *salenptr,
                       struct unp_in_pktinfo *pktp);
char *if_indextoname(unsigned int index, char *name);
char *If_indextoname(unsigned int index, char *name);

int main(void)
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);

    Bind(sockfd, (SA *)&servaddr, sizeof(servaddr));

    dg_echo(sockfd, (SA *)&cliaddr, sizeof(cliaddr));
}

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
    int flags;
    int on = 1;
    socklen_t len;
    ssize_t n;
    char mesg[MAXLINE], str[INET6_ADDRSTRLEN], ifname[IFNAMSIZ];
    struct in_addr in_zero;
    struct unp_in_pktinfo pktinfo;

#ifdef IP_RECVDSTADDR
    if (setsockopt(sockfd, IPPROTO_IP, IP_RECVDSTADDR, &on, sizeof(on)) < 0)
        err_ret("setsockopt of IP_RECVDSTADDR");
#endif
#ifdef IP_RECVIF
    if (setsockopt(sockfd, IPPROTO_IP, IP_RECVIF, &on, sizeof(on)) < 0)
        err_ret("setsockopt of IP_RECVIF");
#endif
    bzero(&in_zero, sizeof(struct in_addr)); /* all 0 IPv4 address */

    for (;;) {
        len   = clilen;
        flags = 0;
        n     = Recvfrom_flags(sockfd, mesg, MAXLINE, &flags, pcliaddr, &len, &pktinfo);

        printf("%ld-byte datagram from %s", n, Sock_ntop(pcliaddr, len));

        if (memcmp(&pktinfo.ipi_addr, &in_zero, sizeof(in_zero)) != 0) {
            printf(", to %s", Inet_ntop(AF_INET, &pktinfo.ipi_addr, str, sizeof(str)));
        }

        if (pktinfo.ipi_ifindex > 0)
            printf(", recv i/f = %s", If_indextoname(pktinfo.ipi_ifindex, ifname));
#ifdef MSG_TRUNC
        if (flags & MSG_TRUNC)
            printf(" (datagram truncated)");
#endif
#ifdef MSG_CTRUNC
        if (flags & MSG_CTRUNC)
            printf(" (control info truncated)");
#endif
#ifdef MSG_BCAST
        if (flags & MSG_BCAST)
            printf(" (broadcast)");
#endif
#ifdef MSG_MCAST
        if (flags & MSG_MCAST)
            printf(" (multicast)");
#endif
        printf("\n");

        Sendto(sockfd, mesg, n, 0, pcliaddr, len);
    }
}

ssize_t recvfrom_flags(int fd, void *ptr, size_t nbytes, int *flagsp, SA *sa, socklen_t *salenptr,
                       struct unp_in_pktinfo *pktp)
{
    struct msghdr msg;
    struct iovec iov[1];
    ssize_t n;

#ifdef HAVE_MSGHDR_MSG_CONTROL
    struct cmsghdr *cmptr;
    union {
        struct cmsghdr cm;
        char
            control[CMSG_SPACE(sizeof(struct in_addr)) + CMSG_SPACE(sizeof(struct unp_in_pktinfo))];
    } control_un;

    msg.msg_control    = control_un.control;
    msg.msg_controllen = sizeof(control_un.control);
    msg.msg_flags      = 0;
#else
    bzero(&msg, sizeof(msg));
#endif

    msg.msg_name    = sa;
    msg.msg_namelen = *salenptr;
    iov[0].iov_base = ptr;
    iov[0].iov_len  = nbytes;
    msg.msg_iov     = iov;
    msg.msg_iovlen  = 1;

    if ((n = recvmsg(fd, &msg, *flagsp)) < 0) {
        return n;
    }

    *salenptr = msg.msg_namelen;

    if (pktp) {
        bzero(pktp, sizeof(struct unp_in_pktinfo)); /* 0.0.0.0, i/f = 0 */
    }

#ifndef HAVE_MSGHDR_MSG_CONTROL
    *flagsp = 0;
    return (n);
#else

    *flagsp = msg.msg_flags;

    if (msg.msg_controllen < sizeof(struct cmsghdr) || (msg.msg_flags & MSG_CTRUNC) ||
        pktp == NULL) {
        return n;
    }

    for (cmptr = CMSG_FIRSTHDR(&msg); cmptr != NULL; cmptr = CMSG_NXTHDR(&msg, cmptr)) {
#ifdef IP_RECVDSTADDR
        if (cmptr->cmsg_level == IPPROTO_IP && cmptr->cmsg_type == IP_RECVDSTADDR) {
            memcpy(&pktp->ipi_addr, CMSG_DATA(cmptr), sizeof(struct in_addr));
            continue;
        }
#endif

#ifdef IP_RECVIF
        if (cmptr->cmsg_level == IPPROTO_IP && cmptr->cmsg_type == IP_RECVIF) {
            struct sockaddr_dl *sdl;

            sdl               = (struct sockaddr_dl *)CMSG_DATA(cmptr);
            pktp->ipi_ifindex = sdl->sdl_index;
            continue;
        }
#endif
        err_quit("unknown ancillary data, len = %d, level = %d, type = %d", cmptr->cmsg_len,
                 cmptr->cmsg_level, cmptr->cmsg_type);
    }
    return (n);
#endif
}

ssize_t Recvfrom_flags(int fd, void *ptr, size_t nbytes, int *flagsp, SA *sa, socklen_t *salenptr,
                       struct unp_in_pktinfo *pktp)
{
    ssize_t n = recvfrom_flags(fd, ptr, nbytes, flagsp, sa, salenptr, pktp);

    if (n < 0) {
        err_quit("recvfrom_flags error");
    }

    return (n);
}

char *if_indextoname(unsigned int index, char *name)
{
    return NULL;
}

char *If_indextoname(unsigned int index, char *name)
{
    char *ptr;

    if ((ptr = if_indextoname(index, name)) == NULL) {
        err_quit("if_indextoname error for %d", index);
    }

    return ptr;
}
