#include "minirt.h"

void ft_mlx_put_pixel(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->len + x * (data->bpp / 8));
    *(unsigned int *)dst = color;
}

int ft_makeColor(t_color c)
{
    return (c.r << 16 | c.g << 8 | c.b);
}

// o = Sphere center, rd = Radius, r = Ray
double ft_hitSphere(t_sphere sp, t_ray r)
{
    t_vec oc = ft_vecMinus(r.o, sp.crdt);
    double a = pow(ft_vecLen(r.dir), 2);
    double hb = ft_vecDot(oc, r.dir);
    // double b = 2.0 * ft_vecDot(oc, r.dir);
    double c = pow(ft_vecLen(oc), 2) - ((sp.dmt / 2.0) * (sp.dmt / 2.0));
    double dis = (hb * hb) - (a * c);
    // double dis = (b * b) - (4.0 * a * c);
    // return ((- b - sqrt(dis)) / (2.0 * a));
    if (dis < 0.0 || a == 0)
        return (INFINITY);
    return ((- hb - sqrt(dis)) / a);
    // if (dis < 0)
    //     return (-1.0);
    // printf("[%f]\n", (-hb - sqrt(dis)) / a);
    // return ((-hb - sqrt(dis)) / a);
}

double ft_hitPlane(t_plane pl, t_ray r)
{
    t_vec oc = ft_vecMinus(pl.crdt, r.o);
    if (ft_vecDot(r.dir, pl.rot) == 0.0)
        return (INFINITY);
    double t = ft_vecDot(oc, pl.rot) / ft_vecDot(r.dir, pl.rot);
    return (t);
}

int ft_rayColor(t_ray r)
{
    // double t = ft_hitSphere((t_sphere){(t_vec){0,0,-1}, 1.0, (t_color){255,0,0}, NULL}, r);
    double mint = INFINITY;
    double t = INFINITY;
    t_color cl;
    t_sphere sp1, sp2;
    sp1.crdt = (t_vec){0,0,-1};
    sp1.dmt = 0.5;
    sp1.color = (t_color){255,0,0};
    sp1.next = &sp2;
    sp2.crdt = (t_vec){0.5,0,-1.5};
    sp2.dmt = 0.7;
    sp2.color = (t_color){0,255,0};
    sp2.next = NULL;

    t_plane pl1, pl2;
    pl1.crdt = (t_vec){0,0,-2.0};
    pl1.rot = (t_vec){0,0,1.0};
    pl1.color = (t_color){100,10,100};
    pl1.next = &pl2;
    pl2.crdt = (t_vec){0,0,-2.0};
    pl2.rot = (t_vec){0,sin(3.14/4),cos(3.14/4)};
    pl2.color = (t_color){10,100,100};
    pl2.next = NULL;
    t_plane *ptrp;
    ptrp = &pl1;
    while (ptrp)
    {
        t = ft_hitPlane(*ptrp, r);
        if (t < mint)
        {
            mint = t;
            cl = ptrp->color;
        }
        ptrp = ptrp->next;
    }
    t_sphere *ptr;
    ptr = &sp1;
    while (ptr)
    {
        t = ft_hitSphere(*ptr, r);
        if (t < mint)
        {
            mint = t;
            cl = ptr->color;
        }
        ptr = ptr->next;
    }
    // printf("sp.dmt = %f\n", t);
    if (mint == INFINITY)
        return (ft_makeColor((t_color){0,0,255}));
    if (mint > 0.0)
    {
        // printf("[%f]\n", t);
        // t_vec pAt = ft_vecPlus(r.o, ft_vecMul(r.dir, t));
        // t_vec uni = ft_vecNrml(ft_vecMinus(pAt, (t_vec){0, 0, -1}));
        // t_vec c = ft_vecMul((t_vec){uni.x + 1, uni.y + 1, uni.z + 1}, 0.5);
        // c = ft_vecMul(c, 255);
        // return ((int)c.x << 16 | (int)c.y << 8 | (int)c.z);
        return (ft_makeColor(cl));
    }
    // t_vec uni = ft_vecNrml(r.dir);
    // t = 0.5 * (uni.y + 1.0);
    // t_vec c = ft_vecMul((t_vec){1, 1, 1}, (1.0 - t));
    // c = ft_vecPlus(c, ft_vecMul((t_vec){0.5, 0.7, 1.0}, t));
    // c = ft_vecMul(c, 255);
    // return ((int)c.x << 16 | (int)c.y << 8 | (int)c.z);
    return (ft_makeColor((t_color){0,0,0}));
}

// ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
t_ray ft_createRay(t_cam cam, double u, double v)
{
    t_ray r;
    r.o = cam.crdt;
    // fixed ray direction
    // r.dir.x = cam.llc.x + u * cam.hoz.x + v * cam.vet.x;
    // r.dir.y = cam.llc.y + u * cam.hoz.y + v * cam.vet.y;
    // r.dir.z = cam.llc.z + u * cam.hoz.z + v * cam.vet.z;
    r.dir.x = cam.llc.x + u * cam.hoz.x + v * cam.vet.x - cam.crdt.x;
    r.dir.y = cam.llc.y + u * cam.hoz.y + v * cam.vet.y - cam.crdt.y;
    r.dir.z = cam.llc.z + u * cam.hoz.z + v * cam.vet.z - cam.crdt.z;
    // ft_info(r.dir);
    return (r);
}

// u = l + (r - l)(i + 0.5)/Nx
// v = b + (t - b)(j + 0.5)/Ny

// Ray direction → -d*(w-axis) + u*(u-axis) + v*(v-axis)
