#include "minirt.h"

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
