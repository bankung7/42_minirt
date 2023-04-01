#include "minirt.h"

void ft_readVector(t_vec vec)
{
    printf("vector: [%.1f][%.1f][%.1f]\n", vec.x, vec.y, vec.z);
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
