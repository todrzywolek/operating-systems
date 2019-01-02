#pragma once

void generate(char const *argv[]);

char **allocate_records(int num_of_records, int record_size);

void read_records(char **records, int num_of_records, int record_size);

void print_first_byte(char **records, int num_of_records);