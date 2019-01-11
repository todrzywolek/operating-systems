#pragma once
#include <pthread.h>

struct buffer_t
{
    char **buf;
    int buffer_size;
    int occupied;
    int nextin;
    int nextout;
    pthread_mutex_t mutex;
    pthread_cond_t more;
    pthread_cond_t less;
};

void init_buffer(struct buffer_t *b, int buffer_size);