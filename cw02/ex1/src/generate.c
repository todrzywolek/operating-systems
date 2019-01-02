#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "generate.h"

void generate(char const *argv[])
{
    int num_of_records, record_size;
    char **records;

    num_of_records = convert_to_int(argv[3]);
    record_size = convert_to_int(argv[4]);

    records = allocate_records(num_of_records, record_size);
    read_records(records, num_of_records, record_size);

    print_first_byte(records, num_of_records);
}

char **allocate_records(int num_of_records, int record_size)
{
    printf("allocating");
    char **records;

    records = (char **)malloc(num_of_records * sizeof(char *));

    for (int i = 0; i < num_of_records; i++)
    {
        records[i] = (char *)malloc(record_size * sizeof(char));
    }

    return records;
}

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

void print_first_byte(char **records, int num_of_records)
{
    printf("printing");
    // for (int i = 0; i < num_of_records; i++)
    // {
    //     printf("%d", records[i][0]);
    // }
}