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
    char line[255];
    printf("start producing\n");
    while (1)
    {
        if (read_line(params->file_params, line))
        {
            printf("end work\n");
            break;
        }

        // save line in buffer
        save_in_buffer(line);
    }
}

int read_line(struct file_params *file_parameters, char *line)
{
    // lock file mutex
    //pthread_mutex_lock(&file_parameters->mutex);

    char *read_result;
    // read line
    read_result = fgets(line, sizeof(line), file_parameters->fp);

    // unlock file mutex
    //pthread_mutex_unlock(&file_parameters->mutex);

    // if EOF finish processing
    if (read_result == NULL)
    {
        return 1;
    }
    return 0;
}

void save_in_buffer(char *line)
{
    // lock buffer mutex

    // save in buffer
    printf("%s", line);

    // unlock buffer mutex
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