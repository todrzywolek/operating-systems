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

    // init semaphores
    sem_init(&b->occupied, 0, 0);
    sem_init(&b->empty, 0, buffer_size);
    sem_init(&b->pmut, 0, 1);
    sem_init(&b->cmut, 0, 1);
}