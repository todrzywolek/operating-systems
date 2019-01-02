#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "utils.h"

int convert_to_int(char const *source)
{
    errno = 0;
    char *p;
    long conv = strtol(source, &p, 10);

    if (errno != 0 || *p != '\0' || conv > INT_MAX)
    {
        printf("Error during conversion\n");
        exit(-1);
    }
    else
        return conv;
}