#include "utils.h"

int isNumber(char *string)
{
    int n;
    int value;
    char c;
    n = sscanf(string, "%d%c", &value, &c);
    if (n != 1)
        return 0;
    return 1;
}