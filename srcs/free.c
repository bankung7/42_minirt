#include "minirt.h"

int ft_free2(char **arr)
{
    if (!arr)
        return (0);
    int i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
    return (0);
}
