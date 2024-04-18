#include "server.h"

void send_to_fd(int fd, const char *msg)
{
    write(fd, msg, strlen(msg));
}
