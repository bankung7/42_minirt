#include "minirt.h"

double ft_clamp(double v, double min, double max)
{
    if (v < min)
        return (min);
    if (v > max)
        return (max);
    return (v);
}

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

double ft_randDouble(double min, double max)
{
    return (min + (max - min) * (rand() / (RAND_MAX + 1.0)));
}

t_vec3 ft_randomColor(void)
{
    return ((t_vec3){ft_randDouble(0, 1), ft_randDouble(0, 1), ft_randDouble(0, 1)});
}

void ft_addLight(t_light **lght, t_light *node)
{
    t_light *head;
    head = *lght;
    if (!head)
        *lght = node;
    else
    {
        while (head->next)
            head = head->next;
        head->next = node;
    }
}

void ft_addSphere(t_sphere **spr, t_sphere *node)
{
    t_sphere *head;
    head = *spr;
    if (!head)
        *spr = node;
    else
    {
        while (head->next)
            head = head->next;
        head->next = node;
    }
}

void ft_addPlane(t_plane **pl, t_plane *node)
{
    t_plane *head;
    head = *pl;
    if (!head)
        *pl = node;
    else
    {
        while (head->next)
            head = head->next;
        head->next = node;
    }
}

void ft_addCylinder(t_cylinder **cydn, t_cylinder *node)
{
    t_cylinder *head;
    head = *cydn;
    if (!head)
        *cydn = node;
    else
    {
        while (head->next)
            head = head->next;
        head->next = node;
    }
}
