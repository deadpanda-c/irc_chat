#include <uuid.h>

#include "server.h"

int log_client_in(server_t *server, client_t *client)
{
    (void)server;

    char *trimmed_line = NULL;
    int len_buffer = 0;

    if (client->username && client->uuid) { // Client not logged in if username is NULL
        send_to_fd(client->fd, ALREADY_CONNECTED);
        return 0;
    }
    // log the client in
    // uuid generate
    // username
    trimmed_line = trim(client->buffer, " \n");
    if (!strcmp(LOGIN, trimmed_line)) {
        send_to_fd(client->fd, SYNTAX_ERROR);
        return 0;
    }
    len_buffer = strlen(client->buffer);
    if (len_buffer > 6) { // 6 is "LOGIN "
        printf("username: [%s]\n", strchr(client->buffer, ' '));

        printf("TRIM: %s\n", trim(client->buffer, "\n"));
        send_to_fd(client->fd, LOGIN_SUCCESSFUL);
        return 1;
    }
    return 1;
}
