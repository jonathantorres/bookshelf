#include "unp.h"

void Pthread_create(pthread_t *, const pthread_attr_t *, void *(*)(void *), void *);
void Pthread_join(pthread_t, void **);
void Pthread_detach(pthread_t);
void Pthread_kill(pthread_t, int);

void Pthread_mutexattr_init(pthread_mutexattr_t *);
void Pthread_mutexattr_setpshared(pthread_mutexattr_t *, int);
void Pthread_mutex_init(pthread_mutex_t *, pthread_mutexattr_t *);
void Pthread_mutex_lock(pthread_mutex_t *);
void Pthread_mutex_unlock(pthread_mutex_t *);

void Pthread_cond_broadcast(pthread_cond_t *);
void Pthread_cond_signal(pthread_cond_t *);
void Pthread_cond_wait(pthread_cond_t *, pthread_mutex_t *);
void Pthread_cond_timedwait(pthread_cond_t *, pthread_mutex_t *, const struct timespec *);

void Pthread_key_create(pthread_key_t *, void (*)(void *));
void Pthread_setspecific(pthread_key_t, const void *);
void Pthread_once(pthread_once_t *, void (*)(void));

typedef struct {
    int rl_cnt;
    char *rl_bufptr;
    char rl_buf[MAXLINE];
} Rline;

static pthread_key_t rl_key;
static pthread_once_t rl_once = PTHREAD_ONCE_INIT;
static void readline_destructor(void *ptr);
static void readline_once(void);
static ssize_t my_read(Rline *tsd, int fd, char *ptr);
ssize_t readline(int fd, void *vptr, size_t maxlen);
ssize_t Readline(int fd, void *ptr, size_t maxlen);
void str_cli(FILE *fp, int sockfd);

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2) {
        err_quit("usage: tcpcli <IPaddress>");
    }

    sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(SERV_PORT);
    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd);

    return 0;
}

void str_cli(FILE *fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];

    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Writen(sockfd, sendline, strlen(sendline));

        if (Readline(sockfd, recvline, MAXLINE) == 0) {
            err_quit("str_cli: server terminated prematurely");
        }

        Fputs(recvline, stdout);
    }
}

static void readline_destructor(void *ptr)
{
    free(ptr);
}

static void readline_once(void)
{
    Pthread_key_create(&rl_key, readline_destructor);
}

static ssize_t my_read(Rline *tsd, int fd, char *ptr)
{
    if (tsd->rl_cnt <= 0) {
    again:
        if ((tsd->rl_cnt = read(fd, tsd->rl_buf, MAXLINE)) < 0) {
            if (errno == EINTR) {
                goto again;
            }

            return -1;
        } else if (tsd->rl_cnt == 0) {
            return 0;
        }

        tsd->rl_bufptr = tsd->rl_buf;
    }

    tsd->rl_cnt--;
    *ptr = *tsd->rl_bufptr++;

    return 1;
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
    size_t n, rc;
    char c, *ptr;
    Rline *tsd;

    Pthread_once(&rl_once, readline_once);

    if ((tsd = pthread_getspecific(rl_key)) == NULL) {
        tsd = Calloc(1, sizeof(Rline));
        Pthread_setspecific(rl_key, tsd);
    }

    ptr = vptr;

    for (n = 1; n < maxlen; n++) {
        if ((rc = my_read(tsd, fd, &c)) == 1) {
            *ptr++ = c;

            if (c == '\n') {
                break;
            }
        } else if (rc == 0) {
            *ptr = 0;
            return n - 1;
        } else {
            return -1;
        }
    }

    *ptr = 0;

    return n;
}

ssize_t Readline(int fd, void *ptr, size_t maxlen)
{
    ssize_t n;

    if ((n = readline(fd, ptr, maxlen)) < 0) {
        err_sys("readline error");
    }

    return n;
}
