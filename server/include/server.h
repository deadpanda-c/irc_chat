#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define USAGE() printf("USAGE: ./myteams_server port\n\n\tport  is the port number on which server socket listens.\n");

#define INFO_LOG(msg) printf("[INFO] %s\n", msg);
#define ERROR_LOG(msg) printf("[ERROR] %s\n", msg);

#define THROW_ERROR(x) {\
    printf("[ERROR] %s\n", x);\
    exit(84);\
}

#define SELECT_FD(fd, set_fds) {\
    if (select(fd, set_fds, NULL, NULL, NULL) < 0 && errno != EINTR) {\
        printf("[ERROR] Select syscall failed\n");\
        exit(84);\
    }\
}

#define MAX_CLIENTS 1024
#define MAX_MSG_LENGTH 1024
#define WELCOME_MSG "Welcome to this IRC Chat !\n"

typedef struct client_s {
    int fd;
} client_t;

typedef struct server_s {
    int fd;
    unsigned short port;

    struct sockaddr_in addr;
    socklen_t socklen;

    fd_set readfds;

    client_t *clients;
    int nb_clients;
} server_t;

void init(server_t *server, const char *port_string);
void run(server_t *server);
void close_server(server_t *server);
void send_to_fd(int fd, const char *msg);
void parse_client_entry(server_t *server);
void disconnect_client(int *client_fd, fd_set *readfds);
