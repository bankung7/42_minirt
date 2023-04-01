#include "minirt.h"

int ft_error(char *str, int res)
{
    printf("%s\n", str);
    return (res);
}

int ft_error2(char *str, int res, char **f2, char *f1)
{
    if (str)
        printf("%s\n", str);
    if (f2)
        ft_free2(f2);
    if (f1)
        free(f1);
    return (res);
}
