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

int main(int argc, char **argv)
{
    struct ifi_info *ifi, *ifihead;
    struct sockaddr *sa;
    u_char *ptr;
    int i, family, doaliases;

    if (argc != 3) {
        err_quit("usage: prifinfo <inet4|inet6> <doaliases>");
    }

    if (strcmp(argv[1], "inet4") == 0)
        family = AF_INET;
#ifdef IPv6
    else if (strcmp(argv[1], "inet6") == 0)
        family = AF_INET6;
#endif
    else
        err_quit("invalid <address-family>");

    doaliases = atoi(argv[2]);

    for (ifihead = ifi = Get_ifi_info(family, doaliases); ifi != NULL; ifi = ifi->ifi_next) {
        printf("%s: ", ifi->ifi_name);

        if (ifi->ifi_index != 0)
            printf("(%d) ", ifi->ifi_index);
        printf("<");

        if (ifi->ifi_flags & IFF_UP)
            printf("UP ");
        if (ifi->ifi_flags & IFF_BROADCAST)
            printf("BCAST ");
        if (ifi->ifi_flags & IFF_MULTICAST)
            printf("MCAST ");
        if (ifi->ifi_flags & IFF_LOOPBACK)
            printf("LOOP ");
        if (ifi->ifi_flags & IFF_POINTOPOINT)
            printf("P2P ");

        printf(">\n");

        if ((i = ifi->ifi_hlen) > 0) {
            ptr = ifi->ifi_haddr;
            do {
                printf("%s%x", (i == ifi->ifi_hlen) ? "  " : ":", *ptr++);
            } while (--i > 0);
            printf("\n");
        }

        if (ifi->ifi_mtu != 0)
            printf("  MTU: %d\n", ifi->ifi_mtu);

        if ((sa = ifi->ifi_addr) != NULL)
            printf("  IP addr: %s\n", Sock_ntop_host(sa, sizeof(*sa)));
        if ((sa = ifi->ifi_brdaddr) != NULL)
            printf("  broadcast addr: %s\n", Sock_ntop_host(sa, sizeof(*sa)));
        if ((sa = ifi->ifi_dstaddr) != NULL)
            printf("  destination addr: %s\n", Sock_ntop_host(sa, sizeof(*sa)));
    }

    free_ifi_info(ifihead);

    return 0;
}

struct ifi_info *get_ifi_info(int family, int doaliases)
{
    struct ifi_info *ifi, *ifihead, **ifipnext;
    int sockfd, len, lastlen, flags, myflags, idx = 0, hlen = 0;
    char *ptr, *buf, lastname[IFNAMSIZ], *cptr, *haddr, *sdlname;
    struct ifconf ifc;
    struct ifreq *ifr, ifrcopy;
    struct sockaddr_in *sinptr;
    struct sockaddr_in6 *sin6ptr;

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    lastlen = 0;
    len     = 100 * sizeof(struct ifreq);

    for (;;) {
        buf         = Malloc(len);
        ifc.ifc_len = len;
        ifc.ifc_buf = buf;
        if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0) {
            if (errno != EINVAL || lastlen != 0) {
                err_sys("ioctl error");
            }
        } else {
            if (ifc.ifc_len == lastlen) {
                break;
            }

            lastlen = ifc.ifc_len;
        }

