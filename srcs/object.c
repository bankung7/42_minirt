#include "minirt.h"

int addObject(t_mrt *mrt, t_object *node)
{
    t_object *head;
    head = mrt->obj;
    if (!head)
        mrt->obj = node;
    else
    {
        while (head->next)
            head = head->next;
        head->next = node;
    }
    return (0);
}

int addLight(t_mrt *mrt, t_light *node)
{
    t_light *head;

    head = mrt->lght;
    if (!head)
        mrt->lght = node;
    // else
    // {
    //     while (head->next)
    //         head = head->next;
    //     head->next = node;
    // }    
    return (0);
}