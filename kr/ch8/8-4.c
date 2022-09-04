#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

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

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

int _fseek(FILE *fp, long offset, int origin);

int main(void)
{
    return 0;
}

int _fseek(FILE *fp, long offset, int origin)
{
    if (fp->flag.is_read == 0) {
        return -1;
    }
    if (origin == SEEK_SET) {
        if (offset < fp->cnt) {
            fp->ptr = fp->base + offset;
            fp->cnt = offset;
            lseek(fp->fd, offset, origin);
            fp->flag.is_eof = 0;
        } else {
            return fp->cnt - offset;
        }
    } else if (origin == SEEK_CUR) {
        if (offset < fp->cnt) {
            fp->ptr += fp->cnt - (fp->cnt - offset);
            fp->cnt = offset;
            lseek(fp->fd, offset, origin);
            fp->flag.is_eof = 0;
        } else {
            return fp->cnt - offset;
        }
    } else if (origin == SEEK_END) {
        if (offset <= 0 && fp->ptr + offset >= fp->base) {
            fp->ptr += offset;
            fp->cnt = lseek(fp->fd, offset, origin);
            fp->flag.is_eof = 0;
        }
    } else {
        return -1;
    }
    return 0;
}
