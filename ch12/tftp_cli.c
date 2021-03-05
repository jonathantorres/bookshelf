#include "defs.h"

void t_start();
void t_stop();
double t_getutime();
double t_getstime();
double t_getrtime();

void mainloop(FILE *fp);
int sig_intr();
void net_close();
void net_send(char *buff, int len);
int net_recv(char *buff, int maxlen);
void do_put(char *remfname, char *locfname);
void do_get(char *remfname, char *locfname);
int recv_RQERR(char *ptr, int nbytes);
void send_RQ(int opcode, char *fname, int mode);
int recv_ACK(char *ptr, int nbytes);
int recv_DATA(char *ptr, int nbytes);
void send_DATA(int blocknum, int nbytes);
void send_ACK(int blocknum);
int writen(int fd, char *ptr, int nbytes);
int readn(int fd, char *ptr, int nbytes);
int tcp_open(char *host, char *service, int port);
int net_open(char *host, char *service, int port);
double t_getrtime();

int func_timeout();
int fsm_loop(int opcode);
int fsm_error(char *ptr, int nbytes);
int fsm_invalid(char *ptr, int nbytes);
int fsm_error();
int fsm_invalid();

void cmd_verbose();
void cmd_trace();
void cmd_status();
void cmd_put();
void cmd_mode();
void cmd_help();
void cmd_get();
void cmd_exit();
void cmd_connect();
void cmd_binary();
void cmd_ascii();
void err_cmd(char *str);
void striphost(char *fname, char *hname);
int binary(char *word, int n);
void docmd(char *cmdptr);
void checkend();
char *gettoken(char *token);
int get_line(FILE *fp);

FILE *file_open();
void file_write(FILE *fp, char *ptr, int nbytes, int mode);
int file_read(FILE *fp, char *ptr, int maxnbytes, int mode);
void file_close(FILE *fp);

