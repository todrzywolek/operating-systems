#pragma once
#include <stdbool.h>

#define MSGTXTLEN (128)

typedef struct msg_buf
{
    long mtype;
    char mtext[MSGTXTLEN];
} msg;

void remove_queue(int *queue);

bool check_queue(char *name, int num);

bool is_empty(int queue);

int create_queue(char *name, int num);

void send_message(int *queue, msg *m);

void read_message(int *queue, msg *m);