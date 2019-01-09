#include "queue_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

void remove_queue(int *queue)
{
    if (*queue == 0)
        return;
    if (msgctl(*queue, IPC_RMID, NULL) < 0)
    {
        printf("Failed to remove the queue!\n");
        return;
    }
    *queue = 0;
}

bool check_queue(char *name, int num)
{
    int ret;
    if ((ret = msgget(ftok(name, num), IPC_EXCL | IPC_CREAT | 0666)) < 0)
    {
        if (errno == EEXIST)
            return true;
        return false;
    }
    remove_queue(&ret);
    return false;
}

bool is_empty(int queue)
{
    struct msqid_ds buf;
    msgctl(queue, IPC_STAT, &buf);
    return !buf.msg_qnum;
}

int create_queue(char *name, int num)
{
    int ret;
    if ((ret = msgget(ftok(name, num), IPC_CREAT | 0666)) < 0)
    {
        printf("Failed to create message queue!\n");
        return 0;
    }
    return ret;
}

void send_message(int *queue, msg *m)
{
    if (msgsnd(*queue, m, sizeof(m->mtext), 0) < 0)
    {
        printf("Failed to send the message!\n");
        remove_queue(queue);
    }
}

void read_message(int *queue, msg *m)
{
    if (msgrcv(*queue, m, sizeof(m->mtext), 0, 0) < 0)
    {
        printf("Failed to receive the message!\n");
        remove_queue(queue);
    }
}