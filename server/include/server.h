#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define USAGE "USAGE: ./myteams_server port\n\n\tport  is the port number on which server socket listens.\n"

#define THROW_ERROR(x) {\
    perror(x);\
    exit(84);\
}

typedef struct server_s {
    int fd;
    unsigned short port;
    struct sockaddr_in addr;
} server_t;

void init(server_t *server, const char *port_string);
void run(server_t *server);
void close_server(server_t *server);
