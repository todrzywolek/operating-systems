#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#include "sys_v_sems.h"
#include "queue.h"

void validate_args(int argc);
void close_barber(int t);

//sem1:
//  0 - barber is working
//  <0 - barber is sleeping
//sem2:
//  0 - client can join the queue
// <0 - client will be able to join the queue soon

key_t key;
int semid;
int shmid;
struct Queue *data;
int numOfSems = 2;
//Number of seats
int seats = 5;

int main(int argc, char *argv[])
{
    validate_args(argc);
    signal(SIGINT, close_barber);
    signal(SIGTERM, close_barber);

    seats = atoi(argv[1]);
    key = create_key("newkey.txt", 4, close_barber);
    semid = create_semaphores(key, numOfSems, close_barber);
    shmid = create_shared_mem(key, sizeof(struct Queue), close_barber);
    data = (struct Queue *)get_mem_pointer(shmid, close_barber);
    q_init(data, seats);
    add(semid, QUEUE_ID, 1);
    add(semid, BARBER_ID, 1);
    while (1)
    {
        add(semid, QUEUE_ID, -1);
        int v = q_clear(data);
        add(semid, QUEUE_ID, 1);
        if (v == 1)
        {
            printf("Falling asleep.\n");
            add(semid, BARBER_ID, -1);
            add(semid, BARBER_ID, -1);
            printf("Waking up.\n");
        }
        add(semid, QUEUE_ID, -1);
        printf("Q: in = %d, out = %d, size = %d.\n", data->queue_in, data->queue_out, data->size);
        int pid = q_get(data);
        add(semid, QUEUE_ID, 1);
        printf("Cutting %d.\n", pid);

        //Simulating doing job
        //sleep(3);

        printf("Stopping cutting %d.\n", pid);
        kill(pid, SIGUSR1);
    }

    close_barber(0);
}

void validate_args(int argc)
{
    if (argc < 2)
    {
        printf("Proper usage: ./b N\n");
        printf("N - number of seats in barber shop.\n");
        exit(-1);
    }
}

void close_barber(int t)
{
    release_semaphores(semid);
    q_delete(data);

    shmctl(shmid, IPC_RMID, NULL);

    exit(0);
}