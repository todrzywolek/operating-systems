#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/times.h>
#include "time_counter.h"

int main(int argc, char const *argv[])
{
    int i;
    for (i = 1; i < argc; i++)
        execute_cmd_and_measure_time(argv[i], i, argc - 1);
    exit(0);

    //    printf("%ld\n", ackermann(3, 14));
    //  return 0;
}