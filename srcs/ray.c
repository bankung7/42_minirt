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
    color->x *= 255.0;
    color->y *= 255.0;
    color->z *= 255.0;
    color->x = ft_clamp(color->x, 0, 255);
    color->y = ft_clamp(color->y, 0, 255);
    color->z = ft_clamp(color->z, 0, 255);
}

int ft_trace(t_mrt *mrt, t_ray *r)
{
    t_rec rec;
    t_sphere *shead = mrt->spr;

    // trace sphere
    while (shead)
    {
        if (ft_hitSphere(shead, r, &rec) == 1)
            return (0);
        shead = shead->next;
    }
    return (1);
}

int ft_rayColor(t_mrt *mrt, t_ray *r)
{
    // hit world
    t_rec rec;
    t_vec3 color = (t_vec3){0, 0, 0};
    rec.hit = 0;
    rec.color = (t_vec3){0, 0, 0};
    rec.t = INFINITY;
    rec.tnear = rec.t;
    rec.tmin = 0.001;
    rec.tmax = INFINITY;

    // hit sphere
    t_sphere *shead = mrt->spr;
    while (shead)
    {
        ft_hitSphere(shead, r, &rec);
        shead = shead->next;
    }

    // hit plane
    t_plane *thead = mrt->pl;
    while (thead)
    {
        ft_hitPlane(thead, r, &rec);
        thead = thead->next;
    }

    // try to find light
    if (rec.hit == 1)
    {
        // ambient light

        // diffuse light
        t_vec3 light = ft_vec3Unit(ft_vec3Minus(mrt->lght->orig, rec.phit));
        double factor = fmax(0.0, ft_vec3Dot(rec.normal, light));

        // specular light
        t_vec3 reflection = ft_vec3Minus(ft_vec3Mul(rec.normal, 2.0 * ft_vec3Dot(rec.normal, light)), light);
        t_vec3 toCam = ft_vec3Mul(rec.phit, -1.0);
        reflection = ft_vec3Unit(reflection);
        toCam = ft_vec3Unit(toCam);
        double cosine = pow(fmax(0.0, ft_vec3Dot(reflection, toCam)), 180);

        // total light
        double lightIntensity = mrt->ambt.ratio + factor + cosine;
        color = ft_vec3Mul(mrt->ambt.color, lightIntensity);
        color = ft_vec3Mulvec3(color, rec.color);

        // // shadow
        t_ray shadow;
        shadow.orig = ft_vec3Plus(rec.phit, ft_vec3Mul(rec.normal, 1e-13));
        shadow.dir = light;
        color = ft_vec3Mul(color, ft_trace(mrt, &shadow));
    }

    ft_makeColor(&color);
    return (ft_vec3ToInt(color));
}

t_ray ft_makeRay(t_mrt *mrt, double i, double j)
{
    double u = (2 * ((i + 0.5) / mrt->scrn.width) - 1) * mrt->scrn.aspectRatio * mrt->cam.fov;
    double v = (1 - 2 * (j + 0.5) / mrt->scrn.height) * mrt->cam.fov;

    t_ray ray;
    ray.orig = mrt->cam.orig;
    ray.dir.x = u * mrt->cam.u.x + v * mrt->cam.v.x - mrt->cam.fov * mrt->cam.w.x;
    ray.dir.y = u * mrt->cam.u.y + v * mrt->cam.v.y - mrt->cam.fov * mrt->cam.w.y;
    ray.dir.z = u * mrt->cam.u.z + v * mrt->cam.v.z - mrt->cam.fov * mrt->cam.w.z;
    ray.dir = ft_vec3Unit(ray.dir);
    return (ray);
}
