#include "minirt.h"

int freeType(t_mrt *mrt, int type)
{
    t_object *head = mrt->obj;
    t_object *head2 = head;
    if (!head)
        return (0);
    printf("this case\n");
    while (head)
    {
        if (head->type == type)
        {
            head = head->next;
            free(head2);
            head2->next = head;
        }
        head = head->next;
        head2 = head;
    }
    return (0);
}

///////////////// error here ///////////////////
int checkUnique(t_mrt *mrt, int type, int unique)
{
    t_object *head = mrt->obj;

    if (!head)
        return (0); 
    while (head)
    {
        if (head->type == type && head->unique == 1)
            return (1);
        else if (head->type == type && unique == 1)
            return (freeType(mrt, type));
        head = head->next;
    }
    return (0);
}

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

int getSphere(t_mrt *mrt, char **attr, int unique)
{
    // check unique
    if (checkUnique(mrt, SPHERE, unique))
        return (free2(attr));
    t_object *obj = malloc(sizeof(t_object));
    if (!obj)
        return (qCode(mrt, 1));
    obj->orig = getVec3(mrt, attr[1], 1);
    obj->radius = getDouble(attr[2]) / 2.0;
    obj->color = getVec3(mrt, attr[3], 255);
    free2(attr);
    obj->type = SPHERE;
    obj->unique = unique;
    obj->next = 0;
    checkVec3(mrt, obj->orig, -INFINITY, INFINITY);
    checkValue(mrt, obj->radius, 0, INFINITY);
    checkVec3(mrt, obj->color, 0, 1);
    if (mrt->qcode)
        return (elog("Sphere parsing fail", mrt->qcode));
    addObject(mrt, obj);
    printf("Sphere parsing completed\n");
    return (mrt->qcode);
}

int getPlane(t_mrt *mrt, char **attr, int unique)
{
    // check unique
    t_object *obj = malloc(sizeof(t_object));
    if (!obj)
        return (qCode(mrt, 1));
    obj->orig = getVec3(mrt, attr[1], 1);
    obj->rot = getVec3(mrt, attr[2], 1);
    obj->color = getVec3(mrt, attr[3], 255);
    free2(attr);
    obj->type = PLANE;
    obj->unique = unique;
    obj->next = 0;
    checkVec3(mrt, obj->orig, -INFINITY, INFINITY);
    checkVec3(mrt, obj->rot, -1.0, 1.0);
    checkVec3(mrt, obj->color, 0, 1);
    if (mrt->qcode)
        return (elog("Plane parsing fail", mrt->qcode));
    addObject(mrt, obj);
    printf("Plane parsing completed\n");
    return (mrt->qcode);
}

// get Cylinder
int getCylinder(t_mrt *mrt, char **attr, int unique)
{
    // check unique
    t_object *obj = malloc(sizeof(t_object));
    if (!obj)
        return (qCode(mrt, 1));
    obj->orig = getVec3(mrt, attr[1], 1);
    obj->rot = getVec3(mrt, attr[2], 1);
    obj->radius = getDouble(attr[3]) / 2.0;
    obj->height = getDouble(attr[4]);
    obj->color = getVec3(mrt, attr[5], 255);
    free2(attr);
    obj->type = CYLINDER;
    obj->unique = unique;
    obj->next = 0;
    checkVec3(mrt, obj->orig, -INFINITY, INFINITY);
    checkVec3(mrt, obj->rot, -1.0, 1.0);
    checkValue(mrt, obj->radius, 0, INFINITY);
    checkValue(mrt, obj->height, 0, INFINITY);
    checkVec3(mrt, obj->color, 0, 1);
    if (mrt->qcode)
        return (elog("Sphere parsing fail", mrt->qcode));
    addObject(mrt, obj);
    printf("Sphere parsing completed\n");
    return (mrt->qcode);
}

int getObject(t_mrt *mrt, char **attr)
{
    if (!ft_strncmp(attr[0], "SP", 3) && arrLen(attr) == 4)
        return (getSphere(mrt, attr, 1));
    if (!ft_strncmp(attr[0], "sp", 3) && arrLen(attr) == 4)
        return (getSphere(mrt, attr, 0));
    if (!ft_strncmp(attr[0], "PL", 3) && arrLen(attr) == 4)
        return (getPlane(mrt, attr, 1));
    if (!ft_strncmp(attr[0], "pl", 3) && arrLen(attr) == 4)
        return (getPlane(mrt, attr, 0));
    if (!ft_strncmp(attr[0], "CY", 3) && arrLen(attr) == 6)
        return (getCylinder(mrt, attr, 1));
    if (!ft_strncmp(attr[0], "cy", 3) && arrLen(attr) == 6)
        return (getCylinder(mrt, attr, 0));
    free2(attr);
    return (0);
}