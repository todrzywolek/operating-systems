#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common.h"
#include "producer.h"

void validate_arguments_number(int number_of_arguments);
FILE *open_input_file(char const *filename);
void print_buffer(char *buffer[], int bsize);

int main(int argc, char const *argv[])
{
    validate_arguments_number(argc);
    FILE *fp = open_input_file(argv[1]);

    struct file_params file_parameters;
    file_parameters.fp = fp;
    file_parameters.line_num = 1;
    //pthread_mutex_init(&file_parameters.mutex, NULL);

    struct buffer_t b;
    b.nextin = 0;
    for (int i = 0; i < BSIZE; i++)
    {
        b.buf[i] = NULL;
    }

    struct producer_params producer_parameters;
    producer_parameters.file_params = &file_parameters;
    producer_parameters.buffer = &b;

    pthread_t thread1_id;
    pthread_t thread2_id;

    pthread_create(&thread1_id, NULL, &producer_start, &producer_parameters);
    printf("\nCreated thread with id=%ld\n", thread1_id);
    pthread_create(&thread2_id, NULL, &producer_start, &producer_parameters);
    printf("\nCreated thread with id=%ld\n", thread2_id);

    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);
    printf("\njoined threads\n");

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