#include "queue.h"

void q_init(struct Queue *q, int size)
{
    q->size = size;
    q->queue_in = q->queue_out = 0;
}

int q_put(struct Queue *q, int e)
{
    if (q->queue_in == ((q->queue_out - 1 + q->size) % q->size))
    {
        return -1; //Queue full
    }

    q->elems[q->queue_in] = e;
    q->queue_in = (q->queue_in + 1) % q->size;
    return 0;
}

int q_get(struct Queue *q)
{
    int e = q->elems[q->queue_out];
    q->queue_out = (q->queue_out + 1) % q->size;
    return e;
}

void q_delete(struct Queue *q)
{
}

int q_clear(struct Queue *q)
{
    if (q->queue_in == q->queue_out)
        return 1;
    return 0;
}