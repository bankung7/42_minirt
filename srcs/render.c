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
            t_vec3 vec = ft_pixelToSpace(mrt, i, j);
            t_ray ray = ft_makeRay(mrt, vec);
            ft_putPixel(&mrt->mlx, i, j, ft_rayColor(mrt, &ray));
        }
    }
    mlx_put_image_to_window(mrt->mlx.mlx, mrt->mlx.mlx_win, mrt->mlx.img, 0, 0);
    mlx_hook(mrt->mlx.mlx_win, 2, 1L<<1, ft_hook, mrt);
    mlx_loop(mrt->mlx.mlx);
}

void ft_parameter(t_mrt *mrt)
{
    // Width x Height
    printf("Widht : %d\n", mrt->scrn.width);
    printf("Height : %d\n", mrt->scrn.height);
    printf("Ambient Ratio : %.1f\n", mrt->ambt.ratio);
    printf("Ambient Color : "); ft_vec3Info(mrt->ambt.color);
    printf("Camera Origin : "); ft_vec3Info(mrt->cam.orig);
    printf("Camera Rotation : "); ft_vec3Info(mrt->cam.rot);
    printf("Camera fov : %.1f\n", mrt->cam.fov);
    int i = 0;
    // Light
    t_light *lght = mrt->lght;
    while (lght && ++i)
    {
        printf("Light %d Origin : ", i); ft_vec3Info(lght->orig);
        printf("Light %d ratio : %.1f\n", i, lght->ratio);
        printf("Light %d Color : ", i); ft_vec3Info(lght->color);
        lght = lght->next;
    }
    i = 0;
    // sphere
    t_sphere *spr = mrt->spr;
    while (spr && ++i)
    {
        printf("Sphere %d Origin : ", i); ft_vec3Info(spr->orig);
        printf("Sphere %d dmt : %.1f\n", i, spr->dmt);
        printf("Sphere %d Color : ", i); ft_vec3Info(spr->color);
        spr = spr->next;
    }
    i = 0;
    t_plane *pl = mrt->pl;
    while (pl && ++i)
    {
        printf("Plane %d Origin : ", i); ft_vec3Info(pl->p);
        printf("Plane %d normal : ", i); ft_vec3Info(pl->normal);
        printf("Plane %d Color : ", i); ft_vec3Info(pl->color);
        pl = pl->next;
    }
    i = 0;
    t_cylinder *cydn = mrt->cydn;
    while (cydn && ++i)
    {
        printf("Cylinder %d Origin : ", i); ft_vec3Info(cydn->orig);
        printf("Cylinder %d rotation : ", i); ft_vec3Info(cydn->rot);
        printf("Cylinder %d dmt : %.1f\n", i, cydn->dmt);
        printf("Cylinder %d height : %.1f\n", i, cydn->height);
        printf("Cylinder %d Color : ", i); ft_vec3Info(cydn->color);
        cydn = cydn->next;
    }
}
