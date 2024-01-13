#include "csapp.h"

#define MAXENTRY 100

int parse_uri(char *uri, char *host, char *port, char *path);
void parse_block_file(char *filename, char list[MAXENTRY][MAXLINE], int limit);
int is_url_blocked(char *uri, char list[MAXENTRY][MAXLINE]);
void *handle_connection(void *vargp);

static char blocked_urls[MAXENTRY][MAXLINE];
static int log_fd;

int main(int argc, char **argv)
{
    int listenfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    int *connfdp;
    pthread_t tid;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }

    listenfd = Open_listenfd(argv[1]);

    log_fd = Open("log.txt", O_WRONLY | O_APPEND, 0);
    memset(blocked_urls, '\0', MAXLINE * MAXENTRY);
    parse_block_file("banned_urls.txt", blocked_urls, MAXENTRY);

    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfdp   = Malloc(sizeof(int));
        *connfdp  = Accept(listenfd, (SA *)&clientaddr, &clientlen);

        Pthread_create(&tid, NULL, handle_connection, connfdp);
    }

    Close(log_fd);
}

void *handle_connection(void *vargp)
{
    pthread_t tid = Pthread_self();
    Pthread_detach(tid);

    int connfd = *(int *)vargp;
    Free(vargp);

    rio_t client_rio, server_rio;
    char c_buf[MAXLINE], s_buf[MAXLINE];
    ssize_t sn, cn;

    char method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char host[MAXLINE], port[MAXLINE], path[MAXLINE];
    char log_buf[MAXLINE];

    int clientfd;
    Rio_readinitb(&server_rio, connfd);

    // parse HTTP request line
    if (!Rio_readlineb(&server_rio, s_buf, MAXLINE)) {
        Close(connfd);
        return NULL;
    }
    sscanf(s_buf, "%s %s %s", method, uri, version);

    // check if url is banned
    if (is_url_blocked(uri, blocked_urls)) {
        sprintf(log_buf, "visited banned url: %s\n", uri);
        Close(connfd);
        return NULL;
    }

    // log visit
    sprintf(log_buf, "url: %s\n", uri);
    Write(log_fd, log_buf, strlen(log_buf));

    memset(host, '\0', MAXLINE);
    memset(port, '\0', MAXLINE);
    memset(path, '\0', MAXLINE);

    int res;

    if ((res = parse_uri(uri, host, port, path)) == -1) {
        fprintf(stderr, "error parsing the url\n");
        Close(connfd);

        return NULL;
    } else if (res == 0) {
        fprintf(stderr, "malformed url path\n");
        Close(connfd);

        return NULL;
    }

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&client_rio, clientfd);

    sprintf(s_buf, "%s %s %s\n", method, path, version);
    Rio_writen(clientfd, s_buf, strlen(s_buf));

    do {
        sn = Rio_readlineb(&server_rio, s_buf, MAXLINE);
        Rio_writen(clientfd, s_buf, sn);
    } while (strcmp(s_buf, "\r\n"));

    while ((cn = Rio_readlineb(&client_rio, c_buf, MAXLINE)) != 0) {
        Rio_writen(connfd, c_buf, cn);
    }

    Close(connfd);
    Close(clientfd);
}

int parse_uri(char *uri, char *host, char *port, char *path)
{
    if (uri[0] == '/') {
        return 0;
    }

    char *prefix = "http://";
    int prelen   = strlen(prefix);

    if (strncmp(uri, prefix, prelen) != 0) {
        return -1;
    }

    char *start, *end;
    start = uri + prelen;
    end   = start;

    while (*end != ':' && *end != '/') {
        end++;
    }

    strncpy(host, start, end - start);

    if (*end == ':') {
        ++end;
        start = end;

        // copy port
        while (*end != '/') {
            end++;
        }

        strncpy(port, start, end - start);
    } else {
        strncpy(port, "80", 2);
    }

    strcpy(path, end);
}

void parse_block_file(char *filename, char list[MAXENTRY][MAXLINE], int limit)
{
    int blockfd;
    char block_buf[MAXLINE];
    rio_t block_rio;
    ssize_t block_n;

    blockfd = Open(filename, O_RDONLY, 0);
    Rio_readinitb(&block_rio, blockfd);

    memset(block_buf, '\0', MAXLINE);
    int num = 0;

    while ((block_n = Rio_readlineb(&block_rio, block_buf, MAXLINE)) != 0) {
        if (num == limit) {
            break;
        }

        if (strncmp(block_buf, "http://", 7) == 0) {
            strcpy(list[num], block_buf);
            num++;
        }
    }

    Close(blockfd);
}

int is_url_blocked(char *uri, char list[MAXENTRY][MAXLINE])
{
    int i;

    for (i = 0; list[i][0] != '\0'; i++) {
        if (strncmp(uri, list[i], strlen(uri)) == 0) {
            return 1;
        }
    }

    return 0;
}
