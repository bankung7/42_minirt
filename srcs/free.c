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

int ft_end(t_mrt *mrt, int res)
{
    t_list *head;

    while (mrt->sphere)
    {
        head = (t_list*)mrt->sphere;
        mrt->sphere = mrt->sphere->next;
        free(head);
    }
    return (res);
}