#include "minirt.h"

// add Camera
int addCamera(t_mrt *mrt, t_camera *node)
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

    if (mrt->cam && mrt->cam->unique == 1)
        return (free2(attr));
    if (mrt->cam && unique == 1)
        freeList((t_list*)mrt->cam);
    cam = malloc(sizeof(t_camera));
    if (!cam)
        return (qCode(mrt, 1));
    cam->orig = getVec3(mrt, attr[1], 1);
    cam->rot = getVec3(mrt, attr[2], 1);
    cam->fov = ft_atoi(attr[3]);
    free2(attr);
    cam->unique = unique;
    cam->next = 0;
    checkVec3(mrt, cam->orig, -INFINITY, INFINITY);
    checkVec3(mrt, cam->rot, -1.0, 1.0);
    checkValue(mrt, cam->fov, 0, 180);
    if (mrt->qcode)
        return (elog("Camera parsing fail", mrt->qcode));
    addCamera(mrt, cam);
    printf("Camera parsing completed\n");
    return (mrt->qcode);
}

int camera(t_mrt *mrt)
{
    if (vec3Len(mrt->cam->rot) == 0) // if rotation is not define
        mrt->cam->rot = vec3(0, 1, 0);
    // printf("%.2f, %.2f, %.2f\n", mrt->cam->rot.x, mrt->cam->rot.y, mrt->cam->rot.z);
    mrt->cam->w = vec3Unit(vec3Minus(mrt->cam->orig, (t_vec3){0, 0, -1}));
    mrt->cam->u = vec3Unit(vec3Cross(vec3Unit(mrt->cam->rot), mrt->cam->w));
    mrt->cam->v = vec3Cross(mrt->cam->w, mrt->cam->u);
    mrt->cam->d = tan(mrt->cam->fov * 0.5* M_PI / 180);
    // printf("%.2f, %.2f, %.2f\n", mrt->cam->u.x, mrt->cam->u.y, mrt->cam->u.z);
    return (0);
}
