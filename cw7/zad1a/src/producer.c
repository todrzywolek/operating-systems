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
    int line_num = 0;
    printf("start producing\n");
    while (1)
    {
        if (read_line(params->file_params, line, &line_num))
        {
            printf("end work\n");
            break;
        }

        // save line in buffer
        save_in_buffer(params->buffer, line, line_num);
    }
}

int read_line(struct file_params *file_parameters, char *line, int *line_num)
{
    // lock file mutex
    //pthread_mutex_lock(&file_parameters->mutex);

    char *read_result;
    // read line
    printf("Thread: %ld - Reading line num %d\n", pthread_self(), file_parameters->line_num);
    read_result = fgets(line, LINE_LENGHT, file_parameters->fp);
    *line_num = file_parameters->line_num;
    file_parameters->line_num++;

    // unlock file mutex
    //pthread_mutex_unlock(&file_parameters->mutex);

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
    //pthread_mutex_lock(&buffer->mutex);

    // strip newline from the end
    line[strcspn(line, "\n")] = 0;
    int line_length = strlen(line);

    // save in buffer
    perform_save(buffer, line, line_length, line_num);

    // unlock buffer mutex
    //pthread_mutex_unlock(&buffer->mutex);
}

void perform_save(struct buffer_t *buffer, char *line, int line_length, int line_num)
{
    if (line_length > 0)
    {
        printf("Thread: %ld - Saving line num %d\n", pthread_self(), line_num);
        buffer->buf[buffer->nextin] = (char *)malloc(sizeof(char) * line_length);
        strcpy(buffer->buf[buffer->nextin], line);
        buffer->nextin++;
        buffer->nextin %= BSIZE;
    }
    else
    {
        printf("Thread: %ld - Line num %d empty, not saving.\n", pthread_self(), line_num);
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