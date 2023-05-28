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
    rec->phit = vec3plus(r->orig, vec3mul(r->dir, t));
    if (obj->type == SPHERE)
        rec->normal = vec3unit(vec3minus(rec->phit, obj->orig));
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
    t_vec3 oc = vec3minus(r->orig, obj->orig);
    double a = vec3dot(r->dir, r->dir);
    double b = 2 * vec3dot(oc, r->dir);
    double c = vec3dot(oc, oc) - (obj->radius * obj->radius);
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
    rec->hit = 1;
    rec->tnear = t1;
    rec->phit = vec3plus(r->orig, vec3mul(r->dir, t1));
    rec->normal = vec3unit(vec3minus(rec->phit, obj->orig));
    rec->color = obj->color;
    return (1);
}

double hitPlane(t_mrt *mrt, t_ray *r, t_object *obj, t_rec *rec)
{
    (void)mrt;
    double t;
    double denom = vec3dot(obj->rot, r->dir);
    if (fabs(denom) > EPSILON)
    {
        t_vec3 pl = vec3minus(obj->orig, r->orig);
        t = vec3dot(pl, obj->rot) / denom;
        if (t > EPSILON && t < rec->tnear)
        {
            rec->hit = 1;
            rec->tnear = t;
            rec->phit = vec3plus(r->orig, vec3mul(r->dir, t));
            rec->normal = obj->rot;
            rec->color = obj->color;
            return (1);
        }
    }
    return (0);
}

double hitDisc(t_object *cy, t_ray *r, t_rec *rec, t_object *pl)
{
    double t = vec3dot(vec3minus(pl->orig, r->orig), cy->rot) / vec3dot(r->dir, cy->rot);
    if (vec3dot(r->dir, cy->rot) == 0.0)
        return (0);
    t_vec3 p = vec3plus(r->orig, vec3mul(r->dir, t));
    if (t > rec->tmin && t < rec->tmax && t < rec->tnear && sqrtf(vec3dot(vec3minus(p, pl->orig), vec3minus(p, pl->orig))) <= cy->radius)
    {
        rec->hit = 1;
        rec->tnear = t;
        rec->phit = vec3plus(r->orig, vec3mul(r->dir, t));
        rec->normal = vec3unit(cy->rot);
        rec->color = cy->color;
        return (1);
    }
    return (0);
}

double hitBody(t_mrt *mrt, t_ray *r, t_object *obj, t_rec *rec)
{
    (void) mrt;
    t_vec3 x = vec3minus(r->orig, obj->orig);
	double dv = vec3dot(r->dir, obj->rot);
	double xv = vec3dot(x, obj->rot);
	double a = pow(vec3len(r->dir), 2) - pow(dv, 2);
    double hb = vec3dot(x, r->dir) - (dv * xv);
    double c = pow(vec3len(x), 2) - (obj->radius * obj->radius) - pow(xv, 2);
    double dis = (hb * hb) - (a * c);
    if (dis < 0.0 || a == 0)
        return (0);
    double t = (- hb - sqrt(dis)) / a;
    t_vec3 p = vec3plus(r->orig, vec3mul(r->dir, t));
    t_vec3 diff = vec3minus(obj->orig, p);
	if (t > rec->tnear || t < rec->tmin || t > rec->tmax)
		return (0);
	// if (hitDisc(obj, r, rec))
	// {
	if (t < rec->tnear && fabs(vec3dot(diff, obj->rot)) <= (obj->height / 2))
	{
		rec->hit = 1;
		rec->tnear = t;
		rec->phit = p;
		// t_vec3 C = vec3minus(obj->orig, vec3mul(obj->rot, obj->height / 2)); 
		// double m = (dv * t) + xv;
		double dtop = vec3dot(diff, obj->rot);
		t_vec3 pcent = vec3plus(obj->orig, vec3mul(obj->rot, -dtop));
		rec->normal = vec3unit(vec3minus(rec->phit, pcent));
		// rec->normal = vec3unit(vec3minus(rec->phit, vec3plus(C, vec3mul(obj->rot, m))));
		rec->color = obj->color;
		return (1);
	}
	// }
    // return(hitDisc(obj, r, rec));
	return (0);
}

double hitCylinder(t_mrt *mrt, t_ray *r, t_object *obj, t_rec *rec)
{
	t_object pl1;
    t_object pl2;
    pl1.type = PLANE, pl1.orig = vec3plus(obj->orig, vec3mul(obj->rot, (obj->height / 2))), pl1.color = obj->color, pl1.rot = obj->rot;
    pl2.type = PLANE, pl2.orig = vec3minus(obj->orig, vec3mul(obj->rot, (obj->height / 2))), pl2.color = obj->color, pl2.rot = vec3mul(obj->rot, -1);
	if (hitBody(mrt, r, obj, rec) || hitDisc(obj, r, rec, &pl1) || hitDisc(obj, r, rec, &pl2))
		return (1);
	else
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

    double u = (2 * ((i + 0.5) / mrt->width) - 1) * mrt->aspectRatio;
    double v = (1 - 2 * (j + 0.5) / mrt->height);

    ray.dir.x = u * mrt->cam->u.x + v * mrt->cam->v.x - mrt->cam->d * mrt->cam->w.x;
    ray.dir.y = u * mrt->cam->u.y + v * mrt->cam->v.y - mrt->cam->d * mrt->cam->w.y;
    ray.dir.z = u * mrt->cam->u.z + v * mrt->cam->v.z - mrt->cam->d * mrt->cam->w.z;

    ray.dir = vec3unit(ray.dir);

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