#pragma once
#include <pthread.h>

#ifndef BSIZE
#define BSIZE 100
#endif


struct buffer_t {
    char *buf[BSIZE];
    int nextin;
    pthread_mutex_t mutex;
};