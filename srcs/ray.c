/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:14:25 by pjerddee          #+#    #+#             */
/*   Updated: 2023/05/28 16:14:26 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clamp(double *n, double min, double max)
{
	if (*n < min)
		*n = min;
	if (*n > max)
		*n = max;
}

double	update_rec(t_ray *r, t_object *obj, t_rec *rec, t_hit hit)
{
	rec->hit = 1;
	rec->tnear = hit.t;
	rec->phit = vec3plus(r->orig, vec3mul(r->dir, hit.t));
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

void	setrec(t_rec *rec, t_ray *r, t_mrt *m)
{
	rec->hit = 0;
	rec->color = vec3(0, 0, 0);
	rec->tnear = INFINITY;
	rec->tmin = EPSILON;
	rec->tmax = INFINITY;
	r->orig = m->cam->orig;
}

int	trace(t_mrt *m, int i, int j)
{
	t_object	*obj;
	t_rec		rec;
	t_ray		r;
	t_u			u;

	setrec(&rec, &r, m);
	u.u = (2 * ((i + 0.5) / m->width) - 1) * m->aspect_ratio;
	u.v = (1 - 2 * (j + 0.5) / m->height);
	r.dir.x = u.u * m->cam->u.x + u.v * m->cam->v.x - m->cam->d * m->cam->w.x;
	r.dir.y = u.u * m->cam->u.y + u.v * m->cam->v.y - m->cam->d * m->cam->w.y;
	r.dir.z = u.u * m->cam->u.z + u.v * m->cam->v.z - m->cam->d * m->cam->w.z;
	r.dir = vec3unit(r.dir);
	obj = m->obj;
	while (obj)
	{
		if (obj->type == SPHERE)
			hit_sphere(&r, obj, &rec);
		else if (obj->type == PLANE)
			hit_plane(&r, obj, &rec);
		else if (obj->type == CYLINDER)
			hit_cylinder(&r, obj, &rec);
		obj = obj->next;
	}
	shading(m, &rec);
	return (make_color(rec.color));
}
