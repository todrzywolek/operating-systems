#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "utils.h"
#include "readdir_search.h"

void readdir_search(input_data *data)
{
    DIR *dir = open_directory(data->path);
    struct dirent *pDirent;
    for (pDirent = readdir(dir); pDirent != NULL; pDirent = readdir(dir))
    {
        if (!strcmp(pDirent->d_name, ".") || !strcmp(pDirent->d_name, ".."))
            continue;

        char *fpath = create_file_path(data, pDirent->d_name);

        struct stat buf;
        if (lstat(fpath, &buf) != 0)
        {
            printf("Error reading struct!");
            return;
        }
        if (S_ISDIR(buf.st_mode))
        {
            if (!vfork())
            {
                search_nested_dir(data, fpath);
            }
        }
        else if (S_ISREG(buf.st_mode))
        {
            process_file(&buf, data, pDirent->d_name);
        }
        free(fpath);
    }
    if (errno > 0)
    {
        printf("Failed reading the directory %s! Error no %i.\n", data->path, errno);
    }
}

DIR *open_directory(char *path)
{
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        printf("No such directory!\n");
        exit(-1);
    }

    return dir;
}

char *create_file_path(input_data *in_data, char *file_name)
{
    const int SLASH_AND_END_OF_STRING = 2;

    char *fpath = (char *)malloc((strlen(in_data->path) +
                                  strlen(file_name) +
                                  SLASH_AND_END_OF_STRING) *
                                 sizeof(char));
    strcpy(fpath, in_data->path);
    strcat(fpath, "/");
    strcat(fpath, file_name);

    return fpath;
}

void search_nested_dir(input_data *parent_input_data, char *path)
{
    input_data nested_input_data;
    init_nested_input_data(&nested_input_data, parent_input_data, path);
    readdir_search(&nested_input_data);
}

void init_nested_input_data(input_data *nested_input_data, input_data *parent_data, char *path)
{
    nested_input_data->year = parent_data->year;
    nested_input_data->month = parent_data->month;
    nested_input_data->day = parent_data->day;
    nested_input_data->sign = parent_data->sign;
    nested_input_data->path = path;
}

void process_file(struct stat *buf, input_data *data, char *file_name)
{
    int is_allowed = 0;
    is_allowed = check_if_allowed_for_process(buf->st_mtime, data);

    if (is_allowed)
    {
        output_f_data out_data;
        // filename
        out_data.d_name = file_name;
        process(buf, data, &out_data);
        show_data(&out_data);

        free(out_data.apath);
    }
}