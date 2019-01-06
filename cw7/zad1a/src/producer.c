#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "producer.h"

void *producer_start(void *parameters)
{
    struct producer_params_t *p;
    p = parameters_to_producer_params(parameters);

    // run producer
    produce(p);

    return NULL;
}

struct producer_params_t *parameters_to_producer_params(void *parameters)
{
    return (struct producer_params_t *)parameters;
}

void produce(struct producer_params_t *params)
{
    char line[LINE_LENGHT];
    int line_num = 0;
    printf("start producing\n");
    while (1)
    {
        if (read_line(params->file_params, line, &line_num))
        {
            printf("Producer thread no %ld - stopping work.\n", pthread_self());
            break;
        }

        // save line in buffer
        save_in_buffer(params->buffer, line, line_num);
    }
}

int read_line(struct file_params_t *file_parameters, char *line, int *line_num)
{
    // lock file mutex
    pthread_mutex_lock(&file_parameters->mutex);

    char *read_result;
    // read line
    printf("Thread: %ld - Reading line num %d\n", pthread_self(), file_parameters->line_num);
    read_result = fgets(line, LINE_LENGHT, file_parameters->fp);
    *line_num = file_parameters->line_num;
    file_parameters->line_num++;

    // unlock file mutex
    pthread_mutex_unlock(&file_parameters->mutex);

    // if EOF finish processing
    if (read_result == NULL)
    {
        return 1;
    }
    return 0;
}

void save_in_buffer(struct buffer_t *buffer, char *line, int line_num)
{
    // lock buffer mutex
    pthread_mutex_lock(&buffer->mutex);

    while (buffer->occupied >= buffer->buffer_size)
    {
        printf("Thread: %ld - Buffer full. Waiting...\n", pthread_self());
        pthread_cond_wait(&buffer->less, &buffer->mutex);
    }

    assert(buffer->occupied < buffer->buffer_size);

    // strip newline from the end
    line[strcspn(line, "\n")] = 0;
    int line_length = strlen(line);

    // save in buffer
    perform_save(buffer, line, line_length, line_num);

    pthread_cond_signal(&buffer->more);

    // unlock buffer mutex
    pthread_mutex_unlock(&buffer->mutex);
}

void perform_save(struct buffer_t *buffer, char *line, int line_length, int line_num)
{
    if (line_length > 0)
    {
        printf("Thread: %ld - Saving line num %d to index %d\t%s\n", pthread_self(), line_num, buffer->nextin, line);
        buffer->buf[buffer->nextin] = (char *)malloc(sizeof(char) * (line_length+1));
        strcpy(buffer->buf[buffer->nextin], line);
        buffer->nextin++;
        buffer->nextin %= buffer->buffer_size;
        buffer->occupied++;
    }
    else
    {
        printf("Thread: %ld - Line num %d empty, skipping.\n", pthread_self(), line_num);
    }
}

void init_file_parameters(struct file_params_t *file_params, FILE *fp)
{
    file_params->fp = fp;
    file_params->line_num = 1;
    pthread_mutex_init(&file_params->mutex, NULL);
}

void init_producer_parameters(struct producer_params_t *producer_params,
                              struct file_params_t *file_parameters,
                              struct buffer_t *b,
                              char const *argv[])
{
    producer_params->file_params = file_parameters;
    producer_params->buffer = b;
    producer_params->logging_level = atoi(argv[7]);
}

void read_lines_in_loop(FILE *fp, char *line)
{
    while (1)
    {

        fgets(line, sizeof(line), fp);
        printf("%s", line);
        if (feof(fp))
        {
            fseek(fp, 0, SEEK_SET);
        }
    }
}