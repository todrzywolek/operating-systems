#pragma once

struct consumer_params_t
{
    int should_exit;
    struct buffer_t *buffer;
};

void *consumer_start(void *parameters);
struct consumer_params_t *parameters_to_consumer_params(void *parameters);
void consume(struct consumer_params_t *cp);
void read_buffer(struct buffer_t *b);
void init_consumer_parameters(struct consumer_params_t *consumer_parameters, struct buffer_t *b);