int (*fsm_ptr [ OP_MAX + 1 ] [ OP_MAX + 1 ] ) () = {
    fsm_invalid,    /* [sent = 0]        [recv = 0]         */
    fsm_invalid,    /* [sent = 0]        [recv = OP_RRQ]        */
    fsm_invalid,    /* [sent = 0]        [recv = OP_WRQ]        */
    fsm_invalid,    /* [sent = 0]        [recv = OP_DATA]       */
    fsm_invalid,    /* [sent = 0]        [recv = OP_ACK]        */
    fsm_invalid,    /* [sent = 0]        [recv = OP_ERROR]      */

    fsm_invalid,    /* [sent = OP_RRQ]   [recv = 0]         */
    fsm_invalid,    /* [sent = OP_RRQ]   [recv = OP_RRQ]        */
    fsm_invalid,    /* [sent = OP_RRQ]   [recv = OP_WRQ]        */
    recv_DATA,      /* [sent = OP_RRQ]   [recv = OP_DATA]       */
    fsm_invalid,    /* [sent = OP_RRQ]   [recv = OP_ACK]        */
    recv_RQERR,     /* [sent = OP_RRQ]   [recv = OP_ERROR]      */

    fsm_invalid,    /* [sent = OP_WRQ]   [recv = 0]         */
    fsm_invalid,    /* [sent = OP_WRQ]   [recv = OP_RRQ]        */
    fsm_invalid,    /* [sent = OP_WRQ]   [recv = OP_WRQ]        */
    fsm_invalid,    /* [sent = OP_WRQ]   [recv = OP_DATA]       */
    recv_ACK,       /* [sent = OP_WRQ]   [recv = OP_ACK]        */
    recv_RQERR,     /* [sent = OP_WRQ]   [recv = OP_ERROR]      */

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

struct sockaddr_in tcp_srv_addr;   /* server's Internet socket addr */
struct servent     tcp_serv_info;  /* from getservbyname() */
struct hostent     tcp_host_info;  /* from gethostbyname() */

static struct rtt_struct   rttinfo; /* used by the rtt_XXX() functions */
static int rttfirst = 1;
static double start, stop, seconds;
static struct timeval      time_start, time_stop; /* for real time */
static struct rusage       ru_start, ru_stop;     /* for user & sys time */

int tout_flag;  /* set to 1 by SIGALRM handler */

char temptoken[];    /* temporary token for anyone to use */

typedef struct Cmds {
  char  *cmd_name;      /* actual command string */
  int   (*cmd_func)();      /* pointer to function */
} Cmds;

Cmds commands[] = {  /* keep in alphabetical order for binary search */
    "?",        cmd_help,
    "ascii",    cmd_ascii,
    "binary",   cmd_binary,
    "connect",  cmd_connect,
    "exit",     cmd_exit,
    "get",      cmd_get,
    "help",     cmd_help,
    "mode",     cmd_mode,
    "put",      cmd_put,
    "quit",     cmd_exit,
    "status",   cmd_status,
    "trace",    cmd_trace,
    "verbose",  cmd_verbose,
};

#define NCMDS (sizeof(commands) / sizeof(Cmds))

int ncmds = NCMDS;

static char line[MAXLINE] = { 0 };
static char *lineptr = NULL;

int main(int argc, char const *argv[])
{
    int  i;
    char *s;
    FILE *fp;

    pname = argv[0];

    while (--argc > 0 && (*++argv)[0] == '-') {
        for (s = argv[0]+1; *s != '\0'; s++) {
            switch (*s) {
            case 'h': /* specify host name */
                if (--argc <= 0) {
                    puts("-h requires another argument");
                    exit(1);
                }
                strcpy(hostname, *++argv);
                break;
            case 't':
                traceflag = 1;
                break;
            case 'v':
                verboseflag = 1;
                break;
            default:
                printf("unknown command line option: %c\n", *s);
                exit(1);
            }
        }
    }

    /*
     * For each filename argument, execute the tftp commands in
     * that file.  If no filename arguments were specified on the
     * command line, we process the standard input by default.
     */
    i = 0;
    fp = stdin;
    do {
        if (argc > 0 && (fp = fopen(argv[i], "r")) == NULL) {
            printf("%s: can't open %s for reading\n", argv[i]);
            exit(1);
        }
        /* process a given file */
        mainloop(fp);
    } while (++i < argc);

    exit(0);
}

void mainloop(FILE *fp)
{
    if (signal(SIGINT, SIG_IGN) != SIG_IGN) {
        signal(SIGINT, sig_intr);
    }

    /*
     * Main loop.  Read a command and execute it.
     * This loop is terminated by a "quit" command, or an
     * end-of-file on the command stream.
     */
    if (setjmp(jmp_mainloop) < 0) {
        puts("Timeout");
        exit(1);
    }

    if (interactive) {
        printf("%s", prompt);
    }

    while (get_line(fp)) {
        if (gettoken(command) != NULL) {
            docmd(command);
        }

        if (interactive) {
            printf("%s", prompt);
        }
    }
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

int sig_intr()
{
    signal(SIGALRM, SIG_IGN); /* first ignore the signal */
    alarm(0);                 /* then assure alarm is off */

    longjmp(jmp_mainloop, 1);
    /* NOTREACHED */
}

int net_open(char *host, char *service, int port)
{
    if ((sockfd = tcp_open(host, service, port)) < 0) {
        return -1;
    }

    DEBUG2("net_open: host %s, port# %d",
            inet_ntoa(tcp_srv_addr.sin_addr),
            ntohs(tcp_srv_addr.sin_port));

    strcpy(openhost, host);     /* save the host's name */

    return 0;
}

void net_close()
{
    DEBUG2("net_close: host = %s, fd = %d", openhost, sockfd);
    close(sockfd);
    sockfd = -1;
}

void cmd_ascii()
{
    modetype = MODE_ASCII;
}

void cmd_binary()
{
    modetype = MODE_BINARY;
}

void cmd_connect()
{
    int val;

    if (gettoken(hostname) == NULL) {
        err_cmd("missing hostname");
    }

    if (gettoken(temptoken) == NULL) {
        return;
    }
    val = atoi(temptoken);
    if (val < 0) {
        err_cmd("invalid port number");
    }
    port = val;
}

void cmd_exit()
{
    exit(0);
}

void cmd_get()
{
    char remfname[MAXFILENAME], locfname[MAXFILENAME];
    char *index();

    if (gettoken(remfname) == NULL) {
        err_cmd("the remote filename must be specified");
    }
    if (gettoken(locfname) == NULL) {
        err_cmd("the local filename must be specified");
    }

    if (index(locfname, ':') != NULL) {
        err_cmd("can't have 'host:' in local filename");
    }

    striphost(remfname, hostname);  /* check for "host:" and process */
    if (hostname[0] == 0) {
        err_cmd("no host has been specified");
    }

    do_get(remfname, locfname);
}

void cmd_help()
{
    int i;
    for (i = 0; i < ncmds; i++) {
        printf("  %s\n", commands[i].cmd_name);
    }
}

void cmd_mode()
{
    if (gettoken(temptoken) == NULL) {
        err_cmd("a mode type must be specified");
    } else {
        if (strcmp(temptoken, "ascii") == 0) {
            modetype = MODE_ASCII;
        } else if (strcmp(temptoken, "binary") == 0) {
            modetype = MODE_BINARY;
        } else {
            err_cmd("mode must be 'ascii' or 'binary'");
        }
    }
}

void cmd_put()
{
    char remfname[MAXFILENAME], locfname[MAXFILENAME];

    if (gettoken(locfname) == NULL) {
        err_cmd("the local filename must be specified");
    }
    if (gettoken(remfname) == NULL) {
        err_cmd("the remote filename must be specified");
    }

    if (index(locfname, ':') != NULL) {
        err_cmd("can't have 'host:' in local filename");
    }

    striphost(remfname, hostname);  /* check for "host:" and process */
    if (hostname[0] == 0)
        err_cmd("no host has been specified");

    do_put(remfname, locfname);
}

void cmd_status()
{
    if (connected) {
        printf("Connected\n");
    } else {
        printf("Not connected\n");
    }

    printf("mode = ");
    switch (modetype) {
    case MODE_ASCII:    printf("netascii");     break;
    case MODE_BINARY:   printf("octet (binary)");   break;
    default:
        puts("unknown modetype");
        exit(1);
    }

    printf(", verbose = %s", verboseflag ? "on" : "off");
    printf(", trace = %s\n", traceflag ? "on" : "off");
}

void cmd_trace()
{
    traceflag = !traceflag;
}

void cmd_verbose()
{
    verboseflag = !verboseflag;
}

int get_line(FILE *fp)
{
    if (fgets(line, MAXLINE, fp) == NULL) {
        return 0;      /* error or end-of-file */
    }
    lineptr = line;
    return 1;
}

char *gettoken(char *token)
{
    int  c;
    char *tokenptr;

    while ((c = *lineptr++) == ' ' || c == '\t') {
        ;       /* skip leading white space */
    }

    if (c == '\0' || c == '\n') {
        return NULL;   /* nothing there */
    }

    tokenptr = token;
    *tokenptr++ = c;    /* first char of token */

    /*
     * Now collect everything up to the next space, tab, newline, or null.
     */
    while ((c = *lineptr++) != ' ' && c != '\t' && c != '\n' && c != '\0') {
        *tokenptr++ = c;
    }

    *tokenptr = 0;      /* null terminate token */
    return token;
}

void checkend()
{
    if (gettoken(temptoken) != NULL) {
        err_cmd("trailing garbage");
    }
}

void docmd(char *cmdptr)
{
    int i;

    if ((i = binary(cmdptr, ncmds)) < 0) {
        err_cmd(cmdptr);
    }

    (*commands[i].cmd_func)();

    checkend();
}

int binary(char *word, int n)
{
    int low, high, mid, cond;

    low  = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, commands[mid].cmd_name)) < 0) {
            high = mid - 1;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;    /* found it, return index in array */
        }
    }
    return -1; /* not found */
}

