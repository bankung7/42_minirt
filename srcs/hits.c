#include "minirt.h"

t_vec3 ft_randIntUnitSphere(void)
{
    while (1)
    {
        t_vec3 p = ft_randDoubleVec3Range(-1, 1);
        if (ft_vec3Dot(p, p) >= 1)
            continue;
        return (p);
    }
}

int ft_hitSphere(t_sphere *spr, t_rec *rec, double tmin, double tmax)
{
    t_vec3 oc = ft_vec3Minus(rec->ray.o, spr->o);
    double a = ft_vec3Dot(rec->ray.dir, rec->ray.dir);
    double hb = ft_vec3Dot(oc, rec->ray.dir);
    double c = ft_vec3Dot(oc, oc) - (spr->r * spr->r);
    double dis = (hb * hb) - (a * c);

    if (dis < 0)
        return (0);
    double sdis = sqrt(dis);
    double root = (-hb - sdis) / a;
    if (root < tmin || tmax < root)
    {
        root = (-hb + sdis) / a;
        if (root < tmin || tmax < root)
            return (0);
    }
    rec->t = root;
    rec->p = ft_rayAt(&rec->ray, root);
    t_vec3 outnormal = ft_vec3Div(ft_vec3Minus(rec->p, spr->o), spr->r);
    if (ft_vec3Dot(rec->ray.dir, outnormal) < 0)
        rec->normal = ft_vec3Mul(outnormal, -1);
    else
        rec->normal = outnormal;
    rec->c = spr->c;
    return (1);
}

int ft_worldHit(t_mrt *mrt, t_rec *rec, double tmin, double tmax)
{
    rec->hit = 0;
    double tnear = tmax;

    // try sphere
    for (int i = 0; i < 2; i++)
    {
        if (ft_hitSphere(&mrt->sphere[i], rec, tmin, tnear) == 1)
        {
            rec->hit = 1;
            tnear = rec->t;
        }
    }
    return (rec->hit);
}