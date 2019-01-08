#include "my_copy.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

void run_copy(char const *argv[])
{
    int num_of_records = convert_to_int(argv[4]);
    int record_size = convert_to_int(argv[5]);

    if (!strcmp(argv[6], "sys"))
    {
        int source = open(argv[2], O_RDWR);
        if (source < 0)
        {
            printf("Failed opening the file!");
            exit(-1);
        }
        int dest = open(argv[3], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        if (dest < 0)
        {
            printf("Nie udalo sie otworzyc pliku!");
            exit(-1);
        }
        sys_copy(source, dest, num_of_records, record_size);
        close(source);
        close(dest);
    }
    else if (!strcmp(argv[6], "lib"))
    {
        FILE *source = fopen(argv[2], "r");
        if (!source)
        {
            printf("Failed opening the file!");
            exit(-1);
        }
        FILE *dest = fopen(argv[3], "w");
        lib_copy(source, dest, num_of_records, record_size);
        fclose(source);
        fclose(dest);
    }
    else
    {
        printf("Unknown mode!\n");
        exit(-1);
    }
}

void sys_copy(int source, int dest, int records, int size)
{
    char *data_block = (char *)malloc(size * sizeof(char));
    int bytes;
    for (int i = 0; i < records; ++i)
    {
        bytes = read(source, data_block, size);
        write(dest, data_block, bytes);
    }
    free(data_block);
}

void lib_copy(FILE *source, FILE *dest, int records, int size)
{
    char *data_block = (char *)malloc(size * sizeof(char));
    int bytes;
    for (int i = 0; i < records; ++i)
    {
        bytes = fread(data_block, sizeof(char), size, source);
        fwrite(data_block, sizeof(char), bytes, dest);
    }
    free(data_block);
}