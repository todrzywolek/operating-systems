#pragma once

struct consumer_mode_t
{
    int length;
    int comp_mode;
    int logging_level;
};

struct consumer_params_t
{
    int should_exit;
    struct buffer_t *buffer;
    struct consumer_mode_t *mode;
};

void *consumer_start(void *parameters);
struct consumer_params_t *parameters_to_consumer_params(void *parameters);
void consume(struct consumer_params_t *cp);
void read_buffer(struct buffer_t *b, int comparing_length, int logging_level);
void init_consumer_parameters(struct consumer_params_t *consumer_parameters, struct buffer_t *b, struct consumer_mode_t *mode);
void init_consumer_mode(struct consumer_mode_t *consumer_mode, char const *argv[]);