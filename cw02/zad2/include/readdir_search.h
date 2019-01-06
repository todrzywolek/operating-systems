#pragma once
#include <dirent.h>
#include <sys/stat.h>

void readdir_search(char *path);
DIR *open_directory(char *path);
void set_file_access(char *access, struct stat *buf);
