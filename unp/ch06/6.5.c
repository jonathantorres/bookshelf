#include "unp.h"

// The server still sends data to the client
// but this client acknowledges it and throws it away

int main(void)
{
    int serv_fd;
    struct sockaddr_in serv_addr;

    serv_fd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_port        = htons(19);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    socklen_t serv_addr_siz = sizeof(serv_addr);

    Connect(serv_fd, (SA *)&serv_addr, serv_addr_siz);

    pause();

    return 0;
}
