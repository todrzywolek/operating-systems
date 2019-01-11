#include <stdio.h>
#include <stdlib.h>
#include "input_validation.h"

int read_producers_number(char const *argv[])
{
    int producers_number = atoi(argv[1]);
    if (producers_number <= 0)
    {
        printf("At least one producer is required. Given: %s\n", argv[1]);
        exit(-1);
    }
    return producers_number;
}

int read_consumers_number(char const *argv[])
{
    int consumers_number = atoi(argv[2]);
    if (consumers_number <= 0)
    {
        printf("At least one consumer is required. Given: %s\n", argv[2]);
        exit(-1);
    }
    return consumers_number;
}

int read_buffer_size(char const *argv[])
{
    int buffer_size = atoi(argv[3]);
    if (buffer_size <= 0)
    {
        printf("Buffer size must be greater than 0. Given: %s\n", argv[3]);
        exit(-1);
    }
    return buffer_size;
}

void validate_arguments_number(int number_of_arguments)
{
    if (number_of_arguments != 9)
    {
        printf("Invalid number of arguments\n");
        printf("Proper usage:\n");
        printf("\t<PRODUCERS> - number of producer threads\n");
        printf("\t<CONSUMERS> - number of consumer threads\n");
        printf("\t<BUFFER_SIZE> - size of global buffer\n");
        printf("\t<SOURCE_FILE> - source file name\n");
        printf("\t<LENGTH> - referential lenght for comparision\n");
        printf("\t<SEARCH_MODE> - program search mode. Possible values:\n");
        printf("\t\t1 - greater than <LENGHT> search mode\n");
        printf("\t\t2 - equal to <LENGHT> search mode\n");
        printf("\t\t3 - lower than <LENGHT> search mode\n");
        printf("\t<LOGGING_LEVEL> - program logging level. Possible values:\n");
        printf("\t\t1 - info logging level. Only consumers search results are displayed.\n");
        printf("\t\t2 - debug logging level. State of every producers and consumers are displayed.\n");
        printf("\t<nk> - program finish condition. Possible values:\n");
        printf("\t\tnk > 0 - program finishes after nk seconds.\n");
        printf("\t\tnk = 0 - program finishes after reaching end of source file.\n");

        exit(-1);
    }
}