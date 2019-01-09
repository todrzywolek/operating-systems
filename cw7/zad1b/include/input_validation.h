#pragma once

int read_producers_number(char const *argv[]);
int read_consumers_number(char const *argv[]);
int read_buffer_size(char const *argv[]);
void validate_arguments_number(int number_of_arguments);