#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "queue_utils.h"

void kill_server();
void send_time(FILE *fp, int qid, char *message, char *qname);

mqd_t q;

int main(int argc, char *argv[])
{
    signal(SIGINT, kill_server);
    //Store client queues here
    q = create_queue(SERVER_NAME, kill_server);
    printf("Created queue, sq = %d\n", q);
    printf("Awaiting message...\n");

    int pid, qid = 0;
    char qname[20];
    FILE *fp = NULL;
    bool finish = false;

    while (1)
    {
        if (finish)
        {
            struct mq_attr isEmpty;
            mq_getattr(q, &isEmpty);
            if (isEmpty.mq_curmsgs == 0)
            {
                printf("Queue is empty. Shutting down.\n");
                kill_server();
            }
        }
        char message[SIZE] = {0};
        receive_message(q, message, kill_server);
        printf("%s\n", message + 1);

        switch (message[0])
        {
        case 1: //New connection
            sscanf(message + 1, "%d %d", &pid, &qid);
            printf("New connection created, pid = %d\n", pid);
            break;
        case 2: //TIME
            send_time(fp, qid, message, qname);
            break;
        case 3: //END
            finish = true;
            break;
        }
    }
    kill_server();
    return 0;
}

void kill_server()
{
    printf("Received signal - server is shutting down.\n");
    mq_close(q);
    mq_unlink(SERVER_NAME);
    exit(0);
}

void send_time(FILE *fp, int qid, char *message, char *qname)
{
    printf("In time\n");
    sscanf(message + 1, "%s", qname);
    printf("Received message: %s", qname);
    fp = popen("date", "r");
    fread(message, sizeof(char), SIZE, fp);
    qid = open_queue(qname, kill_server);
    send_message(qid, message, kill_server);
    mq_close(qid);
}