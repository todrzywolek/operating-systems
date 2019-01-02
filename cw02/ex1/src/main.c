#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void validate_operation_and_argument_number(int number_of_arguments, char const *operation);
void run_operation(char const *argv[]);

int main(int argc, char const *argv[])
{
    validate_operation_and_argument_number(argc, argv[1]);
    run_operation(argv);

    return 0;
}

void validate_operation_and_argument_number(int number_of_arguments, char const *operation)
{
    if (number_of_arguments < 5)
    {
        printf("Invalid number of arguments\n");
        exit(-1);
    }
    else if (strcmp(operation, "generate") == 0 && number_of_arguments != 5)
    {
        printf("Invalid number of arguments for generate operation\n");
        exit(-1);
    }
    else if ((strcmp(operation, "sort") == 0 || strcmp(operation, "copy") == 0) &&
             number_of_arguments != 6)
    {
        printf("Invalid number of arguments for sort or copy operation\n");
        exit(-1);
    }
}

void run_operation(char const *argv[])
{
    char const *operation = argv[1];
    if (strcmp(operation, "generate") == 0)
    {
        printf("running generate\n");
    }
    else if (strcmp(operation, "sort") == 0)
    {
        printf("running sort\n");
    }
    else if (strcmp(operation, "copy") == 0)
    {
        printf("running copy\n");
    }
    else
    {
        printf("Invalid operation.\nAllowed operations:\n\tgenerate\n\tsort\n\tcopy\n");
        exit(-1);
    }
}
