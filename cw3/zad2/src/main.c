#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

struct Command
{
    char *program_name;
    char *args[10];
};

void validate_arguments_number(int number_of_arguments);
FILE *open_input_file(char const *filename);
void read_line(char *line);
void read_line_2(char *line, struct Command *command);
int execute_in_separate_process(struct Command *command);
void err_sys(const char *x);

int main(int argc, char const *argv[])
{
    validate_arguments_number(argc);

    FILE *fp = open_input_file(argv[1]);

    char line[255];
    struct Command command;
    int execution_result = 0, line_number = 1;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        read_line_2(line, &command);
        execution_result = execute_in_separate_process(&command);
        if (execution_result < 0)
        {
            printf("execution failure on line %d. Stopping program.\n", line_number);
            fclose(fp);
            exit(-1);
        }
        line_number++;
    }

    fclose(fp);

    return 0;
}

void validate_arguments_number(int number_of_arguments)
{
    if (number_of_arguments != 2)
    {
        printf("Invalid number of arguments\n");
        printf("Proper usage <FILE_NAME>\n");
        exit(-1);
    }
}

FILE *open_input_file(char const *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Failed to open text file\n");
        exit(1);
    }
    return fp;
}

void read_line_2(char *line, struct Command *command)
{
    char *p = strtok(line, " ");
    command->program_name = p;
    int i = 0;

    for (; p != NULL; p = strtok(NULL, " "))
    {
        command->args[i] = p;
        i++;
    }
    // strip newline from the end
    command->args[i - 1][strcspn(command->args[i - 1], "\n")] = 0;
    command->args[i] = (char *)0;
}

int execute_in_separate_process(struct Command *command)
{
    pid_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork_error");
    else if (pid == 0)
    {
        int execution_result = execvp(command->program_name, command->args);
        if (execution_result < 0)
            return execution_result;
    }
    if (waitpid(pid, NULL, 0) < 0)
        err_sys("wait error");

    return 0;
}

void err_sys(const char *x)
{
    perror(x);
    exit(1);
}