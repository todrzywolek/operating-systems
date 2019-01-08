#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>
#include "time_counter.h"

void execute_cmd_and_measure_time(char *cmd, int instruction_number, int is_final)
{
    struct tms tmsstart, tmsend;
    clock_t start, end;
    int cmd_execution_status;

    printf("\nExecuting command: %s\n", cmd);

    start = save_timestamp(&tmsstart);
    cmd_execution_status = execute_command(cmd);
    end = save_timestamp(&tmsend);

    display_times(end - start, &tmsstart, &tmsend);
    exit_on_final_instruction(instruction_number, is_final, cmd_execution_status);
}

clock_t save_timestamp(struct tms *current_cpu_time)
{
    clock_t current_time;
    if ((current_time = times(current_cpu_time)) == -1)
    {
        printf("times error");
        exit(-1);
    }
    return current_time;
}

int execute_command(char *cmd)
{
    int cmd_execution_status = system(cmd);

    if (cmd_execution_status < 0)
    {
        printf("system() error");
        exit(-1);
    }

    return cmd_execution_status;
}

void display_times(clock_t real, struct tms *tmsstart, struct tms *tmsend)
{
    long clock_ticks_per_second = 0;

    if (is_read_first_time(clock_ticks_per_second))
        clock_ticks_per_second = set_clock_ticks();

    print_times(real, clock_ticks_per_second, tmsstart, tmsend);
}

int is_read_first_time(long variable)
{
    return variable == 0;
}

long set_clock_ticks()
{
    long clock_ticks_per_second = sysconf(_SC_CLK_TCK);
    if (clock_ticks_per_second < 0)
    {
        printf("sysconf error");
        exit(-1);
    }
    return clock_ticks_per_second;
}

void print_times(clock_t real, long clock_ticks_per_second, struct tms *tmsstart, struct tms *tmsend)
{
    print_real_time(real, clock_ticks_per_second);
    print_user_time(tmsstart, tmsend, clock_ticks_per_second);
    print_system_time(tmsstart, tmsend, clock_ticks_per_second);
    print_child_user_time(tmsstart, tmsend, clock_ticks_per_second);
    print_child_system_time(tmsstart, tmsend, clock_ticks_per_second);
}

void print_real_time(clock_t real, long clock_ticks_per_second)
{
    printf("  real:  %7.2f\n", real / (double)clock_ticks_per_second);
}

void print_user_time(struct tms *tmsstart, struct tms *tmsend, long clock_ticks_per_second)
{
    printf("  user:  %7.2f\n",
           (tmsend->tms_utime - tmsstart->tms_utime) / (double)clock_ticks_per_second);
}

void print_system_time(struct tms *tmsstart, struct tms *tmsend, long clock_ticks_per_second)
{
    printf("  sys:   %7.2f\n",
           (tmsend->tms_stime - tmsstart->tms_stime) / (double)clock_ticks_per_second);
}

void print_child_user_time(struct tms *tmsstart, struct tms *tmsend, long clock_ticks_per_second)
{
    printf("  child user:  %7.2f\n",
           (tmsend->tms_cutime - tmsstart->tms_cutime) / (double)clock_ticks_per_second);
}

void print_child_system_time(struct tms *tmsstart, struct tms *tmsend, long clock_ticks_per_second)
{
    printf("  child sys:   %7.2f\n",
           (tmsend->tms_cstime - tmsstart->tms_cstime) / (double)clock_ticks_per_second);
}

void exit_on_final_instruction(int instruction_number, int is_final, int cmd_execution_status)
{
    if (instruction_number == is_final)
        exit(cmd_execution_status);
}