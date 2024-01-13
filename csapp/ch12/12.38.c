#include "csapp.h"

#define SBUFSIZE      4
#define INIT_THREAD_N 1
#define THREAD_LIMIT  4096

typedef struct {
    int *buf;    /* Buffer array */
    int n;       /* Maximum number of slots */
    int front;   /* buf[(front+1)%n] is first item */
    int rear;    /* buf[rear%n] is last item */
    sem_t mutex; /* Protects accesses to buf */
    sem_t slots; /* Counts available slots */
    sem_t items; /* Counts available items */
} sbuf_t;

typedef struct {
    pthread_t tid;
    sem_t mutex;
} ithread;

static int nthreads;
static sbuf_t sbuf;
static ithread threads[THREAD_LIMIT];

void *adjust_threads(void *);
void create_threads(int start, int end);
void init_threads(void);
void *serve_thread(void *vargp);
void doit(int fd);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);
void sbuf_init(sbuf_t *sp, int n);
void sbuf_deinit(sbuf_t *sp);
void sbuf_insert(sbuf_t *sp, int item);
int sbuf_remove(sbuf_t *sp);
int sbuf_empty(sbuf_t *sp);
int sbuf_full(sbuf_t *sp);

int main(int argc, char **argv)
{
    int listenfd, connfd, i;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }

    listenfd = Open_listenfd(argv[1]);
    init_threads();

    Pthread_create(&tid, NULL, adjust_threads, NULL);

    while (1) {
        clientlen = sizeof(clientaddr);
        connfd    = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);
        sbuf_insert(&sbuf, connfd); /* Insert connfd in buffer */
    }
}

void doit(int fd)
{
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;

    /* Read request line and headers */
    Rio_readinitb(&rio, fd);
    if (!Rio_readlineb(&rio, buf, MAXLINE)) {
        return;
    }

    printf("%s", buf);
    sscanf(buf, "%s %s %s", method, uri, version);

    if (strcasecmp(method, "GET")) {
        clienterror(fd, method, "501", "Not Implemented", "Tiny does not implement this method");
        return;
    }

    read_requesthdrs(&rio);

    /* Parse URI from GET request */
    is_static = parse_uri(uri, filename, cgiargs);
    if (stat(filename, &sbuf) < 0) {
        clienterror(fd, filename, "404", "Not found", "Tiny couldn't find this file");
        return;
    }

    /* Serve static content */
    if (is_static) {
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
            clienterror(fd, filename, "403", "Forbidden", "Tiny couldn't read the file");
            return;
        }
        serve_static(fd, filename, sbuf.st_size);
    } else {
        /* Serve dynamic content */
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
            clienterror(fd, filename, "403", "Forbidden", "Tiny couldn't run the CGI program");
            return;
        }
        serve_dynamic(fd, filename, cgiargs);
    }
}

/*
 * read_requesthdrs - read HTTP request headers
 */
void read_requesthdrs(rio_t *rp)
{
    char buf[MAXLINE];

    Rio_readlineb(rp, buf, MAXLINE);
    printf("%s", buf);

    while (strcmp(buf, "\r\n")) {
        Rio_readlineb(rp, buf, MAXLINE);
        printf("%s", buf);
    }

    return;
}

/*
 * parse_uri - parse URI into filename and CGI args
 *             return 0 if dynamic content, 1 if static
 */
int parse_uri(char *uri, char *filename, char *cgiargs)
{
    char *ptr;

    if (!strstr(uri, "cgi-bin")) {
        /* Static content */
        strcpy(cgiargs, "");
        strcpy(filename, ".");
        strcat(filename, uri);

        if (uri[strlen(uri) - 1] == '/') {
            strcat(filename, "home.html");
        }

        return 1;
    } else {
        /* Dynamic content */
        ptr = index(uri, '?');
        if (ptr) {
            strcpy(cgiargs, ptr + 1);
            *ptr = '\0';
        } else {
            strcpy(cgiargs, "");
        }

        strcpy(filename, ".");
        strcat(filename, uri);
        return 0;
    }
}

/*
 * serve_static - copy a file back to the client
 */
void serve_static(int fd, char *filename, int filesize)
{
    int srcfd;
    char *srcp, filetype[MAXLINE], buf[MAXBUF];

    /* Send response headers to client */
    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n", filesize);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: %s\r\n\r\n", filetype);
    Rio_writen(fd, buf, strlen(buf));

    /* Send response body to client */
    srcfd = Open(filename, O_RDONLY, 0);
    srcp  = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);

    Close(srcfd);
    Rio_writen(fd, srcp, filesize);
    Munmap(srcp, filesize);
}

/*
 * get_filetype - derive file type from file name
 */
