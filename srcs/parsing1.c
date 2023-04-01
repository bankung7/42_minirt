#include "minirt.h"

char **ft_getAttr(char *line, int n, int c)
{
    char **attr;

    attr = ft_split(line, c);
    if (!attr)
        return (0);
    if (n == 0 || (ft_arrLen(attr) == n))
        return (attr);
    ft_free2(attr);
    return (0);
}

// Sphere:
// sp 0.0,0.0,20.6 12.6 10,0,255
// [iden] [coordinate] [diameter] [colorRGB]
// identifier: sp
// x,y,z coordinates of the sphere center: 0.0,0.0,20.6
// the sphere diameter: 12.6
// R,G,B colors in range [0-255]: 10, 0, 255
int ft_getSphere(t_mrt *mrt, char **arr)
{
    t_sphere *spr = malloc(sizeof(t_sphere));
    if (!spr)
        return (ft_error2("minirt: parsing sphere error", 1, arr, 0));
    if (ft_getVector(&spr->crdt, ft_getAttr(arr[1], 3, ','), 0, 100))
        return (ft_error2("minirt: parsing sphere error", 1, arr, 0));
    ft_free2(arr);
    spr->next = mrt->sphere;
    mrt->sphere = spr;
    return (0);
}

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

// the problem is the space request is nothing for sphere now