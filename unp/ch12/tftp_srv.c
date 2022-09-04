#include "defs.h"

void net_close();
void net_send(char *buff, int len);
int net_recv(char *buff, int maxlen);
void net_init(char *service, int port);
int net_open(int inetdflag);
void daemon_start(int ignsigcld);
void sig_child();
int recv_xRQ(int opcode, char *ptr, int nbytes);
int recv_RRQ(char *ptr, int nbytes);
int recv_WRQ(char *ptr, int nbytes);
int recv_ACK(char *ptr, int nbytes);
int recv_DATA(char *ptr, int nbytes);
void send_ERROR(int ecode, char *string);
void send_ACK(int blocknum);
void send_DATA(int blocknum, int nbytes);
int writen(int fd, char *ptr, int nbytes);
int readn(int fd, char *ptr, int nbytes);
void strlccpy(char *dest, char *src);

FILE *file_open();
void file_write(FILE *fp, char *ptr, int nbytes, int mode);
int file_read(FILE *fp, char *ptr, int maxnbytes, int mode);
void file_close(FILE *fp);

int fsm_loop(int opcode);
int fsm_error(char *ptr, int nbytes);
int fsm_invalid(char *ptr, int nbytes);
int fsm_error();
int fsm_invalid();

int (*fsm_ptr [ OP_MAX + 1 ] [ OP_MAX + 1 ] ) () = {
    fsm_invalid,    /* [sent = 0]        [recv = 0]         */
    recv_RRQ,       /* [sent = 0]        [recv = OP_RRQ]        */
    recv_WRQ,       /* [sent = 0]        [recv = OP_WRQ]        */
    fsm_invalid,    /* [sent = 0]        [recv = OP_DATA]       */
    fsm_invalid,    /* [sent = 0]        [recv = OP_ACK]        */
    fsm_invalid,    /* [sent = 0]        [recv = OP_ERROR]      */

    fsm_invalid,    /* [sent = OP_RRQ]   [recv = 0]         */
    fsm_invalid,    /* [sent = OP_RRQ]   [recv = OP_RRQ]        */
    fsm_invalid,    /* [sent = OP_RRQ]   [recv = OP_WRQ]        */
    fsm_invalid,    /* [sent = OP_RRQ]   [recv = OP_DATA]       */
    fsm_invalid,    /* [sent = OP_RRQ]   [recv = OP_ACK]        */
    fsm_invalid,    /* [sent = OP_RRQ]   [recv = OP_ERROR]      */

    fsm_invalid,    /* [sent = OP_WRQ]   [recv = 0]         */
    fsm_invalid,    /* [sent = OP_WRQ]   [recv = OP_RRQ]        */
    fsm_invalid,    /* [sent = OP_WRQ]   [recv = OP_WRQ]        */
    fsm_invalid,    /* [sent = OP_WRQ]   [recv = OP_DATA]       */
    fsm_invalid,    /* [sent = OP_WRQ]   [recv = OP_ACK]        */
    fsm_invalid,    /* [sent = OP_WRQ]   [recv = OP_ERROR]      */

    fsm_invalid,    /* [sent = OP_DATA]  [recv = 0]         */
    fsm_invalid,    /* [sent = OP_DATA]  [recv = OP_RRQ]        */
    fsm_invalid,    /* [sent = OP_DATA]  [recv = OP_WRQ]        */
    fsm_invalid,    /* [sent = OP_DATA]  [recv = OP_DATA]       */
    recv_ACK,       /* [sent = OP_DATA]  [recv = OP_ACK]        */
    fsm_error,  /* [sent = OP_DATA]  [recv = OP_ERROR]      */

    fsm_invalid,    /* [sent = OP_ACK]   [recv = 0]         */
    fsm_invalid,    /* [sent = OP_ACK]   [recv = OP_RRQ]        */
    fsm_invalid,    /* [sent = OP_ACK]   [recv = OP_WRQ]        */
    recv_DATA,      /* [sent = OP_ACK]   [recv = OP_DATA]       */
    fsm_invalid,    /* [sent = OP_ACK]   [recv = OP_ACK]        */
    fsm_error,  /* [sent = OP_ACK]   [recv = OP_ERROR]      */

    fsm_invalid,    /* [sent = OP_ERROR] [recv = 0]         */
    fsm_invalid,    /* [sent = OP_ERROR] [recv = OP_RRQ]        */
    fsm_invalid,    /* [sent = OP_ERROR] [recv = OP_WRQ]        */
    fsm_invalid,    /* [sent = OP_ERROR] [recv = OP_DATA]       */
    fsm_invalid,    /* [sent = OP_ERROR] [recv = OP_ACK]        */
    fsm_error   /* [sent = OP_ERROR] [recv = OP_ERROR]      */
};

