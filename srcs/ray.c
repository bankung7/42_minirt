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

// record
void ft_setRecord(t_rec *rec)
{
    rec->hit = 0;
    rec->color = (t_vec3){0, 0 ,0};
    rec->tmin = 0.0001;
    rec->tmax = INFINITY;
}

// lighting
int ft_lighting(t_mrt *mrt, t_rec *rec)
{
    // ambient light
    t_vec3 ambient = ft_vec3Mulvec3(rec->color, ft_vec3Mul(mrt->ambt.color, mrt->ambt.ratio));

    // diffuse light
    t_vec3 light = ft_vec3Unit(ft_vec3Minus(mrt->lght->orig, rec->phit));
    double factor = fmax(0.0, ft_vec3Dot(rec->normal, light));
    t_vec3 diffuse = ft_vec3Mul(rec->color, factor);

    // specular light
    t_vec3 reflect = ft_vec3Mul(rec->normal, (2.0 * ft_vec3Dot(light, rec->normal)));
    reflect = ft_vec3Unit(ft_vec3Minus(reflect, light));
    t_vec3 toCam = ft_vec3Unit(ft_vec3Minus(mrt->cam->orig, rec->phit));
    double cosine = ft_vec3Dot(reflect, toCam);
    t_vec3 specular = (t_vec3){0, 0, 0};
    if (cosine > 0.0)
        specular = ft_vec3Mul(rec->color, pow(cosine, 100));

    // total light
    rec->color = ft_vec3Plus(ambient, diffuse);
    rec->color = ft_vec3Plus(rec->color, specular);
    return (0);
}

// tracing
int ft_trace(t_mrt *mrt, t_ray *r, t_rec *rec, int mode)
{
    t_object *head = mrt->obj;

    while (head)
    {
        if (head->type == SPHERE)
            ft_hitSphere(head, r, rec);
        else if (head->type == PLANE)
            ft_hitPlane(head, r, rec);
        if (mode == 1 && rec->hit == 1)
            return (0);
        head = head->next;
    }
    if (mode == 1)
        return (1);
    return (rec->hit);
}

// preparing world trace
int ft_worldTrace(t_mrt *mrt, t_ray *r)
{
    // record
    t_rec rec;
    t_vec3 color;

    ft_setRecord(&rec);
    ft_trace(mrt, r, &rec, 0);

    if (rec.hit == 1)
    {
        color = rec.color; // set color
        rec.hit = 0; // reset hit
        rec.t = ft_vec3Len(ft_vec3Minus(mrt->lght->orig, rec.phit));

        t_ray shadow;
        shadow.dir = ft_vec3Minus(mrt->lght->orig, rec.phit);
        shadow.orig = ft_vec3Plus(rec.phit, ft_vec3Mul(shadow.dir, 0.0001));
        int inShadow = ft_trace(mrt, &shadow, &rec, 1);

        rec.color = color;
        ft_lighting(mrt, &rec);
        rec.color = ft_vec3Mul(rec.color, inShadow);
    }


    ft_makeColor(&rec.color);
    return (ft_vec3ToInt(rec.color));
}

t_ray ft_makeRay(t_mrt *mrt, double i, double j)
{
    double u = (2 * ((i + 0.5) / mrt->scrn.width) - 1) * mrt->scrn.aspectRatio * mrt->cam->d;
    double v = (1 - 2 * (j + 0.5) / mrt->scrn.height) * mrt->cam->d;

    t_ray ray;
    ray.orig = mrt->cam->orig;
    ray.dir.x = u * mrt->cam->u.x + v * mrt->cam->v.x - mrt->cam->d * mrt->cam->w.x;
    ray.dir.y = u * mrt->cam->u.y + v * mrt->cam->v.y - mrt->cam->d * mrt->cam->w.y;
    ray.dir.z = u * mrt->cam->u.z + v * mrt->cam->v.z - mrt->cam->d * mrt->cam->w.z;
    
    // if normalize, it will show like a bound to the edge
    // ray.dir = ft_vec3Unit(ray.dir);

    return (ray);
}
