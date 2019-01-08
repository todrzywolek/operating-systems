#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "ackermann.h"
#include "time_counter.h"

void validate_arguments_number(int number_of_arguments);
int convert_to_int(char const *source);

int main(int argc, char const *argv[])
{
    int m, n;
    struct tms tmsstart, tmsend;
    clock_t start, end;

    validate_arguments_number(argc);
    m = convert_to_int(argv[1]);
    n = convert_to_int(argv[2]);

    start = save_timestamp(&tmsstart);
    ackermann(m, n);
    end = save_timestamp(&tmsend);

    display_times(end - start, &tmsstart, &tmsend);

    return 0;
}

void validate_arguments_number(int number_of_arguments)
{
    if (number_of_arguments != 3)
    {
        printf("Invalid number of arguments\n");
        exit(-1);
    }
}

int convert_to_int(char const *source)
{
    errno = 0;
    char *p;
    long conv = strtol(source, &p, 10);

    if (errno != 0 || *p != '\0' || conv > INT_MAX)
    {
        printf("Invalid arguments\n");
        exit(-1);
    }
    else
        return conv;
}