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

bool ft_hitSphere(t_vec o, double rd, t_ray r)
{
    t_vec oc = ft_vecMinus(o, r.o);
    // sleep(1);
    double a = ft_vecDot(r.dir, r.dir);
    double b = 2.0 * ft_vecDot(oc, r.dir);
    double c = ft_vecDot(oc, oc) - (rd * rd);
    double dis = (b * b) - (4.0 * a * c);
    // printf("[%f][%f][%f]\n", b, c, dis);
    return (dis > 0);
}

int ft_rayColor(t_ray r)
{
    if (ft_hitSphere((t_vec){0, 0, -1}, 0.5, r))
        return (255 << 16);
    t_vec uni = ft_vecNrml(r.dir);
    double t = 0.5 * (uni.y + 1.0);
    t_vec c = ft_vecMul((t_vec){1, 1, 1}, (1.0 - t));
    c = ft_vecPlus(c, ft_vecMul((t_vec){0.5, 0.7, 1.0}, t));
    c = ft_vecMul(c, 255);
    return ((int)c.x << 16 | (int)c.y << 8 | (int)c.z);
}

// ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
t_ray ft_createRay(t_cam cam, double u, double v)
{
    t_ray r;
    r.o = cam.crdt;
    // fixed ray direction
    r.dir.x = cam.llc.x + u * cam.hoz.x + v * cam.vet.x;
    r.dir.y = cam.llc.y + u * cam.hoz.y + v * cam.vet.y;
    r.dir.z = cam.llc.z + u * cam.hoz.z + v * cam.vet.z;
    // ft_info(r.dir);
    return (r);
}

// u = l + (r - l)(i + 0.5)/Nx
// v = b + (t - b)(j + 0.5)/Ny

// Ray direction → -d*(w-axis) + u*(u-axis) + v*(v-axis)
