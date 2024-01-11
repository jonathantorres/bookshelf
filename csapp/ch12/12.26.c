#include "csapp.h"

static sem_t mutex;

static void init_mutex(void)
{
    Sem_init(&mutex, 0, 1);
}

struct hostent *gethostbyname_ts(const char *name, struct hostent *host)
{
    struct hostent *sharehost;

    P(&mutex);

    sharehost        = gethostbyname(name);
    host->h_addrtype = sharehost->h_addrtype;
    host->h_length   = sharehost->h_length;
    host->h_name     = (char *)Malloc(strlen(sharehost->h_name));

    strcpy(host->h_name, sharehost->h_name);

    int i;
    for (i = 0; sharehost->h_aliases[i] != NULL; i++) {
        // nothing to do
    }
    host->h_aliases = (char **)Malloc(sizeof(char *) * (i + 1));
    for (i = 0; sharehost->h_aliases[i] != NULL; i++) {
        host->h_aliases[i] = (char *)Malloc(strlen(sharehost->h_aliases[i]));
        strcpy(host->h_aliases[i], sharehost->h_aliases[i]);
    }
    host->h_aliases[i] = NULL;

    for (i = 0; sharehost->h_addr_list[i] != NULL; i++) {
        // nothing to do
    }
    host->h_addr_list = (char **)Malloc(sizeof(char *) * (i + 1));
    for (i = 0; sharehost->h_addr_list[i] != NULL; i++) {
        host->h_addr_list[i] = (char *)Malloc(strlen(sharehost->h_addr_list[i]));
        strcpy(host->h_addr_list[i], sharehost->h_addr_list[i]);
    }

    host->h_addr_list[i] = NULL;
    V(&mutex);

    return host;
}

int main(int argc, char *argv[])
{
    init_mutex();

    struct hostent host;
    gethostbyname_ts("127.0.0.1", &host);

    printf("%s\n", host.h_name);

    return 0;
}
