#include "client.h"

static void init_client(client_t *client)
{
    (void)client;
    client->fd = 0;
    client->username = NULL;
    client->fd = socket(AF_INET, SOCK_STREAM, 0);

}

static void init_server(server_t *server, char *ip, char *port)
{
    server->ip = strdup(ip);
    server->port = atoi(port);
}

void init(client_t *client, server_t *server, char *ip, char *port)
{
    init_client(client);
    init_server(server, ip, port);
}
