#pragma once

#include <stdio.h>
#include <pthread.h>
#include "common.h"

#ifndef LINE_LENGHT
#define LINE_LENGHT 255
#endif
struct file_params
{
    FILE *fp;
    int line_num;
    pthread_mutex_t mutex;
};

struct producer_params
{
    struct file_params *file_params;
    struct buffer_t *buffer;
};

void *producer_start(void *parameters);
struct producer_params *parameters_to_producer_params(void *parameters);
void produce(struct producer_params *params);
int read_line(struct file_params *file_parameters, char *line, int *line_num);
void save_in_buffer(struct buffer_t *buffer, char *line, int line_num);
void perform_save(struct buffer_t *buffer, char *line, int line_length, int line_num);

void read_lines_in_loop(FILE *fp, char *line);