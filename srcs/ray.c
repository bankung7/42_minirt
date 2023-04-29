#include "minirt.h"

void ft_rayInfo(t_ray r)
{
    printf("dir : %.2f, %.2f, %.2f\n", r.dir.x, r.dir.y, r.dir.z);
}

int ft_rayColor(t_mrt *mrt, t_ray *r)
{
    // try hit sphere
    // if(ft_hitSphere(&mrt->spr[0], r) == 1)
    //     return (ft_vec3ToInt(mrt->spr[0].color));

    // hit world
    t_vec3 color = (t_vec3){255, 255, 255};
    double tnear = INFINITY;
    double t;

    // hit sphere
    for (int i = 0; i < 2; i++)
    {
        t = ft_hitSphere(&mrt->spr[i], r, 1, INFINITY);
        if (t > 1 && t < tnear)
        {
            tnear = t;
            color = mrt->spr[i].color;
        }
    }

    // hit plane
    t = ft_hitPlane(&mrt->pl[0], r);
    if (t > 1 && t < tnear)
    {
        tnear = t;
        color = mrt->pl[0].color;
    }
    return (ft_vec3ToInt(color));
}

t_ray ft_makeRay(t_mrt *mrt, t_vec3 vec)
{
    // for the direction is not sure to be normalize or not
    // return ((t_ray){mrt->cam.o, ft_vec3Minus(vec, mrt->cam.o)});
    return ((t_ray){mrt->cam.o, ft_vec3Unit(ft_vec3Minus(vec, mrt->cam.o))});
}