struct sockaddr_in tcp_cli_addr;

int main(int argc, char **argv)
{
    int childpid;
    char *s;

    puts("rich's tftpd");

    while (--argc > 0 && (*++argv)[0] == '-')
        for (s = argv[0]+1; *s != '\0'; s++)
            switch (*s) {
            case 'i':
                inetdflag = 0; /* turns OFF the flag */
                               /* (it defaults to 1) */
                break;

            case 'p':       /* specify server's port# */
                if (--argc <= 0) {
                    puts("-p requires another argument");
                    exit(1);
                }
                port = atoi(*++argv);
                break;

            case 't':
                traceflag = 1;
                break;

            default:
                printf("unknown command line option: %c\n", *s);
                exit(1);
            }

    if (inetdflag == 0) {
        daemon_start(1);
        net_init(TFTP_SERVICE, port);
    }

    if (traceflag) {
        if (freopen(DAEMONLOG, "a", stderr) == NULL) {
            printf("can't open %s for writing\n", DAEMONLOG);
            exit(1);
        }
        DEBUG2("pid = %d, inetdflag = %d", getpid(), inetdflag);
    }

    for ( ; ; ) {
        if ((childpid = net_open(inetdflag)) == 0) {
            fsm_loop(0);    /* child processes client's request */
            net_close();    /* then we're done */
            exit(0);
        }
        /* parent waits for another client's request */
    }
    /* NOTREACHED */
    return 0;
}

void net_init(char *service, int port)
{
    struct servent  *sp;

    bzero((char *) &tcp_srv_addr, sizeof(tcp_srv_addr));
    tcp_srv_addr.sin_family      = AF_INET;
    tcp_srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (service != NULL) {
        if ((sp = getservbyname(service, "tcp")) == NULL) {
            printf("net_init: unknown service: %s/tcp\n", service);
            exit(1);
        }
        tcp_serv_info = *sp;            /* structure copy */

        if (port > 0) {
            tcp_srv_addr.sin_port = htons(port);
        } else {
            tcp_srv_addr.sin_port = sp->s_port;
        }
    } else {
        if (port <= 0) {
               puts("tcp_open: must specify either service or port");
               return;
        }
        tcp_srv_addr.sin_port = htons(port);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("net_init: can't create stream socket");
        exit(1);
    }

    if (bind(sockfd, (struct sockaddr *) &tcp_srv_addr, sizeof(tcp_srv_addr)) < 0) {
        perror("net_init: can't bind local address");
        exit(1);
    }

    listen(sockfd, 5);
}

int net_open(int inetdflag)
{
    int newsockfd, childpid, nbytes;
    int clilen, on;
    on = 1;

    if (inetdflag) {
        sockfd = 0; /* descriptor for net_recv() to read from */

        return 0;  /* done */
    }

again:
    clilen = sizeof(tcp_cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &tcp_cli_addr, &clilen);
    if (newsockfd < 0) {
        if (errno == EINTR) {
            errno = 0;
            goto again; /* probably a SIGCLD that was caught */
        }
        puts("accept error");
        exit(1);
    }

    if ((childpid = fork()) < 0) {
        puts("server can't fork");
        exit(1);
    } else if (childpid > 0) {        /* parent */
        close(newsockfd);   /* close new connection */
        return childpid;   /* and return */
    }

    close(sockfd);
    sockfd = newsockfd;

    return 0;      /* return to process the connection */
}

void net_send(char *buff, int len)
{
    int rc;
    short templen;

    DEBUG1("net_send: sent %d bytes", len);

    templen = htons(len);
    rc = writen(sockfd, (char *) &templen, sizeof(short));
    if (rc != sizeof(short)) {
        puts("writen error of length prefix");
        exit(1);
    }

    rc = writen(sockfd, buff, len);
    if (rc != len) {
        puts("writen error");
        exit(1);
    }
}

