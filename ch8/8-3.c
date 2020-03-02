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
    int fd; /* file descriptor */
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

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

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
int _fclose(FILE * file);
int _fflush(FILE * stream);

int main(void)
{
    FILE *fp = _fopen("8-2.c", "r");
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

int _flushbuf(int c, FILE *file)
{
    if (file < _iob || file >= _iob + OPEN_MAX) {
        return EOF;
    }
    int bufsize;
    bufsize = (file->flag.is_unbuf == 1) ? 1 : BUFSIZ;
    if (file->flag.is_write != 1) {
        return EOF;
    }
    if (file->flag.is_eof == 1 || file->flag.is_err == 1) {
        return EOF;
    }
    if (file->base == NULL && file->flag.is_unbuf == 0) {
        if ((file->base = (char * ) malloc(bufsize)) == NULL) {
            file->flag.is_unbuf = 1;
            file->flag.is_err = 1;
            file->cnt = 0;
            file->ptr = file->base;
            return EOF;
        }
    } else {
        if (write(file->fd, file->base, bufsize) == -1) {
            file->flag.is_err = 1;
            return EOF;
        }
    }
    file->cnt = 0;
    file->ptr = file->base;
    *file->ptr++ = c;
    return c;
}

int _fflush(FILE *stream)
{
    if (stream < _iob || stream >= _iob + OPEN_MAX) {
        return EOF;
    }
    int retval;
    FILE * fp;
    retval = 0;
    if (stream == NULL) {
        for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
            if (fp->flag.is_write == 0 && _fflush(fp) == -1) {
                retval = -1;
            }
        }
    } else {
        if (stream->flag.is_write == 0) {
            return -1;
        }
        _flushbuf(EOF, stream);
        if (stream->flag.is_err) {
            retval = -1;
        }
    }
    return retval;
}

int _fclose(FILE *file)
{
    int fd;
    if (file == NULL) {
        return -1;
    }
    fd = file->fd;
    _fflush(file);
    file->cnt = 0;
    file->ptr = NULL;
    if (file->base != NULL) {
        free(file->base);
    }
    file->base = NULL;
    file->flag.is_write = 0;
    file->flag.is_read = 0;
    file->flag.is_unbuf = 0;
    file->flag.is_eof = 0;
    file->flag.is_err = 0;
    file->fd = -1;
    return close(fd);
}
