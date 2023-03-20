#include <stdio.h>
#include "minirt.h"
#include <time.h>

int main(int argc, char **argv)
{
    (void)argv;

    printf("Welcome to RayTracer\n");
    if (argc != 2)
    {
        printf("./minirt [file.rt]\n");
        return (1);
    }

    // setting up in seup.c
    t_mrt mrt;
    ft_setup(&mrt);
    
    // render
    for (int j = mrt.w_hgt - 1; j >= 0; --j)
    {
        for (int i = 0; i < W_WIDTH; ++i)
        {
            double v = (double)j / mrt.w_hgt;
            double u = (double)i / W_WIDTH;
            t_ray r = ft_createRay(mrt.cam, u, v);
            // ft_info(r.dir);
            ft_mlx_put_pixel(&mrt.img, i, j, ft_rayColor(r));
            // printf("[%f][%f]\n", u, v);
        }
    }

    mlx_put_image_to_window(mrt.mlx, mrt.mlx_win, mrt.img.img, 0, 0);
    mlx_loop(mrt.mlx);


    printf("end of line\n");
    return (0);
}