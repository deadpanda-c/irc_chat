#include "client.h"

int main(int ac, char **av)
{
    client_t client = {0};
    server_t server = {0};

    if (ac > 3 || ac == 1)
        return 84;
    if (ac == 2) {
        USAGE();
        return (!strcmp(av[1], "-h") || !strcmp(av[1], "--help")) ? 0 : 84;
    }

    init(&client, &server, av[1], av[2]);

    return 0;
}
