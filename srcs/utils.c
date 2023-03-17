#include "minirt.h"

void ft_info(t_vector v)
{
    printf("x: %f\n", v.x);
    printf("y: %f\n", v.y);
    printf("z: %f\n", v.z);
}

void ft_parr(char **arr)
{
    while (arr && *arr)
    {
        printf("%s\n", *arr);
        arr++;
    }
}

double ft_atof(char *str)
{
    double n;

    n = 0;
    if (!str)
        return (0);
    
    while (str)
    {
        if (ft_isdigit(*str))
            n = n * 10 + (*str - '0');
        else
            break ;
        str++;
    }
    printf("%f\n", n);
    return (0);
}