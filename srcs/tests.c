#include "minirt.h"

void ft_readVector(t_vec vec)
{
    printf("[%.1f][%.1f][%.1f]\n", vec.x, vec.y, vec.z);
}

void ft_readColor(t_color color)
{
    printf("[%d][%d][%d]\n", color.r, color.g, color.b);
}

void ft_readSphere(t_mrt *mrt)
{
    int i = 0;
    t_sphere *head;

    head = mrt->sphere;
    if (!head)
        return ;
    printf("========== test sphere ==========\n");
    while (head)
    {
        printf("sphere object [%d]\n", ++i);
        printf("sphere coordinate : [%.1f] [%.1f] [%.1f]\n", head->crdt.x, head->crdt.y, head->crdt.z);
        printf("dmt : %0.1f\n", head->dmt); 
        printf("color : [%d][%d][%d]\n", head->color.r, head->color.g, head->color.b);
        head = head->next;
    }
    printf("========= Total sphere : %d ==========\n", i);
}

void ft_readEnv(t_mrt *mrt)
{
    printf("Ambient => ratio : [%.1f]\n", mrt->ambt.ratio);
    printf("Ambient => color : "); ft_readColor(mrt->ambt.color);
    printf("Camera => coordinate : "); ft_readVector(mrt->cam.crdt);
    printf("Camera => rotation vector : "); ft_readVector(mrt->cam.rot);
    printf("Camera => FOV : [%d]\n", mrt->cam.fov);
    printf("Light => coordinate : "); ft_readVector(mrt->lght.crdt);
    printf("Light => brightness : [%.1f]\n", mrt->lght.brght);
    printf("Light => color : "); ft_readColor(mrt->lght.color);

}