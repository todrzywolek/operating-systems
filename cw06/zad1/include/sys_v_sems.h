#pragma once

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

#define BARBER_ID (0)
#define QUEUE_ID (1)

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

extern unsigned short *initArrayBuf;
extern void onExit(int);

key_t create_key(char *name, int num, void (*error_handler_fn)(int));
int create_semaphores(key_t k, int numOfSems, void (*error_handler_fn)(int));
void release_semaphores(int semid);
int get_semaphores(key_t key, void (*error_handler_fn)(int));
int create_shared_mem(key_t k, int size, void (*error_handler_fn)(int));
int get_shared_mem(key_t key, void (*error_handler_fn)(int));
int *get_mem_pointer(int shmid, void (*error_handler_fn)(int));
void add(int semid, int n, int val);
int IsZero(int semid, int n);
void WaitTillZero(int semid, int n);