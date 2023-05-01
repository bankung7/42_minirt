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
    double t1 = (-b - sdis) / (2. * a);
    double t2 = (-b + sdis) / (2. * a);
    if (t1 > rec->tnear && t2 > rec->tnear)
        return (0);
    if (t1 > rec->tmin && t1 < rec->tmax && t1 < rec->tnear)
        rec->tnear = t1;
    if (t2 > rec->tmin && t2 < rec->tmax && t2 < rec->tnear)
        rec->tnear = t2;
    // set phit and normal vector
    rec->hit = 1;
    rec->phit = ft_lookAt(r, rec->tnear);
    rec->normal = ft_vec3Unit(ft_vec3Minus(rec->phit, spr->orig));
    rec->color = spr->color;
    return (1);
}

double ft_hitPlane(t_plane *plane, t_ray *r, t_rec *rec, double tnear)
{
    double t;
    double denom = ft_vec3Dot(plane->normal, r->dir);
    if (fabs(denom) > 0.0001)
    {
        t_vec3 pl = ft_vec3Minus(plane->p, r->orig);
        t = ft_vec3Dot(pl, plane->normal) / denom;
        if (t > 0.0001 && t < rec->t && t < tnear)
        {
            rec->hit = 1;
            rec->normal = plane->normal;
            rec->phit = ft_lookAt(r, t);
            rec->color = plane->color;
            return (t);
        }
    }
    return (0);
}
