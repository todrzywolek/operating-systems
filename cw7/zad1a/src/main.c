#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common.h"
#include "producer.h"
#include "consumer.h"

#ifndef PRODUCER_NUM
#define PRODUCER_NUM 1
#endif

#ifndef CONSUMER_NUM
#define CONSUMER_NUM 4
#endif

void validate_arguments_number(int number_of_arguments);
FILE *open_input_file(char const *filename);
void create_threads(pthread_t *threads, int size, void *funct, void *params, char *type);
void join_threads(pthread_t *producers, int size);
void print_buffer(char *buffer[], int bsize);

int main(int argc, char const *argv[])
{
    validate_arguments_number(argc);
    FILE *fp = open_input_file(argv[1]);

    // structure declarations
    struct buffer_t b;
    struct file_params_t file_parameters;
    struct producer_params_t producer_parameters;
    struct consumer_params_t consumer_parameters;

    // producer thread array
    pthread_t producers[PRODUCER_NUM];
    // consumer thread array
    pthread_t consumers[CONSUMER_NUM];

    // structure initialization
    init_buffer(&b);
    init_file_parameters(&file_parameters, fp);
    init_producer_parameters(&producer_parameters, &file_parameters, &b);
    init_consumer_parameters(&consumer_parameters, &b);

    create_threads(producers, PRODUCER_NUM, &producer_start, &producer_parameters, "producer");
    printf("Producers created\n");
    create_threads(consumers, CONSUMER_NUM, &consumer_start, &consumer_parameters, "consumer");
    //printf("Consumers created\n");

    join_threads(producers, PRODUCER_NUM);

    // mark consumers to finish
    consumer_parameters.should_exit = 1;
    printf("Shuld exit status: %d", consumer_parameters.should_exit);
    join_threads(consumers, CONSUMER_NUM);

    //print_buffer(b.buf, BSIZE);
    printf("Finishing work\n");

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

void create_threads(pthread_t *threads, int size, void *funct, void *params, char *type)
{
    int i;
    for (i = 0; i < size; i++)
    {
        pthread_create(&(threads[i]), NULL, funct, params);
        printf("\nCreated %s thread with id=%ld\n", type, threads[i]);
    }
}

void join_threads(pthread_t *threads, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("Joined thread num %ld\n", threads[i]);
        pthread_join(threads[i], NULL);
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