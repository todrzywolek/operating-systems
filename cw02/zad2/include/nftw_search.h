#pragma once
#include <ftw.h>

void nftw_search(char *path);
int fn(const char *path, const struct stat *buf, int typeflag, struct FTW *ftwbuf);
char *dir_name_from_path(char *path);
void process_file_nftw(const char *path, const struct stat *buf);
char *filename_from_path(const char *path);
