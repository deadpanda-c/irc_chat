#include "server.h"
#include <stdbool.h>

static int add_clients(client_t *clients, int new_fd)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i].fd == 0) {
            clients[i].fd = new_fd;
            INFO_LOG("Client's file descriptor added to the list.");
            return 0;
        }
    }
    ERROR_LOG("Can't add the client's file descriptor to the list.");
    return -1;
}

static int accept_new_connection(server_t *server)
{
    int new_socket = 0;

    if (FD_ISSET(server->fd, &server->readfds)) {
        INFO_LOG("Trying to add a new connection");
        new_socket = accept(server->fd, (struct sockaddr *)&server->addr,\
                &server->socklen);
        if (new_socket < 0) THROW_ERROR("accept");

        send_to_fd(new_socket, WELCOME_MSG);

        return add_clients(server->clients, new_socket);
    }
    return 0;
}

static void set_max_fd(server_t *server, int *max_fd)
{
    *max_fd = server->fd;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd > 0)
            FD_SET(server->clients[i].fd, &server->readfds);
        if (server->clients[i].fd > *max_fd) {
            *max_fd = server->clients[i].fd;
        }
    }
}

void run(server_t *server)
{
    int max_fd = 0;

    while (true) {
        FD_ZERO(&server->readfds);
        FD_SET(server->fd, &server->readfds);

        set_max_fd(server, &max_fd);
        SELECT_FD(max_fd + 1, &server->readfds);

        accept_new_connection(server);
        parse_client_entry(server);
    }
}
