#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include "readdir_search.h"

void readdir_search(char *path)
{
    DIR *dir = open_directory(path);
    struct dirent *pDirent;
    for (pDirent = readdir(dir); pDirent != NULL; pDirent = readdir(dir))
    {
        if (!strcmp(pDirent->d_name, ".") || !strcmp(pDirent->d_name, ".."))
            continue;

        const int SLASH_AND_END_OF_STRING = 2;
        char *fpath = (char *)malloc((strlen(path) +
                                      strlen(pDirent->d_name) +
                                      SLASH_AND_END_OF_STRING) *
                                     sizeof(char));
        strcpy(fpath, path);
        strcat(fpath, "/");
        strcat(fpath, pDirent->d_name);

        struct stat buf;
        if (lstat(fpath, &buf) != 0)
        {
            printf("Error reading struct!");
            return;
        }
        if (S_ISDIR(buf.st_mode))
        {
            readdir_search(fpath);
        }
        else if (S_ISREG(buf.st_mode))
        {
            //int fsize = buf.st_size;
            //time_t mdate = buf.st_mtime;
            // access
            char access[10] = "---------";
            set_file_access(access, &buf);

            printf("File access: %s\n", access);
        }
        free(fpath);
    }
    if (errno > 0)
    {
        printf("Failed reading the directory %s! Error no %i.\n", path, errno);
    }
}

DIR *open_directory(char *path)
{
    printf("Path:%s\n", path);
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        printf("No such directory!\n");
        exit(-1);
    }

    return dir;
}

void set_file_access(char *access, struct stat *buf)
{
    printf("Setting file access.\n");

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