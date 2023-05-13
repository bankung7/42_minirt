#include "minirt.h"

// 1. convert the scren pixel to space coordinate
// 2. make the ray from that coordinate
// 3. trace ray

void ft_render(t_mrt *mrt)
{
    for (int j = 0; j < mrt->scrn.height; ++j)
    {
        for (int i = 0; i < mrt->scrn.width; ++i)
        {
            t_ray ray = ft_makeRay(mrt, i, j);
            ft_putPixel(&mrt->mlx, i, j, ft_worldTrace(mrt, &ray));
        }
    }
    mlx_put_image_to_window(mrt->mlx.mlx, mrt->mlx.mlx_win, mrt->mlx.img, 0, 0);
    mlx_hook(mrt->mlx.mlx_win, 2, 1L<<0, ft_exit, mrt);
    mlx_loop(mrt->mlx.mlx);
}

// convert vector to int for coloring
int ft_vec3ToInt(t_vec3 v)
{
    return ((int)v.x << 16 | (int)v.y << 8 | (int)v.z);
}

// parameter information
void ft_parameter(t_mrt *mrt)
{
    // Width x Height
    printf("Widht : %d\n", mrt->scrn.width);
    printf("Height : %d\n", mrt->scrn.height);
    printf("Ambient Ratio : %.1f\n", mrt->ambt.ratio);
    printf("        Color : "); ft_vec3Info(mrt->ambt.color);
    printf("Camera Origin : "); ft_vec3Info(mrt->cam->orig);
    printf("       Rotation : "); ft_vec3Info(mrt->cam->rot);
    printf("       Fov : %.1f\n", mrt->cam->fov);
    int i = 0;
    // Light
    t_light *lght = mrt->lght;
    while (lght && ++i)
    {
        printf("Light %d Origin : ", i); ft_vec3Info(lght->orig);
        printf("         ratio : %.1f\n", lght->ratio);
        printf("         Color : "); ft_vec3Info(lght->color);
        lght = lght->next;
    }
    i = 0;
    // sphere
    t_object *obj = mrt->obj;
    while (obj && ++i)
    {
        if (obj->type == SPHERE)
        {
            printf("Sphere %d Origin : ", i); ft_vec3Info(obj->orig);
            printf("          Dmt : %.1f\n", obj->dmt);
            printf("          Color : "); ft_vec3Info(obj->color);
        }
        else if (obj->type == PLANE)
        {
            printf("Plane %d Origin : ", i); ft_vec3Info(obj->orig);
            printf("         Normal : "); ft_vec3Info(obj->normal);
            printf("         Color : "); ft_vec3Info(obj->color);
        }
        else if (obj->type == CYLINDER)
        {
            printf("Cylinder %d Origin : ", i); ft_vec3Info(obj->orig);
            printf("            Rotation : "); ft_vec3Info(obj->normal);
            printf("            Dmt : %.1f\n", obj->dmt);
            printf("            Height : %.1f\n", obj->height);
            printf("            Color : "); ft_vec3Info(obj->color);
        }
        obj = obj->next;
    }
}
