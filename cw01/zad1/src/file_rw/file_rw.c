#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "time_counter.h"

void validate_arguments_number(int number_of_arguments);
int convert_to_int(char const *source);
void open_read_close_file(FILE *fp);

int main(int argc, char const *argv[])
{
    validate_arguments_number(argc);
    FILE *fp;
    struct tms tmsstart, tmsend;
    clock_t start, end;
    int limit;

    limit = convert_to_int(argv[1]);

    start = save_timestamp(&tmsstart);

    for (int i = 0; i < limit; i++)
        open_read_close_file(fp);

    end = save_timestamp(&tmsend);

    display_times(end - start, &tmsstart, &tmsend);

    return 0;
}

void validate_arguments_number(int number_of_arguments)
{
    if (number_of_arguments != 2)
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

void open_read_close_file(FILE *fp)
{
    fp = fopen("file.txt", "w");
    fprintf(fp, "a");
    fclose(fp);
}