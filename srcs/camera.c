#include "minirt.h"

// add Camera
int	add_camera(t_mrt *mrt, t_camera *node)
{
	t_camera	*head;

	head = mrt->cam;
	if (!head)
		mrt->cam = node;
	else
	{
		while (head->next)
			head = head->next;
		head->next = node;
	}
	return (0);
}

// get camera
int	get_camera(t_mrt *mrt, char **attr, int unique)
{
	t_camera	*cam;

	if (arr_len(attr) != 4)
		return (elog("Camera error", qcode(mrt, 1)));
	if (mrt->cam && (mrt->cam->unique == 1 || unique == 1))
		return (elog("Camera Duplicated", qcode(mrt, 1)));
	cam = malloc(sizeof(t_camera));
	if (!cam)
		return (qcode(mrt, 1));
	cam->orig = getvec3(mrt, attr[1], 1);
	cam->rot = getvec3(mrt, attr[2], 1);
	cam->fov = ft_atoi(attr[3]);
	free2(attr);
	cam->unique = unique;
	cam->next = 0;
	checkvec3(mrt, cam->orig, -INFINITY, INFINITY);
	checkvec3(mrt, cam->rot, -1.0, 1.0);
	checkvalue(mrt, cam->fov, 0, 180);
	if (mrt->qcode)
		return (elog("Camera parsing fail", mrt->qcode));
	add_camera(mrt, cam);
	return (mrt->qcode);
}

int	camera(t_mrt *mrt)
{
	if (!mrt->cam)
		return (qcode(mrt, 1));
	if (vec3len(mrt->cam->rot) == 0)
		mrt->cam->rot = vec3(0, 1, 0);
	mrt->cam->d = 1.0 / tanf(mrt->cam->fov * 0.5 * 3.1415 / 180.0);
	mrt->cam->w = vec3unit(vec3minus(mrt->cam->orig, vec3(0, 0, 0)));
	mrt->cam->u = vec3unit(vec3cross(vec3unit(mrt->cam->rot), mrt->cam->w));
	mrt->cam->v = vec3cross(mrt->cam->w, mrt->cam->u);
	return (0);
}

// switch cam => should be okay now
int	switch_cam(t_mrt *mrt)
{
	t_camera	*head1;
	t_camera	*head2;

	if (!mrt->cam || !mrt->cam->next)
		return (0);
	head1 = mrt->cam;
	mrt->cam = head1->next;
	head2 = head1;
	while (head2->next)
		head2 = head2->next;
	head2->next = head1;
	head1->next = 0;
	camera(mrt);
	mlx_destroy_image(mrt->mlx.mlx, mrt->mlx.img);
	return (render(mrt));
}
