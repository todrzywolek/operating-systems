#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "utils.h"

int year;
int month;
int day;
char sign;

void validate_args(int argc, char *argv[]);
void search(char *path, int mode);
void readdir_search(char *path);
DIR *open_directory(char *path);
void set_file_access(char *access, struct stat *buf);
void nftw_search(char *path);

int main(int argc, char *argv[])
{
    validate_args(argc, argv);

    sign = argv[2][0];
    year = atoi(argv[3]);
    month = atoi(argv[4]);
    day = atoi(argv[5]);
    int mode = atoi(argv[6]);

    search(argv[1], mode);
    return 0;
}

void validate_args(int argc, char *argv[])
{
    if (argc != 7)
    {
        printf("Invalid args number. Expected 6, given %d!\n", argc - 1);
        exit(-1);
    }

    if (!isNumber(argv[3]) || !isNumber(argv[4]) || !isNumber(argv[5]) || !isNumber(argv[6]) || (argv[2][0] != '<' && argv[2][0] != '>' && argv[2][0] != '='))
    {
        printf("Invalid arguments!\n");
        exit(-1);
    }
}

void search(char *path, int mode)
{
    printf("Access%*sName%*sSize%*sModification date%*sAbsolute path\n", 6, "", 25, "", 5, "", 5, "");
    if (mode)
        readdir_search(path);
    else
        nftw_search(path);
}

void readdir_search(char *path)
{
    DIR *dir = open_directory(path);
    struct dirent *pDirent;
    for (pDirent = readdir(dir); pDirent != NULL; pDirent = readdir(dir))
    {
        if (!strcmp(pDirent->d_name, ".") || !strcmp(pDirent->d_name, ".."))
            continue;

        char *fpath = (char *)malloc((strlen(path) + strlen(pDirent->d_name) + 2) * sizeof(char));
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

void nftw_search(char *path)
{
    return;
}