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
    if (mrt->ambt)
        free(mrt->ambt);
    if (mrt->cam)
        free(mrt->cam);
    while (mrt->light)
    {
        head = (t_list*)mrt->light;
        mrt->light = mrt->light->next;
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
    while (mrt->cylinder)
    {
        head = (t_list*)mrt->cylinder;
        mrt->cylinder = mrt->cylinder->next;
        free(head);
    }
    return (0);
}
