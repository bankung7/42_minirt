#include "minirt.h"

int elog(char *str, int res)
{
    printf("Error\n%s\n", str);
    return (res);
}