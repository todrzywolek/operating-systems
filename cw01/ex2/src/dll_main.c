#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <dlfcn.h>
#include "time_counter.h"

void validate_arguments_number(int number_of_arguments);
int convert_to_int(char const *source);

int main(int argc, char const *argv[])
{
    int m1_rows_num, m1_cols_num, m2_rows_num, m2_cols_num;
    int **m1_ptr, **m2_ptr, **m3_ptr;
    struct tms tmsstart, tmsend;
    clock_t start, end;

    validate_arguments_number(argc);

    m1_rows_num = convert_to_int(argv[1]);
    m1_cols_num = convert_to_int(argv[2]);
    m2_rows_num = convert_to_int(argv[3]);
    m2_cols_num = convert_to_int(argv[4]);

    if (m1_rows_num == m2_rows_num && m1_cols_num == m2_cols_num)
    {
        start = save_timestamp(&tmsstart);

        // load library handle
        void *handle = dlopen("lib/libmatrix.so", RTLD_LAZY);
        if (!handle)
        {
            printf("Error opening handle.\n");
            exit(-1);
        }

        // ******************************************************************

        int **(*create_matrix_ptr)(int, int);
        *(void **)(&create_matrix_ptr) = dlsym(handle, "create_matrix");
        if (dlerror() != NULL)
        {
            printf("Error opening \"create_matrix\".\n");
            exit(-1);
        }

        m1_ptr = (*create_matrix_ptr)(m1_rows_num, m1_cols_num);
        m2_ptr = (*create_matrix_ptr)(m2_rows_num, m2_cols_num);

        // ******************************************************************

        void (*set_matrix_values_ptr)(int **, int, int, int **, int, int);
        *(void **)(&set_matrix_values_ptr) = dlsym(handle, "set_matrix_values");
        if (dlerror() != NULL)
        {
            printf("Error opening \"set_matrix_values_ptr\".\n");
            exit(-1);
        }

        (*set_matrix_values_ptr)(m1_ptr, m1_rows_num, m1_cols_num, m2_ptr, m2_rows_num, m2_cols_num);

        // ******************************************************************

        int **(*add_matrices_ptr)(int **, int, int, int **, int, int);
        *(void **)(&add_matrices_ptr) = dlsym(handle, "add_matrices");
        if (dlerror() != NULL)
        {
            printf("Error opening \"add_matrices\".\n");
            exit(-1);
        }

        m3_ptr = (*add_matrices_ptr)(m1_ptr, m1_rows_num, m1_cols_num, m2_ptr, m2_rows_num, m2_cols_num);

        // ******************************************************************

        void (*free_memory_ptr)(int **, int, int **, int, int **);
        *(void **)(&free_memory_ptr) = dlsym(handle, "free_memory");
        if (dlerror() != NULL)
        {
            printf("Error opening \"free_memory\".\n");
            exit(-1);
        }

        (*free_memory_ptr)(m1_ptr, m1_rows_num, m2_ptr, m2_rows_num, m3_ptr);

        // ******************************************************************

        // close lib handle
        dlclose(handle);

        end = save_timestamp(&tmsend);
        display_times(end - start, &tmsstart, &tmsend);
    }
    else
    {
        printf("Addition cannot be done. Rows and columns for both matrixes should be equal\n");
        exit(-1);
    }

    return 0;
}

void validate_arguments_number(int number_of_arguments)
{
    if (number_of_arguments != 5)
    {
        printf("Invalid number of arguments. Four (4) numbers are required.\n");
        exit(-1);
    }
}

int convert_to_int(char const *source)
{
    errno = 0;
    char *p;
    long conv = strtol(source, &p, 10);

    if (errno != 0 || *p != '\0' || conv > INT_MAX)
    {
        printf("Invalid arguments\n");
        exit(-1);
    }
    else
        return conv;
}