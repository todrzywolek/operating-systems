#pragma once
#include <sys/times.h>

void execute_cmd_and_measure_time(char *cmd, int instruction_number, int is_final);

clock_t save_timestamp(struct tms *current_cpu_time);

int execute_command(char *cmd);

void display_times(clock_t real, struct tms *tmsstart, struct tms *tmsend);

int is_read_first_time(long variable);

long set_clock_ticks();

void print_times(clock_t real, long clock_ticks_per_second, struct tms *tmsstart, struct tms *tmsend);

void print_real_time(clock_t real, long clock_ticks_per_second);

void print_user_time(struct tms *tmsstart, struct tms *tmsend, long clock_ticks_per_second);

void print_system_time(struct tms *tmsstart, struct tms *tmsend, long clock_ticks_per_second);

void print_child_user_time(struct tms *tmsstart, struct tms *tmsend, long clock_ticks_per_second);

void print_child_system_time(struct tms *tmsstart, struct tms *tmsend, long clock_ticks_per_second);

void exit_on_final_instruction(int instruction_number, int is_final, int cmd_execution_status);