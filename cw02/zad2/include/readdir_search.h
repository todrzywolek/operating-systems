#pragma once
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

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

void readdir_search(input_data *data);
DIR *open_directory(char *path);
char *create_file_path(input_data *in_data, char *file_name);
void search_nested_dir(input_data *parent_input_data, char *path);
void init_nested_input_data(input_data *nested_input_data, input_data *parent_data, char *path);
void set_file_access(char *access, struct stat *buf);
void process_file(struct stat *buf, input_data *data, char *file_name);
int check_if_allowed_for_process(time_t mdate, input_data *data);
void process(struct stat *buf, input_data *in_data, output_f_data *out_data);
void show_data(output_f_data *odata);
