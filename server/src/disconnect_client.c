#include "server.h"

void disconnect_client(int *client_fd, fd_set *readfds)
{
    FD_CLR(*client_fd, readfds);
    close(*client_fd);
    *client_fd = 0;
}
