#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include "sys_v_sems.h"
#include "queue.h"

int size = 500;
int cuts = 3;
int pid;
struct Queue *data;

void validate_args(int argc);
void leave_barber(int x);
void close_client(int t);

int main(int argc, char *argv[])
{
    validate_args(argc);
    signal(SIGUSR1, leave_barber);

    key_t key = create_key("key.txt", 4, close_client);
    int semid = get_semaphores(key, close_client);
    int shmid = get_shared_mem(key, close_client);
    data = (struct Queue *)get_mem_pointer(shmid, close_client);
    int clients = atoi(argv[1]);
    cuts = atoi(argv[2]);
    for (int i = 0; i < clients; ++i)
    {
        if (fork() == 0)
        {
            pid = getpid();
            printf("%d: Entering the barber'cuts.\n", pid);
            while (1)
            {

                add(semid, QUEUE_ID, -1);
                int r = q_put(data, getpid());
                add(semid, QUEUE_ID, 1);
                printf("%d: Entering queue.\n", pid);
                if (r == -1)
                {
                    printf("%d: Queue full! Leaving the barber'cuts.\n", pid);
                    exit(0);
                }
                else if (is_zero(semid, BARBER_ID))
                {
                    printf("%d: Waking up the barber.\n", pid);
                    add(semid, BARBER_ID, 2);
                }
                pause();
            }
            break;
        }
    }
}

void validate_args(int argc)
{
    if (argc < 3)
    {
        printf("Proper usage: clients C\n");
        printf("clients - number of clients.\n");
        printf("C - number of cuts per client.\n");
        exit(-1);
    }
}

void leave_barber(int x)
{
    cuts--;
    printf("%d: Finishing. Need %d more cuts.\n", pid, cuts);
    if (!cuts)
    {
        printf("%d: Leaving the barber'cuts.\n", pid);
        exit(0);
    }
}

void close_client(int t)
{
    printf("Closing client\n");
}