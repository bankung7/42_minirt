#include "minirt.h"

int ft_hitSphere(t_sphere *spr, t_ray *r)
{
    t_vec3 oc = ft_vec3Minus(r->orig, spr->orig);
    double a = ft_vec3Dot(r->dir, r->dir);
    double b = 2 * ft_vec3Dot(r->dir, oc);
    double c = ft_vec3Dot(oc, oc) - (spr->r * spr->r);
    double dis = b * b - (4 * a * c);
    if (dis < 0)
        return (0);
    return (1);
}