#pragma once

#include <errno.h>
#include <string.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

sem_t *create_semaphore(const char *name, unsigned int initVal, void (*error_handler_fn)(int));
sem_t* GetSemaphore(const char* name);
void take(sem_t *s, void (*error_handler_fn)(int));
void release(sem_t *s, void (*error_handler_fn)(int));
void close_semaphore(sem_t *s);
void remove_semaphore(const char *name);
void *create_shared_mem(const char *name, off_t size, void (*error_handler_fn)(int));
void* GetSharedMem(const char* name, off_t len);
void release_shared_mem(void *addr, size_t len, const char *name);
void CloseSharedMem(void* addr, size_t len);
int GetValue(sem_t* sem);


/*key_t CreateKey(char* name, int num);
int CreateSemaphores(key_t k, int numOfSems);
void ReleaseSemaphores(int semid);
int GetSemaphores(key_t key);
int CreateSharedMem(key_t k, int size);
int GetSharedMem(key_t key);
int* GetMemPointer(int shmid);
void Add(int semid, int n, int val);
int IsZero(int semid, int n);
void WaitTillZero(int semid, int n);*/