#include "minirt.h"

void ft_freeList(t_list *node)
{
    t_list *head = node;
    if (!node)
        return ;
    while (head)
    {
        node = node->next;
        free(head);
        head = node;
    }
}

int ft_clean(t_mrt *mrt)
{
    ft_freeList((t_list*)mrt->lght);
    ft_freeList((t_list*)mrt->spr);
    ft_freeList((t_list*)mrt->pl);
    ft_freeList((t_list*)mrt->cydn);
    return (0);
}
