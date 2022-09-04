#include    <stdio.h>
#include    <stdlib.h>
#include    <strings.h>
#include    <unistd.h>
#include    <signal.h>
#include    <sys/stat.h>
#include    <sys/param.h>
#include    <sys/types.h>
#include    <sys/wait.h>
#include    <errno.h>
#include    <sys/socket.h>
#include    <netinet/in.h>
#include    <arpa/inet.h>

#ifdef  SIGTSTP     /* true if BSD system */
#include    <sys/file.h>
#include    <sys/ioctl.h>
#endif

#define MAXLINE 512
#define SERV_UDP_PORT   6000
#define SERV_TCP_PORT   6000
#define SERV_HOST_ADDR  "localhost"

char *pname;
extern int errno;

void str_echo(int sockfd);
void daemon_start(int ignsigcld);
void sig_child();
int readline(int fd, char *ptr, int maxlen);
int writen(int fd, char *ptr, int nbytes);

int main(int argc, char **argv)
{
    daemon_start(0);

    int sockfd, newsockfd, childpid;
    unsigned int clilen;
    struct sockaddr_in cli_addr, serv_addr;

    pname = argv[0];

    /*
     * Open a TCP socket (an Internet stream socket).
     */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        puts("server: can't open stream socket");
        exit(1);
    }

    /*
     * Bind our local address so that the client can send to us.
     */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port        = htons(SERV_TCP_PORT);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        puts("server: can't bind local address");
        exit(1);
    }

    listen(sockfd, 5);

    for ( ; ; ) {
        /*
         * Wait for a connection from a client process.
         * This is an example of a concurrent server.
         */
        clilen = (unsigned int)sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) {
            puts("server: accept error");
            exit(1);
        }

        if ((childpid = fork()) < 0) {
            puts("server: fork error");
            exit(1);
        } else if (childpid == 0) {   /* child process */
            close(sockfd);      /* close original socket */
            str_echo(newsockfd);    /* process the request */
            exit(0);
        }

        close(newsockfd);       /* parent process */
    }
    return 0;
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

void str_echo(int sockfd)
{
    int n;
    char line[MAXLINE];

    for ( ; ; ) {
        n = readline(sockfd, line, MAXLINE);
        if (n == 0) {
            return;     /* connection terminated */
        } else if (n < 0) {
            puts("str_echo: readline error");
            exit(1);
        }

        if (writen(sockfd, line, n) != n) {
            puts("str_echo: writen error");
            exit(1);
        }
    }
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

void sig_child()
{
    int pid;
    int status;

    while ((pid = wait3(&status, WNOHANG, (struct rusage *) 0)) > 0) {
        ; // do nothing
    }
}
