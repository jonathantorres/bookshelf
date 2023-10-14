#include "csapp.h"

#define MAXJOBS 128
#define MAXARGS 128

enum job_status { running, stopped };

typedef int job_id;

typedef struct {
    job_id id;
    pid_t pid;
    enum job_status status;
    char cmdline[MAXLINE];
    int using;
} job_t, *job_ptr;

static volatile sig_atomic_t fg_pid;
static job_t jobs[MAXJOBS];

static int is_fg_pid(pid_t pid);
static pid_t get_fg_pid();
static void set_fg_pid(pid_t pid);
static void init_jobs();
static void print_jobs();
static int new_job(pid_t pid, char *cmdline, int fg);
static void del_job_by_pid(pid_t pid);
static job_ptr find_job_by_pid(pid_t pid);
static job_ptr find_job_by_jid(job_id id);
static void set_job_status(job_ptr jp, enum job_status status);
static int find_spare_jid();

void sigchild_handler(int sig);
void sigint_handler(int sig);
void sigstop_handler(int sig);

static void eval(char *cmdline);
static int parse_id(char *s);
static int is_number_str(char *s);
static int parseline(char *buf, char **argv);
static int builtin_command(char **argv);

int main(int argc, char **argv)
{
    init_jobs();

    // handle signals
    if (Signal(SIGCHLD, sigchild_handler) == SIG_ERR) {
        unix_error("signal child handler error");
    }

    if (Signal(SIGINT, sigint_handler) == SIG_ERR) {
        unix_error("signal int handler error");
    }

    if (Signal(SIGTSTP, sigstop_handler) == SIG_ERR) {
        unix_error("signal stop handler error");
    }

    char cmdline[MAXLINE];

    while (1) {
        printf("> ");
        Fgets(cmdline, MAXLINE, stdin);

        if (feof(stdin)) {
            exit(0);
        }

        eval(cmdline);
    }
}

static void eval(char *cmdline)
{
    char *argv[MAXARGS];
    char buf[MAXLINE];
    int bg;
    pid_t pid;

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);

    // ignore empty lines
    if (argv[0] == NULL) {
        return;
    }

    if (!builtin_command(argv)) {
        sigset_t mask_one, prev_one;
        Sigemptyset(&mask_one);
        Sigaddset(&mask_one, SIGCHLD);

        // block signal child
        Sigprocmask(SIG_BLOCK, &mask_one, &prev_one);

        if ((pid = Fork()) == 0) {
            // unblock in child process
            Sigprocmask(SIG_SETMASK, &prev_one, NULL);

            // set gid same like pid
            Setpgid(0, 0);

            if (execvp(argv[0], argv) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        sigset_t mask_all, prev_all;
        Sigfillset(&mask_all);

        // save job info
        Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
        job_id new_jid = new_job(pid, cmdline, !bg);
        Sigprocmask(SIG_SETMASK, &prev_all, NULL);

        if (!bg) {
            set_fg_pid(pid);

            while (get_fg_pid()) {
                sigsuspend(&prev_one);
            }
        } else {
            printf("[%d] %d %s \t %s\n", new_jid, pid, "Running", cmdline);
        }

        // unblock child signal
        Sigprocmask(SIG_SETMASK, &prev_one, NULL);
    }
}

static int builtin_command(char **argv)
{
    if (strcmp(argv[0], "quit") == 0) {
        exit(0);
    }

    if (strcmp(argv[0], "&") == 0) {
        return 1;
    }

    if (strcmp(argv[0], "jobs") == 0) {
        print_jobs();
        return 1;
    }

    if (strcmp(argv[0], "fg") == 0) {
        int id;

        if ((id = parse_id(argv[1])) != -1 && argv[2] == NULL) {
            sigset_t mask_one, prev_one;
            Sigemptyset(&mask_one);
            Sigaddset(&mask_one, SIGCHLD);
            Sigprocmask(SIG_BLOCK, &mask_one, &prev_one);

            pid_t pid = id;

            // if param is a job id
            if (argv[1][0] == '%') {
                job_ptr jp = find_job_by_jid(id);
                pid        = jp->pid;
            }

            Kill(pid, SIGCONT);
            set_fg_pid(pid);

            while (get_fg_pid()) {
                sigsuspend(&prev_one);
            }

            Sigprocmask(SIG_SETMASK, &prev_one, NULL);
        } else {
            printf("format error, e.g. fg %%12 || fg 1498\n");
        }

        return 1;
    }

    if (strcmp(argv[0], "bg") == 0) {
        int id;

        // right format: bg %ddd or bg ddd
        if ((id = parse_id(argv[1])) != -1 && argv[2] == NULL) {
            pid_t pid = id;

            // param is a job id
            if (argv[1][0] == '%') {
                job_ptr jp = find_job_by_jid(id);
                pid        = jp->pid;
            }

            Kill(pid, SIGCONT);
        } else {
            printf("format error, e.g. bg %%12  or  bg 1498\n");
        }

        return 1;
    }

    // Not a builtin command
    return 0;
}

static int parseline(char *buf, char **argv)
{
    char *delim;
    int argc;
    int bg;

    // Replace trailing '\n' with space
    buf[strlen(buf) - 1] = ' ';

    // Ignore leading spaces
    while (*buf && (*buf == ' ')) {
        buf++;
    }

    // Build the argv list
    argc = 0;

    while ((delim = strchr(buf, ' '))) {
        argv[argc++] = buf;
        *delim       = '\0';
        buf          = delim + 1;

        // ignore spaces
        while (*buf && (*buf == ' ')) {
            buf++;
        }
    }

    argv[argc] = NULL;

    if (argc == 0) {
        return 1;
    }

    // Should the job run in the background?
    if ((bg = (*argv[argc - 1] == '&')) != 0) {
        argv[--argc] = NULL;
    }

    return bg;
}

static int is_number_str(char *s)
{
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        if (!isdigit(s[i])) {
            return 0;
        }
    }

    return 1;
}

