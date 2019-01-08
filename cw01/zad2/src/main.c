#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "matrix.h"
#include "time_counter.h"

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