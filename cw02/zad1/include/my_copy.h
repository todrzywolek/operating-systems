#pragma once

#include <stdio.h>
#include <stdlib.h>

void run_copy(char const *argv[]);
void sys_copy(int source, int dest, int records, int size);
void lib_copy(FILE *source, FILE *dest, int records, int size);