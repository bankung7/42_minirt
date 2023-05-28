#include "minirt.h"

// int	free_type(t_mrt *mrt, int type)
// {
// 	t_object	*head;
// 	t_object	*head2;

// 	head = mrt->obj;
// 	head2 = head;
// 	if (!head)
// 		return (0);
// 	printf("this case\n");
// 	while (head)
// 	{
// 		if (head->type == type)
// 		{
// 			head = head->next;
// 			free(head2);
// 			head2->next = head;
// 		}
// 		head = head->next;
// 		head2 = head;
// 	}
// 	return (0);
// }

// jsut check there is any that type of object in the loop
int	check_unique(t_mrt *mrt, int type, int unique)
{
	t_object	*head;

	head = mrt->obj;
	if (!mrt->obj)
		return (0);
	while (head)
	{
		if (head->type == type)
		{
			if (unique == 1 || head->unique == 1)
				return (qCode(mrt, 1));
		}
		head = head->next;
	}
	return (0);
}

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

	if (check_unique(mrt, SPHERE, unique))
		return (elog("Duplicated Sphere", 1));
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (qCode(mrt, 1));
	obj->orig = getvec3(mrt, attr[1], 1);
	obj->radius = getdouble(attr[2]) / 2.0;
	obj->color = getvec3(mrt, attr[3], 255);
	free2(attr);
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

	if (check_unique(mrt, PLANE, unique))
		return (elog("Duplicated Plane", 1));
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (qCode(mrt, 1));
	obj->orig = getvec3(mrt, attr[1], 1);
	obj->rot = vec3unit(getvec3(mrt, attr[2], 1));
	obj->color = getvec3(mrt, attr[3], 255);
	free2(attr);
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

	if (check_unique(mrt, CYLINDER, unique))
		return (elog("Duplicated Cylinder", 1));
	obj = malloc(sizeof(t_object));
	if (!obj)
		return (qCode(mrt, 1));
	obj->orig = getvec3(mrt, attr[1], 1);
	obj->rot = vec3unit(getvec3(mrt, attr[2], 1));
	obj->radius = getdouble(attr[3]) / 2.0;
	obj->height = getdouble(attr[4]);
	obj->color = getvec3(mrt, attr[5], 255);
	free2(attr);
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
	printf("Sphere parsing completed\n");
	return (mrt->qcode);
}

int	get_object(t_mrt *mrt, char **attr)
{
	if (!ft_strncmp(attr[0], "SP", 3) && arr_len(attr) == 4)
		return (getSphere(mrt, attr, 1));
	if (!ft_strncmp(attr[0], "sp", 3) && arr_len(attr) == 4)
		return (getSphere(mrt, attr, 0));
	if (!ft_strncmp(attr[0], "PL", 3) && arr_len(attr) == 4)
		return (getPlane(mrt, attr, 1));
	if (!ft_strncmp(attr[0], "pl", 3) && arr_len(attr) == 4)
		return (getPlane(mrt, attr, 0));
	if (!ft_strncmp(attr[0], "CY", 3) && arr_len(attr) == 6)
		return (getCylinder(mrt, attr, 1));
	if (!ft_strncmp(attr[0], "cy", 3) && arr_len(attr) == 6)
		return (getCylinder(mrt, attr, 0));
	free2(attr);
	return (0);
}
