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
    mlx_hook(mrt->mlx.mlx_win, 2, 1L<<0, ft_exit, mrt);
    mlx_loop(mrt->mlx.mlx);
}

// convert vector to int for coloring
int ft_vec3ToInt(t_vec3 v)
{
    return ((int)v.x << 16 | (int)v.y << 8 | (int)v.z);
}

// convert pixel to world coordinate (raster->NDC->world)
t_vec3 ft_pixelToSpace(t_mrt *mrt, int i, int j)
{
    t_vec3 vec;
    vec.x = (2 * (i + 0.5) / mrt->scrn.width - 1) * mrt->scrn.aspectRatio * mrt->cam.fov;
    vec.y = (1 - 2 * (j + 0.5) / mrt->scrn.height) * mrt->cam.fov;
    vec.z = -1;
    return (vec);
}

// parameter information
void ft_parameter(t_mrt *mrt)
{
    // Width x Height
    printf("Widht : %d\n", mrt->scrn.width);
    printf("Height : %d\n", mrt->scrn.height);
    printf("Ambient Ratio : %.1f\n", mrt->ambt.ratio);
    printf("        Color : "); ft_vec3Info(mrt->ambt.color);
    printf("Camera Origin : "); ft_vec3Info(mrt->cam.orig);
    printf("       Rotation : "); ft_vec3Info(mrt->cam.rot);
    printf("       Fov : %.1f\n", mrt->cam.ifov);
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
    t_sphere *spr = mrt->spr;
    while (spr && ++i)
    {
        printf("Sphere %d Origin : ", i); ft_vec3Info(spr->orig);
        printf("          Dmt : %.1f\n", spr->dmt);
        printf("          Color : "); ft_vec3Info(spr->color);
        spr = spr->next;
    }
    i = 0;
    t_plane *pl = mrt->pl;
    while (pl && ++i)
    {
        printf("Plane %d Origin : ", i); ft_vec3Info(pl->p);
        printf("         Normal : "); ft_vec3Info(pl->normal);
        printf("         Color : "); ft_vec3Info(pl->color);
        pl = pl->next;
    }
    i = 0;
    t_cylinder *cydn = mrt->cydn;
    while (cydn && ++i)
    {
        printf("Cylinder %d Origin : ", i); ft_vec3Info(cydn->orig);
        printf("            Rotation : "); ft_vec3Info(cydn->rot);
        printf("            Dmt : %.1f\n", cydn->dmt);
        printf("            Height : %.1f\n", cydn->height);
        printf("            Color : "); ft_vec3Info(cydn->color);
        cydn = cydn->next;
    }
}
