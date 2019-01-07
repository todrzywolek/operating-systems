#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "readdir_search.h"
#include "nftw_search.h"

char sign;
int year;
int month;
int day;
input_data data;

void validate_args(int argc, char *argv[]);
void search(char *path, int mode);
void init_input_data_struct(input_data *data, char *path);

int main(int argc, char *argv[])
{
    validate_args(argc, argv);

    sign = argv[2][0];
    year = atoi(argv[3]);
    month = atoi(argv[4]);
    day = atoi(argv[5]);
    int mode = atoi(argv[6]);

    search(argv[1], mode);
    return 0;
}

void validate_args(int argc, char *argv[])
{
    if (argc != 7)
    {
        printf("Invalid args number. Expected 6, given %d!\n", argc - 1);
        exit(-1);
    }

    if (!isNumber(argv[3]) || !isNumber(argv[4]) || !isNumber(argv[5]) || !isNumber(argv[6]) || (argv[2][0] != '<' && argv[2][0] != '>' && argv[2][0] != '='))
    {
        printf("Invalid arguments!\n");
        exit(-1);
    }
}

void search(char *path, int mode)
{
    printf("Access%*sName%*sSize%*sModification date%*sAbsolute path\n", 6, "", 25, "", 5, "", 5, "");
    init_input_data_struct(&data, path);
    if (mode)
    {
        readdir_search(&data);
    }
    else
        nftw_search(path);
}

void init_input_data_struct(input_data *data, char *path)
{
    data->year = year;
    data->month = month;
    data->day = day;
    data->sign = sign;
    data->path = path;
}