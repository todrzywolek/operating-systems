#pragma once

#include <semaphore.h>

struct buffer_t
{
    char **buf;
    int buffer_size;

    // to check if buffer is full or empty
    sem_t occupied;
    sem_t empty;

    int nextin;
    int nextout;

    // control access to buffer
    sem_t pmut;
    sem_t cmut;
};

void init_buffer(struct buffer_t *b, int buffer_size);