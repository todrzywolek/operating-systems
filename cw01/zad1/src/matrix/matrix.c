#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include "time_counter.h"

void validate_input(int argc, char const *argv[]);
void validate_arguments_number(int number_of_arguments);
void validate_matrix_sizes(char const *argv[]);
int convert_to_int(char const *source);
int **create_matrix(int rows_number, int columns_number);
void set_matrix_values(int **m1_ptr, int m1_rows_num, int m1_cols_num,
                       int **m2_ptr, int m2_rows_num, int m2_cols_num);
void fill_matrix(int **matrix_ptr, int rows_num, int cols_num, int *values, int start);
int **add_matrices(int **m1_ptr, int m1_rows_num, int m1_cols_num,
                   int **m2_ptr, int m2_rows_num, int m2_cols_num);
int *read_matrix_values_from_file(const char *file_name, int total_numbers);
void print_matrix(int **matrix_ptr, int rows_num, int cols_num);
void free_memory(int **m1_ptr, int m1_rows_num, int **m2_ptr, int m2_rows_num, int **m3_ptr);
void delete_matrix(int **matrix_ptr, int rows_number);
int *generate_matrix_values_in_memory(const int total_numbers);

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

        m1_ptr = create_matrix(m1_rows_num, m1_cols_num);
        m2_ptr = create_matrix(m2_rows_num, m2_cols_num);

        set_matrix_values(m1_ptr, m1_rows_num, m1_cols_num, m2_ptr, m2_rows_num, m2_cols_num);
        m3_ptr = add_matrices(m1_ptr, m1_rows_num, m1_cols_num, m2_ptr, m2_rows_num, m2_cols_num);

        free_memory(m1_ptr, m1_rows_num, m2_ptr, m2_rows_num, m3_ptr);

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

void validate_input(int argc, char const *argv[])
{
    validate_arguments_number(argc);
    validate_matrix_sizes(argv);
}

void validate_arguments_number(int number_of_arguments)
{
    if (number_of_arguments != 5)
    {
        printf("Invalid number of arguments. Four (4) numbers are required.\n");
        exit(-1);
    }
}

void validate_matrix_sizes(char const *argv[])
{
    if (argv[1] != argv[3] || argv[2] != argv[4])
    {
        printf("Addition cannot be done. Rows and columns for both matrixes should be equal\n");
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

int **create_matrix(int rows_number, int columns_number)
{
    int **matrix_rows;

    /* Allocate memory for matrix rows */
    matrix_rows = (int **)malloc(sizeof(int *) * rows_number);

    /* Allocate memory for matrix columns */
    for (int i = 0; i < rows_number; i++)
        matrix_rows[i] = (int *)malloc(sizeof(int) * columns_number);

    return matrix_rows;
}

void set_matrix_values(int **m1_ptr, int m1_rows_num, int m1_cols_num,
                       int **m2_ptr, int m2_rows_num, int m2_cols_num)
{
    int m1_total_numbers = m1_rows_num * m1_cols_num;
    int m2_total_numbers = m2_rows_num * m2_cols_num;
    int total_numbers = m1_total_numbers + m2_total_numbers;

    int *values = generate_matrix_values_in_memory(total_numbers);
    fill_matrix(m1_ptr, m1_rows_num, m1_cols_num, values, 0);
    fill_matrix(m2_ptr, m2_rows_num, m2_cols_num, values, m1_total_numbers - 1);

    free(values);
    values = NULL;
}

void fill_matrix(int **matrix_ptr, int rows_num, int cols_num, int *values, int start)
{
    for (int i = 0; i < rows_num; i++)
    {
        for (int j = 0; j < cols_num; j++)
        {
            matrix_ptr[i][j] = values[start];
            start++;
        }
    }
}

int *read_matrix_values_from_file(const char *file_name, const int total_numbers)
{
    int *values = (int *)malloc(sizeof(int) * total_numbers);
    FILE *file = fopen(file_name, "r");
    char line[5];
    int i = 0;

    while (!feof(file))
    {
        fgets(line, 5, file);
        int number = atoi(line);
        values[i] = number;
        i++;
    }
    fclose(file);
    return values;
}

int *generate_matrix_values_in_memory(const int total_numbers)
{
    int *values = (int *)malloc(sizeof(int) * total_numbers);
    srand(time(0));
    for (int i = 0; i < total_numbers; i++)
    {
        values[i] = rand() % 50;
    }

    return values;
}

int **add_matrices(int **m1_ptr, int m1_rows_num, int m1_cols_num,
                   int **m2_ptr, int m2_rows_num, int m2_cols_num)
{
    int **resultant_matrix;
    resultant_matrix = create_matrix(m1_rows_num, m2_cols_num);

    for (int i = 0; i < m1_rows_num; i++)
    {
        for (int j = 0; j < m1_cols_num; j++)
        {
            resultant_matrix[i][j] = m1_ptr[i][j] + m2_ptr[i][j];
        }
    }

    return resultant_matrix;
}

void print_matrix(int **matrix_ptr, int rows_num, int cols_num)
{
    for (int i = 0; i < rows_num; i++)
    {
        for (int j = 0; j < cols_num; j++)
        {
            printf("%3d ", matrix_ptr[i][j]);
        }
        printf("\n");
    }
}

void free_memory(int **m1_ptr, int m1_rows_num, int **m2_ptr, int m2_rows_num, int **m3_ptr)
{
    delete_matrix(m1_ptr, m1_rows_num);
    delete_matrix(m2_ptr, m2_rows_num);
    delete_matrix(m3_ptr, m1_rows_num);
}

void delete_matrix(int **matrix_ptr, int rows_number)
{
    /* Free memory for matrix columns */
    for (int i = 0; i < rows_number; i++)
        free(matrix_ptr[i]);

    /* Free memory for matrix rows */
    free(matrix_ptr);
}