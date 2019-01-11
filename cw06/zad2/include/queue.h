#pragma once
#include <stdlib.h>

struct Queue
{
    int elems[500];
    int size;
    int queue_in;
    int queue_out;
};

void q_init(struct Queue *q, int size);
int q_put(struct Queue *q, int e);
int q_get(struct Queue *q);
void q_delete(struct Queue *q);
int q_clear(struct Queue *q);
