#include "sys_v_sems.h"

unsigned short *initArrayBuf = NULL;

key_t create_key(char *name, int num, void (*error_handler_fn)(int))
{
    key_t k = ftok("key.txt", 4);
    if (k == -1)
    {
        fprintf(stderr, "Failed to create a new key!\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
    return k;
}

int create_semaphores(key_t k, int numOfSems, void (*error_handler_fn)(int))
{
    int semid = semget(k, numOfSems, 0666 | IPC_CREAT);
    if (semid == -1)
    {
        fprintf(stderr, "Failed to create semaphores!\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
    union semun init;
    init.array = (unsigned short *)malloc(numOfSems * sizeof(unsigned short));
    initArrayBuf = init.array;
    for (int i = 0; i < numOfSems; ++i)
        init.array[i] = 0;
    semctl(semid, 0, SETALL, init);

    return semid;
}

void release_semaphores(int semid)
{
    semctl(semid, 0, IPC_RMID, 0);
    if (initArrayBuf)
    {
        free(initArrayBuf);
        initArrayBuf = 0;
    }
}

int get_semaphores(key_t key, void (*error_handler_fn)(int))
{
    int semid = semget(key, 0, 0);
    if (semid == -1)
    {
        fprintf(stderr, "Failed to access semaphores\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
    return semid;
}

int create_shared_mem(key_t k, int size, void (*error_handler_fn)(int))
{
    int shmid = shmget(k, size, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        fprintf(stderr, "Failed to create shared memory!\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
    return shmid;
}

int get_shared_mem(key_t key, void (*error_handler_fn)(int))
{
    int shmid = shmget(key, 0, 0);
    if (shmid == -1)
    {
        fprintf(stderr, "Failed to access shared memory\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
    return shmid;
}

int *get_mem_pointer(int shmid, void (*error_handler_fn)(int))
{
    int *data = (int *)shmat(shmid, NULL, 0);
    if (data == (int *)(-1))
    {
        fprintf(stderr, "Failed to access shared memory!\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
    return data;
}

void add(int semid, int n, int val)
{
    struct sembuf ops[1];
    ops[0].sem_num = n;
    ops[0].sem_op = val;
    ops[0].sem_flg = 0;
    semop(semid, ops, 1);
}

int IsZero(int semid, int n)
{
    struct sembuf ops[1];
    ops[0].sem_num = n;
    ops[0].sem_op = 0;
    ops[0].sem_flg = IPC_NOWAIT;
    if (semop(semid, ops, 1) < 0)
    {
        if (errno == EAGAIN)
            return 0;
    }
    return 1;
}

void WaitTillZero(int semid, int n)
{
    struct sembuf ops[1];
    ops[0].sem_num = n;
    ops[0].sem_op = 0;
    ops[0].sem_flg = 0;
    semop(semid, ops, 1);
}