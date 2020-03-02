#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define NAME_MAX 14

typedef struct {
    long ino;
    char name[NAME_MAX+1];
} Dirent;

typedef struct {
    int fd;
    Dirent d;
} DIR;

DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);

char *name;
struct stat stbuf;
void fsize(char *);

int main(int argc, char **argv)
{
    if (argc == 1) {
        fsize(".");
    } else {
        while (--argc > 0) {
            fsize(*++argv);
        }
    }
    return 0;
}

void dirwalk(char *, void (*fcn)(char *));

void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
    }
    printf("\n%8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s %8s",
        "size", "blocks", "blksize", "nlink", "dev", "ino",
        "mode", "uid", "gid", "rdev", "atime", "mtime","ctime", "name\n");
    printf("%8ld %8ld %8ld %8ld %8ld %8lu %8u %8u %8u %8lu %8ld %8ld %8ld %s\n",
        stbuf.st_size, stbuf.st_blocks, stbuf.st_blksize,
        stbuf.st_nlink, stbuf.st_dev, stbuf.st_ino,
        stbuf.st_mode, stbuf.st_uid, stbuf.st_gid,
        stbuf.st_rdev, stbuf.st_atime, stbuf.st_mtime,
        stbuf.st_ctime, name);
}

#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    Dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->name, ".") == 0
        || strcmp(dp->name, "..") == 0) {
            continue;
        }
        if (strlen(dir)+strlen(dp->name)+2 > sizeof(name)) {
            fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->name);
        } else {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

#ifndef DIRSIZ
#define DIRSIZ 14
#endif

struct direct {
    ino_t d_ino;
    char d_name[DIRSIZ];
};

DIR *opendir(char *dirname)
{
    int fd;
    struct stat stbuf;
    DIR *dp;
    if ((fd = open(dirname, O_RDONLY, 0)) == -1
        || fstat(fd, &stbuf) == -1
        || (stbuf.st_mode & S_IFMT) != S_IFDIR
        || (dp = (DIR *) malloc(sizeof(DIR))) == NULL) {
        return NULL;
    }
    dp->fd = fd;
    return dp;
}

Dirent *readdir(DIR *dp)
{
    struct direct dirbuf;
    static Dirent d;
    while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
        if (dirbuf.d_ino == 0) {
            continue;
        }
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0';
        return &d;
    }
    return NULL;
}

void closedir(DIR *dp)
{
    if (dp) {
        close(dp->fd);
        free(dp);
    }
}
