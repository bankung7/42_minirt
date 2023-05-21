#include "minirt.h"

int arrLen(char **arr)
{
    int i;

    i = 0;
    while (arr && arr[i])
        i++;
    return (i);
}

int free2(char **arr)
{
    int i;

    i = 0;
    while (arr && arr[i])
        free(arr[i++]);
    free(arr);
    return (0);
}

double getDouble(char *str)
{
    double n;

    n = ft_atoi(str);
    while (ft_isdigit(*str) == 1)
        str++;
    if (*str != '.')
        return (n);
    int e = 1;
    while (ft_isdigit(*(++str)))
        n += (*str - '0') / pow(10.0, e++);
    return (n);
}
