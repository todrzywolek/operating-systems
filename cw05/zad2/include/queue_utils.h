#pragma once
#include <mqueue.h>
#include <stdbool.h>

#define SIZE (100)

void remove_queue(mqd_t queue, char *name, void (*kill_service_func)());

mqd_t create_queue(char *name, void (*kill_service_func)());

mqd_t open_queue(char *name, void (*kill_service_func)());

void receive_message(mqd_t q, char *buf, void (*kill_service_func)());

void send_message(mqd_t q, char *buf, void (*kill_service_func)());