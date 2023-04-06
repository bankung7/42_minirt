#include "minirt.h"

int main(int argc, char **argv)
{
    printf("Welcome to RayTracer\n");
    if (argc != 2)
        return (ft_error("usage: ./minirt [filename]", 1));

    // parsing
    t_mrt mrt;
    mrt.light = 0;
    mrt.plane = 0;
    mrt.sphere = 0;
    mrt.cylinder = 0;
    if (ft_parsing(&mrt, argv[1]))
        return (ft_clean(&mrt));

    ft_readEnv(&mrt);

    // setting up in setup.c
    ft_setup(&mrt);
    
    ft_render(&mrt);

    mlx_hook(mrt.mlx_win, 2, 1L<<0, ft_keyhook, &mrt);
    mlx_loop(mrt.mlx);

    ft_clean(&mrt);
    printf("end of program\n");
    return (0);
}
