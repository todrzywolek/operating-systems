#include <unistd.h>
#include <signal.h>

#include "posix_sems.h"
#include "queue.h"

#define QUEUE ("sem1")
#define BARBER ("sem2")
#define BARBER_TEST ("sem3")

sem_t *SemQ;
sem_t *SemB;
sem_t *SemT;
struct Queue *Data;
size_t seats;

int main(int argc, char *argv[])
{
    validate_args(argc);
    signal(SIGINT, close_barber);
    signal(SIGTERM, close_barber);

    SemQ = create_semaphore(QUEUE, 1, close_barber);
    SemB = create_semaphore(BARBER, 1, close_barber);
    SemT = create_semaphore(BARBER_TEST, 1, close_barber);

    seats = atoi(argv[1]);
    Data = (struct Queue *)create_shared_mem(QUEUE, sizeof(struct Queue), close_barber);
    q_init(Data, seats);

    while (1)
    {
        take(SemQ, close_barber);
        int v = q_clear(Data);
        release(SemQ, close_barber);
        if (v == 1)
        {
            printf("Falling asleep.\n");
            take(SemB, close_barber);
            take(SemB, close_barber);
            printf("Waking up.\n");
        }
        take(SemQ, close_barber);
        int pid = q_get(Data);
        release(SemQ, close_barber);

        printf("Cutting %d.\n", pid);

        printf("Stopping cutting %d.\n", pid);
        kill(pid, SIGUSR1);
    }

    close_barber(0);
}

void validate_args(int args)
{
    if (args < 2)
    {
        printf("Proper usage: Seats\n");
        printf("Seats - number of seats in barber shop.\n");
        exit(-1);
    }
}

void close_barber(int t)
{
    close_semaphore(SemQ);
    close_semaphore(SemB);
    close_semaphore(SemT);
    remove_semaphore(BARBER);
    remove_semaphore(QUEUE);
    remove_semaphore(BARBER_TEST);
    release_shared_mem(Data, sizeof(struct Queue), QUEUE);
    exit(0);
}