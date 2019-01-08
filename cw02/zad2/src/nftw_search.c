#define _GNU_SOURCE

#include "nftw_search.h"
#include "utils.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern input_data data;

void nftw_search(char *path)
{
    nftw(path, fn, 1000, FTW_PHYS);
}

int fn(const char *path, const struct stat *buf, int typeflag, struct FTW *ftwbuf)
{
    if (typeflag)
        return 0;

    int is_allowed = 0;
    is_allowed = check_if_allowed_for_process(buf->st_mtime, &data);
    printf("%d\n", is_allowed);

    if (is_allowed)
        process_file_nftw(path, buf);

    return 0;
}

void process_file_nftw(const char *path, const struct stat *buf)
{
    output_f_data out_data;
    // filename
    out_data.d_name = filename_from_path(path);
    process(buf, &data, &out_data);
    show_data(&out_data);

    free(out_data.apath);
    free(out_data.d_name);
}

char *filename_from_path(const char *path)
{
    char *pos, *lastpos;

    pos = strchr(path, '/');
    while (pos != NULL)
    {
        lastpos = pos;
        pos = strchr(pos + 1, '/');
    }

    char *name = malloc(strlen(path) - (lastpos - path) + 1);
    strncpy(name, lastpos + 1, strlen(path) - (lastpos - path) + 1);

    return name;
}