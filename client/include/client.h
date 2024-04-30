#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>

#define USAGE() printf("USAGE: ./irc_cli --help\n\tip  is the server ip address on which the server socket listens.\n\tport is the port number on which the server socket listens.\n");

typedef struct client_s {
    int fd;
    char *username;

    fd_set readfds;
    fd_set writefds;
} client_t;

typedef struct server_s {
    int fd;
    struct sockaddr_in addr;
    unsigned short port;
    char *ip;
} server_t;

void init(client_t *client, server_t *server, char *ip, char *port);
