#include "minirt.h"

void ft_rayInfo(t_ray r)
{
    printf("dir : %.2f, %.2f, %.2f\n", r.dir.x, r.dir.y, r.dir.z);
}

int ft_rayColor(t_mrt *mrt, t_ray *r)
{
    if(ft_hitSphere(&mrt->spr[0], r) == 1)
        return (ft_vec3ToInt(mrt->spr[0].color));
    return (0xFFFFFF);
}

t_ray ft_makeRay(t_mrt *mrt, t_vec3 vec)
{
    // for the direction is not sure to be normalize or not
    // return ((t_ray){mrt->cam.o, ft_vec3Minus(mrt->cam.o, vec)});
    return ((t_ray){mrt->cam.o, ft_vec3Unit(ft_vec3Minus(mrt->cam.o, vec))});
}
