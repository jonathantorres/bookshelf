#include "apue.h"
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void)
{
    char *m = "foo";

    for (int i = 0; i < 5; ++i) {
        key_t k;
        int id;

        k  = ftok("/dev/null", i);
        id = msgget(k, IPC_CREAT | S_IWUSR | S_IRUSR);

        printf("id: %d\n", id);
        msgctl(id, IPC_RMID, NULL);
    }

    for (int i = 0; i < 5; ++i) {
        int id = msgget(IPC_PRIVATE, IPC_CREAT | S_IWUSR | S_IRUSR);

        msgsnd(id, m, sizeof(m), 0);
        msgctl(id, IPC_RMID, NULL);
    }

    return 0;
}
