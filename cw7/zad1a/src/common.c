#include "common.h"

void init_buffer(struct buffer_t *b)
{
    b->nextin = 0;
    b->nextout = 0;
    for (int i = 0; i < BSIZE; i++)
    {
        b->buf[i] = NULL;
    }
    b->occupied = 0;
    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->more, NULL);
    pthread_cond_init(&b->less, NULL);
}