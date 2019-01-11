#include <stdlib.h>
#include "common.h"

void init_buffer(struct buffer_t *b, int buffer_size)
{
    b->buf = (char **)malloc(sizeof(char *) * buffer_size);
    b->buffer_size = buffer_size;
    b->nextin = 0;
    b->nextout = 0;
    for (int i = 0; i < b->buffer_size; i++)
    {
        b->buf[i] = NULL;
    }
    b->occupied = 0;
    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->more, NULL);
    pthread_cond_init(&b->less, NULL);
}