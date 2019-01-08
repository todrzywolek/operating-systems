#pragma once

#include "common.h"
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

void readdir_search(input_data *data);
DIR *open_directory(char *path);
char *create_file_path(input_data *in_data, char *file_name);
void search_nested_dir(input_data *parent_input_data, char *path);
void init_nested_input_data(input_data *nested_input_data, input_data *parent_data, char *path);
void process_file(struct stat *buf, input_data *data, char *file_name);
