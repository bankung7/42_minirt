#include "minirt.h"

int ft_arrLen(char **arr)
{
    int i;

    i = 0;
    if (!arr)
        return (0);
    while (arr[i])
        i++;
    return (i);
}

int ft_printArr(char **arr)
{
    if (!arr)
        return (1);
    int i = 0;
    while (arr && arr[i])
        printf("%s\n", arr[i++]);
    return (0);
}

double ft_atod(char *str)
{
    int i;
    int sign;
    double n;

    i = 0;
    sign = 1;
    n = 0;
    if (str[0] == '+' || str[0] == '-')
    {
        if (str[0] == '-')
            sign = -1;
        i++;
    }
    while (str[i] && ft_isdigit(str[i]) == 1)
        n = (n * 10) + (str[i++] - '0');
    if (str[i++] == '.')
    {
        while (str[i] && ft_isdigit(str[i]) == 1)
            n += (double)(str[i++] - '0') / 10;
    }
    return (n * sign);
}
