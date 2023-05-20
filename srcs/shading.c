#include "minirt.h"

int shading(t_mrt *mrt, t_rec *rec)
{
    if (rec->hit == 0)
        return (0);
    
    // ambient
    t_vec3 ambient = vec3Mul(mrt->ambt.color, mrt->ambt.ratio);
    // ambient = vec3(0, 0, 0);
    
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
    // if (spec > 0.01)
    //     printf("spec : %.4f\n", spec);
    t_vec3 specular = vec3Mul(mrt->lght->color, spec * sratio);
    // printf("spec : %.2f %.2f %.2f\n", specular.x, specular.y, specular.z);

    // total color
    t_vec3 color = vec3Mulvec3(vec3Plus(vec3Plus(ambient, diffuse), specular), rec->color);
    rec->color = color;
    return (0);
}
