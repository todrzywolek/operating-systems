#include "common.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>

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

void process(const struct stat *buf, input_data *in_data, output_f_data *out_data)
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

void set_file_access(char *access, const struct stat *buf)
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