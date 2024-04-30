#include <string.h>
#include <stdbool.h>
#include "server.h"

static bool find_char(char token, char *src)
{
    for (int i = 0; src && src[i]; i++) {
        if (src[i] == token)
            return true;
    }
    return false;
}

static int count_delim(const char *delim, const char*src)
{
    int result = 0;

    for (int i = 0; delim[i]; i++) {
        for (int j = 0; src[j]; j++) {
            result += (src[j] == delim[i]) ? 1 : 0;
        }
    }
    return result;
}

char *trim(char *src, char *delim)
{
    char *result = NULL;
    int nb_delim = 0;
    int len_src = 0;
    int result_index = 0;

    if (!src)
        return NULL;
    len_src = (src) ? strlen(src) : 0;
    nb_delim = count_delim(delim, src);
    result = malloc(sizeof(char) * ((len_src + 1) - nb_delim));
    if (!result)
        THROW_ERROR("malloc trim");
    for (int i = 0; src[i]; i++) {
        if (find_char(src[i], delim))
            continue;
        result[result_index] = src[i];
        result_index++;
    }
    result[result_index] = 0;
    return result;
}
