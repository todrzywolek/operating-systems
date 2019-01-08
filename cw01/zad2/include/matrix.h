#pragma once

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