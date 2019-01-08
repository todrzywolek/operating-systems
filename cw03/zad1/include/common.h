#pragma once

#include <time.h>
#include <sys/stat.h>

typedef struct
{
    int year;
    int month;
    int day;
    char sign;
    char *path;
} input_data;

typedef struct
{
    char *access;
    char *d_name;
    int fsize;
    char *apath;
    time_t mdate;
} output_f_data;

int check_if_allowed_for_process(time_t mdate, input_data *data);
void process(const struct stat *buf, input_data *in_data, output_f_data *out_data);
void set_file_access(char *access, const struct stat *buf);
void show_data(output_f_data *odata);