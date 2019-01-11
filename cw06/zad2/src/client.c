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
size_t N;

int over;
int used;
int pid;
int cuts;

void validate_args(int argc);
void enter_barber();
void leave_barber(int x);
void close_client(int t);

int main(int argc, char *argv[])
{
    validate_args(argc);
    signal(SIGUSR1, leave_barber);

    SemQ = get_semaphore(QUEUE, close_client);
    SemB = get_semaphore(BARBER, close_client);
    SemT = /*CreateSemaphore(BARBER_TEST, 0);*/ get_semaphore(BARBER_TEST, close_client);

    Data = (struct Queue *)get_shared_mem(QUEUE, sizeof(struct Queue), close_client);
    int clients = atoi(argv[1]);
    cuts = atoi(argv[2]);

    for (int i = 0; i < clients; ++i)
    {
        if (fork() == 0)
        {
            pid = getpid();
            printf("%d: Entering the barber's.\n", pid);
            enter_barber();
            exit(0);
        }
    }

    close_client(0);
}

void validate_args(int argc)
{
    if (argc < 3)
    {
        printf("Proper usage: ./c clients C\n");
        printf("clients - number of clients for barber.\n");
        printf("C - number of cuts per client.\n");
        exit(-1);
    }
}

void enter_barber()
{
    used = 0;
    take(SemQ, close_client);
    int r = q_put(Data, pid);
    release(SemQ, close_client);

    printf("%d: Entering queue.\n", pid);
    if (r == -1)
    {
        printf("%d: Queue full! Leaving the barber's.\n", pid);
        close_client(0);
    }
    else
    {
        take(SemT, close_client);
        printf("%d: Wake up the barber? SemB = %d\n", getpid(), get_value(SemB, close_client));
        if (get_value(SemB, close_client) == 0)
        {
            release(SemB, close_client);
            while (get_value(SemB, close_client) != 0)
                ;
            release(SemB, close_client);
            printf("%d: Waking up the barber.\n", pid);
        }
        release(SemT, close_client);
    }
    while (used == 0)
        ;
    if (!over)
        enter_barber();
    close_client(0);
}

void leave_barber(int x)
{
    cuts--;
    printf("%d: Finishing. Need %d more cuts.\n", pid, cuts);
    used = 1;
    if (!cuts)
    {
        printf("%d: Leaving the barber's.\n", pid);
        over = 1;
    }
}

void close_client(int t)
{
    close_semaphore(SemQ);
    close_semaphore(SemB);
    close_semaphore(SemT);
    close_shared_mem(Data, sizeof(struct Queue));
    exit(0);
}