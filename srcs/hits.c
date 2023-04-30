#include "minirt.h"

double ft_hitSphere(t_sphere *spr, t_ray *r, t_rec *rec)
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
    if (t < rec->tmin || t > rec->tmax)
    {
        t = (-b + sqrt(dis)) / (2 * a);
        if (t < rec->tmin || t > rec->tmax)
            return (0);
    }
    // set phit and normal vector
    rec->hit = 1;
    rec->t = t;
    rec->phit = ft_lookAt(r, rec->t);
    // rec->normal = ft_vec3Unit(ft_vec3Minus(rec->phit, spr->orig));
    rec->normal = ft_vec3Unit(ft_vec3Minus(spr->orig, rec->phit));
    return (1);
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
