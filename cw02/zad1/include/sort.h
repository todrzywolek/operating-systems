#pragma once
#include <stdio.h>

void sort(char const *argv[]);
void sys_sort(int file, int records, int size);
void lib_sort(FILE *file, int records, int size);