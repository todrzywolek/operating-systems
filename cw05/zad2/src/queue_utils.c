#include "queue_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

void remove_queue(mqd_t queue, char *name, void (*kill_service_func)())
{
    mq_close(queue);
    mq_unlink(name);
    (*kill_service_func)();
}

mqd_t create_queue(char *name, void (*kill_service_func)())
{
    struct mq_attr atr;
    atr.mq_flags = 0;
    atr.mq_maxmsg = 10;
    atr.mq_msgsize = SIZE;
    atr.mq_curmsgs = 0;
    mqd_t q = mq_open(name, O_EXCL | O_CREAT | O_RDONLY, 0666, &atr);
    if (q == -1)
    {
        printf("Failed to create queue. Errno = %d.\n", errno);
        (*kill_service_func)();
    }
    return q;
}

mqd_t open_queue(char *name, void (*kill_service_func)())
{
    mqd_t q = mq_open(name, O_RDWR);
    if (q == -1)
    {
        printf("Failed to open queue. Errno = %d.\n", errno);
        (*kill_service_func)();
    }
    return q;
}

void receive_message(mqd_t q, char *buf, void (*kill_service_func)())
{
    int s = mq_receive(q, buf, (SIZE + 1), NULL);
    if (s == -1)
    {
        printf("Failed to receive message. Errno = %d.\n", errno);
        (*kill_service_func)();
    }
}

void send_message(mqd_t q, char *buf, void (*kill_service_func)())
{
    if (mq_send(q, buf, SIZE, 1) == -1)
    {
        printf("Failed to send message. Errno = %d.\n", errno);
        (*kill_service_func)();
    }
}