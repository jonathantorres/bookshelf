#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>

#ifdef NULL
#undef NULL
#endif

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct {
    unsigned int is_read  : 1;
    unsigned int is_write : 1;
    unsigned int is_unbuf : 1;
    unsigned int is_eof   : 1;
    unsigned int is_err   : 1;
} flags;

typedef struct _iobuf {
    int cnt;    /* Characters left */
    char *ptr;  /* next character position */
    char *base; /* location of buffer */
    flags flag; /* mode of file access */
    int fd;     /* file descriptor */
} FILE;

FILE _iob[OPEN_MAX];

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

enum _flags {
    _READ   = 01,   /* file open for reading */
    _WRITE  = 02,   /* file open for writing */
    _UNBUF  = 04,   /* file is unbuffered */
    _EOF    = 010,  /* EOF has occurred on this file */
    _ERR    = 020   /* error occurred on this file */
};

int _fillbuf(FILE *fp);
int _flushbuf(int n, FILE *fp);

#define feof(p)     (((p)->flag & _EOF) != 0)
#define ferror(p)   (((p)->flag & _ERR) != 0)
#define fileno(p)   ((p)->fd)

#define getc(p) (--(p)->cnt >= 0\
        ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 \
        ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()   getc(stdin)
#define putchar(x)  putc((x), stdout)

#define PERMS 0666

FILE *_fopen(char *name, char *mode);
int _fillbuff(FILE *fp);

int main(void)
{
    FILE *fp = _fopen("8-2.c", "r");
    assert(fp != NULL);
    return 0;
}

FILE *_fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;
    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if ((fp->flag.is_read == 0) && (fp->flag.is_write == 0)) {
            break;
        }
    }
    if (fp >= _iob + OPEN_MAX) {
        return NULL;
    }
    if (*mode == 'w') {
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1) {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }
    if (fd == -1) {
        return NULL;
    }
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag.is_read = 0;
    fp->flag.is_write = 0;
    fp->flag.is_unbuf = 0;
    fp->flag.is_eof = 0;
    fp->flag.is_err = 0;
    if (*mode == 'r') {
        fp->flag.is_read = 1;
        fp->flag.is_write = 0;
    } else {
        fp->flag.is_read = 0;
        fp->flag.is_write = 1;
    }
    return fp;
}

int _fillbuff(FILE *fp)
{
    int bufsize;
    if ((fp->flag.is_read == 0) || (fp->flag.is_eof == 1) || (fp->flag.is_err == 1)) {
        return EOF;
    }
    bufsize = (fp->flag.is_unbuf == 1) ? 1 : BUFSIZ;
    if (fp->base == NULL) {
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            return EOF;
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag.is_eof = 1;
        } else {
            fp->flag.is_err = 1;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}
