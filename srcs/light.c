#include "minirt.h"

int	add_light(t_mrt *mrt, t_light *node)
{
	t_light	*head;

	head = mrt->lght;
	if (!head)
		mrt->lght = node;
	else
	{
		while (head->next)
			head = head->next;
		head->next = node;
	}
	return (0);
}

int	get_light(t_mrt *mrt, char **attr, int unique)
{
	t_light	*lght;

	if (arr_len(attr) != 4)
		return (elog("Light error", qcode(mrt, free2(attr, 1))));
	if (mrt->lght && (mrt->lght->unique == 1 || unique == 1))
		return (elog("Light Duplicated", qcode(mrt, 1)));
	lght = malloc(sizeof(t_light));
	if (!lght)
		return (qcode(mrt, 1));
	lght->orig = getvec3(mrt, attr[1], 1);
	lght->ratio = getdouble(attr[2]);
	lght->color = getvec3(mrt, attr[3], 255);
	free2(attr, 0);
	lght->unique = unique;
	lght->next = 0;
	checkvec3(mrt, lght->orig, -INFINITY, INFINITY);
	checkvalue(mrt, lght->ratio, 0, 1.0);
	checkvec3(mrt, lght->color, 0, 1);
	if (mrt->qcode)
		return (elog("Light parsing fail", mrt->qcode));
	add_light(mrt, lght);
	printf("Light parsing completed\n");
	return (mrt->qcode);
}

int	shadow(t_mrt *mrt, t_ray *r, double length)
{
	t_rec		rec;
	t_object	*obj;

	rec.hit = 0;
	rec.tnear = INFINITY;
	rec.tmin = EPSILON;
	rec.tmax = INFINITY;
	obj = mrt->obj;
	while (obj)
	{
		if (obj->type == SPHERE)
			hit_sphere(r, obj, &rec);
		else if (obj->type == PLANE)
			hit_plane(r, obj, &rec);
		else if (obj->type == CYLINDER)
			hit_cylinder(r, obj, &rec);
		if (rec.hit == 1 && rec.tnear < length)
			return (1);
		obj = obj->next;
	}
	return (0);
}

int	shading(t_mrt *mrt, t_rec *rec)
{
	t_shade	sd;

	if (rec->hit == 0)
		return (0);
	sd.ambient = vec3mul(mrt->ambt->color, mrt->ambt->ratio);
	sd.sray.orig = vec3plus(rec->phit, vec3mul(rec->normal, EPSILON));
	sd.sray.dir = vec3minus(mrt->lght->orig, rec->phit);
	sd.length = vec3len(sd.sray.dir);
	sd.sray.dir = vec3unit(sd.sray.dir);
	if (shadow(mrt, &sd.sray, sd.length) == 1)
	{
		rec->color = vec3mulvec3(sd.ambient, rec->color);
		return (0);
	}
	sd.light = vec3unit(vec3minus(mrt->lght->orig, rec->phit));
	sd.dfactor = fmax(0.0, vec3dot(rec->normal, sd.light));
	sd.diffuse = vec3mul(mrt->lght->color, sd.dfactor * 0.6);
	sd.viewdir = vec3unit(vec3minus(mrt->cam->orig, rec->phit));
	sd.reflect = vec3mul(rec->normal, (2.0 * vec3dot(sd.light, rec->normal)));
	sd.reflect = vec3unit(vec3minus(sd.reflect, sd.light));
	sd.sfactor = pow(fmax(vec3dot(sd.viewdir, sd.reflect), 0.0), 32);
	sd.specular = vec3mul(mrt->lght->color, sd.sfactor * 0.5);
	sd.color = vec3plus(vec3plus(sd.ambient, sd.diffuse), sd.specular);
	rec->color = vec3mulvec3(sd.color, rec->color);
	return (0);
}
