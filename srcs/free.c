#include "minirt.h"

void ft_free2(char **arr)
{
    if (!arr)
        return ;
    int i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}