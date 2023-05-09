#include "minirt.h"

int main(int argc, char **argv)
{
    t_mrt mrt;
    
    // parsing
    if (argc != 2)
        return (ft_log("Error\nUsage: ./minirt [file]", 0));

    // setup mlx
    ft_setup(&mrt);

    if (ft_parsing(&mrt, argv[1]))
        return (1);

    ft_parameter(&mrt);
    ft_render(&mrt);
    return (0);
}
