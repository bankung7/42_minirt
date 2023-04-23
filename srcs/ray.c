#include "minirt.h"

int setFront(t_ray *r, t_vec3 out)
{
    double front = ft_vec3Dot(r->dir, out);
    if (front < 0)
        r->front = 1;
    else
    {
        r->front = 0;
        r->normal = ft_vec3Mul(r->normal, -1);
    }
    return (r->front);
}

double hit_sphere(t_sphere spr, t_ray *r, double tmin, double tmax)
{
    t_vec3 oc = ft_vec3Minus(r->o, spr.o);
    double a = ft_vec3Dot(r->dir, r->dir);
    double hb = ft_vec3Dot(oc, r->dir);
    double c = ft_vec3Dot(oc, oc) - spr.r * spr.r;
    double dis = (hb * hb) - (a * c);
    if (dis < 0)
        return (0);

    double sdis = sqrt(dis);
    // find the nearest
    double root = (-hb - sdis) / a;
    if (root < tmin || tmax < root)
    {
        root = (-hb + sdis) / a;
        if (root < tmin || tmax < root)
            return (0);
    }

    r->t = root;
    r->p = ft_rayAt(*r, r->t);
    r->normal = ft_vec3Unit(ft_vec3Div(ft_vec3Minus(r->p, spr.o), spr.r));
    r->front = setFront(r, r->normal);
    r->c = spr.color;
    return (1);
}

t_vec3 ft_rayAt(t_ray r, double t)
{
    return (ft_vec3Plus(r.o, ft_vec3Mul(r.dir, t)));
}

int ft_vec3ToColor(t_vec3 v)
{
    return ((int)v.x << 16 | (int)v.y << 8 | (int)v.z);
};

int ft_rayColor(t_mrt *mrt, t_ray *r)
{
    r->c = (t_vec3){255, 255, 255};
    double tmax = INFINITY;

    for (int i = 0; i < 2; i++)
    {
        if(hit_sphere(mrt->sphere[i], r, 0, tmax) == 1)
            tmax = r->t;
    }
    return (ft_vec3ToColor(r->c));
}

t_ray ft_makeRay(t_mrt *mrt, t_vec3 llc, t_vec3 hoz, t_vec3 ver)
{
    t_ray r;
    r.o = mrt->cam.o;
    r.dir = (t_vec3){
        llc.x + hoz.x + ver.x - r.o.x,
        llc.y + hoz.y + ver.y - r.o.y,
        llc.z + hoz.z + ver.z - r.o.z
    };
    return (r);
}