        len += 10 * sizeof(struct ifreq); /* increment */
        free(buf);
    }

    ifihead     = NULL;
    ifipnext    = &ifihead;
    lastname[0] = 0;
    sdlname     = NULL;

    for (ptr = buf; ptr < buf + ifc.ifc_len;) {
        ifr = (struct ifreq *)ptr;

#ifdef HAVE_SOCKADDR_SA_LEN
        len = max(sizeof(struct sockaddr), ifr->ifr_addr.sa_len);
#else
        switch (ifr->ifr_addr.sa_family) {
#ifdef IPV6
            case AF_INET6:
                len = sizeof(struct sockaddr_in6);
                break;
#endif
            case AF_INET:
            default:
                len = sizeof(struct sockaddr);
                break;
        }
#endif
        ptr += sizeof(ifr->ifr_name) + len;

#ifdef HAVE_SOCKADDR_DL_STRUCT
        if (ifr->ifr_addr.sa_family == AF_LINK) {
            struct sockaddr_dl *sdl = (struct sockaddr_dl *)&ifr->ifr_addr;
            sdlname                 = ifr->ifr_name;
            idx                     = sdl->sdl_index;
            haddr                   = sdl->sdl_data + sdl->sdl_nlen;
            hlen                    = sdl->sdl_alen;
        }
#endif

        if (ifr->ifr_addr.sa_family != family) {
            continue;
        }

        myflags = 0;

        if ((cptr = strchr(ifr->ifr_name, ':')) != NULL) {
            *cptr = 0;
        }

        if (strncmp(lastname, ifr->ifr_name, IFNAMSIZ) == 0) {
            if (doaliases == 0)
                continue;
            myflags = IFI_ALIAS;
        }

        memcpy(lastname, ifr->ifr_name, IFNAMSIZ);

        ifrcopy = *ifr;
        Ioctl(sockfd, SIOCGIFFLAGS, &ifrcopy);
        flags = ifrcopy.ifr_flags;

        if ((flags & IFF_UP) == 0)
            continue;

        ifi       = Calloc(1, sizeof(struct ifi_info));
        *ifipnext = ifi;
        ifipnext  = &ifi->ifi_next;

        ifi->ifi_flags   = flags;
        ifi->ifi_myflags = myflags;
#if defined(SIOCGIFMTU) && defined(HAVE_STRUCT_IFREQ_IFR_MTU)
        Ioctl(sockfd, SIOCGIFMTU, &ifrcopy);
        ifi->ifi_mtu = ifrcopy.ifr_mtu;
#else
        ifi->ifi_mtu = 0;
#endif
        memcpy(ifi->ifi_name, ifr->ifr_name, IFI_NAME);
        ifi->ifi_name[IFI_NAME - 1] = '\0';

        if (sdlname == NULL || strcmp(sdlname, ifr->ifr_name) != 0)
            idx = hlen = 0;

        ifi->ifi_index = idx;
        ifi->ifi_hlen  = hlen;

        if (ifi->ifi_hlen > IFI_HADDR) {
            ifi->ifi_hlen = IFI_HADDR;
        }

        if (hlen) {
            memcpy(ifi->ifi_haddr, haddr, ifi->ifi_hlen);
        }

        switch (ifr->ifr_addr.sa_family) {
            case AF_INET:
                sinptr        = (struct sockaddr_in *)&ifr->ifr_addr;
                ifi->ifi_addr = Calloc(1, sizeof(struct sockaddr_in));
                memcpy(ifi->ifi_addr, sinptr, sizeof(struct sockaddr_in));

#ifdef SIOCGIFBRDADDR
                if (flags & IFF_BROADCAST) {
                    Ioctl(sockfd, SIOCGIFBRDADDR, &ifrcopy);
                    sinptr           = (struct sockaddr_in *)&ifrcopy.ifr_broadaddr;
                    ifi->ifi_brdaddr = Calloc(1, sizeof(struct sockaddr_in));
                    memcpy(ifi->ifi_brdaddr, sinptr, sizeof(struct sockaddr_in));
                }
#endif

#ifdef SIOCGIFDSTADDR
                if (flags & IFF_POINTOPOINT) {
                    Ioctl(sockfd, SIOCGIFDSTADDR, &ifrcopy);
                    sinptr           = (struct sockaddr_in *)&ifrcopy.ifr_dstaddr;
                    ifi->ifi_dstaddr = Calloc(1, sizeof(struct sockaddr_in));
                    memcpy(ifi->ifi_dstaddr, sinptr, sizeof(struct sockaddr_in));
                }
#endif
                break;

            case AF_INET6:
                sin6ptr       = (struct sockaddr_in6 *)&ifr->ifr_addr;
                ifi->ifi_addr = Calloc(1, sizeof(struct sockaddr_in6));
                memcpy(ifi->ifi_addr, sin6ptr, sizeof(struct sockaddr_in6));

#ifdef SIOCGIFDSTADDR
                if (flags & IFF_POINTOPOINT) {
                    Ioctl(sockfd, SIOCGIFDSTADDR, &ifrcopy);
                    sin6ptr          = (struct sockaddr_in6 *)&ifrcopy.ifr_dstaddr;
                    ifi->ifi_dstaddr = Calloc(1, sizeof(struct sockaddr_in6));
                    memcpy(ifi->ifi_dstaddr, sin6ptr, sizeof(struct sockaddr_in6));
                }
#endif
                break;

            default:
                break;
        }
    }

    free(buf);

    return ifihead;
}

void free_ifi_info(struct ifi_info *ifihead)
{
    struct ifi_info *ifi, *ifinext;

    for (ifi = ifihead; ifi != NULL; ifi = ifinext) {
        if (ifi->ifi_addr != NULL)
            free(ifi->ifi_addr);
        if (ifi->ifi_brdaddr != NULL)
            free(ifi->ifi_brdaddr);
        if (ifi->ifi_dstaddr != NULL)
            free(ifi->ifi_dstaddr);
        ifinext = ifi->ifi_next;
        free(ifi);
    }
}

struct ifi_info *Get_ifi_info(int family, int doaliases)
{
    struct ifi_info *ifi;

    if ((ifi = get_ifi_info(family, doaliases)) == NULL)
        err_quit("get_ifi_info error");
    return (ifi);
}
