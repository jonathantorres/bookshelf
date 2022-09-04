/*
 * Initialize a daemon process.
 */

#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>
#include    <signal.h>
#include    <sys/stat.h>
#include    <sys/param.h>
#include    <sys/types.h>
#include    <sys/wait.h>
#include    <errno.h>

#ifdef  SIGTSTP     /* true if BSD system */
#include    <sys/file.h>
#include    <sys/ioctl.h>
#endif

extern int  errno;

void daemon_start(int ignsigcld);
void sig_child();

int main(void)
{
    daemon_start(0);
    return 0;
}

/*
 * Detach a daemon process from login session context.
 */
/* nonzero -> handle SIGCLDs so zombies don't clog */
void daemon_start(int ignsigcld)
{
    register int    childpid, fd;

    /*
     * If we were started by init (process 1) from the /etc/inittab file
     * there's no need to detach.
     * This test is unreliable due to an unavoidable ambiguity
     * if the process is started by some other process and orphaned
     * (i.e., if the parent process terminates before we are started).
     */

    if (getppid() == 1) {
        goto out;
    }

    /*
     * Ignore the terminal stop signals (BSD).
     */

#ifdef SIGTTOU
    signal(SIGTTOU, SIG_IGN);
#endif
#ifdef SIGTTIN
    signal(SIGTTIN, SIG_IGN);
#endif
#ifdef SIGTSTP
    signal(SIGTSTP, SIG_IGN);
#endif

    /*
     * If we were not started in the background, fork and
     * let the parent exit.  This also guarantees the first child
     * is not a process group leader.
     */

    if ((childpid = fork()) < 0) {
        perror("can't fork first child");
        exit(1);
    } else if (childpid > 0) {
        exit(0);    /* parent */
    }

    /*
     * First child process.
     *
     * Disassociate from controlling terminal and process group.
     * Ensure the process can't reacquire a new controlling terminal.
     */

#ifdef  SIGTSTP     /* BSD */

    if (setpgid(0, getpid()) == -1) {
        perror("can't change process group");
        exit(1);
    }

    if ((fd = open("/dev/tty", O_RDWR)) >= 0) {
        ioctl(fd, TIOCNOTTY, NULL); /* lose controlling tty */
        close(fd);
    }

#else   /* System V */

    if (setpgrp() == -1) {
        perror("can't change process group");
        exit(1);
    }

    signal(SIGHUP, SIG_IGN);    /* immune from pgrp leader death */

    if ((childpid = fork()) < 0) {
        perror("can't fork second child");
        exit(1);
    } else if (childpid > 0) {
        exit(0);    /* first child */
    }

    /* second child */
#endif

out:
    /*
     * Close any open files descriptors.
     */

    for (fd = 0; fd < NOFILE; fd++) {
        close(fd);
    }

    errno = 0;      /* probably got set to EBADF from a close */

    /*
     * Move the current directory to root, to make sure we
     * aren't on a mounted filesystem.
     */

    chdir("/");

    /*
     * Clear any inherited file mode creation mask.
     */

    umask(0);

    /*
     * See if the caller isn't interested in the exit status of its
     * children, and doesn't want to have them become zombies and
     * clog up the system.
     * With System V all we need do is ignore the signal.
     * With BSD, however, we have to catch each signal
     * and execute the wait3() system call.
     */

    if (ignsigcld) {
#ifdef  SIGTSTP
        signal(SIGCHLD, sig_child);  /* BSD */
#else
        signal(SIGCHLD, SIG_IGN);    /* System V */
#endif
    }
}

void sig_child()
{
#ifdef  BSD
    /*
     * Use the wait3() system call with the WNOHANG option.
     */

    int  pid;
    int  status;

    while ((pid = wait3(&status, WNOHANG, (struct rusage *) 0)) > 0) {
        ; // do nothing
    }
#endif
}