void get_filetype(char *filename, char *filetype)
{
    if (strstr(filename, ".html")) {
        strcpy(filetype, "text/html");
    } else if (strstr(filename, ".gif")) {
        strcpy(filetype, "image/gif");
    } else if (strstr(filename, ".png")) {
        strcpy(filetype, "image/png");
    } else if (strstr(filename, ".jpg")) {
        strcpy(filetype, "image/jpeg");
    } else {
        strcpy(filetype, "text/plain");
    }
}

/*
 * serve_dynamic - run a CGI program on behalf of the client
 */
void serve_dynamic(int fd, char *filename, char *cgiargs)
{
    char buf[MAXLINE], *emptylist[] = {NULL};

    /* Return first part of HTTP response */
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Server: Tiny Web Server\r\n");
    Rio_writen(fd, buf, strlen(buf));

    if (Fork() == 0) {
        /* Child */
        setenv("QUERY_STRING", cgiargs, 1);

        /* Redirect stdout to client */
        Dup2(fd, STDOUT_FILENO);

        /* Run CGI program */
        Execve(filename, emptylist, environ);
    }

    /* Parent waits for and reaps child */
    Wait(NULL);
}

/*
 * clienterror - returns an error message to the client
 */
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg)
{
    char buf[MAXLINE];

    /* Print the HTTP response headers */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n\r\n");
    Rio_writen(fd, buf, strlen(buf));

    /* Print the HTTP response body */
    sprintf(buf, "<html><title>Tiny Error</title>");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<body bgcolor="
                 "ffffff"
                 ">\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "%s: %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<p>%s: %s\r\n", longmsg, cause);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "<hr><em>The Tiny Web server</em>\r\n");
    Rio_writen(fd, buf, strlen(buf));
}

void sbuf_init(sbuf_t *sp, int n)
{
    sp->buf   = Calloc(n, sizeof(int));
    sp->n     = n;
    sp->front = sp->rear = 0;

    Sem_init(&sp->mutex, 0, 1);
    Sem_init(&sp->slots, 0, n);
    Sem_init(&sp->items, 0, 0);
}

void sbuf_deinit(sbuf_t *sp)
{
    Free(sp->buf);
}

void sbuf_insert(sbuf_t *sp, int item)
{
    P(&sp->slots);
    P(&sp->mutex);

    sp->buf[(++sp->rear) % (sp->n)] = item;

    V(&sp->mutex);
    V(&sp->items);
}

int sbuf_remove(sbuf_t *sp)
{
    int item;

    P(&sp->items);
    P(&sp->mutex);

    item = sp->buf[(++sp->front) % (sp->n)];

    V(&sp->mutex);
    V(&sp->slots);

    return item;
}

int sbuf_empty(sbuf_t *sp)
{
    int e;

    P(&sp->mutex);
    e = sp->front == sp->rear;
    V(&sp->mutex);

    return e;
}

int sbuf_full(sbuf_t *sp)
{
    int f;

    P(&sp->mutex);
    f = (sp->rear - sp->front) == sp->n;
    V(&sp->mutex);

    return f;
}

void init_threads(void)
{
    nthreads = INIT_THREAD_N;
    sbuf_init(&sbuf, SBUFSIZE);

    create_threads(0, nthreads);
}

void *serve_thread(void *vargp)
{
    int idx = *(int *)vargp;
    Free(vargp);

    while (1) {
        P(&(threads[idx].mutex));

        int connfd = sbuf_remove(&sbuf);
        doit(connfd);
        Close(connfd);

        V(&(threads[idx].mutex));
    }
}

void create_threads(int start, int end)
{
    int i;

    for (i = start; i < end; i++) {
        Sem_init(&(threads[i].mutex), 0, 1);

        int *arg = (int *)Malloc(sizeof(int));
        *arg     = i;

        Pthread_create(&(threads[i].tid), NULL, serve_thread, arg);
    }
}

void *adjust_threads(void *vargp)
{
    sbuf_t *sp = &sbuf;

    while (1) {
        // if sbuf is full, double threads
        if (sbuf_full(sp)) {
            if (nthreads == THREAD_LIMIT) {
                fprintf(stderr, "too many threads, can't double\n");
                continue;
            }

            // double n
            int dn = 2 * nthreads;
            create_threads(nthreads, dn);
            nthreads = dn;
            continue;
        }

        // half threads
        if (sbuf_empty(sp)) {
            if (nthreads == 1) {
                continue;
            }

            // half n
            int hn = nthreads / 2;
            int i;

            for (i = hn; i < nthreads; i++) {
                P(&(threads[i].mutex));
                Pthread_cancel(threads[i].tid);
                V(&(threads[i].mutex));
            }
            nthreads = hn;
            continue;
        }
    }
}
