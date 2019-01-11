#include <sys/mman.h>
#include <unistd.h>

#include "posix_sems.h"

sem_t *create_semaphore(const char *name, unsigned int initVal, void (*error_handler_fn)(int))
{
    sem_t *s = sem_open(name, O_CREAT | O_RDWR, 0666, initVal);
    if (s == SEM_FAILED)
    {
        fprintf(stderr, "Failed to create a semaphore!\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
    return s;
}

sem_t *get_semaphore(const char *name, void (*error_handler_fn)(int))
{
    sem_t *s = sem_open(name, O_RDWR);
    if (s == SEM_FAILED)
    {
        fprintf(stderr, "Failed to get a semaphore!\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
    return s;
}

void take(sem_t *s, void (*error_handler_fn)(int))
{
    if (sem_wait(s) == -1)
    {
        fprintf(stderr, "Failed to take the semaphore!\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
}

void release(sem_t *s, void (*error_handler_fn)(int))
{
    if (sem_post(s) == -1)
    {
        fprintf(stderr, "Failed to release the semaphore!\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
}

void close_semaphore(sem_t *s)
{
    if (sem_close(s))
        perror(strerror(errno));
}

void remove_semaphore(const char *name)
{
    if (sem_unlink(name) == -1)
    {
        fprintf(stderr, "Failed to remove semaphore!.\n");
        perror(strerror(errno));
    }
}

void *create_shared_mem(const char *name, off_t size, void (*error_handler_fn)(int))
{
    int fd;
    void *ret;
    if ((fd = shm_open(name, O_CREAT | O_RDWR, 0666)) == -1)
    {
        fprintf(stderr, "Failed to create shared memory!\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
    if (ftruncate(fd, size) == -1)
    {
        fprintf(stderr, "Failed to truncate shared memory!\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
    if ((ret = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
        fprintf(stderr, "Failed to map memory to the process!\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
    return ret;
}

void *get_shared_mem(const char *name, off_t size, void (*error_handler_fn)(int))
{
    int fd;
    void *ret;
    if ((fd = shm_open(name, O_RDWR, 0666)) == -1)
    {
        fprintf(stderr, "Failed to get shared memory!\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
    if ((ret = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
        fprintf(stderr, "Failed to map memory to the process!\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
    return ret;
}

void release_shared_mem(void *addr, size_t len, const char *name)
{
    munmap(addr, len);
    shm_unlink(name);
}

void close_shared_mem(void *addr, size_t len)
{
    munmap(addr, len);
}

int get_value(sem_t *sem, void (*error_handler_fn)(int))
{
    int ret;
    if (sem_getvalue(sem, &ret) == -1)
    {
        fprintf(stderr, "Failed to get value of the semaphore!\n");
        perror(strerror(errno));
        (*error_handler_fn)(0);
    }
    return ret;
}