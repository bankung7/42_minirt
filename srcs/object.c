#include "minirt.h"

int	add_object(t_mrt *mrt, t_object *node)
{
	t_object	*head;

	head = mrt->obj;
	if (!head)
		mrt->obj = node;
	else
	{
		while (head->next)
			head = head->next;
		head->next = node;
	}
	return (0);
}

// check unique
int	get_sphere(t_mrt *mrt, char **attr, int unique)
{
	t_object	*obj;

	if (check_unique(mrt, SPHERE, unique) || arr_len(attr) != 4)
		return (elog("Sphere error", qcode(mrt, free2(attr, 1))));
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (qcode(mrt, 1));
	obj->orig = getvec3(mrt, attr[1], 1);
	obj->radius = getdouble(attr[2]) / 2.0;
	obj->color = getvec3(mrt, attr[3], 255);
	free2(attr, 0);
	obj->type = SPHERE;
	obj->unique = unique;
	obj->next = 0;
	checkvec3(mrt, obj->orig, -INFINITY, INFINITY);
	checkvalue(mrt, obj->radius, 0, INFINITY);
	checkvec3(mrt, obj->color, 0, 1);
	if (mrt->qcode)
		return (elog("Sphere parsing fail", mrt->qcode));
	add_object(mrt, obj);
	printf("Sphere parsing completed\n");
	return (mrt->qcode);
}

// check unique
int	get_plane(t_mrt *mrt, char **attr, int unique)
{
	t_object	*obj;

	if (check_unique(mrt, PLANE, unique) || arr_len(attr) != 4)
		return (elog("Duplicated Plane", qcode(mrt, free2(attr, 1))));
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (qcode(mrt, 1));
	obj->orig = getvec3(mrt, attr[1], 1);
	obj->rot = vec3unit(getvec3(mrt, attr[2], 1));
	obj->color = getvec3(mrt, attr[3], 255);
	free2(attr, 0);
	obj->type = PLANE;
	obj->unique = unique;
	obj->next = 0;
	checkvec3(mrt, obj->orig, -INFINITY, INFINITY);
	checkvec3(mrt, obj->rot, -1.0, 1.0);
	checkvec3(mrt, obj->color, 0, 1);
	if (mrt->qcode)
		return (elog("Plane parsing fail", mrt->qcode));
	add_object(mrt, obj);
	printf("Plane parsing completed\n");
	return (mrt->qcode);
}

// get Cylinder
// check unique
int	get_cylinder(t_mrt *mrt, char **attr, int unique)
{
	t_object	*obj;

	if (check_unique(mrt, CYLINDER, unique) || arr_len(attr) != 6)
		return (elog("Cylinder error", qcode(mrt, free2(attr, 1))));
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (qcode(mrt, 1));
	obj->orig = getvec3(mrt, attr[1], 1);
	obj->rot = vec3unit(getvec3(mrt, attr[2], 1));
	obj->radius = getdouble(attr[3]) / 2.0;
	obj->height = getdouble(attr[4]);
	obj->color = getvec3(mrt, attr[5], 255);
	free2(attr, 0);
	obj->type = CYLINDER;
	obj->unique = unique;
	obj->next = 0;
	checkvec3(mrt, obj->orig, -INFINITY, INFINITY);
	checkvec3(mrt, obj->rot, -1.0, 1.0);
	checkvalue(mrt, obj->radius, 0, INFINITY);
	checkvalue(mrt, obj->height, 0, INFINITY);
	checkvec3(mrt, obj->color, 0, 1);
	if (mrt->qcode)
		return (elog("Sphere parsing fail", mrt->qcode));
	add_object(mrt, obj);
	return (mrt->qcode);
}

int	get_object(t_mrt *mrt, char **attr)
{
	if (!ft_strncmp(attr[0], "SP", 3))
		return (get_sphere(mrt, attr, 1));
	if (!ft_strncmp(attr[0], "sp", 3))
		return (get_sphere(mrt, attr, 0));
	if (!ft_strncmp(attr[0], "PL", 3))
		return (get_plane(mrt, attr, 1));
	if (!ft_strncmp(attr[0], "pl", 3))
		return (get_plane(mrt, attr, 0));
	if (!ft_strncmp(attr[0], "CY", 3))
		return (get_cylinder(mrt, attr, 1));
	if (!ft_strncmp(attr[0], "cy", 3))
		return (get_cylinder(mrt, attr, 0));
	free2(attr, 0);
	return (0);
}
