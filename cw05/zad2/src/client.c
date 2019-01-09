#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include "queue_utils.h"

void kill_client();

char name[100];
mqd_t client_q;
mqd_t server_q;

int main(int c, char *v[])
{
    signal(SIGINT, kill_client);

    char name[20];
    sprintf(name, "%s%d", CLIENT_NAME, getpid());
    printf("Client name: %s\n", name);
    client_q = create_queue(name, kill_client);
    server_q = open_queue(SERVER_NAME, kill_client);

    char a[SIZE];
    a[0] = 1;
    sprintf(a + 1, "%d %d", getpid(), client_q);
    printf("%d %d\n", getpid(), client_q);

    send_message(server_q, a, kill_client);

    while (1)
    {
        char command[7];
        printf("Type command: ");
        scanf("%s", command);
        if (strstr(command, "TIME"))
        {
            a[0] = 2;
            sprintf(a + 1, "%s", name);
            printf("Created message: %s\n", a);
        }
        else if (strcmp(command, "END") == 0)
        {
            a[0] = 3;
            printf("ok\n");
            send_message(server_q, a, kill_client);
            kill_client();
        }
        else
            continue;

        send_message(server_q, a, kill_client);
        receive_message(client_q, a, kill_client);
        printf("%s\n", a);
    }
    kill_client();
    return 0;
}

void kill_client()
{
    printf("Received signal - client is shutting down.\n");
    mq_close(client_q);
    mq_close(server_q);
    mq_unlink(name);
    exit(0);
}
