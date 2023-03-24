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

double ft_hitSphere(t_vec o, double rd, t_ray r)
{
    t_vec oc = ft_vecMinus(r.o, o);
    double a = pow(ft_vecLen(r.dir), 2);
    double hb = ft_vecDot(oc, r.dir);
    double c = pow(ft_vecLen(oc), 2) - (rd * rd);
    double dis = (hb * hb) - (a * c);
    if (dis < 0)
        return (-1.0);
    // printf("[%f]\n", (-hb - sqrt(dis)) / a);
    return ((-hb - sqrt(dis)) / a);
}

int ft_rayColor(t_mrt *mrt, t_ray r)
{
    (void)mrt;
    // printf("test %f\n", mrt->sphere->dmt);
    double t = ft_hitSphere((t_vec){0, 0, -1}, ft_convertVP(mrt, mrt->sphere->dmt), r);
    // double t = ft_hitSphere(ft_convertVec(mrt, mrt->sphere->crdt), ft_convertVP(mrt, mrt->sphere->dmt), r);
    
    if (t > 0.0)
    {
        // printf("[%f]\n", t);
        t_vec pAt = ft_vecPlus(r.o, ft_vecMul(r.dir, t));
        t_vec uni = ft_vecNrml(ft_vecMinus(pAt, (t_vec){0, 0, -1}));
        t_vec c = ft_vecMul((t_vec){uni.x + 1, uni.y + 1, uni.z + 1}, 0.5);
        c = ft_vecMul(c, 255);
        return ((int)c.x << 16 | (int)c.y << 8 | (int)c.z);
    }
    t_vec uni = ft_vecNrml(r.dir);
    t = 0.5 * (uni.y + 1.0);
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

double ft_convertVP(t_mrt *mrt, double n)
{
    return (n * mrt->cam.vpWdt / W_WIDTH);
}

t_vec ft_convertVec(t_mrt *mrt, t_vec v)
{
    double c = mrt->cam.vpWdt / W_WIDTH;
    return ((t_vec){v.x * c, v.y * c, v.z * c});
}

// u = l + ( - l)(i + 0.5)/Nx
// v = b + (t - b)(j + 0.5)/Ny

// Ray direction → -d*(w-axis) + u*(u-axis) + v*(v-axis)
