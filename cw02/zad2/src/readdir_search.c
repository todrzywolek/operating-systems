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
            search_nested_dir(data, fpath);
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
        out_data.d_name = file_name;
        process(buf, data, &out_data);
        show_data(&out_data);

        free(out_data.apath);
    }
}

void process(struct stat *buf, input_data *in_data, output_f_data *out_data)
{
    //file size
    out_data->fsize = buf->st_size;

    // modification date
    out_data->mdate = buf->st_mtime;

    // file access
    char access[10] = "---------";
    set_file_access(access, buf);
    out_data->access = access;

    // absolute path
    out_data->apath = (char *)malloc((PATH_MAX + 1) * sizeof(char));
    realpath(in_data->path, out_data->apath);
}

void set_file_access(char *access, struct stat *buf)
{
    if (strlen(access) < 9)
    {
        printf("Access buffer too small. Space for 9 chars is required\n");
        exit(-1);
    }

    if (buf->st_mode & S_IRUSR)
        access[0] = 'r'; /*owner*/
    if (buf->st_mode & S_IWUSR)
        access[1] = 'w'; /*owner*/
    if (buf->st_mode & S_IXUSR)
        access[2] = 'x'; /*owner*/
    if (buf->st_mode & S_IRGRP)
        access[3] = 'r'; /*group*/
    if (buf->st_mode & S_IWGRP)
        access[4] = 'w'; /*group*/
    if (buf->st_mode & S_IXGRP)
        access[5] = 'x'; /*group*/
    if (buf->st_mode & S_IROTH)
        access[6] = 'r'; /*other*/
    if (buf->st_mode & S_IWOTH)
        access[7] = 'w'; /*other*/
    if (buf->st_mode & S_IXOTH)
        access[8] = 'x'; /*other*/
}

int check_if_allowed_for_process(time_t mdate, input_data *data)
{
    struct tm t = *localtime(&mdate);
    if (data->sign == '=')
    {
        if (data->year == t.tm_year + 1900 && data->month == t.tm_mon + 1 && data->day == t.tm_mday)
            return 1;
    }
    else if (data->sign == '>')
    {
        if (data->year < t.tm_year + 1900)
            return 1;
        else if (data->year == t.tm_year)
        {
            if (data->month < t.tm_mon + 1)
                return 1;
            else if (data->month == t.tm_mon + 1)
            {
                if (data->day < t.tm_mday)
                    return 1;
            }
        }
    }
    else
    {
        if (data->year > t.tm_year + 1900)
            return 1;
        else if (data->year == t.tm_year + 1900)
        {
            if (data->month > t.tm_mon + 1)
                return 1;
            else if (data->month == t.tm_mon + 1)
            {
                if (data->day > t.tm_mday)
                    return 1;
            }
        }
    }
    return 0;
}

void show_data(output_f_data *out_data)
{
    struct tm t = *localtime(&out_data->mdate);

    printf("%s", out_data->access);
    printf("%*s%s", 3, "", out_data->d_name);
    printf("%*s%i", (int)(30 - strlen(out_data->d_name)), "", out_data->fsize);
    printf("%*s%d-", 12 - digits(out_data->fsize), "", t.tm_year + 1900);
    if (digits(t.tm_mon + 1) < 2)
        printf("0");
    printf("%d-", t.tm_mon + 1);
    if (digits(t.tm_mday) < 2)
        printf("0");
    printf("%d ", t.tm_mday);
    if (digits(t.tm_hour) < 2)
        printf("0");
    printf("%d:", t.tm_hour);
    if (digits(t.tm_min) < 2)
        printf("0");
    printf("%d:", t.tm_min);
    if (digits(t.tm_sec) < 2)
        printf("0");
    printf("%d  ", t.tm_sec);
    printf("%s/%s\n", out_data->apath, out_data->d_name);
}