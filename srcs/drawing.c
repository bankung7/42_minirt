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

// may thing still wrong here
bool ft_hitSphere(t_vec o, double rd, t_ray r)
{
    t_vec oc;
    oc = ft_vecMinus(r.o, o);
    double a = 1;
    double b = 2.0 * ft_vecDot(oc, r.dir);
    double c = ft_vecDot(oc, oc) - (rd * rd);
    double dis = (b * b) - (4 * a * c);
    return (dis > 0);
}

int ft_rayColor(t_ray ray)
{
    // sphere center
    t_vec v;
    v.x = 0;
    v.y = 0;
    v.z = -1;
    if (ft_hitSphere(v, 0.5, ray))
        return (255 << 16);

    t_vec uVec;
    uVec = ft_vecNrml(ray.dir);
    double t = 0.5 * (uVec.y + 1);
    (void)t;
    return (100 << 8 | 200);
}

t_ray ft_createRay(t_cam cam, double u, double v)
{
    t_ray r;
    r.o = ft_vecMul(cam.crdt, 1);
    r.dir = ft_vecPlus(ft_vecMul(cam.llc, 1), ft_vecMul(cam.hoz, u));
    r.dir = ft_vecPlus(r.dir, ft_vecMul(cam.vet, v));
    r.dir = ft_vecMinus(r.dir, r.o);
    return (r);
}