#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
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
    if (params->logging_level == 2)
        printf("Producer no %ld - Starts producing\n", pthread_self());

    if (params->nk == 0)
        file_dependend_producer_mode(params);
    else if (params->nk > 0)
        time_depended_producer_mode(params);
    else
        printf("nk param should be greater or equal to 0. Stopping producer.\n");
}

void file_dependend_producer_mode(struct producer_params_t *params)
{
    char line[LINE_LENGHT];
    int line_num = 0;
    while (1)
    {
        if (read_line(params->file_params, line, &line_num, params->logging_level))
        {
            if (params->logging_level == 2)
                printf("Producer thread no %ld - stopping work.\n", pthread_self());
            break;
        }
        // save line in buffer
        save_in_buffer(params->buffer, line, line_num, params->logging_level);
    }
}

void time_depended_producer_mode(struct producer_params_t *params)
{
    char line[LINE_LENGHT];
    int line_num = 0;
    while (1)
    {
        if (read_lines_in_loop(params->file_params, line, &line_num, params->logging_level))
        {
            if (params->logging_level == 2)
                printf("Producer thread no %ld - stopping work.\n", pthread_self());
            break;
        }
        // save line in buffer
        save_in_buffer(params->buffer, line, line_num, params->logging_level);
    }
}

int read_line(struct file_params_t *file_parameters, char *line, int *line_num, int logging_level)
{
    // lock file mutex
    pthread_mutex_lock(&file_parameters->mutex);

    char *read_result;
    // read line
    if (logging_level == 2)
        printf("Thread: %ld - Reading line num %d\n", pthread_self(), file_parameters->line_num);
    read_result = fgets(line, LINE_LENGHT, file_parameters->fp);
    line = trimwhitespace(line);
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

void save_in_buffer(struct buffer_t *buffer, char *line, int line_num, int logging_level)
{
    // lock buffer mutex
    pthread_mutex_lock(&buffer->mutex);

    while (buffer->occupied >= buffer->buffer_size)
    {
        if (logging_level == 2)
            printf("Thread: %ld - Buffer full. Waiting...\n", pthread_self());
        pthread_cond_wait(&buffer->less, &buffer->mutex);
    }

    assert(buffer->occupied < buffer->buffer_size);

    // strip newline from the end
    line[strcspn(line, "\n")] = 0;
    int line_length = strlen(line);

    // save in buffer
    perform_save(buffer, line, line_length, line_num, logging_level);

    pthread_cond_signal(&buffer->more);

    // unlock buffer mutex
    pthread_mutex_unlock(&buffer->mutex);
}

void perform_save(struct buffer_t *buffer, char *line, int line_length, int line_num, int logging_level)
{
    if (line_length > 0)
    {
        if (logging_level == 2)
            printf("Thread: %ld - Saving line num %d to index %d\tcontent:%s\n", pthread_self(), line_num, buffer->nextin, line);
        buffer->buf[buffer->nextin] = (char *)malloc(sizeof(char) * (line_length + 1));
        strcpy(buffer->buf[buffer->nextin], line);
        buffer->nextin++;
        buffer->nextin %= buffer->buffer_size;
        buffer->occupied++;
    }
    else
    {
        if (logging_level == 2)
            printf("Thread: %ld - Line num %d empty.Not saving.\n", pthread_self(), line_num);
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
    producer_params->nk = atoi(argv[8]);
}

int read_lines_in_loop(struct file_params_t *file_parameters, char *line, int *line_num, int logging_level)
{
    // lock file mutex
    pthread_mutex_lock(&file_parameters->mutex);
    // read line
    if (logging_level == 2)
        printf("Thread: %ld - Reading line num %d\n", pthread_self(), file_parameters->line_num);

    fgets(line, LINE_LENGHT, file_parameters->fp);
    line = trimwhitespace(line);
    *line_num = file_parameters->line_num;
    file_parameters->line_num++;

    if (feof(file_parameters->fp))
    {
        fseek(file_parameters->fp, 0, SEEK_SET);
        file_parameters->line_num = 1;
    }

    // unlock file mutex
    pthread_mutex_unlock(&file_parameters->mutex);

    return 0;
}

char *trimwhitespace(char *str)
{
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}