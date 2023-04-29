#include "minirt.h"

double ft_hitSphere(t_sphere *spr, t_ray *r, double tmin, double tmax)
{
    t_vec3 oc = ft_vec3Minus(r->orig, spr->orig);
    double a = ft_vec3Dot(r->dir, r->dir);
    double b = 2 * ft_vec3Dot(oc, r->dir);
    double c = ft_vec3Dot(oc, oc) - (spr->r * spr->r);
    double dis = b * b - (4 * a * c);
    if (dis < 0)
        return (0);
    double sdis = sqrt(dis);
    double t = (-b - sdis) / (2 * a);
    if (t < tmin || t > tmax)
    {
        t = (-b + sqrt(dis)) / (2 * a);
        if (t < tmin || t > tmax)
            return (0);
    }
    return (t);
}

double ft_hitPlane(t_plane *plane, t_ray *r)
{
    double t;
    double denom = ft_vec3Dot(plane->normal, r->dir);
    if (fabs(denom) > 0.0001)
    {
        t_vec3 pl = ft_vec3Minus(plane->p, r->orig);
        t = ft_vec3Dot(pl, plane->normal) / denom;
        // printf("t : %.2f\n", t);
        if (t > 0.0001)
            return (t);
    }
    return (0);
}

double ft_randDouble(double min, double max)
{
    return (min + (max - min) * (rand() / (RAND_MAX + 1.)));
}

t_vec3 ft_randomColor(void)
{
    return ((t_vec3){ft_randDouble(0, 255), ft_randDouble(0, 255), ft_randDouble(0, 255)});
}