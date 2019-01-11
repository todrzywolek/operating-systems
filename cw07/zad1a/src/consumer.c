#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "common.h"
#include "consumer.h"

void *consumer_start(void *parameters)
{
    struct consumer_params_t *cp;
    cp = parameters_to_consumer_params(parameters);

    // run consumer
    consume(cp);

    return NULL;
}

struct consumer_params_t *parameters_to_consumer_params(void *parameters)
{
    return (struct consumer_params_t *)parameters;
}

void consume(struct consumer_params_t *cp)
{
    if (cp->mode->logging_level == 2)
        printf("Consumer no %ld - Starts consuming\n", pthread_self());
    while (1)
    {
        // check if should exit
        if (cp->should_exit)
        {
            if (cp->mode->logging_level == 2)
                printf("Consumer thread no %ld - stopping work.\n", pthread_self());
            break;
        }

        // else read buffer
        read_buffer(cp->buffer, cp->mode->length, cp->mode->comp_mode, cp->mode->logging_level);
    }
}

void read_buffer(struct buffer_t *b, int comparing_length, int comp_mode, int logging_level)
{
    char *line;
    if (logging_level == 2)
        printf("Thread:%ld - Reading buffer\n", pthread_self());
    // lock buffer mutex
    pthread_mutex_lock(&b->mutex);

    // read buffer
    while (b->occupied <= 0)
    {
        if (logging_level == 2)
            printf("Thread: %ld - Buffer empty. Waiting...\n", pthread_self());
        pthread_cond_wait(&b->more, &b->mutex);
    }

    assert(b->occupied > 0);

    line = b->buf[b->nextout];
    if (logging_level == 2)
        printf("Reading line from index=%d\n", b->nextout);

    // actual work
    compare(line, comparing_length, b->nextout, comp_mode);

    free(line);
    line = NULL;
    b->nextout++;
    b->nextout %= b->buffer_size;
    b->occupied--;

    pthread_cond_signal(&b->less);

    // unlock buffer mutex
    pthread_mutex_unlock(&b->mutex);
}

void compare(char *text, int comparing_length, int line_num, int comp_mode)
{
    if (comp_mode == 1)
    {
        if (strlen(text) > comparing_length)
        {
            printf("index=%d\t%s\n", line_num, text);
        }
    }
    else if (comp_mode == 2)
    {
        if (strlen(text) == comparing_length)
        {
            printf("index=%d\t%s\n", line_num, text);
        }
    }
    else if (comp_mode == 3)
    {
        if (strlen(text) < comparing_length)
        {
            printf("index=%d\t%s\n", line_num, text);
        }
    }
    else
    {
        printf("Invalid compare mode\n");
    }
}

void init_consumer_mode(struct consumer_mode_t *consumer_mode, char const *argv[])
{
    consumer_mode->length = atoi(argv[5]);
    consumer_mode->comp_mode = atoi(argv[6]);
    consumer_mode->logging_level = atoi(argv[7]);
}

void init_consumer_parameters(struct consumer_params_t *consumer_parameters, struct buffer_t *b, struct consumer_mode_t *mode)
{
    consumer_parameters->buffer = b;
    consumer_parameters->should_exit = 0;
    consumer_parameters->mode = mode;
}