static int parse_id(char *s)
{
    int error = -1;

    if (s == NULL) {
        return error;
    }

    if (s[0] == '%') {
        if (!is_number_str(s + 1)) {
            return error;
        }

        return atoi(s + 1);
    }

    if (is_number_str(s)) {
        return atoi(s);
    }

    return error;
}

static int is_fg_pid(pid_t pid)
{
    return fg_pid == pid;
}

static pid_t get_fg_pid()
{
    return fg_pid;
}

static void set_fg_pid(pid_t pid)
{
    fg_pid = pid;
}

void sigchild_handler(int sig)
{
    int old_errno = errno;
    int status;
    pid_t pid;

    sigset_t mask_all, prev_all;
    Sigfillset(&mask_all);

    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0) {
        if (WIFEXITED(status) || WIFSIGNALED(status)) {
            if (is_fg_pid(pid)) {
                set_fg_pid(0);
            } else {
                Sio_puts("pid ");
                Sio_putl(pid);
                Sio_puts(" terminates\n");
            }

            Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
            del_job_by_pid(pid);
            Sigprocmask(SIG_SETMASK, &prev_all, NULL);
        }

        if (WIFSTOPPED(status)) {
            if (is_fg_pid(pid)) {
                set_fg_pid(0);
            }

            // set pid status stopped
            Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);

            job_ptr jp = find_job_by_pid(pid);
            set_job_status(jp, stopped);

            Sigprocmask(SIG_SETMASK, &prev_all, NULL);
            Sio_puts("pid ");
            Sio_putl(pid);
            Sio_puts(" be stopped\n");
        }

        if (WIFCONTINUED(status)) {
            set_fg_pid(pid);

            // set pid status running
            Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
            job_ptr jp = find_job_by_pid(pid);
            set_job_status(jp, running);
            Sigprocmask(SIG_SETMASK, &prev_all, NULL);

            Sio_puts("pid ");
            Sio_putl(pid);
            Sio_puts(" continue\n");
        }
    }

    errno = old_errno;
}

void sigint_handler(int sig)
{
    if (is_fg_pid(0)) {
        Signal(SIGINT, SIG_DFL);
        Kill(getpid(), SIGINT);
    } else {
        Kill(get_fg_pid(), SIGINT);
    }
}

void sigstop_handler(int sig)
{
    if (is_fg_pid(0)) {
        Signal(SIGTSTP, SIG_DFL);
        Kill(getpid(), SIGTSTP);
    } else {
        Kill(get_fg_pid(), SIGTSTP);
    }
}

static job_ptr find_job_by_jid(job_id id)
{
    return &(jobs[id]);
}

static job_ptr find_job_by_pid(pid_t pid)
{
    for (int i = 0; i < MAXJOBS; i++) {
        job_t j = jobs[i];

        if (j.using && j.pid == pid) {
            return &(jobs[i]);
        }
    }

    return NULL;
}

static void set_job_status(job_ptr jp, enum job_status status)
{
    if (jp) {
        jp->status = status;
    }
}

static int find_spare_jid()
{
    job_id id = -1;

    for (int i = 0; i < MAXJOBS; i++) {
        if (jobs[i].using == 0) {
            id = i;
            break;
        }
    }

    return id;
}

static int new_job(pid_t pid, char *cmdline, int fg)
{
    // find a job id
    job_id id = find_spare_jid();

    if (id == -1) {
        unix_error("no more job ids to use");
    }

    // save process info
    jobs[id].id     = id;
    jobs[id].pid    = pid;
    jobs[id].status = running;

    strcpy(jobs[id].cmdline, cmdline);

    jobs[id].using = 1;

    return id;
}

static void del_job_by_pid(pid_t pid)
{
    for (int i = 0; i < MAXJOBS; i++) {
        if (jobs[i].using && jobs[i].pid == pid) {
            jobs[i].using = 0;
        }
    }
}

static void print_jobs()
{
    for (int i = 0; i < MAXJOBS; i++) {
        job_t j = jobs[i];

        if (j.using) {
            printf("[%d] %d %s \t %s\n", j.id, j.pid, j.status == running ? "Running" : "Stopped",
                   j.cmdline);
        }
    }
}

static void init_jobs()
{
    memset(jobs, 0, sizeof(jobs));
}
