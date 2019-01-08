#include "sort.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

void sort(char const *argv[])
{
    int num_of_records = convert_to_int(argv[3]);
    int record_size = convert_to_int(argv[4]);

    if (!strcmp(argv[5], "sys"))
    {
        int f_desc = open(argv[2], O_RDWR);
        if (f_desc < 0)
        {
            printf("Failed opening the file!");
            exit(-1);
        }
        sys_sort(f_desc, num_of_records, record_size);
        close(f_desc);
    }
    else if (!strcmp(argv[5], "lib"))
    {
        FILE *fp = fopen(argv[2], "r+");
        if (!fp)
        {
            printf("Failed opening the file!");
            exit(-1);
        }
        lib_sort(fp, num_of_records, record_size);
        fclose(fp);
    }
}

void sys_sort(int file, int records, int size)
{
    char *cbuf = (char *)malloc(size * sizeof(char));
    char *current = (char *)malloc(size * sizeof(char));

    for (int i = 0; i < records; i++)
    {
        lseek(file, size * i, SEEK_SET);
        read(file, cbuf, size);
        int smallest = i;
        for (int j = i + 1; j < records; j++)
        {
            read(file, current, 1);
            lseek(file, size - 1, SEEK_CUR);
            if ((unsigned char)cbuf[0] > (unsigned char)current[0])
            {
                smallest = j;
                cbuf[0] = current[0];
            }
        }
        lseek(file, size * i, SEEK_SET);
        read(file, cbuf, size);
        lseek(file, size * smallest, SEEK_SET);
        read(file, current, size);

        lseek(file, size * i, SEEK_SET);
        write(file, current, size);
        lseek(file, size * smallest, SEEK_SET);
        write(file, cbuf, size);
    }
    free(cbuf);
    free(current);
}

void lib_sort(FILE *file, int records, int size)
{
    char *cbuf = (char *)malloc(size * sizeof(char));
    char *current = (char *)malloc(size * sizeof(char));

    for (int i = 0; i < records; i++)
    {
        fseek(file, size * i, 0);
        fread(cbuf, sizeof(char), size, file);
        int smallest = i;
        for (int j = i + 1; j < records; j++)
        {
            fread(current, sizeof(char), 1, file);
            fseek(file, size - 1, 1);
            if ((unsigned char)cbuf[0] > (unsigned char)current[0])
            {
                smallest = j;
                cbuf[0] = current[0];
            }
        }
        fseek(file, size * i, 0);
        fread(cbuf, sizeof(char), size, file);
        fseek(file, size * smallest, 0);
        fread(current, sizeof(char), size, file);

        fseek(file, size * i, 0);
        fwrite(current, sizeof(char), size, file);
        fseek(file, size * smallest, 0);
        fwrite(cbuf, sizeof(char), size, file);
    }
    free(cbuf);
    free(current);
}