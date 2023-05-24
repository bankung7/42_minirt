#include "minirt.h"

void clamp(double *n, double min, double max)
{
    if (*n < min)
        *n = min;
    if (*n > max)
        *n = max;
}

double    updateRec(t_ray *r, t_object *obj, t_rec *rec, double t)
{
    rec->hit = 1;
    rec->tnear = t;
    rec->phit = vec3Plus(r->orig, vec3Mul(r->dir, t));
    if (obj->type == SPHERE || obj->type == CYLINDER)
        rec->normal = vec3Unit(vec3Minus(rec->phit, obj->orig));
    else if (obj->type == PLANE)
        rec->normal = obj->rot;
    rec->color = obj->color;    
    return (1); 
}

int makeColor(t_vec3 color)
{
    color.x *= 255;
    color.y *= 255;
    color.z *= 255;
    clamp(&color.x, 0.0, 255.0);
    clamp(&color.y, 0.0, 255.0);
    clamp(&color.z, 0.0, 255.0);
    // printf("%.2f, %.2f, %.2f\n", color.x, color.y, color.z);
    return ((int)color.x << 16 | (int)color.y << 8 | (int)color.z);
}

double hitSphere(t_mrt *mrt, t_ray *r, t_object *obj, t_rec *rec)
{
    (void)mrt;
    t_vec3 oc = vec3Minus(r->orig, obj->orig);
    double a = vec3Dot(r->dir, r->dir);
    double b = 2 * vec3Dot(oc, r->dir);
    double c = vec3Dot(oc, oc) - (obj->radius * obj->radius);
    double dis = b * b - (4 * a * c);
    if (dis < 0)
        return (0);
    double sdis = sqrt(dis);
    double t1 = (-b - sdis) / (2. * a);
    double t2 = (-b + sdis) / (2. * a);
    
    if (t1 > t2)
        t1 = t2;
    if (t1 < 0)
    {
        t1 = t2;
        if (t1 < 0)
            return (0);
    }
    if (t1 > rec->tnear || t1 < rec->tmin || t1 > rec->tmax)
        return (0);
    return (updateRec(r, obj, rec, t1));
    // rec->hit = 1;
    // rec->tnear = t1;
    // rec->phit = vec3Plus(r->orig, vec3Mul(r->dir, t1));
    // rec->normal = vec3Unit(vec3Minus(rec->phit, obj->orig));
    // printf("%.4f\n", vec3Dot(rec->phit, rec->normal));
    // rec->color = obj->color;
    // printf("%.2f, %.2f, %.2f\n", obj->orig.x, obj->orig.y, obj->orig.z);
    // printf("phit : %.2f, %.2f, %.2f\n", rec->phit.x, rec->phit.y, rec->phit.z);
    // printf("normal : %.2f, %.2f, %.2f\n", rec->normal.x, rec->normal.y, rec->normal.z);
    // printf("%.2f, %.2f, %.2f\n", rec->color.x, rec->color.y, rec->color.z);
    // return (1);
}

double hitPlane(t_mrt *mrt, t_ray *r, t_object *obj, t_rec *rec)
{
    (void)mrt;
    double t;
    double denom = vec3Dot(obj->rot, r->dir);
    if (fabs(denom) > 0.0001)
    {
        t_vec3 pl = vec3Minus(obj->orig, r->orig);
        t = vec3Dot(pl, obj->rot) / denom;
        if (t > 0.0001 && t < rec->tnear)
            return (updateRec(r, obj, rec, t));
        // {
        //     rec->hit = 1;
        //     rec->tnear = t;
        //     rec->phit = vec3Plus(r->orig, vec3Mul(r->dir, t));
        //     rec->normal = obj->rot;
        //     rec->color = obj->color;
        //     return (1);
        // }
    }
    return (0);
}

