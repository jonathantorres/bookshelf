#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/param.h>

#define MAXFILENAME    128 /* max filename length */
#define MAXLINE        512 /* max ascii line length */

#define LPR_SERVICE "printer"    /* name of the network service */
#define SEQNO_FILE  "/tmp/seqno" /* name of the sequence# file */

char hostname[MAXHOSTNAMELEN]    = "hsi"; /* name of host providing the service */
char printername[MAXHOSTNAMELEN] = "lp";  /* name of printer to use on hostname */
int  debugflag                   = 0;     /* -d command line options */
char *pname;

struct sockaddr_in tcp_srv_addr;   /* set by tcp_open() */
struct servent     tcp_serv_info;  /* set by tcp_open() */
struct hostent     tcp_host_info;  /* from gethostbyname() */

static FILE *cfp;           /* file pointer for control file */
static long cfilesize;      /* size of cfile, in bytes */
static char myhostname[MAXHOSTNAMELEN]; /* name of host running lpr */
static char username[MAXHOSTNAMELEN];   /* name of user running lpr */
static char cfname[MAXFILENAME];    /* name of "cf" file */
static char dfname[MAXFILENAME];    /* name of "df" file */
static char buf[MAXLINE];       /* temp buffer */
static int  sockfd;         /* network connection */
static int  seqnum;         /* seq#, set to same value for now */

#define DEBUG2(fmt, arg1, arg2) if (debugflag) { \
                    fprintf(stderr, fmt, arg1, arg2); \
                    fputc('\n', stderr); \
                } else ;

void send_start();
void send_done();
void send_file(char *filename, FILE *fp);
void xmit_file(char *filename, FILE *fp, char *fname, char xmittype);
void copyfile(FILE *fp);
int get_seqno();
long get_size(char *filename, FILE *fp);
void add_H();
void add_P();
void add_C();
void add_L();
void add_N(char *filename);
void add_J(char *filename);
void add_U(char *dfname);
void add_f(char *dfname);

int writen(int fd, char *ptr, int nbytes);
int readn(int fd, char *ptr, int nbytes);
int tcp_open(char *host, char *service, int port);
int readline(int fd, char *ptr, int maxlen);
void my_lock(int fd);
void my_unlock(int fd);

