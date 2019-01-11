#pragma once

#include <stdio.h>
#include <semaphore.h>
#include "common.h"

#ifndef LINE_LENGHT
#define LINE_LENGHT 255
#endif
struct file_params_t
{
    FILE *fp;
    int line_num;
    sem_t file_access_mut;
};

struct producer_params_t
{
    struct file_params_t *file_params;
    struct buffer_t *buffer;
    int logging_level;
    int nk;
    int stop;
    sem_t pparams_mutex;
};

void *producer_start(void *parameters);
struct producer_params_t *parameters_to_producer_params(void *parameters);
void produce(struct producer_params_t *params);
void file_dependend_producer_mode(struct producer_params_t *params);
void time_depended_producer_mode(struct producer_params_t *params);
int read_line(struct file_params_t *file_parameters, char *line, int *line_num, int logging_level);
void save_in_buffer(struct buffer_t *buffer, char *line, int line_num, int logging_level);
void perform_save(struct buffer_t *buffer, char *line, int line_length, int line_num, int logging_level);
void init_file_parameters(struct file_params_t *file_params, FILE *fp);
void init_producer_parameters(struct producer_params_t *producer_params,
                              struct file_params_t *file_parameters,
                              struct buffer_t *b,
                              char const *argv[]);

int read_lines_in_loop(struct producer_params_t *params, char *line, int *line_num);
char *trimwhitespace(char *str);