int net_recv(char *buff, int maxlen)
{
    int nbytes;
    short templen;    /* value-result parameter */

again1:
    if ((nbytes = readn(sockfd, (char *) &templen, sizeof(short))) < 0) {
        if (errno == EINTR) {
            errno = 0;
            goto again1;
        }
        puts("readn error for length prefix");
        exit(1);
    }
    if (nbytes != sizeof(short)) {
        puts("error in readn of length prefix");
        exit(1);
    }

    templen = ntohs(templen);       /* #bytes that follow */
    if (templen > maxlen) {
        puts("record length too large");
        exit(1);
    }

again2:
    if ((nbytes = readn(sockfd, buff, templen)) < 0) {
        if (errno == EINTR) {
            errno = 0;      /* assume SIGCLD */
            goto again2;
        }
        puts("readn error");
        exit(1);
    }
    if (nbytes != templen) {
        puts("error in readn");
        exit(1);
    }

    DEBUG1("net_recv: got %d bytes", nbytes);

    return nbytes;     /* return the actual length of the message */
}

void net_close()
{
    DEBUG2("net_close: host = %s, fd = %d", openhost, sockfd);
    close(sockfd);
    sockfd = -1;
}


void daemon_start(int ignsigcld)
{
    int childpid, fd;

    if (getppid() == 1) {
        goto out;
    }

#ifdef SIGTTOU
    signal(SIGTTOU, SIG_IGN);
#endif
#ifdef SIGTTIN
    signal(SIGTTIN, SIG_IGN);
#endif
#ifdef SIGTSTP
    signal(SIGTSTP, SIG_IGN);
#endif

    if ((childpid = fork()) < 0) {
        perror("can't fork first child");
        exit(1);
    } else if (childpid > 0) {
        exit(0);    /* parent */
    }

    if (setpgid(0, getpid()) == -1) {
        perror("can't change process group");
        exit(1);
    }

    if ((fd = open("/dev/tty", O_RDWR)) >= 0) {
        ioctl(fd, TIOCNOTTY, NULL); /* lose controlling tty */
        close(fd);
    }

out:
    for (fd = 0; fd < NOFILE; fd++) {
        close(fd);
    }

    errno = 0;
    chdir("/");
    umask(0);

    if (ignsigcld) {
#ifdef  SIGTSTP
        signal(SIGCHLD, sig_child);  /* BSD */
#else
        signal(SIGCHLD, SIG_IGN);    /* System V */
#endif
    }
}

void sig_child()
{
    int pid;
    int status;
    while ((pid = wait3(&status, WNOHANG, (struct rusage *) 0)) > 0) {
        ; // do nothing
    }
}

int fsm_loop(int opcode)
{
    int nbytes;
    op_sent = opcode;

    for ( ; ; ) {
        if ((nbytes = net_recv(recvbuff, MAXBUFF)) < 0) {
            puts("net_recv error");
            exit(1);
        }

        if (nbytes < 4) {
            printf("receive length = %d bytes\n", nbytes);
            exit(1);
        }

        op_recv = ldshort(recvbuff);

        if (op_recv < OP_MIN || op_recv > OP_MAX) {
            printf("invalid opcode received: %d", op_recv);
            exit(1);
        }

        if ((*fsm_ptr[op_sent][op_recv])(recvbuff + 2, nbytes - 2) < 0) {
            signal(SIGALRM, SIG_DFL);
            return(0);
        }
    }
}

int fsm_error(char *ptr, int nbytes)
{
    printf("error received: op_sent = %d, op_recv = %d", op_sent, op_recv);
    exit(1);
}

