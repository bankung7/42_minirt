#include "minirt.h"

void ft_rayInfo(t_ray *r)
{
    printf("dir %.2f, %.2f, %.2f\n", r->dir.x, r->dir.y, r->dir.z);
}

t_ray ft_makeRay(t_mrt *mrt, double x, double y)
{
    t_ray ray;

    ray.o = mrt->cam.o;
    ray.dir = (t_vec3){x, y, -1};
    return (ray);
}

int ft_traceSphere(t_mrt *mrt, t_ray *r, t_sphere *spr)
{
    (void)mrt;
    t_vec3 oc = ft_vec3Minus(r->o, spr->o);
    double a = ft_vec3Dot(r->dir, r->dir);
    double b = 2 * ft_vec3Dot(oc, r->dir);
    double c = ft_vec3Dot(oc, oc) - (spr->r * spr->r);
    double dis = b * b - (4 * a * c);
    // printf("dis : %.2f\n", dis);
    return (dis > 0);
}

int ft_traceRay(t_mrt *mrt, t_ray *ray)
{
    mrt->sphere = malloc(sizeof(t_sphere));
    mrt->sphere->o = (t_vec3){0, -100.5, -1};
    mrt->sphere->r = 100;
    return (ft_traceSphere(mrt, ray, mrt->sphere));
}

int main(void)
{
    // setup
    t_mrt mrt;
    mrt.width = 640;
    mrt.height = 480;
    mrt.cam.fov = 90;

    ft_setupMLX(&mrt);

    double scale = tanf(mrt.cam.fov * 0.5 * M_PI / 180.0);
    double aspectRatio = mrt.width / (double)mrt.height;
    mrt.cam.o = (t_vec3){0, 0, 0};

    for (int j = 0; j < mrt.height; ++j)
    {
        for (int i = 0; i < mrt.width; ++i)
        {
            double x = (2 * i / (double)mrt.width - 1) * scale * aspectRatio;
            double y = (1 - 2 * j / (double)mrt.height) * scale;
            t_ray ray = ft_makeRay(&mrt, x, y);
            // ft_rayInfo(&ray);
            if (ft_traceRay(&mrt, &ray) == 1)
                ft_putPixel(&mrt.mlx, i, j, 0xFF0000);
            else
                ft_putPixel(&mrt.mlx, i, j, 0xFFFFFF);
            // printf("x,y [%.2f][%.2f]\n", x, y);
        }
    }

    mlx_put_image_to_window(mrt.mlx.mlx, mrt.mlx.mlx_win, mrt.mlx.img, 0, 0);
    mlx_loop(mrt.mlx.mlx);
    return (0);
}