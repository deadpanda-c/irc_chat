#include "server.h"

void run(server_t *server)
{
    (void)server;
    printf("[*] SERVER IS RUNNING ON PORT %d\n", server->port);
}
