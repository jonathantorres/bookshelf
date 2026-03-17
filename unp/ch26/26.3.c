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

void *copyto(void *arg);
void str_cli(FILE *fp_arg, int sockfd_arg);
static int sockfd;
static FILE *fp;

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

void str_cli(FILE *fp_arg, int sockfd_arg)
{
    char recvline[MAXLINE];
    pthread_t tid;

    sockfd = sockfd_arg;
    fp     = fp_arg;

    Pthread_create(&tid, NULL, copyto, NULL);

    while (Readline(sockfd, recvline, MAXLINE) > 0) {
        Fputs(recvline, stdout);
    }
}

void *copyto(void *arg)
{
    char sendline[MAXLINE];

    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Writen(sockfd, sendline, strlen(sendline));
    }

    Shutdown(sockfd, SHUT_WR);

    return NULL;
}
