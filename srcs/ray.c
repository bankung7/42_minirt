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

int ft_trace(t_mrt *mrt, t_ray *r)
{
    t_rec rec;

    // trace sphere
    for (int i = 0; i < 3; i++)
    {
        if (ft_hitSphere(&mrt->spr[i], r, &rec) == 1)
            return (1);
    }
    return (0);
}

int ft_rayColor(t_mrt *mrt, t_ray *r)
{
    // hit world
    t_rec rec;
    t_vec3 color = mrt->ambt.color;
    rec.hit = 0;
    rec.color = (t_vec3){0, 0, 0};
    rec.t = INFINITY;
    rec.tnear = rec.t;
    rec.tmin = 0.001;
    rec.tmax = INFINITY;

    // double tnear = INFINITY;

    // hit sphere
    for (int i = 0; i < 3; i++)
        ft_hitSphere(&mrt->spr[i], r, &rec);

    // hit plane
    for (int i = 0; i < 5; i++)
        ft_hitPlane(&mrt->pl[i], r, &rec);

    // try to find light
    if (rec.hit == 1)
    {
        // // ambient light
        // t_vec3 acolor = ft_vec3Mul(mrt->ambt.color, mrt->ambt.ratio);
        // // color = ft_vec3Mul(mrt->ambt.color, mrt->ambt.ratio);
        // // color = ft_vec3Mulvec3(color, rec.color);

        // // diffuse light
        // t_vec3 light = ft_vec3Unit(ft_vec3Minus(mrt->lght.orig, rec.phit));
        // double factor = fmax(0, ft_vec3Dot(rec.normal, light));
        // t_vec3 dcolor = ft_vec3Mul(rec.color, (factor * mrt->lght.ratio));
        // // color = ft_vec3Mulvec3(color, ft_vec3Mul(mrt->lght.color, 0.8 * factor));

        // total light
        // color = ft_vec3Plus(acolor, dcolor);

        //light
        t_vec3 light = ft_vec3Unit(ft_vec3Minus(mrt->lght.orig, rec.phit));
        double factor = fmax(0, ft_vec3Dot(rec.normal, light));
        double lightPower = factor * mrt->lght.ratio;
        double lightReflect = 1; // note to think about albedo value
        color = ft_vec3Mul(ft_vec3Mulvec3(rec.color, mrt->lght.color), lightPower * lightReflect);

        // // shadow
        t_ray shadow;
        shadow.orig = ft_vec3Plus(rec.phit, ft_vec3Mul(rec.normal, 1e-4));
        shadow.dir = light;
        if (ft_trace(mrt, &shadow) == 1)
            color = ft_vec3Mul(color, 0);
    }

    ft_makeColor(&color);
    return (ft_vec3ToInt(color));
}

t_ray ft_makeRay(t_mrt *mrt, t_vec3 vec)
{
    // for the direction is not sure to be normalize or not
    // return ((t_ray){mrt->cam.o, ft_vec3Minus(vec, mrt->cam.o)});
    return ((t_ray){mrt->cam.o, ft_vec3Unit(ft_vec3Minus(vec, mrt->cam.o))});
}
