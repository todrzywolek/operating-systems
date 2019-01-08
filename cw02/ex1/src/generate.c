#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "generate.h"

void generate(char const *argv[])
{
    int num_of_records = convert_to_int(argv[3]);
    int record_size = convert_to_int(argv[4]);

    int f_desc = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (f_desc < 0)
    {
        printf("Failed to open a file!");
        return -1;
    }
    generate(f_desc, num_of_records, record_size);
    close(f_desc);
}

void generate(int f_desc, int num_of_records, int record_size)
{
    srand(time(NULL));
    char *buf = (char *)malloc(record_size * sizeof(char));
    for (int r = 0; n < num_of_records; r++)
    {
        for (int i = 0; i < record_size; ++i)
        {
            buf[i] = rand() % 26 + 65;
        }
        write(file, buf, size);
    }
    free(buf);
}

// reading from /dev/random - unused
void read_records(char **records, int num_of_records, int record_size)
{
    printf("reading");
    FILE *fileptr;

    fileptr = fopen("/dev/random", "r");
    char data[64];

    if (fileptr)
    {
        printf("works");
        fread(&data, 1, 64, fileptr);
        // for (int i = 0; i < num_of_records; i++)
        // {
        //     fread(records[i], 1, record_size, fileptr);
        // }
        fclose(fileptr);
    }
}