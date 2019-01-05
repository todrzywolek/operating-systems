#pragma once
#include <pthread.h>

#ifndef BSIZE
#define BSIZE 100
#endif

struct buffer_t
{
    char *buf[BSIZE];
    int occupied;
    int nextin;
    pthread_mutex_t mutex;
    pthread_cond_t more;
    pthread_cond_t less;
};

void init_buffer(struct buffer_t *b);