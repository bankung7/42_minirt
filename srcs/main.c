#include <stdio.h>
#include "minirt.h"

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
            double u = (double)i / (W_WIDTH - 1);
            double v = (double)j / (mrt.w_hgt - 1);
            // create ray here
            ft_mlx_put_pixel(&mrt.img, i, j, ft_rayColor(ft_createRay(mrt.cam, u, v)));
        }
    }

    mlx_put_image_to_window(mrt.mlx, mrt.mlx_win, mrt.img.img, 0, 0);
    mlx_loop(mrt.mlx);

    printf("end of line\n");
    return (0);
}