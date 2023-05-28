#include "minirt.h"

// double ft_hitSphere(t_object *spr, t_ray *r, t_rec *rec)
// {
//     t_vec3 oc = ft_vec3minus(r->orig, spr->orig);
//     double a = ft_vec3dot(r->dir, r->dir);
//     double b = 2 * ft_vec3dot(oc, r->dir);
//     double c = ft_vec3dot(oc, oc) - (spr->r * spr->r);
//     double dis = b * b - (4 * a * c);
//     if (dis < 0)
//         return (0);
//     double sdis = sqrt(dis);
//     double t1 = (-b - sdis) / (2. * a);
//     double t2 = (-b + sdis) / (2. * a);
    
//     if (t1 > t2)
//         t1 = t2;
//     if (t1 < 0)
//     {
//         t1 = t2;
//         if (t1 < 0)
//             return (0);
//     }
//     if (t1 > rec->tnear)
//         return (0);
//     rec->tnear = t1;
//     // set phit and normal vector
//     rec->hit = 1;
//     rec->phit = ft_lookAt(r, rec->tnear);
//     rec->normal = ft_vec3Unit(ft_vec3minus(rec->phit, spr->orig));
//     rec->color = spr->color;
//     return (1);
// }

// // still fail to render
// double ft_hitPlane(t_object *plane, t_ray *r, t_rec *rec)
// {
//     double t;
//     double denom = ft_vec3dot(plane->normal, r->dir);
//     if (fabs(denom) > 0.0001)
//     {
//         t_vec3 pl = ft_vec3minus(plane->orig, r->orig);
//         t = ft_vec3dot(pl, plane->normal) / denom;
//         if (t > 0.0001 && t < rec->tnear)
//         {
//             rec->hit = 1;
//             rec->normal = ft_vec3Unit(plane->normal);
//             rec->phit = ft_lookAt(r, t);
//             rec->color = plane->color;
//             rec->tnear = t;
//             return (1);
//         }
//     }
//     return (0);
// }

// int ft_hitDisc(t_object *disc, t_ray *r, t_rec *rec, double rd)
// {
//     t_vec3 oc = ft_vec3minus(disc->orig, r->orig);
//     if (ft_vec3dot(r->dir, disc->normal) == 0.0)
//         return (0);
//     double t = ft_vec3dot(oc, disc->normal) / ft_vec3dot(r->dir, disc->normal);
//     t_vec3 p = ft_vec3plus(r->orig, ft_vec3mul(r->dir, t));
//     if (t < rec->tnear && ft_vec3Len(ft_vec3minus(p, disc->orig)) <= rd)
//     {
//         rec->hit = 1;
//         rec->normal = ft_vec3Unit(disc->normal);
//         rec->phit = ft_lookAt(r, t);
//         rec->color = disc->color;
//         rec->tnear = t;
//         return (1);
//     }
//     return (0);
// }

// int ft_hitCylinder(t_object *cy, t_ray *r, t_rec *rec)
// {
//     t_vec3 x = ft_vec3minus(r->orig, cy->orig);
// 	double dv = ft_vec3dot(r->dir, cy->normal);
// 	double xv = ft_vec3dot(x, cy->normal);
// 	double a = pow(ft_vec3Len(r->dir), 2) - pow(dv, 2);
//     double hb = ft_vec3dot(x, r->dir) - (dv * xv);
//     double c = pow(ft_vec3Len(x), 2) - ((cy->dmt * cy->dmt) / 4.0) - pow(xv, 2);
//     double dis = (hb * hb) - (a * c);
//     if (dis < 0.0 || a == 0)
//         return (0);
//     double t = (- hb - sqrt(dis)) / a;
//     t_vec3 p = ft_vec3plus(r->orig, ft_vec3mul(r->dir, t));
//     t_vec3 diff = ft_vec3minus(cy->orig, p);
//     if (fabs(ft_vec3dot(diff, cy->normal)) <= (cy->height / 2))
//         return (t);
//     cy->pl1->orig = ft_vec3plus(cy->orig, ft_vec3mul(cy->normal, (cy->height / 2)));
//     cy->pl2->orig = ft_vec3minus(cy->orig, ft_vec3mul(cy->normal, (cy->height / 2)));
//     cy->pl1->normal = cy->normal;
//     cy->pl2->normal = cy->normal;
//     if (ft_hitDisc(cy->pl1, r, rec, cy->dmt / 2) && ft_hitDisc(cy->pl2, r, rec, cy->dmt / 2))
//         return (1);
//     return (0);
    
    // double a = pow(r->dir.x, 2) + pow(r->dir.z, 2);
    // double b = 2.0 * (obj->orig.x * r->dir.x + obj->orig.z * r->dir.z);
    // double c = pow(obj->orig.x, 2) + pow(obj->orig.z, 2) - pow(obj->r, 2);
    // double dis = (b * b) - (4.0 * a * c);
    // if (dis < 0)
    //     return (0);
    // double sdis = sqrt(dis);

    // double t1 = (-b - sdis) / (2. * a);
    // double t2 = (-b + sdis) / (2. * a);
    
    // if (t1 > t2)
    //     t1 = t2;
    // if (t1 < 0)
    // {
    //     t1 = t2;
    //     if (t1 < 0)
    //         return (0);
    // }
    // // printf("Hit cynlinder : %.2f\n", t2);
    // if (t1 > rec->tnear)
    //     return (0);
    // rec->tnear = t1;
    // // set phit and normal vector
    // rec->hit = 1;
    // rec->phit = ft_lookAt(r, rec->tnear);
    // rec->normal = ft_vec3Unit(ft_vec3minus(rec->phit, obj->orig));
    // // rec->normal = ft_vec3Unit((t_vec3){rec->phit.x / obj->r, 0, rec->phit.z / obj->r});
    // rec->color = obj->color;
    // return (1);
}
