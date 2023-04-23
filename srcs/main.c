#include "minirt.h"

void ft_rayInfo(t_ray *r)
{
    printf("dir %.2f, %.2f, %.2f\n", r->dir.x, r->dir.y, r->dir.z);
}

void ft_setSphere(t_mrt *mrt)
{
    mrt->sphere[0].o = (t_vec3){0, 0, -1};
    mrt->sphere[0].r = 0.5;
    mrt->sphere[0].color = (t_vec3){255, 0, 0};
    mrt->sphere[1].o = (t_vec3){0, -100.5, -1};
    mrt->sphere[1].r = 100;
    mrt->sphere[1].color = (t_vec3){200, 200, 200};
    mrt->sphere[2].o = (t_vec3){-1, 0, -1};
    mrt->sphere[2].r = 0.5;
    mrt->sphere[2].color = (t_vec3){0, 0, 255};
    mrt->sphere[3].o = (t_vec3){1, 0, -1};
    mrt->sphere[3].r = 0.5;
    mrt->sphere[3].color = (t_vec3){0, 255, 0};
}

int main(void)
{
    // setup
    t_mrt mrt;

    // image
    mrt.width = 800;
    mrt.aRatio = 16.0 / 9.0;
    mrt.height = (int)(mrt.width / mrt.aRatio);

    // camera
    double vh = 2.0;
    double vw = mrt.aRatio * vh;
    double flen = 1.0;

    mrt.cam.o = (t_vec3){0, 0, 0};
    t_vec3 hoz = (t_vec3){vw, 0, 0};
    t_vec3 ver = (t_vec3){0, vh, 0};
    t_vec3 llc = (t_vec3){
        mrt.cam.o.x - hoz.x / 2 - ver.x / 2 - 0,
        mrt.cam.o.y - hoz.y / 2 - ver.y / 2 - 0,
        mrt.cam.o.z - hoz.z / 2 - ver.z / 2 - flen
    };

    ft_setupMLX(&mrt);
    ft_setSphere(&mrt);

    // render
    for (int j = 0; j < mrt.height; ++j)
    {
        for (int i = 0; i < mrt.width; ++i)
        {
            double u = (double)i / (mrt.width - 1);
            double v = (double)j / (mrt.height - 1);
            t_ray r = ft_makeRay(&mrt, llc, ft_vec3Mul(hoz, u), ft_vec3Mul(ver, v));
            ft_putPixel(&mrt.mlx, i, mrt.height - j, ft_rayColor(&mrt, &r));
            // ft_rayInfo(&r);
        }
    }

    // render

    mlx_put_image_to_window(mrt.mlx.mlx, mrt.mlx.mlx_win, mrt.mlx.img, 0, 0);
    mlx_loop(mrt.mlx.mlx);
    return (0);
}