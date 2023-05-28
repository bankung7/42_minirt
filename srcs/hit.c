#include "minirt.h"

double	hit_sphere(t_ray *r, t_object *obj, t_rec *rec)
{
	t_hit	hit;

	hit.x = vec3minus(r->orig, obj->orig);
	hit.a = vec3dot(r->dir, r->dir);
	hit.hb = vec3dot(hit.x, r->dir);
	hit.c = vec3dot(hit.x, hit.x) - (obj->radius * obj->radius);
	hit.dis = hit.hb * hit.hb - (hit.a * hit.c);
	if (hit.dis < 0)
		return (0);
	hit.sdis = sqrt(hit.dis);
	hit.t = (-hit.hb - hit.sdis) / (hit.a);
	hit.t2 = (-hit.hb + hit.sdis) / (hit.a);
	if (hit.t > hit.t2)
		hit.t = hit.t2;
	if (hit.t < 0)
	{
		hit.t = hit.t2;
		if (hit.t < 0)
			return (0);
	}
	if (hit.t > rec->tnear || hit.t < rec->tmin || hit.t > rec->tmax)
		return (0);
	update_rec(r, obj, rec, hit);
	rec->normal = vec3unit(vec3minus(rec->phit, obj->orig));
	return (1);
}

double	hit_plane(t_ray *r, t_object *obj, t_rec *rec)
{
	double	t;
	double	denom;
	t_vec3	pl;

	denom = vec3dot(obj->rot, r->dir);
	if (fabs(denom) > EPSILON)
	{
		pl = vec3minus(obj->orig, r->orig);
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

double	hit_disc(t_object *cy, t_ray *r, t_rec *rec, t_object *pl)
{
	t_hit	hit;

	hit.dv = vec3dot(r->dir, cy->rot);
	hit.t = vec3dot(vec3minus(pl->orig, r->orig), cy->rot) / hit.dv;
	if (hit.dv == 0.0)
		return (0);
	hit.p = vec3plus(r->orig, vec3mul(r->dir, hit.t));
	if (hit.t > rec->tmin && hit.t < rec->tmax && hit.t < rec->tnear
		&& sqrtf(vec3dot(vec3minus(hit.p, pl->orig),
				vec3minus(hit.p, pl->orig))) <= cy->radius)
	{
		update_rec(r, cy, rec, hit);
		rec->normal = vec3unit(cy->rot);
		return (1);
	}
	return (0);
}

double	hit_body(t_ray *r, t_object *o, t_rec *rec)
{
	t_hit	h;

	h.x = vec3minus(r->orig, o->orig);
	h.dv = vec3dot(r->dir, o->rot);
	h.xv = vec3dot(h.x, o->rot);
	h.a = pow(vec3len(r->dir), 2) - pow(h.dv, 2);
	h.hb = vec3dot(h.x, r->dir) - (h.dv * h.xv);
	h.c = pow(vec3len(h.x), 2) - pow(o->radius, 2) - pow(h.xv, 2);
	h.dis = (h.hb * h.hb) - (h.a * h.c);
	if (h.dis < 0.0 || h.a == 0)
		return (0);
	h.t = (-h.hb - sqrt(h.dis)) / h.a;
	h.p = vec3plus(r->orig, vec3mul(r->dir, h.t));
	h.diff = vec3minus(o->orig, h.p);
	if (h.t > rec->tnear || h.t < rec->tmin || h.t > rec->tmax)
		return (0);
	if (h.t < rec->tnear && fabs(vec3dot(h.diff, o->rot)) <= (o->height / 2))
	{
		update_rec(r, o, rec, h);
		h.dtop = vec3dot(h.diff, o->rot);
		h.pcent = vec3plus(o->orig, vec3mul(o->rot, -h.dtop));
		rec->normal = vec3unit(vec3minus(rec->phit, h.pcent));
		return (1);
	}
	return (0);
}

double	hit_cylinder(t_ray *r, t_object *obj, t_rec *rec)
{
	t_object	pl1;
	t_object	pl2;

	pl1.type = PLANE;
	pl1.orig = vec3plus(obj->orig, vec3mul(obj->rot, (obj->height / 2)));
	pl1.color = obj->color;
	pl1.rot = obj->rot;
	pl2.type = PLANE;
	pl2.orig = vec3minus(obj->orig, vec3mul(obj->rot, (obj->height / 2)));
	pl2.color = obj->color;
	pl2.rot = vec3mul(obj->rot, -1);
	if (hit_body(r, obj, rec) || hit_disc(obj, r, rec, &pl1)
		|| hit_disc(obj, r, rec, &pl2))
		return (1);
	else
		return (0);
}
