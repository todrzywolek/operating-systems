#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include "queue_utils.h"

int cq = 0;

void kill_client();

int main(int c, char *v[])
{
    signal(SIGINT, kill_client);
    if (!check_queue("server", 10))
    {
        printf("Server not found!\n");
        return 1;
    }
    int sq = create_queue("server", 10);
    cq = create_queue("client", getpid());
    printf("Connected, cq = %d\n", cq);
    printf("Sending pid...\n");
    msg m;
    m.mtype = 1;
    //Send PID and queue ID
    sprintf(m.mtext, "%d %d", getpid(), cq);
    send_message(&sq, &m);
    while (1)
    {
        char command[7];
        printf("Type command: ");
        scanf("%s", command);
        sprintf(m.mtext, "%d", cq);
        if (strstr(command, "TIME"))
        {
            m.mtype = 1;
        }
        else if (strstr(command, "END"))
        {
            m.mtype = 2;
            send_message(&sq, &m);
            printf("ok\n");
            break;
        }
        else
            continue;

        if (!check_queue("server", 10))
        {
            printf("Connection with server lost. Shutting down.\n");
            kill_client();
        }
        send_message(&sq, &m);
        read_message(&cq, &m);
        printf("%s\n", m.mtext);
    }
    remove_queue(&cq);
}

void kill_client()
{
    printf("Received signal - client is shutting down.\n");
    remove_queue(&cq);
    exit(0);
}
