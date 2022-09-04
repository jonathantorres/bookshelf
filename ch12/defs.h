#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <netdb.h>
#include <setjmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

extern int errno;

#define MAXBUFF     2048   /* transmit and receive buffer length */
#define MAXDATA     512   /* max size of data per packet to send or rcv */
                          /* 512 is specified by the RFC */
#define MAXFILENAME 128   /* max filename length */
#define MAXHOSTNAME 128   /* max host name length */
#define MAXLINE     512   /* max command line length */
#define MAXTOKEN    128   /* max token length */

#define TFTP_SERVICE "tftp"  /* name of the service */
#define DAEMONLOG    "/tmp/tftpd.log" /* log file for daemon tracing */

char command[];        /* the command being processed */
int  connected;        /* true if we're connected to host */
char hostname[];       /* name of host system */
int  inetdflag;        /* true if we were started by a daemon */
int  interactive;      /* true if we're running interactive */
jmp_buf jmp_mainloop;  /* to return to main command loop */
int  lastsend;         /* #bytes of data in last data packet */
FILE *localfp;         /* fp of local file to read or write */
int  modetype;         /* see MODE_xxx values */
int  nextblknum;       /* next block# to send/receive */
char *pname;           /* the name by which we are invoked */
int  port;             /* port number - host byte order */
                              /* 0 -> use default */
char *prompt;          /* prompt string, for interactive use */
long totnbytes;        /* for get/put statistics printing */
int  traceflag;        /* -t command line option, or "trace" cmd */
int  verboseflag;      /* -v command line option */

#define MODE_ASCII  0   /* values for modetype */
                        /* ascii == netascii */
#define MODE_BINARY 1   /* binary == octet */

/*
 * One receive buffer and one transmit buffer.
 */
char recvbuff[];
char sendbuff[];
int  sendlen;    /* #bytes in sendbuff[] */

/*
 * Define the tftp opcodes.
 */
#define OP_RRQ   1   /* Read Request */
#define OP_WRQ   2   /* Write Request */
#define OP_DATA  3   /* Data */
#define OP_ACK   4   /* Acknowledgment */
#define OP_ERROR 5   /* Error, see error codes below also */
#define OP_MIN   1   /* minimum opcode value */
#define OP_MAX   5   /* maximum opcode value */

int  op_sent;    /* last opcode sent */
int  op_recv;    /* last opcode received */

int rtt_d_flag; /* can be set nonzero by caller for addl info */

#define RTT_RXTMIN      2   /* min retransmit timeout value, seconds */
#define RTT_RXTMAX    120   /* max retransmit timeout value, seconds */
#define RTT_MAXNREXMT   4   /* max #times to retransmit: must also
                            change exp_backoff[] if this changes */

struct rtt_struct {
  float rtt_rtt;    /* most recent round-trip time (RTT), seconds */
  float rtt_srtt;   /* smoothed round-trip time (SRTT), seconds */
  float rtt_rttdev; /* smoothed mean deviation, seconds */
  short rtt_nrexmt; /* #times retransmitted: 0, 1, 2, ... */
  short rtt_currto; /* current retransmit timeout (RTO), seconds */
  short rtt_nxtrto; /* retransmit timeout for next packet, if nonzero */
  struct timeval    time_start; /* for elapsed time */
  struct timeval    time_stop;  /* for elapsed time */
};

/*
 * Define the tftp error codes.
 * These are transmitted in an error packet (OP_ERROR) with an
 * optional netascii Error Message describing the error.
 */
#define ERR_UNDEF   0   /* not defined, see error message */
#define ERR_NOFILE  1   /* File not found */
#define ERR_ACCESS  2   /* Access violation */
#define ERR_NOSPACE 3   /* Disk full or allocation exceeded */
#define ERR_BADOP   4   /* Illegal tftp operation */
#define ERR_BADID   5   /* Unknown TID (port#) */
#define ERR_FILE    6   /* File already exists */
#define ERR_NOUSER  7   /* No such user */

int sockfd = -1; /* fd for socket of server */
char openhost[MAXHOSTNAMELEN] = { 0 };   /* remember host's name */
int traceflag;  /* TFTP variable */

struct sockaddr_in tcp_srv_addr;   /* set by tcp_open() */
struct servent     tcp_serv_info;  /* set by tcp_open() */

/*
 * Debug macros, based on the trace flag (-t command line argument,
 * or "trace" command).
 */
#define DEBUG(fmt)      if (traceflag) { \
                    fprintf(stderr, fmt); \
                    fputc('\n', stderr); \
                    fflush(stderr); \
                } else ;

#define DEBUG1(fmt, arg1)   if (traceflag) { \
                    fprintf(stderr, fmt, arg1); \
                    fputc('\n', stderr); \
                    fflush(stderr); \
                } else ;

#define DEBUG2(fmt, arg1, arg2) if (traceflag) { \
                    fprintf(stderr, fmt, arg1, arg2); \
                    fputc('\n', stderr); \
                    fflush(stderr); \
                } else ;

#define DEBUG3(fmt, arg1, arg2, arg3)   if (traceflag) { \
                    fprintf(stderr, fmt, arg1, arg2, arg3); \
                    fputc('\n', stderr); \
                    fflush(stderr); \
                } else ;

/*
 * Define macros to load and store 2-byte integers, since these are
 * used in the TFTP headers for opcodes, block numbers and error
 * numbers.  These macros handle the conversion between host format
 * and network byte ordering.
 */
#define ldshort(addr)       ( ntohs (*( (u_short *)(addr) ) ) )
#define stshort(sval,addr)  ( *( (u_short *)(addr) ) = htons(sval) )

#ifdef  lint        /* hush up lint */
#undef  ldshort
#undef  stshort
short   ldshort();
#endif  /* lint */
