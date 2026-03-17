#include "unp.h"
#include <setjmp.h>

struct rtt_info {
    float rtt_rtt;     /* most recent measured RTT, seconds */
    float rtt_srtt;    /* smoothed RTT estimator, seconds */
    float rtt_rttvar;  /* smoothed mean deviation, seconds */
    float rtt_rto;     /* current RTO to use, seconds */
    int rtt_nrexmt;    /* #times retransmitted: 0, 1, 2, ... */
    uint32_t rtt_base; /* #sec since 1/1/1970 at start */
};

#define RTT_RXTMIN    2
#define RTT_RXTMAX    60
#define RTT_MAXNREXMT 3
#define RTT_DEBUG

void rtt_debug(struct rtt_info *);
void rtt_init(struct rtt_info *);
void rtt_newpack(struct rtt_info *);
int rtt_start(struct rtt_info *);
void rtt_stop(struct rtt_info *, uint32_t);
int rtt_timeout(struct rtt_info *);
uint32_t rtt_ts(struct rtt_info *);

extern int rtt_d_flag;

static struct rtt_info rttinfo;
static int rttinit = 0;
static struct msghdr msgsend, msgrecv;
static struct hdr {
    uint32_t seq;
    uint32_t ts;
} sendhdr, recvhdr;

static void sig_alrm(int signo);
static sigjmp_buf jmpbuf;
ssize_t dg_send_recv(int fd, const void *outbuff, size_t outbytes, void *inbuff, size_t inbytes,
                     const SA *destaddr, socklen_t destlen);
ssize_t Dg_send_recv(int fd, const void *outbuff, size_t outbytes, void *inbuff, size_t inbytes,
                     const SA *destaddr, socklen_t destlen);
void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen);

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2) {
        err_quit("usage: udpcli <IPaddress>");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(7);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    dg_cli(stdin, sockfd, (SA *)&servaddr, sizeof(servaddr));

    return 0;
}

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    ssize_t n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];

    while (Fgets(sendline, MAXLINE, fp) != NULL) {

        n = Dg_send_recv(sockfd, sendline, strlen(sendline), recvline, MAXLINE, pservaddr, servlen);

        recvline[n] = 0; /* null terminate */
        Fputs(recvline, stdout);
    }
}

ssize_t dg_send_recv(int fd, const void *outbuff, size_t outbytes, void *inbuff, size_t inbytes,
                     const SA *destaddr, socklen_t destlen)
{
    ssize_t n;
    struct iovec iovsend[2], iovrecv[2];

    if (rttinit == 0) {
        rtt_init(&rttinfo);
        rttinit    = 1;
        rtt_d_flag = 1;
    }

    sendhdr.seq++;
    msgsend.msg_name    = destaddr;
    msgsend.msg_namelen = destlen;
    msgsend.msg_iov     = iovsend;
    msgsend.msg_iovlen  = 2;
    iovsend[0].iov_base = &sendhdr;
    iovsend[0].iov_len  = sizeof(struct hdr);
    iovsend[1].iov_base = outbuff;
    iovsend[1].iov_len  = outbytes;

    msgrecv.msg_name    = NULL;
    msgrecv.msg_namelen = 0;
    msgrecv.msg_iov     = iovrecv;
    msgrecv.msg_iovlen  = 2;
    iovrecv[0].iov_base = &recvhdr;
    iovrecv[0].iov_len  = sizeof(struct hdr);
    iovrecv[1].iov_base = inbuff;
    iovrecv[1].iov_len  = inbytes;

    Signal(SIGALRM, sig_alrm);
    rtt_newpack(&rttinfo);

sendagain:
#ifdef RTT_DEBUG
    fprintf(stderr, "send %4d: ", sendhdr.seq);
#endif
    sendhdr.ts = rtt_ts(&rttinfo);
    Sendmsg(fd, &msgsend, 0);

    alarm(rtt_start(&rttinfo));
#ifdef RTT_DEBUG
    rtt_debug(&rttinfo);
#endif

    if (sigsetjmp(jmpbuf, 1) != 0) {
        if (rtt_timeout(&rttinfo) < 0) {
            err_msg("dg_send_recv: no response from server, giving up");
            rttinit = 0; /* reinit in case we're called again */
            errno   = ETIMEDOUT;
            return -1;
        }
#ifdef RTT_DEBUG
        err_msg("dg_send_recv: timeout, retransmitting");
#endif
        goto sendagain;
    }

    do {
        n = Recvmsg(fd, &msgrecv, 0);
#ifdef RTT_DEBUG
        fprintf(stderr, "recv %4d\n", recvhdr.seq);
#endif
    } while (n < sizeof(struct hdr) || recvhdr.seq != sendhdr.seq);

    alarm(0);

    rtt_stop(&rttinfo, rtt_ts(&rttinfo) - recvhdr.ts);

    return (n - sizeof(struct hdr));
}

static void sig_alrm(int signo)
{
    siglongjmp(jmpbuf, 1);
}

ssize_t Dg_send_recv(int fd, const void *outbuff, size_t outbytes, void *inbuff, size_t inbytes,
                     const SA *destaddr, socklen_t destlen)
{
    ssize_t n = dg_send_recv(fd, outbuff, outbytes, inbuff, inbytes, destaddr, destlen);

    if (n < 0) {
        err_quit("dg_send_recv error");
    }

    return n;
}
