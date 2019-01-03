//#include <stdio.h>
//#include <stdlib.h>
//#include <errno.h>
//#include <limits.h>
#include <sys/types>

void validate_arguments_number(int number_of_arguments);
FILE *open_input_file(char *filename);
void read_line(char *line);
void err_sys(const char *x);

struct Command
{
    char *program_name;
    char *args[10];
}

int
main(int argc, char const *argv[])
{
    validate_arguments_number(argc);

    FILE *fp = open_input_file("arguments.txt");

    char line[255];
    struct Command command;
    while (fgets(line, sizeof(line), fp) == NULL)
    {
        read_line(fp);
        execute_in_separate_process(&command);
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

FILE *open_input_file(char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (!in)
    {
        printf("Failed to open text file\n");
        exit(1);
    }
    return fp;
}

void read_line(char *line)
{
    for (char *p = strtok(line, " "); p != NULL; p = strtok(NULL, " "))
    {
        puts(p);
    }
}

void read_line_2(char *line, struct Command *command)
{
    char *p = strtok(line, " ");
    printf("%s", p);
    command->program_name = p;
    int i = 0;

    for (*p = strtok(line, " "); p != NULL; p = strtok(NULL, " "))
    {
        printf("%s", p);
        command->args[i] = p;
        i++;
    }
    command->args[i] = (char *)0;
}

void execute_in_separate_process(struct Command *command)
{
    pit_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork_error");
    else if (pid == 0)
    {
        if (execvp(command->program_name, command->program_name, command->args) < 0)
            err_sys("execvp error");
    }
    if (waitpid(pid, NULL, 0) < 0)
        err_sys("wait error");
}

void err_sys(const char *x)
{
    perror(x);
    exit(1);
}