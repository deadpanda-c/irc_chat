#include "server.h"

static void set_socket_options(server_t *server)
{
    int result = 0;
    const int opt = 1;

    result = setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (result < 0) THROW_ERROR("setsockopt(SO_REUSEADDR)");
    INFO_LOG("Socket Options are now set correctly");
}

static void listen_server(server_t *server)
{
    int result = 0;

    result = listen(server->fd, 0);

    if (result < 0) THROW_ERROR("listen");
    INFO_LOG("THE SERVER IS WAITING FOR CLIENTS CONNECTIONS");
}

static void bind_server(server_t *server)
{
    int result = 0;

    result = bind(server->fd, (struct sockaddr *)&server->addr, (socklen_t)sizeof(server->addr));

    if (result < 0) THROW_ERROR("bind");
}

static void init_clients(client_t **clients)
{
    *clients = NULL;

    *clients = malloc(sizeof(client_t) * MAX_CLIENTS);
    if (!(*clients)) THROW_ERROR("malloc");

    for (int i = 0; i < MAX_CLIENTS; i++) {
        (*clients)[i].fd = 0;
    }
}

void init(server_t *server, const char *port_string)
{
    server->port = (unsigned short)atoi(port_string);
    server->fd = socket(AF_INET, SOCK_STREAM, 0);
    init_clients(&server->clients);

    if (server->fd < 0) THROW_ERROR("socket");

    set_socket_options(server);
    server->addr.sin_port = htons(server->port);
    server->addr.sin_family = AF_INET;
    server->addr.sin_addr.s_addr = INADDR_ANY;
    bind_server(server);
    listen_server(server);
}
