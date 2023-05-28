#include "minirt.h"

void	clamp(double *n, double min, double max)
{
	if (*n < min)
		*n = min;
	if (*n > max)
		*n = max;
}

double	update_rec(t_ray *r, t_object *obj, t_rec *rec, double t)
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

int	make_color(t_vec3 color)
{
	color.x *= 255;
	color.y *= 255;
	color.z *= 255;
	clamp(&color.x, 0.0, 255.0);
	clamp(&color.y, 0.0, 255.0);
	clamp(&color.z, 0.0, 255.0);
	return ((int)color.x << 16 | (int)color.y << 8 | (int)color.z);
}

double	hit_sphere(t_mrt *mrt, t_ray *r, t_object *obj, t_rec *rec)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	dis;
	double	sdis;
	double	t1;
	double	t2;

	(void)mrt;
	a = vec3dot(r->dir, r->dir);
	b = 2 * vec3dot(oc, r->dir);
	c = vec3dot(oc, oc) - (obj->radius * obj->radius);
	dis = b * b - (4 * a * c);
	oc = vec3minus(r->orig, obj->orig);
	if (dis < 0)
		return (0);
	sdis = sqrt(dis);
	t1 = (-b - sdis) / (2. * a);
	t2 = (-b + sdis) / (2. * a);
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

double	hit_plane(t_mrt *mrt, t_ray *r, t_object *obj, t_rec *rec)
{
	double	t;
	double	denom;
	t_vec3	pl;

	(void)mrt;
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
	double	t;
	double	dv;
	t_vec3	rd;
	t_vec3	p;

	dv = vec3dot(r->dir, cy->rot);
	if (dv < EPSILON)
		return (0);
	t = vec3dot(vec3minus(pl->orig, r->orig), cy->rot) / dv;
	p = vec3plus(r->orig, vec3mul(r->dir, t));
	rd = vec3minus(p, pl->orig);
	if (t > rec->tmin && t < rec->tmax
		&& t < rec->tnear && vec3len(rd) <= cy->radius)
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

double	hit_body(t_mrt *mrt, t_ray *r, t_object *obj, t_rec *rec)
{
	t_vec3	x;
	t_vec3	p;
	t_vec3	diff;
	t_vec3	pcent;
	double	dv;
	double	xv;
	double	a;
	double	hb;
	double	c;
	double	dis;
	double	t;
	double	dtop;

	(void) mrt;
	x = vec3minus(r->orig, obj->orig);
	dv = vec3dot(r->dir, obj->rot);
	xv = vec3dot(x, obj->rot);
	a = pow(vec3len(r->dir), 2) - pow(dv, 2);
	hb = vec3dot(x, r->dir) - (dv * xv);
	c = pow(vec3len(x), 2) - (obj->radius * obj->radius) - pow(xv, 2);
	dis = (hb * hb) - (a * c);
	if (dis < 0.0 || a == 0)
		return (0);
	t = (-hb - sqrt(dis)) / a;
	p = vec3plus(r->orig, vec3mul(r->dir, t));
	diff = vec3minus(obj->orig, p);
	if (t > rec->tnear || t < rec->tmin || t > rec->tmax)
		return (0);
	if (t < rec->tnear && fabs(vec3dot(diff, obj->rot)) <= (obj->height / 2))
	{
		rec->hit = 1;
		rec->tnear = t;
		rec->phit = p;
		dtop = vec3dot(diff, obj->rot);
		pcent = vec3plus(obj->orig, vec3mul(obj->rot, -dtop));
		rec->normal = vec3unit(vec3minus(rec->phit, pcent));
		rec->color = obj->color;
		return (1);
	}
	return (0);
}

double	hit_cylinder(t_mrt *mrt, t_ray *r, t_object *obj, t_rec *rec)
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
	if (hit_body(mrt, r, obj, rec) || hit_disc(obj, r, rec, &pl1)
		|| hit_disc(obj, r, rec, &pl2))
		return (1);
	else
		return (0);
}

int	trace(t_mrt *m, int i, int j)
{
	t_object	*obj;
	double		u;
	double		v;
	t_rec		rec;
	t_ray		r;

	rec.hit = 0;
	rec.color = vec3(0, 0, 0);
	rec.tnear = INFINITY;
	rec.tmin = 1;
	rec.tmax = INFINITY;
	r.orig = m->cam->orig;
	u = (2 * ((i + 0.5) / m->width) - 1) * m->aspectRatio;
	v = (1 - 2 * (j + 0.5) / m->height);
	r.dir.x = u * m->cam->u.x + v * m->cam->v.x - m->cam->d * m->cam->w.x;
	r.dir.y = u * m->cam->u.y + v * m->cam->v.y - m->cam->d * m->cam->w.y;
	r.dir.z = u * m->cam->u.z + v * m->cam->v.z - m->cam->d * m->cam->w.z;
	r.dir = vec3unit(r.dir);
	obj = m->obj;
	while (obj)
	{
		if (obj->type == SPHERE)
			hitSphere(m, &r, obj, &rec);
		else if (obj->type == PLANE)
			hitPlane(m, &r, obj, &rec);
		else if (obj->type == CYLINDER)
			hitCylinder(m, &r, obj, &rec);
		obj = obj->next;
	}
	shading(m, &rec);
	return (makeColor(rec.color));
}
