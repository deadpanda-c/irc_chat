#include "server.h"
#include "myteams/logging_client.h"

int main(int ac, char **av)
{
    server_t server = {0};

    if (ac != 2) {
        USAGE();
        return 84;
    }
    if (!strcmp(av[1], "-h") || !strcmp(av[1], "--help")) {
        USAGE();
        return 0;
    }
    init(&server, av[1]);
    run(&server);
//    close_server(&server);
    return 0;
}
