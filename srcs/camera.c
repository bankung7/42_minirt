#include "minirt.h"

int camera(t_mrt *mrt)
{
    // wait of parsing
    mrt->cam = malloc(sizeof(t_camera));
    mrt->cam->orig = (t_vec3){2, 1, 5};
    mrt->cam->rot = (t_vec3){0, 1, 0};
    mrt->cam->fov = 100;

    mrt->cam->w = vec3Unit(vec3Minus(mrt->cam->orig, (t_vec3){0, 0, -1}));
    mrt->cam->u = vec3Unit(vec3Cross(mrt->cam->rot, mrt->cam->w));
    mrt->cam->v = vec3Cross(mrt->cam->w, mrt->cam->u);

    mrt->cam->d = tan(mrt->cam->fov * 0.5* M_PI / 180);
    return (0);
}