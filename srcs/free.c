#include "minirt.h"

// free
int ft_free2(char **arr)
{
    int i = 0;
    if (!arr)
        return (0);
    while (arr && arr[i])
        free(arr[i++]);
    free(arr);
    return (0);
}

// free link list
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

// clean all object in mrt
int ft_clean(t_mrt *mrt)
{
    ft_freeList((t_list*)mrt->lght);
    ft_freeList((t_list*)mrt->spr);
    ft_freeList((t_list*)mrt->pl);
    ft_freeList((t_list*)mrt->cydn);
    return (0);
}
