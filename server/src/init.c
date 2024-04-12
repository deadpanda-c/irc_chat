#include "server.h"

static void set_socket_options(server_t *server)
{
    int result = 0;
    const int opt = 1;

    result = setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (result < 0) THROW_ERROR("setsockopt(SO_REUSEADDR)");
    printf("[*] Socket Options are now set correctly\n");
}

static void listen_server(server_t *server)
{
    int result = 0;

    result = listen(server->fd, 0);

    if (result < 0) THROW_ERROR("listen");
    printf("[*] THE SERVER IS WAITING FOR CLIENTS CONNECTIONS\n");
}

static void bind_server(server_t *server)
{
    int result = 0;

    result = bind(server->fd, (struct sockaddr *)&server->addr, (socklen_t)sizeof(server->addr));

    if (result < 0) THROW_ERROR("bind");
    printf("[*] SERVER IS BINDED ON LOCALHOST ON PORT %d\n", server->port);
}

void init(server_t *server, const char *port_string)
{
    server->port = (unsigned short)atoi(port_string);
    server->fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server->fd < 0) THROW_ERROR("socket");

    server->addr.sin_port = htons(server->port);
    server->addr.sin_family = AF_INET;
    bind_server(server);
    listen_server(server);
    set_socket_options(server);
}
