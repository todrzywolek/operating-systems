#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include "time_counter.h"

void validate_arguments_number(int number_of_arguments);

long convert_to_long(char const *source);

long *allocate_and_populate_array(long size);

long *copy_and_resize_array(long *source, long source_size, long buffer);

void fill_array_with_random_values(long *array, long start_index, long last_index);

int main(int argc, char const *argv[])
{
    long iterations, size, buffer;
    long *numbers = NULL, *new_numbers;
    struct tms tmsstart, tmsend;
    clock_t start, end;

    validate_arguments_number(argc);
    iterations = convert_to_long(argv[1]);
    size = convert_to_long(argv[2]);
    buffer = convert_to_long(argv[3]);

    start = save_timestamp(&tmsstart);

    numbers = allocate_and_populate_array(size);

    for (int i = 0; i < iterations; i++)
    {
        new_numbers = copy_and_resize_array(numbers, size, buffer);

        // free resources from old array
        free(numbers);
        numbers = new_numbers;
        new_numbers == NULL;
    }

    end = save_timestamp(&tmsend);
    display_times(end - start, &tmsstart, &tmsend);
    
    free(numbers);

    return 0;
}

void validate_arguments_number(int number_of_arguments)
{
    if (number_of_arguments != 4)
    {
        printf("Invalid number of arguments. Three (3) numbers are required.\nNumber of iterations, array size and buffer\n");
        exit(-1);
    }
}

long convert_to_long(char const *source)
{
    errno = 0;
    char *p;
    long conv = strtol(source, &p, 10);

    if (errno != 0 || *p != '\0' || conv > LONG_MAX)
    {
        printf("Argument is not a number\n");
        exit(-1);
    }
    else
        return conv;
}

long *allocate_and_populate_array(long size)
{
    long *array = (long *)malloc(sizeof(long) * size);
    fill_array_with_random_values(array, 1, size);

    return array;
}

long *copy_and_resize_array(long *source, long source_size, long buffer)
{
    long new_array_size = source_size + buffer;
    long *new_array = allocate_and_populate_array(new_array_size);
    long i;

    // copy
    for (i = 0; i < source_size; i++)
    {
        new_array[i] = source[i];
    }

    // populate new fields
    fill_array_with_random_values(new_array, i, new_array_size);
    return new_array;
}

void fill_array_with_random_values(long *array, long start_index, long last_index)
{
    srand(time(0));
    for (long i = start_index - 1; i < last_index; i++)
    {
        array[i] = rand() % 50;
    }
}