int fsm_invalid(char *ptr, int nbytes)
{
    printf("protocol botch: op_sent = %d, op_recv = %d", op_sent, op_recv);
    exit(1);
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

int recv_ACK(char *ptr, int nbytes)
{
    int recvblknum;

    recvblknum = ldshort(ptr);
    if (nbytes != 2) {
        printf("ACK packet received with length = %d bytes\n", nbytes + 2);
        exit(1);
    }

    DEBUG1("ACK received, block# %d", recvblknum);

    if (recvblknum == nextblknum) {
        if ((nbytes = file_read(localfp, sendbuff + 4, MAXDATA, modetype)) == 0) {
            if (lastsend < MAXDATA) {
                return -1; /* done */
            }
        }

        lastsend = nbytes;
        nextblknum++;       /* incr for this new packet of data */
        totnbytes += nbytes;
        send_DATA(nextblknum, nbytes);

        return 0;
    } else if (recvblknum < (nextblknum - 1)) {
        puts("recvblknum < nextblknum - 1");
        exit(1);
    } else if (recvblknum > nextblknum) {
        puts("recvblknum > nextblknum");
        exit(1);
    } else {
        return 0;
    }
    /* NOTREACHED */
}

int recv_DATA(char *ptr, int nbytes)
{
    int recvblknum;

    recvblknum = ldshort(ptr);
    ptr += 2;
    nbytes -= 2;

    DEBUG2("DATA received, %d bytes, block# %d", nbytes, recvblknum);

    if (nbytes > MAXDATA) {
        printf("data packet received with length = %d bytes", nbytes);
        exit(1);
    }

    if (recvblknum == nextblknum) {
        nextblknum++;
        totnbytes += nbytes;

        if (nbytes > 0) {
            file_write(localfp, ptr, nbytes, modetype);
        }
    } else if (recvblknum < (nextblknum - 1)) {
        puts("recvblknum < nextblknum - 1");
        exit(1);
    } else if (recvblknum > nextblknum) {
        puts("recvblknum > nextblknum");
        exit(1);
    }

    send_ACK(recvblknum);

    return( (nbytes == MAXDATA) ? 0 : -1 );
}

int recv_RRQ(char *ptr, int nbytes)
{
    char ackbuff[2];

    recv_xRQ(OP_RRQ, ptr, nbytes);  /* verify the RRQ packet */

    lastsend = MAXDATA;
    stshort(0, ackbuff);    /* pretend its an ACK of block# 0 */
    recv_ACK(ackbuff, 2);   /* this sends data block# 1 */

    return 0;  /* the finite state machine takes over from here */
}

int recv_WRQ(char *ptr, int nbytes)
{
    recv_xRQ(OP_WRQ, ptr, nbytes);  /* verify the WRQ packet */

    nextblknum = 1;
    send_ACK(0);

    return 0;  /* the finite stat machine takes over from here */
}

void send_ACK(int blocknum)
{
    DEBUG1("sending ACK for block# %d", blocknum);

    stshort(OP_ACK, sendbuff);
    stshort(blocknum, sendbuff + 2);

    sendlen = 4;
    net_send(sendbuff, sendlen);
    op_sent = OP_ACK;
}

void send_DATA(int blocknum, int nbytes)
{
    DEBUG2("sending %d bytes of DATA with block# %d", nbytes, blocknum);

    stshort(OP_DATA, sendbuff);
    stshort(blocknum, sendbuff + 2);

    sendlen = nbytes + 4;
    net_send(sendbuff, sendlen);
    op_sent = OP_DATA;
}

int recv_xRQ(int opcode, char *ptr, int nbytes)
{
    int  i;
    char *saveptr;
    char filename[MAXFILENAME], dirname[MAXFILENAME], mode[MAXFILENAME];
    struct stat statbuff;

    saveptr = ptr;      /* points to beginning of filename */
    for (i = 0; i < nbytes; i++) {
        if (*ptr++ == '\0') {
            goto FileOK;
        }
    }
    puts("Invalid filename");
    exit(1);

FileOK:
    strcpy(filename, saveptr);
    saveptr = ptr;      /* points to beginning of Mode */

    for ( ; i < nbytes; i++) {
        if (*ptr++ == '\0') {
            goto ModeOK;
        }
    }
    puts("Invalid Mode");
    exit(1);

ModeOK:
    strlccpy(mode, saveptr);    /* copy and convert to lower case */

    if (strcmp(mode, "netascii") == 0) {
        modetype = MODE_ASCII;
    } else if (strcmp(mode, "octet") == 0) {
        modetype = MODE_BINARY;
    } else {
        send_ERROR(ERR_BADOP, "Mode isn't netascii or octet");
    }

    if (filename[0] != '/') {
        send_ERROR(ERR_ACCESS, "filename must begin with '/'");
    }

    if (opcode == OP_RRQ) {
        if (stat(filename, &statbuff) < 0) {
            send_ERROR(ERR_ACCESS, "sys_err_str()");
        }
        if ((statbuff.st_mode & (S_IREAD >> 6)) == 0) {
            send_ERROR(ERR_ACCESS, "File doesn't allow world read permission");
        }
    } else if (opcode == OP_WRQ) {
        char *rindex();
        strcpy(dirname, filename);
        *(rindex(dirname, '/') + 1) = '\0';
        if (stat(dirname, &statbuff) < 0) {
            send_ERROR(ERR_ACCESS, "sys_err_str()");
        }
        if ((statbuff.st_mode & (S_IWRITE >> 6)) == 0) {
            send_ERROR(ERR_ACCESS, "Directory doesn't allow world write permission");
        }
    } else {
        puts("unknown opcode");
        exit(1);
    }

    localfp = file_open(filename, (opcode == OP_RRQ) ? "r" : "w", 0);
    if (localfp == NULL) {
        send_ERROR(ERR_NOFILE, "sys_err_str()");  /* doesn't return */
    }
}

void send_ERROR(int ecode, char *string)
{
    DEBUG2("sending ERROR, code = %d, string = %s", ecode, string);

    stshort(OP_ERROR, sendbuff);
    stshort(ecode, sendbuff + 2);
    strcpy(sendbuff + 4, string);

    sendlen = 4 + strlen(sendbuff + 4) + 1;     /* +1 for null at end */
    net_send(sendbuff, sendlen);
    net_close();
    exit(0);
}

void strlccpy(char *dest, char *src)
{
    char c;
    while ((c = *src++) != '\0') {
        if (isupper(c)) {
            c = tolower(c);
        }
        *dest++ = c;
    }
    *dest = 0;
}

static int  lastcr   = 0;   /* 1 if last character was a carriage-return */
static int  nextchar = 0;

FILE *file_open(char *fname, char *mode, int initblknum)
{
    FILE *fp;

    if (strcmp(fname, "-") == 0) {
        fp = stdout;
    } else if ( (fp = fopen(fname, mode)) == NULL) {
        return (FILE *) 0;
    }

    nextblknum = initblknum;    /* for first data packet or first ACK */
    lastcr     = 0;         /* for file_write() */
    nextchar   = -1;        /* for file_read() */

    DEBUG2("file_open: opened %s, mode = %s", fname, mode);

    return fp;
}

void file_close(FILE *fp)
{
    if (lastcr) {
        puts("final character was a CR");
        exit(1);
    }
    if (nextchar >= 0) {
        puts("nextchar >= 0");
        exit(1);
    }

    if (fp == stdout) {
        return;     /* don't close standard output */
    } else if (fclose(fp) == EOF) {
        puts("fclose error");
        exit(1);
    }
}

int file_read(FILE *fp, char *ptr, int maxnbytes, int mode)
{
    int c, count;

    if (mode == MODE_BINARY) {
        count = read(fileno(fp), ptr, maxnbytes);
        if (count < 0) {
            puts("read error on local file");
            exit(1);
        }

        return count;      /* will be 0 on EOF */
    } else if (mode == MODE_ASCII) {
        for (count = 0; count < maxnbytes; count++) {
            if (nextchar >= 0) {
                *ptr++ = nextchar;
                nextchar = -1;
                continue;
            }

            c = getc(fp);

            if (c == EOF) { /* EOF return means eof or error */
                if (ferror(fp)) {
                    puts("read err from getc on local file");
                    exit(1);
                }
                return count;
            } else if (c == '\n') {
                c = '\r';       /* newline -> CR,LF */
                nextchar = '\n';
            } else if (c == '\r') {
                nextchar = '\0';    /* CR -> CR,NULL */
            } else {
                nextchar = -1;
            }
            *ptr++ = c;
        }
        return count;
    } else {
        puts("unknown MODE value");
        exit(1);
    }
}

void file_write(FILE *fp, char *ptr, int nbytes, int mode)
{
    int c, i;

    if (mode == MODE_BINARY) {
        i = write(fileno(fp), ptr, nbytes);
        if (i != nbytes) {
            printf("write error to local file, i = %d", i);
            exit(1);
        }
    } else if (mode == MODE_ASCII) {
        for (i = 0; i < nbytes; i++) {
            c = *ptr++;
            if (lastcr) {
                if (c == '\n') {
                    c = '\n';
                } else if (c == '\0') {
                    c = '\r';
                } else {
                    printf("CR followed by 0x%02x\n", c);
                    exit(1);
                }
                lastcr = 0;
            } else if (c == '\r') {
                lastcr = 1;
                continue;   /* get next character */
            }

            if (putc(c, fp) == EOF) {
                puts("write error from putc to local file");
                exit(1);
            }
        }
    } else {
        puts("unknown MODE value");
        exit(1);
    }
}
