#include "server.h"

static char *get_client_msg(int *client_fd, fd_set *readfds)
{
    char *buffer = NULL;
    ssize_t valread = 0;

    buffer = malloc(sizeof(char) * (MAX_MSG_LENGTH + 1));
    if (!buffer) THROW_ERROR("malloc buffer");

    valread = read(*client_fd, buffer, MAX_MSG_LENGTH);
    if (valread == 0) {
        disconnect_client(client_fd, readfds);
        INFO_LOG("Client disconnected !");
        return NULL;
    }
    buffer[valread] = 0;
    return (valread < 0) ? NULL : buffer;
}

void parse_client_entry(server_t *server)
{
    char *client_buffer = NULL;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd <= 0)
            continue;
        if (FD_ISSET(server->clients[i].fd, &server->readfds)) {
            client_buffer = get_client_msg(&server->clients[i].fd, &server->readfds);
            if (!client_buffer) {
                server->nb_clients--;
                continue;
            }
        }
        if (client_buffer) {
            free(client_buffer);
            client_buffer = NULL;
        }
    }
}
