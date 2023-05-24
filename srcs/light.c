#include "minirt.h"

// add Light
int addLight(t_mrt *mrt, t_light *node)
{
    t_light *head;

    head = mrt->lght;
    if (!head)
        mrt->lght = node;
    else
    {
        while (head->next)
            head = head->next;
        head->next = node;
    }    
    return (0);
}

// get Light
int getLight(t_mrt *mrt, char **attr, int unique)
{
    t_light *lght;

    if (mrt->lght && mrt->lght->unique == 1)
        return (0);
    if (mrt->lght && unique == 1)
        freeList((t_list*)mrt->lght);
    lght = malloc(sizeof(t_light));
    if (!lght)
        return (qCode(mrt, 1));
    lght->orig = getVec3(mrt, attr[1], 1);
    lght->ratio = getDouble(attr[2]);
    lght->color = getVec3(mrt, attr[3], 255);
    free2(attr);
    lght->unique = unique;
    lght->next = 0;
    checkVec3(mrt, lght->orig, -INFINITY, INFINITY);
    checkValue(mrt, lght->ratio, 0, 1.0);
    checkVec3(mrt, lght->color, 0, 1);
    if (mrt->qcode)
        return (elog("Light parsing fail", mrt->qcode));
    addLight(mrt, lght);
    printf("Light parsing completed\n");
    return (mrt->qcode);
}

// Shadowing
int shadow(t_mrt *mrt , t_ray *r, double length)
{
    t_rec rec;
    t_object *obj;

    rec.hit = 0;
    rec.tnear = INFINITY;
    rec.tmin = 1;
    rec.tmax = INFINITY;
    obj = mrt->obj;
    while (obj)
    {
        if (obj->type == SPHERE)
            hitSphere(mrt, r, obj, &rec);
        else if (obj->type == PLANE)
            hitPlane(mrt, r, obj, &rec);
        if (rec.hit == 1 && rec.tnear < length)
            return (1);
        obj = obj->next;
    }
    return (0);
}

// shading
int shading(t_mrt *mrt, t_rec *rec)
{
    if (rec->hit == 0)
        return (0);
    
    // ambient
    t_vec3 ambient = vec3Mul(mrt->ambt->color, mrt->ambt->ratio);
    // ambient = vec3(0, 0, 0);
    
    // shadow
    t_ray sray;
    sray.orig = vec3Plus(rec->phit, vec3Mul(rec->normal, 1e-4));
    sray.dir = vec3Minus(mrt->lght->orig, rec->phit);
    double length = vec3Len(sray.dir);
    sray.dir = vec3Unit(sray.dir);
    if (shadow(mrt, &sray, length) == 1)
    {
        rec->color = vec3Mulvec3(ambient, rec->color);
        return (0);
    }
    
    // diffuse
    double dratio = 0.6;
    t_vec3 light = vec3Unit(vec3Minus(mrt->lght->orig, rec->phit));
    double factor = fmax(0.0, vec3Dot(rec->normal, light));
    // printf("factor : %.2f\n", factor);
    t_vec3 diffuse = vec3Mul(mrt->lght->color, factor * dratio);
    // diffuse = vec3(0,0 ,0);

    // specular
    double sratio = 0.5;
    t_vec3 viewDir = vec3Unit(vec3Minus(mrt->cam->orig, rec->phit));
    t_vec3 reflect = vec3Mul(rec->normal, (2.0 * vec3Dot(light, rec->normal)));
    reflect = vec3Unit(vec3Minus(reflect, light));
    double spec = pow(fmax(vec3Dot(viewDir, reflect), 0.0), 32);
    t_vec3 specular = vec3Mul(mrt->lght->color, spec * sratio);
    // printf("spec : %.2f %.2f %.2f\n", specular.x, specular.y, specular.z);

    // total color
    rec->color = vec3Mulvec3(vec3Plus(vec3Plus(ambient, diffuse), specular), rec->color);
    return (0);
}