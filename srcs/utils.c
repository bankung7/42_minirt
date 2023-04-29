#include "minirt.h"

int ft_vec3ToInt(t_vec3 v)
{
    return ((int)v.x << 16 | (int)v.y << 8 | (int)v.z);
}

// convert pixel to world coordinate (raster->NDC->world)
t_vec3 ft_pixelToSpace(t_mrt *mrt, int i, int j)
{
    t_vec3 vec;
    vec.x = (2 * (i + 0.5) / mrt->scrn.width - 1) * mrt->scrn.aspectRatio * mrt->cam.fov;
    vec.y = (1 - 2 * (j + 0.5) / mrt->scrn.height) * mrt->cam.fov;
    vec.z = -1;
    return (vec);
}