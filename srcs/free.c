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
    t_object *obj = mrt->obj;
    while (obj)
    {
        obj = obj->next;
        free(mrt->obj);
        mrt->obj = obj;
    }
    t_light *lght = mrt->lght;
    while (lght)
    {
        lght = lght->next;
        free(mrt->lght);
        mrt->lght = lght;
    }
    t_cam *cam = mrt->cam;
    while (cam)
    {
        cam = cam->next;
        free(mrt->cam);
        mrt->cam = cam;
    }
    return (0);
}
