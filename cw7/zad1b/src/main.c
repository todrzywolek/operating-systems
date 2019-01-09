#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include "input_validation.h"
#include "common.h"
#include "producer.h"
#include "consumer.h"

FILE *open_input_file(char const *filename);
void create_threads(pthread_t *threads, int size, void *funct, void *params, char *type);
void set_quit_flag();
void join_threads(pthread_t *producers, int size);
void handle_signal(int signo);
void cleanup_params(struct buffer_t *b, struct file_params_t *file_parameters, struct producer_params_t *producer_parameters);
void clean_buffer(struct buffer_t *b);

// global producer_params delcaration for signal handling
struct producer_params_t producer_parameters;

int main(int argc, char const *argv[])
{
    validate_arguments_number(argc);
    FILE *fp = open_input_file(argv[4]);

    // structure declarations
    struct buffer_t b;
    struct file_params_t file_parameters;
    struct consumer_mode_t consumer_mode;
    struct consumer_params_t consumer_parameters;

    // producer thread array
    int producers_number = read_producers_number(argv);
    pthread_t producers[producers_number];
    // consumer thread array
    int consumers_number = read_consumers_number(argv);
    pthread_t consumers[consumers_number];

    // structure initialization
    int buffer_size = read_buffer_size(argv);
    init_buffer(&b, buffer_size);
    init_file_parameters(&file_parameters, fp);
    init_consumer_mode(&consumer_mode, argv);
    init_producer_parameters(&producer_parameters, &file_parameters, &b, argv);
    init_consumer_parameters(&consumer_parameters, &b, &consumer_mode);

    create_threads(producers, producers_number, &producer_start, &producer_parameters, "producer");
    printf("Producers created\n");
    create_threads(consumers, consumers_number, &consumer_start, &consumer_parameters, "consumer");
    printf("Consumers created\n");

    int nk = atoi(argv[8]);

    if (nk > 0)
    {
        sleep(nk);
        set_quit_flag();
    }
    else if (nk == 0)
    {
        signal(SIGINT, handle_signal);
    }

    join_threads(producers, producers_number);

    // mark consumers to finish
    consumer_parameters.should_exit = 1;
    for (int i = 0; i < consumers_number; i++)
    {
        pthread_cancel(consumers[i]);
    }

    printf("Doing cleanup\n");
    cleanup_params(&b, &file_parameters, &producer_parameters);
    //clean_buffer(&b);
    free(b.buf);
    free(fp);

    printf("Finishing work\n");
    return 0;
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

void handle_signal(int signo)
{
    if (signo == SIGINT)
    {
        printf("Received SIGINT signal. Setting cancel flag to producers\n");
        set_quit_flag();
    }
}

void set_quit_flag()
{
    pthread_mutex_lock(&producer_parameters.pparams_mutex);
    producer_parameters.stop = 1;
    pthread_mutex_unlock(&producer_parameters.pparams_mutex);
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

void cleanup_params(struct buffer_t *b, struct file_params_t *file_parameters, struct producer_params_t *producer_parameters)
{
    sem_destroy(&b->empty);
    sem_destroy(&b->occupied);
    sem_destroy(&b->pmut);
    sem_destroy(&b->cmut);
    sem_destroy(&file_parameters->file_access_mut);
    sem_destroy(&producer_parameters->pparams_mutex);
}

void clean_buffer(struct buffer_t *b)
{
    int i;
    for (i = 0; i < b->buffer_size; i++)
    {
        if (b->buf[i] != NULL)
        {
            free(b->buf[i]);
            b->buf[i] = NULL;
        }
    }
}