int main(int argc, char **argv)
{
    FILE *fp;
    char *s, *filename;
    int  i;

    pname = argv[0];
    while (--argc > 0 && (*++argv)[0] == '-')
        for (s = argv[0]+1; *s != '\0'; s++)
            switch (*s) {
            case 'P':       /* specify printer name */
            case 'p':       /* specify printer name */
                if (--argc <= 0) {
                    printf("-%c requires another argument\n", *s);
                    exit(1);
                }
                strcpy(printername, *++argv);
                break;

            case 'd':       /* debug */
                debugflag = 1;
                break;

            case 'h':       /* specify host name */
                if (--argc <= 0) {
                    puts("-h requires another argument");
                    exit(1);
                }
                strcpy(hostname, *++argv);
                break;

            default:
                fprintf(stderr, "%s: illegal option %c\n", pname, *s);
                break;
            }

    i = 0;
    send_start();
    do {
        if (argc > 0) {
            filename = argv[i];
            if (strcmp(filename, "-") == 0) {
                fp = stdin;
                filename = "-stdin";
             } else if ( (fp = fopen(argv[i], "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", pname, argv[i]);
                continue;
            }
        } else {
            fp = stdin;
            filename = "-stdin";
        }

        send_file(filename, fp);

        fclose(fp);

    } while (++i < argc);
    send_done();
    return 0;
}

int get_seqno()
{
    int seqno;
    FILE *fp;

    if ((fp = fopen(SEQNO_FILE, "r+")) == NULL) {
        printf("can't open %s\n", SEQNO_FILE);
        exit(1);
    }

    my_lock(fileno(fp));        /* exclusive lock on file */

    if (fscanf(fp, "%d", &seqno) != 1) {
        puts("fscanf error for sequence number");
        exit(1);
    }

    rewind(fp);
    fprintf(fp, "%03d\n", (seqno+1) % 1000);   /* next seq# to use */
    fflush(fp);

    my_unlock(fileno(fp));      /* unlock file */

    fclose(fp);         /* and close it, we're done */

    return seqno;
}

void send_start()
{
    int    uid;
    struct passwd *pw;

    DEBUG2("send_start: host = %s, printer = %s", hostname, printername);

    if ((sockfd = tcp_open(hostname, LPR_SERVICE, -1)) < 0) {
        printf("can't connect to service: %s on host: %s\n", LPR_SERVICE, hostname);
        exit(1);
    }

    setuid(getuid());

    if (gethostname(myhostname, MAXHOSTNAMELEN) < 0) {
        perror("gethostname error");
        exit(1);
    }

    uid = getuid();
    if ((pw = getpwuid(uid)) == NULL) {
        printf("getpwuid failed, uid = %d; who are you\n", uid);
        exit(1);
    }
    strcpy(username, pw->pw_name);

    seqnum = get_seqno();

    sprintf(cfname, "cfA%03d%s\n", seqnum, myhostname);
    sprintf(dfname, "dfA%03d%s\n", seqnum, myhostname);
    DEBUG2("cfname = %s, dfname = %s", cfname, dfname);

    if ((cfp = fopen(cfname, "w")) == NULL) {
        printf("can't open control file: %s for writing\n", cfname);
        exit(1);
    }
    cfilesize = 0L;

    add_H();
    add_P();
    add_C();
    add_L();

    sprintf(buf, "%c%s\n", '\002', printername);
    if (writen(sockfd, buf, strlen(buf)) != strlen(buf)) {
        puts("writen error");
        exit(1);
    }

    if (readn(sockfd, buf, 1) != 1) {
        puts("readn error");
        exit(1);
    }
    if (buf[0] != '\0') {
        if (readline(sockfd, &buf[1], MAXLINE-1) > 0) {
           printf("error, server returned: %s\n", buf);
           exit(1);
        } else {
           printf("didn't get ACK from server, got 0x%02x\n", buf[0]);
           exit(1);
        }
    }
}

void send_file(char *filename, FILE *fp)
{
    static int filecount = 0;
    char *ptr;

    if (strcmp(filename, "-stdin") == 0) {
        puts("can't currently print standard input");
        return;
    }

    filecount++;

    if ((ptr = rindex(filename, '/')) != NULL) {
        filename = ptr + 1;
    }

    if (filecount == 1) {
        add_J(filename);
    } else {
        dfname[2]++;    /* A, B, C, ... */
    }

    add_f(dfname);
    add_U(dfname);
    add_N(filename);

    DEBUG2("send_file: %s, dfname = %s", filename, dfname);

    /* transmit file across network */
    xmit_file(filename, fp, dfname, '\003');
}

void send_done()
{
    fclose(cfp);

    if ((cfp = fopen(cfname, "r")) == NULL) {
        perror("can't reopen cfile for reading");
        exit(1);
    }

    xmit_file("-cfile", cfp, cfname, '\002');
    fclose(cfp);

    if (debugflag == 0 && unlink(cfname) < 0) {
        printf("can't unlink control file: %s\n", cfname);
        exit(1);
    }

    close(sockfd);
}

void xmit_file(char *filename, FILE *fp, char *fname, char xmittype)
{
    long size;

    size = get_size(filename, fp);
    DEBUG2("xmit_file: %s, size = %ld", filename, size);

    sprintf(buf, "%c%ld %s\n", xmittype, size, fname);
    if (writen(sockfd, buf, strlen(buf)) != strlen(buf)) {
        perror("writen error");
        exit(1);
    }
    if (readn(sockfd, buf, 1) != 1) {
        perror("readn error");
        exit(1);
    }
    if (buf[0] != '\0') {
        printf("didn't get an ACK from server, got 0x%02x\n", buf[0]);
        exit(1);
    }

    copyfile(fp);

    if (writen(sockfd, "", 1) != 1) {
        perror("writen error");
        exit(1);
    }
    if (readn(sockfd, buf, 1) != 1) {
        perror("readn error");
        exit(1);
    }
    if (buf[0] != '\0') {
        printf("didn't get an ACK from server, got 0x%02x\n", buf[0]);
        exit(1);
    }
}

void copyfile(FILE *fp)
{
    int len;
    char line[MAXLINE];

    while (fgets(line, MAXLINE, fp) != NULL) {
        len = strlen(line);
        if (writen(sockfd, line, len) != len) {
            perror("writen error");
            exit(1);
        }
    }

    if (ferror(fp)) {
        puts("read error from fgets");
        exit(1);
    }
}

long get_size(char *filename, FILE *fp)
{
    struct stat statbuff;

    if (fstat(fileno(fp), &statbuff) < 0) {
        perror("can't fstat");
        exit(1);
    }

    return statbuff.st_size;
}

void add_H()
{
    fprintf(cfp, "H%s\n", myhostname);
    cfilesize += strlen(myhostname) + 2;
}

void add_P()
{
    fprintf(cfp, "P%s\n", username);
    cfilesize += strlen(username) + 2;
}

void add_J(char *filename)
{
    fprintf(cfp, "J%s\n", filename);
    cfilesize += strlen(filename) + 2;
}

void add_C()
{
    /* just use this host's name */
    fprintf(cfp, "C%s\n", myhostname);
    cfilesize += strlen(myhostname) + 2;
}

void add_L()
{
    fprintf(cfp, "L%s\n", username);
    cfilesize += strlen(username) + 2;
}

void add_f(char *dfname)
{
    fprintf(cfp, "f%s\n", dfname);
    cfilesize += strlen(dfname) + 2;
}

void add_U(char *dfname)
{
    fprintf(cfp, "U%s\n", dfname);
    cfilesize += strlen(dfname) + 2;
}

void add_N(char *filename)
{
    fprintf(cfp, "N%s\n", filename);
    cfilesize += strlen(filename) + 2;
}

int readn(int fd, char *ptr, int nbytes)
{
    int nleft, nread;
    nleft = nbytes;
    while (nleft > 0) {
        nread = read(fd, ptr, nleft);
        if (nread < 0) {
            return nread;      /* error, return < 0 */
        } else if (nread == 0) {
            break;          /* EOF */
        }

        nleft -= nread;
        ptr   += nread;
    }
    return nbytes - nleft;     /* return >= 0 */
}

int writen(int fd, char *ptr, int nbytes)
{
    int nleft, nwritten;
    nleft = nbytes;
    while (nleft > 0) {
        nwritten = write(fd, ptr, nleft);
        if (nwritten <= 0) {
            return nwritten;       /* error */
        }

        nleft -= nwritten;
        ptr   += nwritten;
    }
    return nbytes - nleft;
}

int tcp_open(char *host, char *service, int port)
{
    int     fd, resvport;
    unsigned long   inaddr;
    struct servent  *sp;
    struct hostent  *hp;

    bzero((char *) &tcp_srv_addr, sizeof(tcp_srv_addr));
    tcp_srv_addr.sin_family = AF_INET;

    if (service != NULL) {
        if ((sp = getservbyname(service, "tcp")) == NULL) {
            printf("tcp_open: unknown service: %s/tcp\n", service);
            return -1;
        }
        tcp_serv_info = *sp;            /* structure copy */
        if (port > 0) {
            /* caller's value */
            tcp_srv_addr.sin_port = htons(port);
        } else {
            /* service's value */
            tcp_srv_addr.sin_port = sp->s_port;
        }
    } else {
        if (port <= 0) {
            puts("tcp_open: must specify either service or port");
            return -1;
        }
        tcp_srv_addr.sin_port = htons(port);
    }

    if ((inaddr = inet_addr(host)) != INADDR_NONE) {
        /* it's dotted-decimal */
        bcopy((char *) &inaddr, (char *) &tcp_srv_addr.sin_addr, sizeof(inaddr));
        tcp_host_info.h_name = NULL;
    } else {
        if ((hp = gethostbyname(host)) == NULL) {
            printf("tcp_open: host name error: %s\n", host);
            return(-1);
        }
        tcp_host_info = *hp;    /* found it by name, structure copy */
        bcopy(hp->h_addr, (char *) &tcp_srv_addr.sin_addr, hp->h_length);
    }

    if (port >= 0) {
        if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            puts("tcp_open: can't create TCP socket");
            return -1;
        }
    } else if (port < 0) {
        resvport = IPPORT_RESERVED - 1;
        if ((fd = rresvport(&resvport)) < 0) {
            puts("tcp_open: can't get a reserved TCP port");
            return -1;
        }
    }

    if (connect(fd, (struct sockaddr *) &tcp_srv_addr, sizeof(tcp_srv_addr)) < 0) {
        puts("tcp_open: can't connect to server");
        close(fd);
        return -1;
    }

    return fd; /* all OK */
}

int readline(int fd, char *ptr, int maxlen)
{
    int n, rc;
    char c;

    for (n = 1; n < maxlen; n++) {
        if ((rc = read(fd, &c, 1)) == 1) {
            *ptr++ = c;
            if (c == '\n') {
                break;
            }
        } else if (rc == 0) {
            if (n == 1) {
                return(0);  /* EOF, no data read */
            } else {
                break;      /* EOF, some data was read */
            }
        } else {
            return(-1); /* error */
        }
    }

    *ptr = 0;
    return n;
}

void my_lock(int fd)
{
    lseek(fd, 0L, 0); /* rewind before lockf */

    /* 0L -> lock entire file */
    if (lockf(fd, F_LOCK, 0L) == -1) {
        perror("can't F_LOCK");
        exit(1);
    }
}

void my_unlock(int fd)
{
    lseek(fd, 0L, 0);
    if (lockf(fd, F_ULOCK, 0L) == -1) {
        perror("can't F_ULOCK");
        exit(1);
    }
}
