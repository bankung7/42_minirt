#include "minirt.h"

double ft_clamp(double v, double min, double max)
{
    if (v < min)
        return (min);
    if (v > max)
        return (max);
    return (v);
}

// try read attr
void ft_readAttr(char **attr)
{
    int i = 0;
    while (attr && attr[i])
        printf("%s\n", attr[i++]);
}

// arr length
int ft_arrLen(char **arr)
{
    int i = 0;
    while (arr && arr[i])
        i++;
    return (i);
}

// vetor info
void ft_vec3Info(t_vec3 v)
{
    printf("[%.1f][%.1f][%.1f]\n", v.x, v.y, v.z);
}

void ft_addLight(t_light **lght, t_light *node)
{
    t_light *head;
    head = *lght;
    if (!head)
        *lght = node;
    else
    {
        while (head->next)
            head = head->next;
        head->next = node;
    }
}

void ft_addObject(t_object **obj, t_object *node)
{
    t_object *head;
    head = *obj;
    if (!head)
        *obj = node;
    else
    {
        while (head->next)
            head = head->next;
        head->next = node;
    }
}

void ft_addCamera(t_cam **cam, t_cam *node)
{
    t_cam *head;
    head = *cam;
    if (!head)
        *cam = node;
    else
    {
        while (head->next)
            head = head->next;
        head->next = node;
    }
}