void striphost(char *fname, char *hname)
{
    char *index();
    char *ptr1, *ptr2;

    if ((ptr1 = index(fname, ':')) == NULL) {
        return;     /* there is not a "host:" present */
    }

    /*
     * Copy the entire "host:file" into the hname array,
     * then replace the colon with a null byte.
     */
    strcpy(hname, fname);
    ptr2 = index(hname, ':');
    *ptr2 = 0;  /* null terminates the "host" string */

    /*
     * Now move the "file" string left in the fname array,
     * removing the "host:" portion.
     */
    strcpy(fname, ptr1 + 1);    /* ptr1 + 1 to skip over the ':' */
}

void err_cmd(char *str)
{
    fprintf(stderr, "%s: '%s' command error", pname, command);
    if (strlen(str) > 0) {
        fprintf(stderr, ": %s", str);
    }
    fprintf(stderr, "\n");
    fflush(stderr);

    longjmp(jmp_mainloop, 1);   /* 1 -> not a timeout, we've already
                                printed our error message */
}

void send_RQ(int opcode, char *fname, int mode)
{
    int  len;
    char *modestr;

    DEBUG2("sending RRQ/WRQ for %s, mode = %d", fname, mode);

    stshort(opcode, sendbuff);
    strcpy(sendbuff+2, fname);
    len = 2 + strlen(fname) + 1;    /* +1 for null byte at end of fname */

    switch(mode) {
    case MODE_ASCII:    modestr = "netascii";   break;
    case MODE_BINARY:   modestr = "octet";  break;
    default:
        puts("unknown mode");
        exit(1);
    }
    strcpy(sendbuff + len, modestr);
    len += strlen(modestr) + 1; /* +1 for null byte at end of modestr */

    sendlen = len;
    net_send(sendbuff, sendlen);
    op_sent = opcode;
}

