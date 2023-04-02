#include "minirt.h"

// Sphere:
// sp 0.0,0.0,20.6 12.6 10,0,255
// [iden] [coordinate] [diameter] [colorRGB]
// identifier: sp
// x,y,z coordinates of the sphere center: 0.0,0.0,20.6
// the sphere diameter: 12.6
// R,G,B colors in range [0-255]: 10, 0, 255

// Cylinder:
// cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
// [iden] [coordinate] [rotation vector] [colorRGB]
// identifier: cy
// x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
// 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis:
// 0.0,0.0,1.0
// the cylinder diameter: 14.2
// the cylinder height: 21.42
// R,G,B colors in range [0,255]: 10, 0, 255

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
    return (0);
}

int ft_getVector(t_vec *vec, char **attr)
{
    if (!attr)
        return (1);
    vec->x = ft_atod(attr[0]);
    vec->y = ft_atod(attr[1]);
    vec->z = ft_atod(attr[2]);
    return (0);
}