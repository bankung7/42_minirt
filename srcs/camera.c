#include "minirt.h"

// add Camera
int add_camera(t_mrt *mrt, t_camera *node)
{
    t_camera *head;

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
int getCamera(t_mrt *mrt, char **attr, int unique)
{
    t_camera *cam;

    if (mrt->cam && (mrt->cam->unique == 1 || unique == 1))
        return (elog("Camera Duplicated", qCode(mrt, 1)));
    cam = malloc(sizeof(t_camera));
    if (!cam)
        return (qCode(mrt, 1));
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
    printf("Camera parsing completed\n");
    return (mrt->qcode);
}

int camera(t_mrt *mrt)
{
    if (vec3len(mrt->cam->rot) == 0) // if rotation is not define
        mrt->cam->rot = vec3(0, 1, 0);
    mrt->cam->d = tan(mrt->cam->fov * 0.5* M_PI / 180);
    printf("%.2f, %.2f, %.2f\n", mrt->cam->rot.x, mrt->cam->rot.y, mrt->cam->rot.z);
    mrt->cam->w = vec3unit(vec3minus(mrt->cam->orig, (t_vec3){0, 0, -mrt->cam->d}));
    mrt->cam->u = vec3unit(vec3cross(vec3unit(mrt->cam->rot), mrt->cam->w));
    mrt->cam->v = vec3cross(mrt->cam->w, mrt->cam->u);
    printf("u: %.2f, %.2f, %.2f\n", mrt->cam->u.x, mrt->cam->u.y, mrt->cam->u.z);
    printf("v: %.2f, %.2f, %.2f\n", mrt->cam->v.x, mrt->cam->v.y, mrt->cam->v.z);
    printf("w: %.2f, %.2f, %.2f\n", mrt->cam->w.x, mrt->cam->w.y, mrt->cam->w.z);
    return (0);
}

// switch cam => should be okay now
int switch_cam(t_mrt *mrt)
{
    t_camera *head1 = mrt->cam;
    t_camera *head2;

    if (!mrt->cam || !mrt->cam->next)
        return (0);
    printf("switch cam\n");
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

// rotation view of the camera
