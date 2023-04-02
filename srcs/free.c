#include "minirt.h"

int ft_free2(char **arr)
{
    if (!arr)
        return (0);
    int i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
    return (0);
}

int ft_clean(t_mrt *mrt)
{
    t_list *head;
    while (mrt->lght)
    {
        head = (t_list*)mrt->lght;
        mrt->lght = mrt->lght->next;
        free(head);
    }
    while (mrt->plane)
    {
        head = (t_list*)mrt->plane;
        mrt->plane = mrt->plane->next;
        free(head);
    }
    while (mrt->sphere)
    {
        head = (t_list*)mrt->sphere;
        mrt->sphere = mrt->sphere->next;
        free(head);
    }
    while (mrt->cynd)
    {
        head = (t_list*)mrt->cynd;
        mrt->cynd = mrt->cynd->next;
        free(head);
    }
    return (0);
}