double hitDisc(t_object *cy, t_ray *r, t_rec *rec)
{
    t_object pl1;
    t_object pl2;
    pl1.type = PLANE, pl1.orig = vec3Plus(cy->orig, vec3Mul(cy->rot, (cy->height / 2))), pl1.color = cy->color;
    pl2.type = PLANE, pl2.orig = vec3Minus(cy->orig, vec3Mul(cy->rot, (cy->height / 2))), pl2.color = cy->color;
    if (vec3Dot(r->dir, cy->rot) == 0.0)
        return (0);
    double t1 = vec3Dot(vec3Minus(pl1.orig, r->orig), cy->rot) / vec3Dot(r->dir, cy->rot);
    double t2 = vec3Dot(vec3Minus(pl2.orig, r->orig), cy->rot) / vec3Dot(r->dir, cy->rot);
    t_vec3 p1 = vec3Plus(r->orig, vec3Mul(r->dir, t1));
    t_vec3 p2 = vec3Plus(r->orig, vec3Mul(r->dir, t2));
    if (t1 <= t2 && t1 < rec->tnear && vec3Len(vec3Minus(p1, pl1.orig)) <= cy->radius)
        return (updateRec(r, &pl1, rec, t1));   
    else if (t2 < t1 && t2 < rec->tnear && vec3Len(vec3Minus(p2, pl2.orig)) <= cy->radius)
        return (updateRec(r, &pl2, rec, t2));
    // {
    //     rec->hit = 1;
    //     rec->tnear = t;
    //     rec->phit = p;
    //     rec->normal = vec3Unit(cy->rot);
    //     rec->color = cy->color;
    //     return (1);
    // }
    return (0);
}

double hitCylinder(t_mrt *mrt, t_ray *r, t_object *obj, t_rec *rec)
{
    (void) mrt;
    t_vec3 x = vec3Minus(r->orig, obj->orig);
	double dv = vec3Dot(r->dir, obj->rot);
	double xv = vec3Dot(x, obj->rot);
	double a = pow(vec3Len(r->dir), 2) - pow(dv, 2);
    double hb = vec3Dot(x, r->dir) - (dv * xv);
    double c = pow(vec3Len(x), 2) - (obj->radius * obj->radius) - pow(xv, 2);
    double dis = (hb * hb) - (a * c);
    if (dis < 0.0 || a == 0)
        return (0);
    double t = (- hb - sqrt(dis)) / a;
    t_vec3 p = vec3Plus(r->orig, vec3Mul(r->dir, t));
    t_vec3 diff = vec3Minus(obj->orig, p);
    if (t < rec->tnear && fabs(vec3Dot(diff, obj->rot)) <= (obj->height / 2))
        return (updateRec(r, obj, rec, t));     
    hitDisc(obj, r, rec);
       
    // obj->pl1->orig = vec3Plus(obj->orig, vec3Mul(obj->rot, (obj->height / 2)));
    // obj->pl2->orig = vec3Minus(obj->orig, vec3Mul(obj->rot, (obj->height / 2)));
    // if (t < rec->tnear && hitDisc(obj->rot, r, rec, obj->radius / 2))
    //     return (updateRec(r, obj, rec, t));
        // return (1);
    return (0);
}

int trace(t_mrt *mrt, int i, int j)
{
    t_rec rec;
    t_ray ray;
    
    // set record
    rec.hit = 0;
    rec.color = vec3(0, 0, 0);
    rec.tnear = INFINITY;
    rec.tmin = 1;
    rec.tmax = INFINITY;

    // make ray
    ray.orig = mrt->cam->orig;

    double u = (2 * ((i + 0.5) / mrt->width) - 1) * mrt->aspectRatio * mrt->cam->d;
    double v = (1 - 2 * (j + 0.5) / mrt->height) * mrt->cam->d;

    ray.dir.x = u * mrt->cam->u.x + v * mrt->cam->v.x - mrt->cam->d * mrt->cam->w.x;
    ray.dir.y = u * mrt->cam->u.y + v * mrt->cam->v.y - mrt->cam->d * mrt->cam->w.y;
    ray.dir.z = u * mrt->cam->u.z + v * mrt->cam->v.z - mrt->cam->d * mrt->cam->w.z;

    ray.dir = vec3Unit(ray.dir);

    // printf("%.2f, %.2f, %.2f\n", ray.dir.x, ray.dir.y, ray.dir.z);

    // try hit something
    t_object *obj = mrt->obj;
    while (obj)
    {
        if (obj->type == SPHERE)
            hitSphere(mrt, &ray, obj, &rec);
        else if (obj->type == PLANE)
            hitPlane(mrt, &ray, obj, &rec);
        else if (obj->type == CYLINDER)
            hitCylinder(mrt, &ray, obj, &rec);
        obj = obj->next;
    }

    // shading
    shading(mrt, &rec);

    return (makeColor(rec.color));
}