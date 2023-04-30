#include "minirt.h"

void ft_rayInfo(t_ray r)
{
    printf("dir : %.2f, %.2f, %.2f\n", r.dir.x, r.dir.y, r.dir.z);
}

t_vec3 ft_lookAt(t_ray *r, double t)
{
    return (ft_vec3Plus(r->orig, ft_vec3Mul(r->dir, t)));
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
    t_rec rec;
    rec.hit = 0;
    rec.color = mrt->ambt.color;
    rec.tmin = 1;
    rec.tmax = INFINITY;

    double tnear = INFINITY;

    // hit sphere
    for (int i = 0; i < 2; i++)
    {
        if (ft_hitSphere(&mrt->spr[i], r, &rec) == 1 && rec.t > 1 & rec.t < tnear)
        {
            tnear = rec.t;
            rec.color = ft_vec3Mulvec3(mrt->ambt.color, mrt->spr[i].color);
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

    // try to find light
    if (rec.hit == 1)
    {
        t_vec3 pl = ft_vec3Minus(mrt->lght.orig, rec.phit);
        double cosine = fmax(0, ft_vec3Dot(rec.normal, ft_vec3Unit(pl)));
        // printf("lambert factor : %.4f\n", cosine);
        double luminosity = 1.0 / (rec.t * rec.t);
        t_vec3 lcolor = ft_vec3Mul(mrt->lght.color, (cosine * luminosity));
        rec.color = ft_vec3Mulvec3(lcolor, rec.color);
    }

    ft_makeColor(&rec.color);
    return (ft_vec3ToInt(rec.color));
}

t_ray ft_makeRay(t_mrt *mrt, t_vec3 vec)
{
    // for the direction is not sure to be normalize or not
    // return ((t_ray){mrt->cam.o, ft_vec3Minus(vec, mrt->cam.o)});
    return ((t_ray){mrt->cam.o, ft_vec3Unit(ft_vec3Minus(vec, mrt->cam.o))});
}
