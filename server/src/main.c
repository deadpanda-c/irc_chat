#include "server.h"

int main(int ac, char **av)
{
    server_t server = {0};

    if (ac != 2) {
        printf(USAGE);
        return 84;
    }
    if (!strcmp(av[1], "-h") || !strcmp(av[1], "--help")) {
        printf(USAGE);
        return 0;
    }
    init(&server, av[1]);
    run(&server);
    close_server(&server);
    return 0;
}
