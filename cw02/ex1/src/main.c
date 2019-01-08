#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generate.h"
#include "sort.h"
#include "my_copy.h"

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
    printf("Args:%d", number_of_arguments);
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
    else if (strcmp(operation, "sort") == 0 && number_of_arguments != 6)
    {
        printf("Invalid number of arguments for sort operation\n");
        exit(-1);
    }
    else if (strcmp(operation, "copy") == 0 && number_of_arguments != 7)
    {
        printf("Invalid number of arguments for copy operation\n");
        exit(-1);
    }
}

void run_operation(char const *argv[])
{
    char const *operation = argv[1];
    if (strcmp(operation, "generate") == 0)
    {
        printf("running generate\n");
        generate(argv);
    }
    else if (strcmp(operation, "sort") == 0)
    {
        printf("running sort\n");
        sort(argv);
    }
    else if (strcmp(operation, "copy") == 0)
    {
        printf("running copy\n");
        run_copy(argv);
    }
    else
    {
        printf("Invalid operation.\nAllowed operations:\n\tgenerate\n\tsort\n\tcopy\n");
        exit(-1);
    }
}
