#pragma once
#include <pthread.h>

#ifndef BSIZE
#define BSIZE 100
#endif

#ifndef LIMIT
#define LIMIT 45
#endif

struct buffer_t
{
    char *buf[BSIZE];
    int occupied;
    int nextin;
    int nextout;
    pthread_mutex_t mutex;
    pthread_cond_t more;
    pthread_cond_t less;
};

void init_buffer(struct buffer_t *b);