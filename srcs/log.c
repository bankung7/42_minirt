#include "minirt.h"

// free
int ft_free2(char **arr)
{
    int i = 0;
    if (!arr)
        return (0);
    while (arr && arr[i])
        free(arr[i++]);
    free(arr);
    return (0);
}

int ft_log(char *str, int res)
{
    if (str)
        printf("%s\n", str);
    return (res);
}

int ft_flog(char *str, int res, char **arr, char *s)
{
    if (arr)
        ft_free2(arr);
    if (s)
        free(s);
    return (ft_log(str, res));
}

// vetor info
void ft_vec3Info(t_vec3 v)
{
    printf("[%.1f][%.1f][%.1f]\n", v.x, v.y, v.z);
}