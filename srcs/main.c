#include <stdio.h>
#include "minirt.h"
#include <time.h>

int main(int argc, char **argv)
{
    printf("Welcome to RayTracer\n");
    if (argc != 2)
        return (ft_error("usage: ./minirt [filename]", 1));

    t_mrt mrt;
    mrt.status = 0;
    ft_parsing(&mrt, argv[1]);
    ft_readSphere(&mrt);

    // setting up in setup.c
    // ft_setup(&mrt);
    
    // ft_render(&mrt);

    // mlx_hook(mrt.mlx_win, 2, 1L<<0, ft_keyhook, &mrt);
    // mlx_loop(mrt.mlx);
    ft_end(&mrt, 0);
    printf("end of program\n");
    return (0);
}