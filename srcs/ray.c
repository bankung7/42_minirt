#include "minirt.h"

void ft_rayInfo(t_ray r)
{
    printf("dir : %.2f, %.2f, %.2f\n", r.dir.x, r.dir.y, r.dir.z);
}

void ft_makeColor(t_vec3 *color)
{
    color->x *= 255.;
    color->y *= 255.;
    color->z *= 255.;
}

int ft_rayColor(t_mrt *mrt, t_ray *r)
{
    // hit world
    t_vec3 color = mrt->ambt.color;
    double tnear = INFINITY;
    double t;

    // hit sphere
    for (int i = 0; i < 2; i++)
    {
        t = ft_hitSphere(&mrt->spr[i], r, 1, INFINITY);
        if (t > 1 && t < tnear)
        {
            tnear = t;
            // color = mrt->spr[i].color;
            color = ft_vec3Mulvec3(mrt->ambt.color, mrt->spr[i].color);
            color = ft_vec3Mul(color, mrt->ambt.ratio);
        }
    }

    // hit plane
    // for (int i = 0; i < 5; i++)
    // {
    //     t = ft_hitPlane(&mrt->pl[i], r);
    //     if (t > 1 && t < tnear)
    //     {
    //         tnear = t;
    //         color = mrt->pl[i].color;
    //     }
    // }
    ft_makeColor(&color);
    return (ft_vec3ToInt(color));
}

t_ray ft_makeRay(t_mrt *mrt, t_vec3 vec)
{
    // for the direction is not sure to be normalize or not
    // return ((t_ray){mrt->cam.o, ft_vec3Minus(vec, mrt->cam.o)});
    return ((t_ray){mrt->cam.o, ft_vec3Unit(ft_vec3Minus(vec, mrt->cam.o))});
}
