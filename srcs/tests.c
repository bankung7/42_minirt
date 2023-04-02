#include "minirt.h"

void ft_readVector(t_vec vec)
{
    printf("[%.1f][%.1f][%.1f]\n", vec.x, vec.y, vec.z);
}

void ft_readColor(t_color color)
{
    printf("[%d][%d][%d]\n", color.r, color.g, color.b);
}

void ft_readLight(t_mrt *mrt)
{
    t_lght *head;

    head = mrt->lght;
    while (head)
    {
        printf("Light => coordinate : "); ft_readVector(head->crdt);
        printf("Light => brightness : [%.1f]\n", head->brght);
        printf("Light => color : "); ft_readColor(head->color);
        head = head->next;
    }
}

void ft_readPlane(t_mrt *mrt)
{
    t_plane *head;

    head = mrt->plane;
    while (head)
    {
        printf("plane => coordinate : "); ft_readVector(head->crdt);
        printf("plane => rot : "); ft_readVector(head->rot);
        printf("plane => color : "); ft_readColor(head->color);
        head = head->next;
    }
}

void ft_readSphere(t_mrt *mrt)
{
    t_sphere *head;

    head = mrt->sphere;
    while (head)
    {
        printf("sphere => coordinate : "); ft_readVector(head->crdt);
        printf("sphere => dmt : [%.1f]\n", head->dmt);
        printf("sphere => color : "); ft_readColor(head->color);
        head = head->next;
    }
}

void ft_readEnv(t_mrt *mrt)
{
    printf("Ambient => ratio : [%.1f]\n", mrt->ambt.ratio);
    printf("Ambient => color : "); ft_readColor(mrt->ambt.color);
    printf("Camera => coordinate : "); ft_readVector(mrt->cam.crdt);
    printf("Camera => rotation vector : "); ft_readVector(mrt->cam.rot);
    printf("Camera => FOV : [%d]\n", mrt->cam.fov);
    ft_readLight(mrt);
    ft_readPlane(mrt);
    ft_readSphere(mrt);
}