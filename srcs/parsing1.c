#include "minirt.h"

char **ft_getAttr(char *line, int n, int c)
{
    char **attr = ft_split(line, c);
    if (n == -1 || ft_arrLen(attr) == n)
        return (attr);
    ft_free2(attr);
    return (0);
}

int ft_getColor(t_color *color, char **attr)
{
    if (!attr)
        return (1);
    color->r = ft_atoi(attr[0]);
    color->g = ft_atoi(attr[1]);
    color->b = ft_atoi(attr[2]);
    ft_free2(attr);
    return (0);
}

int ft_getVector(t_vec *vec, char **attr)
{
    if (!attr)
        return (1);
    vec->x = ft_atod(attr[0]);
    vec->y = ft_atod(attr[1]);
    vec->z = ft_atod(attr[2]);
    ft_free2(attr);
    return (0);
}