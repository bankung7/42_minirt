#include "minirt.h"

t_vec3 ft_rayAt(t_ray *r, double t)
{
    return (ft_vec3Plus(r->o, ft_vec3Mul(r->dir, t)));
}

t_vec3 ft_rayColor(t_mrt *mrt, t_ray *r)
{
    t_rec rec;
    rec.ray = *r;
    if (ft_worldHit(mrt, &rec, 0, INFINITY))
        return (rec.c);
    return ((t_vec3){0.5, 0.7, 0.9});
}

t_ray ft_makeRay(t_mrt *mrt, t_vec3 w, t_vec3 llc)
{
    t_ray ray;
    ray.o = mrt->cam.o;
    ray.dir = ft_vec3Minus(ft_vec3Plus(llc, w), ray.o);
    return (ray);
}