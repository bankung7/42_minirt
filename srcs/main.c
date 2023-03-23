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

    t_mrt mrt;
    // ft_parsing(&mrt, argv[1]);

    // setting up in setup.c
    ft_setup(&mrt);
    
    ft_render(&mrt);

    mlx_hook(mrt.mlx_win, 2, 1L<<0, ft_keyhook, &mrt);
    mlx_loop(mrt.mlx);

    printf("end of line\n");
    return (0);
}