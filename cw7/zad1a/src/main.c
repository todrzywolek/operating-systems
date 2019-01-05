#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common.h"
#include "producer.h"

#ifndef PRODUCER_NUM
#define PRODUCER_NUM 3
#endif

void validate_arguments_number(int number_of_arguments);
FILE *open_input_file(char const *filename);
void create_producer_threads(pthread_t *producers, int size, void *producer_params);
void join_producer_threads(pthread_t *producers, int size);
void print_buffer(char *buffer[], int bsize);

int main(int argc, char const *argv[])
{
    validate_arguments_number(argc);
    FILE *fp = open_input_file(argv[1]);

    // structure declarations
    struct file_params_t file_parameters;
    struct buffer_t b;
    struct producer_params_t producer_parameters;

    // producer thread array
    pthread_t producers[PRODUCER_NUM];

    // structure initialization
    init_file_parameters(&file_parameters, fp);
    init_buffer(&b);
    init_producer_parameters(&producer_parameters, &file_parameters, &b);

    create_producer_threads(producers, PRODUCER_NUM, &producer_parameters);

    printf("created\n");

    join_producer_threads(producers, PRODUCER_NUM);

    print_buffer(b.buf, BSIZE);

    fclose(fp);
    return 0;
}

void validate_arguments_number(int number_of_arguments)
{
    if (number_of_arguments != 2)
    {
        printf("Invalid number of arguments\n");
        printf("Proper usage <FILE_NAME>\n");
        exit(-1);
    }
}

FILE *open_input_file(char const *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Failed to open text file\n");
        exit(1);
    }
    return fp;
}

void create_producer_threads(pthread_t *producers, int size, void *producer_params)
{
    int i;
    for (i = 0; i < size; i++)
    {
        pthread_create(&(producers[i]), NULL, &producer_start, producer_params);
        printf("\nCreated producer thread with id=%ld\n", producers[i]);

        //pthread_create(&thread2_id, NULL, &producer_start, &producer_parameters);
        //printf("\nCreated thread with id=%ld\n", thread2_id);
    }
}

void join_producer_threads(pthread_t *producers, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("Joined thread num %ld\n", producers[i]);
        pthread_join(producers[i], NULL);
    }
}

void print_buffer(char *buffer[], int bsize)
{
    int i;
    for (i = 0; i < bsize; i++)
    {
        if (buffer[i] != NULL)
        {
            printf("%s\n", buffer[i]);
        }
    }
}