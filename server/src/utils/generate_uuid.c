#include <uuid/uuid.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

char *generate_uuid(void)
{
    uuid_t binuuid;
    char *uuid = NULL;

    uuid = malloc(UUID_LENGTH);
    if (!uuid)
        THROW_ERROR("malloc uuid");
    uuid_generate_random(binuuid);
    uuid_unparse_upper(binuuid, uuid);
    printf("UUID: %s\n", uuid);
    return uuid;
}
