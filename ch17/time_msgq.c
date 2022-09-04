#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define KEY ((key_t) 54321)

#define COUNT    20000
#define BUFFSIZE 128
#define PERMS    0666

int main(void)
{
    int i, msqid;
    struct {
      long  m_type;
      char  m_text[BUFFSIZE];
    } msgbuff;

    if ((msqid = msgget(KEY, PERMS | IPC_CREAT)) < 0) {
        perror("msgget error");
        exit(1);
    }
    msgbuff.m_type = 1L;

    for (i = 0; i < COUNT; i++) {
        if (msgsnd(msqid, &msgbuff, BUFFSIZE, 0) < 0) {
            perror("msgsnd error");
            exit(1);
        }

        if (msgrcv(msqid, &msgbuff, BUFFSIZE, 0L, 0) != BUFFSIZE) {
            perror("msgrcv error");
            exit(1);
        }
    }

    if (msgctl(msqid, IPC_RMID, (struct msqid_ds *) 0) < 0) {
        perror("IPC_RMID error");
        exit(1);
    }

    puts("done");

    return 0;
}
