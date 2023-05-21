#include "minirt.h"

int shadow(t_mrt *mrt , t_ray *r, double length)
{
    t_rec rec;
    rec.hit = 0;
    rec.tnear = INFINITY;
    rec.tmin = 1;
    rec.tmax = INFINITY;
    t_object *obj = mrt->obj;

    while (obj)
    {
        if (obj->type == 0)
            hitSphere(mrt, r, obj, &rec);
        else if (obj->type == 1)
            hitPlane(mrt, r, obj, &rec);
        if (rec.hit == 1 && rec.tnear < length)
            return (1);
        obj = obj->next;
    }
    return (0);
}

int shading(t_mrt *mrt, t_rec *rec)
{
    if (rec->hit == 0)
        return (0);
    
    // ambient
    t_vec3 ambient = vec3Mul(mrt->ambt->color, mrt->ambt->ratio);
    // ambient = vec3(0, 0, 0);
    
    // shadow
    t_ray sray;
    sray.orig = rec->phit;
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
