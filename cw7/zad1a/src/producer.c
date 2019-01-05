#include <stdlib.h>
#include <string.h>
#include "producer.h"

void *producer_start(void *parameters)
{
    struct producer_params *p;
    p = parameters_to_producer_params(parameters);

    // run producer
    produce(p);

    return NULL;
}

struct producer_params *parameters_to_producer_params(void *parameters)
{
    return (struct producer_params *)parameters;
}

void produce(struct producer_params *params)
{
    char line[LINE_LENGHT];
    printf("start producing\n");
    while (1)
    {
        if (read_line(params->file_params, line))
        {
            printf("end work\n");
            break;
        }

        // save line in buffer
        save_in_buffer(params->buffer, line);
    }
}

int read_line(struct file_params *file_parameters, char *line)
{
    // lock file mutex
    //pthread_mutex_lock(&file_parameters->mutex);

    char *read_result;
    // read line
    read_result = fgets(line, LINE_LENGHT, file_parameters->fp);

    // unlock file mutex
    //pthread_mutex_unlock(&file_parameters->mutex);

    // if EOF finish processing
    if (read_result == NULL)
    {
        return 1;
    }
    return 0;
}

void save_in_buffer(struct buffer_t *buffer, char *line)
{
    // lock buffer mutex
    //pthread_mutex_lock(&buffer->mutex);

    // strip newline from the end
    line[strcspn(line, "\n")] = 0;
    int line_length = strlen(line);

    // save in buffer
    perform_save(buffer, line, line_length);

    // unlock buffer mutex
    //pthread_mutex_unlock(&buffer->mutex);
}

void perform_save(struct buffer_t *buffer, char *line, int line_length)
{
    if (line_length > 0)
    {
        buffer->buf[buffer->nextin] = (char *)malloc(sizeof(char) * line_length);
        strcpy(buffer->buf[buffer->nextin], line);
        buffer->nextin++;
        buffer->nextin %= BSIZE;
    }
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