#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include "queue_utils.h"

void kill_server();
void send_time(FILE *fp, int *from, msg *message);

int sq = 0;

int main(int c, char *v[])
{
    signal(SIGINT, kill_server);
    //Store client queues here
    sq = create_queue("server", 10);
    printf("Created queue, sq = %d\n", sq);
    printf("Awaiting message...\n");
    msg m;
    bool finish = false;
    while (1)
    {
        int from;
        char com_mes[50];
        FILE *fp = NULL;
        if (finish && is_empty(sq))
        {
            printf("Queue is empty - shutting down.\n");
            kill_server();
        }
        read_message(&sq, &m);

        sscanf(m.mtext, "%d %s", &from, com_mes);
        printf("%s from %d\n", com_mes, from);
        switch (m.mtype)
        {
        case 1: //TIME
            send_time(fp, &from, &m);
            break;
        case 2: //END
            finish = true;
            break;
        }
    }
    remove_queue(&sq);
}

void kill_server()
{
    printf("Received signal - server is shutting down.\n");
    remove_queue(&sq);
    exit(0);
}

void send_time(FILE *fp, int *from, msg *message)
{
    fp = popen("date", "r");
    fread(message->mtext, sizeof(char), MSGTXTLEN, fp);
    send_message(from, message);
}