int recv_RQERR(char *ptr, int nbytes)
{
    int ecode;

    ecode = ldshort(ptr);
    ptr += 2;
    nbytes -= 2;
    ptr[nbytes] = 0;    /* assure it's null terminated ... */

    DEBUG2("ERROR received, %d bytes, error code %d", nbytes, ecode);

    fflush(stdout);
    fprintf(stderr, "Error# %d: %s\n", ecode, ptr);
    fflush(stderr);

    return -1; /* terminate finite state loop */
}

void do_get(char *remfname, char *locfname)
{
    if ((localfp = file_open(locfname, "w", 1)) == NULL) {
        printf("can't fopen %s for writing\n", locfname);
        return;
    }

    if (net_open(hostname, TFTP_SERVICE, port) < 0) {
        return;
    }

    totnbytes = 0;
    t_start();      /* start timer for statistics */
    send_RQ(OP_RRQ, remfname, modetype);
    fsm_loop(OP_RRQ);
    t_stop();       /* stop timer for statistics */
    net_close();
    file_close(localfp);

    printf("Received %ld bytes in %.1f seconds\n", totnbytes, t_getrtime()); /* print stastics */
}

void do_put(char *remfname, char *locfname)
{
    if ((localfp = file_open(locfname, "r", 0)) == NULL) {
        printf("can't fopen %s for reading\n", locfname);
        return;
    }

    if (net_open(hostname, TFTP_SERVICE, port) < 0) {
        return;
    }

    totnbytes = 0;
    t_start();      /* start timer for statistics */
    lastsend = MAXDATA;
    send_RQ(OP_WRQ, remfname, modetype);
    fsm_loop(OP_WRQ);
    t_stop();       /* stop timer for statistics */
    net_close();
    file_close(localfp);

    printf("Sent %ld bytes in %.1f seconds\n", totnbytes, t_getrtime()); /* print stastics */
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
            printf("tcp_open: unknown service: %s/tcp", service);
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
            printf("tcp_open: host name error: %s", host);
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

void t_start()
{
    if (gettimeofday(&time_start, (struct timezone *) 0) < 0) {
        puts("t_start: gettimeofday() error");
        exit(1);
    }
    if (getrusage(RUSAGE_SELF, &ru_start) < 0) {
        puts("t_start: getrusage() error");
        exit(1);
    }
}

void t_stop()
{
    if (getrusage(RUSAGE_SELF, &ru_stop) < 0) {
        puts("t_stop: getrusage() error");
        exit(1);
    }
    if (gettimeofday(&time_stop, (struct timezone *) 0) < 0) {
        puts("t_stop: gettimeofday() error");
        exit(1);
    }
}

double t_getutime()
{
    start = ((double) ru_start.ru_utime.tv_sec) * 1000000.0
                + ru_start.ru_utime.tv_usec;
    stop = ((double) ru_stop.ru_utime.tv_sec) * 1000000.0
                + ru_stop.ru_utime.tv_usec;
    seconds = (stop - start) / 1000000.0;

    return seconds;
}

double t_getstime()
{
    start = ((double) ru_start.ru_stime.tv_sec) * 1000000.0
                + ru_start.ru_stime.tv_usec;
    stop = ((double) ru_stop.ru_stime.tv_sec) * 1000000.0
                + ru_stop.ru_stime.tv_usec;
    seconds = (stop - start) / 1000000.0;

    return seconds;
}

double t_getrtime()
{
    start = ((double) time_start.tv_sec) * 1000000.0
                + time_start.tv_usec;
    stop = ((double) time_stop.tv_sec) * 1000000.0
                + time_stop.tv_usec;
    seconds = (stop - start) / 1000000.0;

    return seconds;
}
